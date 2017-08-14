/*
 * Copyright (C) 2014-2017 Fredrik Wikstrom <fredrik@a500.org>
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

#include <libraries/zip.h>

#include <interfaces/zip.h>
#include <proto/exec.h>
#include <assert.h>

struct ZipIFace * IZip = NULL;
static struct ZipBase * __ZipBase;
static struct ZipIFace * __IZip;

/****************************************************************************/

extern struct ZipBase * ZipBase;

/****************************************************************************/

void _INIT_5_IZip(void)
{
    if (ZipBase == NULL) /* Library base is NULL, we need to open it */
    {
        /* We were called before the base constructor.
         * This means we will be called _after_ the base destructor.
         * So we cant drop the interface _after_ closing the last library base,
         * we just open the library here which ensures that.
         */
        __ZipBase = ZipBase = (struct ZipBase *)IExec->OpenLibrary("zip.library", 53L);
        assert(ZipBase != NULL);
    }

    __IZip = IZip = (struct ZipIFace *)IExec->GetInterface((struct Library *)ZipBase, "main", 1, NULL);
    assert(IZip != NULL);
}
__attribute__((section(".ctors.zzzy"))) static void
(*zip_main_constructor_ptr)(void) USED = _INIT_5_IZip;

/****************************************************************************/

void _EXIT_5_IZip(void)
{
    if (__IZip)
    {
        IExec->DropInterface ((struct Interface *)__IZip);
    }
    if (__ZipBase)
    {
        IExec->CloseLibrary((struct Library *)__ZipBase);
    }
}
__attribute__((section(".dtors.zzzy"))) static void
(*zip_main_destructor_ptr)(void) USED = _EXIT_5_IZip;

/****************************************************************************/

