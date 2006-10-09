/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    SystemIO

\brief    


\date     $Date: 2006/08/27 20:29:04,34 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SystemIO"

#include  <pdefault.h>
#include  <sCTX_Base.hpp>
#include  <sSystemIO.hpp>


/******************************************************************************/
/**
\brief  GetContext - 



\return ctxptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContext"

CTX_Base *SystemIO :: GetContext ( )
{

  return(context);

}

/******************************************************************************/
/**
\brief  Read - 



\return string - String value

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

char *SystemIO :: Read (char *string )
{

  if ( !string )
    string = nstring;
  *string = 0;
  
  if ( context )
    string = context->Input(string);
  else
    string = ReadConsole(string);

  return(string);
}

/******************************************************************************/
/**
\brief  ReadConsole - 



\return string - String value

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadConsole"

char *__cdecl SystemIO :: ReadConsole (char *string )
{

  return(gets(string));


}

/******************************************************************************/
/**
\brief  SetContext - 




\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContext"

void SystemIO :: SetContext (CTX_Base *ctxptr )
{

  context = ctxptr;

}

/******************************************************************************/
/**
\brief  SystemIO - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SystemIO"

     SystemIO :: SystemIO ( )
                     :   context(NULL),
  nstring(4096)
{



}

/******************************************************************************/
/**
\brief  Write - 



\return term - Success

\param  string - String value
\param  clear_opt - 
\param  flush_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical SystemIO :: Write (char *string, logical clear_opt, logical flush_opt )
{
  logical      term = NO;
  if ( context )
    context->Output(string,clear_opt,flush_opt);
  else
    term = WriteConsole(string,clear_opt,flush_opt);

  return(term);
}

/******************************************************************************/
/**
\brief  WriteConsole - 



\return term - Success

\param  string - String value
\param  clear_opt - 
\param  flush_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteConsole"

logical __cdecl SystemIO :: WriteConsole (char *string, logical clear_opt, logical flush_opt )
{
  logical      term = NO;
  if ( clear_opt )
    ; // printf(""); clear sequence
  printf(string);
  return(term);
}

/******************************************************************************/
/**
\brief  ~SystemIO - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SystemIO"

     SystemIO :: ~SystemIO ( )
{



}


