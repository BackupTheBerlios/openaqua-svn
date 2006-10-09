/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    gvtx

\brief    


\date     $Date: 2006/07/28 11:40:08,00 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   gvtx_H
#define   gvtx_H


#if defined (__cplusplus)
  extern "C" {
#endif

SOSImpExp          int __cdecl StringLength (char *buffer, int int_len );
SOSImpExp          uint8 *__cdecl gvtxaas (uint8 *ubuffer, int int_len );
SOSImpExp          uint8 *__cdecl gvtxans (uint8 *ubuffer, int int_len );
SOSImpExp          char *__cdecl gvtxasc (char *buffer, int int_len );
SOSImpExp          char *__cdecl gvtxath (char *targbuf, char *buffer, int int_len );
SOSImpExp          char *__cdecl gvtxbcs (char *string, char *buffer, int buflen, int16 maxlens );
SOSImpExp          char *__cdecl gvtxbtc (char *targarea, int32 tlen, char *srcearea, int32 slen );
SOSImpExp          char *__cdecl gvtxbtoa (int64 val64, char *buffer, uint32 radix );
SOSImpExp          char *__cdecl gvtxbtp (char *picbuf, int64 val64, int int_len );
SOSImpExp          char *__cdecl gvtxbts (char *string, const char *buffer_c, int int_len );
SOSImpExp          char *__cdecl gvtxbxor (char *buffer, int int_len );
SOSImpExp          char *__cdecl gvtxcode (char *buffer, int int_len );
SOSImpExp          char *__cdecl gvtxctb (char *targarea, int32 tlen, char *srcearea, int32 slen );
SOSImpExp          char *__cdecl gvtxctc (char *targarea, int32 tlen, char *srcearea, int32 slen );
SOSImpExp          char *__cdecl gvtxcth (char *buffer, uint8 ucharval );
SOSImpExp          char *__cdecl gvtxdecode (char *buffer, int int_len );
SOSImpExp          char *__cdecl gvtxgst (char *buffer, size_t len );
SOSImpExp          uint16 __cdecl gvtxhti (char *buffer );
SOSImpExp          uint32 __cdecl gvtxhtl (char *buffer );
SOSImpExp          int __cdecl gvtxhtn (uint8 ucharval );
SOSImpExp          char *__cdecl gvtxith (char *buffer, int16 intsval );
SOSImpExp          char *__cdecl gvtxitoa (int16 intsval, char *buffer, uint32 radix );
SOSImpExp          char *__cdecl gvtxitp (char *picbuf, int16 intsval, int int_len );
SOSImpExp          char *__cdecl gvtxlth (char *buffer, int32 intval );
SOSImpExp          char *__cdecl gvtxltoa (int32 intval, char *buffer, uint32 radix );
SOSImpExp          char *__cdecl gvtxltp (char *picbuf, int32 intval, int int_len );
SOSImpExp          char *__cdecl gvtxstb (char *buffer, const char *string_c, int int_len );
SOSImpExp          void __cdecl gvtxxtoa (int64 val64, char *buffer, uint32 radix );
SOSImpExp          char *__cdecl gvtxxtp (char *picbuf, char *string, int int_len );

#if defined (__cplusplus)
             }
#endif
#endif
