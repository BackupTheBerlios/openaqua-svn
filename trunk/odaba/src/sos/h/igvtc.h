/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    gvtc



\date     $Date: 2006/03/12 19:20:44,93 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   gvtc_H
#define   gvtc_H


#if defined (__cplusplus)
  extern "C" {
#endif

SOS7ImpExp         logical __cdecl Pack (void *dest_buffer, size_t *pdest_size, void *source_buffer, size_t source_size, int level_AUTO );
SOS7ImpExp         logical __cdecl Unpack (void *dest_buffer, size_t *pdest_size, void *source_buffer, size_t source_size );

#if defined (__cplusplus)
             }
#endif
#endif
