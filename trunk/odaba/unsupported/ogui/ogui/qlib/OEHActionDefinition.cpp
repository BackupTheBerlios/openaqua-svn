/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OEHActionDefinition

\brief    


\date     $Date: 2006/07/05 23:34:34,70 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHActionDefinition"

#include  <pogui7.h>
#include  <sDFont.hpp>
#include  <sDPixmap.hpp>
#include  <sOFont.hpp>
#include  <sOIconSet.hpp>
#include  <sOEHActionDefinition.hpp>


/******************************************************************************/
/**
\brief  Initialize - 




\param  names - 
\param  displ_text - 
\param  shortcut - 
\param  pDPixmap_normal - 
\param  pDPixmap_active - 
\param  pDPixmap_disabled - 
\param  pDFont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void OEHActionDefinition :: Initialize (char *names, char *displ_text, char *shortcut, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled, DFont *pDFont )
{

BEGINSEQ
  if ( !names | !*names )                            OGUIERR(99)
  gvtxbts(name,names,sizeof(name)-1);
  if ( displ_text )
    text = strdup(displ_text);
  if ( shortcut )
    short_cut = strdup(shortcut);
  
  if ( pDPixmap_normal || pDPixmap_active || pDPixmap_disabled )
    icon = new OIconSet(pDPixmap_normal,pDPixmap_active,pDPixmap_disabled);

  if ( pDFont )
    font = new OFont(*pDFont);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  OEHActionDefinition - 




\param  names - 
\param  displ_text - 
\param  shortcut - 
\param  pDPixmap_normal - 
\param  pDPixmap_active - 
\param  pDPixmap_disabled - 
\param  pDFont - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHActionDefinition"

     OEHActionDefinition :: OEHActionDefinition (char *names, char *displ_text, char *shortcut, DPixmap *pDPixmap_normal, DPixmap *pDPixmap_active, DPixmap *pDPixmap_disabled, DFont *pDFont )
                     :   text(NULL),
  short_cut(NULL),
  icon(NULL),
  font(NULL)
{

  Initialize(names,displ_text,shortcut,pDPixmap_normal,pDPixmap_active,pDPixmap_disabled,pDFont);

}

/******************************************************************************/
/**
\brief  ~OEHActionDefinition - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OEHActionDefinition"

     OEHActionDefinition :: ~OEHActionDefinition ( )
{

  if ( text )
    free(text);
  text = NULL;
  
  if ( short_cut )
    free(short_cut);
  short_cut = NULL;
  
  delete icon;
  icon = NULL;
  
  delete font;
  font = NULL;

}


