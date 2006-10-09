/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OText



\date     $Date: 2006/04/28 14:10:49,37 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OText"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOText.hpp>
#include  <sPropertyHandle.hpp>
#include  <sOText.hpp>


/******************************************************************************/
/**
\brief  GetHelp

\return string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHelp"

char *OText :: GetHelp ( )
{

  return ( this ? long_text : NULL );


}

/******************************************************************************/
/**
\brief  GetTitle

\return string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTitle"

char *OText :: GetTitle ( )
{

  return ( this ? title : NULL );


}

/******************************************************************************/
/**
\brief  GetTooltip

\return string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTooltip"

char *OText :: GetTooltip ( )
{

  return ( this ? tooltip : NULL );


}

/******************************************************************************/
/**
\brief  OText

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OText"

     OText :: OText ( )
                     : OPersistent (),
  title(NULL),
  tooltip(NULL),
  long_text(NULL)
{


}

/******************************************************************************/
/**
\brief  i01


\param  bcOPersistent
\param  title
\param  tooltip
\param  long_text
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OText"

     OText :: OText (OPersistent bcOPersistent, char *title, char *tooltip, char *long_text )
                     : OPersistent (bcOPersistent),
  title(NULL),
  tooltip(NULL),
  long_text(NULL)
{
if(title && *title)         this->title     = strdup(title);
if(tooltip && *tooltip)     this->tooltip   = strdup(tooltip);
if(long_text && *long_text) this->long_text = strdup(long_text);
/*
  "OText("
  + ADK_Persistent::Generate()
  + ", \"" + title + "\""
  + ", \"" + tooltip + "\""
  + ", \"" + long_text + "\""
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

logical OText :: Read (PropertyHandle *ph )
{
  char      *str;
  logical    term = NO;
  if ( (str = ph->GetString("title")) && *str ) 
    title = strdup(str);

  if ( (str = ph->GetString("tooltip")) && *str ) 
    tooltip = strdup(str);

  if ( (str = ph->GetString("long_text")) && *str ) 
    long_text = strdup(str);

  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OText :: Reset ( )
{
  if ( title )
    free(title);
  title = NULL;

  if ( tooltip )
    free(tooltip);
  tooltip = NULL;

  if ( long_text )
    free(long_text);
  long_text = NULL;
}

/******************************************************************************/
/**
\brief  SetupText


\param  pOText
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupText"

void OText :: SetupText (OText *pOText )
{

  if ( !title && pOText->get_title() )
    title = strdup(pOText->get_title());
  if ( !tooltip && pOText->get_tooltip() )
    tooltip = strdup(pOText->get_tooltip());
  if ( !long_text && pOText->get_long_text())
    long_text = strdup(pOText->get_long_text());


}

/******************************************************************************/
/**
\brief  ~OText


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OText"

     OText :: ~OText ( )
{

  Reset();

}


