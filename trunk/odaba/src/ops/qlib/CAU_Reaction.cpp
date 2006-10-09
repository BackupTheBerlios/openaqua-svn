/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    CAU_Reaction

\brief    Reaction
          The  reaction defines  a link  between an  event and an action that is
          called  when  the  event  is  signaled.  The  reaction  defines a path
          between  the  generating  object  instance  and  the  reacting  object
          instances.  When the path is referring  to a collection each object in
          the collection will react on the event.
          Events  and related  action are  defined in causality. Causalities are
          either  part of  a dictionary  resource (structure,  member) or can be
          defined as global causalities.

\date     $Date: 2006/03/13 21:30:17,90 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CAU_Reaction"

#include  <pops7.h>
#include  <sCAU_Reaction.hpp>


/******************************************************************************/
/**
\brief  set__AUTOIDENT - 



\param  autoident -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set__AUTOIDENT"

void CAU_Reaction :: set__AUTOIDENT (int32 autoident )
{

  __AUTOIDENT = autoident;

}


