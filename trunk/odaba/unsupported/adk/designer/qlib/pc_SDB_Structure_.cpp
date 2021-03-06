/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_SDB_Structure_

\brief    


\date     $Date: 2006/03/12 19:37:45,51 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_Structure_"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ODC_ImpClass.hpp>
#include  <spc_SDB_Structure_.hpp>


/******************************************************************************/
/**
\brief  CheckContextClass - 


\return

\param  base_context -
\param  prjnames -
\param  high_ctx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckContextClass"

logical pc_SDB_Structure_ :: CheckContextClass (char *base_context, char *prjnames, CTX_Control *high_ctx )
{
  PropertyHandle    *sys_ident = GPH("sys_ident");
  PropertyHandle    *smcebase  = GPH("smcebase");
  PropertyHandle    *ddetype   = smcebase->GPH("ddetype");
  PropertyHandle    *ddeprv    = smcebase->GPH("ddeprv");
  char               name[ID_SIZE];
  logical            term = NO;
BEGINSEQ
  if ( !base_context )                               LEAVESEQ
  if ( !Exist() || !Get(AUTO) )                      ERROR
  if ( !strcmp(sys_ident->GetString(),base_context)) LEAVESEQ
     
  if ( !smcebase->Get(FIRST_INSTANCE) )              ERROR
  if ( strcmp(ddetype->GetString(),base_context) )    
  {
    pc_ODC_ImpClass   impl(GetObjectHandle(),PI_Read);
                                                     P_SDBCERR
    if ( !impl.Get(*ddetype) )                       ERROR
    if ( impl.CheckContextClass(base_context,prjnames,high_ctx) )
                                                     ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitContextClass - 


\return term -
-------------------------------------------------------------------------------
\brief i00


\param  context_type -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitContextClass"

logical pc_SDB_Structure_ :: InitContextClass (CTX_Types context_type )
{
  char                   *clasname;
  logical                 term = NO;
BEGINSEQ
  if ( !Exist() )                                    ERROR
    
  switch ( context_type )
  {
    case  CTXT_Window      : 
    case  CTXT_Control     : clasname = "CTX_Control";
                             break;
    case  CTXT_Application : clasname = "CTX_Application";
                             break;
    case  CTXT_Project     : clasname = "CTX_Project";
                             break;
    case  CTXT_Document    : clasname = "CTX_Document";
                             break;
    case  CTXT_Property    : clasname = "CTX_Property";
                             break;
    case  CTXT_Structure   : clasname = "CTX_Structure";
                             break;
    case  CTXT_Object      : clasname = "CTX_Object";
                             break;
    case  CTXT_Database    : clasname = "CTX_Database";
                             break;
    default                : LEAVESEQ
  }
  
  term = InitContextClass(clasname);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i01


\param  base_context -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitContextClass"

logical pc_SDB_Structure_ :: InitContextClass (char *base_context )
{
  PropertyHandle    *checked  = GPH("checked");
  PropertyHandle    *ready    = GPH("ready");
  PropertyHandle    *smcebase = GPH("smcebase");
  PropertyHandle    *ddetype  = smcebase->GPH("ddetype");
  PropertyHandle    *ddeprv   = smcebase->GPH("ddeprv");
  char               name[ID_SIZE];
  logical            term = NO;
BEGINSEQ
  if ( NoWrite() )                                    ERROR
     
  if ( base_context )
  {
    smcebase->Add(Key(gvtxstb(name,base_context,sizeof(name))));
    *ddetype = base_context;
    *ddeprv  = "ODC_protected";
  }
  
  *checked = (logical)YES;
  *ready   = (logical)YES;

  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_Structure_ - Konstruktor


-------------------------------------------------------------------------------
\brief i0


\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Structure_"

                        pc_SDB_Structure_ :: pc_SDB_Structure_ (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{



}

/******************************************************************************/
/**
\brief i01


\param  obhandle -
\param  extnames -
\param  accopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_Structure_"

                        pc_SDB_Structure_ :: pc_SDB_Structure_ (DBObjectHandle &obhandle, char *extnames, PIACC accopt )
                     : PropertyHandle (obhandle,extnames,accopt)
{



}


