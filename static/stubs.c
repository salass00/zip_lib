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

#include <proto/zip.h>
#include <stdarg.h>

zip_int64_t zip_source_make_command_bitmap(zip_source_cmd_t cmd0, ...) {
	zip_int64_t bitmap;
	va_list     ap;
	int         cmd;

	bitmap = ZIP_SOURCE_MAKE_COMMAND_BITMASK(cmd0);

	va_start(ap, cmd0);

	while ((cmd = va_arg(ap, int)) >= 0)
		bitmap |= ZIP_SOURCE_MAKE_COMMAND_BITMASK(cmd);

	va_end(ap);

	return bitmap;
}

int zip_archive_set_tempdir(zip_t *archive, const char *tempdir) {
	return IZip->zip_archive_set_tempdir(archive, tempdir);
}

int zip_close(zip_t *archive) {
	return IZip->zip_close(archive);
}

int zip_delete(zip_t *archive, zip_uint64_t index) {
	return IZip->zip_delete(archive, index);
}

zip_int64_t zip_dir_add(zip_t *archive, const char *name, zip_flags_t flags) {
	return IZip->zip_dir_add(archive, name, flags);
}

void zip_discard(zip_t *archive) {
	IZip->zip_discard(archive);
}

void zip_error_clear(zip_t *archive) {
	IZip->zip_error_clear(archive);
}

void zip_error_get(zip_t *archive, int *zep, int *sep) {
	IZip->zip_error_get(archive, zep, sep);
}

int zip_error_get_sys_type(int ze) {
	return IZip->zip_error_get_sys_type(ze);
}

int zip_error_to_str(char *buf, zip_uint64_t len, int ze, int se) {
	return IZip->zip_error_to_str(buf, len, ze, se);
}

int zip_fclose(zip_file_t *file) {
	return IZip->zip_fclose(file);
}

zip_t *zip_fdopen(int fd, int flags, int *errorp) {
	return IZip->zip_fdopen(fd, flags, errorp);
}

zip_int64_t zip_file_add(zip_t *archive, const char *name, zip_source_t *source,
	zip_flags_t flags)
{
	return IZip->zip_file_add(archive, name, source, flags);
}

void zip_file_error_clear(zip_file_t *file) {
	IZip->zip_file_error_clear(file);
}

void zip_file_error_get(zip_file_t *file, int *zep, int *sep) {
	IZip->zip_file_error_get(file, zep, sep);
}

int zip_file_extra_field_delete(zip_t *archive, zip_uint64_t index, zip_uint16_t ef_index,
	zip_flags_t flags)
{
	return IZip->zip_file_extra_field_delete(archive, index, ef_index, flags);
}

int zip_file_extra_field_delete_by_id(zip_t *archive, zip_uint64_t index, zip_uint16_t ef_id,
	zip_uint16_t ef_index, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_delete_by_id(archive, index, ef_id, ef_index, flags);
}

int zip_file_extra_field_set(zip_t *archive, zip_uint64_t index, zip_uint16_t ef_id,
	zip_uint16_t ef_index, const zip_uint8_t *data, zip_uint16_t len, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_set(archive, index, ef_id, ef_index, data, len, flags);
}

zip_int16_t zip_file_extra_fields_count(zip_t *archive, zip_uint64_t index, zip_flags_t flags) {
	return IZip->zip_file_extra_fields_count(archive, index, flags);
}

zip_int16_t zip_file_extra_fields_count_by_id(zip_t *archive, zip_uint64_t index, zip_uint16_t ef_id,
	zip_flags_t flags)
{
	return IZip->zip_file_extra_fields_count_by_id(archive, index, ef_id, flags);
}

const zip_uint8_t *zip_file_extra_field_get(zip_t *archive, zip_uint64_t index, zip_uint16_t ef_index,
	zip_uint16_t *idp, zip_uint16_t *lenp, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_get(archive, index, ef_index, idp, lenp, flags);
}

