/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TBaseComponent

\brief    Resource component
          Resources  defined  in  the  repository are converted into an internal
          format when being activated (red).

\date     $Date: 2006/04/28 14:53:42,12 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TBaseComponent"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sPropertyHandle.hpp>
#include  <sTBaseComponent.hpp>
#include  <sTBaseComponent.hpp>

int32 bc_count = 0;
int32 bc_max = 0;
int32 bc_total = 0;

/******************************************************************************/
/**
\brief  Close


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void TBaseComponent :: Close ( )
{



}

/******************************************************************************/
/**
\brief  ComponentState

\return int

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ComponentState"

int TBaseComponent :: ComponentState ( ) const
{

  return componentState;

}

/******************************************************************************/
/**
\brief  Create

\return term

\param  fDeleteOnDestroy_YES - Delete resource component, when destroying
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical TBaseComponent :: Create (logical fDeleteOnDestroy_YES )
{
  logical term = NO;
BEGINSEQ
  deleteOnDestroy = fDeleteOnDestroy_YES;

// we set owner now, but InsertComponent will be called during DoCreate!

  componentState |= csDangling;
  
  if ( DoCreate() )                                  ERROR

  if ( DoCreated() )                                 ERROR
RECOVER
  term = YES;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoCreate

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreate"

logical TBaseComponent :: DoCreate ( )
{

  return(NO);
  return(NO);
}

/******************************************************************************/
/**
\brief  DoCreated

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreated"

logical TBaseComponent :: DoCreated ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  DoDestroy


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoDestroy"

void TBaseComponent :: DoDestroy ( )
{



}

/******************************************************************************/
/**
\brief  GetID

\return id

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

int TBaseComponent :: GetID ( )
{

  return(UNDEF);

}

/******************************************************************************/
/**
\brief  IsDeleting

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDeleting"

logical TBaseComponent :: IsDeleting ( )
{

  return ( (componentState & csDestroying) && deleteOnDestroy );


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

logical TBaseComponent :: Read (PropertyHandle *ph )
{

  deleteOnDestroy = NO;

  return(NO);
}

/******************************************************************************/
/**
\brief  TBaseComponent

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TBaseComponent"

     TBaseComponent :: TBaseComponent ( )
                     :   deleteOnDestroy(NO),
  componentState(0)

{


bc_count++;
bc_total++;
if ( bc_count > bc_max ) bc_max = bc_count;
}

/******************************************************************************/
/**
\brief  i01


\param  children_list
\param  delete_on_destroy
\param  component_state
\param  component_owner
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TBaseComponent"

     TBaseComponent :: TBaseComponent (DLL(TBaseComponent) children_list, logical delete_on_destroy, int component_state, TBaseComponent *component_owner )
                     :   deleteOnDestroy(delete_on_destroy),
  componentState(component_state)

{
  /*
  ??
  "TBaseComponent("
  + "  children_list"
  + ", " + "NO"
  + ", 0"
  + ", NULL"
  + ")";
  
  */
}

/******************************************************************************/
/**
\brief  ~TBaseComponent - Destructor
        The  essential  functionality  when  destroying  a resource component is
        done by the Destroy function.

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~TBaseComponent"

     TBaseComponent :: ~TBaseComponent ( )
{


bc_count--;
}


