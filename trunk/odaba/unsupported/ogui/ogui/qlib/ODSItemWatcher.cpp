/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSItemWatcher

\brief    


\date     $Date: 2006/03/13 21:35:28,26 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODSItemWatcher"

#include  <pogui7.h>
#include  <sODSItemStatic.hpp>
#include  <sODSItemWatcher.hpp>


/******************************************************************************/
/**
\brief  ODSItemWatcher - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSItemWatcher"

                        ODSItemWatcher :: ODSItemWatcher ( )
                     : QObject ()
{

  startTimer(1000);


}

/******************************************************************************/
/**
\brief  timerEvent - 



\param  pQTimerEvent -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "timerEvent"

void ODSItemWatcher :: timerEvent (QTimerEvent *pQTimerEvent )
{

  ODSItemStatic::checkItems();


}


