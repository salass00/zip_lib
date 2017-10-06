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

int zip_archive_set_tempdir(zip_t *za, const char *tempdir) {
	return IZip->zip_archive_set_tempdir(za, tempdir);
}

int zip_close(zip_t *za) {
	return IZip->zip_close(za);
}

int zip_delete(zip_t *za, zip_uint64_t idx) {
	return IZip->zip_delete(za, idx);
}

zip_int64_t zip_dir_add(zip_t *za, const char *name, zip_flags_t flags) {
	return IZip->zip_dir_add(za, name, flags);
}

void zip_discard(zip_t *za) {
	IZip->zip_discard(za);
}

void zip_error_clear(zip_t *za) {
	IZip->zip_error_clear(za);
}

void zip_error_get(zip_t *za, int *zep, int *sep) {
	IZip->zip_error_get(za, zep, sep);
}

int zip_error_get_sys_type(int ze) {
	return IZip->zip_error_get_sys_type(ze);
}

int zip_error_to_str(char *buf, zip_uint64_t len, int ze, int se) {
	return IZip->zip_error_to_str(buf, len, ze, se);
}

int zip_fclose(zip_file_t *zf) {
	return IZip->zip_fclose(zf);
}

zip_t *zip_fdopen(int fd_orig, int _flags, int *zep) {
	return IZip->zip_fdopen(fd_orig, _flags, zep);
}

zip_int64_t zip_file_add(zip_t *za, const char *name, zip_source_t *source,
	zip_flags_t flags)
{
	return IZip->zip_file_add(za, name, source, flags);
}

void zip_file_error_clear(zip_file_t *zf) {
	IZip->zip_file_error_clear(zf);
}

void zip_file_error_get(zip_file_t *zf, int *zep, int *sep) {
	IZip->zip_file_error_get(zf, zep, sep);
}

int zip_file_extra_field_delete(zip_t *za, zip_uint64_t idx, zip_uint16_t ef_idx,
	zip_flags_t flags)
{
	return IZip->zip_file_extra_field_delete(za, idx, ef_idx, flags);
}

int zip_file_extra_field_delete_by_id(zip_t *za, zip_uint64_t idx, zip_uint16_t ef_id,
	zip_uint16_t ef_idx, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_delete_by_id(za, idx, ef_id, ef_idx, flags);
}

int zip_file_extra_field_set(zip_t *za, zip_uint64_t idx, zip_uint16_t ef_id,
	zip_uint16_t ef_idx, const zip_uint8_t *data, zip_uint16_t len, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_set(za, idx, ef_id, ef_idx, data, len, flags);
}

zip_int16_t zip_file_extra_fields_count(zip_t *za, zip_uint64_t idx, zip_flags_t flags) {
	return IZip->zip_file_extra_fields_count(za, idx, flags);
}

zip_int16_t zip_file_extra_fields_count_by_id(zip_t *za, zip_uint64_t idx, zip_uint16_t ef_id,
	zip_flags_t flags)
{
	return IZip->zip_file_extra_fields_count_by_id(za, idx, ef_id, flags);
}

const zip_uint8_t *zip_file_extra_field_get(zip_t *za, zip_uint64_t idx, zip_uint16_t ef_idx,
	zip_uint16_t *idp, zip_uint16_t *lenp, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_get(za, idx, ef_idx, idp, lenp, flags);
}

const zip_uint8_t *zip_file_extra_field_get_by_id(zip_t *za, zip_uint64_t idx, zip_uint16_t ef_id,
	zip_uint16_t ef_idx, zip_uint16_t *lenp, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_get_by_id(za, idx, ef_id, ef_idx, lenp, flags);
}

const char *zip_file_get_comment(zip_t *za, zip_uint64_t idx, zip_uint32_t *lenp,
	zip_flags_t flags)
{
	return IZip->zip_file_get_comment(za, idx, lenp, flags);
}

int zip_file_get_external_attributes(zip_t *za, zip_uint64_t idx, zip_flags_t flags,
	zip_uint8_t *opsys, zip_uint32_t *attributes)
{
	return IZip->zip_file_get_external_attributes(za, idx, flags, opsys, attributes);
}

int zip_file_rename(zip_t *za, zip_uint64_t idx, const char *name, zip_flags_t flags) {
	return IZip->zip_file_rename(za, idx, name, flags);
}

int zip_file_replace(zip_t *za, zip_uint64_t idx, zip_source_t *source, zip_flags_t flags) {
	return IZip->zip_file_replace(za, idx, source, flags);
}

