/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    fmi



\date     $Date: 2006/05/10 20:15:04,29 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   fmi_H
#define   fmi_H

#include  <cProgramLanguage.h>
#include  <sDatabaseHandle.hpp>
#include  <sNString.hpp>

#if defined (__cplusplus)
  extern "C" {
#endif

                   char *__cdecl ProgramLanguageExtension (NString &nstring, DatabaseHandle &dbhandle, ProgramLanguage plang );

#if defined (__cplusplus)
             }
#endif
#endif
