/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    CAU_simpleAction

\brief    Simple action
          A  simple action defines an action  outside of any specific context by
          name  and action type. Simple actions must be defined as method in the
          context  where  they  are  defined  (e.g. in the structure or property
          context  when defining a structure or  property action). The method an
          action  is  referring  to,  may  have  different  types  as  function,
          expression etc.

\date     $Date: 2006/03/13 21:30:17,95 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CAU_simpleAction"

#include  <pops7.h>
#include  <sCAU_simpleAction.hpp>


/******************************************************************************/
/**
\brief  CAU_simpleAction - 


-------------------------------------------------------------------------------
\brief  i0


\param  actnames -
\param  acttyp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CAU_simpleAction"

                        CAU_simpleAction :: CAU_simpleAction (char *actnames, ActionType acttyp )
                     :   action_type(acttyp)
{

  gvtxstb(sys_ident,actnames,sizeof(sys_ident));

}

/******************************************************************************/
/**
\brief  i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CAU_simpleAction"

                        CAU_simpleAction :: CAU_simpleAction ( )
                     :   action_type(ACT_undefined)
{

  memset(sys_ident,' ',sizeof(sys_ident));

}


