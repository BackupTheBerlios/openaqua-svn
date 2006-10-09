/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cStructMemberList

\brief    


\date     $Date: 2006/06/01 17:11:20,25 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cStructMemberList"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <scStructMemberList.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cStructMemberList :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cStructMemberList();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoAfterInsertData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterInsertData"

int8 cStructMemberList :: DoAfterInsertData ( )
{
  PropertyHandle    *prophdl   = GetCurrentPropertyHandle();
  PropertyHandle    *type      = prophdl->GPH("ddetype");
  PropertyHandle    *type_name = NULL;
  logical            ask       = YES;
  char               executed  = NO;
BEGINSEQ
  if ( !UserState1() )                               LEAVESEQ
  SetUserState1(NO);

  PropertyHandle  seltype(GetRESDictionary(),"FORM_select_SDB_Type");
                                                     P_SDBCERR
  type_name  = seltype.GPH("type_name");
  *type_name = *type;
    
  if ( !prophdl->IsA("SDB_Attribute")  &&
       !prophdl->IsA("SDB_BaseStruct")    )
  {
    if ( type_name->IsEmpty() && prophdl->IsA("SDB_Reference") )
      *type_name = "MEMO";
    do
    {
      if ( ExecuteWindow(&seltype,"FORM_select_SDB_Type","Edit",NO) )
                                                     LEAVESEQ
    } while ( type_name->IsEmpty() );
    
    ask = NO;
  }
  
  SetDefaults(prophdl,type_name->GetString());

  if ( !ask )                                        LEAVESEQ
    
  while ( type->IsEmpty() )
  {
    if ( ExecuteWindow(&seltype,"FORM_select_SDB_Type","Edit",NO) )
                                                     LEAVESEQ
    *type = *type_name;
    prophdl->Save();
  }
RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  DoBeforeInsertData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeInsertData"

int8 cStructMemberList :: DoBeforeInsertData ( )
{
  PropertyHandle    *init_ph   = GetInitPropertyHandle();
  PropertyHandle    *new_ident = init_ph->GPH("sys_ident");
  PropertyHandle    *prophdl   = GetCurrentPropertyHandle();
  PropertyHandle    *members   = prophdl->GetParentProperty()->GPH("members");
  char               executed  = NO;
BEGINSEQ
  if ( new_ident->IsEmpty() )                        ERROR
  if ( !strcmp(prophdl->GetType(),"SDB_Member") )    ERROR
  
  SetUserState1(!members->Get(*new_ident) ? YES : NO);
RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return  - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical cStructMemberList :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("SetDefaults",ALINK(this,cStructMemberList,SetDefaults)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = cSDBResource_Base::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDefaults - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaults"

logical cStructMemberList :: SetDefaults ( )
{
  PropertyHandle    *prophdl = GetCurrentPropertyHandle();
  PropertyHandle    *type    = prophdl->GPH("ddetype");
  logical            term    = NO;
BEGINSEQ
  if ( prophdl->NoWrite() )                          ERROR

  if ( SetDefaults(prophdl,type->GetString()) )      ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  prophdl - Property handle
\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaults"

logical cStructMemberList :: SetDefaults (PropertyHandle *prophdl, char *typenames )
{

  return ( prophdl->ExecuteInstanceAction("SetDefaults",typenames) );


}

/******************************************************************************/
/**
\brief  cStructMemberList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cStructMemberList"

     cStructMemberList :: cStructMemberList ( )
                     : cSDBResource_Base ()
{



}

/******************************************************************************/
/**
\brief  ~cStructMemberList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cStructMemberList"

     cStructMemberList :: ~cStructMemberList ( )
{



}