int zip_file_set_comment(zip_t *za, zip_uint64_t idx, const char *comment, zip_uint16_t len,
	zip_flags_t flags)
{
	return IZip->zip_file_set_comment(za, idx, comment, len, flags);
}

int zip_file_set_external_attributes(zip_t *za, zip_uint64_t idx, zip_flags_t flags,
	zip_uint8_t opsys, zip_uint32_t attributes)
{
	return IZip->zip_file_set_external_attributes(za, idx, flags, opsys, attributes);
}

const char *zip_file_strerror(zip_file_t *zf) {
	return IZip->zip_file_strerror(zf);
}

zip_file_t *zip_fopen(zip_t *za, const char *fname, zip_flags_t flags) {
	return IZip->zip_fopen(za, fname, flags);
}

zip_file_t *zip_fopen_encrypted(zip_t *za, const char *fname, zip_flags_t flags,
	const char *password)
{
	return IZip->zip_fopen_encrypted(za, fname, flags, password);
}

zip_file_t *zip_fopen_index(zip_t *za, zip_uint64_t index, zip_flags_t flags) {
	return IZip->zip_fopen_index(za, index, flags);
}

zip_file_t *zip_fopen_index_encrypted(zip_t *za, zip_uint64_t index, zip_flags_t flags,
	const char *password)
{
	return IZip->zip_fopen_index_encrypted(za, index, flags, password);
}

zip_int64_t zip_fread(zip_file_t *zf, void *outbuf, zip_uint64_t toread) {
	return IZip->zip_fread(zf, outbuf, toread);
}

const char *zip_get_archive_comment(zip_t *za, int *lenp, zip_flags_t flags) {
	return IZip->zip_get_archive_comment(za, lenp, flags);
}

int zip_get_archive_flag(zip_t *za, zip_flags_t flag, zip_flags_t flags) {
	return IZip->zip_get_archive_flag(za, flag, flags);
}

const char *zip_get_name(zip_t *za, zip_uint64_t idx, zip_flags_t flags) {
	return IZip->zip_get_name(za, idx, flags);
}

zip_int64_t zip_get_num_entries(zip_t *za, zip_flags_t flags) {
	return IZip->zip_get_num_entries(za, flags);
}

zip_int64_t zip_name_locate(zip_t *za, const char *fname, zip_flags_t flags) {
	return IZip->zip_name_locate(za, fname, flags);
}

zip_t *zip_open(const char *fn, int _flags, int *zep) {
	return IZip->zip_open(fn, _flags, zep);
}

int zip_set_archive_comment(zip_t *za, const char *comment, zip_uint16_t len) {
	return IZip->zip_set_archive_comment(za, comment, len);
}

int zip_set_archive_flag(zip_t *za, zip_flags_t flag, int value) {
	return IZip->zip_set_archive_flag(za, flag, value);
}

int zip_set_default_password(zip_t *za, const char *passwd) {
	return IZip->zip_set_default_password(za, passwd);
}

int zip_set_file_compression(zip_t *za, zip_uint64_t idx, zip_int32_t method, zip_uint32_t flags) {
	return IZip->zip_set_file_compression(za, idx, method, flags);
}

zip_source_t *zip_source_buffer(zip_t *za, const void *data, zip_uint64_t len, int freep) {
	return IZip->zip_source_buffer(za, data, len, freep);
}

zip_source_t *zip_source_file(zip_t *za, const char *fname, zip_uint64_t start, zip_int64_t len) {
	return IZip->zip_source_file(za, fname, start, len);
}

zip_source_t *zip_source_filep(zip_t *za, FILE *file, zip_uint64_t start, zip_int64_t len) {
	return IZip->zip_source_filep(za, file, start, len);
}

void zip_source_free(zip_source_t *src) {
	IZip->zip_source_free(src);
}

zip_source_t *zip_source_function(zip_t *za, zip_source_callback zcb, void *ud) {
	return IZip->zip_source_function(za, zcb, ud);
}

zip_source_t *zip_source_zip(zip_t *za, zip_t *srcza, zip_uint64_t srcidx, zip_flags_t flags,
	zip_uint64_t start, zip_int64_t len)
{
	return IZip->zip_source_zip(za, srcza, srcidx, flags, start, len);
}

int zip_stat(zip_t *za, const char *fname, zip_flags_t flags, zip_stat_t *st) {
	return IZip->zip_stat(za, fname, flags, st);
}

int zip_stat_index(zip_t *za, zip_uint64_t index, zip_flags_t flags, zip_stat_t *st) {
	return IZip->zip_stat_index(za, index, flags, st);
}