const zip_uint8_t *zip_file_extra_field_get_by_id(zip_t *archive, zip_uint64_t index, zip_uint16_t ef_id,
	zip_uint16_t ef_index, zip_uint16_t *lenp, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_get_by_id(archive, index, ef_id, ef_index, lenp, flags);
}

const char *zip_file_get_comment(zip_t *archive, zip_uint64_t index, zip_uint32_t *lenp,
	zip_flags_t flags)
{
	return IZip->zip_file_get_comment(archive, index, lenp, flags);
}

int zip_file_get_external_attributes(zip_t *archive, zip_uint64_t index, zip_flags_t flags,
	zip_uint8_t *opsys, zip_uint32_t *attributes)
{
	return IZip->zip_file_get_external_attributes(archive, index, flags, opsys, attributes);
}

int zip_file_rename(zip_t *archive, zip_uint64_t index, const char *name, zip_flags_t flags) {
	return IZip->zip_file_rename(archive, index, name, flags);
}

int zip_file_replace(zip_t *archive, zip_uint64_t index, zip_source_t *source, zip_flags_t flags) {
	return IZip->zip_file_replace(archive, index, source, flags);
}

int zip_file_set_comment(zip_t *archive, zip_uint64_t index, const char *comment, zip_uint16_t len,
	zip_flags_t flags)
{
	return IZip->zip_file_set_comment(archive, index, comment, len, flags);
}

int zip_file_set_external_attributes(zip_t *archive, zip_uint64_t index, zip_flags_t flags,
	zip_uint8_t opsys, zip_uint32_t attributes)
{
	return IZip->zip_file_set_external_attributes(archive, index, flags, opsys, attributes);
}

const char *zip_file_strerror(zip_file_t *file) {
	return IZip->zip_file_strerror(file);
}

zip_file_t *zip_fopen(zip_t *archive, const char *fname, zip_flags_t flags) {
	return IZip->zip_fopen(archive, fname, flags);
}

zip_file_t *zip_fopen_encrypted(zip_t *archive, const char *fname, zip_flags_t flags,
	const char *password)
{
	return IZip->zip_fopen_encrypted(archive, fname, flags, password);
}

zip_file_t *zip_fopen_index(zip_t *archive, zip_uint64_t index, zip_flags_t flags) {
	return IZip->zip_fopen_index(archive, index, flags);
}

zip_file_t *zip_fopen_index_encrypted(zip_t *archive, zip_uint64_t index, zip_flags_t flags,
	const char *password)
{
	return IZip->zip_fopen_index_encrypted(archive, index, flags, password);
}

zip_int64_t zip_fread(zip_file_t *file, void *outbuf, zip_uint64_t toread) {
	return IZip->zip_fread(file, outbuf, toread);
}

const char *zip_get_archive_comment(zip_t *archive, int *lenp, zip_flags_t flags) {
	return IZip->zip_get_archive_comment(archive, lenp, flags);
}

int zip_get_archive_flag(zip_t *archive, zip_flags_t flag, zip_flags_t flags) {
	return IZip->zip_get_archive_flag(archive, flag, flags);
}

const char *zip_get_name(zip_t *archive, zip_uint64_t index, zip_flags_t flags) {
	return IZip->zip_get_name(archive, index, flags);
}

zip_int64_t zip_get_num_entries(zip_t *archive, zip_flags_t flags) {
	return IZip->zip_get_num_entries(archive, flags);
}

zip_int64_t zip_name_locate(zip_t *archive, const char *fname, zip_flags_t flags) {
	return IZip->zip_name_locate(archive, fname, flags);
}

zip_t *zip_open(const char *path, int flags, int *errorp) {
	return IZip->zip_open(path, flags, errorp);
}

int zip_set_archive_comment(zip_t *archive, const char *comment, zip_uint16_t len) {
	return IZip->zip_set_archive_comment(archive, comment, len);
}

int zip_set_archive_flag(zip_t *archive, zip_flags_t flag, int value) {
	return IZip->zip_set_archive_flag(archive, flag, value);
}

