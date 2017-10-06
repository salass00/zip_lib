
/* This file was generated by idltool 53.23. Do not edit */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif
#ifndef LIBRARIES_ZIP_H
#include <libraries/zip.h>
#endif

/* forward declaration */
struct ZipIFace;

extern uint32               VARARGS68K _main_Obtain(struct ZipIFace *);
extern uint32               VARARGS68K _main_Release(struct ZipIFace *);
extern zip_int32_t          VARARGS68K _main_zip_archive_set_tempdir(struct ZipIFace *, zip_t * za, CONST_STRPTR tempdir);
extern zip_int32_t          VARARGS68K _main_zip_close(struct ZipIFace *, zip_t * za);
extern zip_int32_t          VARARGS68K _main_zip_delete(struct ZipIFace *, zip_t * za, zip_uint64_t idx);
extern zip_int64_t          VARARGS68K _main_zip_dir_add(struct ZipIFace *, zip_t * za, CONST_STRPTR name, zip_flags_t flags);
extern void                 VARARGS68K _main_zip_discard(struct ZipIFace *, zip_t * za);
extern void                 VARARGS68K _main_zip_error_clear(struct ZipIFace *, zip_t * za);
extern void                 VARARGS68K _main_zip_error_get(struct ZipIFace *, zip_t * za, zip_int32_t * zep, zip_int32_t * sep);
extern zip_int32_t          VARARGS68K _main_zip_error_get_sys_type(struct ZipIFace *, zip_int32_t ze);
extern zip_int32_t          VARARGS68K _main_zip_error_to_str(struct ZipIFace *, STRPTR buf, zip_uint64_t len, zip_int32_t ze, zip_int32_t se);
extern zip_int32_t          VARARGS68K _main_zip_fclose(struct ZipIFace *, zip_file_t * zf);
extern zip_t *              VARARGS68K _main_zip_fdopen(struct ZipIFace *, zip_int32_t fd_orig, zip_int32_t _flags, zip_int32_t * zep);
extern zip_int64_t          VARARGS68K _main_zip_file_add(struct ZipIFace *, zip_t * za, CONST_STRPTR name, zip_source_t * source, zip_flags_t flags);
extern void                 VARARGS68K _main_zip_file_error_clear(struct ZipIFace *, zip_file_t * zf);
extern void                 VARARGS68K _main_zip_file_error_get(struct ZipIFace *, zip_file_t * zf, zip_int32_t * zep, zip_int32_t * sep);
extern zip_int32_t          VARARGS68K _main_zip_file_extra_field_delete(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_uint16_t ef_idx, zip_flags_t flags);
extern zip_int32_t          VARARGS68K _main_zip_file_extra_field_delete_by_id(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_uint16_t ef_id, zip_uint16_t ef_idx, zip_flags_t flags);
extern zip_int32_t          VARARGS68K _main_zip_file_extra_field_set(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_uint16_t ef_id, zip_uint16_t ef_idx, const zip_uint8_t * data, zip_uint16_t len, zip_flags_t flags);
extern zip_int16_t          VARARGS68K _main_zip_file_extra_fields_count(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_flags_t flags);
extern zip_int16_t          VARARGS68K _main_zip_file_extra_fields_count_by_id(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_uint16_t ef_id, zip_flags_t flags);
extern const zip_uint8_t *  VARARGS68K _main_zip_file_extra_field_get(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_uint16_t ef_idx, zip_uint16_t * idp, zip_uint16_t * lenp, zip_flags_t flags);
extern const zip_uint8_t *  VARARGS68K _main_zip_file_extra_field_get_by_id(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_uint16_t ef_id, zip_uint16_t ef_idx, zip_uint16_t * lenp, zip_flags_t flags);
extern CONST_STRPTR         VARARGS68K _main_zip_file_get_comment(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_uint32_t * lenp, zip_flags_t flags);
extern zip_int32_t          VARARGS68K _main_zip_file_get_external_attributes(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_flags_t flags, zip_uint8_t * opsys, zip_uint32_t * attributes);
extern zip_int32_t          VARARGS68K _main_zip_file_rename(struct ZipIFace *, zip_t * za, zip_uint64_t idx, CONST_STRPTR name, zip_flags_t flags);
extern zip_int32_t          VARARGS68K _main_zip_file_replace(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_source_t * source, zip_flags_t flags);
extern zip_int32_t          VARARGS68K _main_zip_file_set_comment(struct ZipIFace *, zip_t * za, zip_uint64_t idx, CONST_STRPTR comment, zip_uint16_t len, zip_flags_t flags);
extern zip_int32_t          VARARGS68K _main_zip_file_set_external_attributes(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_flags_t flags, zip_uint8_t opsys, zip_uint32_t attributes);
extern CONST_STRPTR         VARARGS68K _main_zip_file_strerror(struct ZipIFace *, zip_file_t * zf);
extern zip_file_t *         VARARGS68K _main_zip_fopen(struct ZipIFace *, zip_t * za, CONST_STRPTR fname, zip_flags_t flags);
extern zip_file_t *         VARARGS68K _main_zip_fopen_encrypted(struct ZipIFace *, zip_t * za, CONST_STRPTR fname, zip_flags_t flags, CONST_STRPTR password);
extern zip_file_t *         VARARGS68K _main_zip_fopen_index(struct ZipIFace *, zip_t * za, zip_uint64_t index, zip_flags_t flags);
extern zip_file_t *         VARARGS68K _main_zip_fopen_index_encrypted(struct ZipIFace *, zip_t * za, zip_uint64_t index, zip_flags_t flags, CONST_STRPTR password);
extern zip_int64_t          VARARGS68K _main_zip_fread(struct ZipIFace *, zip_file_t * zf, APTR outbuf, zip_uint64_t toread);
extern CONST_STRPTR         VARARGS68K _main_zip_get_archive_comment(struct ZipIFace *, zip_t * za, zip_int32_t * lenp, zip_flags_t flags);
extern zip_int32_t          VARARGS68K _main_zip_get_archive_flag(struct ZipIFace *, zip_t * za, zip_uint32_t flag, zip_flags_t flags);
extern CONST_STRPTR         VARARGS68K _main_zip_get_name(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_flags_t flags);
extern zip_int64_t          VARARGS68K _main_zip_get_num_entries(struct ZipIFace *, zip_t * za, zip_flags_t flags);
extern zip_int64_t          VARARGS68K _main_zip_name_locate(struct ZipIFace *, zip_t * za, CONST_STRPTR fname, zip_flags_t flags);
extern zip_t *              VARARGS68K _main_zip_open(struct ZipIFace *, CONST_STRPTR fn, zip_int32_t _flags, zip_int32_t * zep);
extern zip_int32_t          VARARGS68K _main_zip_set_archive_comment(struct ZipIFace *, zip_t * za, CONST_STRPTR comment, zip_uint16_t len);
extern zip_int32_t          VARARGS68K _main_zip_set_archive_flag(struct ZipIFace *, zip_t * za, zip_uint32_t flag, zip_int32_t value);
extern zip_int32_t          VARARGS68K _main_zip_set_default_password(struct ZipIFace *, zip_t * za, CONST_STRPTR passwd);
extern zip_int32_t          VARARGS68K _main_zip_set_file_compression(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_int32_t method, zip_flags_t flags);
extern zip_source_t *       VARARGS68K _main_zip_source_buffer(struct ZipIFace *, zip_t * za, CONST_APTR data, zip_uint64_t len, zip_int32_t freep);
extern zip_source_t *       VARARGS68K _main_zip_source_file(struct ZipIFace *, zip_t * za, CONST_STRPTR fname, zip_uint64_t start, zip_int64_t len);
extern zip_source_t *       VARARGS68K _main_zip_source_filep(struct ZipIFace *, zip_t * za, FILE * file, zip_uint64_t start, zip_int64_t len);
extern void                 VARARGS68K _main_zip_source_free(struct ZipIFace *, zip_source_t * src);
extern zip_source_t *       VARARGS68K _main_zip_source_function(struct ZipIFace *, zip_t * za, zip_source_callback zcb, APTR ud);
extern zip_source_t *       VARARGS68K _main_zip_source_zip(struct ZipIFace *, zip_t * za, zip_t * srcza, zip_uint64_t srcidx, zip_flags_t flags, zip_uint64_t start, zip_int64_t len);
extern zip_int32_t          VARARGS68K _main_zip_stat(struct ZipIFace *, zip_t * za, CONST_STRPTR fname, zip_flags_t flags, zip_stat_t * st);
extern zip_int32_t          VARARGS68K _main_zip_stat_index(struct ZipIFace *, zip_t * za, zip_uint64_t index, zip_flags_t flags, zip_stat_t * st);
extern void                 VARARGS68K _main_zip_stat_init(struct ZipIFace *, zip_stat_t * st);
extern CONST_STRPTR         VARARGS68K _main_zip_strerror(struct ZipIFace *, zip_t * za);
extern zip_int32_t          VARARGS68K _main_zip_unchange(struct ZipIFace *, zip_t * za, zip_uint64_t idx);
extern zip_int32_t          VARARGS68K _main_zip_unchange_all(struct ZipIFace *, zip_t * za);
extern zip_int32_t          VARARGS68K _main_zip_unchange_archive(struct ZipIFace *, zip_t * za);
extern zip_error_t *        VARARGS68K _main_zip_get_error(struct ZipIFace *, zip_t * za);
extern int                  VARARGS68K _main_zip_error_code_zip(struct ZipIFace *, const zip_error_t * error);
extern int                  VARARGS68K _main_zip_error_code_system(struct ZipIFace *, const zip_error_t * error);
extern void                 VARARGS68K _main_zip_error_fini(struct ZipIFace *, zip_error_t * error);
extern void                 VARARGS68K _main_zip_error_init(struct ZipIFace *, zip_error_t * error);
extern void                 VARARGS68K _main_zip_error_init_with_code(struct ZipIFace *, zip_error_t * error, int ze);
extern void                 VARARGS68K _main_zip_error_set(struct ZipIFace *, zip_error_t * error, int ze, int se);
extern const char *         VARARGS68K _main_zip_error_strerror(struct ZipIFace *, zip_error_t * error);
extern int                  VARARGS68K _main_zip_error_system_type(struct ZipIFace *, const zip_error_t * error);
extern zip_int64_t          VARARGS68K _main_zip_error_to_data(struct ZipIFace *, const zip_error_t * error, void * data, zip_uint64_t length);
extern zip_t *              VARARGS68K _main_zip_open_from_source(struct ZipIFace *, zip_source_t * zs, int flags, zip_error_t * ze);
extern int                  VARARGS68K _main_zip_file_set_encryption(struct ZipIFace *, zip_t * za, zip_uint64_t idx, zip_uint16_t method, const char * password);
