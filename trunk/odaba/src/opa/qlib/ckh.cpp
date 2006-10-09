/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ckh

\brief    


\date     $Date: 2006/03/12 19:18:30,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ckh"

#include  <popa7.h>
#include  <scka.hpp>
#include  <scke.hpp>
#include  <sckh.hpp>
#include  <sckm.hpp>
#include  <skcb.hpp>
#include  <sckh.hpp>


/******************************************************************************/
/**
\brief  ckh - 



\param  kcbptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ckh"

                        ckh :: ckh (kcb *kcbptr )
                     : ckhinst(NULL), ckhkcb(kcbptr), ckhcur(UNDF), 
 ckhkey(NULL), ckhdim(AUTO), ckhopc(0), ckhcke(NULL)

{
  int16 indx = 0;
  kfc      *kfcptr = NULL;

BEGINSEQ
  if ( !kcbptr )                                      LEAVESEQ
  
//  if ( !kcbptr->scbsmcb->smcbsts.stscnof() )       
  if ( kcbptr->scbsmcb->smcbsts.stscsav() )
    while ( kfcptr = ckhkcb->GetEntry(++indx) )
      if ( kfcptr->kfcfmcbg()->fmcbdim != 1 )
        switch ( kfcptr->kfcfmcbg()->fmcbrlev )                           
        {
          case R_GENERIC : break;
          case R_REFR    : if ( !(ckhcke = new ckm(kfcptr)) ) 
                                                     SDBERR(95)
                           break;
          case R_DIRECT  : 
          default        : if ( !(ckhcke = new cka(kfcptr)) )    
                                                     SDBERR(95)
        }

  if ( !(ckhkey = new char[kcbptr->GetKeyLength()]) )     SDBERR(95)
  memset(ckhkey,' ',kcbptr->GetKeyLength());

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ckhchg - 


\return cond

\param  ckhptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ckhchg"

logical ckh :: ckhchg (ckh *ckhptr )
{
  char     *keyptr1;
  char     *keyptr2;
  int16 indx = 0;
  logical   cond = YES;

BEGINSEQ
  if ( ckhdim != ckhptr->ckhdim || !ckhdim )          LEAVESEQ
  cond = NO;

  ckhkcb->kcbkgt(ckhinst,ckhkey);
  ckhkcb->kcbkgt(ckhptr->ckhinst,ckhptr->ckhkey);
  
  if ( ckhkcb->kcbkcp(ckhkey,ckhptr->ckhkey) )    
    cond = YES;
  else
  {
//  single references are to be checked, too 

    if ( ckhcke && ckhcke->CheckMod() )
      while ( keyptr1 = ckhkget(++indx) )  
      {
        if ( !(keyptr2 = ckhptr->ckhkget(indx)) )        ERROR
        if ( ckhkcb->kcbkcp(keyptr1,keyptr2) )    
        {
          cond = YES;
          break;
        }   
      }
  }


RECOVER

ENDSEQ
  return(cond);

}

/******************************************************************************/
/**
\brief  ckhclos - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ckhclos"

logical ckh :: ckhclos ( )
{
  logical   term = NO;

BEGINSEQ
  if ( !ckhopc )                                        ERROR
  if ( !(--ckhopc) )
  {
    if ( ckhcke )
      ckhcke->CloseCKE();

// close all single reference elements      

    ckhdim = AUTO;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ckhkget - 


\return keyptr -

\param  indx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ckhkget"

char *ckh :: ckhkget (int16 indx )
{
  char     *keyptr = ckhkey;

BEGINSEQ
  if ( indx > ckhdim )                                  ERROR 

  ckhkcb->kcbkgt(ckhinst,keyptr);

  if ( ckhcke )
    if ( !ckhcke->GetKey(keyptr,ckhinst,indx) )         ERROR

// get keys from single reference elements


RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  ckhopen - 


\return count -

\param  instptr -
\param  srceinst -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ckhopen"

int8 ckh :: ckhopen (void *instptr, void *srceinst )
{

BEGINSEQ
  if ( !ckhopc )
  {
    ckhdim = 1;
    ckhinst = (char *)instptr;
  
    if ( srceinst )
      instptr = srceinst;

    if ( ckhcke )
      if ( (ckhdim = ckhcke->OpenCKE(instptr,srceinst ? YES : NO)) == AUTO )
                                                           ERROR

// for single references ckhdim becomes 0 for any empty reference !!!
  }
   
  ckhopc++;

RECOVER
  ckhdim = AUTO;
ENDSEQ
  return(ckhdim);

}

/******************************************************************************/
/**
\brief  ~ckh - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ckh"

                        ckh :: ~ckh ( )
{

  if ( ckhopc )
  {
    ckhopc = 1;
    ckhclos();
  }
   
  delete ckhkey;
  delete ckhcke;


}


