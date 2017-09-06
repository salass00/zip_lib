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
#include <proto/bzip2.h>
#include <proto/zip.h>

/* Version Tag */
#include "zip.library_rev.h"
static CONST UBYTE USED verstag[] = VERSTAG;

struct ExecIFace   *IExec;
struct NewlibIFace *INewlib;
struct ZIFace      *IZ;
struct BZip2IFace  *IBZip2;

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

static struct Interface *OpenInterface(CONST_STRPTR name, ULONG version) {
	struct Library   *library;
	struct Interface *interface;

	library = IExec->OpenLibrary(name, version);
	if (library == NULL)
		return NULL;

	interface = IExec->GetInterface(library, "main", 1, NULL);
	if (interface == NULL) {
		IExec->CloseLibrary(library);
		return NULL;
	}

	return interface;
}

static void CloseInterface(struct Interface *interface) {
	struct Library *library;

	if (interface == NULL)
		return;

	library = interface->Data.LibBase;

	IExec->DropInterface(interface);
	IExec->CloseLibrary(library);
}

/* Open the library */
static struct ZipBase *libOpen(struct LibraryManagerInterface *Self, ULONG version) {
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
static BPTR libClose(struct LibraryManagerInterface *Self) {
	struct ZipBase *libBase = (struct ZipBase *)Self->Data.LibBase;

	/* Make sure to undo what open did */

	/* Make the close count */
	libBase->libNode.lib_OpenCnt--;

	return ZERO;
}


/* Expunge the library */
static BPTR libExpunge(struct LibraryManagerInterface *Self) {
	/* If your library cannot be expunged, return 0 */
	BPTR result = ZERO;
	struct ZipBase *libBase = (struct ZipBase *)Self->Data.LibBase;
	if (libBase->libNode.lib_OpenCnt == 0) {
		result = libBase->segList;

		/* Undo what the init code did */
		CloseInterface((struct Interface *)IBZip2);
		CloseInterface((struct Interface *)IZ);
		CloseInterface((struct Interface *)INewlib);

		IExec->Remove((struct Node *)libBase);
		IExec->DeleteLibrary((struct Library *)libBase);
	} else {
		result = ZERO;
		libBase->libNode.lib_Flags |= LIBF_DELEXP;
	}
	return result;
}

/* The ROMTAG Init Function */
static struct ZipBase *libInit(struct ZipBase *libBase, BPTR seglist, struct ExecIFace *iexec) {
	IExec = iexec;

	libBase->libNode.lib_Node.ln_Type = NT_LIBRARY;
	libBase->libNode.lib_Node.ln_Pri  = 0;
	libBase->libNode.lib_Node.ln_Name = (STRPTR)"zip.library";
	libBase->libNode.lib_Flags        = LIBF_SUMUSED|LIBF_CHANGED;
	libBase->libNode.lib_Version      = VERSION;
	libBase->libNode.lib_Revision     = REVISION;
	libBase->libNode.lib_IdString     = (STRPTR)VSTRING;

	libBase->segList = seglist;

	INewlib = (struct NewlibIFace *)OpenInterface("newlib.library", 53);
	if (INewlib == NULL) {
		IExec->Alert(AG_OpenLib|AO_NewlibLib);
		goto cleanup;
	}

	IZ = (struct ZIFace *)OpenInterface("z.library", 53);
	if (IZ == NULL || !LIB_IS_AT_LEAST(IZ->Data.LibBase, 53, 5)) {
		IExec->Alert(AG_OpenLib|AO_Unknown);
		goto cleanup;
	}

	IBZip2 = (struct BZip2IFace *)OpenInterface("bzip2.library", 53);
	if (IBZip2 == NULL || !LIB_IS_AT_LEAST(IBZip2->Data.LibBase, 53, 4)) {
		IExec->Alert(AG_OpenLib|AO_Unknown);
		goto cleanup;
	}

	return libBase;

cleanup:

	CloseInterface((struct Interface *)IBZip2);
	CloseInterface((struct Interface *)IZ);
	CloseInterface((struct Interface *)INewlib);

	IExec->DeleteLibrary((struct Library *)libBase);
	return NULL;
}

/* ------------------- Manager Interface ------------------------ */
/* These are generic. Replace if you need more fancy stuff */
static uint32 _manager_Obtain(struct LibraryManagerInterface *Self) {
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

static uint32 _manager_Release(struct LibraryManagerInterface *Self) {
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
static CONST APTR lib_manager_vectors[] = {
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
static CONST struct TagItem lib_managerTags[] = {
	{ MIT_Name,			(Tag)"__library"		},
	{ MIT_VectorTable,	(Tag)lib_manager_vectors},
	{ MIT_Version,		1						},
	{ TAG_DONE,			0						}
};

/* ------------------- Library Interface(s) ------------------------ */

#include "zip_vectors.c"

/* Uncomment this line (and see below) if your library has a 68k jump table */
/* extern APTR VecTable68K[]; */

static CONST struct TagItem main_v1_Tags[] = {
	{ MIT_Name,			(Tag)"main"			},
	{ MIT_VectorTable,	(Tag)main_v1_vectors	},
	{ MIT_Version,		1					},
	{ TAG_DONE,			0					}
};

static CONST CONST_APTR libInterfaces[] = {
	lib_managerTags,
	main_v1_Tags,
	NULL
};

static CONST struct TagItem libCreateTags[] = {
	{ CLT_DataSize,		sizeof(struct ZipBase)	},
	{ CLT_InitFunc,		(Tag)libInit			},
	{ CLT_Interfaces,	(Tag)libInterfaces		},
	/* Uncomment the following line if you have a 68k jump table */
	/* { CLT_Vector68K, (Tag)VecTable68K }, */
	{TAG_DONE,		 0 }
};


/* ------------------- ROM Tag ------------------------ */
static CONST struct Resident lib_res USED = {
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

