/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    CSA_Handle

\brief    


\date     $Date: 2006/03/12 19:21:22,15 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSA_Handle"

#include  <pdefault.h>
#include  <sCS_Connection.hpp>
#include  <sCS_Message.hpp>
#include  <sCSA_Handle.hpp>


/******************************************************************************/
/**
\brief  CSAClose


\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSAClose"

void CSA_Handle :: CSAClose (char *parmstring )
{



}

/******************************************************************************/
/**
\brief  CSAClosed


\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSAClosed"

void CSA_Handle :: CSAClosed (char *parmstring )
{



}

/******************************************************************************/
/**
\brief  CSACommand


\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSACommand"

void CSA_Handle :: CSACommand (char *parmstring )
{



}

/******************************************************************************/
/**
\brief  CSACreate


\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSACreate"

void CSA_Handle :: CSACreate (char *parmstring )
{



}

/******************************************************************************/
/**
\brief  CSADelete


\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSADelete"

void CSA_Handle :: CSADelete (char *parmstring )
{



}

/******************************************************************************/
/**
\brief  CSADirty


\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSADirty"

void CSA_Handle :: CSADirty (char *parmstring )
{



}

/******************************************************************************/
/**
\brief  CSAInsert


\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSAInsert"

void CSA_Handle :: CSAInsert (char *parmstring )
{



}

/******************************************************************************/
/**
\brief  CSAOpen


\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSAOpen"

void CSA_Handle :: CSAOpen (char *parmstring )
{



}

/******************************************************************************/
/**
\brief  CSAOpened


\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSAOpened"

void CSA_Handle :: CSAOpened (char *parmstring )
{



}

/******************************************************************************/
/**
\brief  CSARemove


\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSARemove"

void CSA_Handle :: CSARemove (char *parmstring )
{



}

/******************************************************************************/
/**
\brief  CSAUpdate


\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSAUpdate"

void CSA_Handle :: CSAUpdate (char *parmstring )
{



}

/******************************************************************************/
/**
\brief  CSA_Handle

-------------------------------------------------------------------------------
\brief i0


\param  cs_connection -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSA_Handle"

                        CSA_Handle :: CSA_Handle (CS_Connection *cs_connection )
                     : CS_Handle (),
  csconnection(cs_connection)
{



}

/******************************************************************************/
/**
\brief i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSA_Handle"

                        CSA_Handle :: CSA_Handle ( )
                     : CS_Handle (),
  csconnection(NULL)
{



}

/******************************************************************************/
/**
\brief  ExecuteEvent

\return term - Success

\param  dwServiceFunc -
\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteEvent"

logical CSA_Handle :: ExecuteEvent (uint32 dwServiceFunc, char *parmstring )
{
  logical                 term = NO;
BEGINSEQ
  switch ( dwServiceFunc )
  {
    case CSA_undefined : ERROR 
                         break;
    case SE_Open       : 
    case CE_Open       : CSAOpen(parmstring);
                         break;
    case SE_Opened     : 
    case CE_Opened     : CSAOpened(parmstring);
                         break;
    case SE_Create     : 
    case CE_Create     : CSACreate(parmstring);
                         break;
    case SE_Update     : 
    case CE_Update     : CSAUpdate(parmstring);
                         break;
    case SE_Insert    : 
    case CE_Insert    :  CSAInsert(parmstring);
                         break;
    case SE_Remove    : 
    case CE_Remove    :  CSAInsert(parmstring);
                         break;
    case SE_Delete    : 
    case CE_Delete    :  CSADelete(parmstring);
                         break;
    case SE_Close      : 
    case CE_Close      : CSAClose(parmstring);
                         break;
    case SE_Closed     : 
    case CE_Closed     : CSAClosed(parmstring);
                         break;
    case SE_Command    : 
    case CE_Command    : char      command[65];
                         char      string[256];
                         RunCommand(command,string);
                         break;
    default            : SOSERR(99);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FireEvent

\return term - Success

\param  event_id -
\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FireEvent"

logical CSA_Handle :: FireEvent (CSA_Events event_id, char *parmstring )
{
  logical                 term = NO;
  if ( csconnection )
  {
    term = GenerateCSEvent(event_id,NULL);
  }
  else
    term = ExecuteEvent(event_id,parmstring);

  return(term);
}

/******************************************************************************/
/**
\brief  GenerateCSEvent

\return term - Success

\param  event_id -
\param  pParams -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateCSEvent"

logical CSA_Handle :: GenerateCSEvent (CSA_Events event_id, CS_Message *pParams )
{

  csconnection->SendCSMessage((int32)CSA_EVENT,event_id,pParams,NULL);
  return(NO);
}

/******************************************************************************/
/**
\brief  RunCommand


\param  command -
\param  parmstring -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RunCommand"

void CSA_Handle :: RunCommand (char *command, char *parmstring )
{



}

/******************************************************************************/
/**
\brief  ~CSA_Handle


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSA_Handle"

                        CSA_Handle :: ~CSA_Handle ( )
{



}


