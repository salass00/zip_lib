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

#ifndef ZIP_BASE_H
#define ZIP_BASE_H 1

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/elf.h>
#include <proto/z.h>
#include <proto/bzip2.h>
#include <proto/lzma.h>
#include <proto/amisslmaster.h>
#include <proto/amissl.h>

struct ZipBase {
	struct Library      LibNode;
	BPTR                SegList;
	Elf32_Handle        ElfHandle;

	struct ExecIFace   *IExec;
	struct DOSIFace    *IDOS;
	struct ElfIFace    *IElf;
	struct NewlibIFace *INewlib;
};

struct ZipInterfaceData {
	struct ZIFace            *IZ;
	struct BZip2IFace        *IBZip2;
	struct LZMAIFace         *ILZMA;
	struct AmiSSLMasterIFace *IAmiSSLMaster;
	struct AmiSSLIFace       *IAmiSSL;

	UBYTE *DataSegment;
	ULONG  DataOffset;
};

struct Interface *open_interface(struct ZipBase *zb, CONST_STRPTR name, ULONG version);
void close_interface(struct ZipBase *zb, struct Interface *interface);

#endif /* ZIP_BASE_H */

