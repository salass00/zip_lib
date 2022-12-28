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

/****** zip.library/zip_archive_set_tempdir ******************************************
*
*   NAME
*      zip_archive_set_tempdir -- Description
*
*   SYNOPSIS
*      zip_int32_t zip_archive_set_tempdir(zip_t *za, const char *tempdir);
*
*   FUNCTION
*
*   INPUTS
*       za - 
*       tempdir - 
*
*   RESULT
*       The result ...
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*
*****************************************************************************
*
*/

register APTR r13 __asm("r13");

zip_int32_t _main_zip_archive_set_tempdir(struct ZipIFace *Self, zip_t *za, const char *tempdir)
{
	/* This function was never documented and no longer exists in libzip 1.2.0 */
#if LIBZIP_VERSION_MAJOR > 1 || (LIBZIP_VERSION_MAJOR == 1 && LIBZIP_VERSION_MINOR >= 2)
	if (tempdir) {
		return -1;
	}
	return 0;
#else
	APTR old_r13 = r13;
	zip_int32_t res;

	r13 = Self->Data.EnvironmentVector;
	res = zip_archive_set_tempdir(za, tempdir);
	r13 = old_r13;

	return res;
#endif
}

