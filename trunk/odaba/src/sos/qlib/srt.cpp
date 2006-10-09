/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    srt

\brief    Ordered list
          Ordered  lists are  lists of  entries that  are ordered according to a
          value in the list or according to a component key.

\date     $Date: 2006/06/21 13:16:13,39 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "srt"

#include  <pdefault.h>
#include  <ckeycmp.h>
#include  <csmcbmac.h>
#include  <iNetConversion.h>
#include  <sRessourceLock.hpp>
#include  <sfmcb.hpp>
#include  <skcb.hpp>
#include  <sksrt.hpp>
#include  <ssrt.hpp>
#include  <ssrt.hpp>


/******************************************************************************/
/**
\brief  CheckError - 


\return errcd - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckError"

int srt :: CheckError ( )
{

  return(stscerr());


}

/******************************************************************************/
/**
\brief  Compare - 


\return cmpval - Comparision result

\param  entry1 - 
\param  entry2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Compare"

int srt :: Compare (const void *entry1, const void *entry2 )
{
  char	    *buffer1 = (char *)entry1;
  char	    *buffer2 = (char *)entry2;
  int        cmpval  = UNDEF;
  char      *cint1;
  char      *cint2;
  int16     *sint1;
  int16     *sint2;
  int32     *lint1;
  int32     *lint2;
  int64     *llint1;
  int64     *llint2;
  char      *cptr1;
  char      *cptr2;
  float     *fint1;
  float     *fint2;
  double    *dint1;
  double    *dint2;
BEGINSEQ
  if ( !srtklen )                               SOSERR(5)

  switch ( srtktyp )
  {
    case 'C' : cmpval = memcmp(buffer1+srtkpos-1,
                               buffer2+srtkpos-1,
                               srtklen      );
               break;
    case 'V' : cmpval = strcmp(buffer1+srtkpos-1,
                               buffer2+srtkpos-1);
               break;
    case 'I' : switch ( srtklen )
               {
                 case 1  : cint1  = buffer1+srtkpos-1;
                           cint2  = buffer2+srtkpos-1;
                           cmpval = ( *cint1 > *cint2 ) - ( *cint1 < *cint2 );
                           break;
                 case 2  : sint1  = (int16 *)(buffer1+srtkpos-1);
                           sint2  = (int16 *)(buffer2+srtkpos-1);
                           cmpval = ( *sint1 > *sint2 ) - ( *sint1 < *sint2 );
                           break;
                 case 4  : lint1  = (int32 *)(buffer1+srtkpos-1);
                           lint2  = (int32 *)(buffer2+srtkpos-1);
                           cmpval = ( *lint1 > *lint2 ) - ( *lint1 < *lint2 );
                           break;
                 case 8  : llint1 = (int64 *)(buffer1+srtkpos-1);
                           llint2 = (int64 *)(buffer2+srtkpos-1);
                           cmpval = ( *llint1 > *llint2 ) - ( *llint1 < *llint2 );
                           break;
                 default :                                   ERROR
	       }
               break;
    case 'c' : cptr1   = *(char **)(buffer1+srtkpos-1);
               cptr2   = *(char **)(buffer2+srtkpos-1);
               cmpval = memcmp(cptr1,cptr2,srtklen);
               break;
    case 'v' : cptr1   = *(char **)(buffer1+srtkpos-1);
               cptr2   = *(char **)(buffer2+srtkpos-1);
               cmpval = strcmp(cptr1,cptr2);
               break;
    case 'S' : 
    case 'K' : cmpval = ((ksrt *)this)->Compare(entry1,entry2);
               break; 
//    case 'M' : cmpval = ((msrt *)this)->Compare(entry1,entry2);
//               break; 
    case 'F' : switch ( srtklen )
               {
                 case 4  : fint1  = (float *)(buffer1+srtkpos-1);
                           fint2  = (float *)(buffer2+srtkpos-1);
                           cmpval = ( *fint1 > *fint2 ) - ( *fint1 < *fint2 );
                 case 8  : dint1  = (double *)(buffer1+srtkpos-1);
                           dint2  = (double *)(buffer2+srtkpos-1);
                           cmpval = ( *dint1 > *dint2 ) - ( *dint1 < *dint2 );
		 default :                                 ERROR
	       }
	       break;
    default  :                                             ERROR
  }

RECOVER

ENDSEQ
  if ( cmpval )
    cmpval = cmpval < 0 ? -1 : 1;
  return(cmpval);

}

/******************************************************************************/
/**
\brief  EntryFromPIF - 


\return term - Success

\param  indx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EntryFromPIF"

logical srt :: EntryFromPIF (int16 indx )
{
  char                   *entry;
  logical                 term = NO;
BEGINSEQ
  switch ( srtktyp )
  {
    case 'I' : if ( srtklen > 1 )
                 break;
    case 'C' :
    case 'V' : 
    case 'c' : 
    case 'v' : 
    case UNDEF: 
    case 'F' : LEAVESEQ
  }
  
  entry = (srtenty + (indx-1) * srtelen) +srtkpos-1;
  switch ( srtktyp )
  {
    case 'I' : switch ( srtklen )
               {
                 case 2  : *(int16 *)entry = PIFToShort(*(int16 *)entry,YES);
                           break;
                 case 4  : *(int32 *)entry  = PIFToLong(*(int32 *)entry,YES);
                           break;
                 case 8  : *(int64 *)entry   = PIFToBig(*(int64 *)entry,YES);
                           break;
                 default : SOSERR(99)
               }
               break;
    case 'S' : 
    case 'K' : ((ksrt *)this)->ksrtkcbg()->FromPIF(entry,YES);
               break; 
    default  : SOSERR(99)
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EntryToPIF - 


\return term - Success

\param  indx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EntryToPIF"

logical srt :: EntryToPIF (int16 indx )
{
  char                   *entry;
  logical                 term = NO;
BEGINSEQ
  switch ( srtktyp )
  {
    case 'I' : if ( srtklen > 1 )
                 break;
    case 'C' :
    case 'V' : 
    case 'c' : 
    case 'v' : 
    case UNDEF: 
    case 'F' : LEAVESEQ
  }
  
  entry = (srtenty + (indx-1) * srtelen) +srtkpos-1;
  switch ( srtktyp )
  {
    case 'I' : switch ( srtklen )
               {
                 case 2  : *(int16 *)entry = ShortToPIF(*(int16 *)entry,YES);
                           break;
                 case 4  : *(int32 *)entry  = LongToPIF(*(int32 *)entry,YES);
                           break;
                 case 8  : *(int64 *)entry   = BigToPIF(*(int64 *)entry,YES);
                           break;
                 default : SOSERR(99)
               }
               break;
    case 'S' : 
    case 'K' : ((ksrt *)this)->ksrtkcbg()->ToPIF(entry,YES);
               break; 
    default  : SOSERR(99)
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExtractKey - 


\return keyptr - 

\param  entry1 - 
\param  key_area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractKey"

char *srt :: ExtractKey (const void *entry1, char *key_area )
{
  char                   *keyptr;
BEGINSEQ
  if ( !srtklen )                               SOSERR(5)

  switch ( srtktyp )
  {
    case 'S' : 
    case 'K' : keyptr = ((ksrt *)this)->ExtractKey(entry1,key_area);
               break; 
    default  : keyptr = ((char *)entry1)+srtkpos-1;
  }

RECOVER

ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  FreeTable - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeTable"

logical srt :: FreeTable ( )
{

  if ( !srtind )
    msmfs((void **)&srtenty);

  return(NO);
}

/******************************************************************************/
/**
\brief  FromPIF - Convert from platform independent format (PIF)
        Plattform  independent  applications  may  store  the list in a platform
        indipendent  format  (PIF),  which  requires conversion before using the
        table.  The  table  is  automatically  converted into platform dependent
        format, when being used the first time.

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromPIF"

logical srt :: FromPIF ( )
{
  int                     indx = 0;
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SOSERR(99)

  switch ( srtktyp )
  {
    case 'I' : if ( srtklen > 1 )
                 break;
    case 'C' :
    case 'V' : 
    case 'c' : 
    case 'v' : 
    case UNDEF: 
    case 'F' :   LEAVESEQ
  }
  
  while ( indx++ < srtecnt )
    if ( EntryFromPIF(indx) )                        ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Success

\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical srt :: Lock (logical wait )
{

  return(this ? srt_lock->ILock(wait) : YES);

}

/******************************************************************************/
/**
\brief  ToPIF - Convert to platform independent format (PIF)
        Plattform  independent  applications  may  store  the list in a platform
        indipendent  format  (PIF).  The  table must be explicitely converted to
        PIF before storing it.

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToPIF"

logical srt :: ToPIF ( )
{
  int                     indx = 0;
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       SOSERR(99)

  switch ( srtktyp )
  {
    case 'I' : if ( srtklen > 1 )
                 break;
    case 'C' :
    case 'V' : 
    case 'c' : 
    case 'v' : 
    case UNDEF: 
    case 'F' : LEAVESEQ
  }
  
  while ( indx++ < srtecnt )
    if ( EntryToPIF(indx) )                          ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical srt :: Unlock ( )
{

  return(this ? srt_lock->IUnlock(): YES);

}

/******************************************************************************/
/**
\brief  srt - 


-------------------------------------------------------------------------------
\brief  SRT_ - 


\param  maxe - 
\param  elen - 
\param  klen - 
\param  kpos - 
\param  ktype - 
\param  expand - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srt"

     srt :: srt (int32 maxe, int16 elen, int16 klen, int16 kpos, char ktype, logical expand )
                     : srtmaxe(maxe), srtecnt(0), srtelen(elen),
 srtklen(MAX(klen,0)), srtkpos(MAX(kpos,0)), srtktyp(ktype),
 srtind(NO), srtexp(expand), 
srtenty(NULL), srt_lock(NULL)

{

  srtini();


}

/******************************************************************************/
/**
\brief  SRT_C - 


\param  srtptr - 
\param  fcnt - 
\param  elen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srt"

     srt :: srt (srt *srtptr, int16 fcnt, int16 elen )
                     : srtmaxe(srtptr->srtecnt+fcnt), srtecnt(0), 
 srtelen(elen), srtklen(srtptr->srtklen), srtkpos(srtptr->srtkpos), 
 srtktyp(srtptr->srtktyp), srtind(NO), 
 srtexp(srtptr->srtexp),
 srt_lock(NULL)

 

{
  char      *targ;
  char      *srce;
  int32      ecnt;
  int16      i; 

BEGINSEQ
  if ( srtini() )                                    ERROR

  ecnt = MIN(srtmaxe,srtptr->srtecnt);
  elen = MIN(srtelen,srtptr->srtelen);

  for ( i=0, targ = srtenty, srce = srtptr->srtenty;
	i < ecnt;
	i++, targ+=srtelen, srce+=srtptr->srtelen        )
    memcpy(targ,srce,(int)elen);

  srtecnt = ecnt;
  stssfil();

  SOSRESET

RECOVER
  stsserr();
ENDSEQ

}

/******************************************************************************/
/**
\brief  SRT_D - 


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
#define    MOD_ID  "srt"

     srt :: srt (int32 ecnt, int16 elen, int16 klen, int16 kpos, char ktype, char *table_ptr, logical expand )
                     : srtmaxe(ecnt), srtecnt(ecnt), srtelen(elen),
 srtklen(MAX(klen,0)), srtkpos(MAX(kpos,0)), srtktyp(ktype),
 srtind(YES), srtexp(expand), 
 srtenty(table_ptr),
 srt_lock(NULL)


{

BEGINSEQ
  srt_lock = new RessourceLock(NO);
  if ( ecnt < 0 )                                    SOSERR(7)
  if ( srtchk() )                                    ERROR
  stssfil();

  SOSRESET

RECOVER
  stsserr();
ENDSEQ

}

/******************************************************************************/
/**
\brief  SRT_I - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srt"

     srt :: srt ( )
                     : sts(),
 srtmaxe(0), srtecnt(0), srtelen(0),
 srtklen(0), srtkpos(0), srtktyp(UNDEF), srtexp(NO),
 srtind(NO), srtenty(NULL),
 srt_lock(NULL)


{

  srt_lock = new RessourceLock(NO);


}

/******************************************************************************/
/**
\brief  SRT_S - 


\param  codset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srt"

     srt :: srt (char **codset )
                     : srtmaxe(0), srtecnt(-1), srtelen(0), 
 srtklen(0), srtkpos(0), srtktyp(UNDEF), srtind(NO), srtexp(NO), 
 srt_lock(NULL)


{
  char        buffer[33];

  while ( codset[++srtecnt] )
    srtelen = MAX(srtelen,(short int)strlen(codset[srtecnt])+1);

  buffer[0] = (char)(srtelen-1);

  if ( !srtini() )         
  {
    for ( short int i=0; i < srtecnt; i++ )
      srtiad(i+1,gvtxstb(buffer+1,codset[i],srtelen-1)-1);

    stssfil();
  }


}

/******************************************************************************/
/**
\brief  srtbsr - 


\return lindx - 

\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtbsr"

int32 srt :: srtbsr (void *skey )
{
  char          cmpval = ERIC;
  register int  cur  = 0;
  register int  low  = 0;
  int           lc   = 0;
  int           rc   = 0;
  register int  high = srtecnt-1;

BEGINSEQ
  if ( !this || !srtenty )                           ERROR
  
  stsrerr();
  
  if ( !srtklen )                                    SOSERR(5)
  if ( !srtecnt )                                    ERROR

  while ( !( ( cmpval == 1 && cur >= high-rc ) || 
             ( cmpval == -1 && cur <= low+lc )    ) )
  {           
    cur=(high+low)/2;           
    cmpval = srtkcp(skey,srtenty+cur*srtelen);

    switch ( cmpval )
    {           
      case 0 : LEAVESEQ           
      case 1 : low = cur == low ? high : cur;
               lc = 1;
               break;           
      case -1: high = cur == high ? low : cur;
               rc = 1;
               break;
      default: ;
    }           
  } 

  if ( cmpval == 1 )           
    if ( ++cur >= srtecnt )                          ERROR

RECOVER
  stsserr();
  cur = -1;
ENDSEQ
  if ( cmpval )
    stsserr();
  return(++cur);

}

/******************************************************************************/
/**
\brief  srtchk - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtchk"

logical srt :: srtchk ( )
{
  int       term = NO;

BEGINSEQ
  stsrerr();
  if ( srtmaxe < 0  ||  srtelen <= 0 )               SOSERR(3)

  switch ( srtktyp )
  {
    case 'V'   :
    case 'v'   :
    case 'C'   :
    case 'c'   :
    case 'I'   :
    case 'P'   :
//  case 'F'   :
    case UNDEF : break;
    default    : srtktyp = UNDEF;                                    
  }

RECOVER
  stsserr();
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  srtcnt - 


\return srtecnt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtcnt"

int32 srt :: srtcnt ( )
{

  return(srtecnt);

}

/******************************************************************************/
/**
\brief  srtfad - 


\return entry_area - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtfad"

void *srt :: srtfad ( )
{
  int32        maxe  = srtmaxe;
  void        *entry = NULL;

BEGINSEQ
  if ( !this )                                       SOSERR(99)

  stsrerr();
  if ( srtecnt >= srtmaxe )
    if ( !srtexp || srtsch(maxe+=MAX(maxe/10,1)) < maxe )
                                                     ERROR
  entry = srtenty + srtecnt++ * srtelen;

RECOVER

ENDSEQ
  return(entry);

}

/******************************************************************************/
/**
\brief  srtfgt - 


\return entry_area - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtfgt"

void *srt :: srtfgt ( )
{
  void        *entry = NULL;
BEGINSEQ
  if ( !this || !srtenty )                           ERROR
  
  stsrerr();
  if ( srtecnt >= srtmaxe )                          ERROR

  entry = srtenty + srtecnt * srtelen;


RECOVER

ENDSEQ
  return(entry);
}

/******************************************************************************/
/**
\brief  srtiad - 


\return term - Success

\param  lindx - 
\param  entry_area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtiad"

logical srt :: srtiad (int32 lindx, void *entry_area )
{
  int32         maxe = srtmaxe;
  char         *entry;
  register int  j;
  logical       term = NO;

BEGINSEQ
  if ( !this )                                       SOSERR(99)

  stsrerr();
  if ( lindx <= 0  || --lindx > srtecnt  )           SOSERR(3)

  if ( srtecnt >= srtmaxe )
    if ( !srtexp || srtsch(maxe+=MAX(maxe/10,1)) < maxe )  
                                                     ERROR
  for( j = srtecnt,
       entry = srtenty + srtecnt * srtelen;
       j > lindx;
       j--, entry-=srtelen )
    memcpy( entry, entry - srtelen, (int) srtelen );

  if ( entry_area )
    memcpy(entry,entry_area,(int)srtelen );
  else
    memset(entry,0,(int)srtelen );
  srtecnt++;

RECOVER
  if ( SOSERROR )
    stsserr();
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  srtidl - 


\return term - Success

\param  lindx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtidl"

logical srt :: srtidl (int32 lindx )
{
  logical    term = NO;

BEGINSEQ
  if ( !this || !srtenty )                           ERROR
  
  stsrerr();
  if ( lindx > srtecnt  ||  lindx <= 0 )           SOSERR(3)

  memcpy ( srtenty + (lindx-1) * srtelen,
	   srtenty + lindx * srtelen,
	   (int) ((srtecnt - lindx) * srtelen)    );

  srtecnt--;

RECOVER
  if ( this ) stsserr();
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  srtigt - 


\return entry_area - 

\param  lindx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtigt"

void *srt :: srtigt (int32 lindx )
{
  void     *datarea = NULL;

BEGINSEQ
  if ( !this || !srtenty )                           ERROR
  
  stsrerr();
  if ( lindx <= 0  ||  lindx > srtecnt )             ERROR

  datarea = srtenty + (lindx-1) * srtelen;

RECOVER

ENDSEQ
  return(datarea);

}

/******************************************************************************/
/**
\brief  srtini - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtini"

logical srt :: srtini ( )
{
  int32     len  = ((int32)srtelen)*(int32)srtmaxe;
  logical   term = NO;

BEGINSEQ
  if ( !srt_lock )
    srt_lock = new RessourceLock(NO);

  if ( srtchk() )                                    ERROR

  if ( srtmaxe && !srtenty )
  {
    if ( !(srtenty = (char *)msmgs(len)) )           ERROR
    srtind = NO; // table muss freigegeben werden
  }
  stssini();
  SOSRESET

RECOVER
  stsserr();
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  srtiup - 


\return entry_area - 

\param  entry_area - 
\param  lindx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtiup"

void *srt :: srtiup (void *entry_area, int32 lindx )
{

BEGINSEQ
  if ( !this || !srtenty )                           ERROR
  
  stsrerr();
  if ( lindx <= 0  ||  lindx > srtecnt )             SOSERR(3)

  entry_area = memcpy(srtenty + (lindx-1) * srtelen,entry_area,(int)srtelen);

RECOVER
  stsserr();
  entry_area = NULL;
ENDSEQ
  return(entry_area);

}

/******************************************************************************/
/**
\brief  srtkad - 


\return lindx - 

\param  entry_area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtkad"

int32 srt :: srtkad (void *entry_area )
{
  char          key_area[MAX_KEYLEN];
  register int  indx;

BEGINSEQ
  if ( !this )                                       SOSERR(99)
  if ( !srtklen )                                    SOSERR(5)

  if ( !(indx = srtbsr(srtktyp == 'S' ? ((ksrt *)this)->ksrtkcbg()->kcbkgt((char *)entry_area,key_area)
                                      : (char *)entry_area+srtkpos-1)) )
    indx = srtecnt+1;

  if ( !stscerr() )                                  SOSERR(4)
  stsrerr();

  if ( srtiad(indx,entry_area) )                     ERROR

RECOVER
  stsserr();
  indx = 0;
ENDSEQ
  return(indx);

}

/******************************************************************************/
/**
\brief  srtkcp - 


\return cmpval - Comparision result

\param  skey - 
\param  entry_area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtkcp"

int srt :: srtkcp (void *skey, void *entry_area )
{

  return ( srtktyp == 'S' ? ((ksrt *)this)->ksrtkcbg()->kcbkcp((char *)skey,(char *)entry_area,CMP_KI)
                          : Compare((char *)skey-(srtkpos - 1),entry_area) );


}

/******************************************************************************/
/**
\brief  srtkln - 


\return srtklen - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtkln"

int16 srt :: srtkln ( )
{

  return(srtklen);

}

/******************************************************************************/
/**
\brief  srtkps - 


\return srtkpos - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtkps"

int16 srt :: srtkps ( )
{

  return(srtkpos);

}

/******************************************************************************/
/**
\brief  srtktp - 


\return srtktyp - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtktp"

char srt :: srtktp ( )
{

  return(srtktyp);

}

/******************************************************************************/
/**
\brief  srtlen - 


\return srtelen - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtlen"

int16 srt :: srtlen ( )
{

  return(srtelen);

}

/******************************************************************************/
/**
\brief  srtmax - 


\return srtmaxe - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtmax"

int32 srt :: srtmax ( )
{

  return(srtmaxe);

}

/******************************************************************************/
/**
\brief  srtres - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtres"

void srt :: srtres ( )
{

  if ( this )
    srtecnt = 0;

}

/******************************************************************************/
/**
\brief  srtsch - 


\return maxe - 

\param  maxe - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtsch"

int32 srt :: srtsch (int32 maxe )
{
  int32     size = 0;

BEGINSEQ
  stsrerr();
  if ( maxe < srtecnt )                              SOSERR(8)

  size = maxe*srtelen;
    
  if ( srtenty )
  {
    if ( !(size = msmcs((void **)&srtenty,size)) )   ERROR
  }
  else
    if ( !(srtenty = (char *)msmgs(size)) )          ERROR

  if ( (size = srtmaxe = size/srtelen) < 0 )         SOSERR(8)

RECOVER
  if ( SOSERROR )
    stsserr();
ENDSEQ
  return (size);

}

/******************************************************************************/
/**
\brief  srtset - 


\return term - Success

\param  maxe - 
\param  elen - 
\param  klen - 
\param  kpos - 
\param  ktype - 
\param  expand - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtset"

logical srt :: srtset (int32 maxe, int16 elen, int16 klen, int16 kpos, char ktype, logical expand )
{

  srtmaxe = maxe;
  srtecnt = 0;
  srtelen = elen;
  srtklen = MAX(klen,0);
  srtkpos = MAX(kpos,0);
  srtktyp = ktype; 
  srtind  = NO;
  srtexp  = expand;           

  return( srtini() );


}

/******************************************************************************/
/**
\brief  srtsetc - 



\param  ecnt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtsetc"

void srt :: srtsetc (int32 ecnt )
{

  srtecnt = ecnt;

}

/******************************************************************************/
/**
\brief  srtsete - 



\param  tbllen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtsete"

void srt :: srtsete (int32 tbllen )
{

 srtecnt = (short int)(tbllen/srtelen);

}

/******************************************************************************/
/**
\brief  srtsetm - 



\param  maxe - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtsetm"

void srt :: srtsetm (int32 maxe )
{

  srtmaxe = maxe;

}

/******************************************************************************/
/**
\brief  srtsett - 



\param  tblptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtsett"

void srt :: srtsett (void *tblptr )
{

  srtenty = (char *)tblptr;

}

/******************************************************************************/
/**
\brief  srtsind - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtsind"

void srt :: srtsind ( )
{

  srtind = YES;

}

/******************************************************************************/
/**
\brief  srtsor - 


\return term - Success

\param  kpos - 
\param  klen - 
\param  ktype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtsor"

logical srt :: srtsor (int16 kpos, int16 klen, char ktype )
{
  extern     srt  *c_srtpt;

  logical    term = NO;

BEGINSEQ
  if ( Lock() )                                        SOSERR(99)

  stsrerr();

  if ( klen )
    srtklen = klen;
  if ( kpos )
    srtkpos = kpos;
  if ( ktype )
    srtktyp = ktype;

  if ( !srtklen )                                    SOSERR(5)

  c_srtpt = this;

  SOSRESET
  qsort(srtenty,srtecnt,srtelen,(int(__cdecl *)(const void *,const void *))srtcmp);
  
  SOSCERR

RECOVER
  stsserr();
  term = YES;
ENDSEQ
  Unlock();
  return(term);

}

/******************************************************************************/
/**
\brief  srtssr - 


\return lindx - 

\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srtssr"

int32 srt :: srtssr (void *skey )
{
  int32       indx = 0;

BEGINSEQ
  if ( Lock() )                                      ERROR

  indx = srtbsr(skey);
  if ( stscerr() )
  {
    stsrerr();
    indx = 0;
  }
  Unlock();
RECOVER

ENDSEQ
  return(indx);

}

/******************************************************************************/
/**
\brief  srttbl - 


\return tblptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "srttbl"

void *srt :: srttbl ( )
{

  return(srtenty);

}

/******************************************************************************/
/**
\brief  ~srt - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~srt"

     srt :: ~srt ( )
{

  FreeTable();
  delete srt_lock;
  srt_lock = NULL;

}


