/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    mvli

\brief    


\date     $Date: 2006/06/28 18:03:21,87 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "mvli"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sexd.hpp>
#include  <sinti.hpp>
#include  <smvli.hpp>


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

int32 mvli :: AddExt (EB_Number ebsnum, char *skey, int32 lindx0 )
{
  logical   extlock = stsclck();

BEGINSEQ
  if ( Lock() )                                      ERROR
  if ( !exd_area )
    if ( GetTable() )                                ERROR

  if ( mvlsrt->srtssr(mvlsrt->srtkps() != 1 ? skey : (char *)&ebsnum) ) 
  {
    SetKeyErrorVariables(skey);
    SDBERR(64)
  }
  
  if ( !mvlchk(AUTO) )                               ERROR

  mvlpcrt(ebsnum,mvlsrt->srtkps() != 1 ? skey : (char*)NULL);
  
  lindx0 = refcuri = mvlsrt->srtkad(mvlpenty) - 1;
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

\param  intiptr - 
\param  entnr - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddID"

logical mvli :: AddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{

  return(ref::AddID(intiptr,entnr,lindx0));

}

/******************************************************************************/
/**
\brief  DeleteID - 


\return term - Termination code

\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical mvli :: DeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{

  return(ref::DeleteID(intiptr,oldinst,entnr));

}

/******************************************************************************/
/**
\brief  GetIDPointer - 


\return extref - 

\param  skey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIDPointer"

EB_Number *mvli :: GetIDPointer (char *skey )
{
  int32        index;
  EB_Number  *extref = NULL;
BEGINSEQ
  if ( !this )                                        ERROR
  if ( Refresh() )                                    ERROR
  if ( !(index = mvlsrt->srtssr(skey)) )              ERROR
  extref = (EB_Number *)mvlsrt->srtigt(index);
RECOVER

ENDSEQ
  return(extref);
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

int32 mvli :: GetIndex (char *skey, EB_Number ebsnum, logical exact )
{
  int32        indx0;
BEGINSEQ
  if ( Refresh() )                                          ERROR
  indx0 = mvlsrt->srtbsr(skey)-1;
//  indx0 = mvlsrt->srtbsr(mvlsrt->srtkps() != 1 ? skey : (char *)&ebsnum)-1;
  if ( exact && mvlsrt->stscerr() )                         ERROR
  if ( FillIndexEntry(indx0) )                              ERROR
RECOVER
  refcuri = AUTO;
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

char *mvli :: GetKey (int32 lindx0, char *keyptr )
{

BEGINSEQ
  if ( !keyptr )                                     SDBERR(99)
  
  if ( lindx0 == AUTO )
  {
    if ( refcuri == AUTO )                           ERROR
  }
  else   
    if ( FillIndexEntry(lindx0) )                    ERROR

  memcpy(keyptr,mvlpenty+(mvlsrt->srtkps() == 1 ? 0 : 1),mvlsrt->srtkln());

RECOVER
  keyptr = NULL;

ENDSEQ
  return(keyptr);

}

/******************************************************************************/
/**
\brief  UpdateID - 


\return term - Termination code

\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateID"

logical mvli :: UpdateID (inti *intiptr, void *oldinst, EB_Number entnr )
{

  return( ref::UpdateID(intiptr,oldinst,entnr) );



}

/******************************************************************************/
/**
\brief  mvli - 



\param  lobhandle - 
\param  extref - 
\param  clnumb - 
\param  akcbptr - 
\param  maxl - 
\param  globind - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvli"

     mvli :: mvli (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, int16 maxl, logical globind )
                     : mvlp(lobhandle,extref,clnumb,IDB_MVLI,MVLI_OLN,
 maxl,akcbptr,globind)

{

//  if ( !memcmp(akcbptr->GetKeyName(),"__IDENTITY ",11) )
//    mvlsrt->srtsor(1,4,'I');

}

/******************************************************************************/
/**
\brief  ~mvli - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~mvli"

     mvli :: ~mvli ( )
{



}


