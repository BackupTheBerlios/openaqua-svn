/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    gvts

\brief    Text String service functions


\date     $Date: 2006/07/12 12:48:32,32 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   gvts_H
#define   gvts_H

#include "csosdll.h"
#define  STRToPosition                             gvtsswt

#if defined (__cplusplus)
  extern "C" {
#endif

SOSImpExp          char *__cdecl CompleteExpression (char *expression );
SOSImpExp          logical __cdecl ContainsText (char *string, char *reg_string, int32 max_len, logical case_opt );
SOSImpExp          char *__cdecl GetExpressionBegin (char *startpos, int int_len );
SOSImpExp          char *__cdecl GetExpressionEnd (char *startpos, int int_len, logical ignore_last );
SOSImpExp          char *__cdecl GetKeyParm (char *string, char *keyword, logical compress_opt, logical ignore_last );
SOSImpExp          char *__cdecl GetParmKey (char *string, char **keyword_ptr, logical compress_opt, logical ignore_last );
SOSImpExp          int32 __cdecl GetParmPos (char *string, char *parm_string, char separator, logical compress_opt );
SOSImpExp          char *__cdecl GetParmString (char *string, int argc, char *argv[] );
SOSImpExp          char *__cdecl GetPosParm (char *string, int32 parm_no, char separator, logical compress_opt );
SOSImpExp          int32 __cdecl GetSearchStringCount (char *string, char *search_string );
                   ParenthethisDefinition *__cdecl GetStartChar (char stop_char );
                   ParenthethisDefinition *__cdecl GetStopChar (char start_char );
SOSImpExp          char *__cdecl GetStringValue (char *result_string, char *source_string );
SOSImpExp          char *__cdecl GrtPropertyParms (char *string );
                   char *__cdecl InsertCharBefore (char *string, char new_char, char search_char, int32 maxlen );
SOSImpExp          logical __cdecl IsValid (char *buffer, int int_len, char *string );
SOSImpExp          char *__cdecl NextProperty (char *string, char **expr_pos );
SOSImpExp          char *__cdecl PrevProperty (char *string, char **expr_pos, size_t len );
SOSImpExp          char *__cdecl ReplaceControlSequences (char *string, int32 lmaxlens, logical duplicate );
SOSImpExp          int __cdecl STRCompare (char *string1, char *string2 );
SOSImpExp          logical __cdecl STRContainsAlpha (char *string );
SOSImpExp          char *__cdecl STRExchange (char *string, char *ostring, char *nstring, int32 lmaxlens );
SOSImpExp          char *__cdecl STRGetToken (char *string, char sepchar );
SOSImpExp          int32 __cdecl STRReplaceCharacter (char *string, char ichar, char ochar );
SOSImpExp          char *__cdecl STRSearchChar (char *string, char searchChar, logical tail );
SOSImpExp          int32 __cdecl STRToPosition (char *string, int16 strcnt, char **strarea_ptr );
SOSImpExp          char *__cdecl gvtsapb (char *string, int int_len );
SOSImpExp          char *__cdecl gvtsbls (char *string, int16 remain, char *buffer, int int_len );
SOSImpExp          char *__cdecl gvtscat (char *targ_string, int32 maxlen, char *string1, char *string2, char *string3 );
SOSImpExp          char *__cdecl gvtscct (char *string, char sign );
SOSImpExp          char *__cdecl gvtschs (char *string, char sepchar, char *buffer, int int_len );
SOSImpExp          char *__cdecl gvtscin (char *string, char ichar, int16 num, int32 lmaxlens );
SOSImpExp          char *__cdecl gvtsexc (char *string, char *ostring, char *nstring, int32 lmaxlens );
SOSImpExp          char *__cdecl gvtsexi (char *string, char *ostring, char *nstring, int32 lmaxlens );
SOSImpExp          char *__cdecl gvtsexx (char *string, char *ostring, char *nstring, int32 lmaxlens, char *( __far __cdecl *cf)(char*,char*) );
SOSImpExp          char *__cdecl gvtsfac (char *astrn, char *vstrn, char *nstrn );
SOSImpExp          char *__cdecl gvtsfbp (char *startpos, int int_len );
SOSImpExp          char *__cdecl gvtsfbpb (char *startpos, int int_len );
SOSImpExp          int __cdecl gvtsicmp (char *string1, char *string2, int32 maxlen_w );
SOSImpExp          char *__cdecl gvtsiscn (char *string, char *ostring );
SOSImpExp          char *__cdecl gvtslwr (char *string );
SOSImpExp          logical __cdecl gvtsnck (char *string );
SOSImpExp          int __cdecl gvtsnicmp (char *string1, char *string2, int int_len );
SOSImpExp          char *__cdecl gvtsopg (char *string, int *int_len_ptr );
SOSImpExp          char *__cdecl gvtsscn (char *string, char *ostring );
SOSImpExp          char *__cdecl gvtssdl (char *string, int16 dcount );
SOSImpExp          char *__cdecl gvtssin (char *string, char *istring, int32 maxlen );
SOSImpExp          char *__cdecl gvtssrt (char *string, int int_len );
SOSImpExp          char *__cdecl gvtsupr (char *string );

#if defined (__cplusplus)
             }
#endif
#endif
