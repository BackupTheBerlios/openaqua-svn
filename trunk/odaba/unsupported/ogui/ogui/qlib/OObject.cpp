/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OObject

\brief    


\date     $Date: 2006/03/13 21:36:09,59 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OObject"

#include  <pogui7.h>
#include  <sODataWidget.hpp>
#include  <sOObject.hpp>


/******************************************************************************/
/**
\brief  GetODW - 


\return pODataWidget - Parent data widget

\param  pQObject -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetODW"

ODataWidget *__cdecl OObject :: GetODW (QObject *pQObject )
{

  pQObject = pQObject->findChild<QObject *>(ODW_NAME);

  return(pQObject ? (ODataWidget *)(((OObject *)pQObject)->o_ptr)
                  : NULL);

}

/******************************************************************************/
/**
\brief  OObject - Konstruktor



\param  pQObject -
\param  extra_data -
\param  names -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OObject"

                        OObject :: OObject (QObject *pQObject, void *extra_data, char *names )
                     : QObject (pQObject),
  o_ptr(extra_data)
{

  setObjectName(names ? names : "EXTRA_DATA");

}

/******************************************************************************/
/**
\brief  RegisterODW - 


\return term -

\param  pODataWidget - Parent data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegisterODW"

logical __cdecl OObject :: RegisterODW (ODataWidget *pODataWidget )
{
  QWidget      *pQWidget;
  logical       term = NO;
BEGINSEQ
  if ( !(pQWidget = pODataWidget->WidgetQ()) )       ERROR
    
  if ( !pQWidget->findChild<QObject *>(ODW_NAME) )
    new OObject(pQWidget,pODataWidget,ODW_NAME);  
    
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


