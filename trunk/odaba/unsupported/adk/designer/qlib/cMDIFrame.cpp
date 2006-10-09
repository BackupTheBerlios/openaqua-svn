/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cMDIFrame



\date     $Date: 2006/05/23 14:26:20,31 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cMDIFrame"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <scControlFrame.hpp>
#include  <scMDIFrame.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  ctx_ctl_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cMDIFrame :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cMDIFrame();
  return(NO);

}

/******************************************************************************/
/**
\brief  GetControlFrame

\return ctl_frame

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetControlFrame"

cControlFrame *cMDIFrame :: GetControlFrame ( )
{
  cControlFrame           * ctl_frame = NULL;
  ctl_frame = (cControlFrame*)GetFieldContext("ctl_edit_frame");
  return(ctl_frame);
}

/******************************************************************************/
/**
\brief  ShowControl

\return term - 

\param  c_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowControl"

logical cMDIFrame :: ShowControl (PropertyHandle *c_ph )
{
  logical                 term = NO;
  cControlFrame         * ctl_frame = NULL;
BEGINSEQ
  if ( !(ctl_frame = GetControlFrame()) )            ERROR

  term = ctl_frame->ShowControl(c_ph);
  SetSize(ctl_frame->GetSize());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cMDIFrame


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cMDIFrame"

     cMDIFrame :: cMDIFrame ( )
{
}

/******************************************************************************/
/**
\brief  ~cMDIFrame


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cMDIFrame"

     cMDIFrame :: ~cMDIFrame ( )
{
}


