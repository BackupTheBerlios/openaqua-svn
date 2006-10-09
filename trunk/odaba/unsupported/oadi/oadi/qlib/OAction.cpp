/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OAction



\date     $Date: 2006/04/30 16:05:40,43 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OAction"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sCTX_GUIBase.hpp>
#include  <sOADKFactory.hpp>
#include  <sOCAU_SimpleAction.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTComponent.hpp>
#include  <sTProjectManager.hpp>
#include  <sOAction.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OAction :: CastPointer (char *typenames )
{

  return (   !typenames                             ? NULL
           : !strcmp(typenames,"OAction")           ? this
           : !strcmp(typenames,"ODataSourceHaving") ? (ODataSourceHaving *)this
                                                    : OResource::CastPointer(typenames) );

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

char OAction :: Execute (CTX_GUIBase *ctxptr )
{
  logical                 executed = AUTO;

  return(executed);
}

/******************************************************************************/
/**
\brief  ExecuteAction

\return term

\param  ctxptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

logical OAction :: ExecuteAction (CTX_GUIBase *ctxptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( preHandler && !preHandler->IsEmpty() )
    if ( preHandler->Execute(ctxptr) > 0 )           ERROR

  if ( Execute(ctxptr) )                             ERROR
  
  if ( postHandler && !postHandler->IsEmpty() )
    postHandler->Execute(ctxptr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OAction

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OAction"

     OAction :: OAction ( )
                     : OResource (),
  preHandler(0),
  postHandler(0),
  owner(NULL)
{

  memset(_class,0,sizeof(_class));


}

/******************************************************************************/
/**
\brief  i1


\param  bcOResource
\param  bcODataSourceHaving
\param  s_class
\param  pOCAU_SimpleAction_preHandler
\param  pOCAU_SimpleAction_postHandler
\param  pCTX_GUIBase
\param  brunning
\param  bresult
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OAction"

     OAction :: OAction (OResource bcOResource, ODataSourceHaving bcODataSourceHaving, char *s_class, OCAU_SimpleAction *pOCAU_SimpleAction_preHandler, OCAU_SimpleAction *pOCAU_SimpleAction_postHandler, CTX_GUIBase *pCTX_GUIBase, logical brunning, logical bresult )
                     : OResource(),
ODataSourceHaving(dataSource),
  preHandler(0),
  postHandler(0),
  owner(NULL)
{
  logical   term = NO;
  memset(_class,0,sizeof(_class)); 
  strncpy(_class,s_class,sizeof(_class));

}

/******************************************************************************/
/**
\brief  Owner

\return pTComponent

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Owner"

TComponent *OAction :: Owner ( )
{

  return(owner);

}

/******************************************************************************/
/**
\brief  Read

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OAction :: Read (PropertyHandle *ph )
{
  uint32             id;
  logical            term = NO;
  OResource::Read(ph);

  strncpy(_class,ph->GetString("class"),ID_SIZE);

  dataSource.Read(ph->GPH("data_source"));

  preHandler  = CACHE_READ(ph,"pre_handler",OCAU_SimpleAction);
  postHandler = CACHE_READ(ph,"post_handler",OCAU_SimpleAction);

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OAction :: Reset ( )
{
  if ( preHandler )
    preHandler->Release();
  preHandler = NULL;

  if ( postHandler )
    postHandler->Release();
  postHandler = NULL;

  memset(_class,0,sizeof(_class));
  dataSource.Reset();
    
  OResource::Reset();

}

/******************************************************************************/
/**
\brief  SetProperties

\return term

\param  class_names
\param  as_collection
\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProperties"

logical OAction :: SetProperties (char *class_names, logical as_collection, PropertyHandle *prophdl )
{
  logical                 term = NO;
  OResource::SetProperties();
  
  strncpy(_class,class_names ? class_names : "",ID_SIZE);

  if ( prophdl )
    dataSource.SetProperties(as_collection,prophdl);

  return(term);
}

/******************************************************************************/
/**
\brief  xSetOwner


\param  pTComponent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xSetOwner"

void OAction :: xSetOwner (TComponent *pTComponent )
{

  owner = pTComponent;

}

/******************************************************************************/
/**
\brief  ~OAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OAction"

     OAction :: ~OAction ( )
{
  if ( !Deleting() )
    Reset();
}


