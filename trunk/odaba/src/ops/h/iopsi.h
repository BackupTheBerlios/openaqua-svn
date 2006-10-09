/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    opsi



\date     $Date: 2006/04/19 21:57:58,12 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   opsi_H
#define   opsi_H

class     ErrorProtocol;
class     PropertyHandle;
#include  <sNString.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

                   char *__cdecl SDBOutputMessage (NString &nstring, logical clear_opt, int errcode );
                   char *__cdecl SDBOutputMessageParm (NString &nstring, logical clear_opt, int errcode, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5, char *parm6 );
                   logical __cdecl SDBSetProperty (PropertyHandle *prophdl, char *propnames, char *string, ErrorProtocol *protocol, char *parm1, char *parm2 );

#if defined (__cplusplus)
             }
#endif
#endif
