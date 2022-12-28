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
#include "../zip_vectors.h"

/****** zip.library/zip_close ******************************************
*
*   NAME
*      zip_close -- Close archive
*
*   SYNOPSIS
*      zip_int32_t zip_close(zip_t *archive);
*
*   FUNCTION
*       The zip_close() function closes archive and frees the memory
*       allocated for it. If any files within were changed, those changes are
*       written to disk first. If writing changes fails, zip_close() fails
*       and archive is left unchanged. If archive contains no files, the file
*       is completely removed (no empty archive is written).
*
*       To close a zip file without saving changes, use zip_discard().
*
*   INPUTS
*       archive - Zip archive handle.
*
*   RESULT
*       Upon successful completion 0 is returned. Otherwise, -1 is returned
*       and the error code in archive is set to indicate the error. 
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*       zip_open(), zip_discard()
*
*****************************************************************************
*
*/

register APTR r13 __asm("r13");

zip_int32_t _main_zip_close(struct ZipIFace *Self, zip_t *archive)
{
	APTR old_r13 = r13;
	zip_int32_t res;

	r13 = Self->Data.EnvironmentVector;
	res = zip_close(archive);
	r13 = old_r13;

	return res;
}

