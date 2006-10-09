/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CTX_Object

\brief    Database Object Context
          The  Database  Object  context  allows  defining functionality that is
          executed  when  opening  or  closing  a  Database  Object.  The parent
          context  for an object context is  an object con-text (if the Database
          Object  is not the root Database  Object) or the database context (for
          the root Database Object).
          The   default   database   object   context   can   be overloaded by a
          application specific database context class.

\date     $Date: 2006/03/12 19:16:48,57 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_Object"

#include  <popa7.h>
#include  <coctp.h>
#include  <sACObject.hpp>
#include  <sCTX_Base.hpp>
#include  <sCTX_Object.hpp>


/******************************************************************************/
/**
\brief  CTX_Object - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_Object"

                        CTX_Object :: CTX_Object ( )
                     : CTX_DBBase (),
  object_handle(NULL)
{



}

/******************************************************************************/
/**
\brief  GetConnectionClient - 


\return client -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConnectionClient"

ODABAClient CTX_Object :: GetConnectionClient ( )
{

  return (   this && object_handle 
           ? object_handle->GetConnectionClient()
           : GetMainClient() );

}

/******************************************************************************/
/**
\brief  GetContextType - Get Context type
        The function returns the specific context type as CTX_DBObject

\return ctxtype - Context type

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextType"

CTX_Types CTX_Object :: GetContextType ( )
{


  return(CTXT_Object);
}

/******************************************************************************/
/**
\brief  Initialize - 



\param  obhandle - Database Object handle
\param  highctx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CTX_Object :: Initialize (ACObject *obhandle, CTX_Base *highctx )
{

  CTX_DBBase::Initialize(NULL,highctx);
  object_handle = obhandle;

}

/******************************************************************************/
/**
\brief  ~CTX_Object - Destructor
        The  function destroys the database object context. The function must be
        overloaded  in  an  application  specific implementation of the database
        object context.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_Object"

                        CTX_Object :: ~CTX_Object ( )
{



}


