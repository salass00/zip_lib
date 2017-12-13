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

#include "zipint.h"
#include "zipamigaos.h"

#define IS_VALID_BPTR(bptr) ((((uint32)(bptr)) & 0xC0000000) == 0)

static zip_int64_t read_file(void *state, void *data, zip_uint64_t len, zip_source_cmd_t cmd);

ZIP_EXTERN zip_source_t *
zip_source_amigaos_fh(zip_t *za, BPTR fh, zip_uint64_t start, zip_int64_t len)
{
	if (za == NULL)
		return NULL;

	return zip_source_amigaos_fh_create(fh, start, len, NULL, &za->error);
}

ZIP_EXTERN zip_source_t *
zip_source_amigaos_fh_create(BPTR fh, zip_uint64_t start, zip_int64_t len, zip_error_t *error)
{
	if (fh == ZERO || !IS_VALID_BPTR(fh)) {
		zip_error_set(error, ZIP_ER_INVAL, 0);
		return NULL;
	}

	return _zip_source_amigaos_fh_or_name(NULL, fh, start, len, NULL, error);
}

zip_source_t *
_zip_source_amigaos_fh_or_name(const char *fname, BPTR fh, zip_uint64_t start, zip_int64_t len, const zip_stat_t *st, zip_error_t *error)
{
	_zip_source_amigaos_read_file_t *ctx;
	zip_source_t                    *zs;
	struct ExamineData              *exd;

	if (fh == ZERO && fname == NULL) {
		zip_error_set(error, ZIP_ER_INVAL, 0);
		return NULL;
	}

	ctx = (_zip_source_amigaos_read_file_t *)malloc(sizeof(_zip_source_amigaos_read_file_t));
	if (ctx == NULL) {
		zip_error_set(error, ZIP_ER_MEMORY, 0);
		return NULL;
	}

	ctx->fname = NULL;
	if (fname != NULL) {
		ctx->fname = strdup(fname);
		if (ctx->fname == NULL) {
			zip_error_set(error, ZIP_ER_MEMORY, 0);
			free(ctx);
			return NULL;
		}
	}

	ctx->fh    = fh;
	ctx->start = start;
	ctx->len   = (len < 0) ? 0 : len;

	if (st != NULL) {
		memcpy(&ctx->st, st, sizeof(ctx->st));
		ctx->st.name = NULL;
		ctx->st.valid &= ~ZIP_STAT_NAME;
	} else {
		zip_stat_init(&ctx->st);
	}

	if (ctx->len != 0) {
		ctx->st.size = ctx->len;
		ctx->st.valid |= ZIP_STAT_SIZE;
	}

	zip_error_init(&ctx->examine_error);

	ctx->tmpname = NULL;
	ctx->fhout = ZERO;

	zip_error_init(&ctx->error);

	ctx->supports = ZIP_SOURCE_SUPPORTS_READABLE | zip_source_make_command_bitmap(ZIP_SOURCE_SUPPORTS, ZIP_SOURCE_TELL, -1);

	if (ctx->fname != NULL) {
		exd = IDOS->ExamineObjectTags(EX_StringNameInput, ctx->fname, TAG_END);
		if (exd == NULL) {
			if (ctx->start == 0 && ctx->len == 0) {
				ctx->supports = ZIP_SOURCE_SUPPORTS_WRITABLE;
			}
		}
	} else {
		exd = IDOS->ExamineObjectTags(EX_FileHandleInput, ctx->fh, TAG_END);
	}

	if (exd != NULL) {
		if ((ctx->st.valid & ZIP_STAT_TIME) == 0) {
			ctx->st.mtime = _convert_datestamp(&exd->Date);
			ctx->st.valid |= ZIP_STAT_TIME;
		}
		if (EXD_IS_FILE(exd) && exd->FileSize != -1) {
			ctx->supports = ZIP_SOURCE_SUPPORTS_SEEKABLE;

			if ((ctx->start + ctx->len) > (zip_uint64_t)exd->FileSize) {
				zip_error_set(error, ZIP_ER_INVAL, 0);
				free(ctx->fname);
				free(ctx);
				return NULL;
			}

			if (ctx->len == 0) {
				ctx->st.size = (zip_uint64_t)exd->FileSize - ctx->start;
				ctx->st.valid |= ZIP_STAT_SIZE;

				if (ctx->fname != NULL && start == 0) {
					ctx->supports = ZIP_SOURCE_SUPPORTS_WRITABLE;
				}
			}
		}
	} else {
		zip_error_set(&ctx->examine_error, ZIP_ER_READ, _convert_ioerr(IDOS->IoErr()));
	}

	zs = zip_source_function_create(read_file, ctx, error);
	if (zs == NULL) {
		zip_error_set(error, ZIP_ER_MEMORY, 0);
		free(ctx->fname);
		free(ctx);
		return NULL;
	}

	return zs;
}

