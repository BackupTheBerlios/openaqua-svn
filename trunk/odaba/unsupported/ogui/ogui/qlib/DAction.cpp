/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    DAction

\brief    


\date     $Date: 2006/07/09 17:21:29,53 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DAction"

#include  <pogui7.h>
#include  <sDFont.hpp>
#include  <sDPixmap.hpp>
#include  <sOFont.hpp>
#include  <sOIconSet.hpp>
#include  <sDAction.hpp>


/******************************************************************************/
/**
\brief  DAction - 




\param  act_names - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DAction"

     DAction :: DAction (char *act_names )
                     :   disabled(NO),
  text(NULL),
  tool_tip(NULL),
  help(NULL),
  short_cut(NULL),
  icon(NULL),
  font(NULL)
{

  memset(name,' ',ID_SIZE);
  
  if ( act_names )
    gvtxstb(name,act_names,ID_SIZE);

}

/******************************************************************************/
/**
\brief  HasText - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasText"

logical DAction :: HasText ( )
{

  return ( text || tool_tip || help );

}

/******************************************************************************/
/**
\brief  Initialize - 




\param  names - 
\param  fDisabled - 
\param  displ_text - 
\param  tip - 
\param  what - 
\param  shortcut - 
\param  pDPixmap_normal - 
\param  pDPixmap_active - 
\param  pDPixmap_disabled - 
\param  pDFont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void DAction :: Initialize (char *names, logical fDisabled, char *displ_text, char *tip, char *what, char *shortcut, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled, DFont *pDFont )
{

  if ( names )
    gvtxstb(name,names,sizeof(name)-1);

  disabled = fDisabled;

  if ( displ_text )
    text = strdup(displ_text);
  if ( tip )
    tool_tip = strdup(tip);
  if ( what )
    help = strdup(what);

  if ( shortcut )
    short_cut = strdup(shortcut);
  
  if ( pDPixmap_normal || pDPixmap_active || pDPixmap_disabled )
    icon = new OIconSet(pDPixmap_normal,pDPixmap_active,pDPixmap_disabled);

  if ( pDFont )
    font = new OFont(*pDFont);


}

/******************************************************************************/
/**
\brief  IsDisabled - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDisabled"

logical DAction :: IsDisabled ( )
{

  return(disabled);

}

/******************************************************************************/
/**
\brief  ~DAction - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DAction"

     DAction :: ~DAction ( )
{

  if ( text )
    free(text);
  text = NULL;
  
  if ( tool_tip )
    free(tool_tip);
  tool_tip = NULL;
  
  if ( help )
    free(help);
  help = NULL;
  
  if ( short_cut )
    free(short_cut);
  short_cut = NULL;
  
  delete icon;
  icon = NULL;
  
  delete font;
  font = NULL;

}


