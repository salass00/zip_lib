/*
 * Copyright (C) 2014-2023 Fredrik Wikstrom <fredrik@a500.org>
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
#include "zip-internal.h"
#include "zip_vectors.h"

extern CONST struct TagItem main_v1_Tags[];

static BOOL open_libs(struct ZipBase *zipbase, struct ZipIData *id)
{
	id->IZ = (struct ZIFace *)open_interface("z.library", 53);
	if (id->IZ == NULL)
	{
		return FALSE;
	}

	id->IBZip2 = (struct BZip2IFace *)open_interface("bzip2.library", 53);
	if (id->IBZip2 == NULL)
	{
		return FALSE;
	}

	id->ILZMA = (struct LZMAIFace *)open_interface("lzma.library", 53);
	if (id->ILZMA == NULL)
	{
		return FALSE;
	}

	/* Cannot open AmiSSL here as Clone() is called from ramlib */

	return TRUE;
}

struct ZipIFace * _main_Clone(struct ZipIFace *Self)
{
	struct ZipBase   *zipbase = (struct ZipBase *)Self->Data.LibBase;
	struct ZipIFace  *new_iface;
	struct ZipIData  *id;

	new_iface = (struct ZipIFace *)IExec->MakeInterface(&zipbase->LibNode, main_v1_Tags);
	if (new_iface == NULL)
		return NULL;

	id = (struct ZipIData *)INTERFACE_DATA(new_iface);

	memset(id, 0, sizeof(*id));

	if (!open_libs(zipbase, id))
	{
		new_iface->Expunge();
		return NULL;
	}

	/* Call Expunge() when RefCount goes to zero */
	new_iface->Data.Flags |= IFLF_CLONED|IFLF_CLONE_EXPUNGE;

	return new_iface;
}

