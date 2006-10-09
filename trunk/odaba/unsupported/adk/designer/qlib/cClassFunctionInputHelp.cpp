/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassFunctionInputHelp

\brief    


\date     $Date: 2006/06/21 16:46:53,82 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cClassFunctionInputHelp"

#include  <pdesign.h>
#include  <cODE_OBJECTTYPE.h>
#include  <scClassFunctionInputHelp.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cClassFunctionInputHelp :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cClassFunctionInputHelp();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterHandleOpen - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterHandleOpen"

int8 cClassFunctionInputHelp :: DoAfterHandleOpen ( )
{

  SetFilter(YES);
  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterShow - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterShow"

int8 cClassFunctionInputHelp :: DoAfterShow ( )
{

  return( cClassInputHelp::DoAfterShow() );

}

/******************************************************************************/
/**
\brief  DoBeforeDataSet - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeDataSet"

int8 cClassFunctionInputHelp :: DoBeforeDataSet ( )
{
  PropertyHandle  *prophdl  = GetPropertyHandle();
  PropertyHandle  *type     = prophdl->GPH("type");
  PropertyHandle  *source   = prophdl->GPH("source");
  PropertyHandle  *ident    = prophdl->GPH("ident");
  int8             executed = NO;
BEGINSEQ
  if ( !prophdl->Exist() )                           LEAVESEQ
    
  if ( (ODE_OBJECTTYPE)type->GetInt() != OT_Function )
                                                     ERROR
  if ( source->IsEmpty() )                           ERROR
  if ( *source == *ident )                           ERROR
RECOVER
  executed = YES;
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  cClassFunctionInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cClassFunctionInputHelp"

     cClassFunctionInputHelp :: cClassFunctionInputHelp ( )
                     : cClassInputHelp ()
{

  SetAsMyClass();

}

/******************************************************************************/
/**
\brief  ~cClassFunctionInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cClassFunctionInputHelp"

     cClassFunctionInputHelp :: ~cClassFunctionInputHelp ( )
{



}


