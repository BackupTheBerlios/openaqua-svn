/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cControlFrame

\brief    


\date     $Date: 2006/06/03 15:11:15,76 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cControlFrame"

#include  <pdesign.h>
#include  <cqt.h>
#include  <streams.h>
#include  <scControlEdit.hpp>
#include  <scPropertyTable.hpp>
#include  <scControlFrame.hpp>


/******************************************************************************/
/**
\brief  CloseFieldControl - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseFieldControl"

logical cControlFrame :: CloseFieldControl ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  
  if ( dived )
  {
    RemoveField("ctl_edit_frame");
    dived = NO;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cControlFrame :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cControlFrame();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoAfterEnter - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterEnter"

int8 cControlFrame :: DoAfterEnter ( )
{
  int8                    executed = NO;
if ( control )
	UpdatePropertiesPH(&control_ph);
  return(executed);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return  - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical cControlFrame :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("ReloadControl",ALINK(this,cControlFrame,ReloadControl)),
                           cfte("SizeChanged",ALINK(this,cControlFrame,SizeChanged)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = CTX_Control::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetControlPH - 


\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControlPH"

PropertyHandle *cControlFrame :: GetControlPH ( )
{

  return(&control_ph);

}

/******************************************************************************/
/**
\brief  GetFieldPH - 


\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFieldPH"

PropertyHandle *cControlFrame :: GetFieldPH ( )
{

  return(&field_ph);

}

/******************************************************************************/
/**
\brief  GetPropertiesContext - 


\return properties - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertiesContext"

cPropertyTable *cControlFrame :: GetPropertiesContext ( )
{
  CTX_Control    * ctl_design = NULL;
  cPropertyTable * properties = NULL;
BEGINSEQ
  ctl_design = (CTX_Control*)HighContext("designer", CTXT_Control);
  if ( ! ctl_design )                                OADIERR(99)
  
  properties = (cPropertyTable*)ctl_design->GetControlContext("properties");
  if ( ! properties )                                OADIERR(99)
RECOVER
  properties = NULL;
ENDSEQ
  return(properties);
}

/******************************************************************************/
/**
\brief  OpenFieldControl - 


\return term - 

\param  ctrl_ph - 
\param  pos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenFieldControl"

logical cControlFrame :: OpenFieldControl (PropertyHandle *ctrl_ph, const DPoint &pos )
{
  logical                 term     = NO;
  cControlFrame         * sub_edit = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  
  if ( !(sub_edit = (cControlFrame*)CreateField("ctl_edit_frame", NO, pos, AUTO)) )
                                                     ERROR
  if ( !control )                                    ERROR
  
  sub_edit->ShowControl(ctrl_ph);
  
  dived = YES;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReloadControl - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReloadControl"

logical cControlFrame :: ReloadControl ( )
{
  logical       started = NO;
  logical       term    = NO;
BEGINSEQ
  static char    * const ctl_edit   = "__control_edit";
  static int       const context_nr = 100003;

  if ( !this )                                       ERROR
  
  started = control_ph.StartRTA() ? YES : NO;

  if ( control )
  {
    control->SetControlPH(NULL);
    control->ResetControl();
    RemoveField(ctl_edit);
    control = NULL;
  }
  
  InvalidateDesignerCache();
  if ( control = (cControlEdit *)CreateControl(ctl_edit, &control_ph, DSize(), DPoint(), NULL, 0, context_nr) )
  {
    control->SetControlPH(&control_ph);
    control->InitDesigner();
    SetSize(control->GetSize() + DSize(12,12));
  }
  else
    ExecuteWindow(&control_ph,"ADK_FieldControl","Edit",NO);
RECOVER
  term = YES;
ENDSEQ
  control_ph.StopRTA(started);
  return(term);
}

/******************************************************************************/
/**
\brief  ShowControl - 


\return term - 

\param  c_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowControl"

logical cControlFrame :: ShowControl (PropertyHandle *c_ph )
{

  if ( !control_ph.IsValid() )
  {
    class_ph.Open(GetDATDB(), "ADK_Class", PI_Read);
    control_ph.Open(&class_ph, "controls");
  }
  control_ph.ChangeMode(PI_Update);
  
  class_ph.Get(c_ph->GetPropertyHandle("class")->ExtractKey());
  control_ph.Get(c_ph->ExtractKey());

  ReloadControl();
  
  UpdatePropertiesPH(&control_ph);
  return(NO);
}

/******************************************************************************/
/**
\brief  SizeChanged - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SizeChanged"

logical cControlFrame :: SizeChanged ( )
{
  logical                 term = NO;
  SetSize(control->GetSize() + DSize(12,12));

  if ( ((CTX_Control*)GetHighContext()) == ((CTX_Control*)HighContext("mdi_frame")) )
    ((CTX_Control*)GetHighContext())->SetSize(GetSize());

  return(term);
}

/******************************************************************************/
/**
\brief  UpdatePropertiesPH - 


\return term - 

\param  ph_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdatePropertiesPH"

logical cControlFrame :: UpdatePropertiesPH (PropertyHandle *ph_ptr )
{
  logical          term       = NO;
  cPropertyTable * properties = NULL;
BEGINSEQ
  if ( !this )                                       ERROR

  if ( ! (properties = GetPropertiesContext()) )     ERROR
  properties->Update(ph_ptr);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cControlFrame - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cControlFrame"

     cControlFrame :: cControlFrame ( )
                     : CTX_Control (),
  control(NULL),
  class_ph(),
  control_ph(),
  field_ph(),
  dived(NO)
{



}

/******************************************************************************/
/**
\brief  ~cControlFrame - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cControlFrame"

     cControlFrame :: ~cControlFrame ( )
{



}


