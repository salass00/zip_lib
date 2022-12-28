/*
 * Example code for using zip.library
 *
 * Copyright (C) 2017 Fredrik Wikstrom <fredrik@a500.org>
 *
 * Compiles with:
 * ppc-amigaos-gcc -O2 -Wall -Wwrite-strings -Werror -o extract_zip -I/SDK/local/newlib/lib/libzip/include extract_zip.c
 *
 * Usage:
 * extract_zip <archive> [PASSWORD=<password>]
 */

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/zip.h>
#include <string.h>
#include <stdio.h>

struct Library *ZipBase;
struct ZipIFace *IZip;

#define TEMPLATE "ARCHIVE/A,PASSWORD/K,NODECOMP/S"

enum {
	ARG_ARCHIVE,
	ARG_PASSWORD,
	ARG_NODECOMP,
	NUM_ARGS
};

#define BUFFER_SIZE 65536 /* 64 KiB */

static BOOL extract_zip(CONST_STRPTR archive, CONST_STRPTR password, BOOL nodecomp) {
	zip_t       *za;
	int          error, status;
	zip_error_t  ze;
	zip_int64_t  num_entries, index;
	APTR         buffer = NULL;
	zip_stat_t   stat;
	TEXT         pathbuf[1024];
	TEXT         namebuf[256];
	BPTR         dirlock = ZERO;
	zip_file_t  *zf = NULL;
	BPTR         file = ZERO;
	int          readlen, writelen;
	zip_uint64_t done;
	zip_uint64_t size;
	BOOL         result = FALSE;

	/* Open archive */
	za = IZip->zip_open(archive, ZIP_RDONLY, &error);
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

	/* Get number of entries */
	num_entries = IZip->zip_get_num_entries(za, 0);
	if (num_entries == -1) {
		fprintf(stderr, "%s: %s (line %d)\n", archive, IZip->zip_strerror(za), __LINE__);
		goto cleanup;
	}

	buffer = IExec->AllocVecTags(BUFFER_SIZE,
		AVT_Type, MEMF_SHARED,
		AVT_Lock, FALSE,
		TAG_END);
	if (buffer == NULL) {
		IDOS->PrintFault(ERROR_NO_FREE_STORE, NULL);
		goto cleanup;
	}

	for (index = 0; index < num_entries; index++) {
		if (IDOS->CheckSignal(SIGBREAKF_CTRL_C)) {
			fputs("Break signal received\n", stderr);
			goto cleanup;
		}

		status = IZip->zip_stat_index(za, index, 0, &stat);
		if (status == -1) {
			fprintf(stderr, "%s (index %lld): %s (line %d)\n", archive, index, IZip->zip_strerror(za), __LINE__);
			goto cleanup;
		}

		/* Skip entries that don't have a valid name */
		if ((stat.valid & ZIP_STAT_NAME) != ZIP_STAT_NAME)
			continue;

		strlcpy(pathbuf, stat.name, sizeof(pathbuf));

		/* Split file name from path */
		strlcpy(namebuf, IDOS->FilePart(pathbuf), sizeof(namebuf));
		*(IDOS->PathPart(pathbuf)) = '\0';

		/* Try to lock destination directory */
		dirlock = IDOS->Lock(pathbuf, ACCESS_READ);
		if (dirlock == ZERO) {
			if (IDOS->IoErr() == ERROR_OBJECT_NOT_FOUND) {
				/* Create all directories in path */
				dirlock = IDOS->CreateDirTree(pathbuf);
			}

			if (dirlock == ZERO) {
				IDOS->PrintFault(IDOS->IoErr(), pathbuf);
				goto cleanup;
			}
		}

		/* Not sure if there's a better way to check if an entry is a directory but all directory
         * entries seem to have a slash at the end of the name which means that the file name
         * component will be empty here.
		 *
		 * This kind of cludge is needed for the xadmaster LhA client too when using xadmaster
		 * (or at least it used to be) so maybe it's OK.
         */
		if (namebuf[0] != '\0') {
			/* Add file name back to path */
			IDOS->AddPart(pathbuf, namebuf, sizeof(pathbuf));

			/* Get uncompressed size, if available */
			if ((stat.valid & ZIP_STAT_SIZE) == ZIP_STAT_SIZE)
				size = stat.size;
			else
				size = -1;

			/* Open file in archive */
			zf = IZip->zip_fopen_index(za, index, nodecomp ? ZIP_FL_COMPRESSED : 0);
			if (zf == NULL) {
				fprintf(stderr, "%s (index %lld): %s (line %d)\n", archive, index, IZip->zip_strerror(za), __LINE__);
				goto cleanup;
			}

			/* Open destination file */
			file = IDOS->Open(pathbuf, MODE_NEWFILE);
			if (file == ZERO) {
				IDOS->PrintFault(IDOS->IoErr(), stat.name);
				goto cleanup;
			}

			done = 0;
			printf("Extracting %s... 0%%", stat.name);
			fflush(stdout); /* No newline was written so stdout must be flushed manually */

			while ((readlen = IZip->zip_fread(zf, buffer, BUFFER_SIZE)) > 0) {
				writelen = IDOS->Write(file, buffer, readlen);

				if (writelen >= 0) {
					done += writelen;

					if (size != -1) {
						/* Update progress if uncompressed file size is known */
						printf("\rExtracting %s... %u%%", stat.name, (unsigned)((done * 100) / size));
						fflush(stdout); /* No newline was written so stdout must be flushed manually */
					}
				}

				if (writelen != readlen) {
					putc('\n', stdout);
					IDOS->PrintFault(IDOS->IoErr(), stat.name);
					goto cleanup;
				}

				if (IDOS->CheckSignal(SIGBREAKF_CTRL_C)) {
					putc('\n', stdout);
					fputs("Break signal received\n", stderr);
					goto cleanup;
				}
			}

			if (readlen == -1) {
				putc('\n', stdout);
				fprintf(stderr, "%s (index %lld): %s (line %d)\n", archive, index, IZip->zip_file_strerror(zf), __LINE__);
				goto cleanup;
			}

			printf("\rExtracting %s... Done\n", stat.name);

			/* Close file in archive */
			IZip->zip_fclose(zf);
			zf = NULL;

			/* Close destination file */
			IDOS->Close(file);
			file = ZERO;
		}

		/* Unlock destination directory */
		IDOS->UnLock(dirlock);
		dirlock = ZERO;
	}

	/* Success */
	result = TRUE;

cleanup:

	if (zf != NULL) {
		/* Close file in archive */
		IZip->zip_fclose(zf);
	}

	if (file != ZERO) {
		/* Close destination file */
		IDOS->Close(file);
	}

	if (dirlock != ZERO) {
		/* Unlock destination directory */
		IDOS->UnLock(dirlock);
	}

	if (buffer != NULL)
		IExec->FreeVec(buffer);

	/* Close archive and free resources */
	if (za != NULL)
		IZip->zip_close(za);

	return result;
}

int main(void) {
	struct RDArgs *rda;
	int32          args[NUM_ARGS];
	CONST_STRPTR   archive;
	CONST_STRPTR   password;
	BOOL           nodecomp;
	int            rc = RETURN_ERROR;

	/* Disable builtin break handling */
	signal(SIGINT, SIG_IGN);

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
	password = (CONST_STRPTR)args[ARG_PASSWORD];
	nodecomp = args[ARG_NODECOMP] ? TRUE : FALSE;

	if (extract_zip(archive, password, nodecomp))
		rc = RETURN_OK;

cleanup:

	/* Close zip.library */
	IExec->DropInterface((struct Interface *)IZip);
	IExec->CloseLibrary(ZipBase);

	IDOS->FreeArgs(rda);

	return rc;
}

