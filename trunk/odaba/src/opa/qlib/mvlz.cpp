/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    mvlz

\brief    


\date     $Date: 2006/04/19 18:57:56,12 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "mvlz"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <smvlp.hpp>
#include  <smvlz.hpp>


/******************************************************************************/
/**
\brief  AddExt - 


\return ebsnum - 

\param  ebsnum - 
\param  skey - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExt"

int32 mvlz :: AddExt (EB_Number ebsnum, char *skey, int32 lindx0 )
{
  logical   extlock = stsclck();

BEGINSEQ
  if ( Lock() )                                       ERROR

  if ( mvlsrt->srtssr((char *)&ebsnum) )              SDBERR(64)
  if ( !mvlchk(AUTO) )                                ERROR

  mvlzebsn = ebsnum;
  lindx0 = refcuri = mvlsrt->srtkad((char *)&mvlzebsn) - 1;
  Modify();
RECOVER
  lindx0 = AUTO;
ENDSEQ
  if ( Unlock(extlock) )
    lindx0 = AUTO;
  return(lindx0);

}

/******************************************************************************/
/**
\brief  AddID - 


\return term - Termination code

\param  instptr - 
\param  entnr - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddID"

logical mvlz :: AddID (void *instptr, EB_Number entnr, int32 lindx0 )
{

  return ( AddExt(entnr,NULL,lindx0) == AUTO );

}

/******************************************************************************/
/**
\brief  DeleteID - 


\return term - Termination code

\param  instptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical mvlz :: DeleteID (void *instptr, void *oldinst, EB_Number entnr )
{
  EB_Number    ebsnum = entnr;
  int32         lindx0 = 0;
  logical      term   = NO;
BEGINSEQ
  if ( refcuri == AUTO || entnr != mvlzebsn )
    if ( !(refcuri = GetIndex(NULL,entnr,YES)) )     ERROR
  
  if ( DelExt(refcuri) )                             ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillIndexEntry - 


\return term - Termination code

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillIndexEntry"

logical mvlz :: FillIndexEntry (int32 lindx0 )
{
  logical   term = NO;

BEGINSEQ
  if ( lindx0 < 0 )                                      ERROR
  
  if ( refcuri != lindx0 )
  {   
    if ( Refresh() )                                     ERROR
    if ( lindx0 >= mvlsrt->srtcnt() )                    ERROR

    mvlzebsn = *(long *)mvlsrt->srtigt((short int)(lindx0+1));
    refcuri = lindx0;
  }

RECOVER
  refcuri  = AUTO;
  mvlzebsn = 0;
  term     = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  GetID - 


\return ebsnum - 

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number mvlz :: GetID (int32 lindx0 )
{


BEGINSEQ
  if ( lindx0 == AUTO )
    lindx0 = refcuri;
    
  if ( refcuri != lindx0 )                      
  {
    if ( Refresh() )                                       ERROR
    if ( FillIndexEntry(lindx0) )                          ERROR
  }
RECOVER
  mvlzebsn = 0;
ENDSEQ
  return(mvlzebsn);

}

/******************************************************************************/
/**
\brief  GetIndex - 


\return lindx0 - 

\param  skey - 
\param  ebsnum - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 mvlz :: GetIndex (char *skey, EB_Number ebsnum, logical exact )
{
  int16 indx0;
BEGINSEQ
  if ( Refresh() )                                      ERROR
  indx0 = mvlsrt->srtbsr((char *)&ebsnum)-1;
  if ( exact && mvlsrt->stscerr() )                     ERROR
  if ( FillIndexEntry(indx0) )                          ERROR
RECOVER
  refcuri  = AUTO;
  mvlzebsn = 0;
ENDSEQ
  mvlsrt->stsrerr();
  return(refcuri);  

}

/******************************************************************************/
/**
\brief  GetKey - 


\return skey - 

\param  lindx0 - 
\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKey"

char *mvlz :: GetKey (int32 lindx0, char *keyptr )
{

BEGINSEQ
  if ( !keyptr )                                     SDBERR(99)
  
  if ( lindx0 == AUTO )
  {
    if ( refcuri == AUTO )                           ERROR
  }
  else   
    if ( FillIndexEntry(lindx0) )                    ERROR
  
  *(EB_Number *)keyptr = mvlzebsn;
RECOVER
  keyptr = NULL;

ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  UpdateID - 


\return term - Termination code

\param  instptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateID"

logical mvlz :: UpdateID (void *instptr, void *oldinst, EB_Number entnr )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  mvlz - 



\param  lobhandle - 
\param  extref - 
\param  clnumb - 
\param  maxl - 
\param  globind - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlz"

                        mvlz :: mvlz (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, int16 maxl, logical globind )
                     : mvl(lobhandle,extref,clnumb,IDB_MVLZ,MVLP_ECT,maxl,NULL,globind), 
  mvlzebsn(0)

{

BEGINSEQ
  if ( mvlcrt(8,0,NULL) )                            ERROR
  mvlsrt->srtsor(1,8,'I');
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~mvlz - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~mvlz"

                        mvlz :: ~mvlz ( )
{



}


