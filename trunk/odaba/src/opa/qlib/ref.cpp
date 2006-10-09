/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    ref

\brief    


\date     $Date: 2006/07/12 19:16:18,75 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ref"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBFieldDef.hpp>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sDBStructDef.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sLNode.hpp>
#include  <sMemoAccess.hpp>
#include  <iNetConversion.h>
#include  <sPCSHandle.hpp>
#include  <sRefAccess.hpp>
#include  <sXRef.hpp>
#include  <sbinti.hpp>
#include  <sexd.hpp>
#include  <sgmvl.hpp>
#include  <sguid.hpp>
#include  <sicb.hpp>
#include  <sinti.hpp>
#include  <skmvl.hpp>
#include  <smvld.hpp>
#include  <smvli.hpp>
#include  <smvln.hpp>
#include  <smvlp.hpp>
#include  <sref.hpp>
#include  <srefp.hpp>
#include  <srefs.hpp>
#include  <srefx.hpp>
#include  <sref.hpp>


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

int32 ref :: AddExt (EB_Number ebsnum, char *skey, int32 lindx0 )
{

  return(0);

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

logical ref :: AddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{
  char       keyarea[MAX_KEYLEN];
  EB_Number  entnum;
  char      *keyptr; 
  char      *instptr = GetKeyInstance(intiptr);
  int       indx = 0;
  kcb      *kcbptr;
  logical   term = NO;

BEGINSEQ
  if ( !(kcbptr = refsakcb->get_key_def()) )
  {
    if ( AddExt(entnr,NULL,lindx0) == AUTO )         ERROR
//    if ( WriteIndexEntry(lindx0,instptr) )           ERROR
    LEAVESEQ
  }

  if ( !new_ckh.get_ckhcke() )
  {
    if ( IsIdentityOrder() ) 
    {
      entnum = entnr;
      entnum.FromPIF(ob_handle->IsPIF());
      keyptr = (char *)&entnum;
    }
    else
      keyptr = kcbptr->kcbkgt(instptr,keyarea);
    
    if ( AddExt(entnr,keyptr,AUTO) == AUTO )         ERROR
//    if ( WriteIndexEntry(lindx0,instptr) )           ERROR
    LEAVESEQ
  }

  new_ckh.ckhopen(instptr,NULL);                     SDBCERR
  while ( keyptr = new_ckh.ckhkget(++indx) )
    if ( AddExt(entnr,keyptr,AUTO) == AUTO )      
      if ( SDBERROR != 64 )                          ERROR

RECOVER
  term = YES;
ENDSEQ
  new_ckh.ckhclos();
  return(term);

}

/******************************************************************************/
/**
\brief  CheckDBDelInstances - 



\return term - Termination code

\param  nresult - 
\param  repair - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBDelInstances"

logical ref :: CheckDBDelInstances (NString &nresult, logical repair )
{
  int32                   indx0  = 0;
  logical                 errors = AUTO;
  int16                   sid;
  refs                   *refsptr;
  NString                 nstring;
  EB_Number               entnr;
  char                    keystr[513];
  char                    key[513];
  char                   *keyptr;
  logical                 term = NO;
BEGINSEQ
  if ( (refsptr = GetSharedRef()) && 
       refsptr->get_refsotyp() == IDB_MVLD )        LEAVESEQ
       
  nstring += " contains invalid instance references:";
  while ( !(entnr = GetID(indx0)).IsEmpty() )
  {
    errors = AUTO;
    if ( !(sid = ob_handle->CheckDBEntry(entnr)) ||
         ( refsid != 151 && sid != refsid && !refsakcb->get_field_def()->get_weak_typed() )             )
    {
      if ( repair )
        errors = DelExt(indx0);
      term = YES;
      nstring += "\n         -";
      nstring += ' ';
      if ( keyptr = GetKey(indx0,key) )
      {
        if ( struct_access->get_struct_def()->smcbityp == 72 ) // __OOBJECT
          ((guid *)keyptr)->GetString(keystr);
        else
          refsakcb->get_key_def()->scbsmcb->ConvertToString(keyptr,keystr,512);
        nstring += keystr;
      }      
      else
        nstring += (int32)entnr.get_ebsnum();
      nstring += (char*)(errors || !repair ? " (not corrected)" : " (deleted)");
    }
    if ( !repair || errors )
      indx0++;   
  }
  if ( term )
  {
    Save();
    nresult += nstring;
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDBIndex - 



\return term - Termination code

\param  nresult - 
\param  check_opts - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBIndex"

logical ref :: CheckDBIndex (NString &nresult, CheckOptions check_opts )
{
  int32                 indx0  = 0;
  char                 *keyname = (char *)refsakcb->GetKeyName();
  ref                  *refptr;
  gmvl                 *gref;
  short                *attrtype;
  NString               nstring;
  logical               term = NO;
BEGINSEQ
  nstring = "\n        Index '";
  if ( keyname && *keyname )
    nstring.Append(keyname,ID_SIZE);
  else
    nstring += "undefined";
  nstring += "' contains errors";
  
  if ( !refrex || !refrex->get_ebsnum() )            LEAVESEQ
  
  if ( check_opts.ref_indexes )
  {
    if ( CheckDBRefIndex(nstring,check_opts.repair_all) )
      term = YES;
    if ( (check_opts.repair_all || !term) && check_opts.deleted_references )
      if ( CheckDBDelInstances(nstring,check_opts.repair_all) )
        term = YES;
  }
  
  if ( term )
    nresult += nstring;

  if ( GetGenAttribute() )  // generic reference 
  {
    indx0  = 0;
    gref = (gmvl *)this;
    while ( attrtype = (short *)gref->GetKey(indx0++,(char *)attrtype) )
      if ( refptr = gref->GetReference(*attrtype,YES) )
        if ( refptr->CheckDBIndex(nresult,check_opts) )
        {
          term = YES;
          gref->Modify();
          gref->stssmod();
        }
    if ( gref->stscmod() )
    {
      gref->Save();
      gref->stsrmod();
    }
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDBRefIndex - 



\return term - Termination code

\param  nresult - 
\param  repair - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBRefIndex"

logical ref :: CheckDBRefIndex (NString &nresult, logical repair )
{

  return( CheckIndex(nresult,repair) );


}

/******************************************************************************/
/**
\brief  CheckID - 



\return cond - 

\param  instptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckID"

int16 ref :: CheckID (void *instptr, void *oldinst, EB_Number entnr )
{
  kcb      *kcbptr;
  char     *newkey;
  char      keyarea[MAX_KEYLEN];
  int16     cond = NO;

BEGINSEQ
  if ( !(kcbptr = refsakcb->get_key_def()) ||
       !refsakcb->get_unique()             || 
       new_ckh.get_ckhcke() )                       LEAVESEQ
       
  if ( !(newkey = CheckMod(instptr,oldinst,keyarea)) )      
  {
    cond = AUTO;                                    LEAVESEQ
  }
  
  if ( refsakcb->get_no_empty() )
    if ( kcbptr->scbsmcb->IsEmpty(newkey) )         SDBERR(209)
      
  if ( WSGetIndex(kcbptr->GetKey((char *)instptr,keyarea),0,YES) != AUTO )
                                                    SDBERR(66)
RECOVER
  cond = YES;
ENDSEQ
  return(cond);

}

/******************************************************************************/
/**
\brief  CheckIndex - 



\return term - Termination code

\param  nresult - 
\param  repair - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckIndex"

logical ref :: CheckIndex (NString &nresult, logical repair )
{
  logical                 term = NO;
BEGINSEQ
  if ( !refrex || !refrex->get_ebsnum() )            LEAVESEQ
    
  if ( ob_handle->CheckEBI(*refrex) || Refresh() )
  {
    nresult += "\n         Index not accessible";
    if ( repair )
    {
      *refrex = 0;
      InitialWrite();
      stsssav();
      nresult += " - index deleted";
    }
    else
      nresult += " - not repaired";
    term = YES; 
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckMod - 



\return newkey - 

\param  instptr - 
\param  oldinst - 
\param  key_area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckMod"

char *ref :: CheckMod (void *instptr, void *oldinst, char *key_area )
{
  kcb      *kcbptr;
  char     *newkey = NULL;
  char      oldkey[MAX_KEYLEN];
  logical   cond = YES;
BEGINSEQ
  if ( !(kcbptr = refsakcb->get_key_def()) ||
       kcbptr->scbsmcb->smcbsts.stscnof()     )      LEAVESEQ
  
  if ( oldinst )
  {
    if ( new_ckh.get_ckhcke() )
    {
      if ( new_ckh.ckhopen(instptr,NULL) == AUTO    ||
           old_ckh.ckhopen(oldinst,instptr) == AUTO   ) 
                                                     ERROR
      if ( new_ckh.ckhchg(&old_ckh) )
        newkey = oldkey;               // irgendwas, rückgabewert muß ungleich NULL sein wenn schlüsseländerung
      LEAVESEQ
    }
    else
      kcbptr->GetKey((char *)oldinst,oldkey);
  }
  else
    if ( !WSGetKey(AUTO,oldkey) )                    ERROR
    
  newkey = kcbptr->GetKey((char *)instptr,key_area);
  if ( !kcbptr->CompareKeys(newkey,oldkey) )         ERROR
RECOVER
  newkey = NULL;
ENDSEQ
  return(newkey);
}

/******************************************************************************/
/**
\brief  CheckNewID - 



\return cond - 

\param  instptr - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckNewID"

logical ref :: CheckNewID (void *instptr, EB_Number entnr )
{
  kcb      *kcbptr;
  char      keyarea[MAX_KEYLEN];
  char     *keyptr;
  EB_Number entnum;
  int16     indx = 0;
  logical   cond = NO;
BEGINSEQ
  if ( !(kcbptr = refsakcb->get_key_def()) )         LEAVESEQ

  SDBEV3(kcbptr->scbsmcb->smcbname,ID_SIZE)
  SDBEV2(struct_access->get_struct_def()->smcbname,ID_SIZE)
  
  if ( !new_ckh.get_ckhcke() )
  {
    if ( IsIdentityOrder() ) 
    {
      entnum = entnr;
      entnum.FromPIF(ob_handle->IsPIF());
      keyptr = (char *)&entnum;
    }
    else
      keyptr = kcbptr->GetKey((char *)instptr,keyarea);
    
    SDBEV1(keyptr,(int16)kcbptr->scbsmcb->GetLength())
    if ( refsakcb->get_unique() )
      if ( GetIndex(keyptr,0,YES) != AUTO )
      {
        SetKeyErrorVariables(keyptr);                 SDBERR(64)
      }           
        
    if ( refsakcb->get_no_empty() )
      if ( kcbptr->scbsmcb->IsEmpty(keyptr) )         SDBERR(209)
    LEAVESEQ
  }
 
  new_ckh.ckhopen(instptr,NULL);                      SDBCERR
  while ( keyptr = new_ckh.ckhkget(++indx) )
  {
    SDBEV1(keyptr,(int16)kcbptr->scbsmcb->GetLength())
    if ( refsakcb->get_unique() )
      if ( GetIndex(keyptr,0,YES) != AUTO )
      {
        SetKeyErrorVariables(keyptr);                 SDBERR(64)
      }           
        
    if ( refsakcb->get_no_empty() )
      if ( kcbptr->scbsmcb->IsEmpty(keyptr) )         SDBERR(209)
  }
RECOVER
  cond = YES;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical ref :: CheckWProtect ( )
{
  logical                 cond = NO;
BEGINSEQ
  if ( !refrex || refrex->IsEmpty(ob_handle->get_pif()) )  
                                                     LEAVESEQ
  if ( !exd_area )                                   SDBERR(99)

  if ( exd_area->get_exdacb()->stscwpt() == 1 )      ERROR
RECOVER
  cond = YES;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  DelExt - 



\return term - Termination code

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelExt"

logical ref :: DelExt (int32 lindx0 )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  DelKey - 



\return term - Termination code

\param  skey - 
\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelKey"

logical ref :: DelKey (char *skey, EB_Number ebsnum )
{
  int32      lindx0;
  logical   extlock = stsclck();
  logical   term = NO;

BEGINSEQ
  if ( Lock() )                                      ERROR

  if ( (lindx0 = GetIndex(skey,ebsnum)) == AUTO )
  {
    if ( GetIndex(ebsnum) != AUTO )                  ERROR
    LEAVESEQ  // auto correction, entry not in index
  }

  if ( DelExt(lindx0) )                              ERROR

RECOVER
  term = YES;
ENDSEQ
  if ( Unlock(extlock) )
    term = YES;
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteID - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical ref :: DeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  kcb      *kcbptr;
  char     *instptr = GetKeyInstance(intiptr);
  char      keyarea[MAX_KEYLEN];
  char     *keyptr; 
  EB_Number entnum;
  int       indx = 0;
  logical   term = NO;

BEGINSEQ
  if ( !(kcbptr = refsakcb->get_key_def()) )
  {
    if ( DelExt(refcuri) )                             ERROR
    LEAVESEQ
  }

  if ( oldinst )
    oldinst = GetOldKeyInstance(intiptr,oldinst);
    
  if ( !old_ckh.get_ckhcke() )
  {
    if ( IsIdentityOrder() ) 
    {
      entnum = entnr;
      entnum.FromPIF(ob_handle->IsPIF());
      keyptr = (char *)&entnum;
    }
    else
      keyptr = kcbptr->GetKey(oldinst ? (char *)oldinst : instptr,keyarea);
    
    if ( DelKey(keyptr,entnr) )                        ERROR
      
    LEAVESEQ
  }

  if ( oldinst )
  {
    if ( old_ckh.ckhopen(oldinst,instptr) == AUTO )        
    {
      SDBCERR
      LEAVESEQ
    }  

    while ( keyptr = old_ckh.ckhkget(++indx) )
      DelKey(keyptr,entnr);
  }


RECOVER
  term = YES;
ENDSEQ
  old_ckh.ckhclos();
  return(term);

}

/******************************************************************************/
/**
\brief  i1 - 



\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical ref :: DeleteID (EB_Number entnr )
{
  int32         lindx0 = 0;
  EB_Number    ebsnum;
  logical      term = NO;
  while ( !(ebsnum = GetID(lindx0++)).IsEmpty() )
    if ( ebsnum == entnr )
      if ( DelExt(--lindx0) )
        lindx0++;

  return(term);
}

/******************************************************************************/
/**
\brief  DeleteReference - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteReference"

void ref :: DeleteReference ( )
{
  refs      *refsptr = GetSharedRef();
  if ( refsptr )
    refsptr->refsdel();
  else if ( refrex )
  {
    *refrex = 0;
    stssmod();
  }
  
  refmod  = NO;
  refcuri = AUTO;


}

/******************************************************************************/
/**
\brief  GetCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 ref :: GetCount ( )
{

 return (UNDEF);

}

/******************************************************************************/
/**
\brief  GetGenAttribute - 



\return fldname - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenAttribute"

char *ref :: GetGenAttribute ( )
{

  return(NULL);

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

EB_Number ref :: GetID (int32 lindx0 )
{

 return (UNDEF);

}

/******************************************************************************/
/**
\brief  GetIndex - 



\return lindx0 - 
-------------------------------------------------------------------------------
\brief  REFNGT_K - 



\param  skey - 
\param  ebsnum - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 ref :: GetIndex (char *skey, EB_Number ebsnum, logical exact )
{

  return (AUTO);

}

/******************************************************************************/
/**
\brief  i1 - 



\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIndex"

int32 ref :: GetIndex (EB_Number ebsnum )
{
  EB_Number               entnr;
  int32                   lindx0 = 0;
BEGINSEQ
  if ( ebsnum.IsEmpty(ob_handle->IsPIF()) )          ERROR
    
  while ( !(entnr = GetID(lindx0)).IsEmpty() )
  {
    if ( entnr == ebsnum )                           LEAVESEQ
    lindx0++;
  }

  ERROR
RECOVER
  lindx0 = AUTO;
ENDSEQ
  return(lindx0);
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

char *ref :: GetKey (int32 lindx0, char *keyptr )
{

 return (NULL);

}

/******************************************************************************/
/**
\brief  GetKeyInstance - 



\return instptr - 

\param  intiptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyInstance"

char *ref :: GetKeyInstance (inti *intiptr )
{

  return ( refsakcb->get_field_def() &&
           refsakcb->get_field_def()->get_weak_typed() 
           ? intiptr->get_iselarea() + Bintiptr->get_weak_typed_offset()
           : intiptr->get_iselarea()                );

}

/******************************************************************************/
/**
\brief  GetKeyLength - 



\return klen - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyLength"

int16 ref :: GetKeyLength ( )
{

  return( refsakcb->get_key_def() ?
          refsakcb->get_key_def()->kcbklng() : 0 );

}

/******************************************************************************/
/**
\brief  GetKeyNum - 



\return keyname - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyNum"

char *ref :: GetKeyNum ( )
{
  kcb        *kcbptr;
  char       *keyname = NULL;

BEGINSEQ
  if ( kcbptr = refsakcb->get_key_def() )
    if ( GetGenAttribute() )
      kcbptr = ((gmvl*)this)->get_index_def()->get_key_def();
  
  if ( !kcbptr )                                     ERROR
  
  if ( ob_handle->GetSystemVersion() >= 2 )
    keyname = (char *)kcbptr->GetKeyNumPtr();
  else 
    keyname = kcbptr->scbsmcb->smcbname;

RECOVER

ENDSEQ
  return(keyname);
}

/******************************************************************************/
/**
\brief  GetModCount - 



\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetModCount"

int16 ref :: GetModCount ( )
{


  return(UNDEF);
}

/******************************************************************************/
/**
\brief  GetOldKeyInstance - 



\return instptr - 

\param  intiptr - 
\param  oldinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOldKeyInstance"

char *ref :: GetOldKeyInstance (inti *intiptr, void *oldinst )
{

  return ( refsakcb->get_field_def() &&
           refsakcb->get_field_def()->get_weak_typed() 
           ? ((char *)oldinst) + Bintiptr->get_weak_typed_offset()
           : (char *)oldinst                                     );

}

/******************************************************************************/
/**
\brief  GetRefCuri - 



\return lindx0 - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRefCuri"

int32 ref :: GetRefCuri ( )
{
  refs    *refsptr;
  return ( !(refsptr = GetSharedRef()) || !refsptr->HasWorkspace() || !refsptr->refsakcb->get_key_def()
            ? refcuri : refsptr->get_ws_curri() );


}

/******************************************************************************/
/**
\brief  GetSharedRef - 



\return refsptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSharedRef"

refs *ref :: GetSharedRef ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  HasWorkspace - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasWorkspace"

logical ref :: HasWorkspace ( )
{
  refs             *refsptr;
  logical           cond = YES;
BEGINSEQ
  if ( !EntryHandle::HasWorkspace() )                ERROR
  if ( !refsakcb || !refsakcb->get_key_def() )       ERROR
  
  if ( !(refsptr = GetSharedRef()) )                 ERROR
  
  // singuläre referenzen und clustered tables werden nicht im Workspace behandelt
  switch ( refsptr->get_refsotyp() )
  {
    case R_REFS   : 
    case R_REFP   :
    case IDB_MVLD :                                  ERROR
    default       : ;
  }

  // key-mvls werden nicht im Workspace behandelt
  if ( refsid == 151 )                               ERROR

  // temporäre extents werden nicht im Workspace behandelt
  if ( refsakcb->get_field_def()->get_log_reference() )
                                                     ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IdentityToPIF - 



\return keyptr - 

\param  skey - 
\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IdentityToPIF"

char *ref :: IdentityToPIF (char *skey, char *keyptr )
{
  kcb                    *kcbptr = refsakcb->get_key_def();
  logical                 term = NO;
  if ( skey && keyptr &&
       kcbptr && kcbptr->scbsmcb->smcbsts.stscnof() &&
       struct_access->get_pif()                       )
    *(int64 *)keyptr = BigToPIF(*(int64 *)skey,YES);
  else
    keyptr = skey;  

  return(keyptr);
}

/******************************************************************************/
/**
\brief  InitialWrite - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitialWrite"

logical ref :: InitialWrite ( )
{
  logical   term   = NO;

BEGINSEQ
  if ( !(*refrex).IsEmpty(ob_handle->get_pif()) )    LEAVESEQ
  Reset();
  if ( (*refrex = struct_access->CreateEBI(mb_number,cluster_number,
                                           AUTO,GetVersion())).IsEmpty() )
                                                     ERROR
// AUTO für sbnumber ist zumindest fraglich
RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Initialize - 




\param  akcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void ref :: Initialize (DBIndex *akcbptr )
{
  StructAccess   *structacc;
  kcb            *kcbptr;
  fmcb           *keyfmcb;
BEGINSEQ
  if ( !akcbptr )                                    LEAVESEQ

  refsid = akcbptr->get_field_def()->fmcbityp;

  if ( ob_handle && (refsid && refsid != TEMPSID) )  // no StructAccess for temp. structures
  {
    if ( !(structacc = ob_handle->GetStructAccess(refsid)) ||
         !(struct_access = structacc->GetRefAccess())  )
      if ( akcbptr->get_field_def()->fmcbsmcb->smcbstyp != ST_CODE ) 
                                                    SDBERR(99)
  
    if ( (kcbptr = akcbptr->get_key_def()) && kcbptr->IsMemoKey() )
    {
SDBERR(99)
//      keyfmcb = kcbptr->scbsmcb->smcbfmcl->GetEntry(1);
//      if ( !keyfmcb->fmcbsmcb->smcbacc )
//        keyfmcb->fmcbsmcb->smcbacc = new MemoAccess(ob_handle,keyfmcb->fmcbsize);
    }
  }
  
  if ( akcbptr->IsTransient() )
    stsstrans();


RECOVER


ENDSEQ

}

/******************************************************************************/
/**
\brief  IsIdentityOrder - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIdentityOrder"

logical ref :: IsIdentityOrder ( )
{
  kcb     *kcbptr = this ? refsakcb->get_key_def() : NULL;

  return( kcbptr ? kcbptr->scbsmcb->smcbsts.stscnof() : NO);

}

/******************************************************************************/
/**
\brief  IsModified - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsModified"

logical ref :: IsModified ( )
{

  return (   !this  || !exd_area  ? NO 
           : refmod               ? YES 
           :                        NO  );

}

/******************************************************************************/
/**
\brief  IsTemporary - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTemporary"

logical ref :: IsTemporary ( )
{

  return( refsakcb && refsakcb->get_temporary() );

}

/******************************************************************************/
/**
\brief  Lock - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical ref :: Lock ( )
{
  logical   term   = NO;
  logical   locked = NO;
  exd      *exdptr = NULL;
  logical   intlock = NO;

BEGINSEQ
  if ( !stsclck() && refrex )
  {
    if ( refglob )
    {
      if ( stscsav() && !refrex->IsEmpty(ob_handle->get_pif()) )
      {
        if  ( (exdptr = ProvideEXD()) && !exdptr->stscwpt() )
        {
          if ( exdptr->LockInternal(YES) )           ERROR
          intlock = YES;
        }
        if ( !exdptr->stscusr2() )
        {
          acb       acbenty(*refrex,0);
          if ( ob_handle->Lock(&acbenty) )         ERROR
          locked = YES;
        }
//                 was geschieht, wenn TA geschrieben wird ?
//                 dann treten in minimalen Zeiteinheiten Unstimmigkeiten auf
//                 die müssen noch geklärt werden (z.B. durch noch mal lesen).
      }
    }  
    if ( !refrex->IsEmpty(ob_handle->get_pif()) )
      if ( Refresh() )                               ERROR
  }

RECOVER
  if ( locked )
  {
    struct_access->Unlock(*refrex);
    locked = NO;
  }
  term = YES;
ENDSEQ
  if ( locked )
    stsslck();
  if ( intlock )
    exdptr->UnlockInternal();
  return(term);

}

/******************************************************************************/
/**
\brief  PIFToIdentity - 



\return keyptr - 

\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PIFToIdentity"

char *ref :: PIFToIdentity (char *keyptr )
{
  kcb                    *kcbptr = refsakcb->get_key_def();
  logical                 term = NO;
  if ( keyptr && 
       kcbptr && kcbptr->scbsmcb->smcbsts.stscnof() &&
       struct_access->get_pif()                        )
    *(int64 *)keyptr = PIFToBig(*(int64 *)keyptr,YES);

  return(keyptr);
}

/******************************************************************************/
/**
\brief  ProvideEXD - 



\return exdptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEXD"

exd *ref :: ProvideEXD ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  ReadIndexEntry - 



\return term - Termination code

\param  lindx0 - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadIndexEntry"

logical ref :: ReadIndexEntry (int32 lindx0, void *instptr )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  Refresh - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical ref :: Refresh ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  ReleaseReference - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseReference"

void ref :: ReleaseReference ( )
{

  if ( exd_area )
  {
    exd_area->ReleaseInstance(active_handle);
    exd_area = NULL;
  }
  mod_count = 0;

}

/******************************************************************************/
/**
\brief  Repair - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Repair"

logical ref :: Repair ( )
{
  NString              nresult;
  logical              term = NO;
  if ( CheckDBDelInstances(nresult,YES) )
    printf(nresult);

  return(term);
}

/******************************************************************************/
/**
\brief  ReserveEXD - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveEXD"

logical ref :: ReserveEXD ( )
{
  int16       count = 100;
  logical     term  = NO;
BEGINSEQ
  if ( !exd_area )                                   LEAVESEQ
  
  if ( exd_area->Reserve(YES) )                      ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReserveReference - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveReference"

void ref :: ReserveReference ( )
{

  exd_area->ReserveInstance(active_handle);

}

/******************************************************************************/
/**
\brief  Reset - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical ref :: Reset ( )
{
  logical  sav = stscsav();
//  refrex  = NULL; wegen refsdel() in DeleteReference()
  refcuri = AUTO;
  refmod  = NO;
  stsreset();

  if ( sav )
    stsssav();
  return(NO);

}

/******************************************************************************/
/**
\brief  ResetEXD - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetEXD"

logical ref :: ResetEXD ( )
{
  logical    term = NO;
BEGINSEQ
  if ( !exd_area )                                   LEAVESEQ
  if ( exd_area->stscmod() || exd_area->get_exdacb()->stscmod() )
  {
    struct_access->WriteEXD(exd_area,AUTO,mb_number,AUTO,AUTO);
    mod_count = exd_area->get_mod_count();      // neu 11.5.99
  }
  exd_area->Reset();

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ResetRefCuri - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetRefCuri"

void ref :: ResetRefCuri ( )
{
  refs    *refsptr;
  refcuri = AUTO;
  
  if ( refsptr = GetSharedRef() )
    refsptr->reset_ws_curri();

}

/******************************************************************************/
/**
\brief  Save - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical ref :: Save ( )
{

 return (NO);

}

/******************************************************************************/
/**
\brief  SetAutoIdent - 



\return cond_setting - 

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAutoIdent"

char ref :: SetAutoIdent (void *instptr )
{
  kcb      *kcbptr; 
  char      keyarea[MAX_KEYLEN];
  int32     count;
  int32     autoident;
  char      cond_setting = NO;

BEGINSEQ
  if ( !(kcbptr = refsakcb->get_key_def()) ||
       !kcbptr->scbsmcb->smcbsts.stscold()        )  LEAVESEQ

  autoident = *(int32 *)kcbptr->GetKey((char *)instptr,keyarea);

  if ( !autoident )
  {
    switch ( count = GetCount() )
    {
      case AUTO :                                      ERROR
      case 0    : break;
      default   : if ( !GetKey(count-1,(char *)&autoident) ) 
                                                       ERROR 
    }
    autoident++;
    kcbptr->SetKey((char *)instptr,(char *)&autoident);
    cond_setting = YES;
  }

RECOVER
  cond_setting = ERIC;

ENDSEQ
  return(cond_setting);

}

/******************************************************************************/
/**
\brief  SetKeyErrorVariables - 




\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKeyErrorVariables"

void ref :: SetKeyErrorVariables (char *keyptr )
{
  kcb  *kcbptr;
  char  keystr[MAX_KEYLEN+1];
BEGINSEQ
  SDBEV1("",0)
  SDBEV2("",0)
  SDBEV3("",0)
  
  if ( !this )                                       LEAVESEQ
    
  SDBEV2(struct_access->get_struct_def()->smcbname,ID_SIZE)
  
  if ( !(kcbptr = refsakcb->get_key_def()) )         LEAVESEQ

  SDBEV3(kcbptr->scbsmcb->smcbname,ID_SIZE)
  
  *keystr = 0;
  if ( keyptr && !kcbptr->scbsmcb->smcbsts.stscnof() )
    kcbptr->scbsmcb->ConvertToString(keyptr,keystr,255);
  SDBEV1(keystr,UNDEF)

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetKeyNum - 



\return term - Termination code

\param  keyarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetKeyNum"

logical ref :: SetKeyNum (char *keyarea )
{
  char                   *keyptr = GetKeyNum();
  logical                 term = NO;
BEGINSEQ
  if ( !keyptr )                                     ERROR
    
  if ( ob_handle->GetSystemVersion() >= 2 )
    memcpy(keyarea,keyptr,2);
  else 
    memcpy(keyarea,keyptr,16);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetVersion - 




\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

void ref :: SetVersion (uint16 version_nr )
{

  if ( refmod )
    Save();
  
  Reset();
  EntryHandle::SetVersion(version_nr);

}

/******************************************************************************/
/**
\brief  Setup - 



\return term - Termination code

\param  extref - 
\param  clnumb - 
\param  w_mbnumber - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical ref :: Setup (EB_Number *extref, EB_Number clnumb, int16 w_mbnumber )
{
  logical  sav = stscsav();
  Reset();
  
  if ( !extref && IsTemporary() && GetSharedRef() )
    extref = &GetSharedRef()->get_temp_rex();
    
  refrex         = extref;
  cluster_number = clnumb;
  mb_number      = w_mbnumber;
  
  stssfil();
  if ( sav )
    stsssav();
  return(NO);

}

/******************************************************************************/
/**
\brief  Unlock - 



\return term - Termination code

\param  extlock - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical ref :: Unlock (logical extlock )
{
  logical   lock;
  logical   term   = NO;

BEGINSEQ
//  term = Save();  stand hier bis 20.11.99
  lock = refrex ? !refrex->IsEmpty(ob_handle->get_pif()) : NO;  
  if ( extlock )                                     LEAVESEQ
  term = Save();
  
  if ( stsclck() && stscsav() && lock )
  {
    acb       acbenty(*refrex,0);
    term = ob_handle->Unlock(&acbenty);
  }
  stsrlck();

ENDSEQ
  return(term);

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

logical ref :: UpdateID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  kcb        *kcbptr;
  char       *instptr = GetKeyInstance(intiptr);
  char        keyarea[MAX_KEYLEN];
  char        oldkey[MAX_KEYLEN];
  char       *oldkeyptr = NULL;
  EB_Number   oldentnr;
  int32        indx0 = AUTO;
  logical     term  = NO;

BEGINSEQ
  if ( !(kcbptr = refsakcb->get_key_def()) )         LEAVESEQ

  if ( oldinst )
  {
    SDBRESET
    oldinst = GetOldKeyInstance(intiptr,oldinst);
    new_ckh.ckhopen(instptr,NULL);                   SDBCERR
    old_ckh.ckhopen(oldinst,instptr);                SDBCERR
  }
  else
  {
    oldentnr  = WSGetID(AUTO);
    if ( oldentnr != entnr )                // es koennte sein, dass das eine erlaubte Einstellung ist
    {
      if ( (indx0 = WSGetIndex(entnr)) == AUTO )     ERROR
      oldentnr = entnr;
    }
    oldkeyptr = WSGetKey(indx0,oldkey);     // muß fuer AUTO vor CheckID laufen, da der mit neuem Schlüssel verstellt
  }

  switch ( CheckID(instptr,oldinst,entnr) )     
  {
    case YES  :                                      ERROR
    case AUTO :                                      LEAVESEQ
    default   : if ( !oldinst )
                {
                  if ( !oldkeyptr || oldentnr.IsEmpty() )  
                                                     ERROR

                  if ( WSDelKey(oldkeyptr,oldentnr)) ERROR
                  if ( WSAddExt(entnr,kcbptr->GetKey(instptr,keyarea),AUTO) == AUTO )
                                                     ERROR  
                }
                else
                {
                  if ( WSDeleteID(intiptr,oldinst,entnr) )
                                                     ERROR
                  if ( WSAddID(intiptr,entnr,AUTO) ) ERROR
                }
  }
RECOVER
  term = YES;
ENDSEQ
  new_ckh.ckhclos();
  old_ckh.ckhclos();
  return(term);

}

/******************************************************************************/
/**
\brief  WSAddExt - 



\return lindx0 - 

\param  ebsnum - 
\param  skey - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSAddExt"

int32 ref :: WSAddExt (EB_Number ebsnum, char *skey, int32 lindx0 )
{

  return(AddExt(ebsnum,skey,lindx0));

}

/******************************************************************************/
/**
\brief  WSAddID - 



\return term - Termination code

\param  intiptr - 
\param  entnr - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSAddID"

logical ref :: WSAddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{

  return(AddID(intiptr,entnr,lindx0));


}

/******************************************************************************/
/**
\brief  WSCheckNewID - 



\return cond - 

\param  instptr - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSCheckNewID"

logical ref :: WSCheckNewID (void *instptr, EB_Number entnr )
{

  return(CheckNewID(instptr,entnr));

}

/******************************************************************************/
/**
\brief  WSDelKey - 



\return term - Termination code

\param  skey - 
\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSDelKey"

logical ref :: WSDelKey (char *skey, EB_Number ebsnum )
{

  return(DelKey(skey,ebsnum));

}

/******************************************************************************/
/**
\brief  WSDeleteID - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSDeleteID"

logical ref :: WSDeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{

  return(DeleteID(intiptr,oldinst,entnr));

}

/******************************************************************************/
/**
\brief  i1 - 



\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSDeleteID"

logical ref :: WSDeleteID (EB_Number entnr )
{

  return(DeleteID(entnr));

}

/******************************************************************************/
/**
\brief  WSDeleteReference - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSDeleteReference"

void ref :: WSDeleteReference ( )
{
  refs      *refsptr = GetSharedRef();
  if ( !HasWorkspace() || !refsptr )
    DeleteReference();
  else
  {  
    Unlock(NO);
    Refresh();
    refsptr->DeleteDiffListReference();
    Reset();    
  }


}

/******************************************************************************/
/**
\brief  WSGetCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSGetCount"

int32 ref :: WSGetCount ( )
{

 return (GetCount());

}

/******************************************************************************/
/**
\brief  WSGetID - 



\return ebsnum - 

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSGetID"

EB_Number ref :: WSGetID (int32 lindx0 )
{

 return (GetID(lindx0));

}

/******************************************************************************/
/**
\brief  WSGetIndex - 



\return lindx0 - 
-------------------------------------------------------------------------------
\brief  REFNGT_K - 



\param  skey - 
\param  ebsnum - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSGetIndex"

int32 ref :: WSGetIndex (char *skey, EB_Number ebsnum, logical exact )
{

  return (GetIndex(skey,ebsnum,exact));

}

/******************************************************************************/
/**
\brief  i1 - 



\param  ebsnum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSGetIndex"

int32 ref :: WSGetIndex (EB_Number ebsnum )
{

  return(GetIndex(ebsnum));

}

/******************************************************************************/
/**
\brief  WSGetKey - 



\return skey - 

\param  lindx0 - 
\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSGetKey"

char *ref :: WSGetKey (int32 lindx0, char *keyptr )
{

 return (GetKey(lindx0,keyptr));

}

/******************************************************************************/
/**
\brief  WSSetAutoIdent - 



\return cond_setting - 

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WSSetAutoIdent"

char ref :: WSSetAutoIdent (void *instptr )
{

  return ( SetAutoIdent(instptr) );
 

}

/******************************************************************************/
/**
\brief  WriteIndexEntry - 



\return term - Termination code

\param  lindx0 - 
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteIndexEntry"

logical ref :: WriteIndexEntry (int32 lindx0, void *instptr )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  ref - 



-------------------------------------------------------------------------------
\brief  REF_ - 



\param  lobhandle - 
\param  extref - 
\param  clnumb - 
\param  akcbptr - 
\param  globind - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ref"

     ref :: ref (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind )
                     : sts(),
EntryHandle(lobhandle,0,clnumb,NULL),
  refrex(extref), 
  struct_access(NULL), 
  refsakcb(akcbptr), 
  refsid(UNDEF),
  refcuri(AUTO), 
  refmod(NO),
  refglob(globind), 
  new_ckh(akcbptr ? akcbptr->get_key_def() : NULL),
  old_ckh(akcbptr ? akcbptr->get_key_def() : NULL)
{

BEGINSEQ
  if ( !akcbptr )                                    LEAVESEQ

  Initialize(akcbptr);


ENDSEQ

}

/******************************************************************************/
/**
\brief  i1 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ref"

     ref :: ref ( )
                     : sts (),
EntryHandle (),
  refrex(NULL),
  struct_access(NULL),
  refsakcb(NULL),
  refcuri(AUTO),
  refsid(UNDEF),
  refmod(NO),
  refglob(NO),
  new_ckh(NULL),
  old_ckh(NULL)
{



}

/******************************************************************************/
/**
\brief  refcrt - 



\return refptr - 

\param  lobhandle - 
\param  extref - 
\param  clnumb - 
\param  akcbptr - 
\param  globind - 
\param  pcs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refcrt"

ref *__cdecl ref :: refcrt (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind, PCSHandle *pcs_handle )
{
  ref     *refptr = NULL;

BEGINSEQ
  lobhandle->ResetError();
  if ( lobhandle->IsXMLBase() )
    refptr = new XRef (lobhandle,akcbptr);
  else switch ( akcbptr->GetOrgTyp(lobhandle->get_pif()) )
  {
    case IDB_ICBE : refptr = new icb (lobhandle,extref,clnumb,akcbptr,globind);
                    break; 
    case IDB_MVLD : refptr = new mvld(lobhandle,extref,clnumb,akcbptr,AUTO,globind);
                    break; 
/*
    case IDB_MVLY : refptr = new mvly(lobhandle,extref,clnumb,akcbptr);
                    break; 
*/
    case IDB_MVLG : refptr = new gmvl(lobhandle,extref,clnumb,akcbptr,globind);
                    break; 
    case IDB_MVLI : refptr = new mvli(lobhandle,extref,clnumb,akcbptr,AUTO,globind);
                    break; 
    case IDB_MVLN : refptr = new mvln(lobhandle,extref,clnumb,akcbptr,AUTO,globind);
                    break; 
    case IDB_MVLP : refptr = new mvlp(lobhandle,extref,clnumb,IDB_MVLP,MVLP_OLN,
                                      AUTO,akcbptr,globind);
                    break; 
    case R_REFS   : refptr = new refp(lobhandle,extref,clnumb,akcbptr,globind);
                    break;
    case R_REFP   : refptr = new refx(lobhandle,extref,clnumb,akcbptr,globind);
                    break;
    default        :                                       SDBERR(99)                                                                           
  } 
  if ( !refptr )                                           SDBERR(95)
  if ( lobhandle->GetErrorCode() )
  {
    if ( SDBERROR != 3 )                                   SDBERR(119)
    if ( extref )
      *extref = 0;
    SDBRESET    
    if ( !(refptr = refcrt(lobhandle,extref,clnumb,akcbptr,globind,pcs_handle)) )
                                                           SDBERR(119)
  }
  refptr->active_handle = pcs_handle;
RECOVER
  delete refptr;
  refptr = NULL;
ENDSEQ
  return(refptr);

}

/******************************************************************************/
/**
\brief  ~ref - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ref"

     ref :: ~ref ( )
{



}


