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

#define LIBRARIES_BZIP2_H
#include <bzlib.h>
#include <interfaces/bzip2.h>
#include "zip-internal.h"

register APTR r13 __asm("r13");

#define _IBZIP2 (((struct ZipIData *)r13)->IBZip2)

int BZ2_bzCompressInit(bz_stream *strm, int blockSize100k, int verbosity, int workFactor)
{
	struct BZip2IFace *IBZip2 = _IBZIP2;
	return IBZip2->BZ2_bzCompressInit(strm, blockSize100k, verbosity, workFactor);
}

int BZ2_bzCompress(bz_stream *strm, int action)
{
	struct BZip2IFace *IBZip2 = _IBZIP2;
	return IBZip2->BZ2_bzCompress(strm, action);
}

int BZ2_bzCompressEnd(bz_stream *strm)
{
	struct BZip2IFace *IBZip2 = _IBZIP2;
	return IBZip2->BZ2_bzCompressEnd(strm);
}

int BZ2_bzDecompressInit(bz_stream *strm, int verbosity, int small)
{
	struct BZip2IFace *IBZip2 = _IBZIP2;
	return IBZip2->BZ2_bzDecompressInit(strm, verbosity, small);
}

int BZ2_bzDecompress(bz_stream *strm)
{
	struct BZip2IFace *IBZip2 = _IBZIP2;
	return IBZip2->BZ2_bzDecompress(strm);
}

int BZ2_bzDecompressEnd(bz_stream *strm)
{
	struct BZip2IFace *IBZip2 = _IBZIP2;
	return IBZip2->BZ2_bzDecompressEnd(strm);
}