static zip_int64_t
read_file(void *state, void *data, zip_uint64_t len, zip_source_cmd_t cmd)
{
	struct read_file *ctx;
	char             *buf;
	zip_uint64_t      n;
	int32             i;

	ctx = (struct read_file *)state;
	buf = (char *)data;

	switch (cmd) {
		case ZIP_SOURCE_BEGIN_WRITE:
			if (ctx->fname == NULL) {
				zip_error_set(&ctx->error, ZIP_ER_OPNOTSUPP, 0);
				return -1;
			}
			return create_temp_output(ctx);

		case ZIP_SOURCE_COMMIT_WRITE:
			if (IDOS->Close(ctx->fh) == FALSE) {
				ctx->fh = ZERO;
				zip_error_set(&ctx->error, ZIP_ER_WRITE, _convert_ioerr(IDOS->IoErr()));
			}
			ctx->fh = ZERO;
			if (IDOS->Rename(ctx->tmpname, ctx->fname) == FALSE) {
				zip_error_set(&ctx->error, ZIP_ER_RENAME, _convert_ioerr(IDOS->IoErr()));
                return -1;
			}
			free(ctx->tmpname);
			ctx->tmpname = NULL;
			return 0;

		case ZIP_SOURCE_CLOSE:
			if (ctx->fname != NULL) {
				IDOS->Close(ctx->f);
				ctx->f = ZERO;
			}
			return 0;

		case ZIP_SOURCE_ERROR:
			return zip_error_to_data(&ctx->error, data, len);

		case ZIP_SOURCE_FREE:
			free(ctx->fname);
			free(ctx->tmpname);
			IDOS->Close(ctx->f);
			free(ctx);
			return 0;

		case ZIP_SOURCE_OPEN:
			if (ctx->fname != NULL) {
				ctx->f = IDOS->Open(ctx->fname, MODE_OLDFILE);
				if (ctx->f == ZERO) {
					zip_error_set(&ctx->error, ZIP_ER_OPEN, _convert_ioerr(IDOS->IoErr()));
					return -1;
				}
			}

			if (ctx->start > 0) {
				if (ctx->start > ZIP_INT64_MAX) {
					zip_error_set(&ctx->error, ZIP_ER_SEEK, EOVERFLOW);
					return -1;
				}

				if (IDOS->ChangeFilePosition(ctx->f, ctx->start, OFFSET_BEGINNING) == FALSE) {
					/* TODO: skip by reading */
					zip_error_set(&ctx->error, ZIP_ER_SEEK, _convert_ioerr(IDOS->IoErr()));
					return -1;
				}
			}
			ctx->current = 0;
			return 0;

		case ZIP_SOURCE_READ:
			if (ctx->end > 0) {
				n = ctx->end - ctx->current;
				if (n > len) {
					n = len;
				}
			} else {
				n = len;
			}

			if (n > INT32_MAX)
				n = INT32_MAX;

			i = IDOS->Read(ctx->f, buf, n);
			if (i == -1) {
				zip_error_set(&ctx->error, ZIP_ER_READ, _convert_ioerr(IDOS->IoErr()));
				return -1;
			}
			ctx->current += i;

			return (zip_int64_t)i;

		case ZIP_SOURCE_REMOVE:
			if (Delete(ctx->fname) == FALSE) {
				zip_error_set(&ctx->error, ZIP_ER_REMOVE, _convert_ioerr(IDOS->IoErr()));
				return -1;
			}
			return 0;

		case ZIP_SOURCE_ROLLBACK_WRITE:
			if (ctx->fout != ZERO) {
				IDOS->Close(ctx->fout);
				ctx->fout = ZERO;
			}
			IDOS->Delete(ctx->tmpname);
			free(ctx->tmpname);
			ctx->tmpname = NULL;
			return 0;

		case ZIP_SOURCE_SEEK:
			{
				zip_source_args_seek_t *args;
				zip_int64_t             new_current;
				BOOL                    need_seek;

				args = ZIP_SOURCE_GET_ARGS(zip_source_args_seek_t, data, len, &ctx->error);
				if (args == NULL)
					return -1;

				need_seek = TRUE;

				switch (args->whence) {
					case SEEK_SET:
						new_current = args->offset;
						break;

					case SEEK_END:
						if (ctx->end == 0) {
							if (IDOS->ChangeFilePosition(ctx->f, args->offset, OFFSET_BEGINNING) == FALSE) {
								zip_error_set(&ctx->error, ZIP_ER_SEEK, _convert_ioerr(IDOS->IoErr()));
								return -1;
							}
							new_current = IDOS->GetFilePosition(ctx->f);
							if (new_current < 0) {
								zip_error_set(&ctx->error, ZIP_ER_SEEK, _convert_ioerr(IDOS->IoErr()));
								return -1;
							}
							new_current -= (zip_int64_t)ctx->start;
							need_seek = FALSE;
						} else {
							new_current = (zip_int64_t)ctx->end + args->offset;
						}
						break;

					case SEEK_CUR:
						new_current = (zip_int64_t)ctx->current + args->offset;
						break;

					default:
						zip_error_set(&ctx->error, ZIP_ER_INVAL, 0);
						return -1;
				}

				if (new_current < 0 || (ctx->end != 0 && (zip_uint64_t)new_current > ctx->end) ||
					(zip_uint64_t)new_current + ctx->start < ctx->start)
				{
					zip_error_set(&ctx->error, ZIP_ER_INVAL, 0);
					return -1;
				}

				ctx->current = (zip_uint64_t)new_current;

				if (need_seek) {
					if (IDOS->ChangeFilePosition(ctx->f, ctx->current + ctx->start, OFFSET_BEGINNING) == FALSE) {
						zip_error_set(&ctx->error, ZIP_ER_SEEK, _convert_ioerr(IDOS->IoErr()));
						return -1;
					}
				}
				return 0;
			}

		case ZIP_SOURCE_SEEK_WRITE:
			{
				zip_source_args_seek_t *args;

				args = ZIP_SOURCE_GET_ARGS(zip_source_args_seek_t, data, len, &ctx->error);
				if (args == NULL)
					return -1;

				if (IDOS->ChangeFilePosition(ctx->fout, args->offset, mode) == FALSE) {
					zip_error_set(&ctx->error, ZIP_ER_SEEK, _convert_ioerr(IDOS->IoErr()));
					return -1;
				}
				return 0;
			}

		case ZIP_SOURCE_STAT:
			if (len < sizeof(ctx->st))
				return -1;

			if (zip_error_code_zip(&ctx->stat_error) != 0) {
				zip_error_set(&ctx->error, zip_error_code_zip(&ctx->stat_error), zip_error_code_system(&ctx->stat_error));
				return -1;
			}

			memcpy(data, &ctx->st, sizeof(ctx->st));
			return sizeof(ctx->st);

		case ZIP_SOURCE_SUPPORTS:
			return ctx->supports;

		case ZIP_SOURCE_TELL:
			return (zip_int64_t)ctx->current;

		case ZIP_SOURCE_TELL_WRITE:
			{
				int64 ret;

				ret = IDOS->GetFilePosition(ctx->fout);
				if (ret < 0) {
					zip_error_set(&ctx->error, ZIP_ER_TELL, _convert_ioerr(IDOS->IoErr()));
					return -1;
				}
				return ret;
			}

		case ZIP_SOURCE_WRITE:
			{
				int32 ret;

				ret = IDOS->Write(ctx->fout, data, len);
				if (ret != len) {
					zip_error_set(&ctx->error, ZIP_ER_WRITE, _convert_ioerr(IDOS->IoErr()));
					return -1;
				}

				return (zip_int64_t)ret;
			}

		default:
			zip_error_set(&ctx->error, ZIP_ER_OPNOTSUPP, 0);
			return -1;
	}
}

