/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    CSUtilityHandle

\brief    


\date     $Date: 2006/03/12 19:09:48,71 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSUtilityHandle_HPP
#define   CSUtilityHandle_HPP

class     CSUtilityHandle;

#include  <cApplicationTypes.h>
#include  <sDBObjectHandle.hpp>
#include  <sODABAClient.hpp>
#include  <sPropertyHandle.hpp>
#include  <sUtilityHandle.hpp>
#pragma pack(8)

class  CSUtilityHandle :public UtilityHandle
{

public     :
public     :         OPI7ImpExp                                          CSUtilityHandle (ODABAClient &odaba_client, char *utiname, char *inipath, char *utititle, char *progpath=NULL, ApplicationTypes application_type=APT_Console );
public     :         OPI7ImpExp                                          CSUtilityHandle (ODABAClient &odaba_client, char *utiname, char *inipath, char *progpath=NULL, ApplicationTypes application_type=APT_Console );
public     :         OPI7ImpExp                  logical Copy ( );
public     :                                     logical CopyAllObjects (DBObjectHandle &srce_object, DBObjectHandle &targ_object );
public     :         OPI7ImpExp                  logical CopyCollection (PropertyHandle &coll_pi );
public     :         OPI7ImpExp                  logical CopyDB ( );
public     :         OPI7ImpExp                  logical CopyInstances (char *targ_ext, char *srce_ext );
public     :                                     logical CopyObject ( );
public     :         OPI7ImpExp                  logical CopyResDB (UtilityHandle *sdbuold );
public     :         OPI7ImpExp                  logical Licence ( );
public     :         OPI7ImpExp                  logical RecreateExtent ( );
public     :         OPI7ImpExp                  logical VersionSetup (uint16 version );
public     :         OPI7ImpExp                                          ~CSUtilityHandle ( );
};

#pragma pack()
#endif
