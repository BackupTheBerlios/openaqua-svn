/********************************* Class Declaration ***************************/
/**
\package  VGKbase - 
\class    vgkbi

\brief    


\date     $Date: 2006/07/21 12:13:15,25 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   vgkbi_H
#define   vgkbi_H


#if defined (__cplusplus)
  extern "C" {
#endif

                   double __cdecl BauPreisIndex ( );
                   char *__cdecl GetEigentuemerKennung ( );
                   char *__cdecl GetImportFolder (NString &nstring, DatabaseHandle &dbhandle, char *sub_folder );
                   char *__cdecl GetSparteFromType (PropertyHandle *prophdl );

#if defined (__cplusplus)
             }
#endif
#endif
