/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OFunctAction



\date     $Date: 2006/05/03 19:00:46,17 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OFunctAction"

#include  <poadi.h>
#include  <sCTX_GUIBase.hpp>
#include  <sTWidgetControl.hpp>
#include  <sOFunctAction.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OFunctAction :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"OFunctAction") ? this
                                               : OAction::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  Execute

\return executed - How was function exetuted

\param  ctxptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

char OFunctAction :: Execute (CTX_GUIBase *ctxptr )
{
  int8               executed = AUTO;

  if ( ctxptr && *function )
    if ( (executed = ctxptr->ExecuteFunction(function,NO)) == AUTO )
      if ( ctxptr->get_control() )
        executed = ctxptr->get_control()->ExecuteDefaultAction(function);
    

  return(executed);
}

/******************************************************************************/
/**
\brief  OFunctAction

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFunctAction"

     OFunctAction :: OFunctAction ( )
                     : OAction ()
{

  memset(function,0,sizeof(function));

}

/******************************************************************************/
/**
\brief  SetFunction


\param  fnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFunction"

void OFunctAction :: SetFunction (char *fnames )
{

  strncpy(function,fnames,sizeof(function)-1);

}

/******************************************************************************/
/**
\brief  SetProperties

\return term

\param  fname
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProperties"

logical OFunctAction :: SetProperties (char *fname )
{

  strncpy(function,fname ? fname : "",ID_SIZE);
  return(NO);
}

/******************************************************************************/
/**
\brief  ~OFunctAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OFunctAction"

     OFunctAction :: ~OFunctAction ( )
{
}


