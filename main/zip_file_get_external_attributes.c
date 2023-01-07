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

/****** zip.library/zip_file_get_external_attributes ******************************************
*
*   NAME
*      zip_file_get_external_attributes -- Description
*
*   SYNOPSIS
*      zip_int32_t zip_file_get_external_attributes(zip_t *za, zip_uint64_t idx, 
*          zip_flags_t flags, zip_uint8_t * opsys, zip_uint32_t * attributes);
*
*   FUNCTION
*
*   INPUTS
*       za - 
*       idx - 
*       flags - 
*       opsys - 
*       attributes - 
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

zip_int32_t _main_zip_file_get_external_attributes(struct ZipIFace *Self, zip_t *za,
	zip_uint64_t idx, zip_flags_t flags, zip_uint8_t *opsys, zip_uint32_t *attributes)
{
	APTR old_r13 = r13;
	zip_int32_t res;

	r13 = (struct ZipIData *)INTERFACE_DATA(Self);
	res = zip_file_get_external_attributes(za, idx, flags, opsys, (zip_uint32_t *)attributes);
	r13 = old_r13;

	return res;
}