int zip_set_default_password(zip_t *archive, const char *passwd) {
	return IZip->zip_set_default_password(archive, passwd);
}

int zip_set_file_compression(zip_t *archive, zip_uint64_t index, zip_int32_t method, zip_uint32_t flags) {
	return IZip->zip_set_file_compression(archive, index, method, flags);
}

zip_source_t *zip_source_buffer(zip_t *archive, const void *data, zip_uint64_t len, int freep) {
	return IZip->zip_source_buffer(archive, data, len, freep);
}

zip_source_t *zip_source_file(zip_t *archive, const char *fname, zip_uint64_t start, zip_int64_t len) {
	return IZip->zip_source_file(archive, fname, start, len);
}

zip_source_t *zip_source_filep(zip_t *archive, FILE *file, zip_uint64_t start, zip_int64_t len) {
	return IZip->zip_source_filep(archive, file, start, len);
}

void zip_source_free(zip_source_t *src) {
	IZip->zip_source_free(src);
}

zip_source_t *zip_source_function(zip_t *archive, zip_source_callback zcb, void *ud) {
	return IZip->zip_source_function(archive, zcb, ud);
}

zip_source_t *zip_source_zip(zip_t *archive, zip_t *srcarchive, zip_uint64_t srcindex, zip_flags_t flags,
	zip_uint64_t start, zip_int64_t len)
{
	return IZip->zip_source_zip(archive, srcarchive, srcindex, flags, start, len);
}

int zip_stat(zip_t *archive, const char *fname, zip_flags_t flags, zip_stat_t *st) {
	return IZip->zip_stat(archive, fname, flags, st);
}

int zip_stat_index(zip_t *archive, zip_uint64_t index, zip_flags_t flags, zip_stat_t *st) {
	return IZip->zip_stat_index(archive, index, flags, st);
}

void zip_stat_init(zip_stat_t *st) {
	IZip->zip_stat_init(st);
}

const char *zip_strerror(zip_t *archive) {
	return IZip->zip_strerror(archive);
}

int zip_unchange(zip_t *archive, zip_uint64_t index) {
	return IZip->zip_unchange(archive, index);
}

int zip_unchange_all(zip_t *archive) {
	return IZip->zip_unchange_all(archive);
}

int zip_unchange_archive(zip_t *archive) {
	return IZip->zip_unchange_archive(archive);
}

/* Functions added in V53.5 */

zip_error_t *zip_get_error(zip_t *archive) {
	return IZip->zip_get_error(archive);
}

int zip_error_code_zip(const zip_error_t *error) {
	return IZip->zip_error_code_zip(error);
}

int zip_error_code_system(const zip_error_t *error) {
	return IZip->zip_error_code_system(error);
}

void zip_error_fini(zip_error_t *error) {
	IZip->zip_error_fini(error);
}

void zip_error_init(zip_error_t *error) {
	IZip->zip_error_init(error);
}

void zip_error_init_with_code(zip_error_t *error, int ze) {
	IZip->zip_error_init_with_code(error, ze);
}

void zip_error_set(zip_error_t *error, int ze, int se) {
	IZip->zip_error_set(error, ze, se);
}

const char *zip_error_strerror(zip_error_t *error) {
	return IZip->zip_error_strerror(error);
}

int zip_error_system_type(const zip_error_t *error) {
	return IZip->zip_error_system_type(error);
}

zip_int64_t zip_error_to_data(const zip_error_t *error, void *data, zip_uint64_t length) {
	return IZip->zip_error_to_data(error, data, length);
}

zip_t *zip_open_from_source(zip_source_t *source, int flags, zip_error_t *ze) {
	return IZip->zip_open_from_source(source, flags, ze);
}

int zip_file_set_encryption(zip_t *archive, zip_uint64_t index, zip_uint16_t method,
	const char *password)
{
	return IZip->zip_file_set_encryption(archive, index, method, password);
}

/* Functions added in V53.6 */

