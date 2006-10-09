/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    TComponent



\date     $Date: 2006/05/03 23:12:52,60 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TComponent"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sTComponent.hpp>
#include  <sTComponent.hpp>

int32 bc_count = 0;
int32 bc_max = 0;
int32 bc_total = 0;

/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *TComponent :: CastPointer (char *typenames )
{
  return (   !typenames                      ? NULL
           : !strcmp(typenames,"TComponent") ? this
                                             : NULL );
}

/******************************************************************************/
/**
\brief  Close


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void TComponent :: Close ( )
{
  TComponent         *c;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  while ( c = children.GetHead() ) 
    delete c;
//  c->Close(this);
  
  if ( owner ) 
    owner->RemoveComponent(this);
  owner = NULL;
  
  if  ( !deleting ) 
    delete this;

ENDSEQ
}

/******************************************************************************/
/**
\brief  Create

\return term

\param  pTComponent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical TComponent :: Create (TComponent *pTComponent )
{
  logical   term = NO;
BEGINSEQ
// we set owner now, but InsertComponent will be called during DoCreate!
  if ( pTComponent )
    pTComponent->InsertComponent(this);

// 0.090
  if ( DoCreate() )                                  ERROR

// 0.019 (90% füt SetupDefaultActions)
  if ( DoCreated() )                                 ERROR


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Deleting


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deleting"

void TComponent :: Deleting ( )
{

  deleting = YES;

}

/******************************************************************************/
/**
\brief  DoCreate

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreate"

logical TComponent :: DoCreate ( )
{

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

logical TComponent :: DoCreated ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  InsertComponent


\param  pTComponent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertComponent"

void TComponent :: InsertComponent (TComponent *pTComponent )
{
BEGINSEQ
  if ( pTComponent->owner == this )                 LEAVESEQ

  if ( pTComponent->owner ) 
    pTComponent->owner->RemoveComponent(pTComponent);

  children.AddTail(pTComponent);

  pTComponent->owner = this;

ENDSEQ
}

/******************************************************************************/
/**
\brief  IsDeleting

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDeleting"

logical TComponent :: IsDeleting ( )
{

  return(deleting);

}

/******************************************************************************/
/**
\brief  Owner

\return pTComponent

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Owner"

TComponent *TComponent :: Owner ( ) const
{

  return ( this ? owner : NO );

}

/******************************************************************************/
/**
\brief  OwnerOfType

\return pTComponent

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OwnerOfType"

TComponent *TComponent :: OwnerOfType (char *typenames )
{
  TComponent  *p = (TComponent *)owner;
  void        *o = NULL;

BEGINSEQ
  while ( p )
  {
    if ( o = p->CastPointer(typenames) )             LEAVESEQ
    p = (TComponent *)p->owner;
  }

ENDSEQ
  return((TComponent *)o);
}

/******************************************************************************/
/**
\brief  RemoveComponent


\param  pTComponent
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveComponent"

void TComponent :: RemoveComponent (TComponent *pTComponent )
{
  if ( pTComponent->owner == this ) 
    pTComponent->owner = NULL;
  
  children.Remove(pTComponent);
}

/******************************************************************************/
/**
\brief  TComponent


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TComponent"

     TComponent :: TComponent ( )
                     :   owner(NULL),
  children(),
  deleting(NO)
{

bc_total++;
if ( ++bc_count > bc_max ) bc_max = bc_count;

}

/******************************************************************************/
/**
\brief  ~TComponent


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~TComponent"

     TComponent :: ~TComponent ( )
{

bc_count--;

}


