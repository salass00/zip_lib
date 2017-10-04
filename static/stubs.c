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

int zip_archive_set_tempdir(struct zip *za, const char *tempdir) {
	return IZip->zip_archive_set_tempdir(za, tempdir);
}

int zip_close(struct zip *za) {
	return IZip->zip_close(za);
}

int zip_delete(struct zip *za, zip_uint64_t idx) {
	return IZip->zip_delete(za, idx);
}

zip_int64_t zip_dir_add(struct zip *za, const char *name, zip_flags_t flags) {
	return IZip->zip_dir_add(za, name, flags);
}

void zip_discard(struct zip *za) {
	IZip->zip_discard(za);
}

void zip_error_clear(struct zip *za) {
	IZip->zip_error_clear(za);
}

void zip_error_get(struct zip *za, int *zep, int *sep) {
	IZip->zip_error_get(za, zep, sep);
}

int zip_error_get_sys_type(int ze) {
	return IZip->zip_error_get_sys_type(ze);
}

int zip_error_to_str(char *buf, zip_uint64_t len, int ze, int se) {
	return IZip->zip_error_to_str(buf, len, ze, se);
}

int zip_fclose(struct zip_file *zf) {
	return IZip->zip_fclose(zf);
}

struct zip *zip_fdopen(int fd_orig, int _flags, int *zep) {
	return IZip->zip_fdopen(fd_orig, _flags, zep);
}

zip_int64_t zip_file_add(struct zip *za, const char *name, struct zip_source *source,
	zip_flags_t flags)
{
	return IZip->zip_file_add(za, name, source, flags);
}

void zip_file_error_clear(struct zip_file *zf) {
	IZip->zip_file_error_clear(zf);
}

void zip_file_error_get(struct zip_file *zf, int *zep, int *sep) {
	IZip->zip_file_error_get(zf, zep, sep);
}

int zip_file_extra_field_delete(struct zip *za, zip_uint64_t idx, zip_uint16_t ef_idx,
	zip_flags_t flags)
{
	return IZip->zip_file_extra_field_delete(za, idx, ef_idx, flags);
}

int zip_file_extra_field_delete_by_id(struct zip *za, zip_uint64_t idx, zip_uint16_t ef_id,
	zip_uint16_t ef_idx, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_delete_by_id(za, idx, ef_id, ef_idx, flags);
}

int zip_file_extra_field_set(struct zip *za, zip_uint64_t idx, zip_uint16_t ef_id,
	zip_uint16_t ef_idx, const zip_uint8_t *data, zip_uint16_t len, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_set(za, idx, ef_id, ef_idx, data, len, flags);
}

zip_int16_t zip_file_extra_fields_count(struct zip *za, zip_uint64_t idx, zip_flags_t flags) {
	return IZip->zip_file_extra_fields_count(za, idx, flags);
}

zip_int16_t zip_file_extra_fields_count_by_id(struct zip *za, zip_uint64_t idx,
	zip_uint16_t ef_id, zip_flags_t flags)
{
	return IZip->zip_file_extra_fields_count_by_id(za, idx, ef_id, flags);
}

const zip_uint8_t *zip_file_extra_field_get(struct zip *za, zip_uint64_t idx,
	zip_uint16_t ef_idx, zip_uint16_t *idp, zip_uint16_t *lenp, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_get(za, idx, ef_idx, idp, lenp, flags);
}

const zip_uint8_t *zip_file_extra_field_get_by_id(struct zip *za, zip_uint64_t idx,
	zip_uint16_t ef_id, zip_uint16_t ef_idx, zip_uint16_t *lenp, zip_flags_t flags)
{
	return IZip->zip_file_extra_field_get_by_id(za, idx, ef_id, ef_idx, lenp, flags);
}

const char *zip_file_get_comment(struct zip *za, zip_uint64_t idx, zip_uint32_t *lenp,
	zip_flags_t flags)
{
	return IZip->zip_file_get_comment(za, idx, lenp, flags);
}

int zip_file_get_external_attributes(struct zip *za, zip_uint64_t idx, zip_flags_t flags,
	zip_uint8_t *opsys, zip_uint32_t *attributes)
{
	return IZip->zip_file_get_external_attributes(za, idx, flags, opsys, attributes);
}

int zip_file_rename(struct zip *za, zip_uint64_t idx, const char *name, zip_flags_t flags) {
	return IZip->zip_file_rename(za, idx, name, flags);
}

int zip_file_replace(struct zip *za, zip_uint64_t idx, struct zip_source *source, zip_flags_t flags) {
	return IZip->zip_file_replace(za, idx, source, flags);
}

int zip_file_set_comment(struct zip *za, zip_uint64_t idx, const char *comment, zip_uint16_t len,
	zip_flags_t flags)
{
	return IZip->zip_file_set_comment(za, idx, comment, len, flags);
}

int zip_file_set_external_attributes(struct zip *za, zip_uint64_t idx, zip_flags_t flags,
	zip_uint8_t opsys, zip_uint32_t attributes)
{
	return IZip->zip_file_set_external_attributes(za, idx, flags, opsys, attributes);
}

const char *zip_file_strerror(struct zip_file *zf) {
	return IZip->zip_file_strerror(zf);
}

struct zip_file *zip_fopen(struct zip *za, const char *fname, zip_flags_t flags) {
	return IZip->zip_fopen(za, fname, flags);
}

struct zip_file *zip_fopen_encrypted(struct zip *za, const char *fname, zip_flags_t flags,
	const char *password)
{
	return IZip->zip_fopen_encrypted(za, fname, flags, password);
}

