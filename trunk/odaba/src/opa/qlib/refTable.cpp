/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    refTable

\brief    


\date     $Date: 2006/07/07 13:16:53,45 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "refTable"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sCSHandleList.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBHandle.hpp>
#include  <sDBIndex.hpp>
#include  <sDBIndexList.hpp>
#include  <sDictionary.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sLNode.hpp>
#include  <sPCSHandle.hpp>
#include  <sbinti.hpp>
#include  <sexd.hpp>
#include  <sgmvl.hpp>
#include  <sinti.hpp>
#include  <skmvl.hpp>
#include  <sref.hpp>
#include  <srefTable.hpp>


/******************************************************************************/
/**
\brief  AddGenericRef - 


\return term - Termination code

\param  fldname - 
\param  intiptr - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddGenericRef"

logical refTable :: AddGenericRef (char *fldname, inti *intiptr, EB_Number entnr )
{
  ref       *refptr;
  char      *attrname;
  int16      indx0 = 0;
  logical    term = NO;

BEGINSEQ
  if ( !generic )                                    LEAVESEQ
    
  while ( refptr = GetReference(++indx0) )
    if ( (attrname = refptr->GetGenAttribute()) && 
         !memcmp(attrname,fldname,ID_SIZE)           &&
         (refptr = ((gmvl *)refptr)->SetAttributeType(intiptr->get_iselarea(),YES)) )
       if ( refptr->WSAddID(intiptr,entnr,AUTO) )      ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical refTable :: AddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{
  ref       *refptr;
  int16      indx0 = 0;
  logical    term = NO;

  stsrmod();
  stsrsav();

  while ( refptr = GetReference(++indx0) )
  {
    if ( !refptr->stscold() )
    {
      if ( refptr->WSAddID(intiptr,entnr,lindx0) )
        term = YES;
      if ( refptr->IsModified() == YES )
        stssmod();
      if ( refptr->stscmod() )
        stsssav();
    }
  }

  return(term);

}

/******************************************************************************/
/**
\brief  CheckMod - 


\return cond - 

\param  instptr - 
\param  oldinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckMod"

logical refTable :: CheckMod (void *instptr, void *oldinst )
{
  ref       *refptr;
  int16      indx0 = 0;
  char       keyarea[MAX_KEYLEN];
  logical    cond  = YES;
BEGINSEQ
  while ( refptr = GetReference(++indx0) )
    if ( !refptr->stscold() )
      if ( refptr->CheckMod(instptr,oldinst,keyarea) ) LEAVESEQ

  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  CheckNew - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckNew"

logical refTable :: CheckNew ( )
{
  ref       *refptr;
  int16      indx0 = 0;
  logical    cond = NO;
  while ( refptr = GetReference(++indx0) )
    if ( refptr->stscold() )
      if ( refptr->IsTemporary() )
        cond = YES;
      else                            // setzt keymvl voraus
        if ( refptr->GetCount() > 0 )
          refptr->stsrold();
        else 
        {
          cond = YES;
          if ( refptr->get_refrex()->IsEmpty() )
          {  
            if ( refptr->InitialWrite() )
              cond = NO;
            else
            {  
              topref->refmod = YES;
              topref->Save();      
            }  
          }  
        }
        
  if ( !cond ) 
    stsrold();
  return(cond);
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

logical refTable :: CheckNewID (void *instptr, EB_Number entnr )
{
  ref       *refptr;
  int16      indx0 = 0;
  logical    term = NO;

BEGINSEQ
  while ( refptr = GetReference(++indx0) )
    if ( !refptr->stscold() )
      if ( refptr->WSCheckNewID(instptr,entnr) )
                                                    ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckWProtect - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical refTable :: CheckWProtect ( )
{
  ref                    *refptr;
  int16                   indx0 = 0;
  logical                 cond = NO;
BEGINSEQ
  while ( refptr = GetReference(++indx0) )
  {
    refptr->Refresh();
    if ( refptr->CheckWProtect() )                   ERROR
  }

RECOVER
  cond = YES;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Create - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

logical refTable :: Create ( )
{
  logical    term = NO;

BEGINSEQ
  if ( !topref || ( !topref->refglob && !keymvl ) )  LEAVESEQ
  
  if ( topref->get_refrex()->IsEmpty() )
  {
    if ( topref->InitialWrite() )                    ERROR
    stsssav();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DelGenericRef - 


\return term - Termination code

\param  fldname - 
\param  bintiptr - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelGenericRef"

logical refTable :: DelGenericRef (char *fldname, binti *bintiptr, EB_Number entnr )
{
  ref       *refptr;
  char      *attrname;
  int16      indx0 = 0;
  logical    term  = NO;
BEGINSEQ
  if ( !generic )                                    LEAVESEQ
    
  while ( refptr = GetReference(++indx0) )
    if ( (attrname = refptr->GetGenAttribute()) && 
         !memcmp(attrname,fldname,ID_SIZE)           &&
         (refptr = ((gmvl *)refptr)->SetAttributeType(bintiptr->get_iselarea(),YES)) )
      if ( refptr->WSDeleteID(bintiptr,bintiptr->GetOldInst(NULL),entnr) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
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

logical refTable :: DeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  ref       *refptr;
  int16      indx0 = 0;
  logical    term = NO;
  stsrmod();
  stsrsav();
  
  while ( refptr = GetReference(++indx0) )
  {
    if ( !refptr->stscold() )
    {
      if ( refptr->WSDeleteID(intiptr,oldinst,entnr) )
        term = YES;
      if ( refptr->IsModified() == YES )
        stssmod();
    }
  }
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

logical refTable :: DeleteID (EB_Number entnr )
{
  int32         lindx0;
  int16        indx0 = 0;
  ref         *refptr;
  EB_Number    ebsnum;
  logical      term = NO;
  stsrmod();
  stsrsav();
  
  while ( refptr = GetReference(++indx0) )
  {
    if ( !refptr->stscold() )
    {
      lindx0 = 0;
      while ( !(ebsnum = refptr->GetID(lindx0++)).IsEmpty() )
        if ( ebsnum == entnr )
          if ( refptr->DelExt(--lindx0) )
            lindx0++;
      if ( refptr->IsModified() == YES )
        stssmod();
    }
  }

  return(term);
}

/******************************************************************************/
/**
\brief  DeleteReference - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteReference"

logical refTable :: DeleteReference ( )
{
  ref       *refptr;
  int16      indx0 = 0;
  logical    term = NO;
  while ( refptr = GetReference(++indx0) )
    if ( !refptr->stscold() )
      refptr->WSDeleteReference();
  stsrlck();
  
  if ( keymvl && !keymvl->stscold())
    keymvl->DeleteReference();
  return(term);
}

/******************************************************************************/
/**
\brief  GetID - 


\return entnr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number refTable :: GetID ( )
{
  EB_Number               entnr = 0;
BEGINSEQ
  if ( !topref )                                     LEAVESEQ
  if ( !topref->get_refrex() )                       ERROR
 
  entnr = *topref->get_refrex();
RECOVER
  entnr = 0;
ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetReference - 


\return refptr - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  keynames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReference"

ref *refTable :: GetReference (char *keynames )
{
  char      name[ID_SIZE];
  refEntry *refeptr = GetEntry(gvtxstb(name,keynames,ID_SIZE));
  return ( refeptr ? refeptr->get_ref_pointer() : NULL );


}

/******************************************************************************/
/**
\brief  i1 - 


\param  indx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReference"

ref *refTable :: GetReference (int16 indx )
{
  refEntry *refeptr = GetEntry(indx);

  return ( refeptr ? refeptr->get_ref_pointer() : NULL );


}

/******************************************************************************/
/**
\brief  HasKeyLocks - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasKeyLocks"

logical refTable :: HasKeyLocks ( )
{

// müssen wir ggf. abfragen, da fremde keylocks bei der Referenzpflege 
// nicht beactet werden
// --> ACRelationship::Updatenverse
  return(NO);
}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical refTable :: Lock ( )
{
  logical    term = NO;
BEGINSEQ
  if ( !topref || stsclck() )                        LEAVESEQ
  if ( topref->Refresh() )                           ERROR
  
  if ( SetInWork(YES) )
  {
    term = 2;                                        LEAVESEQ
  } 
   
  if ( topref->ReserveEXD() )                        SDBERR(6)
  if ( topref->Lock() )                         
  {
    topref->ResetEXD();
    ERROR
  }
  stsslck();
RECOVER
  SetInWork(NO);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OldinstRequested - 


\return cond - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  curref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OldinstRequested"

logical refTable :: OldinstRequested (ref *curref )
{
  ref       *refptr;
  int16      indx0 = 0;

  oldinst_opt = NO;
  
  while ( !oldinst_opt && (refptr = GetReference(++indx0)) )
  {
    if ( refptr->get_refsakcb()->get_key_def() && 
         (curref != refptr || refptr->get_new_ckh().get_ckhcke()) )
      oldinst_opt = YES;
  }

  return(oldinst_opt);
}

/******************************************************************************/
/**
\brief  Refresh - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical refTable :: Refresh ( )
{
  ref       *refptr;
  int16      indx0 = 0;

  if ( keymvl )
  {
    keymvl->set_mod_count(0);
    keymvl->Refresh();
  }  
  while ( refptr = GetReference(++indx0) )
    if ( !refptr->stscold() )
    {
      refptr->set_mod_count(0);
      refptr->Refresh();
    }

  return(NO);
}

/******************************************************************************/
/**
\brief  RemoveReference - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveReference"

logical refTable :: RemoveReference ( )
{
  refEntry   *refeptr;
  ref        *refptr;
  while ( refeptr = GetEntry((int16)1) )
  {
    refptr = refeptr->get_ref_pointer();
    if ( !refptr->stscold() )
      refptr->Save();                 
    delete refptr;
    DeleteEntry(1);
  }
    
  delete keymvl;
  keymvl = NULL;

  return(NO);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical refTable :: Reset ( )
{
  ref       *refptr;
  int16      indx0 = 0;

  if ( keymvl )
    keymvl->Reset();
    
  while ( refptr = GetReference(++indx0) )
    if ( !refptr->stscold() )
      refptr->Reset();
  
  stssini();

  return(NO);
}

/******************************************************************************/
/**
\brief  ResetEBNumber - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetEBNumber"

void refTable :: ResetEBNumber ( )
{
  ref       *refptr;
  int16      indx0 = 0;
BEGINSEQ
  if ( !topref || !topref->get_refrex() )            LEAVESEQ
  topref->set_refrex(NULL);
  
  stsrmod();
  stsrsav();
  
  while ( refptr = GetReference(++indx0) )
  {
    refptr->set_refrex(NULL);
    refptr->stsrmod();
    refptr->stsrsav();
  }

ENDSEQ

}

/******************************************************************************/
/**
\brief  ResetNew - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetNew"

logical refTable :: ResetNew ( )
{
  ref       *refptr;
  int16      indx0 = 0;
  while ( refptr = GetReference(++indx0) )
  {
    if ( refptr->stscold() )
    {
      if ( !refptr->IsTemporary() )
        refptr->Save();
      refptr->stsrold();
    }
  }
  stsrold();
  return(NO);
}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical refTable :: Save ( )
{
  ref       *refptr;
  int16      indx0 = 0;
  logical    term = NO;

  stsrmod();
  stsrsav();

  while ( refptr = GetReference(++indx0) )
  {
    if ( !refptr->stscold() )
    {
      if ( refptr->Save() )
        term = YES;
      if ( refptr->stscmod() )
      {  
        refptr->stsrmod();
        if ( keymvl )
          keymvl->Modify();
        else
          stsssav();
      }
    }
  }
  
  if ( keymvl )
  {
    keymvl->Save();
    if ( keymvl->stscmod() )
      stsssav();
    keymvl->stsrmod();
  }
  return(term);
}

/******************************************************************************/
/**
\brief  SelectSourceRef - 


\return refptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SelectSourceRef"

ref *refTable :: SelectSourceRef ( )
{
  ref       *refptr;
  ref       *source_ref = NULL;
  int16      indx0 = 0;
  logical    cond = NO;
  while ( refptr = GetReference(++indx0) )
    if ( !refptr->stscold() && !refptr->IsTemporary())
    {
      source_ref = refptr;  // als erste Lösung. besser ist jedoch, wenn nicht generisch und empty zugelassen
      if ( !refptr->get_refsakcb()->get_no_empty() && 
           !refptr->get_refsakcb()->get_generic()     )  // sonst nicht vollständig
        break;
    }

  return(source_ref);
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

char refTable :: SetAutoIdent (void *instptr )
{
  ref       *refptr;
  int16      indx0        = 0;
  char       cond_setting = NO;
BEGINSEQ
  if ( !autoid_key )                                 LEAVESEQ
    
  while ( refptr = GetReference(++indx0) )
    if ( !refptr->stscold() )
    {
      switch ( refptr->WSSetAutoIdent(instptr) )
      {
        case ERIC : ERROR
        case YES  : cond_setting = YES;
        case NO   :
        default   : ;
      }
    }
RECOVER
  cond_setting = ERIC;
ENDSEQ
  return(cond_setting);
}

/******************************************************************************/
/**
\brief  SetInWork - 


\return term - Termination code

\param  workopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInWork"

logical refTable :: SetInWork (logical workopt )
{
  logical      term = NO;
BEGINSEQ
  if ( !this  )                                      LEAVESEQ
  if ( workopt )
  {
    if ( !topref->get_exd_area() )                   LEAVESEQ
    if ( topref->get_exd_area()->SetInWork(workopt) )
                                                     ERROR
    lock_exd = topref->get_exd_area();
    lock_exd->ReserveInstance(NULL);
  }
  else
  {
    if ( !lock_exd )                                 LEAVESEQ
    term = lock_exd->SetInWork(workopt);
    lock_exd->ReleaseInstance(NULL);
  }

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

void refTable :: SetVersion (uint16 version_nr )
{
  ref       *refptr;
  int16      indx0 = 0;
  if ( keymvl )
    keymvl->SetVersion(version_nr);
  
  while ( refptr = GetReference(++indx0) )
    refptr->SetVersion(version_nr);


}

/******************************************************************************/
/**
\brief  Setup - 


\return term - Termination code

\param  extref - 
\param  clnumb - 
\param  mbnumber - MainBase number
\param  accopt - Access mode
\param  tempmain - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical refTable :: Setup (EB_Number *extref, EB_Number clnumb, int16 mbnumber, PIACC accopt, logical tempmain )
{
  EB_Number *subext;
  ref       *refptr;
  int16      mainbase;
  logical    obj_version;
  int16      indx0  = 0;
  logical    newind = extref ? extref->IsEmpty() : YES;
  logical    term   = NO;
BEGINSEQ
  if ( topref ) 
    topref->Setup(extref,clnumb,mbnumber);
  
  if ( accopt == PI_Write )
    if ( Create() )                                  ERROR

  stsrold();
  if ( keymvl )
  {
    obj_version = (keymvl->get_version() == CUR_VERSION || 
                   keymvl->get_version() == keymvl->get_ob_handle()->get_version() ? YES : NO);
    while ( refptr = GetReference(++indx0) )
      if ( !refptr->IsTemporary() )
      {
        if ( !keymvl->ProvideExtRef(refptr,accopt) && obj_version ) 
                                                     SDBCERR
        if ( refptr->stscold() )
        {
          if ( !newind )
            stssold();
          else
            refptr->stsrold();
        }
      }
  }
  
  indx0 = 0;
  while ( refptr = GetReference(++indx0) )
    if ( refptr != topref )
    {
      mainbase = mbnumber;
      if ( refptr->IsTemporary() )
      {
//        refptr->stssold();  sonst werden temporäre Inizes nicht gefüllt, 7.7.2006
// ???       if ( (subext = refptr->get_refrex())->IsEmpty() )
        if ( (subext = refptr->get_refrex()) && !subext->IsEmpty() )
          refptr->DeleteReference();
        if ( tempmain )
          mainbase = refptr->get_ob_handle()->get_db_handle()->GetTempMain();
        // else subext = NULL; ??????
      }
      else
        if ( !keymvl )
          subext = extref;
        else    
          subext = keymvl->GetExtRef(refptr);
    
      if ( refptr->Setup(subext,clnumb,mainbase) )
        term = YES;
    }

RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical refTable :: Unlock (logical extlock )
{
  logical                 term = NO;
BEGINSEQ
  if ( !topref || !stsclck() )                       LEAVESEQ
  
  term = topref->Unlock(extlock);
  topref->ResetEXD();
    
  if ( !extlock )  
  {
    stsrlck();
    SetInWork(NO);
  }
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
\param  temp_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateID"

logical refTable :: UpdateID (inti *intiptr, void *oldinst, EB_Number entnr, logical temp_only )
{
  ref       *refptr;
  char      *instptr = intiptr->get_iselarea();
  int16      indx0 = 0;
  logical    term = NO;

  stsrmod();
  stsrsav();

  while ( refptr = GetReference(++indx0) )
  {
    if ( !refptr->stscold() )
    {
      if ( !temp_only || refptr->IsTemporary() )
      {
        if ( refptr->UpdateID(intiptr,oldinst,entnr) )
          term = YES;
        if ( refptr->IsModified() == YES )
          stssmod();
      }
    }
  }

  return(term);

}

/******************************************************************************/
/**
\brief  UpdateNew - 


\return term - Termination code

\param  intiptr - 
\param  entnr - 
\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateNew"

logical refTable :: UpdateNew (inti *intiptr, EB_Number entnr, int32 lindx0 )
{
  ref       *refptr;
  int16      indx0 = 0;
  logical    term = NO;
  stsrmod();
  stsrsav();

  while ( refptr = GetReference(++indx0) )
  {
    if ( refptr->stscold() )
    {
      if ( refptr->WSAddID(intiptr,entnr,lindx0) )
        term = YES;
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  refTable - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  lobhandle - 
\param  fielddef - Internal field defintion
\param  pcs_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refTable"

     refTable :: refTable (LACObject *lobhandle, DBFieldDef *fielddef, PCSHandle *pcs_handle )
                     : GSRT(refEntry)(1,sizeof(refEntry),
     ID_SIZE,1,'C',YES),
  keymvl(NULL), 
  topref(NULL),
  oldinst_opt(NO),
  generic(NO),
  autoid_key(NO),
  schema_version(fielddef->get_version()),
  lock_exd(NULL)
{
  ref         *refptr;
  logical      globind = fielddef->get_update();
  DBIndex     *dbindex;
  DLO(DBIndex) cursor;
BEGINSEQ
  if ( fielddef->get_multikey() && fielddef->fmcbdim != 1 ) 
// Autokorrektur: für singuläre Referenzen ist maximal ein Schlüssel für Zuordnung erlaubt
  {
    if ( !(keymvl = new kmvl(lobhandle,NULL,0,lobhandle->GetSystemVersion(),globind) ) )
                                                     ERROR
    topref = keymvl;
  }
  
  cursor = *fielddef->get_index_list();
  cursor.GoTop(); 
  while ( dbindex = cursor.GetNext() )
  { 
    dbindex->SetupIndexDef();  
    if ( dbindex->get_generic() )
      generic = YES;
    if ( dbindex->get_key_def() && dbindex->get_key_def()->scbsmcb->smcbsts.stscold() )
      autoid_key = YES;
      
    if ( !(refptr = ref::refcrt(lobhandle,NULL,0,dbindex,
                                dbindex->GetOrgTyp(lobhandle->get_pif()) != R_REFP && globind,
                                pcs_handle))) ERROR

    refEntry   refent((char *)dbindex->GetKeyName(),refptr);
    AddEntry(&refent);
    
    if ( !dbindex->get_temporary() && !keymvl )
      if ( !topref || dbindex->get_key_def() == fielddef->fmcbsmcb->smcbidky ) // oder IK
        topref = refptr;
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i1 - 


\param  refptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "refTable"

     refTable :: refTable (ref *refptr )
                     : GSRT(refEntry)(1,sizeof(refEntry),
     ID_SIZE,1,'C',YES),
  keymvl(NULL), 
  topref(refptr),
  oldinst_opt(NO),
  generic(NO),
  autoid_key(NO),
  schema_version(CUR_VERSION),
  lock_exd(NULL)
{

  refEntry   refent(refptr);
  AddEntry(&refent);

  generic    = refptr->get_refsakcb()->get_generic();
  
  if ( refptr->get_refsakcb()->get_key_def() &&
       refptr->get_refsakcb()->get_key_def()->scbsmcb->smcbsts.stscold() )
   autoid_key = YES;


}


