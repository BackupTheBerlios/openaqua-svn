/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cDoubleTabMaster

\brief    


\date     $Date: 2006/06/01 17:02:42,87 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cDoubleTabMaster"

#include  <pdesign.h>
#include  <sNString.hpp>
#include  <scDoubleTabMaster.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cDoubleTabMaster :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cDoubleTabMaster();
  return(NO);

}

/******************************************************************************/
/**
\brief  DisplayLevelChanged - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayLevelChanged"

logical cDoubleTabMaster :: DisplayLevelChanged ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( ignore_slave )                                LEAVESEQ
  if ( !Parm(1) )                                    ERROR
  
  display_level = atoi(Parm(1));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterSelect - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cDoubleTabMaster :: DoAfterSelect ( )
{
  NString        slave_name = "tab";
  CTX_Control  * slave_context = NULL;
BEGINSEQ
  slave_name += GetDisplayLevel();

  slave_context = GetFieldContext(slave_name);
  if ( ! slave_context )                             ERROR

  slave_context->SetDisplayLevel(display_level);

  ignore_slave = NO;
RECOVER

ENDSEQ
  return NO;
}

/******************************************************************************/
/**
\brief  DoBeforeSelect - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeSelect"

int8 cDoubleTabMaster :: DoBeforeSelect ( )
{

  ignore_slave = YES;
  return NO;
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

logical cDoubleTabMaster :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("DisplayLevelChanged",ALINK(this,cDoubleTabMaster,DisplayLevelChanged)),
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
\brief  cDoubleTabMaster - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cDoubleTabMaster"

     cDoubleTabMaster :: cDoubleTabMaster ( )
                     : CTX_Control (),
  display_level(0),
  ignore_slave(NO)
{



}

/******************************************************************************/
/**
\brief  ~cDoubleTabMaster - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cDoubleTabMaster"

     cDoubleTabMaster :: ~cDoubleTabMaster ( )
{



}


