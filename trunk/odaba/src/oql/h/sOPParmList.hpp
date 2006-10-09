/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPParmList

\brief    


\date     $Date: 2006/03/12 19:20:09,39 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPParmList_HPP
#define   OPParmList_HPP

class     OPParmList;

#ifndef   DPA_OPBase_HPP
#define   DPA_OPBase_HPP
#include  <sOPBase.hpp>
#include  <sDPA.h>
#endif
class     OPBase;
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  OPParmList :public DPA(OPBase)
{
protected  :         logical                                      owner ATTR_ALIGN(4);                                       //

public     :
                     logical                                      get_owner() { return(owner); }
public     :                                     void ClearList ( );
public     :                                     ParmList *CreateParmlist ( );
public     :                                     OPBase *Get (char *varnames );
public     :                                     OPBase *Get (PropertyHandle &prophdl );
public     :                                                             OPParmList (logical owning=YES );
public     :                                     ParmList *SetupParmlist (ParmList *plist );
public     :                                                             ~OPParmList ( );
};

#pragma pack()
#endif
