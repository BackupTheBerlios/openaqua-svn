/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODeferrer

\brief    


\date     $Date: 2006/03/13 21:35:37,65 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODeferrer"

#include  <pogui7.h>
#include  <sODeferrer.hpp>


/******************************************************************************/
/**
\brief  Fire - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fire"

void ODeferrer :: Fire ( )
{



}

/******************************************************************************/
/**
\brief  ODeferrer - 



\param  pQObject -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODeferrer"

                        ODeferrer :: ODeferrer (QObject *pQObject )
                     :  QObject(pQObject)
{

  timerid = startTimer(0);


}

/******************************************************************************/
/**
\brief  timerEvent - 



\param  pQTimerEvent -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "timerEvent"

void ODeferrer :: timerEvent (QTimerEvent *pQTimerEvent )
{

  killTimer(timerid);
  
  if ( parent() ) 
    setParent(NULL);
    
  Fire();
  delete this;


}


