/*
 * Copyright (C) 2014-2017 Fredrik Wikstrom <fredrik@a500.org>
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

#include <lzma.h>
#include <limits.h>
#include <stdlib.h>

struct ctx {
	zip_error_t *error;
	bool compress;
	int compression_flags;
	bool end_of_input;
	lzma_stream zstr;
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

	memset(&ctx->zstr, 0, sizeof(ctx->zstr));

	return ctx;
}

static void *
compress_allocate(zip_uint16_t method, int compression_flags, zip_error_t *error) {
	return allocate(true, compression_flags, error);
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

static int
compression_flags(void *ud) {
	return 0;
}

static int
map_error(lzma_ret ret) {
	switch (ret) {
		case LZMA_OK:
		case LZMA_STREAM_END:
			return ZIP_ER_OK;
		case LZMA_MEM_ERROR:
			return ZIP_ER_MEMORY;
		case LZMA_FORMAT_ERROR:
		case LZMA_DATA_ERROR:
		case LZMA_BUF_ERROR:
			return ZIP_ER_COMPRESSED_DATA;
		case LZMA_OPTIONS_ERROR:
		case LZMA_PROG_ERROR:
			return ZIP_ER_INVAL;
		default:
			return ZIP_ER_INTERNAL;
	}
}

static bool
start(void *ud) {
	struct ctx *ctx = (struct ctx *)ud;
	lzma_ret ret;

	ctx->zstr.avail_in = 0;
	ctx->zstr.next_in = NULL;
	ctx->zstr.avail_out = 0;
	ctx->zstr.next_out = NULL;

	if (ctx->compress) {
		lzma_options_lzma options;

		if (lzma_lzma_preset(&options, ctx->compression_flags)) {
			zip_error_set(ctx->error, ZIP_ER_INTERNAL, 0);
			return false;
		}

		ret = lzma_alone_encoder(&ctx->zstr, &options);
	} else {
		ret = lzma_alone_decoder(&ctx->zstr, UINT64_MAX);
	}

	if (ret != LZMA_OK) {
		zip_error_set(ctx->error, map_error(ret), 0);
		return false;
	}

	return true;
}

static bool
end(void *ud) {
	struct ctx *ctx = (struct ctx *)ud;

	lzma_end(&ctx->zstr);

	return true;
}

static bool
input(void *ud, zip_uint8_t *data, zip_uint64_t length) {
	struct ctx *ctx = (struct ctx *)ud;

	if (length > UINT_MAX || ctx->zstr.avail_in > 0) {
		zip_error_set(ctx->error, ZIP_ER_INVAL, 0);
		return false;
	}

	ctx->zstr.avail_in = length;
	ctx->zstr.next_in = data;

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
	lzma_ret ret;

	if (ctx->zstr.avail_in == 0 && !ctx->end_of_input) {
		*length = 0;
		return ZIP_COMPRESSION_NEED_DATA;
	}

	ctx->zstr.avail_out = ZIP_MIN(UINT_MAX, *length);
	ctx->zstr.next_out = data;

	ret = lzma_code(&ctx->zstr, ctx->end_of_input ? LZMA_FINISH : LZMA_RUN);

	*length = *length - ctx->zstr.avail_out;

	switch (ret) {
		case LZMA_OK:
			if (ctx->zstr.avail_in == 0) {
				return ZIP_COMPRESSION_NEED_DATA;
			}
			return ZIP_COMPRESSION_OK;
		case LZMA_STREAM_END:
			return ZIP_COMPRESSION_END;
		default:
			zip_error_set(ctx->error, map_error(ret), 0);
			return ZIP_COMPRESSION_ERROR;
	}
}

zip_compression_algorithm_t zip_algorithm_lzma_compress = {
	compress_allocate,
	deallocate,
	compression_flags,
	start,
	end,
	input,
	end_of_input,
	process
};

zip_compression_algorithm_t zip_algorithm_lzma_decompress = {
	decompress_allocate,
	deallocate,
	compression_flags,
	start,
	end,
	input,
	end_of_input,
	process
};