void zip_stat_init(zip_stat_t *st) {
	IZip->zip_stat_init(st);
}

const char *zip_strerror(zip_t *za) {
	return IZip->zip_strerror(za);
}

int zip_unchange(zip_t *za, zip_uint64_t idx) {
	return IZip->zip_unchange(za, idx);
}

int zip_unchange_all(zip_t *za) {
	return IZip->zip_unchange_all(za);
}

int zip_unchange_archive(zip_t *za) {
	return IZip->zip_unchange_archive(za);
}

/* Functions added in V53.5 */

zip_error_t *zip_get_error(zip_t *za) {
	return IZip->zip_get_error(za);
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

zip_t *zip_open_from_source(zip_source_t *zs, int flags, zip_error_t *ze) {
	return IZip->zip_open_from_source(zs, flags, ze);
}

int zip_file_set_encryption(zip_t *za, zip_uint64_t idx, zip_uint16_t method,
	const char *password)
{
	return IZip->zip_file_set_encryption(za, idx, method, password);
}

/* Functions added in V53.6 */

void zip_register_progress_callback(zip_t *za, zip_progress_callback_t cb) {
	IZip->zip_register_progress_callback(za, cb);
}

int zip_register_progress_callback_with_state(zip_t *za, double precision,
	zip_progress_callback cb, void (*ud_free)(void *), void *ud)
{
	return IZip->zip_register_progress_callback_with_state(za, precision, cb, ud_free, ud);
}

zip_error_t *zip_file_get_error(zip_file_t *zf) {
	return IZip->zip_file_get_error(zf);
}

int zip_file_set_mtime(zip_t *za, zip_uint64_t idx, time_t mtime, zip_flags_t flags) {
	return IZip->zip_file_set_mtime(za, idx, mtime, flags);
}

zip_int8_t zip_fseek(zip_file_t *zf, zip_int64_t offset, int whence) {
	return IZip->zip_fseek(zf, offset, whence);
}

zip_int64_t zip_ftell(zip_file_t *zf) {
	return IZip->zip_ftell(zf);
}

int zip_source_begin_write(zip_source_t *zs) {
	return IZip->zip_source_begin_write(zs);
}

zip_source_t *zip_source_buffer_create(const void *data, zip_uint64_t len, int freep, zip_error_t *error) {
	return IZip->zip_source_buffer_create(data, len, freep, error);
}

int zip_source_close(zip_source_t *zs) {
	return IZip->zip_source_close(zs);
}

int zip_source_commit_write(zip_source_t *zs) {
	return IZip->zip_source_commit_write(zs);
}

zip_error_t *zip_source_error(zip_source_t *zs) {
	return IZip->zip_source_error(zs);
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

int zip_source_is_deleted(zip_source_t *zs) {
	return IZip->zip_source_is_deleted(zs);
}

void zip_source_keep(zip_source_t *zs) {
	IZip->zip_source_keep(zs);
}

int zip_source_open(zip_source_t *zs) {
	return IZip->zip_source_open(zs);
}

zip_int64_t zip_source_read(zip_source_t *zs, void *data, zip_uint64_t len) {
	return IZip->zip_source_read(zs, data, len);
}

void zip_source_rollback_write(zip_source_t *zs) {
	IZip->zip_source_rollback_write(zs);
}

int zip_source_seek(zip_source_t *zs, zip_int64_t offset, int whence) {
	return IZip->zip_source_seek(zs, offset, whence);
}

zip_int64_t zip_source_seek_compute_offset(zip_uint64_t offset, zip_uint64_t length, void *data,
	zip_uint64_t data_length, zip_error_t *error)
{
	return IZip->zip_source_seek_compute_offset(offset, length, data, data_length, error);
}

int zip_source_seek_write(zip_source_t *zs, zip_int64_t offset, int whence) {
	return IZip->zip_source_seek_write(zs, offset, whence);
}

int zip_source_stat(zip_source_t *zs, zip_stat_t *zstat) {
	return IZip->zip_source_stat(zs, zstat);
}

zip_int64_t zip_source_tell(zip_source_t *zs) {
	return IZip->zip_source_tell(zs);
}

zip_int64_t zip_source_tell_write(zip_source_t *zs) {
	return IZip->zip_source_tell_write(zs);
}

zip_int64_t zip_source_write(zip_source_t *zs, const void *data, zip_uint64_t len) {
	return IZip->zip_source_write(zs, data, len);
}

