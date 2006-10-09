/********************************** Class Declaration ***************************/
/**
\package  AdkCtxi - 
\class    GlobalC

\brief    


\date     $Date: 2006/03/06 12:55:07,92 $
\dbsource adk.dev - ODABA Version 9.0
*/
/*************************************************************************************/
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
