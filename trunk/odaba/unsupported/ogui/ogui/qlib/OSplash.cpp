/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    OSplash



\date     $Date: 2006/04/26 11:30:38,18 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSplash"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sOSplash.hpp>


/******************************************************************************/
/**
\brief  Message


\param  qsText
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Message"

void OSplash :: Message (QString qsText )
{
  if ( this ) 
    showMessage(qsText);
}

/******************************************************************************/
/**
\brief  OSplash


\param  qsText
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSplash"

                        OSplash :: OSplash (QString qsText )
                     : QSplashScreen(qsText)
{
show();
}

/******************************************************************************/
/**
\brief  Wait


\param  pQWidget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Wait"

void OSplash :: Wait (QWidget *pQWidget )
{
  if ( this )
    finish(pQWidget);
}

/******************************************************************************/
/**
\brief  ~OSplash


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSplash"

                        OSplash :: ~OSplash ( )
{
}