void zip_register_progress_callback(zip_t *archive, zip_progress_callback_t cb) {
	IZip->zip_register_progress_callback(archive, cb);
}

int zip_register_progress_callback_with_state(zip_t *archive, double precision,
	zip_progress_callback cb, void (*ud_free)(void *), void *ud)
{
	return IZip->zip_register_progress_callback_with_state(archive, precision, cb, ud_free, ud);
}

zip_error_t *zip_file_get_error(zip_file_t *file) {
	return IZip->zip_file_get_error(file);
}

int zip_file_set_mtime(zip_t *archive, zip_uint64_t index, time_t mtime, zip_flags_t flags) {
	return IZip->zip_file_set_mtime(archive, index, mtime, flags);
}

zip_int8_t zip_fseek(zip_file_t *file, zip_int64_t offset, int whence) {
	return IZip->zip_fseek(file, offset, whence);
}

zip_int64_t zip_ftell(zip_file_t *file) {
	return IZip->zip_ftell(file);
}

int zip_source_begin_write(zip_source_t *source) {
	return IZip->zip_source_begin_write(source);
}

zip_source_t *zip_source_buffer_create(const void *data, zip_uint64_t len, int freep, zip_error_t *error) {
	return IZip->zip_source_buffer_create(data, len, freep, error);
}

int zip_source_close(zip_source_t *source) {
	return IZip->zip_source_close(source);
}

int zip_source_commit_write(zip_source_t *source) {
	return IZip->zip_source_commit_write(source);
}

zip_error_t *zip_source_error(zip_source_t *source) {
	return IZip->zip_source_error(source);
}

zip_source_t *zip_source_file_create(const char *fname, zip_uint64_t start, zip_int64_t len, zip_error_t *error) {
	return IZip->zip_source_file_create(fname, start, len, error);
}

zip_source_t *zip_source_filep_create(FILE *file, zip_uint64_t start, zip_int64_t len, zip_error_t *error) {
	return IZip->zip_source_filep_create(file, start, len, error);
}

zip_source_t *zip_source_function_create(zip_source_callback fn, void *userdata, zip_error_t *error) {
	return IZip->zip_source_function_create(fn, userdata, error);
}

int zip_source_is_deleted(zip_source_t *source) {
	return IZip->zip_source_is_deleted(source);
}

void zip_source_keep(zip_source_t *source) {
	IZip->zip_source_keep(source);
}

int zip_source_open(zip_source_t *source) {
	return IZip->zip_source_open(source);
}

zip_int64_t zip_source_read(zip_source_t *source, void *data, zip_uint64_t len) {
	return IZip->zip_source_read(source, data, len);
}

void zip_source_rollback_write(zip_source_t *source) {
	IZip->zip_source_rollback_write(source);
}

int zip_source_seek(zip_source_t *source, zip_int64_t offset, int whence) {
	return IZip->zip_source_seek(source, offset, whence);
}

zip_int64_t zip_source_seek_compute_offset(zip_uint64_t offset, zip_uint64_t length, void *data,
	zip_uint64_t data_length, zip_error_t *error)
{
	return IZip->zip_source_seek_compute_offset(offset, length, data, data_length, error);
}

int zip_source_seek_write(zip_source_t *source, zip_int64_t offset, int whence) {
	return IZip->zip_source_seek_write(source, offset, whence);
}

int zip_source_stat(zip_source_t *source, zip_stat_t *sourcetat) {
	return IZip->zip_source_stat(source, sourcetat);
}

zip_int64_t zip_source_tell(zip_source_t *source) {
	return IZip->zip_source_tell(source);
}

zip_int64_t zip_source_tell_write(zip_source_t *source) {
	return IZip->zip_source_tell_write(source);
}

zip_int64_t zip_source_write(zip_source_t *source, const void *data, zip_uint64_t len) {
	return IZip->zip_source_write(source, data, len);
}

const char *zip_libzip_version(void) {
	return IZip->zip_libzip_version();
}