struct zip_file *zip_fopen_index(struct zip *za, zip_uint64_t index, zip_flags_t flags) {
	return IZip->zip_fopen_index(za, index, flags);
}

struct zip_file *zip_fopen_index_encrypted(struct zip *za, zip_uint64_t index, zip_flags_t flags,
	const char *password)
{
	return IZip->zip_fopen_index_encrypted(za, index, flags, password);
}

zip_int64_t zip_fread(struct zip_file *zf, void *outbuf, zip_uint64_t toread) {
	return IZip->zip_fread(zf, outbuf, toread);
}

const char *zip_get_archive_comment(struct zip *za, int *lenp, zip_flags_t flags) {
	return IZip->zip_get_archive_comment(za, lenp, flags);
}

int zip_get_archive_flag(struct zip *za, zip_flags_t flag, zip_flags_t flags) {
	return IZip->zip_get_archive_flag(za, flag, flags);
}

const char *zip_get_name(struct zip *za, zip_uint64_t idx, zip_flags_t flags) {
	return IZip->zip_get_name(za, idx, flags);
}

zip_int64_t zip_get_num_entries(struct zip *za, zip_flags_t flags) {
	return IZip->zip_get_num_entries(za, flags);
}

zip_int64_t zip_name_locate(struct zip *za, const char *fname, zip_flags_t flags) {
	return IZip->zip_name_locate(za, fname, flags);
}

struct zip *zip_open(const char *fn, int _flags, int *zep) {
	return IZip->zip_open(fn, _flags, zep);
}

int zip_set_archive_comment(struct zip *za, const char *comment, zip_uint16_t len) {
	return IZip->zip_set_archive_comment(za, comment, len);
}

int zip_set_archive_flag(struct zip *za, zip_flags_t flag, int value) {
	return IZip->zip_set_archive_flag(za, flag, value);
}

int zip_set_default_password(struct zip *za, const char *passwd) {
	return IZip->zip_set_default_password(za, passwd);
}

int zip_set_file_compression(struct zip *za, zip_uint64_t idx, zip_int32_t method,
	zip_uint32_t flags)
{
	return IZip->zip_set_file_compression(za, idx, method, flags);
}

struct zip_source *zip_source_buffer(struct zip *za, const void *data, zip_uint64_t len,
	int freep)
{
	return IZip->zip_source_buffer(za, data, len, freep);
}

struct zip_source *zip_source_file(struct zip *za, const char *fname, zip_uint64_t start,
	zip_int64_t len)
{
	return IZip->zip_source_file(za, fname, start, len);
}

struct zip_source *zip_source_filep(struct zip *za, FILE *file, zip_uint64_t start,
	zip_int64_t len)
{
	return IZip->zip_source_filep(za, file, start, len);
}

void zip_source_free(struct zip_source *src) {
	IZip->zip_source_free(src);
}

struct zip_source *zip_source_function(struct zip *za, zip_source_callback zcb, void *ud) {
	return IZip->zip_source_function(za, zcb, ud);
}

struct zip_source *zip_source_zip(struct zip *za, struct zip *srcza, zip_uint64_t srcidx,
	zip_flags_t flags, zip_uint64_t start, zip_int64_t len)
{
	return IZip->zip_source_zip(za, srcza, srcidx, flags, start, len);
}

int zip_stat(struct zip *za, const char *fname, zip_flags_t flags, struct zip_stat *st) {
	return IZip->zip_stat(za, fname, flags, st);
}

int zip_stat_index(struct zip *za, zip_uint64_t index, zip_flags_t flags, struct zip_stat *st) {
	return IZip->zip_stat_index(za, index, flags, st);
}

void zip_stat_init(struct zip_stat *st) {
	IZip->zip_stat_init(st);
}

const char *zip_strerror(struct zip *za) {
	return IZip->zip_strerror(za);
}

int zip_unchange(struct zip *za, zip_uint64_t idx) {
	return IZip->zip_unchange(za, idx);
}

int zip_unchange_all(struct zip *za) {
	return IZip->zip_unchange_all(za);
}

int zip_unchange_archive(struct zip *za) {
	return IZip->zip_unchange_archive(za);
}

zip_error_t *zip_get_error(struct zip *za) {
	return IZip->zip_get_error(za);
}

int zip_error_code_zip(const struct zip_error *error) {
	return IZip->zip_error_code_zip(error);
}

int zip_error_code_system(const struct zip_error *error) {
	return IZip->zip_error_code_system(error);
}

void zip_error_fini(struct zip_error *error) {
	IZip->zip_error_fini(error);
}

void zip_error_init(struct zip_error *error) {
	IZip->zip_error_init(error);
}

void zip_error_init_with_code(struct zip_error *error, int ze) {
	IZip->zip_error_init_with_code(error, ze);
}

void zip_error_set(struct zip_error *error, int ze, int se) {
	IZip->zip_error_set(error, ze, se);
}

const char *zip_error_strerror(struct zip_error *error) {
	return IZip->zip_error_strerror(error);
}

int zip_error_system_type(const struct zip_error *error) {
	return IZip->zip_error_system_type(error);
}

zip_int64_t zip_error_to_data(const struct zip_error *error, void *data, zip_uint64_t length) {
	return IZip->zip_error_to_data(error, data, length);
}

struct zip *zip_open_from_source(struct zip_source *zs, int flags, struct zip_error *ze) {
	return IZip->zip_open_from_source(zs, flags, ze);
}


