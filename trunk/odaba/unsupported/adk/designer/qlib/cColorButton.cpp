/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cColorButton

\brief    


\date     $Date: 2006/08/30 14:47:14,86 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cColorButton"

#include  <pdesign.h>
#include  <cqt.h>
#include  <sDColor.hpp>
#include  <scColorButton.hpp>


/******************************************************************************/
/**
\brief  Changed - 



\return  - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Changed"

logical cColorButton :: Changed ( )
{
  logical                 term = NO;
  PropertyHandle        * attr_ph;
  DColor                  bgcolor;
BEGINSEQ
  if ( !(attr_ph = GetPropertyHandle()) )            ERROR
  if ( !attr_ph->Inherits("clr") )                   ERROR
                                                     
  bgcolor = DColor(
      attr_ph->GetPropertyHandle("clrred")->GetInt(),
      attr_ph->GetPropertyHandle("clrgreen")->GetInt(),
      attr_ph->GetPropertyHandle("clrblue")->GetInt()
    );
  GetButtonContext("Color")->SetBackgroundColor(bgcolor);

RECOVER
  term = YES;
ENDSEQ
  return (cNotifyHighContext::Changed());
}

/******************************************************************************/
/**
\brief  ColorDialog - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColorDialog"

logical cColorButton :: ColorDialog ( )
{
  logical                 term = NO;
  QColor                  color;
  PropertyHandle        * attr_ph;

BEGINSEQ
  if ( !(attr_ph = GetPropertyHandle()) )            ERROR
  if ( !attr_ph->Inherits("clr") )                   ERROR

  color.setRgb(
    attr_ph->GetPropertyHandle("clrred")->GetInt(),
    attr_ph->GetPropertyHandle("clrgreen")->GetInt(),
    attr_ph->GetPropertyHandle("clrblue")->GetInt()
  );

  color = QColorDialog::getColor ( color );
  if ( color.isValid() )
  {
    *attr_ph->GetPropertyHandle("clrred")   = color.red();
    *attr_ph->GetPropertyHandle("clrgreen") = color.green();
    *attr_ph->GetPropertyHandle("clrblue")  = color.blue();
    attr_ph->Save();

    Changed();
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

int32 cColorButton :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cColorButton();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoBeforeFillData - 



\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeFillData"

int8 cColorButton :: DoBeforeFillData ( )
{
  int8         executed = NO;

  Changed();

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

logical cColorButton :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("Changed",ALINK(this,cColorButton,Changed)),
                           cfte("ColorDialog",ALINK(this,cColorButton,ColorDialog)),
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
    term = cNotifyHighContext::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}


