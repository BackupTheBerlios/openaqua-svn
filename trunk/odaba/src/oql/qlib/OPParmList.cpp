/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPParmList

\brief    


\date     $Date: 2006/03/12 19:21:01,06 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OPParmList"

#include  <poql.h>
#include  <sOPBase.hpp>
#include  <sParmList.hpp>
#include  <sPropertyHandle.hpp>
#include  <sOPParmList.hpp>


/******************************************************************************/
/**
\brief  ClearList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearList"

void OPParmList :: ClearList ( )
{
  int16     parm_cnt;
  parm_cnt = GetSize();
  while ( parm_cnt-- )
    if ( owner )
    {
      delete (*this)[parm_cnt];
      (*this)[parm_cnt] = NULL;
    }
  Clear();

}

/******************************************************************************/
/**
\brief  CreateParmlist

\return plist

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateParmlist"

ParmList *OPParmList :: CreateParmlist ( )
{
  ParmList     *plist = new ParmList(NO);
BEGINSEQ
  if ( !SetupParmlist(plist) )                       ERROR

RECOVER
  delete plist;
  plist = NULL;
ENDSEQ
  return(plist);
}

/******************************************************************************/
/**
\brief  Get - 


\return op_node -
-------------------------------------------------------------------------------
\brief i0


\param  varnames -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

OPBase *OPParmList :: Get (char *varnames )
{
  OPBase                   *op_node = NULL;
  DBFieldDef               *fielddef;
  char                      vname[ID_SIZE];
  int32                     indx0 = 0;
  logical                   term = NO;
BEGINSEQ
  if ( !varnames || !*varnames )                     ERROR
  gvtxstb(vname,varnames,ID_SIZE);

  while ( op_node = GetAt(indx0++) )
    if ( fielddef = op_node->GetDescription() )
      if ( !memcmp(fielddef->fmcbname,vname,ID_SIZE) )
        break;
RECOVER
  op_node = NULL;
ENDSEQ
  return(op_node);
}

/******************************************************************************/
/**
\brief i01


\param  prophdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

OPBase *OPParmList :: Get (PropertyHandle &prophdl )
{
  OPBase                   *op_node = NULL;
  DBFieldDef               *fielddef;
  if ( fielddef = prophdl.GetDescription() )
    op_node = Get(fielddef->fmcbname);
  return(op_node);
}

/******************************************************************************/
/**
\brief  OPParmList - 



\param  owning -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OPParmList"

                        OPParmList :: OPParmList (logical owning )
                     : DPA(OPBase) (),
  owner(owning)
{



}

/******************************************************************************/
/**
\brief  SetupParmlist

\return plist

\param  plist
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupParmlist"

ParmList *OPParmList :: SetupParmlist (ParmList *plist )
{
  OPBase       *op_node  = NULL;
  logical       new_list = plist ? NO : YES;
  int32         indx0    = 0;
  if ( !plist )
    plist = new ParmList(NO);
  else
    plist->ClearList();
      
  while ( op_node = GetAt(indx0++) )
    plist->AddParm(op_node->GetValue());
  return(plist);
}

/******************************************************************************/
/**
\brief  ~OPParmList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OPParmList"

                        OPParmList :: ~OPParmList ( )
{
  int16     parm_cnt;
  if ( owner )
    ClearList();


}


