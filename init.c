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

#include <dos/dos.h>
#include <proto/exec.h>
#include <proto/z.h>
#include <proto/zip.h>

/* Version Tag */
#include "zip.library_rev.h"
STATIC CONST UBYTE USED verstag[] = VERSTAG;

struct ExecIFace *IExec;

struct Library *NewlibBase;
struct NewlibIFace *INewlib;

struct Library *ZBase;
struct ZIFace *IZ;

struct ZipBase {
	struct Library libNode;
	BPTR segList;
	/* If you need more data fields, add them here */
};

/*
 * The system (and compiler) rely on a symbol named _start which marks
 * the beginning of execution of an ELF file. To prevent others from 
 * executing this library, and to keep the compiler/linker happy, we
 * define an empty _start symbol here.
 *
 * On the classic system (pre-AmigaOS 4.x) this was usually done by
 * moveq #0,d0
 * rts
 *
 */

int32 _start(void) {
	/* If you feel like it, open DOS and print something to the user */
	return RETURN_FAIL;
}

/* Open the library */
STATIC struct ZipBase *libOpen(struct LibraryManagerInterface *Self, ULONG version) {
	struct ZipBase *libBase = (struct ZipBase *)Self->Data.LibBase; 

	if (version > VERSION)
		return NULL;

	/* Add any specific open code here 
	   Return 0 before incrementing OpenCnt to fail opening */

	/* Add up the open count */
	libBase->libNode.lib_OpenCnt++;
	return libBase;
}

/* Close the library */
STATIC BPTR libClose(struct LibraryManagerInterface *Self) {
	struct ZipBase *libBase = (struct ZipBase *)Self->Data.LibBase;

	/* Make sure to undo what open did */

	/* Make the close count */
	libBase->libNode.lib_OpenCnt--;

	return ZERO;
}


/* Expunge the library */
STATIC BPTR libExpunge(struct LibraryManagerInterface *Self) {
	/* If your library cannot be expunged, return 0 */
	BPTR result = ZERO;
	struct ZipBase *libBase = (struct ZipBase *)Self->Data.LibBase;
	if (libBase->libNode.lib_OpenCnt == 0) {
		result = libBase->segList;

		/* Undo what the init code did */
		IExec->DropInterface((struct Interface *)IZ);
		IExec->CloseLibrary(ZBase);

		IExec->DropInterface((struct Interface *)INewlib);
		IExec->CloseLibrary(NewlibBase);

		IExec->Remove((struct Node *)libBase);
		IExec->DeleteLibrary((struct Library *)libBase);
	} else {
		result = ZERO;
		libBase->libNode.lib_Flags |= LIBF_DELEXP;
	}
	return result;
}

/* The ROMTAG Init Function */
STATIC struct ZipBase *libInit(struct ZipBase *libBase, BPTR seglist, struct ExecIFace *iexec) {
	IExec = iexec;

	libBase->libNode.lib_Node.ln_Type = NT_LIBRARY;
	libBase->libNode.lib_Node.ln_Pri  = 0;
	libBase->libNode.lib_Node.ln_Name = (STRPTR)"zip.library";
	libBase->libNode.lib_Flags        = LIBF_SUMUSED|LIBF_CHANGED;
	libBase->libNode.lib_Version      = VERSION;
	libBase->libNode.lib_Revision     = REVISION;
	libBase->libNode.lib_IdString     = (STRPTR)VSTRING;

	libBase->segList = seglist;

	NewlibBase = IExec->OpenLibrary("newlib.library", 53);
	INewlib = (struct NewlibIFace *)IExec->GetInterface(NewlibBase, "main", 1, NULL);

	if (INewlib != NULL) {
		ZBase = IExec->OpenLibrary("z.library", 53);
		IZ = (struct ZIFace *)IExec->GetInterface(ZBase, "main", 1, NULL);

		if (IZ != NULL && LIB_IS_AT_LEAST(ZBase, 53, 5)) {
			return libBase;
		}

		IExec->DropInterface((struct Interface *)IZ);
		IExec->CloseLibrary(ZBase);
	}

	IExec->DropInterface((struct Interface *)INewlib);
	IExec->CloseLibrary(NewlibBase);

	IExec->DeleteLibrary((struct Library *)libBase);
	return NULL;
}

/* ------------------- Manager Interface ------------------------ */
/* These are generic. Replace if you need more fancy stuff */
STATIC uint32 _manager_Obtain(struct LibraryManagerInterface *Self) {
	uint32 res;
	__asm__ __volatile__(
	"1:	lwarx	%0,0,%1\n"
	"addic	%0,%0,1\n"
	"stwcx.	%0,0,%1\n"
	"bne-	1b"
	: "=&r" (res)
	: "r" (&Self->Data.RefCount)
	: "cc", "memory");

	return res;
}

STATIC uint32 _manager_Release(struct LibraryManagerInterface *Self) {
	uint32 res;
	__asm__ __volatile__(
	"1:	lwarx	%0,0,%1\n"
	"addic	%0,%0,-1\n"
	"stwcx.	%0,0,%1\n"
	"bne-	1b"
	: "=&r" (res)
	: "r" (&Self->Data.RefCount)
	: "cc", "memory");

	return res;
}

/* Manager interface vectors */
STATIC CONST APTR lib_manager_vectors[] = {
	_manager_Obtain,
	_manager_Release,
	NULL,
	NULL,
	libOpen,
	libClose,
	libExpunge,
	NULL,
	(APTR)-1
};

/* "__library" interface tag list */
STATIC CONST struct TagItem lib_managerTags[] = {
	{ MIT_Name,			(Tag)"__library"		},
	{ MIT_VectorTable,	(Tag)lib_manager_vectors},
	{ MIT_Version,		1						},
	{ TAG_DONE,			0						}
};

/* ------------------- Library Interface(s) ------------------------ */

#include "zip_vectors.c"

/* Uncomment this line (and see below) if your library has a 68k jump table */
/* extern APTR VecTable68K[]; */

STATIC CONST struct TagItem main_v1_Tags[] = {
	{ MIT_Name,			(Tag)"main"			},
	{ MIT_VectorTable,	(Tag)main_v1_vectors	},
	{ MIT_Version,		1					},
	{ TAG_DONE,			0					}
};

STATIC CONST CONST_APTR libInterfaces[] = {
	lib_managerTags,
	main_v1_Tags,
	NULL
};

STATIC CONST struct TagItem libCreateTags[] = {
	{ CLT_DataSize,		sizeof(struct ZipBase)	},
	{ CLT_InitFunc,		(Tag)libInit			},
	{ CLT_Interfaces,	(Tag)libInterfaces		},
	/* Uncomment the following line if you have a 68k jump table */
	/* { CLT_Vector68K, (Tag)VecTable68K }, */
	{TAG_DONE,		 0 }
};


/* ------------------- ROM Tag ------------------------ */
STATIC CONST struct Resident lib_res USED = {
	RTC_MATCHWORD,
	(struct Resident *)&lib_res,
	(APTR)(&lib_res + 1),
	RTF_NATIVE|RTF_AUTOINIT, /* Add RTF_COLDSTART if you want to be resident */
	VERSION,
	NT_LIBRARY, /* Make this NT_DEVICE if needed */
	0, /* PRI, usually not needed unless you're resident */
	"zip.library",
	VSTRING,
	(APTR)libCreateTags
};

