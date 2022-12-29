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

#include <libraries/amisslmaster.h>

struct ExecIFace   *IExec;
struct DOSIFace    *IDOS;
struct NewlibIFace *INewlib;
struct ZIFace      *IZ;
struct BZip2IFace  *IBZip2;
struct LZMAIFace   *ILZMA;
struct AmiSSLIFace *IAmiSSL;

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

	/* Need IUtility to clear memory? */

	zid->DataSegment = zb->IElf->CopyDataSegment(zb->ElfHandle, &zid->DataOffset);
	if (zid->DataSegment == NULL)
	{
		izip->Expunge();
		izip = NULL;
		goto cleanup;
	}

	izip->Data.EnvironmentVector = zid->DataSegment + zid->DataOffset;
	r13 = izip->Data.EnvironmentVector;

	IExec   = zb->IExec;
	IDOS    = zb->IDOS;
	INewlib = zb->INewlib;

	zid->IZ = (struct ZIFace *)open_interface(zb, "z.library", 53);
	if (zid->IZ == NULL)
	{
		izip->Expunge();
		izip = NULL;
		goto cleanup;
	}

	zid->IBZip2 = (struct BZip2IFace *)open_interface(zb, "bzip2.library", 53);
	if (zid->IBZip2 == NULL)
	{
		izip->Expunge();
		izip = NULL;
		goto cleanup;
	}

	zid->ILZMA = (struct LZMAIFace *)open_interface(zb, "lzma.library", 53);
	if (zid->ILZMA == NULL)
	{
		izip->Expunge();
		izip = NULL;
		goto cleanup;
	}

	zid->IAmiSSLMaster = (struct AmiSSLMasterIFace *)open_interface(zb, "amisslmaster.library", AMISSLMASTER_MIN_VERSION);
	if (zid->IAmiSSLMaster == NULL)
	{
		izip->Expunge();
		izip = NULL;
		goto cleanup;
	}

	if (zid->IAmiSSLMaster->OpenAmiSSLTags(AMISSL_CURRENT_VERSION,
		AmiSSL_UsesOpenSSLStructs, TRUE,
		AmiSSL_GetIAmiSSL,         &zid->IAmiSSL,
		AmiSSL_ErrNoPtr,           __errno(),
		TAG_END) != 0)
	{
		izip->Expunge();
		izip = NULL;
		goto cleanup;
	}

	IZ      = zid->IZ;
	IBZip2  = zid->IBZip2;
	ILZMA   = zid->ILZMA;
	IAmiSSL = zid->IAmiSSL;

	izip->Data.Flags |= IFLF_CLONED|IFLF_CLONE_EXPUNGE;

cleanup:

	r13 = old_r13;

	return izip;
}

