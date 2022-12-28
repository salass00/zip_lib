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

/****** zip.library/zip_open ******************************************
*
*   NAME
*      zip_open -- Open zip archive
*
*   SYNOPSIS
*      zip_t *zip_open(const char *path, int flags, int *errorp);
*
*   FUNCTION
*       The zip_open() function opens the zip archive specified by path and
*       returns a pointer to a struct zip, used to manipulate the archive.
*       The flags are specified by or'ing the following values, or 0 for none
*       of them.
*
*       ZIP_CHECKCONS - Perform additional stricter consistency checks on the
*                       archive, and error if they fail.
*       ZIP_CREATE    - Create the archive if it does not exist.
*       ZIP_EXCL      - Error if archive already exists.
*       ZIP_TRUNCATE  - If archive exists, ignore its current contents. In
*                       other words, handle it the same way as an empty
*                       archive.
*       ZIP_RDONLY    - Open archive in read-only mode.
*
*       If an error occurs and errorp is non-NULL, it will be set to the
*       corresponding error code.
*
*   INPUTS
*       path   - Path to zip archive.
*       flags  - Flags.
*       errorp - Pointer to a storage area for the error code, or NULL.
*
*   RESULT
*       Upon successful completion zip_open() returns a struct zip pointer.
*       Otherwise, NULL is returned and zip_open() sets *errorp to indicate
*       the error. 
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*       zip_fdopen(), zip_open_from_source(), zip_close(), zip_discard()
*
*****************************************************************************
*
*/

register APTR r13 __asm("r13");

zip_t *_main_zip_open(struct ZipIFace *Self, const char *path, int flags, int *errorp)
{
	APTR old_r13 = r13;
	zip_t *res;

	r13 = Self->Data.EnvironmentVector;
	res = zip_open(path, flags, errorp);
	r13 = old_r13;

	return res;
}

