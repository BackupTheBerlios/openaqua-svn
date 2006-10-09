/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OToolBarList

\brief    


\date     $Date: 2006/03/13 21:36:19,03 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OToolBarList"

#include  <pogui7.h>
#include  <sOToolBar.hpp>
#include  <sOToolBarList.hpp>


/******************************************************************************/
/**
\brief  FindToolBar

\return pOToolBar -

\param  action -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindToolBar"

OToolBar *OToolBarList :: FindToolBar (OEHAction *action )
{
  OToolBar   *tool_bar = NULL;
  int         count    = size();
  int         indx0    = 0;
BEGINSEQ
  while ( indx0 < count ) 
    if ( tool_bar = at(indx0++) )
      if ( tool_bar->get_toolbar_action() == action )
                                                     LEAVESEQ

  ERROR
RECOVER
  tool_bar = NULL;
ENDSEQ
  return(tool_bar);
}

/******************************************************************************/
/**
\brief  Hide

\return pOToolBar -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Hide"

OToolBar *OToolBarList :: Hide ( )
{
  OToolBar   *tool_bar = NULL;
  int         count    = size();
  int         indx0    = 0;
  while ( indx0 < count ) 
    if ( tool_bar = at(indx0++) )
      tool_bar->hide();

  return(tool_bar);
}

/******************************************************************************/
/**
\brief  OToolBarList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OToolBarList"

                        OToolBarList :: OToolBarList ( )
                     : QList<OToolBar *> ()
{



}

/******************************************************************************/
/**
\brief  Show

\return pOToolBar -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Show"

OToolBar *OToolBarList :: Show ( )
{
  OToolBar   *tool_bar = NULL;
  int         count    = size();
  int         indx0    = 0;
  while ( indx0 < count ) 
    if ( tool_bar = at(indx0++) )
      tool_bar->show();

  return(tool_bar);
}

/******************************************************************************/
/**
\brief  ~OToolBarList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OToolBarList"

                        OToolBarList :: ~OToolBarList ( )
{



}


