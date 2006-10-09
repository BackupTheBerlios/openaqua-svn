/********************************* Class Source Code ***************************/
/**
\package  SOS
\class    SystemStates



\date     $Date: 2006/05/03 13:06:23,95 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SystemStates"

#include  <pdefault.h>
#include  <sSystemStates.hpp>


/******************************************************************************/
/**
\brief  CheckRequest

\return cond - Return value

\param  reqtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckRequest"

logical SystemStates :: CheckRequest (CTX_RequestTypes reqtype )
{

  return ( element_stati[reqtype] );


}

/******************************************************************************/
/**
\brief  DisableContext


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisableContext"

void SystemStates :: DisableContext ( )
{

  element_stati[RQ_Disabled] = YES;

}

/******************************************************************************/
/**
\brief  EnableContext


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EnableContext"

void SystemStates :: EnableContext ( )
{

  element_stati[RQ_Disabled] = NO;

}

/******************************************************************************/
/**
\brief  ResetRequest


\param  reqtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetRequest"

void SystemStates :: ResetRequest (CTX_RequestTypes reqtype )
{
  element_stati[reqtype] = NO;
}

/******************************************************************************/
/**
\brief  SetRequest


\param  reqtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRequest"

void SystemStates :: SetRequest (CTX_RequestTypes reqtype )
{
  element_stati[reqtype] = YES;
}


