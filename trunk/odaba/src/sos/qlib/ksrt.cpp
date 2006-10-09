/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ksrt

\brief    


\date     $Date: 2006/03/12 19:22:40,43 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ksrt"

#include  <pdefault.h>
#include  <csmcbmac.h>
#include  <skcb.hpp>
#include  <sksrt.hpp>
#include  <sksrt.hpp>


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

int ksrt :: Compare (const void *entry1, const void *entry2 )
{
  char	    *buffer1 = (char *)entry1;
  char	    *buffer2 = (char *)entry2;
  int        cmpval  = UNDEF;

BEGINSEQ
  if ( !srtklen )                               SOSERR(5)

  switch ( srtktyp )
  {
    case 'S' : cmpval = ksrtkcbg()->kcbkcp((char *)entry1,(char *)entry2,CMP_II);
               break;
    case 'K' : cmpval = ksrtkcbg()->kcbkcp(buffer1+srtkpos-1,
                                           buffer2+srtkpos-1,
                                           CMP_KK);  
               break; 
    default  :                                  ERROR
  }

RECOVER

ENDSEQ
  return(cmpval);

}

/******************************************************************************/
/**
\brief  ExtractKey

\return keyptr -

\param  entry1 -
\param  key_area -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *ksrt :: ExtractKey (const void *entry1, char *key_area )
{
  char       *keyptr = NULL;
BEGINSEQ
  if ( !srtklen )                               SOSERR(5)

  switch ( srtktyp )
  {
    case 'S' : keyptr = ksrtkcbg()->GetKey((char *)entry1,key_area);
               break;
    case 'K' : keyptr = (char *)entry1+srtkpos-1;
               if ( key_area )
                 keyptr = (char *)memcpy(key_area,keyptr,srtklen);
               break; 
    default  :                                  ERROR
  }

RECOVER

ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  SetKey

\return keyptr -

\param  entry1 -
\param  key_area -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKey"

char *ksrt :: SetKey (const void *entry1, char *key_area )
{
  char       *keyptr = NULL;
BEGINSEQ
  if ( !srtklen )                               SOSERR(5)

  switch ( srtktyp )
  {
    case 'S' : keyptr = ksrtkcbg()->SetKey((char *)entry1,key_area);
               break;
    case 'K' : keyptr = (char *)entry1+srtkpos-1;
               if ( key_area )
                 keyptr = (char *)memcpy(keyptr,key_area,srtklen);
               break; 
    default  :                                  ERROR
  }

RECOVER

ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  ksrt

-------------------------------------------------------------------------------
\brief KSRT_


\param  kcbptr - Key definition
\param  maxe -
\param  elen -
\param  klen -
\param  kpos -
\param  ktype -
\param  expand -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ksrt"

                        ksrt :: ksrt (kcb *kcbptr, int32 maxe, int16 elen, int16 klen, int16 kpos, char ktype, logical expand )
                     : srt(maxe,elen,klen,kpos,ktype,expand),
 ksrtkcb(kcbptr)

{

BEGINSEQ
  srtktyp = ktype;
  if ( ksrtchk() )                                   ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief KSRT_C


\param  ksrtptr -
\param  ecnt -
\param  elen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ksrt"

                        ksrt :: ksrt (ksrt *ksrtptr, int32 ecnt, int16 elen )
                     : srt(ksrtptr,ecnt,elen),
 ksrtkcb(ksrtptr->ksrtkcb)

{

BEGINSEQ
  srtktyp = ksrtptr->srtktyp;
  if ( ksrtchk() )                                   ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief KSRT_D


\param  kcbptr - Key definition
\param  ecnt -
\param  elen -
\param  klen -
\param  kpos -
\param  ktype -
\param  table_ptr -
\param  expand -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ksrt"

                        ksrt :: ksrt (kcb *kcbptr, int32 ecnt, int16 elen, int16 klen, int16 kpos, char ktype, char *table_ptr, logical expand )
                     : srt(ecnt,elen,klen,kpos,ktype,table_ptr,expand),
 ksrtkcb(kcbptr)

{

BEGINSEQ
  srtktyp = ktype;
  if ( ksrtchk() )                                   ERROR


RECOVER


ENDSEQ

}

/******************************************************************************/
/**
\brief KSRT_I


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ksrt"

                        ksrt :: ksrt ( )
                     : srt(),
 ksrtkcb(NULL)

{



}

/******************************************************************************/
/**
\brief  ksrtchk

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ksrtchk"

logical ksrt :: ksrtchk ( )
{
  logical   term = NO;

BEGINSEQ
  stsrerr();
  
  switch ( srtktyp )
  {
    case 'C'   :
    case 'I'   :
    case 'P'   :
//  case 'F'   :
    case UNDEF : break;
    case 'K'   :
    case 'S'   : if ( !ksrtkcb )                     SOSERR(9)
                 srtklen = ksrtkcb->kcbklng();
                 break;
    default    : srtktyp = UNDEF;                                    
  }

  if ( srtktyp && !srtklen )                         SOSERR(5)

RECOVER
  stsserr();
  char   string[60];
  gvtxbts(string,ksrtkcb->scbsmcb->smcbname,ID_SIZE);
  SOSError().TraceMessage(string);
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ksrtkcbg

\return ksrtkcb

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ksrtkcbg"

kcb *ksrt :: ksrtkcbg ( )
{

  stsrerr(); 

  return(ksrtkcb);
}

/******************************************************************************/
/**
\brief  ~ksrt


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ksrt"

                        ksrt :: ~ksrt ( )
{



}


