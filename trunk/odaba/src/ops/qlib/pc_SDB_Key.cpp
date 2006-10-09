/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    pc_SDB_Key



\date     $Date: 2006/05/11 13:41:24,89 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Key"

#include  <pops7.h>
#ifndef   DLL_kcb_HPP
#define   DLL_kcb_HPP
#include  <skcb.hpp>
#include  <sDLL.h>
#endif
#include  <sErrorProtocol.hpp>
#include  <skcb.hpp>
#include  <iopsi.h>
#include  <spc_SDB_KeyComponent.hpp>
#include  <spc_SDB_Key.hpp>


/******************************************************************************/
/**
\brief  Check

\return term

\param  protocol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical pc_SDB_Key :: Check (ErrorProtocol *protocol )
{
  PropertyHandle   *sys_ident = GPH("sys_ident");
  logical           term      = NO;
BEGINSEQ
  protocol->SetErrorVariable(2,sys_ident->GetString(),0);

  pc_SDB_KeyComponent  components(GPH("components"));
  
  if ( components.GetCount() < 1 && *sys_ident != "__IDENTITY" )
  {
    protocol->Write(197,0);
    ERROR
  }

  if ( components.CheckAll(protocol) )              ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckAll

\return term

\param  protocol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAll"

logical pc_SDB_Key :: CheckAll (ErrorProtocol *protocol )
{
  int32       indx0 = 0;
  logical     term  = NO;
  while ( Get(indx0++) )
    if ( Check(protocol) )
      term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  IsKeyComponent

\return cond - 

\param  fldnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsKeyComponent"

logical pc_SDB_Key :: IsKeyComponent (char *fldnames )
{
  pc_SDB_KeyComponent   components(GPH("components"));
  int32                 indx0 = 0;
  logical               cond  = NO;
  while ( !cond && Get(indx0++) )
    cond = components.IsKeyComponent(fldnames);
  return(cond);
}

/******************************************************************************/
/**
\brief  Store

\return term

\param  kcbptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical pc_SDB_Key :: Store (kcb *kcbptr )
{

  return ( pc_SDB_KeyComponent(GPH("components")).StoreAll(kcbptr->scbsmcb) );

}

/******************************************************************************/
/**
\brief  StoreAll

\return term

\param  keylist
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreAll"

logical pc_SDB_Key :: StoreAll (DLL(kcb) *keylist )
{
  kcb        *kcbptr = NULL;
  logical     term   = NO;
BEGINSEQ
  DeleteSet();
  keylist->GoTop();
  while ( kcbptr = keylist->GetNext() )
  {
    Add(Key(kcbptr->scbsmcb->smcbname));             SDBCERR
    if ( Store(kcbptr) )
      term = YES;
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_Key


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Key"

     pc_SDB_Key :: pc_SDB_Key (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{
}


