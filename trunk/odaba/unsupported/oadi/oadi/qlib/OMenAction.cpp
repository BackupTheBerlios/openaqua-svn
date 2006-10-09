/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OMenAction



\date     $Date: 2006/04/30 16:13:35,17 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OMenAction"

#include  <poadi.h>
#include  <sCTX_Control.hpp>
#include  <sCTX_GUIBase.hpp>
#include  <sOEventAction.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTField.hpp>
#include  <sOMenAction.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OMenAction :: CastPointer (char *typenames )
{

  return (   !typenames                         ? NULL
           : !strcmp(typenames,"OMenaction")    ? this
           : !strcmp(typenames,"OContextStyle") ? (OContextStyle *)this
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

char OMenAction :: Execute (CTX_GUIBase *ctxptr )
{
  TWidgetControl   *tw;
  int8              executed = AUTO;

  if ( contextMenu )
  { 
     if ( tw = ctxptr->get_control() )
     {
       OI_CAST(TField,tw)->SetupContextMenu();
       executed = NO;
     }
  }
  else
  {
    ;
  }

  return(executed);
}

/******************************************************************************/
/**
\brief  OMenAction

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OMenAction"

     OMenAction :: OMenAction ( )
                     : OAction (),
OContextStyle (),
OBasePersistent (),
  menu(NULL),
  contextMenu(NO)
{
}

/******************************************************************************/
/**
\brief  i01


\param  bcOAction
\param  bcOContextStyle
\param  pOEventAction
\param  is_context_menu
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OMenAction"

     OMenAction :: OMenAction (OAction bcOAction, OContextStyle bcOContextStyle, OEventAction *pOEventAction, logical is_context_menu )
                     : OAction (bcOAction),
OContextStyle (bcOContextStyle),
  menu(pOEventAction),
  contextMenu(is_context_menu)
{
/*
  "OMenAction("
  +        ADK_Action::Generate()
  + ", " + ADK_ContextStyle::Generate()
  + ", NULL" // not set in Read
  + ", NO"   // not set ni Read
  + ")";
*/
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

logical OMenAction :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OAction::Read(ph);
  OContextStyle::Read(ph);


  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OMenAction :: Reset ( )
{
  if ( menu )
    menu->Release();
  menu = NULL;

  OAction::Reset();
  OContextStyle::Reset();


}

/******************************************************************************/
/**
\brief  SetContextMenuProperty


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContextMenuProperty"

void OMenAction :: SetContextMenuProperty ( )
{
  OAction::SetProperties(NULL,UNDEF,NULL);

  contextMenu = YES;


}

/******************************************************************************/
/**
\brief  ~OMenAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OMenAction"

     OMenAction :: ~OMenAction ( )
{
  if ( !Deleting() )
    Reset();

}


