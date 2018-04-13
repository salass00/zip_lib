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

/****** zip.library/zip_file_replace ******************************************
*
*   NAME
*      zip_file_replace -- Replace a file in an archive
*
*   SYNOPSIS
*      zip_int32_t zip_file_replace(zip_t *archive, zip_uint64_t index,
*          zip_source_t *source, zip_flags_t flags);
*
*   FUNCTION
*       The function zip_file_replace() replaces an existing file in a zip
*       archive. The argument archive specifies the zip archive to which the
*       file should be added. index specifies which file should be replaced.
*       The flags argument can be any of:
*
*       ZIP_FL_ENC_GUESS - Guess encoding of name (default).
*       ZIP_FL_ENC_UTF_8 - Interpret name as UTF-8.
*       ZIP_FL_ENC_CP437 - Interpret name as code page 437 (CP-437).
*
*       The data is obtained from the source argument, see zip_source().
*
*   INPUTS
*       archive - Zip archive handle
*       index   - Index of file to replace
*       source  - Zip source handle.
*       flags   - Flags.
*
*   RESULT
*       Upon successful completion, zip_file_replace() returns 0. Otherwise,
*       -1 is returned and the error code in archive is set to indicate the
*       error.
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*       zip_file_add()
*
*****************************************************************************
*
*/

zip_int32_t _main_zip_file_replace(struct ZipIFace *Self, zip_t *archive,
	zip_uint64_t index, zip_source_t *source, zip_flags_t flags)
{
	return zip_file_replace(archive, index, source, flags);
}

