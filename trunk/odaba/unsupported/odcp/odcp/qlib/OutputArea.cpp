/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    OutputArea

\brief    


\date     $Date: 2006/08/28 21:17:50,31 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OutputArea"

#include  <podcp8.h>
#include  <sCTX_Control.hpp>
#include  <sOutputArea.hpp>


/******************************************************************************/
/**
\brief  DisplayOutput - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayOutput"

logical OutputArea :: DisplayOutput ( )
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

CTX_Control *OutputArea :: GetTargetContext ( )
{

  return ( this ? target_ctx : NULL );

}

/******************************************************************************/
/**
\brief  MessageOutput - 




\param  string - 0-terminated string
\param  pError - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MessageOutput"

void OutputArea :: MessageOutput (char *string, Error *pError )
{

  SetupOutput(string,NO);
  if ( pError )
    SetupOutput(pError->GetText(),NO);
  SetupOutput("\n",NO);


}

/******************************************************************************/
/**
\brief  OutputArea - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OutputArea"

     OutputArea :: OutputArea ( )
                     :   output(),
  output_ctx(NULL),
  target_ctx(NULL)
{



}

/******************************************************************************/
/**
\brief  ScrollToEnd - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ScrollToEnd"

logical OutputArea :: ScrollToEnd ( )
{
  logical     term  = NO;
  int         i     = 0,
              iLine = 0;
BEGINSEQ
  if ( !output_ctx )                                ERROR
  if ( output.IsEmpty() )                           LEAVESEQ

  while ( output[i] != '\0' )
  {
    if ( output[i] == '\n' )
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

void OutputArea :: SetOutputContext (CTX_Control *ctx_ptr )
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

void OutputArea :: SetTargetContext (CTX_Control *ctx_ptr )
{

  target_ctx = ctx_ptr;

}

/******************************************************************************/
/**
\brief  SetupOutput - 



\return term - 

\param  string - 0-terminated string
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupOutput"

logical OutputArea :: SetupOutput (char *string, logical clear_opt )
{

  if ( clear_opt )
    output = "";
    
  if ( string )
    output += string;  

  

  return(NO);
}

/******************************************************************************/
/**
\brief  ~OutputArea - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OutputArea"

     OutputArea :: ~OutputArea ( )
{



}


