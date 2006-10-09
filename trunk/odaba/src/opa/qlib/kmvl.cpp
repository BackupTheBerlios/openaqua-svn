/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    kmvl

\brief    


\date     $Date: 2006/07/07 13:20:50,96 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "kmvl"

#include  <popa7.h>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sDBIndexList.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sgmvl.hpp>
#include  <sref.hpp>
#include  <skmvl.hpp>


/******************************************************************************/
/**
\brief  GetExtRef - 


\return extref - 

\param  refptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtRef"

EB_Number *kmvl :: GetExtRef (ref *refptr )
{
  char         keyarea[ID_SIZE];
  char        *keyptr;
  EB_Number   *extref = NULL;
BEGINSEQ
  memset(keyarea,' ',ID_SIZE);
  refptr->SetKeyNum(keyarea);

  if ( !(extref = GetIDPointer(keyarea)) )           ERROR

RECOVER
  extref = NULL;
ENDSEQ
  return(extref);
}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical kmvl :: IsEmpty ( )
{

  return ( mvlsrt ? !mvlsrt->srtcnt() : YES );

}

/******************************************************************************/
/**
\brief  ProvideExtRef - 


\return extref - 

\param  refptr - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideExtRef"

EB_Number *kmvl :: ProvideExtRef (ref *refptr, PIACC accopt )
{
  char       keyarea[ID_SIZE];  // jetzt nur noch INT(4), langer Schlüssel für Umstellung
  char      *keyptr;
  int16      talevel = 0;
  logical    extlock = stsclck();
  EB_Number *extref;
  logical    newref  = NO;
BEGINSEQ
  if ( !extlock && Lock() )                          ERROR
  talevel = ob_handle->StartTAIntern(NO,YES,AUTO);
  
  memset(keyarea,' ',ID_SIZE);
  refptr->SetKeyNum(keyarea);
  stsrold();
  if ( extref = GetIDPointer(keyarea) )
  {
    if ( !extref->IsEmpty(ob_handle->get_pif()) )    LEAVESEQ
  }
  if ( accopt == PI_Read )                           ERROR
  
  
  if ( !extlock && Lock() )                          ERROR
  
  if ( !(extref = GetIDPointer(keyarea)) )
  {
    if ( ob_handle->get_access_mode() == PI_Read )   ERROR
      
    if ( version != CUR_VERSION && version != ob_handle->get_version() ) 
                                                     ERROR
    if ( AddExt(0,keyarea,UNDEF) == AUTO )           ERROR
    extref = GetIDPointer(keyarea);
  }
  
  if ( extref && extref->IsEmpty(ob_handle->get_pif()) )
  {  
    if ( !refptr->IsTemporary() )
      refptr->stssold();
    if ( accopt > PI_Read )
    {
      if ( refptr->Setup(extref,cluster_number,mb_number) ) 
                                                     ERROR
      if ( refptr->InitialWrite() )                  ERROR
      refmod = YES;
      Save();      
    }  
  }
  else
    refmod = NO;

RECOVER
  extref = NULL;
ENDSEQ
  if ( Unlock(extlock) )
    extref = NULL;
  if ( talevel )
    ob_handle->StopTA(AUTO,!extref);
  return(extref);
}

/******************************************************************************/
/**
\brief  kmvl - 



\param  lobhandle - 
\param  extref - 
\param  clnumb - 
\param  version - 
\param  globind - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "kmvl"

     kmvl :: kmvl (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, uint16 version, logical globind )
                     : mvli (lobhandle,extref,clnumb,
      lobhandle->GetDictionary()
  ->GetStructDef("SDB_ExtendRef",SYS_NSID,version)
  ->GetEntry("indizes")->get_index_list()->GetHead(),
  UNDEF,globind)
{



}

/******************************************************************************/
/**
\brief  ~kmvl - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~kmvl"

     kmvl :: ~kmvl ( )
{



}


