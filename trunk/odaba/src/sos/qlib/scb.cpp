/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    scb

\brief    


\date     $Date: 2006/03/12 19:22:41,85 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "scb"

#include  <pdefault.h>
#ifndef   GSRT_fcb_HPP
#define   GSRT_fcb_HPP
#include  <sfcb.hpp>
#include  <sGSRT.h>
#endif
#include  <sfcb.hpp>
#include  <sfmcb.hpp>
#include  <ssmcb.hpp>
#include  <ssrt.hpp>
#include  <sscb.hpp>


/******************************************************************************/
/**
\brief  GetFMCB - 


\return fmcbptr - Field definition block

\param  indx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFMCB"

fmcb *scb :: GetFMCB (int16 indx )
{
  fcb      *fcbptr = NULL;

BEGINSEQ
  if ( !scbfcb || !(fcbptr = scbfcb->GetEntry(indx)) )
                                                     ERROR

RECOVER

ENDSEQ
  return ( fcbptr ? fcbptr->fcbfmcb : NULL );

}

/******************************************************************************/
/**
\brief  GetName - 


\return strname -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *scb :: GetName ( )
{

  return(scbsmcb->smcbname);

}

/******************************************************************************/
/**
\brief  scb

-------------------------------------------------------------------------------
\brief SCB_


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "scb"

                        scb :: scb ( )
                     :   scbsmcb(NULL), scbfcb(NULL)

{

  SOSRESET


}

/******************************************************************************/
/**
\brief SCB_I


\param  smcbptr - Structure definition block
\param  elen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "scb"

                        scb :: scb (smcb *smcbptr, int16 elen )
                     :   scbsmcb(smcbptr), scbfcb(NULL)

{

  scbini(smcbptr,elen);


}

/******************************************************************************/
/**
\brief  scbeg

\return fcbptr

\param  fldnames - Field name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "scbeg"

fcb *scb :: scbeg (char *fldnames )
{
  fcb      *fcbptr;
  char      fldname[ID_SIZE];
  short int indx = 0;

  gvtxstb(fldname,fldnames,sizeof(fldname));

  while ( fcbptr = scbfcb->GetEntry(++indx) )
    if ( !memcmp(fcbptr->fcbfmcb->fmcbname,fldname,sizeof(fldname)) )
      break;
  return(fcbptr);

}

/******************************************************************************/
/**
\brief  scbini

-------------------------------------------------------------------------------
\brief SCBINI


\param  smcbptr - Structure definition block
\param  srtptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "scbini"

void scb :: scbini (smcb *smcbptr, srt *srtptr )
{

  scbsmcb = smcbptr;
  scbfcb  = (GSRT(fcb) *)srtptr;


}

/******************************************************************************/
/**
\brief SCBINI_K


\param  smcbptr - Structure definition block
\param  elen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "scbini"

void scb :: scbini (smcb *smcbptr, int16 elen )
{
  fmcb      *fmcbptr;               
  short int  indx = 0;                     

BEGINSEQ
  scbsmcb = smcbptr;
  if ( !smcbptr->smcbfmcl )                          LEAVESEQ
  
  if ( !(scbfcb = new GSRT(fcb)(smcbptr->smcbfmcl->GetCount(),
                                elen,UNDEF,UNDEF,UNDEF,YES)) )   
                                                     SOSERR(95)
                                                     SOSCERR
  while ( fmcbptr = smcbptr->smcbfmcl->GetEntry(++indx) )
    scbfcb->AddFreeEntry()->fcbfmcbs(fmcbptr);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~scb


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~scb"

                        scb :: ~scb ( )
{

  delete scbfcb;
  scbfcb = NULL;


}


