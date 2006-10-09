/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OJumpAction



\date     $Date: 2006/04/28 11:23:15,51 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OJumpAction"

#include  <poadi.h>
#include  <sOJumpAction.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OJumpAction :: CastPointer (char *typenames )
{

  return (   !typenames                       ? NULL
           : !strcmp(typenames,"OJumpAction") ? this
                                              : OAction::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  OJumpAction

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OJumpAction"

     OJumpAction :: OJumpAction ( )
                     : OAction (),
  target()
{


}

/******************************************************************************/
/**
\brief  SetTarget

\return term

\param  rcdsText
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTarget"

logical OJumpAction :: SetTarget (const DString &rcdsText )
{

  target = rcdsText;
  return(NO);
}

/******************************************************************************/
/**
\brief  ~OJumpAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OJumpAction"

     OJumpAction :: ~OJumpAction ( )
{
}


