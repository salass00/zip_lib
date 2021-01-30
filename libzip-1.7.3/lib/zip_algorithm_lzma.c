/*
 * Copyright (C) 2014-2018 Fredrik Wikstrom <fredrik@a500.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "zipint.h"

#include "lzma/LzmaDec.h"
#include <stdlib.h>
#include <limits.h>

static void *SzAlloc(void *p, size_t size) {
	return malloc(size);
}

static void SzFree(void *p, void *address) {
	free(address);
}

static ISzAlloc alloc = { SzAlloc, SzFree };

struct ctx {
	zip_error_t *error;
	bool compress;
	int compression_flags;
	bool end_of_input;
	size_t avail_in;
	void *next_in;
	union {
		struct {
			CLzmaDec state;
		} dec;
	};
};

static void *
allocate(bool compress, int compression_flags, zip_error_t *error) {
	struct ctx *ctx;

	ctx = (struct ctx *)malloc(sizeof(*ctx));
	if (ctx == NULL)
		return NULL;

	ctx->error = error;
	ctx->compress = compress;
	ctx->compression_flags = compression_flags;
	if (ctx->compression_flags < 1 || ctx->compression_flags > 9) {
		ctx->compression_flags = 9;
	}
	ctx->end_of_input = false;

	if (compress) {
		/* FIXME: Implement compression */
		free(ctx);
		return NULL;
	} else {
		LzmaDec_Construct(&ctx->dec.state);
	}

	return ctx;
}

static void *
decompress_allocate(zip_uint16_t method, int compression_flags, zip_error_t *error) {
	return allocate(false, compression_flags, error);
}

static void
deallocate(void *ud) {
	struct ctx *ctx = (struct ctx *)ud;

	free(ctx);
}

static zip_uint16_t
general_purpose_bit_flags(void *ud) {
	return 0;
}

static bool
start(void *ud) {
	struct ctx *ctx = (struct ctx *)ud;

	ctx->avail_in = 0;
	ctx->next_in = NULL;

	return true;
}

static bool
end(void *ud) {
	struct ctx *ctx = (struct ctx *)ud;

	LzmaDec_Free(&ctx->dec.state, &alloc);

	return true;
}

static int
map_error(SRes res) {
	switch (res) {
		case SZ_OK:
			return ZIP_ER_OK;

		case SZ_ERROR_MEM:
			return ZIP_ER_MEMORY;

		case SZ_ERROR_DATA:
		case SZ_ERROR_UNSUPPORTED:
		case SZ_ERROR_INPUT_EOF:
			return ZIP_ER_COMPRESSED_DATA;

		default:
			return ZIP_ER_INTERNAL;
	}
}

static bool
input(void *ud, zip_uint8_t *data, zip_uint64_t length) {
	struct ctx *ctx = (struct ctx *)ud;

	if (length > UINT_MAX || ctx->avail_in != 0) {
		zip_error_set(ctx->error, ZIP_ER_INVAL, 0);
		return false;
	}

	if (ctx->dec.state.dic == NULL) {
		SRes res;

		if (length < 9) {
			zip_error_set(ctx->error, ZIP_ER_INTERNAL, 0);
			return false;
		}

		if (data[2] != 5 || data[3] != 0) {
			zip_error_set(ctx->error, ZIP_ER_COMPRESSED_DATA, 0);
			return false;
		}

		res = LzmaDec_Allocate(&ctx->dec.state, &data[4], 5, &alloc);
		if (res != SZ_OK) {
			zip_error_set(ctx->error, map_error(res), 0);
			return false;
		}

		LzmaDec_Init(&ctx->dec.state);

		data += 9;
		length -= 9;
	}

	ctx->avail_in = length;
	ctx->next_in = data;

	return true;
}

static void
end_of_input(void *ud) {
	struct ctx *ctx = (struct ctx *)ud;

	ctx->end_of_input = true;
}

static zip_compression_status_t
process(void *ud, zip_uint8_t *data, zip_uint64_t *length) {
	struct ctx *ctx = (struct ctx *)ud;
	const Byte *src;
	Byte *dst;
	SizeT src_len, dst_len;
	ELzmaFinishMode finish_mode;
	ELzmaStatus status;
	SRes res;

	if (ctx->avail_in == 0) {
		*length = 0;
		return ZIP_COMPRESSION_NEED_DATA;
	}

	src = ctx->next_in;
	src_len = ctx->avail_in;

	dst = (Byte *)data;
	dst_len = *length;

	finish_mode = LZMA_FINISH_ANY;

	res = LzmaDec_DecodeToBuf(&ctx->dec.state, dst, &dst_len, src, &src_len, finish_mode, &status);

	ctx->avail_in -= src_len;
	ctx->next_in += src_len;

	*length = dst_len;

	if (res != SZ_OK) {
		zip_error_set(ctx->error, map_error(res), 0);
		return false;
	}

	if (status == LZMA_STATUS_FINISHED_WITH_MARK)
		return ZIP_COMPRESSION_END;

	return ZIP_COMPRESSION_OK;
}

zip_compression_algorithm_t zip_algorithm_lzma_decompress = {
	decompress_allocate,
	deallocate,
	general_purpose_bit_flags,
	63,
	start,
	end,
	input,
	end_of_input,
	process
};

