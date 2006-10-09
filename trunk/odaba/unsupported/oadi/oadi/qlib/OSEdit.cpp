/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OSEdit



\date     $Date: 2006/04/28 16:54:15,68 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSEdit"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOHighlighter.hpp>
#include  <sOToolBox.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTProjectManager.hpp>
#include  <sOSEdit.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OSEdit :: CastPointer (char *typenames )
{

  return (   !typenames                  ? NULL
           : !strcmp(typenames,"OSEdit") ? this
                                         : OStyle::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateInstance

\return rc

\param  instptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OSEdit :: CreateInstance (void **instptrp )
{
  *instptrp = new OSEdit();
  return(0);
}

/******************************************************************************/
/**
\brief  GetObjectType

\return typenames

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetObjectType"

char *OSEdit :: GetObjectType ( )
{

  return("OSEdit");

}

/******************************************************************************/
/**
\brief  HasHscrol

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasHscrol"

logical OSEdit :: HasHscrol ( )
{

  return ( this ? auto_hscrol : UNDEF );

}

/******************************************************************************/
/**
\brief  HasPassword

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasPassword"

logical OSEdit :: HasPassword ( )
{

  return ( this ? pass_word : UNDEF );

}

/******************************************************************************/
/**
\brief  HasVscrol

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasVscrol"

logical OSEdit :: HasVscrol ( )
{

  return ( this ? auto_vscrol : UNDEF );

}

/******************************************************************************/
/**
\brief  OSEdit

-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSEdit"

     OSEdit :: OSEdit ( )
                     : OStyle (),
  multiLine()
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOStyle
\param  is_multiline
\param  is_richtext
\param  pOHighlighter
\param  pOToolBox
\param  is_password
\param  auto_hscroll
\param  auto_vscroll
\param  is_upper
\param  is_lower
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSEdit"

     OSEdit :: OSEdit (OStyle bcOStyle, logical is_multiline, logical is_richtext, OHighlighter *pOHighlighter, OToolBox *pOToolBox, logical is_password, logical auto_hscroll, logical auto_vscroll, logical is_upper, logical is_lower )
                     : OStyle (bcOStyle),
  multiLine(is_multiline),
  rich_text(is_richtext),
  highlighter(pOHighlighter),
  toolbar(pOToolBox),
  pass_word(is_password),
  auto_hscrol(auto_hscroll),
  auto_vscrol(auto_vscroll),
  upper(is_upper),
  lower(is_lower)
{
/*
  "OSEdit("
  +        ADK_OStyle::Generate()
  + ", " + multi_line
  + ", " + rich_text
  + ", " + highlighter.Generate()
  + ", " + toolbar.Generate()
  + ", " + pass_word
  + ", " + auto_hscrol
  + ", " + auto_vscrol
  + ", " + upper
  + ", " + lower
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

logical OSEdit :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OStyle::Read(ph);

  multiLine   = ph->GetInt("multi_line");
  rich_text   = ph->GetInt("rich_text");

  pass_word   = ph->GetInt("pass_word");
  auto_hscrol = ph->GetInt("auto_hscrol");
  auto_vscrol = ph->GetInt("auto_vscrol");
  upper       = ph->GetInt("upper");
  lower       = ph->GetInt("lower");

  highlighter = CACHE_READ(ph,"highlighter",OHighlighter);
  toolbar = CACHE_READ(ph,"toolbar",OToolBox);

//  Out("res_cache.Add(new OSEdit(" + ... "," + multi_line + "," + rich_text,
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OSEdit :: Reset ( )
{
  if ( highlighter )
    highlighter->Release();
  highlighter = NULL;
  
  if ( toolbar )
    toolbar->Release();
  toolbar = NULL;

  OStyle::Reset();
}

/******************************************************************************/
/**
\brief  ~OSEdit


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSEdit"

     OSEdit :: ~OSEdit ( )
{
  if ( !Deleting() )
    Reset();
}


