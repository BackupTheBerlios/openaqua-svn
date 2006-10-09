/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    GlobalC



\date     $Date: 2006/03/12 19:35:23,21 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   GlobalC_H
#define   GlobalC_H

#include  <cProgramLanguage.h>
#include  <sDatabaseHandle.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

                   char *__cdecl ClassLanguageExt (DatabaseHandle &dbhandle, char *clsnames );
                   char *__cdecl PLLanguageExt (DatabaseHandle &dbhandle, ProgramLanguage plang );

#if defined (__cplusplus)
             }
#endif
#endif
