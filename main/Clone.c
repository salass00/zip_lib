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

#include <interfaces/zip.h>
#include "zip-base.h"
#include "../zip_vectors.h"

extern CONST struct TagItem main_v1_Tags[];

register APTR r13 __asm("r13");

struct ZipIFace * _main_Clone(struct ZipIFace *Self)
{
	struct ZipBase *zb = (struct ZipBase *)Self->Data.LibBase;
	struct ExecIFace *iexec = zb->IExec;
	struct ZipIFace *izip;
	struct ZipInterfaceData *zid;
	APTR old_r13 = r13;

	izip = (struct ZipIFace *)iexec->MakeInterface(&zb->LibNode, main_v1_Tags);
	if (izip == NULL)
		return NULL;

	zid = (struct ZipInterfaceData *)((BYTE *)izip - izip->Data.NegativeSize);

	zid->DataSegment = zb->IElf->CopyDataSegment(zb->ElfHandle, &zid->DataOffset);
	if (zid->DataSegment == NULL)
	{
		iexec->DeleteInterface((struct Interface *)izip);
		return NULL;
	}

	izip->Data.EnvironmentVector = zid->DataSegment + zid->DataOffset;

	r13 = izip->Data.EnvironmentVector;

	/* FIXME: Setup global library interfaces */

	r13 = old_r13;

	izip->Data.Flags |= IFLF_CLONED|IFLF_CLONE_EXPUNGE;

	return izip;
}

