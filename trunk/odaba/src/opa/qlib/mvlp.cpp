/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvlp

\brief    


\date     $Date: 2006/03/12 19:19:02,43 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "mvlp"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sDBStructDef.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sexd.hpp>
#include  <sinti.hpp>
#include  <smvlp.hpp>


/******************************************************************************/
/**
\brief  AddExt - 


\return lindx0 -

\param  ebsnum -
\param  skey -
\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExt"

int32 mvlp :: AddExt (EB_Number ebsnum, char *skey, int32 lindx0 )
{
  logical   extlock = stsclck();
  int32  indx;

BEGINSEQ
  if ( Lock() )                                      ERROR
  if ( !exd_area )
    if ( GetTable() )                                ERROR
  
  if ( lindx0 == AUTO )
    lindx0 = refcuri;
    
  if ( !(indx = mvlchk(lindx0)) )                    ERROR
  mvlpcrt(ebsnum,skey);

  mvlsrt->srtiad(indx,mvlpenty);

  Modify();
  refcuri = indx-1;
  lindx0  = refcuri;
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

logical mvlp :: AddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{
  logical  term = NO;
  term = AddExt(entnr,NULL,lindx0) == AUTO;

  return(term);
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

logical mvlp :: DeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  EB_Number    ebsnum = entnr;
  int32         lindx0 = 0;
  logical      term   = NO;
BEGINSEQ
  if ( refcuri == AUTO || entnr != *mvlpenty )
  {
    while ( !(ebsnum = GetID(lindx0++)).IsEmpty() )
      if ( ebsnum == entnr )
        break;
  }

  if ( ebsnum.IsEmpty() )                            ERROR
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

logical mvlp :: FillIndexEntry (int32 lindx0 )
{
  logical   term = NO;

BEGINSEQ
  if ( lindx0 < 0 )                                      ERROR
  
  if ( refcuri != lindx0 )
  {   
    if ( Refresh() )                                     ERROR
    if ( lindx0 >= mvlsrt->srtcnt() )                    ERROR

    memcpy(mvlpenty,mvlsrt->srtigt(lindx0+1),mvlsrt->srtlen());
    refcuri = lindx0;
  }

RECOVER
  refcuri = AUTO;
  term    = YES;
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

EB_Number mvlp :: GetID (int32 lindx0 )
{
  EB_Number  ebsnum;

BEGINSEQ
  if ( lindx0 == AUTO )
    lindx0 = refcuri;
    
  if ( refcuri != lindx0 )                      
  {
    if ( Refresh() )                                       ERROR
    if ( FillIndexEntry(lindx0) )                          ERROR
  }  

  if ( refcuri != AUTO )
    ebsnum = *mvlpenty;		

RECOVER

ENDSEQ
  return(ebsnum);

}

/******************************************************************************/
/**
\brief  MoveDown - 


\return lindx0 -

\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveDown"

int32 mvlp :: MoveDown (int32 lindx0 )
{
  logical   extlock = stsclck();
BEGINSEQ
  if ( Lock() )                                      ERROR
  if ( mvlsrt->srtkln() > 0 )                        SDBERR(99)

  if ( FillIndexEntry(lindx0) )                      ERROR
  if ( lindx0+1 >= mvlsrt->srtcnt() )                ERROR

  if ( mvlsrt->srtidl(lindx0+1) )                    ERROR
  if ( mvlsrt->srtiad(lindx0+2,mvlpenty) )           ERROR
  
  refcuri = ++lindx0;
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
\brief  MoveUp - 


\return lindx0 -

\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveUp"

int32 mvlp :: MoveUp (int32 lindx0 )
{
  logical   extlock = stsclck();
BEGINSEQ
  if ( Lock() )                                      ERROR
  if ( mvlsrt->srtkln() > 0 )                        SDBERR(99)

  if ( FillIndexEntry(lindx0) )                      ERROR
  if ( lindx0 <= 0 )                                 ERROR

  if ( mvlsrt->srtidl(lindx0+1) )                    ERROR
  if ( mvlsrt->srtiad(lindx0,mvlpenty) )             ERROR
  
  refcuri = --lindx0;
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
\brief  RepairMVL - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RepairMVL"

logical mvlp :: RepairMVL ( )
{


  return(NO);
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

logical mvlp :: UpdateID (inti *intiptr, void *oldinst, EB_Number entnr )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  mvlp - 



\param  lobhandle -
\param  extref -
\param  clnumb -
\param  otyp -
\param  olen -
\param  maxl -
\param  akcbptr -
\param  globind -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlp"

                        mvlp :: mvlp (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, char otyp, int16 olen, int16 maxl, DBIndex *akcbptr, logical globind )
                     : mvl(lobhandle,extref,clnumb,otyp,MVLP_ECT,maxl,akcbptr,globind), 
mvlpenty(NULL)
{
  kcb      *kcbptr = otyp != IDB_MVLP ? akcbptr->get_key_def() : NULL;
  int16 klen   = kcbptr ? kcbptr->kcbklng() : 0;
  int16 len    = otyp == IDB_MVLD ? akcbptr->get_field_def()->GetDBStruct()->get_ext_length()
                                      : klen;
  int16 kpos   = otyp == IDB_MVLD ? UNDEF
                                      : kcbptr ? olen+1 : 0;

BEGINSEQ
  if ( mvlcrt(len+olen,kpos,kcbptr) )                     ERROR

  if ( !(mvlpenty = (EB_Number *)new char[klen+olen] ) )  SDBERR(95)
  memset((char *)mvlpenty,0,olen);
  memset((char *)mvlpenty+olen,' ',klen);

RECOVER
 

ENDSEQ

}

/******************************************************************************/
/**
\brief  mvlpcrt - 



\param  ebsnum -
\param  skey -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlpcrt"

void mvlp :: mvlpcrt (EB_Number ebsnum, char *skey )
{

  *mvlpenty = ebsnum;

  if ( skey )
    memcpy(mvlpenty+1,skey,mvlsrt->srtkln());
    
  refmod = YES;

}

/******************************************************************************/
/**
\brief  mvlpidxg - 


\return lindx0 -

\param  ebsnum -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "mvlpidxg"

int32 mvlp :: mvlpidxg (EB_Number ebsnum )
{
  EB_Number    *rexptr;
  register int  indx = 0;

BEGINSEQ

  while ( rexptr = (EB_Number *)mvlsrt->srtigt(++indx) )
    if ( *rexptr == ebsnum )
      break;
       
  if ( !rexptr )                                         ERROR
  indx--;

RECOVER
  indx = AUTO;
ENDSEQ
  return(indx);

}

/******************************************************************************/
/**
\brief  ~mvlp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~mvlp"

                        mvlp :: ~mvlp ( )
{
  char     *tblptr;

  delete mvlpenty;
  mvlpenty = NULL;

}


