/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ckm

\brief    


\date     $Date: 2006/03/12 19:18:30,65 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ckm"

#include  <popa7.h>
#include  <sACReference.hpp>
#include  <skfc.hpp>
#include  <sref.hpp>
#include  <sckm.hpp>


/******************************************************************************/
/**
\brief  CheckMod - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckMod"

logical ckm :: CheckMod ( )
{

  return( ckmnode->GetRef()->refmod ? YES : NO );


}

/******************************************************************************/
/**
\brief  CloseCKE - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseCKE"

logical ckm :: CloseCKE ( )
{

  delete ckmnode;
  ckmnode = NULL;
  return(NO);


}

/******************************************************************************/
/**
\brief  GetKey - 


\return keyptr -

\param  keyptr -
\param  instptr -
\param  indx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *ckm :: GetKey (char *keyptr, void *instptr, int16 indx )
{
  fmcb     *keyfmcb = ckekfc->fcbfmcb;
  fmcb      strfmcb = *ckekfc->kfcfmcbg();

BEGINSEQ

  strfmcb.fmcbrlev = R_DIRECT;

  if ( !ckmnode || !(instptr = (char *)ckmnode->Get((int32)(indx-1),NO)) )
							   ERROR
  strfmcb.fmcbkgt((char *)instptr,keyptr+keyfmcb->fmcbposn);

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  OpenCKE - 


\return count -

\param  instptr -
\param  refopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenCKE"

int16 ckm :: OpenCKE (void *instptr, logical refopt )
{
  PropertyHandle   *pibptr;
  node             *nodeptr;
  int32          count;
BEGINSEQ
  if ( !(pibptr = (PropertyHandle *)(((char *)instptr)+ckekfc->kfcfmcbg()->fmcbposn)) ||
       !(nodeptr = pibptr->get_nodeptr())      ||
       !nodeptr->IsValid()             )             ERROR

  if ( !refopt )
    if ( pibptr->Save() )                            ERROR
  
  if ( !(ckmnode = (ACReference *)nodeptr->CreateCopyNode()) )
                                                     ERROR
  
  if ( (count = ckmnode->GetCount()) == ERIC )       ERROR

RECOVER
  count = AUTO;
ENDSEQ
  return((int)count);

}

/******************************************************************************/
/**
\brief  ckm - 



\param  kfcptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ckm"

                        ckm :: ckm (kfc *kfcptr )
                     : cke(kfcptr),
 ckmnode(NULL)

{



}

/******************************************************************************/
/**
\brief  ~ckm - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ckm"

                        ckm :: ~ckm ( )
{



}


