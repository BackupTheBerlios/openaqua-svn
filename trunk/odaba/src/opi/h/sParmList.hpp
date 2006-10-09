/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ParmList

\brief    


\date     $Date: 2006/03/12 19:10:03,10 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ParmList_HPP
#define   ParmList_HPP

class     ParmList;

#ifndef   DPA_PropertyHandle_HPP
#define   DPA_PropertyHandle_HPP
#include  <sPropertyHandle.hpp>
#include  <sDPA.h>
#endif
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  ParmList :public DPA(PropertyHandle)
{
protected  :         logical                                      owner ATTR_ALIGN(4);                                       //

public     :
public     :         OPI7ImpExp                  logical AddParm (PropertyHandle *prophdl_ptr );
public     :         OPI7ImpExp                  logical AddParm (PropertyHandle &prophdl, char *parmstr );
public     :         OPI7ImpExp                  void ClearList ( );
public     :         OPI7ImpExp                  logical Compare (ParmList *parameters, logical convert );
public     :         OPI7ImpExp                  logical Copy (ParmList *parameters, logical field_copy );
public     :         OPI7ImpExp                  logical Copy (ParmList *parameters );
public     :                                     PropertyHandle *Get (char *varnames );
public     :                                     PropertyHandle *Get (PropertyHandle &prophdl );
public     :         OPI7ImpExp                                          ParmList (logical owning=YES );
public     :         OPI7ImpExp                                          ParmList (PropertyHandle &prophdl, char **parm_list );
public     :         OPI7ImpExp                                          ParmList (ParmList &plist_ref );
public     :         OPI7ImpExp                                          ParmList (char *parm_string, char *separators );
public     :         OPI7ImpExp                  logical operator= (ParmList &plist_ref );
public     :         OPI7ImpExp                                          ~ParmList ( );
};

#pragma pack()
#endif
