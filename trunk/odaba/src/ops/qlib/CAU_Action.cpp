/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    CAU_Action

\brief    Conditional action
          A  conditional  action  allows  handling  events  for initializing new
          instances,  consistency checks for modifications and other purposes. A
          conditional  action  is  defined  in  a structure or property context.
          Conditional  actions may combine related object  instances or a set of
          instances  in the database. A conditional  action is identified by its
          name, which must be unique in the context of the causality.
          A  conditional action defines the direct  reaction on an event, i.e. a
          reaction  of the same object instance that has generated the event. It
          is,  however,  also  possible  to  define reactions of other (related)
          instances  via reactions. A conditional action is imbedded in pre- and
          post-processing.  The pre-processing  action can  suppress running the
          action  if  necessary.  The  post-processing  allows  final  handling 
          specific for a given context.

\date     $Date: 2006/05/14 20:47:11,95 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CAU_Action"

#include  <pops7.h>
#include  <sCAU_Action.hpp>


/******************************************************************************/
/**
\brief  CAU_Action - Simple action
        The  action  defines  the  action  name  and  type  for the action to be
        performed.

-------------------------------------------------------------------------------
\brief  i0


\param  action_name
\param  actiontyp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CAU_Action"

     CAU_Action :: CAU_Action (char *action_name, ActionType actiontyp )
                     : CAU_simpleAction (action_name,actiontyp)

{
  memset(structure,' ',sizeof(structure));
  memset(property,' ',sizeof(property));

}

/******************************************************************************/
/**
\brief  i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CAU_Action"

     CAU_Action :: CAU_Action ( )
                     : CAU_simpleAction ()
{
}


