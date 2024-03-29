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

void _main_Expunge(struct ZipIFace *Self)
{
	struct ZipIData *id = (struct ZipIData *)INTERFACE_DATA(Self);

	if (Self->Data.RefCount != 0)
	{
		/* There are still users of this interface */
		return;
	}

	if (id->IAmiSSL != NULL)
	{
		id->IAmiSSLMaster->CloseAmiSSL();
		id->IAmiSSL = NULL;
	}

	if (id->IAmiSSLMaster != NULL)
	{
		close_interface((struct Interface *)id->IAmiSSLMaster);
		id->IAmiSSLMaster = NULL;
	}

	if (id->ILZMA != NULL)
	{
		close_interface((struct Interface *)id->ILZMA);
		id->ILZMA = NULL;
	}

	if (id->IBZip2 != NULL)
	{
		close_interface((struct Interface *)id->IBZip2);
		id->IBZip2 = NULL;
	}

	if (id->IZ != NULL)
	{
		close_interface((struct Interface *)id->IZ);
		id->IZ = NULL;
	}

	/* Stop DeleteInterface() call below from calling Self->Expunge() again.
	 * Alternatively we could just call FreeVec(id) if we are fine with making
	 * assumptions about how MakeInterface() allocates the memory.
	 */
	Self->Data.Flags &= ~(IFLF_CLONED|IFLF_CLONE_EXPUNGE);

	IExec->DeleteInterface((struct Interface *)Self);
}

