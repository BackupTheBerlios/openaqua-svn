/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    cWorkspace

\brief    


\date     $Date: 2006/03/12 19:37:27,56 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cWorkspace"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <scMDIFrame.hpp>
#include  <scWorkspace.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc -

\param  ctx_ctl_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cWorkspace :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cWorkspace();
  return(NO);


}

/******************************************************************************/
/**
\brief  ShowControl


\param  c_ph -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowControl"

void cWorkspace :: ShowControl (PropertyHandle *c_ph )
{
  cMDIFrame * mdi_frame;
BEGINSEQ
  if ( strcmp(c_ph->GetCurrentType(),"ADK_FieldControl") )
                                                     ERROR
  mdi_frame = (cMDIFrame*)GetControlContext("mdi_frame");
  if ( !mdi_frame )
    mdi_frame = (cMDIFrame*)CreateField("mdi_frame", NO, DPoint(0,0), AUTO);

  if ( !mdi_frame )                                  ERROR

  mdi_frame->ShowControl(c_ph);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  cWorkspace


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cWorkspace"

                        cWorkspace :: cWorkspace ( )
{



}

/******************************************************************************/
/**
\brief  ~cWorkspace - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cWorkspace"

                        cWorkspace :: ~cWorkspace ( )
{



}


