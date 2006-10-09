/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    msrt



\date     $Date: 2006/03/12 19:22:41,54 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "msrt"

#include  <pdefault.h>
#include  <csmcbmac.h>
#include  <sacc.hpp>
#include  <skcb.hpp>
#include  <smsrt.hpp>


/******************************************************************************/
/**
\brief  Compare

\return cmpval - Comparision result

\param  entry1 -
\param  entry2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compare"

int msrt :: Compare (const void *entry1, const void *entry2 )
{
  char                   *instptr;
  int                     cmpval = UNDEF;
  
  logical                 term = NO;
BEGINSEQ
  if ( !fill_opt1 )
  {
    if ( !(instptr = access->Access(*(int32 *)entry1)) )
                                                     ERROR
    strncpy(key1,instptr,key_size);
  }
  if ( !fill_opt2 )
  {
    if ( !(instptr = access->Access(*(int32 *)entry2)) )
                                                     ERROR
    strncpy(key2,instptr,key_size);
  }
  cmpval = memcmp(key1,key2,key_size);
RECOVER
  term = YES;
ENDSEQ
  if ( cmpval )
    cmpval = cmpval < 0 ? -1 : 1;  return(term);
}

/******************************************************************************/
/**
\brief  FillKey

\return term - Success

\param  entry1 -
\param  keynum -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillKey"

logical msrt :: FillKey (const void *entry1, int16 keynum )
{
  char                   *buffer = (char *)entry1;
  logical                 term = NO;
BEGINSEQ
  fill_opt1 = NO;
  fill_opt2 = NO;
  if ( !entry1 )                                     LEAVESEQ
    
  if ( keynum == 1 )
    strncpy(key1,buffer,key_size);
    
  if ( keynum == 2 )
    strncpy(key2,buffer,key_size);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  msrt


\param  kcbptr - Key definition
\param  maxe -
\param  elen -
\param  klen -
\param  kpos -
\param  expand -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "msrt"

                        msrt :: msrt (kcb *kcbptr, int32 maxe, int16 elen, int16 klen, int16 kpos, logical expand )
                     : ksrt (kcbptr,maxe,elen,klen,kpos,'M',expand),
  key1(NULL),
  key2(NULL),
  fill_opt1(NO),
  fill_opt2(NO),
  key_size(UNDEF)
{
  fmcb       *keyfmcb;
BEGINSEQ
  if ( !(keyfmcb = kcbptr->scbsmcb->smcbfmcl->GetEntry(1)) ) SOSERR(99)

  key_size = keyfmcb->fmcbsize;
  if ( !(key1 = new char[key_size]) || 
       !(key1 = new char[key_size])    )             SOSERR(95)

  access = keyfmcb->fmcbsmcb->smcbacc;
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~msrt


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~msrt"

                        msrt :: ~msrt ( )
{

  delete key1;
  delete key2;

}


