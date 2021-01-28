#ifndef HAD_CONFIG_H
#define HAD_CONFIG_H
#ifndef _HAD_ZIPCONF_H
#include "zipconf.h"
#endif
/* BEGIN DEFINES */
/* #undef HAVE___PROGNAME */
/* #undef HAVE__CLOSE */
/* #undef HAVE__DUP */
/* #undef HAVE__FDOPEN */
/* #undef HAVE__FILENO */
/* #undef HAVE__SETMODE */
/* #undef HAVE__SNPRINTF */
/* #undef HAVE__STRDUP */
/* #undef HAVE__STRICMP */
/* #undef HAVE__STRTOI64 */
/* #undef HAVE__STRTOUI64 */
/* #undef HAVE__UMASK */
/* #undef HAVE__UNLINK */
/* #undef HAVE_ARC4RANDOM */
/* #undef HAVE_CLONEFILE */
/* #undef HAVE_COMMONCRYPTO */
#define HAVE_CRYPTO 1
/* #undef HAVE_FICLONERANGE */
#define HAVE_FILENO 1
#define HAVE_FSEEKO 1
#define HAVE_FTELLO 1
/* #undef HAVE_GETPROGNAME */
/* #undef HAVE_GNUTLS */
#define HAVE_LIBBZ2 1
#define HAVE_LIBLZMA 1
#define HAVE_LOCALTIME_R 1
/* #undef HAVE_MBEDTLS */
#define HAVE_MKSTEMP 1
/* #undef HAVE_NULLABLE */
#define HAVE_OPENSSL 1
/* #undef HAVE_SETMODE */
#define HAVE_SNPRINTF 1
#define HAVE_STRCASECMP 1
#define HAVE_STRDUP 1
#define HAVE_STRICMP 1
#define HAVE_STRTOLL 1
#define HAVE_STRTOULL 1
#define HAVE_STRUCT_TM_TM_ZONE 1
/* #undef HAVE_STDBOOL_H */
#define HAVE_STRINGS_H 1
#define HAVE_UNISTD_H 1
/* #undef HAVE_WINDOWS_CRYPTO */
#define SIZEOF_OFF_T 4
#define SIZEOF_SIZE_T 4
#define HAVE_DIRENT_H 1
/* #undef HAVE_FTS_H */
/* #undef HAVE_NDIR_H */
/* #undef HAVE_SYS_DIR_H */
/* #undef HAVE_SYS_NDIR_H */
#define WORDS_BIGENDIAN 1
/* #undef HAVE_SHARED */
/* END DEFINES */
#define PACKAGE "libzip"
#define VERSION "1.7.3"

#endif /* HAD_CONFIG_H */
