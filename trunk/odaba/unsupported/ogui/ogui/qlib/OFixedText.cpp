/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OFixedText

\brief    


\date     $Date: 2006/03/13 21:35:52,89 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OFixedText"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOFixedText.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sOFixedText.hpp>


/******************************************************************************/
/**
\brief  ClearData - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearData"

void OFixedText :: ClearData ( )
{

  clear();


}

/******************************************************************************/
/**
\brief  FillData - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

void OFixedText :: FillData ( )
{

  setText(ods()->Value());


}

/******************************************************************************/
/**
\brief  FrameQ - 


\return pQFrame -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *OFixedText :: FrameQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  OFixedText - 


\return term -

\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OFixedText"

                        OFixedText :: OFixedText (ODataWidget *pODataWidget, ODataWidget *oODataWidget )
                     : QLabel (pODataWidget ? pODataWidget->WidgetQ() : NULL),
OEHControlValue (pODataWidget,oODataWidget,NO)
{

  connect(ods(),SIGNAL(OnInstanceUpdated()),
          this, SLOT(loadValue()));

  setAlignment(alignment() & ~Qt::AlignVCenter);


}

/******************************************************************************/
/**
\brief  SetText - 


\return term -

\param  qsText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetText"

logical OFixedText :: SetText (QString qsText )
{
  logical                 term = NO;
  setText(qsText);
  return(term);
}

/******************************************************************************/
/**
\brief  WidgetQ - 


\return pQWidget -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OFixedText :: WidgetQ ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  ~OFixedText - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OFixedText"

                        OFixedText :: ~OFixedText ( )
{



}


