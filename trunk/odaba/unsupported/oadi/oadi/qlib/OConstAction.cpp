/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OConstAction



\date     $Date: 2006/04/30 16:26:13,73 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OConstAction"

#include  <poadi.h>
#include  <sOConstAction.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OConstAction :: CastPointer (char *typenames )
{

  return (   !typenames                        ? NULL
           : !strcmp(typenames,"OConstAction") ? this
                                               : OAction::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  Execute

\return executed - How was function exetuted

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

char OConstAction :: Execute ( )
{

  return(AUTO);  // not yet implemented

}

/******************************************************************************/
/**
\brief  OConstAction

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OConstAction"

     OConstAction :: OConstAction ( )
                     : OAction (),
  text(NULL)
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOAction
\param  text
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OConstAction"

     OConstAction :: OConstAction (OAction bcOAction, char *text )
                     : OAction (bcOAction),
  text(NULL)
{
  if ( text )
    this->text = strdup(text);

/*
  "OConstAction("
  + ADK_Action::Generate()
  + ", " + ???
  + ")";
  is this even a adk class that needs a generate?
*/
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OConstAction :: Reset ( )
{
  if ( text )
    free(text);
  text = NULL;

  OAction::Reset();
}

/******************************************************************************/
/**
\brief  SetText

\return term

\param  string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

logical OConstAction :: SetText (char *string )
{

  Reset();

  if ( string )
    text = strdup(string);
  return(NO);
}

/******************************************************************************/
/**
\brief  ~OConstAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OConstAction"

     OConstAction :: ~OConstAction ( )
{
  if ( !Deleting() )
    Reset();
}


