/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    gvtu

\brief    


\date     $Date: 2006/03/12 19:20:47,04 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   gvtu_H
#define   gvtu_H


#if defined (__cplusplus)
  extern "C" {
#endif

SOS7ImpExp         logical __cdecl gvtucat (char *targbuf, int32 targmlen, char *srcebuf, int32 srcemlen );
SOS7ImpExp         char *__cdecl gvtucin (char *buffer, int int_len, int16 num );
SOS7ImpExp         logical __cdecl gvtufck (char *buffer, int int_len );
SOS7ImpExp         char *__cdecl gvtultu (char *buffer, int int_len );
SOS7ImpExp         int32 __cdecl gvtussr (char *buffer, char *string, int32 maxlen );
SOS7ImpExp         char *__cdecl gvtutcp (char *buffer, int int_len );
SOS7ImpExp         char *__cdecl gvtutlb (char *buffer, int int_len );
SOS7ImpExp         char *__cdecl gvtutlc (char *buffer, int int_len );
SOS7ImpExp         int __cdecl gvtutle (char *buffer, int int_len );
SOS7ImpExp         int __cdecl gvtutle0 (char *buffer, int int_len );
SOS7ImpExp         int16 __cdecl gvtutwc (char *buffer, int int_len );
SOS7ImpExp         char *__cdecl gvtuutl (char *buffer, int int_len );
SOS7ImpExp         int16 __cdecl gvtuwfd (char *buffer, int int_len, char sepchar );

#if defined (__cplusplus)
             }
#endif
#endif
