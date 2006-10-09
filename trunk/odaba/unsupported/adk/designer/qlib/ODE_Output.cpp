/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/14|13:42:34,87}|(REF) - Context that communicates with the output area
\class    ODE_Output

\brief    


\date     $Date: 2006/04/10 18:27:14,42 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODE_Output"

#include  <pdesign.h>
#include  <sODE_Output.hpp>


/******************************************************************************/
/**
\brief  DisplayOutput

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayOutput"

logical ODE_Output :: DisplayOutput ( )
{
  PropertyHandle  *out   = output_ctx ? output_ctx->GetPropertyHandle() : NULL;
  logical          term  = NO;

BEGINSEQ
  if ( !out )                                        ERROR
  
  *out = output;  
  output_ctx->FillControl();
  output_ctx->FlushGUI();
  ScrollToEnd();
RECOVER
  term = YES;
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  GetTargetContext - 


\return ctx_ptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTargetContext"

CTX_Control *ODE_Output :: GetTargetContext ( )
{

  return ( this ? target_ctx : NULL );

}

/******************************************************************************/
/**
\brief  MessageOutput


\param  string
\param  pError
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MessageOutput"

void ODE_Output :: MessageOutput (char *string, Error *pError )
{

  SetupOutput(string,NO);
  if ( pError )
    SetupOutput(pError->GetText(),NO);
  SetupOutput("\n",NO);


}

/******************************************************************************/
/**
\brief  ODE_Output - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODE_Output"

                        ODE_Output :: ODE_Output ( )
                     :   output(),
  output_ctx(NULL),
  target_ctx(NULL)
{



}

/******************************************************************************/
/**
\brief  ScrollToEnd

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ScrollToEnd"

logical ODE_Output :: ScrollToEnd ( )
{
  logical     term  = NO;
  int         i     = 0,
              iLine = 0;
BEGINSEQ
  // scroll to end
  if(!output_ctx)                                   ERROR
  if(!output)                                       ERROR
  while(output[i]!='\0'){
    if(output[i]=='\n')
      iLine++;
    i++;
  }
  output_ctx->SetPosition(DPoint(1,iLine));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetOutputContext - 



\param  ctx_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOutputContext"

void ODE_Output :: SetOutputContext (CTX_Control *ctx_ptr )
{

  output_ctx = ctx_ptr;

}

/******************************************************************************/
/**
\brief  SetTargetContext - 



\param  ctx_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTargetContext"

void ODE_Output :: SetTargetContext (CTX_Control *ctx_ptr )
{

  target_ctx = ctx_ptr;

}

/******************************************************************************/
/**
\brief  SetupOutput - 


\return term - 

\param  string
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupOutput"

logical ODE_Output :: SetupOutput (char *string, logical clear_opt )
{

  if ( clear_opt )
    output = "";
    
  if ( string )
    output += string;  

  

  return(DisplayOutput());
}

/******************************************************************************/
/**
\brief  ~ODE_Output - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODE_Output"

                        ODE_Output :: ~ODE_Output ( )
{



}


