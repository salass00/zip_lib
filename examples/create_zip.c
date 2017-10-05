/*
 * Example code for using zip.library
 *
 * Copyright (C) 2017 Fredrik Wikstrom <fredrik@a500.org>
 *
 * Compiles with:
 * ppc-amigaos-gcc -O2 -Wall -Wwrite-strings -Werror -o create_zip -I/SDK/local/newlib/lib/libzip/include create_zip.c
 *
 * Usage:
 * create_zip <archive> <file1> <file2> <file3> ...
 */

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/zip.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Library *ZipBase;
struct ZipIFace *IZip;

#define TEMPLATE "ARCHIVE/A,FILES/M,PASSWORD/K"

enum {
	ARG_ARCHIVE,
	ARG_FILES,
	ARG_PASSWORD,
	ARG_MAX
};

static BOOL create_zip(CONST_STRPTR archive, CONST_STRPTR *files, int comp_level, CONST_STRPTR password) {
	zip_t             *za = NULL;
	int                i, error, status;
	zip_error_t        ze;
	CONST_STRPTR       path;
	CONST_STRPTR       name;
	zip_source_t      *zs;
	zip_int64_t        idx;
	BOOL               result = FALSE;

	/* Delete any existing files by the same name */
	status = IDOS->Delete(archive);
	if (status == 0) {
		error = IDOS->IoErr();
		if (error != ERROR_OBJECT_NOT_FOUND) {
			IDOS->PrintFault(error, archive);
			goto cleanup;
		}
	}

	/* Create zip archive */
	za = IZip->zip_open(archive, ZIP_CREATE, &error);
	if (za == NULL) {
		IZip->zip_error_init_with_code(&ze, error);
		fprintf(stderr, "%s: %s (line %d)\n", archive, IZip->zip_error_strerror(&ze), __LINE__);
		IZip->zip_error_fini(&ze);
		goto cleanup;
	}

	if (password != NULL) {
		/* Set default password for encrypted files */
		status = IZip->zip_set_default_password(za, password);
		if (status == -1) {
			fprintf(stderr, "%s: %s (line %d)\n", archive, IZip->zip_strerror(za), __LINE__);
			goto cleanup;
		}
	}

	if (files != NULL) {
		for (i = 0; (path = files[i]) != NULL; i++) {
			/* Open source file */
			zs = IZip->zip_source_file(za, path, 0, 0);
			if (zs == NULL) {
				fprintf(stderr, "%s: %s (line %d)\n", path, IZip->zip_strerror(za), __LINE__);
				goto cleanup;
			}

			/* Remove any eventual volume, assign or device name from the path so
			 * libzip doesn't get confused
			 */
			name = strrchr(path, ':');
			if (name != NULL)
				name++;
			else
				name = path;

			/* Add to archive */
			idx = IZip->zip_file_add(za, name, zs, ZIP_FL_ENC_GUESS);
			if (idx == -1) {
				fprintf(stderr, "%s: %s (line %d)\n", name, IZip->zip_strerror(za), __LINE__);
				IZip->zip_source_free(zs);
				goto cleanup;
			}

			/* Set compression level */
			status = IZip->zip_set_file_compression(za, idx, ZIP_CM_DEFLATE, comp_level);
			if (status == -1) {
				fprintf(stderr, "%s: %s (line %d)\n", name, IZip->zip_strerror(za), __LINE__);
				goto cleanup;
			}

			if (password != NULL) {
				/* Enable encryption */
				status = IZip->zip_file_set_encryption(za, idx, ZIP_EM_AES_256, NULL);
				if (status == -1) {
					fprintf(stderr, "%s: %s (line %d)\n", name, IZip->zip_strerror(za), __LINE__);
					goto cleanup;
				}
			}
		}
	}

	/* Write changes to archive file and close it */
	status = IZip->zip_close(za);
	if (status == -1) {
		fprintf(stderr, "%s: %s (line %d)\n", archive, IZip->zip_strerror(za), __LINE__);
		goto cleanup;
	}

	/* Success */
	result = TRUE;

cleanup:

	/* Discard archive changes on failure */
	if (result == FALSE && za != NULL)
		IZip->zip_discard(za);

	return result;
}

int main(void) {
	struct RDArgs *rda;
	int32          args[ARG_MAX];
	CONST_STRPTR   archive;
	CONST_STRPTR  *files;
	/* Compression level in the range 1-9, where 1 is fastest and 9 is best (slowest) compression */
	const int      comp_level = 9;
	CONST_STRPTR   password;
	int            rc = RETURN_ERROR;

	memset(args, 0, sizeof(args));

	rda = IDOS->ReadArgs(TEMPLATE, args, NULL);

	if (rda == NULL) {
		IDOS->PrintFault(IDOS->IoErr(), NULL);
		goto cleanup;
	}

	/* Open zip.library */
	ZipBase = IExec->OpenLibrary("zip.library", 53);
	IZip    = (struct ZipIFace *)IExec->GetInterface(ZipBase, "main", 1, NULL);

	if (IZip == NULL) {
		fprintf(stderr, "Failed to open zip.library!\n");
		goto cleanup;
	}

	if (!LIB_IS_AT_LEAST(ZipBase, 53, 5)) {
		fprintf(stderr, "Version of zip.library is too old!\nThis program requires version 53.5 or newer.\n");
		goto cleanup;
	}

	archive  = (CONST_STRPTR)args[ARG_ARCHIVE];
	files    = (CONST_STRPTR *)args[ARG_FILES];
	password = (CONST_STRPTR)args[ARG_PASSWORD];

	if (create_zip(archive, files, comp_level, password))
		rc = RETURN_OK;

cleanup:

	/* Close zip.library */
	IExec->DropInterface((struct Interface *)IZip);
	IExec->CloseLibrary(ZipBase);

	IDOS->FreeArgs(rda);

	return rc;
}

