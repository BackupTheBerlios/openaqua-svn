/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    CTX_Application

\brief    


\date     $Date: 2006/07/05 14:04:25,52 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_Application"

#include  <podcp8.h>
#include  <sCTX_Application.hpp>


/******************************************************************************/
/**
\brief  CTX_Application - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_Application"

     CTX_Application :: CTX_Application ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  GetContextType - Returns CTXT_Application



\return ctxtype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextType"

CTX_Types CTX_Application :: GetContextType ( )
{

  return ( CTXT_Application );

}

/******************************************************************************/
/**
\brief  ~CTX_Application - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_Application"

     CTX_Application :: ~CTX_Application ( )
{



}


