/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    GlobalObject

\brief    


\date     $Date: 2006/03/12 19:17:35,43 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "GlobalObject"

#include  <popa7.h>
#include  <sLACObject.hpp>
#include  <sGlobalObject.hpp>


/******************************************************************************/
/**
\brief  GetACObject - 


\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetACObject"

LACObject *GlobalObject :: GetACObject ( )
{

  return ( object_ref );

}

/******************************************************************************/
/**
\brief  GlobalObject - 



\param  lobhandle -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GlobalObject"

                        GlobalObject :: GlobalObject (LACObject *lobhandle )
                     : object_lock(YES),
  object_ref(lobhandle)
{



}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

\param  wait -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical GlobalObject :: Lock (logical wait )
{

  return ( object_lock.ILock(wait) );

}

/******************************************************************************/
/**
\brief  SetupContext - 



\param  highctx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupContext"

void GlobalObject :: SetupContext (CTX_Base *highctx )
{

  if ( object_ref->get_ocontext() )
    object_ref->get_ocontext()->CTX_Base::Initialize(highctx);


}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical GlobalObject :: Unlock ( )
{

  return ( object_lock.IUnlock() );

}

/******************************************************************************/
/**
\brief  ~GlobalObject - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~GlobalObject"

                        GlobalObject :: ~GlobalObject ( )
{

  delete object_ref;
  object_ref = NULL;

}


