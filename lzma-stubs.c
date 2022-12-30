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

#include <interfaces/lzma.h>
#include "zip-internal.h"

register APTR r13 __asm("r13");

#define _ILZMA (((struct ZipIData *)r13)->ILZMA)

lzma_ret lzma_code(lzma_stream *strm, lzma_action action)
{
	struct LZMAIFace *ILZMA = _ILZMA;
	return ILZMA->lzma_code(strm, action);
}

void lzma_end(lzma_stream *strm)
{
	struct LZMAIFace *ILZMA = _ILZMA;
	return ILZMA->lzma_end(strm);
}

lzma_ret lzma_stream_encoder(lzma_stream *strm, const lzma_filter *filters, lzma_check check)
{
	struct LZMAIFace *ILZMA = _ILZMA;
	return ILZMA->lzma_stream_encoder(strm, filters, check);
}

lzma_ret lzma_alone_encoder(lzma_stream *strm, const lzma_options_lzma *options)
{
	struct LZMAIFace *ILZMA = _ILZMA;
	return ILZMA->lzma_alone_encoder(strm, options);
}

lzma_ret lzma_stream_decoder(lzma_stream *strm, uint64_t memlimit, uint32_t flags)
{
	struct LZMAIFace *ILZMA = _ILZMA;
	return ILZMA->lzma_stream_decoder(strm, memlimit, flags);
}

lzma_ret lzma_alone_decoder(lzma_stream *strm, uint64_t memlimit)
{
	struct LZMAIFace *ILZMA = _ILZMA;
	return ILZMA->lzma_alone_decoder(strm, memlimit);
}

lzma_bool lzma_lzma_preset(lzma_options_lzma *options, uint32_t preset)
{
	struct LZMAIFace *ILZMA = _ILZMA;
	return ILZMA->lzma_lzma_preset(options, preset);
}

