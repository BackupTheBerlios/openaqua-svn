/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    kfcl

\brief    


\date     $Date: 2006/03/12 19:22:40,15 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "kfcl"

#include  <pdefault.h>
#include  <csmcbdef.h>
#include  <csmcbmac.h>
#include  <ssmcb.hpp>
#include  <skfcl.hpp>


/******************************************************************************/
/**
\brief  Deinitialize


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinitialize"

void kfcl :: Deinitialize ( )
{
  kfc      *kfcptr;
  int16     indx = 0;
  while ( kfcptr = GetEntry(++indx) )
    kfcptr->Deinitialize();


}

/******************************************************************************/
/**
\brief  kfclesu

\return term - Success

\param  smcbptr - Structure definition block
\param  ignore -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kfclesu"

logical kfcl :: kfclesu (smcb *smcbptr, logical ignore )
{
  kfc      *kfcptr;
  fmcb     *fmcbptr;
  int16     indx = 0;
  logical   term = NO;

BEGINSEQ
  stsrerr();
  
  while ( kfcptr = GetEntry(++indx) )
  {
    if ( !(fmcbptr = smcbptr->GetEntry(kfcptr->fcbfmcb->fmcbname)) )
                                                     ERROR
    kfcptr->kfcesu(fmcbptr);
    
    kfcptr->fcbfmcb->fmcbic = ignore && (kfcptr->fcbfmcb->fmcbityp == T_CHAR   ||
                                         kfcptr->fcbfmcb->fmcbityp == T_STRING || 
                                         kfcptr->fcbfmcb->fmcbityp == T_CCHAR    );
  }
  
  if ( GetCount() == 1 && (fmcbptr = GetEntry(1)->kfcfmcb) && 
       ( !memcmp(fmcbptr->fmcbname,"#_AUTOIDENT ",12) ||
         !memcmp(fmcbptr->fmcbname,"__AUTOIDENT ",12)   ) )
    stssold();

RECOVER
  if ( SOSERROR )
    stsserr();
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  kfclkcp

\return cmpval - Comparision result

\param  area1 -
\param  area2 -
\param  cmptyp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kfclkcp"

int kfcl :: kfclkcp (char *area1, char *area2, char cmptyp )
{
  kfc           *keykfc;
  fmcb          *fmcb1;
  fmcb          *fmcb2;
  int32          offs1;
  int32          offs2;
  kcb           *kcbptr;
  short          indx   = 0;
  int            cmpval = 0;

BEGINSEQ
  if ( !this )                                       LEAVESEQ
  stsrerr();
  
  if ( !area1 || !area2 )                            ERROR
  
  while ( !cmpval && (keykfc = GetEntry(++indx)) )
  {
    fmcb1    = cmptyp == CMP_II ? keykfc->kfcfmcbg() : keykfc->fcbfmcb;
    fmcb2    = cmptyp == CMP_KK ? keykfc->fcbfmcb : keykfc->kfcfmcbg();
    offs1    = cmptyp == CMP_II ? keykfc->kfcpos : 0;
    offs2    = cmptyp == CMP_KK ? 0 : keykfc->kfcpos;
 
    switch ( fmcb1->fmcbstpg() )
    {
      case UNDEF   :
      case ST_BASE :
      case ST_CODE :
      case ST_KEY  : cmpval = fmcb1->fmcbicmp(fmcb2,area1+fmcb1->fmcbposn+offs1,
                                                    area2+fmcb2->fmcbposn+offs2);
                     break;
      case ST_SYS  :
      case ST_USER : if ( !(kcbptr = fmcb1->fmcbsmcb->smcbidky) )
                                                                 SOSSET(99)
                     cmpval = kcbptr->kcbkcp(area1+fmcb1->fmcbposn+offs1,
                                             area2+fmcb2->fmcbposn+offs2,cmptyp);
    }
  }
                                  
  if ( SOSERROR )                                    ERROR

RECOVER
  stsserr();
  cmpval = ERIC;
ENDSEQ
  return(cmpval);

}

/******************************************************************************/
/**
\brief  kfclkgt


\param  instptr - Structured instance
\param  keyptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kfclkgt"

void kfcl :: kfclkgt (char *instptr, char *keyptr )
{
  kfc       *keykfc;
  int32      indx = 0;

  while ( keykfc = GetEntry(++indx) )
    keykfc->kfckgt(instptr,keyptr);

  stsrerr();


}

/******************************************************************************/
/**
\brief  kfclkpt


\param  instptr - Structured instance
\param  keyptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kfclkpt"

void kfcl :: kfclkpt (char *instptr, char *keyptr )
{
  kfc      *keykfc;
  int32     indx = 0;
  while ( keykfc = GetEntry(++indx) )
    keykfc->kfckpt(instptr,keyptr);

  stsrerr();


}


