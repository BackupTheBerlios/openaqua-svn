/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    InputArea

\brief    


\date     $Date: 2006/08/28 08:00:21,50 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "InputArea"

#include  <podcp8.h>
#include  <sCTX_Control.hpp>
#include  <sInputArea.hpp>


/******************************************************************************/
/**
\brief  GetLine - 



\return string - 0-terminated string

\param  string - 0-terminated string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLine"

char *InputArea :: GetLine (char *string )
{
  PropertyHandle  *in    = input_ctx ? input_ctx->GetPropertyHandle() : NULL;
  logical          term  = NO;

BEGINSEQ
  input = "";
  if ( !in )                                        ERROR
  
  input = in->GetString();
  *in = "";
  input_ctx->FillControl();
  input_ctx->FlushGUI();

  if ( string )
    strcpy(string,input);
RECOVER
  if ( string ) *string = 0;
ENDSEQ
  return(input);
}

/******************************************************************************/
/**
\brief  InputArea - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputArea"

     InputArea :: InputArea ( )
                     :   input(2048),
  input_ctx(NULL)
{



}

/******************************************************************************/
/**
\brief  SetInputContext - 




\param  ctx_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInputContext"

void InputArea :: SetInputContext (CTX_Control *ctx_ptr )
{

  input_ctx = ctx_ptr;

}

/******************************************************************************/
/**
\brief  ~InputArea - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~InputArea"

     InputArea :: ~InputArea ( )
{



}


