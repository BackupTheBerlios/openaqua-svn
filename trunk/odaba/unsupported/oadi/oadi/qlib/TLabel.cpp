/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:32:37,32}|(REF)
\class    TLabel

\brief    


\date     $Date: 2006/03/13 21:33:24,12 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TLabel"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sOContextStyle.hpp>
#include  <sOElementStyle.hpp>
#include  <sOField.hpp>
#include  <sOFrameStyle.hpp>
#include  <sOLabel.hpp>
#include  <sOLabelDefinition.hpp>
#include  <sOStyle.hpp>
#include  <sOWidget.hpp>
#include  <sTCheckBoxField.hpp>
#include  <sTLabel.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return term -

\param  pTControl -
\param  pOLabelDefinition -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical TLabel :: Create (TControl *pTControl, OLabelDefinition *pOLabelDefinition )
{
  OLabelDefinition  *ld   = pOLabelDefinition;
  OElementStyle     *es;
  OStyle            *st;
  OFrameStyle       *fs; 
  OAlign            *a;
  DPoint             p;
  logical            term = NO;

BEGINSEQ
  target = PTR_CAST(TWidgetControl,pTControl);

  if ( PTR_CAST(TCheckBoxField,target) ) 
    drawFocusRect = YES;

  es = new OElementStyle; 
  es->Create(this,YES);
  st = new OStyle;
  st->Create(this,YES);
  fs = new OFrameStyle; 
  fs->Create(this,YES);
  es->SetStyle(st);

  a = es->Align();
  a->SetHori(ld->HoriPos(HPS_undefined));
  a->SetVert(ld->VertPos(VPS_undefined));
  es->SetSize(ld->Size());

  switch( a->Hori(HPS_OuterLeft) )
  {
    case HPS_InnerLeft  :
    case HPS_OuterRight : p.X = 0;                    break;
    case HPS_InnerRight : 
    case HPS_OuterLeft  : p.X = es->Size().Width;     break;
    case HPS_Center     : p.X = -es->Size().Width/2;  break;
  }

  switch( a->Vert(VPS_InnerTop) )
  {
    case VPS_InnerTop    :
    case VPS_OuterBottom : p.Y = 0;                    break;
    case VPS_InnerBottom :
    case VPS_OuterTop    : p.Y = es->Size().Height;    break;
    case VPS_Center      : p.Y = -es->Size().Height/2; break;
  }

  es->SetPosition(p);

  if ( TControl::Create(pTControl,es,fs) )           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoCreate - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoCreate"

logical TLabel :: DoCreate ( )
{
  OLabel            *l;
  logical            term = NO;
BEGINSEQ
  if ( TWidgetControl::DoCreate() )                     ERROR

// create widget
  
  l = new OLabel(ClientWidgetParent(),WidgetOwner());
  controlWidget = l;
  l->setBuddy(target->ControlWidget() ? target->ControlWidget()->WidgetQ() : NULL);  
  l->setFocusProxy(target->ControlWidget() ? target->ControlWidget()->WidgetQ() : NULL);  
  l->SetDrawFocusRect(drawFocusRect);
  
  BindClientWidget(controlWidget,0);

  loadText(); // *fixme* use activity

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetDrawFocusRect - 



\param  fEnable -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDrawFocusRect"

void TLabel :: SetDrawFocusRect (logical fEnable )
{

  drawFocusRect = fEnable;

  if ( controlWidget )
    ((OLabel *)controlWidget)->SetDrawFocusRect(drawFocusRect);

}

/******************************************************************************/
/**
\brief  TLabel - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TLabel"

                        TLabel :: TLabel ( )
                     : TWidgetControl (),
  target(NULL),
  drawFocusRect(NO)
{



}

/******************************************************************************/
/**
\brief  loadText - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "loadText"

logical TLabel :: loadText ( )
{
  OText      *lab;
  logical     term = NO;
  lab = target->ElementStyle()->TextDefinitions();

  ((OLabel *)controlWidget)->setText(SZ2QS(lab->Title()));
  return(term);
}



#define GRTTI_CLS  TLabel
#define GRTTI_NAME "OADI8.TLabel"

#ifdef  HAS_RTTI_TWidgetControl
#  ifndef GRTTI_BASE1
#    define GRTTI_BASE1 TWidgetControl
#  else
#    ifndef GRTTI_BASE2
#      define GRTTI_BASE2 TWidgetControl
#    else
#      ifndef GRTTI_BASE3
#        define GRTTI_BASE3 TWidgetControl
#      else
#        error "Too many base classes. Plz update RTTI in SOS and OMA/TPL."
#      endif
#    endif
#  endif
#endif

#define GRTTI_CREATE
#include <rtti_imp.h>
