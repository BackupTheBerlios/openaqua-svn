/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    CTX_Project

\brief    


\date     $Date: 2006/08/28 08:00:41,31 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_Project"

#include  <podcp8.h>
#include  <sDBErrorHandle.hpp>
#include  <sCTX_Project.hpp>


/******************************************************************************/
/**
\brief  CTX_Project - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_Project"

     CTX_Project :: CTX_Project ( )
                     : CTX_Application ()
{
  ErrorHandle         *hdl;
  SetApplicationContext(this);       // set context in SystemIO process variable


}

/******************************************************************************/
/**
\brief  GetContextType - Returns CTXT_Project



\return ctxtype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextType"

CTX_Types CTX_Project :: GetContextType ( )
{

  return ( CTXT_Project );

}

/******************************************************************************/
/**
\brief  Input - 



\return string - 0-terminated string

\param  string - 0-terminated string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Input"

char *CTX_Project :: Input (char *string )
{

  return( InputArea::GetLine(string) );

}

/******************************************************************************/
/**
\brief  Output - 



\return term - 

\param  string - 0-terminated string
\param  clear_opt - 
\param  flush_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CTX_Project :: Output (char *string, logical clear_opt, logical flush_opt )
{

  SetupOutput(string,clear_opt);
  
  if ( flush_opt )
    DisplayOutput();
  return(NO);
}

/******************************************************************************/
/**
\brief  ~CTX_Project - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_Project"

     CTX_Project :: ~CTX_Project ( )
{

  SetApplicationContext(NULL);       // set context in SystemIO process variable


}


