#ifndef PROTO_ZIP_H
#define PROTO_ZIP_H

/*
**	$Id$
**
**	Prototype/inline/pragma header file combo
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#ifndef LIBRARIES_ZIP_H
#include <libraries/zip.h>
#endif

/****************************************************************************/

#ifndef __NOLIBBASE__
 #ifndef __USE_BASETYPE__
  #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
   extern struct AmigaOS::Library * ZipBase;
  #else
   extern struct Library * ZipBase;
  #endif
 #else
  #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
   extern struct AmigaOS::ZipBase * ZipBase;
  #else
   extern struct ZipBase * ZipBase;
  #endif
 #endif /* __USE_BASETYPE__ */
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/zip.h>
 #ifdef __USE_INLINE__
  #include <inline4/zip.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_ZIP_PROTOS_H
  #define CLIB_ZIP_PROTOS_H 1
 #endif /* CLIB_ZIP_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  #if defined(__cplusplus) && defined(__USE_AMIGAOS_NAMESPACE__)
   extern struct AmigaOS::ZipIFace * IZip;
  #else
   extern struct ZipIFace * IZip;
  #endif
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_ZIP_PROTOS_H
  #include <clib/zip_protos.h>
 #endif /* CLIB_ZIP_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/zip.h>
  #else /* __PPC__ */
   #include <ppcinline/zip.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/zip_protos.h>
  #endif /* __PPC__ */
 #else /* __GNUC__ */
  #include <pragmas/zip_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_ZIP_H */
