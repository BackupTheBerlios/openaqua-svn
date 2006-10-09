/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    CTX_Administration

\brief    


\date     $Date: 2006/07/05 14:04:24,11 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_Administration"

#include  <podcp8.h>
#include  <sCTX_Administration.hpp>


/******************************************************************************/
/**
\brief  CTX_Administration - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_Administration"

     CTX_Administration :: CTX_Administration ( )
                     : CTX_Application ()
{



}

/******************************************************************************/
/**
\brief  GetContextType - Returns CTXT_Administration



\return ctxtype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextType"

CTX_Types CTX_Administration :: GetContextType ( )
{

  return ( CTXT_Administration );

}

/******************************************************************************/
/**
\brief  ~CTX_Administration - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_Administration"

     CTX_Administration :: ~CTX_Administration ( )
{



}


