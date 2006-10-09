/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cSDBResourceNotifyHigh

\brief    


\date     $Date: 2006/06/01 17:10:24,57 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cSDBResourceNotifyHigh"

#include  <pdesign.h>
#include  <scSDBResourceNotifyHigh.hpp>


/******************************************************************************/
/**
\brief  Changed - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Changed"

logical cSDBResourceNotifyHigh :: Changed ( )
{
  CTX_GUIBase        *guibase = NULL;
  return (  (guibase = GetHighContext()) 
           ? guibase->ExecuteFunction("Changed")
           : NO                                  );

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

int32 cSDBResourceNotifyHigh :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cSDBResourceNotifyHigh();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoAfterSelect - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterSelect"

int8 cSDBResourceNotifyHigh :: DoAfterSelect ( )
{

  cSDBResource_Base::DoAfterSelect();
  Changed();
  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterStoreData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterStoreData"

int8 cSDBResourceNotifyHigh :: DoAfterStoreData ( )
{

  cSDBResource_Base::DoAfterStoreData();
  Changed();
  return(NO);
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

logical cSDBResourceNotifyHigh :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("Changed",ALINK(this,cSDBResourceNotifyHigh,Changed)),
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
    term = cSDBResource_Base::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cSDBResourceNotifyHigh - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cSDBResourceNotifyHigh"

     cSDBResourceNotifyHigh :: cSDBResourceNotifyHigh ( )
                     : cSDBResource_Base ()
{



}

/******************************************************************************/
/**
\brief  ~cSDBResourceNotifyHigh - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cSDBResourceNotifyHigh"

     cSDBResourceNotifyHigh :: ~cSDBResourceNotifyHigh ( )
{



}


