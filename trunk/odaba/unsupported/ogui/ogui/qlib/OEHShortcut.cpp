/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    OEHShortcut

\brief    


\date     $Date: 2006/04/20 15:01:40,80 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OEHShortcut"

#include  <pogui7.h>
#include  <sOEHShortcut.hpp>


/******************************************************************************/
/**
\brief  OEHShortcut - 


-------------------------------------------------------------------------------
\brief  i0


\param  string - Character string
\param  oeh_frame - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHShortcut"

                        OEHShortcut :: OEHShortcut (char *string, OEH_Frame oeh_frame )
                     :   key_sequence(NULL),
  frame(oeh_frame)
{

  if ( string )
    key_sequence = strdup(string);

}

/******************************************************************************/
/**
\brief  i00


\param  string - Character string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHShortcut"

                        OEHShortcut :: OEHShortcut (char *string )
                     :   key_sequence(NULL),
  frame(OEH_undefined)
{

  if ( string )
    key_sequence = strdup(string);

}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OEHShortcut"

                        OEHShortcut :: OEHShortcut ( )
                     :   key_sequence(NULL),
  frame(OEH_undefined)
{



}

/******************************************************************************/
/**
\brief  Shortcut

\return pQKeySequence

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Shortcut"

QKeySequence OEHShortcut :: Shortcut ( )
{

  return ( QKeySequence(key_sequence ? key_sequence : "") );

}

/******************************************************************************/
/**
\brief  ShortcutContext

\return schortcut_context

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShortcutContext"

Qt::ShortcutContext OEHShortcut :: ShortcutContext ( )
{

  switch ( frame )
  {
    case OEH_Application : return(Qt::ApplicationShortcut); 
    case OEH_Window      : return(Qt::WindowShortcut);      
    case OEH_Widget      :
    case OEH_undefined   :
    default              : return(Qt::WidgetShortcut);
  }

}

/******************************************************************************/
/**
\brief  operator== - 


\return cond - 

\param  rOEHShortcut - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical OEHShortcut :: operator== (OEHShortcut &rOEHShortcut )
{
logical      cond = YES;
BEGINSEQ
if(!key_sequence || !rOEHShortcut.key_sequence )    ERROR
if( strcmp(key_sequence, rOEHShortcut.key_sequence) !=0 )
                                                    ERROR

if(QKeySequence(key_sequence) != QKeySequence(rOEHShortcut.key_sequence))
                                                    ERROR
if( frame && rOEHShortcut.frame &&
    frame != rOEHShortcut.frame )                   ERROR

/*
  return (   key_sequence && rOEHShortcut.key_sequence &&
             QKeySequence(key_sequence) == QKeySequence(rOEHShortcut.key_sequence) &&
             (frame == rOEHShortcut.frame || !frame || !rOEHShortcut.frame)
           ? YES : NO );
*/
RECOVER
  cond = NO;
ENDSEQ
  return cond;
}


