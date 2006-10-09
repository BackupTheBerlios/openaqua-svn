/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    TControlFactory

\brief    


\date     $Date: 2006/06/19 19:42:48,57 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "TControlFactory"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sOAction.hpp>
#include  <sOApplication.hpp>
#include  <sOButtonControl.hpp>
#include  <sODesktop.hpp>
#include  <sOElementStyle.hpp>
#include  <sOFieldControl.hpp>
#include  <sOProject.hpp>
#include  <sOSButtonGroup.hpp>
#include  <sOSCheckBox.hpp>
#include  <sOSEdit.hpp>
#include  <sOSGroupBox.hpp>
#include  <sOSListBox.hpp>
#include  <sOSRadioGroup.hpp>
#include  <sOSSplitter.hpp>
#include  <sOSTabControl.hpp>
#include  <sOSWindow.hpp>
#include  <sOStyle.hpp>
#include  <sOWinAction.hpp>
#include  <sOWindow.hpp>
#include  <sTAction.hpp>
#include  <sTApplication.hpp>
#include  <sTButtonBoxField.hpp>
#include  <sTButtonGroup.hpp>
#include  <sTCheckBoxField.hpp>
#include  <sTControl.hpp>
#include  <sTDateField.hpp>
#include  <sTDesktop.hpp>
#include  <sTEditField.hpp>
#include  <sTField.hpp>
#include  <sTGroupBox.hpp>
#include  <sTListBoxField.hpp>
#include  <sTProject.hpp>
#include  <sTPushButton.hpp>
#include  <sTRadioGroup.hpp>
#include  <sTSplitter.hpp>
#include  <sTTabControl.hpp>
#include  <sTTimeField.hpp>
#include  <sTWindow.hpp>
#include  <scfte.hpp>
#include  <sTControlFactory.hpp>


/******************************************************************************/
/**
\brief  NewControl - 


\return tcontrol - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewControl"

TControl *__cdecl TControlFactory :: NewControl (char *typenames )
{
  static cfte   cttbl[] = {
                             cfte("ODesktop",SLINK(TDesktop,CreateControl)),

                             cfte("OProject",SLINK(TProject,CreateControl)),
                             cfte("OApplication",SLINK(TApplication,CreateControl)),
                             cfte("OWindow",SLINK(TWindow,CreateControl)),

                             cfte("OButton",SLINK(TPushButton,CreateControl)),

                             cfte("OSButtonBox",SLINK(TButtonBoxField,CreateControl)),
                             cfte("OSDate",SLINK(TDateField,CreateControl)),
                             cfte("OSEdit",SLINK(TEditField,CreateControl)),
                             cfte("OSListBox",SLINK(TListBoxField,CreateControl)),
                             cfte("OSCheckBox",SLINK(TCheckBoxField,CreateControl)),
                             cfte("OSSplitter",SLINK(TSplitter,CreateControl)),
                             cfte("OSGroupBox",SLINK(TGroupBox,CreateControl)),
                             cfte("OSButtonGroup",SLINK(TButtonGroup,CreateControl)),
                             cfte("OSRadioGroup",SLINK(TRadioGroup,CreateControl)),
                             cfte("OSTabControl",SLINK(TTabControl,CreateControl)),
                             cfte("OSTime",SLINK(TTimeField,CreateControl)),
                             cfte("OSWindow",SLINK(TWindow,CreateControl)),

                             cfte()
                          };
  static srt    cftesrt(sizeof(cttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)cttbl,NO);
  cfte         *cfteptr;
  char          buffer[ID_SIZE];
  TControl     *tcontrol = NULL;
  

BEGINSEQ
  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(buffer,typenames,ID_SIZE))) )
    cfteptr->VoidCall(&tcontrol);

  if ( !tcontrol )                                   ERROR

RECOVER
  delete tcontrol;
  tcontrol = NULL;

ENDSEQ
  return(tcontrol);
}

/******************************************************************************/
/**
\brief  TControlFactory - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TControlFactory"

     TControlFactory :: TControlFactory ( )
{



}


