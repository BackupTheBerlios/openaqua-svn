/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    rvr



\date     $Date: 2006/05/18 13:28:39,32 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "rvr"

#include  <popa7.h>
#include  <fileacc.h>
#include  <sacb.hpp>
#include  <srvre.hpp>
#include  <srvrh.hpp>
#include  <ssvel.hpp>
#include  <stim.hpp>
#include  <srvr.hpp>


/******************************************************************************/
/**
\brief  Close


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void rvr :: Close ( )
{
  if ( rvrfile )
  {
    lseek(rvrfile,0,SEEK_END);
    close(rvrfile);
    rvrfile = 0;
  }

}

/******************************************************************************/
/**
\brief  DeleteFile

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteFile"

logical rvr :: DeleteFile ( )
{
  char         path[128];
  logical      term = NO;

BEGINSEQ
  if ( rvrfncr(path) )                               ERROR
    
  remove(path);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetEntryLength

\return entlen - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntryLength"

int32 rvr :: GetEntryLength ( )
{
  rvre     *rvreptr = (rvre *)rvrwork;
  int32      len     = RVRE + rvreptr->rvreulen;

  if ( rvreptr->rvreinst )
    len += ((acb *)(rvrwork + len))->get_acbieh().get_iehlen() + ACB;
  else
    len += rvreptr->rvreelen;
  return(len);
}

/******************************************************************************/
/**
\brief  GetFixedLength

\return len - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFixedLength"

int32 rvr :: GetFixedLength ( )
{
  rvre     *rvreptr = (rvre *)rvrwork;

  return (RVRE+rvreptr->rvreulen+rvreptr->rvreinst*ACB);

}

/******************************************************************************/
/**
\brief  GetNext

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNext"

logical rvr :: GetNext ( )
{
  rvrh      rvrhdr;
  logical   term = NO;

BEGINSEQ
  SDBRESET

  if ( !rvrpos )
  {
    lseek(rvrfile,0,SEEK_SET);
    if ( read(rvrfile,(void *)&rvrhdr,sizeof(rvrh)) != sizeof(rvrh) ) 
                                                     SDBERR(1)
    if ( memcmp(&rvrhdr,"RVRH",4) )                  SDBERR(1)
    rvrpos = sizeof(rvrh);    
  }
  else
    rvrpos += GetEntryLength();

  if ( rvrrdh() )                                    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  GetWorkInst

\return acbptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkInst"

acb *rvr :: GetWorkInst ( )
{
  rvre       *rvreptr = (rvre *)rvrwork;
  acb        *acbptr = (acb *)(rvrwork+RVRE+rvreptr->rvreulen);
  int         len    = ACB + acbptr->get_acbieh().get_iehlen();
BEGINSEQ
  if ( rvriwlen < len )
  {
    delete rvrwint;
    rvrwint = NULL;
  }
  
  if ( !rvrwint )
    if ( !(rvrwint = new char[rvriwlen = len]) )    SDBERR(95)

  memcpy(rvrwint,acbptr,ACB);
  acbptr = (acb *)rvrwint;
RECOVER
  acbptr = NULL;
ENDSEQ
  return(acbptr);
}

/******************************************************************************/
/**
\brief  IsOpened

\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOpened"

logical rvr :: IsOpened ( )
{

  return ( rvrfile ? YES : NO );

}

/******************************************************************************/
/**
\brief  Lock

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical rvr :: Lock ( )
{
  register  int  i = 100;
  logical   term = NO;

BEGINSEQ
  if ( rvrnet ) 
  { 
    term = YES;
    if ( lseek(rvrfile,0,SEEK_SET) < 0 )	   SDBERR(1)

    while ( term && i-- )
    {
#ifdef __unix__
      term = NO;
#else
      term = _locking(rvrfile,_LK_LOCK,4);
#endif      
      if ( term )
      	tim::timestp(1);
    }
    if ( term )                            	    SDBERR(6)
  }

RECOVER


ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Open

\return term - Termination code

\param  recnum - Numer of recovery file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical rvr :: Open (uint16 recnum )
{
  char         path[128];
  logical      term = NO;
BEGINSEQ
  if ( recnum )
    rvrnum = recnum;
  
  if ( rvrfncr(path) )                               ERROR
  if ( rvrfopn(path) )                               ERROR
  rvrsup(NULL,0);

  if ( !fillength(rvrfile) && rvrout )
    rvrinit();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Read

\return extinst - 

\param  extinst - 
\param  extlen - External length
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

char *rvr :: Read (char *extinst, int32 extlen, int32 offset )
{
  rvre     *rvreptr = (rvre *)rvrwork;
  int32      position;
  int32      len;

BEGINSEQ
  SDBRESET

  if ( !rvrpos )                                        ERROR
  
  position = rvrpos + GetFixedLength();
  len = extlen == AUTO ? rvreptr->rvreelen : extlen;

  if ( lseek(rvrfile,position,SEEK_SET) == -1L )    SDBERR(1)
  if ( read(rvrfile,extinst,(int)len) != (int)len ) SDBERR(1)

RECOVER
  extinst = NULL;
ENDSEQ
  return(extinst);

}

/******************************************************************************/
/**
\brief  StartTA

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartTA"

logical rvr :: StartTA ( )
{
  logical     term = NO;
BEGINSEQ
  if ( Lock() )                                      ERROR
  rvrtastart = fillength(rvrfile);

  if ( Write(NULL,0,'B',0) )                         ERROR

RECOVER
  Unlock();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StopTA

\return pos

\param  error - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopTA"

int64 rvr :: StopTA (logical error )
{
  int32        pos = rvrtastart;
BEGINSEQ
  if ( Write(NULL,0,error ? 'C' : 'E',0) )           SDBERR(99)
  
#ifndef __unix__  
  if ( _commit(rvrfile) == -1 )                      SDBERR(99)
#endif  

RECOVER
  pos = AUTO;
ENDSEQ
  Unlock();
  rvrtastart = AUTO;
  return(pos);
}

/******************************************************************************/
/**
\brief  TA_Next

\return acbptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TA_Next"

acb *rvr :: TA_Next ( )
{
  rvre     *rvreptr  = (rvre *)rvrwork;
  acb      *acbptr   = NULL;
BEGINSEQ
  while ( !acbptr ) 
  {
    if ( GetNext() )                                 ERROR
    if ( rvreptr->rvreoper == 'E' || rvreptr->rvreoper == 'C' )
                                                     LEAVESEQ
      
    if ( rvreptr->rvreinst )
    {
      if ( !(acbptr = GetWorkInst()) )               ERROR
      if ( !Read((char *)(acbptr+1),
                acbptr->get_acbieh().get_iehlen(),
                0) )                                 ERROR
      if ( rvreptr->rvreoper == 'D' )
        acbptr->stssdel();
    }
  }

RECOVER
  acbptr = NULL;
ENDSEQ
  return(acbptr);
}

/******************************************************************************/
/**
\brief  TA_Top

\return term - Termination code

\param  position - Position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TA_Top"

logical rvr :: TA_Top (int32 position )
{
  logical     term = NO;
BEGINSEQ
  SDBRESET

  rvrpos = position;
  
  if ( rvrrdh() )                                    ERROR
  
  if ( ((rvre *)rvrwork)->rvreoper != 'B' )          SDBERR(1)


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Unlock

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical rvr :: Unlock ( )
{
  logical   term = NO;

BEGINSEQ
  if ( rvrnet ) 
  { 
    if ( lseek(rvrfile,0,SEEK_SET) < 0 )	   SDBERR(1)
#ifdef __unix__
#else
    if ( _locking(rvrfile,_LK_UNLCK,4) )           SDBERR(6)
#endif  
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Write

\return term - Termination code

\param  acbptr - 
\param  extlen - External length
\param  opera - 
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical rvr :: Write (acb *acbptr, int32 extlen, char opera, int32 offset )
{
  rvre     *rvreptr = (rvre *)rvrwork;
  logical   term = NO;

BEGINSEQ
  if ( !rvrfile )                                     LEAVESEQ

  rvreptr->rvredat  = dbdt().SetDate().GetLongInt();
  rvreptr->rvretim  = dbtm().SetTime().GetLongInt();
  rvreptr->rvreelen = extlen;
  rvreptr->rvreeoff = offset;
  rvreptr->rvreinst = acbptr ? YES : NO;
  rvreptr->rvreulen = rvruil;
  rvreptr->rvreoper = opera;

  if ( rvruil )
    memcpy(rvreptr->rvreuser,rvruser,rvruil);

  if ( rvrwt(rvrwork,RVRE+rvruil) )                  ERROR
  if ( rvreptr->rvreinst )
    if ( rvrwt(acbptr,sizeof(acb)+acbptr->get_acbieh().get_iehlen()) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  rvr


\param  recpath - Recovery path
\param  recnum - Numer of recovery file
\param  userinfo - Area for application recovery information
\param  uilen - Length of application data area
\param  w_netopt - Multi-user option
\param  w_outopt - 
\param  w_app - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rvr"

     rvr :: rvr (char *recpath, uint16 recnum, char *userinfo, int16 uilen, logical w_netopt, logical w_outopt, logical w_app )
                     :   rvrnum(recnum), 
  rvrfile(0), 
  rvrnet(w_app ? w_netopt : NO), 
  rvruser(userinfo), 
  rvruil(uilen), 
  rvrwork(NULL), 
  rvrpos(0), 
  rvrout(w_outopt),
  rvrapp(w_app),
  rvrtastart(AUTO),
  rvrwint(NULL),
  rvriwlen(0)
{
  logical   term = NO;

BEGINSEQ
  if ( recnum || !rvrapp )
  {
    if ( strlen(recpath) > sizeof(rvrpath)-1 )     SDBERR(99)
    strcpy(rvrpath,recpath);
    ReplaceSysVariable(rvrpath,sizeof(rvrpath));
  }
  
  if ( recnum && rvrapp )
  {
    rvrsup(userinfo,uilen);
    if ( Open(0) )                                 ERROR
  }

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  rvrcrt

\return recnum - Numer of recovery file

\param  recpath - Recovery path
\param  recnum - Numer of recovery file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rvrcrt"

uint16 rvr :: rvrcrt (char *recpath, uint16 recnum )
{
  rvrh      rvrhdr;
  char      path[45];
  uint16    recno   = 0;

BEGINSEQ
  if ( recnum )
    rvrnum = MAX(rvrnum,recnum-1);
    
  if ( rvrfile )
  {
    if ( lseek(rvrfile,0,SEEK_SET) < 0 )             SDBERR(1)
    if ( read(rvrfile,(void *)&rvrhdr,sizeof(rvrh)) != sizeof(rvrh) )
                                                     SDBERR(1)
    rvrhdr.rvrhtdat  = dbdt().SetDate().GetLongInt();
    rvrhdr.rvrhttim  = dbtm().SetTime().GetLongInt();
    lseek(rvrfile,0,SEEK_SET);
    if ( write(rvrfile,(void *)&rvrhdr,sizeof(rvrh)) != sizeof(rvrh) )
                                                     SDBERR(1)
    lseek(rvrfile,0,SEEK_END);
    close(rvrfile);
  }

  rvrnum++;
  if ( recpath ) 
  {
   gvtsexc(recpath,"\\","/",UNDEF);
   if ( strlen(recpath) > sizeof(rvrpath)-2 )       SDBERR(99)
    if ( recpath[strlen(recpath)-1] != '/' ) 
      strcat(recpath,"/"); 
    strcpy(rvrpath,recpath);
  }

  if ( rvrfncr(path) )                                     ERROR
  if ( rvrfopn(path) )                                     ERROR
  if ( rvrinit() )                                         ERROR

  recno = rvrnum;

RECOVER


ENDSEQ
  return(recno);

}

/******************************************************************************/
/**
\brief  rvrfncr

\return term - Termination code

\param  recpath - Recovery path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rvrfncr"

logical rvr :: rvrfncr (char *recpath )
{
  char      filnam[13];
  logical   term = NO;

BEGINSEQ
  strcpy(recpath,rvrpath);
  gvtsexc(recpath,"\\","/",UNDEF);
    
  if ( recpath[strlen(recpath)-1] != '/' )
    strcat(recpath,"/");

  if ( !IsDirectory(recpath) )                        SDBERR(1)

  strcat(recpath,rvrfngt(filnam,rvrnum));

RECOVER
  *recpath = 0;
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  rvrfngt

\return filenames - 

\param  filnames - 
\param  recnum - Numer of recovery file
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rvrfngt"

char *__cdecl rvr :: rvrfngt (char *filnames, uint16 recnum )
{
  strcpy(filnames,"REC99999.RVR");
  gvtxitp(filnames,recnum,8);

  return(filnames);

}

/******************************************************************************/
/**
\brief  rvrfopn

\return term - Termination code

\param  recpath - Recovery path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rvrfopn"

logical rvr :: rvrfopn (char *recpath )
{
  logical   term = NO;

BEGINSEQ
#ifdef __unix__
    if ( (rvrfile = open(recpath,
                         (rvrout ? O_RDWR | O_CREAT | (rvrapp ? O_TRUNC : NO) : O_RDONLY ),
                         S_IREAD | S_IWRITE)) < 0 )  
                         SDBERR(86)  
#else
  if ( rvrnet )
  {
    if ( (rvrfile = sopen(recpath,
                          (rvrout ? O_RDWR | O_CREAT | O_BINARY :
                                          O_RDONLY | O_BINARY         ),
                          SH_DENYNO, S_IREAD | S_IWRITE)) < 0 )
                                                     SDBERR(86)
  }
  else
    if ( (rvrfile = open(recpath,
                         (rvrout ? O_RDWR | O_CREAT | O_BINARY | (rvrapp ? O_TRUNC : NO) :
                                         O_RDONLY | O_BINARY         ),
                         S_IREAD | S_IWRITE)) < 0 )  SDBERR(86)
#endif

RECOVER
  term = YES;
  rvrfile = 0;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  rvrinit

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rvrinit"

logical rvr :: rvrinit ( )
{
  rvrh      rvrhdr;
  logical   term = NO;

BEGINSEQ
  rvrhdr.rvrhsdat = dbdt().SetDate().GetLongInt();
  rvrhdr.rvrhstim = dbtm().SetTime().GetLongInt();
  rvrhdr.rvrhtdat = 0;
  rvrhdr.rvrhttim = 0;

  lseek(rvrfile,0,SEEK_SET);
  if ( write(rvrfile,(void *)&rvrhdr,sizeof(rvrh)) != sizeof(rvrh) ) 
                                                       SDBERR(1)

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  rvrrdh

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rvrrdh"

logical rvr :: rvrrdh ( )
{
  rvre        rvrenty;
  rvre       *rvreptr = (rvre *)rvrwork;
  int32        rlen;
  logical     term = NO;
BEGINSEQ
  if ( lseek(rvrfile,rvrpos,SEEK_SET) == -1L )         SDBERR(1)
  if ( !(rlen = read(rvrfile,(void *)&rvrenty,RVRE)) ) ERROR
  if ( rlen != RVRE )                                  SDBERR(1)

  if ( memcmp(rvrenty.rvreidnt,"RVRE",4) )             SDBERR(1)
  
  if ( rvruil < rvrenty.rvreulen )
  {
    rvrsup(NULL,rvrenty.rvreulen);
    rvreptr = (rvre *)rvrwork;
  }
  *rvreptr = rvrenty;

  rlen = rvreptr->rvreulen + rvreptr->rvreinst * sizeof(acb);
  if ( read(rvrfile,rvreptr->rvreuser,rlen) != rlen )  SDBERR(1)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  rvrsup


\param  userinfo - Area for application recovery information
\param  uilen - Length of application data area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rvrsup"

void rvr :: rvrsup (char *userinfo, int16 uilen )
{
  rvre      rvrenty;

  rvruser = userinfo;
  rvruil  = uilen;

  if ( rvruil < uilen )
    delete rvrwork, rvrwork = NULL;
    
  if ( !rvrwork )
    rvrwork = new char[RVRE+rvruil+sizeof(acb)];
  memcpy(rvrwork,(void *)&rvrenty,RVRE);
  
  if ( !userinfo )
    rvruser = rvrwork + RVRE;
}

/******************************************************************************/
/**
\brief  rvrwt

\return term - Termination code

\param  datarea
\param  datlen
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "rvrwt"

logical rvr :: rvrwt (void *datarea, uint16 datlen )
{
  logical   term = NO;

BEGINSEQ
  if ( lseek(rvrfile,0,SEEK_END) < 0 )               SDBERR(1)
    
  if (datarea)
    if ( write(rvrfile,datarea,(unsigned)datlen) != (int)datlen )
      switch ( errno )
      {
        case  EACCES : SDBERR(6)
        default      : SDBERR(1)
      }

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ~rvr - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~rvr"

     rvr :: ~rvr ( )
{
  Close();
    
  delete rvrwork;
  rvrwork = NULL;

}


