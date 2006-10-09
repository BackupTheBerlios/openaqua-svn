/********************************* Class Source Code ***************************/
/**
\package  VGKbase - 
\class    pc_ActionStatus

\brief    


\date     $Date: 2006/07/21 13:08:50,90 $
\dbsource transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ActionStatus"

#include  <pVGKbase.h>
#include  <spc_ActionStatus.hpp>


/******************************************************************************/
/**
\brief  CheckStatus - 



\return errnum - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  state_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckStatus"

int32 pc_ActionStatus :: CheckStatus (char *state_string )
{
  DEFLOCALERR

BEGINSEQ
  PropertyHandle    states(GetDBHandle(),"ActionStatus",PI_Read);
                                                    LOCAL_SDBCERR
  states.SetOrder("sk_name");
  if ( !states.Get(PropertyHandle(state_string)) )  LOCALERR(18)
  
  if ( !Get(FIRST_INSTANCE) )
  {
    Add(states.ExtractKey());                       LOCAL_SDBCERR
    LEAVESEQ
  }

  if ( GetID() != states.GetID() )                  ERROR
RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckStatus"

int32 pc_ActionStatus :: CheckStatus (int32 id )
{
  logical   term = NO;
BEGINSEQ
  if ( !Get(FIRST_INSTANCE) )                       ERROR
  if ( GPH("extern_id")->GetInt() != id )           ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetStatus - 



\return errnum - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  state_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStatus"

int32 pc_ActionStatus :: SetStatus (char *state_string )
{
  DEFLOCALERR

BEGINSEQ
  PropertyHandle    states(GetDBHandle(),"ActionStatus",PI_Read);
                                                    LOCAL_SDBCERR
  states.SetOrder("sk_name");
  if ( !states.Get(PropertyHandle(state_string)) )  LOCALERR(18)
  
  Provide(states.ExtractKey());                     LOCAL_SDBCERR

RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStatus"

int32 pc_ActionStatus :: SetStatus (int32 id )
{
  DEFLOCALERR
BEGINSEQ
  Provide(Key((char *)&id));                        LOCAL_SDBCERR
RECOVER

ENDSEQ
  return(LOCALERROR);
}

/******************************************************************************/
/**
\brief  pc_ActionStatus - 




\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ActionStatus"

     pc_ActionStatus :: pc_ActionStatus (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


