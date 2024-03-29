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

/****** zip.library/zip_fdopen ******************************************
*
*   NAME
*      zip_fdopen -- Open zip archive using open file descriptor
*
*   SYNOPSIS
*      zip_t *zip_fdopen(int fd, int flags, int *errorp);
*
*   FUNCTION
*       The zip archive specified by the open file descriptor fd is opened
*       and a pointer to a struct zip, used to manipulate the archive, is
*       returned. In contrast to zip_open(), using zip_fdopen the archive can
*       only be opened in read-only mode. The fd argument may not be used any
*       longer after calling zip_fdopen. The flags are specified by or'ing
*       the following values, or 0 for none of them.
*
*       ZIP_CHECKCONS - Perform additional stricter consistency checks on the
*                       archive, and error if they fail.
*
*       If an error occurs and errorp is non-NULL, it will be set to the
*       corresponding error code.
*
*   INPUTS
*       fd     - Open file descriptor.
*       flags  - Flags.
*       errorp - Pointer to a storage area for the error code, or NULL.
*
*   RESULT
*       Upon successful completion zip_fdopen() returns a struct zip pointer,
*       and fd should not be used any longer, nor passed to close().
*       Otherwise, NULL is returned and *errorp is set to indicate the error.
*       In the error case, fd remains unchanged.
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*       zip_open(), zip_close(), zip_discard()
*
*****************************************************************************
*
*/

register APTR r13 __asm("r13");

zip_t *_main_zip_fdopen(struct ZipIFace *Self, int fd, int flags, int *errorp)
{
	APTR old_r13 = r13;
	zip_t *res;

	r13 = (struct ZipIData *)INTERFACE_DATA(Self);
	res = zip_fdopen(fd, flags, errorp);
	r13 = old_r13;

	return res;
}

