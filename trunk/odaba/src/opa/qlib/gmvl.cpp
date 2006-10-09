/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    gmvl

\brief    


\date     $Date: 2006/04/11 12:33:23,76 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "gmvl"

#include  <popa7.h>
#include  <sACGenericAttr.hpp>
#include  <sDBIndex.hpp>
#include  <sDBIndexList.hpp>
#include  <sDictionary.hpp>
#include  <sEB_Number.hpp>
#include  <sENUM_Value.hpp>
#include  <sENUM_ValueList.hpp>
#include  <sLACObject.hpp>
#include  <sbinti.hpp>
#include  <sexd.hpp>
#include  <sinti.hpp>
#include  <skcb.hpp>
#include  <sref.hpp>
#include  <sgmvl.hpp>


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

logical gmvl :: AddID (inti *intiptr, EB_Number entnr, int32 lindx0 )
{
  ACGenericAttr *nodeptr;
  int32           attrtype = attr_type;
  int32           curi = AUTO;
  char          *instptr = intiptr->get_iselarea();
  int32           indx0 = 0;
  int32           curindx;
  logical        term = NO;
BEGINSEQ
  nodeptr = Bintiptr->GetGenAttrNode(GetGenAttribute(),NULL);
  curindx = nodeptr->get_nodecur();
    
// wenn der Node im Initialzustand, dürfen wir die Einstellung nicht verändern
// Es ist dann aber auch nichts hinzuzufügen.
  if ( nodeptr->get_nodeinst()->stscini() )          LEAVESEQ 
  
  while ( nodeptr->Get(indx0++,NO) )
    if ( SetAttributeType(instptr,YES) )
      if ( ref_list[attr_type]->WSAddID(Bintiptr,entnr,lindx0) )
        term = YES;
      else if ( attrtype == attr_type )
        curi = ref_list[attr_type]->refcuri;

  if ( curindx == AUTO )
//    nodeptr->Cancel();
    nodeptr->SetGenAttribute(0,NULL);
  else
  {
    nodeptr->Get(curindx,NO);
    if ( SetAttributeType(instptr,YES) && curi != AUTO )
      ref_list[attr_type]->GetID(curi);
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CheckID - 


\return cond

\param  instptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckID"

logical gmvl :: CheckID (void *instptr, void *oldinst, EB_Number entnr )
{

  return ( YES );


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

char *gmvl :: CheckMod (void *instptr, void *oldinst, char *key_area )
{

  return ( !SetAttributeType(instptr,NO) ? NULL :
           ref_list[attr_type]->CheckMod(instptr,oldinst,key_area));



}

/******************************************************************************/
/**
\brief  CheckNewID - 


\return cond

\param  instptr - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckNewID"

logical gmvl :: CheckNewID (void *instptr, EB_Number entnr )
{

  return ( !SetAttributeType(instptr,NO) ? NO :
           ref_list[attr_type]->WSCheckNewID(instptr,entnr));



}

/******************************************************************************/
/**
\brief  CreateReference - 


\return term - Termination code

\param  attrtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateReference"

logical gmvl :: CreateReference (int attrtype )
{
  logical                 extlock = stsclck();
  int32                    attrkey = attrtype; // explizite Konvertierung 
  char                   *skey = (char *)&attrkey;
  logical                 term = NO;
BEGINSEQ
  if ( !extlock && Lock() )                          ERROR
  if ( Refresh() )                                   ERROR

  if ( GetIndex(skey,0,YES) != AUTO )                LEAVESEQ
  if ( AddExt(0,skey,AUTO) == AUTO )                 ERROR
  
  SetupReferences();
  if ( ref_list[attrtype]->InitialWrite() )          ERROR
  refmod = YES;
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
\brief  i0


\param  intiptr - 
\param  oldinst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical gmvl :: DeleteID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  ACGenericAttr *nodeptr;
  char          *instptr = GetKeyInstance(intiptr);
  kcb           *kcbptr;
  char           keyarea[MAX_KEYLEN];
  int32          indx0 = 0;
  logical        term = NO;
  nodeptr = Bintiptr->GetGenAttrNode(GetGenAttribute(),NULL);
  kcbptr = index_def->get_key_def();
    
  while ( nodeptr->Get(indx0++,NO) )
    if ( !SetAttributeType(instptr,YES) )
      term = YES;
    else
    {
      if ( oldinst )
      {
        oldinst = GetOldKeyInstance(intiptr,oldinst);
        kcbptr->kcbkpt((char *)oldinst,kcbptr->kcbkgt(instptr,keyarea));
      }
      if ( ref_list[attr_type]->WSDeleteID(Bintiptr,oldinst,entnr) )
        term = YES;
    }


  return(term);
}

/******************************************************************************/
/**
\brief  i1


\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteID"

logical gmvl :: DeleteID (EB_Number entnr )
{
  int             attrtype;
  ENUM_ValueList *vlist;
  ENUM_Value     *eval;
  ref            *refptr;
  smcb           *cs_smcb;
  int32           lindx0 = 0;
  logical         term = NO;
  stsrmod();
  
  cs_smcb = refsakcb->get_key_def()->scbsmcb->GetEntry(1)->fmcbsmcb;
  vlist = (ENUM_ValueList *)cs_smcb->smcbacc;
  
  while ( eval = vlist->GetEntry(lindx0++) )
  {
    attrtype = eval->code;
    if ( attrtype > 0 && (refptr = GetReference(attrtype,NO)) )
      refptr->WSDeleteID(entnr);
      
    if ( refptr->IsModified() )
      stssmod();                    // wird nach oben nicht richtig weitergeleitet
  }
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteReference - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteReference"

void gmvl :: DeleteReference ( )
{
  int32                   index = 0;
  char                    keyarea[MAX_KEYLEN];
  int                     attrtype;
  ref                    *refptr;

  while ( mvlsrt->srtigt((int16)++index) )
  {
    attrtype = *(int32 *)GetKey(index-1,keyarea);
    if ( refptr = GetReference(attrtype,YES) )
      refptr->WSDeleteReference();
  }

  mvli::DeleteReference();

}

/******************************************************************************/
/**
\brief  GetAttributeType - 


\return attrtype - 

\param  refptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAttributeType"

int16 gmvl :: GetAttributeType (ref *refptr )
{
  int       count    = ref_list.GetSize();
  int       attrtype = UNDEF;
BEGINSEQ
  while ( ++attrtype < count )
    if ( ref_list[attrtype] == refptr )              LEAVESEQ

  ERROR
RECOVER
  attrtype = UNDEF;
ENDSEQ
  return(attrtype);
}

/******************************************************************************/
/**
\brief  GetGenAttribute - 


\return fldname - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGenAttribute"

char *gmvl :: GetGenAttribute ( )
{

  return(index_def->get_key_def()->get_kcbgfmcb()->fmcbname);

}

/******************************************************************************/
/**
\brief  GetReference - 


\return refptr - 

\param  attrtype - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetReference"

ref *gmvl :: GetReference (int attrtype, logical provide )
{
  ref                    *refptr = NULL;
BEGINSEQ
  if ( attrtype == CS_U )                            ERROR
  if ( attrtype < 0 )                                SDBERR(99)

  if ( Refresh() )                                   ERROR
    
  if ( attrtype >= ref_list.GetSize() )
    ref_list.SetAtGrow(attrtype,NULL);
  
  if ( !(refptr = ref_list[attrtype]) )
  {
    index_def->set_generic(NO);
    if ( !(refptr = refcrt(ob_handle,NULL,cluster_number,index_def,refglob,active_handle)) )
                                                     ERROR
    ref_list[attrtype] = refptr;
    refptr->stssusr1();
  }

  if ( !refptr->get_refrex() && attrtype )
  {
    if ( Refresh() )                                 ERROR
    if ( !refptr->get_refrex() )
      SetupReferences();
    if ( !refptr->get_refrex() && provide )
      if ( CreateReference(attrtype) )               ERROR
  }

RECOVER
  refptr = NULL;
ENDSEQ
  index_def->set_generic(YES);
  return(refptr);
}

/******************************************************************************/
/**
\brief  Refresh - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical gmvl :: Refresh ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( stscusr2() )                                  LEAVESEQ
    
  if ( !mvlchck() )                                  LEAVESEQ
  
  stssusr2();
  term = mvli::Refresh() || SetupReferences();
  stsrusr2();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical gmvl :: Reset ( )
{
  uint16    count = ref_list.GetSize();
  ref      *refptr;
  logical   term = NO;
  while ( count-- )
    if ( refptr = ref_list[count] )
    {
      refptr->Reset();
      refptr->set_refrex(NULL);
    }

  mvli::Reset();
  return(term);
}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical gmvl :: Save ( )
{
  uint16                  count = ref_list.GetSize();
  ref                    *refptr;
  char                   *refinst;
  logical                 term = NO;
BEGINSEQ
  while ( count-- )
  {
    if ( refptr = ref_list[count] )
      if ( refptr->Save() )
        term = YES;
  }
  
  refinst = exd_area ? exd_area->GetInstance() : NULL;
  if ( mvli::Save() )                                ERROR
  if ( exd_area && refinst != exd_area->GetInstance() )
    SetupReferences();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetAttributeType - 


\return refptr - 

\param  instptr - 
\param  provide - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAttributeType"

ref *gmvl :: SetAttributeType (void *instptr, logical provide )
{
  char           keyarea[MAX_KEYLEN];

  attr_type = *(int32 *)code_kcb->kcbkgt(((char *)instptr)+index_def->get_key_def()->get_kcbgoff(),keyarea);
  return ( attr_type > 0 ? GetReference(attr_type,provide) : NULL);


}

/******************************************************************************/
/**
\brief  SetVersion - 



\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

void gmvl :: SetVersion (uint16 version_nr )
{
  uint16    count = ref_list.GetSize();
  ref      *refptr;
  while ( count-- )
    if ( refptr = ref_list[count] )
      refptr->SetVersion(version_nr);

  mvli::SetVersion(version_nr);

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

logical gmvl :: Setup (EB_Number *extref, EB_Number clnumb, int16 w_mbnumber )
{
  logical     term = NO;
BEGINSEQ
  ref::Setup(extref,clnumb,w_mbnumber);
  if ( Refresh() )                                   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupReferences - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReferences"

logical gmvl :: SetupReferences ( )
{
  int16                   index = 0;
  int                     curi  = 0;
  EB_Number              *extref;
  int                     attrtype;
  char                    keyarea[MAX_KEYLEN];
  ref                    *refptr;
  logical                 term = NO;
BEGINSEQ
  while ( extref = (EB_Number *)mvlsrt->srtigt(++index) )
  {
    attrtype = *(int32 *)GetKey(index-1,keyarea);
    if ( attrtype <= 0 )                             SDBERR(99)
    
    if ( attrtype >= ref_list.GetSize() )
      ref_list.SetAtGrow(attrtype,NULL);
    if ( refptr = ref_list[attrtype] )
    {
      if ( refptr->stscfil() )
        refptr->set_refrex(extref);
      else
        refptr->Setup(extref,cluster_number,mb_number);
    }
    while ( ++curi < attrtype )
    {
      if ( ref_list[curi] )
        ref_list[curi]->set_refrex(NULL);
    }
    curi = attrtype;
  }

RECOVER
  term = YES;
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

logical gmvl :: UpdateID (inti *intiptr, void *oldinst, EB_Number entnr )
{
  node          *nodeptr;
  ref           *refptr;
  char           string[ID_SIZE+1];
  logical        term = NO;

BEGINSEQ
  if ( refptr = SetAttributeType(intiptr->get_iselarea(),YES) )
  { 
    gvtxbts(string,refptr->get_refsakcb()->get_key_def()->get_kcbgfmcb()->fmcbname,ID_SIZE);
    if ( !(nodeptr = intiptr->GetSubNode(string,NULL)) )  SDBERR(99)
    if ( !nodeptr->IsPositioned() )                  LEAVESEQ   // wenn generisches Attribute nicht eingestellt ist, machen wir nix!
    if ( refptr->UpdateID(intiptr,oldinst,entnr) )   ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  gmvl - 



\param  lobhandle - 
\param  extref - 
\param  clnumb - 
\param  akcbptr - 
\param  globind - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gmvl"

                        gmvl :: gmvl (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind )
                     : mvli(lobhandle,extref,clnumb,
     lobhandle->GetDictionary()->
        GetExtendDef("SDB_GenRef",0)->
        get_index_list()->GetHead(),
     AUTO,globind),
  ref_list(),
  index_def(akcbptr),
  code_kcb(NULL),
  attr_type(UNDEF)


{

BEGINSEQ
  if ( !akcbptr || !(code_kcb = akcbptr->get_key_def()->get_kcbgfmcb()->fmcbsmcb->smcbidky) )
                                                     SDBERR(99)
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  ~gmvl - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~gmvl"

                        gmvl :: ~gmvl ( )
{
  uint16    count = ref_list.GetSize();

  while ( count-- )
    delete ref_list[count];
  ref_list.Clear();

}


