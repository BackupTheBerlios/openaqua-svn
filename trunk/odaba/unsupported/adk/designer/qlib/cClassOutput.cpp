/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassOutput

\brief    


\date     $Date: 2006/08/28 07:57:58,32 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cClassOutput"

#include  <stdinc.h>
#include  <pdesign.h>
#include  <sRegExp.hpp>
#include  <spODE.hpp>
#include  <scClassOutput.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return  - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cClassOutput :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cClassOutput();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterOpen - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterOpen"

int8 cClassOutput :: DoAfterOpen ( )
{
  pODE            *ode_ctx     = ODEContext(this);

BEGINSEQ
  if ( !ode_ctx )                                    ERROR

  ode_ctx->SetOutputContext(this);
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterSelect - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cClassOutput :: DoAfterSelect ( )
{
  CTX_Control    *target_ctx = ODEContext(this)->GetTargetContext();
  DPoint          pos;
  static RegExp   lines("[^\n]*\n");
  static RegExp   error("^[^(]*\\(([0-9][0-9]*)\\)", YES);
  std::string     data(GetPropertyHandle()->GetString());
  std::string     line;
  std::string     errnum;
  VECTOR(intPair) matches;
BEGINSEQ
  if ( !target_ctx )                                 ERROR
    
  matches = lines.Search(data);
  pos     = GetPosition();
  
  if ( matches.size() < pos.Y )                      ERROR
  line    = data.substr(matches[pos.Y - 1].first,matches[pos.Y - 1].second);
  matches = error.Search(line);
  
  if ( matches.size() < 2 )                          LEAVESEQ
  
  errnum = line.substr(matches[1].first, matches[1].second);
  
  target_ctx->SetParm((char *)errnum.c_str());
  target_ctx->ExecuteFunction("GotoLine");
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  DoBeforeClose - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeClose"

int8 cClassOutput :: DoBeforeClose ( )
{
  pODE            *ode_ctx     = ODEContext(this);

BEGINSEQ
  if ( !ode_ctx )                                    ERROR

  ode_ctx->SetOutputContext(NULL);
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  cClassOutput - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cClassOutput"

     cClassOutput :: cClassOutput ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cClassOutput - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cClassOutput"

     cClassOutput :: ~cClassOutput ( )
{



}


