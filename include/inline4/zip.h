#ifndef INLINE4_ZIP_H
#define INLINE4_ZIP_H

/*
** This file was auto generated by idltool 53.25.
**
** It provides compatibility to OS3 style library
** calls by substituting functions.
**
** Do not edit manually.
*/ 

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
#include <interfaces/zip.h>

/* Inline macros for Interface "main" */
#define zip_archive_set_tempdir(archive, tempdir) IZip->zip_archive_set_tempdir((archive), (tempdir))
#define zip_close(archive) IZip->zip_close((archive))
#define zip_delete(archive, idx) IZip->zip_delete((archive), (idx))
#define zip_dir_add(archive, name, flags) IZip->zip_dir_add((archive), (name), (flags))
#define zip_discard(archive) IZip->zip_discard((archive))
#define zip_error_clear(archive) IZip->zip_error_clear((archive))
#define zip_error_get(archive, zep, sep) IZip->zip_error_get((archive), (zep), (sep))
#define zip_error_get_sys_type(ze) IZip->zip_error_get_sys_type((ze))
#define zip_error_to_str(buf, len, ze, se) IZip->zip_error_to_str((buf), (len), (ze), (se))
#define zip_fclose(file) IZip->zip_fclose((file))
#define zip_fdopen(fd, flags, errorp) IZip->zip_fdopen((fd), (flags), (errorp))
#define zip_file_add(archive, name, source, flags) IZip->zip_file_add((archive), (name), (source), (flags))
#define zip_file_error_clear(file) IZip->zip_file_error_clear((file))
#define zip_file_error_get(file, zep, sep) IZip->zip_file_error_get((file), (zep), (sep))
#define zip_file_extra_field_delete(archive, idx, ef_idx, flags) IZip->zip_file_extra_field_delete((archive), (idx), (ef_idx), (flags))
#define zip_file_extra_field_delete_by_id(archive, idx, ef_id, ef_idx, flags) IZip->zip_file_extra_field_delete_by_id((archive), (idx), (ef_id), (ef_idx), (flags))
#define zip_file_extra_field_set(archive, idx, ef_id, ef_idx, data, len, flags) IZip->zip_file_extra_field_set((archive), (idx), (ef_id), (ef_idx), (data), (len), (flags))
#define zip_file_extra_fields_count(archive, idx, flags) IZip->zip_file_extra_fields_count((archive), (idx), (flags))
#define zip_file_extra_fields_count_by_id(archive, idx, ef_id, flags) IZip->zip_file_extra_fields_count_by_id((archive), (idx), (ef_id), (flags))
#define zip_file_extra_field_get(archive, idx, ef_idx, idp, lenp, flags) IZip->zip_file_extra_field_get((archive), (idx), (ef_idx), (idp), (lenp), (flags))
#define zip_file_extra_field_get_by_id(archive, idx, ef_id, ef_idx, lenp, flags) IZip->zip_file_extra_field_get_by_id((archive), (idx), (ef_id), (ef_idx), (lenp), (flags))
#define zip_file_get_comment(archive, idx, lenp, flags) IZip->zip_file_get_comment((archive), (idx), (lenp), (flags))
#define zip_file_get_external_attributes(archive, idx, flags, opsys, attributes) IZip->zip_file_get_external_attributes((archive), (idx), (flags), (opsys), (attributes))
#define zip_file_rename(archive, idx, name, flags) IZip->zip_file_rename((archive), (idx), (name), (flags))
#define zip_file_replace(archive, idx, source, flags) IZip->zip_file_replace((archive), (idx), (source), (flags))
#define zip_file_set_comment(archive, idx, comment, len, flags) IZip->zip_file_set_comment((archive), (idx), (comment), (len), (flags))
#define zip_file_set_external_attributes(archive, idx, flags, opsys, attributes) IZip->zip_file_set_external_attributes((archive), (idx), (flags), (opsys), (attributes))
#define zip_file_strerror(file) IZip->zip_file_strerror((file))
#define zip_fopen(archive, fname, flags) IZip->zip_fopen((archive), (fname), (flags))
#define zip_fopen_encrypted(archive, fname, flags, password) IZip->zip_fopen_encrypted((archive), (fname), (flags), (password))
#define zip_fopen_index(archive, index, flags) IZip->zip_fopen_index((archive), (index), (flags))
#define zip_fopen_index_encrypted(archive, index, flags, password) IZip->zip_fopen_index_encrypted((archive), (index), (flags), (password))
#define zip_fread(file, outbuf, toread) IZip->zip_fread((file), (outbuf), (toread))
#define zip_get_archive_comment(archive, lenp, flags) IZip->zip_get_archive_comment((archive), (lenp), (flags))
#define zip_get_archive_flag(archive, flag, flags) IZip->zip_get_archive_flag((archive), (flag), (flags))
#define zip_get_name(archive, idx, flags) IZip->zip_get_name((archive), (idx), (flags))
#define zip_get_num_entries(archive, flags) IZip->zip_get_num_entries((archive), (flags))
#define zip_name_locate(archive, fname, flags) IZip->zip_name_locate((archive), (fname), (flags))
#define zip_open(path, flags, errorp) IZip->zip_open((path), (flags), (errorp))
#define zip_set_archive_comment(archive, comment, len) IZip->zip_set_archive_comment((archive), (comment), (len))
#define zip_set_archive_flag(archive, flag, value) IZip->zip_set_archive_flag((archive), (flag), (value))
#define zip_set_default_password(archive, passwd) IZip->zip_set_default_password((archive), (passwd))
#define zip_set_file_compression(archive, idx, method, flags) IZip->zip_set_file_compression((archive), (idx), (method), (flags))
#define zip_source_buffer(archive, data, len, freep) IZip->zip_source_buffer((archive), (data), (len), (freep))
#define zip_source_file(archive, fname, start, len) IZip->zip_source_file((archive), (fname), (start), (len))
#define zip_source_filep(archive, file, start, len) IZip->zip_source_filep((archive), (file), (start), (len))
#define zip_source_free(src) IZip->zip_source_free((src))
#define zip_source_function(archive, zcb, ud) IZip->zip_source_function((archive), (zcb), (ud))
#define zip_source_zip(archive, srcza, srcidx, flags, start, len) IZip->zip_source_zip((archive), (srcza), (srcidx), (flags), (start), (len))
#define zip_stat(archive, fname, flags, st) IZip->zip_stat((archive), (fname), (flags), (st))
#define zip_stat_index(archive, index, flags, st) IZip->zip_stat_index((archive), (index), (flags), (st))
#define zip_stat_init(st) IZip->zip_stat_init((st))
#define zip_strerror(archive) IZip->zip_strerror((archive))
#define zip_unchange(archive, idx) IZip->zip_unchange((archive), (idx))
#define zip_unchange_all(archive) IZip->zip_unchange_all((archive))
#define zip_unchange_archive(archive) IZip->zip_unchange_archive((archive))
#define zip_get_error(archive) IZip->zip_get_error((archive))
#define zip_error_code_zip(error) IZip->zip_error_code_zip((error))
#define zip_error_code_system(error) IZip->zip_error_code_system((error))
#define zip_error_fini(error) IZip->zip_error_fini((error))
#define zip_error_init(error) IZip->zip_error_init((error))
#define zip_error_init_with_code(error, ze) IZip->zip_error_init_with_code((error), (ze))
#define zip_error_set(error, ze, se) IZip->zip_error_set((error), (ze), (se))
#define zip_error_strerror(error) IZip->zip_error_strerror((error))
#define zip_error_system_type(error) IZip->zip_error_system_type((error))
#define zip_error_to_data(error, data, length) IZip->zip_error_to_data((error), (data), (length))
#define zip_open_from_source(source, flags, ze) IZip->zip_open_from_source((source), (flags), (ze))
#define zip_file_set_encryption(archive, idx, method, password) IZip->zip_file_set_encryption((archive), (idx), (method), (password))
#define zip_register_progress_callback(archive, cb) IZip->zip_register_progress_callback((archive), (cb))
#define zip_register_progress_callback_with_state(archive, precision, cb, ud_free, ud) IZip->zip_register_progress_callback_with_state((archive), (precision), (cb), (ud_free), (ud))
#define zip_file_get_error(file) IZip->zip_file_get_error((file))
#define zip_file_set_mtime(archive, idx, mtime, flags) IZip->zip_file_set_mtime((archive), (idx), (mtime), (flags))
#define zip_fseek(file, offset, whence) IZip->zip_fseek((file), (offset), (whence))
#define zip_ftell(file) IZip->zip_ftell((file))
#define zip_source_begin_write(source) IZip->zip_source_begin_write((source))
#define zip_source_buffer_create(data, len, freep, error) IZip->zip_source_buffer_create((data), (len), (freep), (error))
#define zip_source_close(source) IZip->zip_source_close((source))
#define zip_source_commit_write(source) IZip->zip_source_commit_write((source))
#define zip_source_error(source) IZip->zip_source_error((source))
#define zip_source_file_create(fname, start, len, error) IZip->zip_source_file_create((fname), (start), (len), (error))
#define zip_source_filep_create(file, start, len, error) IZip->zip_source_filep_create((file), (start), (len), (error))
#define zip_source_function_create(fn, userdata, error) IZip->zip_source_function_create((fn), (userdata), (error))
#define zip_source_is_deleted(source) IZip->zip_source_is_deleted((source))
#define zip_source_keep(source) IZip->zip_source_keep((source))
#define zip_source_open(source) IZip->zip_source_open((source))
#define zip_source_read(source, data, len) IZip->zip_source_read((source), (data), (len))
#define zip_source_rollback_write(source) IZip->zip_source_rollback_write((source))
#define zip_source_seek(source, offset, whence) IZip->zip_source_seek((source), (offset), (whence))
#define zip_source_seek_compute_offset(offset, length, data, data_length, error) IZip->zip_source_seek_compute_offset((offset), (length), (data), (data_length), (error))
#define zip_source_seek_write(source, offset, whence) IZip->zip_source_seek_write((source), (offset), (whence))
#define zip_source_stat(source, zstat) IZip->zip_source_stat((source), (zstat))
#define zip_source_tell(source) IZip->zip_source_tell((source))
#define zip_source_tell_write(source) IZip->zip_source_tell_write((source))
#define zip_source_write(source, data, len) IZip->zip_source_write((source), (data), (len))
#define zip_libzip_version() IZip->zip_libzip_version()
#define zip_source_buffer_fragment(archive, frags, nfrags, freep) IZip->zip_source_buffer_fragment((archive), (frags), (nfrags), (freep))
#define zip_source_buffer_fragment_create(frags, nfrags, freep, error) IZip->zip_source_buffer_fragment_create((frags), (nfrags), (freep), (error))

#endif /* INLINE4_ZIP_H */
