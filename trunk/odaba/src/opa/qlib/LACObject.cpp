/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    LACObject

\brief    Database Object handle
          Database  Object  handle  (Object  handle) are necessary for accessing
          data  in an Database Object. It  allows accessing extents that contain
          the  main instances  in a  Database Object.  The object handle for the
          root  Database Object it the database  handle ({\b {.r DBHandle}}) and
          need not to be opened explicitly. 
          An  object handle is necessary for opening collection handles (PI) for
          accessing object instances stored in extents.  
          Moreover;  the object handle  administrates transactions. Transactions
          can be started and stopped for each object handle. 
          The  object handle  allows also  defining Database Object versions for
          creating and accessing version slices for a Database Object.

\date     $Date: 2006/08/26 13:11:41,62 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "LACObject"

#include  <popa7.h>
#include  <coctp.h>
#include  <idbd.h>
#ifndef   P_ODC_NamedObject_HPP
#define   P_ODC_NamedObject_HPP
#include  <sPI.hpp>
class       ODC_NamedObject;
PI_dcl     (ODC_NamedObject)
#endif
#ifndef   DLL_ACExtend_HPP
#define   DLL_ACExtend_HPP
#include  <sACExtend.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_ACObject_HPP
#define   DLL_ACObject_HPP
#include  <sACObject.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_DiffListBuffer_HPP
#define   DLL_DiffListBuffer_HPP
#include  <sDiffListBuffer.hpp>
#include  <sDLL.h>
#endif
#ifndef   DPA_DiffListBuffer_HPP
#define   DPA_DiffListBuffer_HPP
#include  <sDiffListBuffer.hpp>
#include  <sDPA.h>
#endif
#ifndef   GSRT_ExtentListEntry_HPP
#define   GSRT_ExtentListEntry_HPP
#include  <sGSRT.h>
#endif
#ifndef   DPA_StructAccess_HPP
#define   DPA_StructAccess_HPP
#include  <sStructAccess.hpp>
#include  <sDPA.h>
#endif
#ifndef   GSRT_VersionEntry_HPP
#define   GSRT_VersionEntry_HPP
#include  <sVersionEntry.hpp>
#include  <sGSRT.h>
#endif
#ifndef   GSRT_exdEntry_HPP
#define   GSRT_exdEntry_HPP
#include  <sexdEntry.hpp>
#include  <sGSRT.h>
#endif
#include  <sACExtend.hpp>
#include  <sACHierNode.hpp>
#include  <sACNode.hpp>
#include  <sACPath.hpp>
#include  <sACPathNode.hpp>
#include  <sACRelationship.hpp>
#include  <sACSRTNode.hpp>
#include  <sACStructure.hpp>
#include  <sACTempExtent.hpp>
#include  <sACTransient.hpp>
#include  <sBNFData.hpp>
#include  <sBNFExpData.hpp>
#include  <sCSNode.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBHandle.hpp>
#include  <sDBHeader.hpp>
#include  <sDBIndex.hpp>
#include  <sDBIndexList.hpp>
#include  <sDBStructDef.hpp>
#include  <sDLL_Handle.hpp>
#include  <sDelInstEntry.hpp>
#include  <sDictionary.hpp>
#include  <sDiffListBuffer.hpp>
#include  <sDifferenceList.hpp>
#include  <sEntryEvent.hpp>
#include  <sGlobalObject.hpp>
#include  <sInternalTA.hpp>
#include  <sLDBHandle.hpp>
#include  <sODC_NamedObject.hpp>
#include  <sOperEnvironment.hpp>
#include  <sPoolTA.hpp>
#include  <sRootBaseTA.hpp>
#include  <sSDB_ObjectExt.hpp>
#include  <sSDB_ObjectVE.hpp>
#include  <sStructAccess.hpp>
#include  <sSystemObject.hpp>
#include  <sTABuffer.hpp>
#include  <sacb.hpp>
#include  <sbnode.hpp>
#include  <skmvl.hpp>
#include  <smvli.hpp>
#include  <snode.hpp>
#include  <sLACObject.hpp>


/******************************************************************************/
/**
\brief  ActivateShadowDB - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateShadowDB"

logical LACObject :: ActivateShadowDB ( )
{
  ACObject      *objptr;
  logical        term   = NO;
BEGINSEQ
  ILock(YES);     // solange Shadow-RB gesetzt ist, muss ACObject geperrt werden
  
  if ( !shadow_sal )                                 ERROR
    
  object_list->GoTop();
  while ( objptr = object_list->GetNext() )
    objptr->GetLocalACObject()->ActivateShadowDB();
  
  struct_acc_list = shadow_sal;

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddACExtent - 



\return term - Termination code

\param  acextent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddACExtent"

logical LACObject :: AddACExtent (ACExtend *acextent )
{

  ILock(YES);
  
  acextent_list.Insert(acextent);

  IUnlock();

  return(NO);
}

/******************************************************************************/
/**
\brief  AddCSNode - 



\return term - Termination code

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddCSNode"

logical LACObject :: AddCSNode (node *nodeptr )
{
  logical     term = NO;
  cs_nodes.AddTail(nodeptr);
  return(term);
}

/******************************************************************************/
/**
\brief  AddDelInstEntry - 



\return term - Termination code

\param  extnames - Extent name
\param  pifent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddDelInstEntry"

logical LACObject :: AddDelInstEntry (char *extnames, EB_Number pifent )
{
  logical                 term = NO;
BEGINSEQ
  if ( !ta_buffer )                                  LEAVESEQ

  ta_buffer->AppendDIList(new DelInstEntry(extnames,pifent,NULL));
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddEvent - 



\return term - Termination code

\param  acbptr - 
\param  event_id - Ivend type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEvent"

logical LACObject :: AddEvent (acb *acbptr, CSA_Events event_id )
{

  return ( local_events.AddEvent(acbptr->get_ebsnum(),event_id,
                                 acbptr->get_acbieh().get_iehsid(),
                                 acbptr->IsInstance())          );

}

/******************************************************************************/
/**
\brief  AddExtendRef - 



\return extref - 

\param  dbextdef - Extent definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddExtendRef"

EB_Number *LACObject :: AddExtendRef (DBExtend *dbextdef )
{
  EB_Number   *extref;
  TypeKey     &tkey = dbextdef->GetNameKey();
  int16        mbnumber;
  logical      temp_ext = NO;
  logical      extlock;
  logical      el_exist;
BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  ILock(YES);
  
  if ( object_instance->Lock() )                     ERROR
  if ( (extref = GetExtendRef(tkey)) && !extref->IsEmpty(pif) )                       
                                                     LEAVESEQ
  mbnumber = dbextdef->get_mb_number();
  if ( mbnumber != TEMP_MAIN && access_mode < PI_Update )
                                                     SDBERR(28)
  
  el_exist = extend_list->get_refrex()->IsEmpty(pif) ? NO : YES;
  
  if ( !extref )
  {
    if ( mbnumber == TEMP_MAIN || *dbextdef->fmcbname == '#' )
    {
      if ( mbnumber != TEMP_MAIN )
        dbextdef->set_mb_number(mbnumber=TEMP_MAIN);
      if ( temp_extend_list->AddExt(0,tkey,UNDEF) == AUTO )
                                                     ERROR
      temp_ext = YES;
    }
    else
      if ( extend_list->AddExt(0,tkey,UNDEF) == AUTO )
                                                     ERROR
    if ( !(extref = GetExtendRef(tkey)) )            ERROR
  }
  
  kmvl  tempmvli(this,extref,0,CUR_VERSION,YES);
                 
  if ( mbnumber == TEMP_MAIN )
    if ( (mbnumber = db_handle->GetTempMain()) == AUTO )
                                                     SDBERR(169)
  tempmvli.Setup(extref,0,mbnumber);
  tempmvli.InitialWrite();
  if ( !temp_ext )
  {
    extlock = extend_list->stsclck();
    extend_list->Lock();
    extend_list->set_refmod();
    extend_list->Save();
    local_dbhandle->Flush();
    extend_list->Unlock(extlock);
  }
  refTable       rt(this,dbextdef,NULL);
  rt.Setup(extref,0,mbnumber,PI_Write,mbnumber == TEMP_MAIN);
  
  if ( !el_exist && !extend_list->get_refrex()->IsEmpty(pif) )
    if ( WriteObjectInst() )                         ERROR

RECOVER
  extref = NULL;
ENDSEQ
  if ( this )
  {
    object_instance->Unlock();
    IUnlock();
  }
  return(extref);
}

/******************************************************************************/
/**
\brief  ChangeTimeStamp - Change time stamp for current version



\return term - Termination code

\param  version_nr - Internal version number
\param  timestamp - Date/time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeTimeStamp"

logical LACObject :: ChangeTimeStamp (uint16 version_nr, dttm timestamp )
{
  exd           version_inst(this,NULL,sizeof(SDB_ObjectVE),CUR_VERSION);
  SDB_ObjectVE *ext_ver;
  SDB_ObjectExt save_obj(*get_ExtObject());
  VersionEntry *ve_ptr;
  uint16        curversion;
  dttm          current;
  EB_Number     entnr;
  logical       locked = NO;
  logical       extlock = object_instance->stsclck();
  logical       term = NO;
BEGINSEQ
  if ( access_mode < PI_Write )                      SDBERR(198)
  if ( !extlock )
    if ( object_instance->Lock() )                   ERROR
    else
      locked = YES;
  
  version_inst.SetIEH(sizeof(SDB_ObjectExt),2,IDB_INS,0);
  ext_ver = (SDB_ObjectVE *)version_inst.GetInstance();

  if ( ReadObjectInst() )                            ERROR
  curversion = get_ExtObject()->get_version();  
  CreateVersList();  
  current.SetCurrent();
  
  if ( version_nr > curversion )                     SDBERR(205)
    
  if ( timestamp.IsEmpty() )
    timestamp.SetCurrent();
  else if ( timestamp < current )                    SDBERR(206)
  
  version_nr--;
  if ( (ve_ptr = version_list->GetEntry((char *)&version_nr)) &&
       ve_ptr->get_time_stamp() >= timestamp                     )
                                                     SDBERR(206)
  version_nr+=2;
  if ( (ve_ptr = version_list->GetEntry((char *)&version_nr)) &&
       !ve_ptr->get_time_stamp().IsEmpty()                    &&
       ve_ptr->get_time_stamp() <= timestamp                     )
                                                     SDBERR(206)
  version_nr--;
  if ( !(ve_ptr = version_list->GetEntry((char *)&version_nr)) )
                                                     SDBERR(99)
  for ( entnr = get_ExtObject()->get_version_list();  
        !entnr.IsEmpty(pif);
        entnr = ext_ver->get_next_object_ve()        )
  {
    if ( ReadVersionInst(version_inst,entnr) )       ERROR
    if ( ext_ver->get_version_number() == version_nr )
    {
      ext_ver->set_time_stamp(timestamp);
      if ( WriteVersionInst(version_inst,version_inst.get_exdebsn()) ) 
                                                     ERROR
      break;
    }
  }
  ve_ptr->get_time_stamp() = timestamp;

RECOVER
  memcpy(get_ExtObject(),&save_obj,sizeof(SDB_ObjectExt));
  term = YES;
ENDSEQ
  if ( locked )
    object_instance->Unlock();
  return(term);
}

/******************************************************************************/
/**
\brief  CheckDBEntry - 



\return sid - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckDBEntry"

int16 LACObject :: CheckDBEntry (EB_Number entnr )
{

  return( local_dbhandle->CheckDBEntry(entnr) );

}

/******************************************************************************/
/**
\brief  CheckEBI - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEBI"

logical LACObject :: CheckEBI (exd *exdptr )
{
  TABuffer  *tabuffer;
  logical    term = NO;
BEGINSEQ
  if ( exdptr->get_exdacb()->get_mod_count() )       LEAVESEQ
  
  if ( tabuffer = ta_buffer->LocateBuffer(exdptr) )
  {
    if ( tabuffer->CheckEBI(exdptr) )                ERROR
  }
  else
    if ( local_dbhandle->CheckEBI(exdptr) )          ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  i01 - 



\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckEBI"

logical LACObject :: CheckEBI (EB_Number entnr )
{

  return( local_dbhandle->CheckEBI(entnr) );

}

/******************************************************************************/
/**
\brief  CheckWProtect - 



\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical LACObject :: CheckWProtect (exd *exdptr )
{
  TABuffer               *tabuffer;
  logical                 wpmode = YES;
  wpmode = exdptr->stscnof() && ta_buffer && 
           (tabuffer = ta_buffer->LocateBuffer(exdptr->get_ta_count()))   // exd in TRansaction
           ? tabuffer->CheckWProtect(exdptr) ? YES : NO 
           : local_dbhandle->CheckWProtect(exdptr);

  return(wpmode);

}

/******************************************************************************/
/**
\brief  ClearDiffListBuffer - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClearDiffListBuffer"

void LACObject :: ClearDiffListBuffer ( )
{
  uint16         dlcount;
  ILock(YES);
  
  if ( dl_buffers )
  {
    dlcount = dl_buffers->GetSize();
    while ( dlcount-- )
      delete (*dl_buffers)[dlcount];
    dl_buffers->Clear();
  }

  IUnlock();

}

/******************************************************************************/
/**
\brief  CloseObject - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CloseObject"

logical LACObject :: CloseObject ( )
{
  ACObject      *objptr;
  ACExtend      *extptr;
  node          *nodeptr;
  ACObject::CloseObject();
  
  guid_pi.Close();
  
  delete global_object;
  global_object = NULL;
  
  while ( objptr = object_list->GetTail() )
    delete objptr;

  delete objname_pi;
  objname_pi = NULL;
  delete objid_pi;
  objid_pi = NULL;

  while ( nodeptr = cs_nodes.RemoveTail() )
    delete nodeptr;
  
  if ( acextent_tree )
  {
    BTI(ACExtend)  extent_list(acextent_list);
    extent_list.Cancel();
    while ( extptr = extent_list.GetNext() )
      extptr->CloseTopNodes();
    
    extent_list.Cancel();
    while ( extptr = extent_list.GetNext() )
      extptr->CloseExtentNode(YES);
    
    while ( extptr = acextent_list.RemoveTail() )
      delete extptr;
    delete acextent_tree;
    acextent_tree = NULL;
  }
  
  delete temp_extend_list;
  temp_extend_list = NULL;
  
  if ( extend_list )
  {
    extend_list->Save();
    delete extend_list;
    extend_list = NULL;
  }
    
  if ( db_handle && db_handle->get_root_object_list()->Find(this) )
    db_handle->get_root_object_list()->RemoveAt();
    
  delete object_instance;
  object_instance = NULL;

  if ( obj_handle )
  {
    if ( obj_handle->get_object_list()->Find(this) )
      obj_handle->get_object_list()->RemoveAt();
    delete obj_handle;
    obj_handle = NULL;
  }
  return(NO);
}

/******************************************************************************/
/**
\brief  CreateACObject - 



\return obhandle - Database Object handle
-------------------------------------------------------------------------------
\brief  i1 - 



\param  objid - Instance or index identity
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateACObject"

ACObject *LACObject :: CreateACObject (int32 objid, PIACC accopt, uint16 version_nr )
{
  ACObject     *acobject = NULL;
BEGINSEQ
  if ( !(acobject = new LACObject(this,objid,accopt,version_nr)) )
                                                     SDBERR(95)
                                                     SDBCERR
RECOVER
  delete acobject;
  acobject = NULL;
ENDSEQ
  return(acobject);
}

/******************************************************************************/
/**
\brief  i2 - 



\param  obname - 
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateACObject"

ACObject *LACObject :: CreateACObject (char *obname, PIACC accopt, uint16 version_nr )
{
  ACObject     *acobject = NULL;
BEGINSEQ
  if ( !(acobject = new LACObject(this,obname,accopt,version_nr)) )
                                                     SDBERR(95)
                                                     SDBCERR

RECOVER
  delete acobject;
  acobject = NULL;
ENDSEQ
  return(acobject);
}

/******************************************************************************/
/**
\brief  CreateEntry - 



\return entnr - 

\param  mbnumber - MainBase number
\param  sbnumber - SubBase number
\param  clnumb - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEntry"

EB_Number LACObject :: CreateEntry (int16 mbnumber, uint16 sbnumber, EB_Number clnumb, uint16 version_nr )
{
  EB_Number     entnr;

BEGINSEQ
// -->SV18
//  if ( version_nr != version && version_nr != CUR_VERSION )
//                                                    SDBERR(199)
  if ( version_nr = CUR_VERSION )
    version_nr = version;
    
  entnr = db_handle->CreateEntry(mbnumber,sbnumber,clnumb,version_nr);
RECOVER

ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  CreateNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbextdef - Extent definition
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNode"

node *LACObject :: CreateNode (DBExtend *dbextdef, PIACC accopt )
{
  node               *nodeptr = NULL;
BEGINSEQ
  if ( dbextdef->fmcbsmcb->smcbstyp == ST_VIEW )  // externally defined view
  {
    if ( !(nodeptr = new ACPath(this,dbextdef,NULL,accopt)) )  
                                                     SDBERR(95)
                                                     SDBCERR
    LEAVESEQ
  }

  switch ( dbextdef->get_acctype() )
  {  
    case AT_ODABA   : if ( !IsXMLBase() && !local_dbhandle->get_root_base() )
                                                     SDBERR(525)
                      if ( !(nodeptr = new ACProperty(this,NULL,dbextdef,NULL,accopt)) )
                                                     SDBERR(95)
                                                     SDBCERR
                      break;
    case AT_SLIST   : if ( !(nodeptr = new ACSRTNode(this,NULL,dbextdef,NULL,NULL)) )
                                                     ERROR
                      break;
    case AT_BIN     : if ( !(nodeptr = DLLHandle()->CreateNode("obina.dll",this,dbextdef,accopt,NO)) )
                                                     ERROR
                      break;
    case AT_ESDF    : if ( !(nodeptr = DLLHandle()->CreateNode("oesdf.dll",this,dbextdef,accopt,NO)) )
                                                     ERROR
                      break;
    case AT_OEL     : if ( !(nodeptr = DLLHandle()->CreateNode("ooel.dll",this,dbextdef,accopt,NO)) )
                                                     ERROR
                      break;
    case AT_ODBC    : if ( !(nodeptr = DLLHandle()->CreateNode("oodbc.dll",this,dbextdef,accopt,NO)) )
                                                     ERROR
                      break;
    case AT_COMEIN  : if ( !(nodeptr = DLLHandle()->CreateNode("ocomein.dll",this,dbextdef,accopt,NO)) )
                                                     ERROR
                      break;
    case AT_XML     : if ( !(nodeptr = DLLHandle()->CreateNode("oxml.dll",this,dbextdef,accopt,NO)) )
                                                     ERROR
                      break;
    case AT_CODE    : break;                
    default         : SDBERR(99)                
  }

RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  extnames - Extent name
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNode"

node *LACObject :: CreateNode (char *extnames, PIACC accopt )
{
  DBExtend      *dbext;
  ACExtend      *system_node;
  node          *nodeptr   = NULL;
  logical        extadd = NO;
  Dictionary    *dictptr = GetDictionary();
  TypeKey        tkey(dictptr,extnames);
  NodeTypes      node_type = NT_ACTopNode;
BEGINSEQ
  extadd = accopt > PI_Read ? YES : NO;
  
  if ( obj_overload && *tkey.Name() != '#' )
  {    
    if ( !dictptr->ProvideExtendDef(tkey) )         ERROR
    *tkey.Name() = '#';
    if ( !dictptr->GetExtendDef(tkey) )
      if ( !dictptr->CreateTempExtent(dbext,tkey) )  ERROR
    node_type = NT_ACHierNode;
  }
  
  if ( (dbext = GetDictionary()->ProvideExtendDef(tkey,GetSchemaVersion())) &&
       dbext->fmcbsmcb                                                          &&
       dbext->fmcbsmcb->smcbstyp != ST_CODE )
  { 
    if ( dbext->get_transient() || dbext->fmcbsmcb->smcbstyp == ST_VIEW ) // View Extents 
    {
      if ( !(nodeptr = CreateNode(dbext,accopt)) )ERROR
    }
    else
    {
      if ( !(system_node = ProvideACExtend(tkey,accopt,extadd)) )
                                                     ERROR
      switch ( node_type )
      {
        case NT_ACTopNode  : 
        case NT_undefined  : if ( handle_cache )
                               nodeptr = system_node->ReserveNode(accopt);
                             if ( !nodeptr )
                               if ( !(nodeptr = new ACTopNode(system_node,accopt)) )
                                                     SDBERR(95)
                                                     SDBCERR
                             if ( !strcmp(extnames,"__OBJECT") )
                               nodeptr->SetGUID();
                             break;
        case NT_ACHierNode : if ( !(nodeptr = new ACHierNode(system_node,accopt)) )
                                                     SDBERR(95)
                                                     SDBCERR
                             nodeptr->InitReference();
                             break;
        default            : SDBERR(99);
      }
    }
  }
  else  // CS-Node 
  {
    if ( !local_dbhandle->get_root_base() )          SDBERR(525)
    if ( !(nodeptr = new CSNode(this,extnames)))     SDBERR(95)
                                                     SDBCERR
    if ( nodeptr->get_nodetype() != NT_CSNode )      ERROR
    
  }


RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreateObjInst - 



\return entnr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateObjInst"

EB_Number LACObject :: CreateObjInst ( )
{
  exd            *objectarea;
  EB_Number       entnr = 0;
BEGINSEQ
  if ( !(objectarea = new exd(this,NULL,sizeof(SDB_ObjectExt))) )
                                                     ERROR
  objectarea->SetIEH(sizeof(SDB_ObjectExt),1,IDB_INS,0);
  SDB_ObjectExt ext_ob(0);
  ext_ob.ToPIF(pif);
  *(SDB_ObjectExt *)objectarea->GetInstance() = ext_ob;
  objectarea->SetPIF();
    
  if ( (entnr = CreateEntry(0,0,0)).IsEmpty() )      ERROR
  objectarea->set_exdebsn(entnr);
  if ( objectarea->Write(AUTO,(int16)AUTO) )         ERROR
  entnr.FromPIF(pif);
RECOVER
  entnr = 0;
ENDSEQ
  return(entnr);
}

/******************************************************************************/
/**
\brief  CreatePathNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  prop_path - Property path
\param  operenv - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *LACObject :: CreatePathNode (char *prop_path, OperEnvironment *operenv, PIACC accopt )
{
  node              *nodeptr = NULL;
BEGINSEQ
  nodeptr = new ACPathNode(this,prop_path,operenv,accopt);   SDBCERR
  if ( !nodeptr->IsValid() )                         ERROR
RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  parm_bnf - 
\param  operenv - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePathNode"

node *LACObject :: CreatePathNode (BNFData *parm_bnf, OperEnvironment *operenv, PIACC accopt )
{
  node              *nodeptr = NULL;
BEGINSEQ
  nodeptr = new ACPathNode(this,parm_bnf,operenv,accopt);   SDBCERR
  if ( !nodeptr->IsValid() )                         ERROR
RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreateTempExtentList - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempExtentList"

logical LACObject :: CreateTempExtentList ( )
{
  DBStructDef   *strdef;
  DBFieldDef    *flddef;
  logical        term = NO;
BEGINSEQ
  if ( !(strdef = GetDictionary()->GetStructDef("SDB_ObjectID",SYS_NSID,GetSystemVersion())) )
                                                     SDBERR(99)
  if ( !(flddef = strdef->GetEntry("extends")) )     SDBERR(99)

  if ( !(temp_extend_list = new mvli(this,NULL,0,flddef->get_index_list()->GetHead(),
                                UNDEF,NO)) )         SDBERR(95)
  temp_extend_list->stsslck(); // sichern der mvl verhindern

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateTempNode - 



\return nodeptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbfield_def - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempNode"

node *LACObject :: CreateTempNode (DBFieldDef *dbfield_def )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  nodeptr = new ACTopNode(this,dbfield_def);         SDBCERR
RECOVER
  delete nodeptr;
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  basenode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempNode"

node *LACObject :: CreateTempNode (node *basenode )
{
  node                   *nodeptr = NULL;
BEGINSEQ
  nodeptr = new ACTempExtent((bnode *)basenode);      SDBCERR

RECOVER
  nodeptr = NULL;
ENDSEQ
  return(nodeptr);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  basenode - 
\param  grouping_rule - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateTempNode"

node *LACObject :: CreateTempNode (node *basenode, char *grouping_rule )
{
  node                   *nodeptr = NULL;

  return(nodeptr);
}

/******************************************************************************/
/**
\brief  CreateVersEntry - 



\return term - Termination code

\param  version_nr - Internal version number
\param  timestamp - Date/time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateVersEntry"

logical LACObject :: CreateVersEntry (uint16 version_nr, dttm timestamp )
{
  SDB_ObjectVE ove(get_ExtObject()->get_version_list(),version_nr,timestamp);
  exd          version_inst(this,NULL,sizeof(SDB_ObjectVE),CUR_VERSION);
  logical      term = NO;
BEGINSEQ
  version_inst.SetIEH(sizeof(SDB_ObjectVE),2,IDB_INS,0);
  memcpy(version_inst.GetInstance(),&ove,sizeof(SDB_ObjectVE));
  
  version_inst.InitEXD(0,0,NO);
  if ( WriteVersionInst(version_inst,0) )            ERROR
  
  get_ExtObject()->InitVersion(version_inst.get_exdebsn(),version_nr);
  if ( WriteObjectInst() )                           ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateVersList - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateVersList"

logical LACObject :: CreateVersList ( )
{
  exd           version_inst(this,NULL,sizeof(SDB_ObjectVE));
  SDB_ObjectVE *ext_ver;
  EB_Number     entnr;
  logical       term = NO;
BEGINSEQ
  version_inst.SetIEH(sizeof(SDB_ObjectVE),2,IDB_INS,0);
  ext_ver = (SDB_ObjectVE *)version_inst.GetInstance();
  
  if ( get_ExtObject()->get_version_list().IsEmpty(pif) && access_mode == PI_Write )
    CreateVersEntry(get_ExtObject()->get_version(),dttm());

  version_list->Clear();
  for ( entnr = get_ExtObject()->get_version_list();  
        !entnr.IsEmpty(pif);
        entnr = ext_ver->get_next_object_ve()        )
  {
    if ( ReadVersionInst(version_inst,entnr) )       ERROR
    VersionEntry    ve(ext_ver->get_version_number(),ext_ver->get_time_stamp());
    if ( !version_list->AddEntry(&ve) )             ERROR
  }
  
  VersionEntry    ve(get_ExtObject()->get_version());
// 16.06.98 - war Add ohne Get und ohne Error-Abfrage  
  if ( !version_list->GetEntry(&ve) )                      // falls schon drin, wird ignoriert
    version_list->AddEntry(&ve);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeactivateShadowDB - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeactivateShadowDB"

logical LACObject :: DeactivateShadowDB ( )
{
  ACObject      *objptr;
  logical        term   = NO;
  object_list->GoTop();
  while ( objptr = object_list->GetNext() )
    objptr->GetLocalACObject()->DeactivateShadowDB();
  
  struct_acc_list = original_sal;

  IUnlock();  // --> ActivateShadowRB





  return(term);
}

/******************************************************************************/
/**
\brief  Delete - 



\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical LACObject :: Delete (exd *exdptr )
{
  EB_Number      entnr  = exdptr->get_exdebsn();
  logical        term   = NO;

BEGINSEQ
  if ( entnr.IsEmpty(pif) )                          LEAVESEQ
  if ( exdptr->get_reqversion() != version )         SDBERR(199)

  if ( ta_buffer )
  {
    if ( ta_buffer->Delete(exdptr) )                 ERROR
  }
  else
    if ( local_dbhandle->Delete(exdptr) )            ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  DeleteExtendRef - 



\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteExtendRef"

logical LACObject :: DeleteExtendRef (char *extnames )
{
  int32         lindx0;
  char         extname[ID_SIZE];
  logical      locked = NO;
  logical      term   = NO;
BEGINSEQ
  ILock(YES);
  
  if ( HasWorkspace() )                              SDBERR(341)
    
  SDBEV1(extnames,UNDEF)
  gvtxstb(extname,extnames,ID_SIZE);
  
  if ( (lindx0 = extend_list->GetIndex(extname,0,YES)) == AUTO )
                                                     ERROR
  if ( access_mode != PI_Write )                     SDBERR(28)
  if ( object_instance->Lock() )                     ERROR
  locked = YES;
    
  if ( extend_list->DelExt(lindx0) )                 ERROR
  extend_list->set_refmod();
  extend_list->Save();

RECOVER
  term = YES;
ENDSEQ
  if ( locked )
    object_instance->Unlock(); 
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  DeleteExtent - Delete extent



\return term - Termination code

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteExtent"

logical LACObject :: DeleteExtent (char *extnames )
{
  logical                 term = NO;
  // das wollen wir wohl noch machen (siehe doku(deutsch)
  return(term);
}

/******************************************************************************/
/**
\brief  ExtentExist - 



\return cond - 

\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtentExist"

logical LACObject :: ExtentExist (char *extnames )
{
  TypeKey                 tkey(extnames,0);
  logical                 cond = NO;
BEGINSEQ
  if ( !tkey )                                     ERROR

  if ( extend_list->GetIndex(tkey,0,YES) >= 0 )
    cond = YES;
RECOVER

ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  FieldReserved - 



\return cond - 

\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FieldReserved"

logical LACObject :: FieldReserved (DBFieldDef *fielddef )
{
  DBFieldDef             *flddef;
  logical                 cond = YES;
BEGINSEQ
  reserved_fields.GoTop();
  while ( flddef = reserved_fields.GetNext() )
    if ( flddef == fielddef )
      LEAVESEQ
  
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  FlushCluster - 



\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushCluster"

logical LACObject :: FlushCluster (acb *acbptr )
{


    return(!ta_buffer ? local_dbhandle->FlushCluster(acbptr) : NO);


}

/******************************************************************************/
/**
\brief  GenerateLocalEvents - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateLocalEvents"

logical LACObject :: GenerateLocalEvents ( )
{
  int32                   indx = 0;
  StructAccess           *struct_access;
  exd                    *exdarea;
  EntryEvent             *ev_ptr;
  logical                 term = NO;
  while ( ev_ptr = local_events.Get(indx++) )
  {
    if ( struct_access = (*struct_acc_list)[ev_ptr->get_sid()] )
      if ( exdarea = struct_access->GetEXD(ev_ptr->ebsnum,CUR_VERSION) )
        if ( exdarea->get_use_count() > 0 )
        {
          exdarea->ReserveInstance(NULL);
          exdarea->get_exdacb()->GenerateEvent(ev_ptr);
          exdarea->ReleaseInstance(NULL);
        }
    
    if ( server_object )
      server_events.AddEvent(*ev_ptr);
  }
  local_events.Clear();
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateServerEvents - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateServerEvents"

logical LACObject :: GenerateServerEvents ( )
{
  int32                   indx = 0;
  EntryEvent             *ev_ptr;
  logical                 term = NO;
BEGINSEQ
  if ( !server_object )                              LEAVESEQ
  
  while ( ev_ptr = server_events.Get(++indx) )
    local_dbhandle->GenerateServerEvent(ev_ptr);
  
  server_events.Clear();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetACExtend - 



\return sysnode - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetACExtend"

ACExtend *LACObject :: GetACExtend (TypeKey &tkey )
{
  ACExtend *sysnode;
BEGINSEQ
  ILock(YES);
  
  if ( sysnode = acextent_list.Get(tkey,tkey.Exact()) )  
    if ( tkey != sysnode->Name() )                 ERROR

  IUnlock();

RECOVER

ENDSEQ
  return(sysnode);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetACExtend"

ACExtend *LACObject :: GetACExtend (char *extnames )
{
  TypeKey    tkey(GetDictionary(),extnames);
  return( GetACExtend(tkey) );

}

/******************************************************************************/
/**
\brief  GetDBVersion - 



\return version - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBVersion"

uint16 LACObject :: GetDBVersion ( )
{

  return( local_dbhandle->get_db_header()->get_version() );

}

/******************************************************************************/
/**
\brief  GetDiffListEXD - 



\return exdptr - 

\param  entnr - 
\param  wslevel - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDiffListEXD"

exd *LACObject :: GetDiffListEXD (EB_Number entnr, uint8 wslevel )
{
  DiffListBuffer         *dl_buffer;
  exd                    *exdptr = NULL;
BEGINSEQ
  if ( !(dl_buffer = ProvideDLBuffer(wslevel)) )       SDBERR(99)

  exdptr = dl_buffer->Locate(entnr,AUTO,0);
RECOVER
  exdptr = NULL;
ENDSEQ
  return(exdptr);
}

/******************************************************************************/
/**
\brief  GetEBI - 



\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEBI"

logical LACObject :: GetEBI (exd *exdptr )
{
  TABuffer  *tabuffer;
  logical    term = NO;
BEGINSEQ
  if ( exdptr->get_exdacb()->get_mod_count() )       LEAVESEQ
  
  if ( tabuffer = ta_buffer->LocateBuffer(exdptr) )
  {
    tabuffer->GetEBI(exdptr);
    exdptr->set_read_ta(tabuffer->get_ta_count());
  }
  else
    if ( local_dbhandle->GetEBI(exdptr->get_exdacb()) )   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  GetEXD - 



\return exdptr - 

\param  exdarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEXD"

exd *LACObject :: GetEXD (exd *exdarea )
{
  exd          *exdptr = NULL;
  StructAccess *structacc;
BEGINSEQ
  if ( !exdarea->GetIEH()->get_iehsid() )            ERROR
    
  if ( !(structacc = GetStructAccess(exdarea->GetIEH()->get_iehsid())) )   
                                                     SDBERR(99)
  
  exdptr = structacc->GetEXD(exdarea);
RECOVER
  exdptr = NULL;
ENDSEQ
  return(exdptr);
}

/******************************************************************************/
/**
\brief  GetExtendRef - 



\return extref - 

\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtendRef"

EB_Number *LACObject :: GetExtendRef (TypeKey &tkey )
{
  EB_Number     *entnr;
  char           extname[ID_SIZE];
BEGINSEQ
  if ( !this )                                       SDBERR(99)
  
  ILock(YES);
  
  if ( !(entnr = extend_list->GetIDPointer(tkey)) )
    entnr = temp_extend_list->GetIDPointer(tkey);
RECOVER

ENDSEQ
  if ( this )
    IUnlock();
  return(entnr);
}

/******************************************************************************/
/**
\brief  GetExtent - Provide extent form Database Object



\return ext_name - 

\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtent"

char *LACObject :: GetExtent (int32 indx0 )
{
  char    *ext_name = NULL;
BEGINSEQ
  if ( !this )                                       SDBERR(70)

  nstring.Resize(RET_STR_LEN);
  if ( !(ext_name = extend_list->GetKey(indx0,(char *)nstring)) )
                                                     ERROR
  *(((char *)nstring)+ID_SIZE) = 0;
  gvtxbts(ext_name,ext_name,extend_list->mvlsrt->srtkln());
RECOVER

ENDSEQ
  return(ext_name);
}

/******************************************************************************/
/**
\brief  GetExtentList - 



\return extent_list - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtentList"

GSRT(ExtentListEntry) *LACObject :: GetExtentList ( )
{
  GSRT(ExtentListEntry)   *extlist = NULL;
  if ( extend_list )
    extlist = (GSRT(ExtentListEntry) *)extend_list->mvlsrt;
  return(extlist);
}

/******************************************************************************/
/**
\brief  GetLength - 



\return instlen - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLength"

int32 LACObject :: GetLength (acb *acbptr )
{
  TABuffer      *tabuffer;
  int32          size;
  uint16         version_nr;
BEGINSEQ
  if ( acbptr->get_ebsnum().IsEmpty(pif) )           ERROR

  if ( (version_nr = acbptr->get_version_number()) == CUR_VERSION )
    version_nr = version;
    
  for ( tabuffer = ta_buffer; tabuffer; tabuffer = tabuffer->get_high_TA() )
    if ( !tabuffer->LocateEntry(acbptr->get_ebsnum(),AUTO,version_nr) )
    {
      if ( !(size = tabuffer->GetLength(acbptr)) )   ERROR
      LEAVESEQ
    }
  
  if ( !(size = local_dbhandle->GetLength(acbptr)) ) ERROR

RECOVER
  size  = IEH;
  ResetError();
ENDSEQ
  return(size-IEH);

}

/******************************************************************************/
/**
\brief  GetLocalACObject - 



\return lobhandle - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLocalACObject"

LACObject *LACObject :: GetLocalACObject ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  GetModCount - 



\return modcount - 

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetModCount"

int16 LACObject :: GetModCount (EB_Number entnr )
{
  EB_Number   ebsnum(entnr);
  int16       sid;
  char        otype;
  logical     delind;
  int16       modcount = UNDEF;
BEGINSEQ
  ebsnum.ToPIF(pif);
  
  if ( LocateTAEntry(ebsnum,YES,CUR_VERSION) )        ERROR

  local_dbhandle->GetInstInfo(ebsnum,sid,otype,delind,modcount);
RECOVER

ENDSEQ
  return(modcount);
}

/******************************************************************************/
/**
\brief  GetStructAccess - 



\return structacc - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  sid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructAccess"

StructAccess *LACObject :: GetStructAccess (int16 sid )
{
  DBStructDef  *strdef;
  StructAccess *stracc = NULL;
  int16         abssid  = abs(sid);
  StructAccess *structacc = NULL;
BEGINSEQ
  ILock(YES);
  if ( sid == TEMPSID )                                  LEAVESEQ // no StructAccess for temporary structures
  
  if ( abssid >= struct_acc_list->GetSize() )
    struct_acc_list->SetAtGrow(abssid,NULL);

  if ( abssid && !(*struct_acc_list)[abssid] )
  {
    if ( !(strdef = (DBStructDef *)db_handle->get_dictionary()->ProvideStructDef(sid,GetSchemaVersion())) )
                                                     ERROR
    switch ( strdef->smcbatyp )
    {
      case AT_NONE    : if ( strdef->smcbstyp != ST_CODE )
                          SDBERR(99)
                        break;
      case AT_CODE    :
      case AT_ODABA   : structacc = new ACStructure(this,strdef,16,struct_acc_list == shadow_sal);
                        break;
      default         :                              ERROR
    }

    if ( !((*struct_acc_list)[abssid] = structacc) ) SDBERR(95)
//                                                   SDBCERR
  }
RECOVER
  delete (*struct_acc_list)[abssid];
  (*struct_acc_list)[abssid] = NULL;
ENDSEQ
  stracc = (*struct_acc_list)[abssid];
  IUnlock();
  return (stracc);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  strdefptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructAccess"

StructAccess *LACObject :: GetStructAccess (DBStructDef *strdefptr )
{
  StructAccess  *structacc = NULL;
BEGINSEQ
  if ( !strdefptr )                                  ERROR
  if ( !strdefptr->smcbityp ) // 20.8.98, Optimierung
    if ( !GetDictionary()->ProvideStructDef(strdefptr->smcbname) )
                                                     ERROR
  structacc = GetStructAccess(strdefptr->smcbityp);

RECOVER
  structacc = NULL;
ENDSEQ
  return(structacc);
}

/******************************************************************************/
/**
\brief  GetTADiffList - 



\return dlistptr - 

\param  entnr - 
\param  recursiv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTADiffList"

DifferenceList *LACObject :: GetTADiffList (EB_Number entnr, logical recursiv )
{
  DifferenceList        *dlistptr = NULL;
  TABuffer              *tabuffer = ta_buffer;
BEGINSEQ
  if ( !tabuffer )                                   ERROR

  dlistptr = tabuffer->GetDiffList(entnr);
  
  while ( !dlistptr && recursiv && 
          (tabuffer = tabuffer->get_high_TA()) )
    dlistptr = tabuffer->GetDiffList(entnr);

RECOVER
  dlistptr = NULL;
ENDSEQ
  return(dlistptr);
}

/******************************************************************************/
/**
\brief  GetTALevel - 



\return talevel - Transaction level

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTALevel"

int16 LACObject :: GetTALevel ( )
{

  return ( this && ta_buffer ? ta_buffer->get_ta_level() : 0);

}

/******************************************************************************/
/**
\brief  GetTimeStamp - Get date/time for version



\return timestamp - Date/time value

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTimeStamp"

dttm LACObject :: GetTimeStamp (uint16 version_nr )
{
  VersionEntry           *ve_ptr;
  dttm                    timestamp;
  if ( version_nr == USHORTMAX )
    version_nr = version;

  if ( ve_ptr = version_list->GetEntry((char *)&version_nr) )
    timestamp = ve_ptr->get_time_stamp();
//  else
//  Refresh der Object-Instanz

  return(timestamp);
}

/******************************************************************************/
/**
\brief  GetUsedLength - 



\return instlen - 

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetUsedLength"

int32 LACObject :: GetUsedLength (acb *acbptr )
{
  TABuffer  *tabuffer;
  int32       length = AUTO;
  uint16      version_nr;
BEGINSEQ
  if ( acbptr->get_ebsnum().IsEmpty(pif) )           ERROR

  if ( (version_nr = acbptr->get_version_number()) == CUR_VERSION )
    version_nr = version;
    
  tabuffer = ta_buffer;
  while ( tabuffer )
  {
    if ( !tabuffer->LocateEntry(acbptr->get_ebsnum(),AUTO,version_nr) )
    {
      if ( !(length = tabuffer->GetUsedLength(acbptr)) ) ERROR
      LEAVESEQ
    }
    tabuffer = tabuffer->get_high_TA();
  }
  
  length = local_dbhandle->GetUsedLength(acbptr);

RECOVER

ENDSEQ
  return(length);
}

/******************************************************************************/
/**
\brief  GetVersion - Get version number for the time point



\return version_nr - Internal version number

\param  timestamp - Date/time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVersion"

uint16 LACObject :: GetVersion (dttm timestamp )
{
  int16            index      = 0;
  uint16           version_nr = CUR_VERSION;
  VersionEntry    *ve_ptr;
  if ( timestamp.IsEmpty() )
    version_nr = version;
  else
    while ( ve_ptr = version_list->GetEntry(++index) )
      if ( ve_ptr->get_time_stamp().IsEmpty() ||
           timestamp <= ve_ptr->get_time_stamp() )
      {
        version_nr = ve_ptr->get_version();
        break;
      }


  return(version_nr);
}

/******************************************************************************/
/**
\brief  GetWorkspaceLevel - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWorkspaceLevel"

logical LACObject :: GetWorkspaceLevel ( )
{

  return(this && !IsXMLBase() ? local_dbhandle->GetWorkspaceLevel() : UNDEF);

}

/******************************************************************************/
/**
\brief  HasWorkspace - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasWorkspace"

logical LACObject :: HasWorkspace ( )
{

  return(this && !IsXMLBase() ? local_dbhandle->HasWorkspace() : NO);

}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbhandle - Database handle
\param  accopt - Access mode
\param  version_nr - Internal version number
\param  is_server - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical LACObject :: Initialize (DBHandle *dbhandle, PIACC accopt, uint16 version_nr, logical is_server )
{
  logical           term = NO;
BEGINSEQ
  ACObject::Initialize(dbhandle,accopt,version_nr);
  server_object = is_server;  
  
  if ( Initialize() )                                ERROR
    
  if ( dbhandle )
    if ( local_dbhandle = dbhandle->GetLocalDBHandle() )
      if ( local_dbhandle->get_current_rb() )
        pif = local_dbhandle->get_current_rb()->IsPIF();
  
  if ( this != (ACObject *)dbhandle )
  {
    if ( local_dbhandle )
      if ( Open(local_dbhandle->get_db_header()->get_root_objekt(),NULL) )
                                                   ERROR
    dbhandle->get_root_object_list()->AddTail(this);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical LACObject :: Initialize ( )
{
  logical           term = NO;
BEGINSEQ
  if ( !(original_sal = new DPA(StructAccess)(256)) )
                                                     SDBERR(95)
  struct_acc_list = original_sal;
  
  if ( !(internal_ta = new InternalTA(this)) )       SDBERR(95)
                                                     SDBCERR
  acextent_tree = new BinTree(sizeof(ACExtend),
                              offsetof(ACExtend,sys_ident),
                              sizeof(TypeKey),'C',32);
  acextent_list.SetTree(acextent_tree);

  version_list = new GSRT(VersionEntry)(20,sizeof(VersionEntry),2,1,'I',YES);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsExternalTA - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExternalTA"

logical LACObject :: IsExternalTA ( )
{
  TABuffer          *tabuffer;
  logical            cond = NO;
BEGINSEQ
  if ( !this || !(tabuffer = ta_buffer->GetTop() ) ) ERROR

  if ( tabuffer == internal_ta )                     ERROR

  cond = YES;
RECOVER
  cond = NO;
ENDSEQ
  return (cond);
}

/******************************************************************************/
/**
\brief  IsInternalTA - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInternalTA"

logical LACObject :: IsInternalTA ( )
{

  return ( this && ta_buffer == internal_ta ? YES : NO );


}

/******************************************************************************/
/**
\brief  IsModified - 



\return cond - 

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsModified"

int8 LACObject :: IsModified (exd *exdptr )
{
  uint8      modcount = exdptr->get_exdacb()->get_mod_count();
  logical    cond     = NO;
BEGINSEQ
  if ( !modcount )
  {
    if ( GetEBI(exdptr) )                           ERROR
    if ( !exdptr->get_mod_count() || exdptr->get_exdacb()->get_mod_count() )
    {
      cond = YES;
      LEAVESEQ
    }
  }
  if ( !db_handle->get_net_option() )               LEAVESEQ
  
  if ( ta_buffer->LocateBuffer(exdptr->get_ta_count()) )
                                                    LEAVESEQ
  if ( exdptr->stscnof() )                           
  {
SDBSET(666)
SDBRESET
    ERROR
  }  
  
  if ( local_dbhandle->Get_Mod(exdptr) != modcount ||
       exdptr->get_exdacb()->stsctrans()           )  
    cond = YES;
RECOVER
  cond = AUTO;
ENDSEQ
  return(cond);

}

/******************************************************************************/
/**
\brief  IsOpened - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOpened"

logical LACObject :: IsOpened ( )
{

  return ( object_instance ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsPIF - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPIF"

logical LACObject :: IsPIF ( )
{

  return(local_dbhandle ? local_dbhandle->IsPIF() : NO);

}

/******************************************************************************/
/**
\brief  LACObject - Create an Database Object handle



-------------------------------------------------------------------------------
\brief  i0 - 



\param  dbhandle - Database handle
\param  accopt - Access mode
\param  version_nr - Internal version number
\param  is_server - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LACObject"

     LACObject :: LACObject (DBHandle *dbhandle, PIACC accopt, uint16 version_nr, logical is_server )
                     : ACObject (),
  object_instance(NULL),
  extend_list(NULL),
  acextent_tree(NULL),
  temp_extend_list(NULL),
  version_list(NULL),
  ta_buffer(NULL),
  ta_count(0),
  internal_ta(NULL),
  struct_acc_list(NULL),
  local_dbhandle(NULL),
  server_object(NO),
  global_object(NULL),
  shadow_sal(NULL),
  original_sal(NULL),
  dl_buffers(NULL),
  handle_cache(NO),
  pif(NO)
{

BEGINSEQ
  SDBCERR
  
  Initialize(dbhandle,accopt,version_nr,is_server);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i04 - 



\param  lobhandle_ref - 
\param  gl_object - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LACObject"

     LACObject :: LACObject (LACObject &lobhandle_ref, logical gl_object )
                     : ACObject (lobhandle_ref,gl_object),
  object_instance(NULL),
  extend_list(NULL),
  acextent_tree(NULL),
  temp_extend_list(NULL),
  version_list(NULL),
  ta_buffer(NULL),
  ta_count(0),
  internal_ta(NULL),
  struct_acc_list(NULL),
  local_dbhandle(lobhandle_ref.get_local_dbhandle()),
  server_object(NO),
  global_object(NULL),
  shadow_sal(NULL),
  original_sal(NULL),
  dl_buffers(NULL),
  handle_cache(NO),
  pif(NO)
{

BEGINSEQ
  SDBCERR
  
  ACObject::Initialize();
  Initialize();
  
  if ( local_dbhandle )
    pif = local_dbhandle->get_current_rb()->IsPIF();
  
  if ( Open(local_dbhandle->get_db_header()->get_root_objekt(),NULL) )
                                                   ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i1 - 



\param  obhandle - Database Object handle
\param  objid - Instance or index identity
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LACObject"

     LACObject :: LACObject (ACObject *obhandle, int32 objid, PIACC accopt, uint16 version_nr )
                     : ACObject (obhandle,objid,accopt,version_nr),
  object_instance(NULL),
  extend_list(NULL),
  acextent_tree(NULL),
  temp_extend_list(NULL),
  version_list(NULL),
  ta_buffer(NULL),
  ta_count(0),
  internal_ta(NULL),
  struct_acc_list(NULL),
  local_dbhandle(NULL),
  server_object(NO),
  global_object(NULL),
  shadow_sal(NULL),
  original_sal(NULL),
  dl_buffers(NULL),
  handle_cache(NO),
  pif(NO)
{
  PI(SDB_ObjectID)  &obj_pi = *obhandle->get_objid_pi();
  EB_Number          ebsnum;
BEGINSEQ
  SDBCERR
  
  ACObject::Initialize();
  Initialize();
  
  if ( local_dbhandle = obhandle->get_db_handle()->GetLocalDBHandle() )
    pif = local_dbhandle->get_current_rb()->IsPIF();
  
  if ( (ebsnum = obj_pi.GetID((char *)&objid)).IsEmpty() )
                                                     SDBERR(62)
  obj_pi.Cancel();

  if ( Open(ebsnum,obhandle) )                       ERROR  


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i2 - 



\param  obhandle - Database Object handle
\param  obname - 
\param  accopt - Access mode
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LACObject"

     LACObject :: LACObject (ACObject *obhandle, char *obname, PIACC accopt, uint16 version_nr )
                     : ACObject (obhandle,obname,accopt,version_nr),
  object_instance(NULL),
  extend_list(NULL),
  acextent_tree(NULL),
  temp_extend_list(NULL),
  version_list(NULL),
  ta_buffer(NULL),
  ta_count(0),
  internal_ta(NULL),
  struct_acc_list(NULL),
  local_dbhandle(NULL),
  server_object(NO),
  global_object(NULL),
  shadow_sal(NULL),
  original_sal(NULL),
  dl_buffers(NULL),
  handle_cache(NO),
  pif(NO)
{
  PI(ODC_NamedObject)  &obj_pi = *obhandle->get_objname_pi();
  EB_Number             ebsnum;
  char                  name[40];
BEGINSEQ
  SDBCERR
  
  ACObject::Initialize();
  Initialize();
  
  if ( local_dbhandle = obhandle->get_db_handle()->GetLocalDBHandle() )
    pif = local_dbhandle->get_current_rb()->IsPIF();
  
  SDBEV1(obname,40)
  if ( !obj_pi.Provide(gvtxstb(name,obname,40)) )    SDBERR(63)

  if ( (ebsnum = obj_pi.Get()->object_ref).IsEmpty() )
  {
    if ( (ebsnum = CreateObjInst()).IsEmpty() )      SDBERR(63)
    obj_pi->object_ref = ebsnum;
    obj_pi.Modify();  
    obj_pi.Save();                                  SDBCERR
  }

  obj_pi.Cancel();

  if ( Open(ebsnum,obhandle) )                      ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i21 - 



\param  data_source_name - Data source name
\param  accmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LACObject"

     LACObject :: LACObject (char *data_source_name, PIACC accmode )
                     : ACObject (),
  object_instance(NULL),
  extend_list(NULL),
  acextent_tree(NULL),
  temp_extend_list(NULL),
  version_list(NULL),
  ta_buffer(NULL),
  ta_count(0),
  internal_ta(NULL),
  struct_acc_list(NULL),
  local_dbhandle(NULL),
  server_object(NO),
  global_object(NULL),
  shadow_sal(NULL),
  original_sal(NULL),
  dl_buffers(NULL),
  handle_cache(NO),
  pif(NO)
{
  Services           *services = SystemServices();
BEGINSEQ
  if ( !services )                                   SDBERR(99)

  strcpy(ds_handle->data_source,data_source_name);

  ds_handle = new DataSourceHandle();
  services->SetupDataSource(ds_handle);

  if ( ds_handle->Open(ds_handle->client,PI_Read) )  ERROR
  
  obj_handle       = ds_handle->object_handle.get_obhandle(); 
  db_handle        = obj_handle->get_db_handle();
  access_mode      = obj_handle->get_access_mode(); 
  version          = obj_handle->get_version();
  
  ACObject::Initialize();
  
  pif = local_dbhandle->get_current_rb()->IsPIF();
  if ( Open(local_dbhandle->get_db_header()->get_root_objekt(),NULL) )
                                                   ERROR
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i3 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LACObject"

     LACObject :: LACObject ( )
                     : ACObject (),
  object_instance(NULL),
  extend_list(NULL),
  acextent_tree(NULL),
  temp_extend_list(NULL),
  version_list(NULL),
  ta_buffer(NULL),
  ta_count(0),
  internal_ta(NULL),
  struct_acc_list(NULL),
  local_dbhandle(NULL),
  server_object(NO),
  global_object(NULL),
  shadow_sal(NULL),
  original_sal(NULL),
  dl_buffers(NULL),
  handle_cache(NO),
  pif(NO)
{




}

/******************************************************************************/
/**
\brief  LocateTAEntry - 



\return cond - 

\param  entnr - 
\param  shadow_opt - 
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateTAEntry"

logical LACObject :: LocateTAEntry (EB_Number entnr, logical shadow_opt, uint16 version_nr )
{
  TABuffer      *tabuffer;
  logical        cond = YES;
BEGINSEQ
  if ( version_nr == CUR_VERSION )
    version_nr = version;
    
  for ( tabuffer = ta_buffer; tabuffer; tabuffer = tabuffer->get_high_TA() )
    if ( !tabuffer->LocateEntry(entnr,shadow_opt,version_nr) )
      LEAVESEQ
  
  cond = NO;
ENDSEQ
  return(cond);

}

/******************************************************************************/
/**
\brief  Lock - 



\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical LACObject :: Lock (acb *acbptr )
{


// was ist, wenn der EBI aus der Transaktion kommt?
  
  return( acbptr->get_ebsnum().IsEmpty(pif) 
          ? NO 
          : local_dbhandle->Lock(acbptr) );


}

/******************************************************************************/
/**
\brief  LockInternal - 



\return term - Termination code

\param  exdptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockInternal"

logical LACObject :: LockInternal (exd *exdptr, logical wait )
{

  return ( exdptr->get_exdebsn().IsEmpty(pif) 
           ? NO 
           : local_dbhandle->LockInternal(exdptr,wait) );

}

/******************************************************************************/
/**
\brief  LockKey - 



\return term - Termination code

\param  entnr - 
\param  db_index - 
\param  keyptr - 
\param  owner_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LockKey"

logical LACObject :: LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{

  return( local_dbhandle->LockKey(entnr,db_index,keyptr,owner_id) );

}

/******************************************************************************/
/**
\brief  NewVersion - Create new version



\return term - Termination code

\param  timestamp - Date/time value
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NewVersion"

logical LACObject :: NewVersion (dttm timestamp, uint16 version_nr )
{
  exd           version_inst(this,NULL,sizeof(SDB_ObjectVE),CUR_VERSION);
  SDB_ObjectVE *ext_ver;
  SDB_ObjectExt save_obj(*get_ExtObject());
  uint16        curversion;
  EB_Number     entnr;
  logical       locked = NO;
  logical       term = NO;
BEGINSEQ
  if ( access_mode < PI_Write )                      SDBERR(198)
  
  // hier mus noch zusätzlich Workspace::IsEmpty(recursive=YES) abgefragt werden, 
  // da für inaktive workspaces versions erzeugt werden können.
  if ( HasWorkspace() )                              SDBERR(363)
  
  if ( object_instance->Lock() )                     ERROR
  locked = YES;
  if ( ReadObjectInst() )                            ERROR
  curversion = get_ExtObject()->get_version();  
  CreateVersList();
    
  if ( version_nr == USHORTMAX )
    version_nr = curversion + 1;
  if ( version_nr != curversion+1 )                  SDBERR(178)
  
  entnr = get_ExtObject()->get_version_list();
  version_inst.SetIEH(sizeof(SDB_ObjectVE),2,IDB_INS,0);
  ext_ver = (SDB_ObjectVE *)version_inst.GetInstance();
  
  if ( entnr.IsEmpty(pif) )                          SDBERR(99)
  ReadVersionInst(version_inst,entnr);
    
  if ( ext_ver->get_time_stamp().IsEmpty() || timestamp > ext_ver->get_time_stamp() )
    if ( ChangeTimeStamp(curversion,timestamp) )     ERROR
  
  if ( CreateVersEntry(version_nr,dttm()) )          ERROR
  CreateVersList();
RECOVER
  memcpy(get_ExtObject(),&save_obj,sizeof(SDB_ObjectExt));
  term = YES;
ENDSEQ
  if ( locked )
    object_instance->Unlock();
  return(term);
}

/******************************************************************************/
/**
\brief  Open - 



\return term - Termination code

\param  ebsnum - 
\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical LACObject :: Open (EB_Number ebsnum, ACObject *obhandle )
{
  DBStructDef   *strdef;
  DBFieldDef    *flddef;
  DBObjectHandle ob_handle(this);
  logical        term = NO;
  logical        newobj;
BEGINSEQ
  ebsnum.ToPIF(pif);
  if ( !(object_instance = new exd(this,NULL,sizeof(SDB_ObjectExt),CUR_VERSION)) )
                                                     ERROR
  object_instance->SetIEH(sizeof(SDB_ObjectExt),1,IDB_INS,0);
  object_instance->InitEXD(ebsnum,0,NO);
  
  if ( ((SystemObject *)(ACObject *)this)->VersionCheck() )      ERROR
  
  if ( ReadObjectInst() )                            ERROR
  
  CreateVersList();      // das stand früher ganz hinten!
  if ( ACObject::SetActVersion(obhandle) )           ERROR
  
  if ( !(strdef = GetDictionary()->GetStructDef("SDB_ObjectID",SYS_NSID,GetSystemVersion())) )
                                                     SDBERR(99)
  if ( !(flddef = strdef->GetEntry("extends")) )     SDBERR(99)

  if ( (newobj = get_ExtObject()->get_extends().IsEmpty(pif)) && access_mode < PI_Write )
                                                     SDBERR(28)
                    
  if ( !(extend_list = new mvli(this,get_ExtObject()->get_extends_ptr(),0,
                                flddef->get_index_list()->GetHead(),
                                UNDEF,YES)) )        SDBERR(95)
                                                     SDBCERR
  if ( newobj )  // für neue Objects müssen wir die Extent-Liste initialisieren
  {
    if ( extend_list->InitialWrite() )               ERROR
    if ( WriteObjectInst() )                         ERROR
  }
  extend_list->SetVersion(version);

  if ( CreateTempExtentList() )                      ERROR
  
  CreateContext(); 
  if ( ACObject::OpenPIs() )                          ERROR
  
  if ( newobj )
  {
    if ( extend_list->Save() )                       ERROR
    if ( WriteObjectInst() )                         ERROR
  }
  
  if ( ((SystemObject *)(ACObject *)this)->VersionChecka() )
                                                     ERROR
  ACObject::Open(ebsnum,obhandle);

  if ( local_dbhandle->get_shadow_rb() )
  {
    if ( !(shadow_sal = new DPA(StructAccess)(256)) )
                                                     SDBERR(95)
    if ( !(dl_buffers = new DPA(DiffListBuffer)(10)) )
                                                     SDBERR(95)
  }
  extend_list->SetShadowWrite(WRITE_EXTEND_LIST);
  guid_pi.Open(ob_handle,"__OBJECT",access_mode);
  
  handle_cache = TestSysVariable("HANDLE_CACHE","YES");
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideACExtend - 



\return acext_ptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  tkey - 
\param  accopt - Access mode
\param  extadd - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideACExtend"

ACExtend *LACObject :: ProvideACExtend (TypeKey &tkey, PIACC accopt, logical extadd )
{
  DBExtend     *extdef;
  StructAccess *acstruct;
  ACExtend     *sysnode;
  Dictionary   *dictionary = db_handle->get_dictionary();
  char          extnames[256];
  logical       newext = NO;
BEGINSEQ
  ILock(YES);
  
  if ( !tkey )                                       ERROR
  tkey.ScopedName(dictionary,extnames,sizeof(extnames)-1);

  if ( sysnode = GetACExtend(tkey) )
  {
    if ( !sysnode->get_extend_node() )               ERROR
    if ( sysnode->Upgrade(NULL,accopt) )             ERROR
    LEAVESEQ
  }
  SDBEV1(tkey,UNDEF)

  if ( !(extdef = dictionary->ProvideExtendDef(tkey,db_handle->GetSchemaVersion())) )
  {
    SDBError().TraceMessage(extnames);
    sysnode = new ACExtend(this,extnames);           SDBERR(68)
  }
                                                   
  if ( extdef->fmcbsmcb->smcbstyp == ST_CODE )       SDBERR(126)
    
  if ( extdef->fmcbsmcb->smcbatyp == AT_ODABA )
    if ( !(acstruct = GetStructAccess(extdef->fmcbityp)) )
                                                     ERROR
  newext = YES;
  if ( !(sysnode = new ACExtend(this,extdef,NULL,accopt,extadd)) )
                                                     SDBERR(95)
                                                     SDBCERR
RECOVER
  if ( newext )
    delete sysnode;
  sysnode = NULL;
ENDSEQ
  IUnlock();
  return(sysnode);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  extnames - Extent name
\param  accopt - Access mode
\param  extadd - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideACExtend"

ACExtend *LACObject :: ProvideACExtend (char *extnames, PIACC accopt, logical extadd )
{
  Dictionary   *dictionary = db_handle->get_dictionary();
  TypeKey       tkey(dictionary,extnames);
// global extents:
// N::E.C opens extent E in name space N ignoring C
  
  return( ProvideACExtend(tkey,accopt,extadd) );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  dbextdef - Extent definition
\param  ac_baseext - 
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideACExtend"

ACExtend *LACObject :: ProvideACExtend (DBExtend *dbextdef, ACExtend *ac_baseext, PIACC accopt )
{
  ACExtend *sysnode;
  logical   newext = NO;
BEGINSEQ
  if ( sysnode = GetACExtend(dbextdef->fmcbname) )
  {
    if ( sysnode->Upgrade(NULL,accopt) )             ERROR
    LEAVESEQ
  }
  SDBEV1(dbextdef->fmcbname,ID_SIZE)

  newext = YES;
  if ( !(sysnode = new ACExtend(this,dbextdef,ac_baseext,accopt,accopt > PI_Read)) )
                                                     SDBERR(95)
                                                     SDBCERR
RECOVER
  if ( newext )
    delete sysnode;
  sysnode = NULL;
ENDSEQ
  return(sysnode);
}

/******************************************************************************/
/**
\brief  i2 - 



\param  extnames - Extent name
\param  accopt - Access mode
\param  acrelptr - 
\param  extadd - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideACExtend"

ACExtend *LACObject :: ProvideACExtend (char *extnames, PIACC accopt, ACRelationship *acrelptr, logical extadd )
{
  ACExtend               *acext_ptr;
BEGINSEQ
  if ( *extnames != '.' )
    acext_ptr = ProvideACExtend(extnames,accopt,extadd);
  else
  {
    if ( !(acext_ptr = new ACExtend(extnames,accopt,acrelptr)) )
                                                     SDBERR(95)
                                                     SDBCERR
  }

RECOVER
  delete acext_ptr;
  acext_ptr = NULL;
ENDSEQ
  return(acext_ptr);
}

/******************************************************************************/
/**
\brief  ProvideCSRef - 



\return extref - 

\param  tkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideCSRef"

EB_Number *LACObject :: ProvideCSRef (TypeKey &tkey )
{
  LACObject   *sys_object;
  EB_Number   *extref = NULL;
  logical      locked = NO;
BEGINSEQ
  ILock(YES);
  SDBEV1(tkey.Name(),ID_SIZE)
  if ( !(extref = extend_list->GetIDPointer(tkey)) )
  {
    if ( access_mode != PI_Write )                   SDBERR(28)
    
    if ( !is_global_object && db_handle->get_net_option() )
    {                                                                  // extents müssen immer außerhalb der Transaktion angelegt werden.
      if ( !(sys_object = ReserveGlobalObject()) )   SDBERR(99)
      extref = sys_object->ProvideCSRef(tkey);
      ReleaseGlobalObject();
      if ( !extref )                                 ERROR
      if ( !(extref = extend_list->GetIDPointer(tkey)) )
                                                     SDBERR(99)
    }
    else
    {
      if ( object_instance->Lock() )                 ERROR
      locked = YES;
    
      if ( extend_list->AddExt(0,tkey,UNDEF) == AUTO )
                                                     ERROR
      extref = extend_list->GetIDPointer(tkey);
  
      if ( (*extref = db_handle->CreateEntry(0,0,0)).IsEmpty() )
                                                     ERROR
      extend_list->set_refmod();
      extend_list->Save();
      local_dbhandle->Flush();
    }
  }
RECOVER
  extref = NULL;
ENDSEQ
  if ( locked )
    object_instance->Unlock();
  IUnlock();
  return(extref);
}

/******************************************************************************/
/**
\brief  ProvideDLBuffer - 



\return dl_buffer - 

\param  wslevel - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDLBuffer"

DiffListBuffer *LACObject :: ProvideDLBuffer (uint8 wslevel )
{
  DiffListBuffer         *dl_buffer = NULL;

BEGINSEQ
  ILock(YES);
  if ( !dl_buffers )                                 SDBERR(99)

  if ( wslevel >= dl_buffers->GetSize() )
    dl_buffers->SetAtGrow(wslevel,NULL);

  if ( dl_buffer = (*dl_buffers)[wslevel] )          LEAVESEQ
    
  if ( !(dl_buffer = new DiffListBuffer(this,wslevel)) )
                                                     SDBERR(95)
  (*dl_buffers)[wslevel] = dl_buffer;
RECOVER
  dl_buffer = NULL;
ENDSEQ
  IUnlock();
  return(dl_buffer);
}

/******************************************************************************/
/**
\brief  ProvideDiffListEXD - 



\return exdptr - 

\param  entnr - 
\param  wslevel - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDiffListEXD"

exd *LACObject :: ProvideDiffListEXD (EB_Number entnr, uint8 wslevel )
{
  DiffListBuffer         *dl_buffer;
  exd                    *exdptr = NULL;
BEGINSEQ
  if ( !(dl_buffer = ProvideDLBuffer(wslevel)) )     SDBERR(99)

  if ( !(exdptr = dl_buffer->ProvideEXD(entnr)) )    ERROR
  exdptr->get_exdacb()->set_ws_level(wslevel);

RECOVER
  exdptr = NULL;
ENDSEQ
  return(exdptr);
}

/******************************************************************************/
/**
\brief  ProvideTADiffList - 



\return dlistptr - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dlist_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideTADiffList"

DifferenceList *LACObject :: ProvideTADiffList (DifferenceList *dlist_ptr )
{
  DifferenceList        *dlistptr = NULL;
BEGINSEQ
  if ( !ta_buffer )                                  ERROR

  dlistptr = ta_buffer->ProvideDiffList(dlist_ptr);
RECOVER
  dlistptr = NULL;
ENDSEQ
  return(dlistptr);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  db_index - 
\param  entnr - 
\param  shared_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideTADiffList"

DifferenceList *LACObject :: ProvideTADiffList (DBIndex *db_index, EB_Number entnr, logical shared_opt )
{
  DifferenceList        *dlistptr = NULL;
BEGINSEQ
  if ( !ta_buffer )                                  ERROR 

  dlistptr = ta_buffer->ProvideDiffList(db_index,entnr,shared_opt);
RECOVER
  dlistptr = NULL;
ENDSEQ
  return(dlistptr);
}

/******************************************************************************/
/**
\brief  Read - 



\return term - Termination code

\param  exdptr - 
\param  w_instlen - 
\param  skip_ta - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical LACObject :: Read (exd *exdptr, int32 w_instlen, logical skip_ta )
{
  int32           oldlen  = exdptr->GetLength();
  int32           instlen = w_instlen == AUTO ? oldlen : w_instlen;
  TABuffer      *tabuffer;
  logical        term = NO;

BEGINSEQ
  if ( exdptr->get_exdebsn().IsEmpty(pif) )          ERROR

  if ( instlen <= 0 )
    if ( !(instlen = GetLength(exdptr->get_exdacb())) )
      instlen = exdptr->get_entry_size();
    
  sdb_error->ResetError();
  if ( !skip_ta && (tabuffer = ta_buffer->LocateBuffer(exdptr)) )
  {
    if ( !tabuffer->Read(exdptr,instlen) )           LEAVESEQ
    SDBCERR
  }
  
  if ( local_dbhandle->Read(exdptr,instlen) )        ERROR
RECOVER
  exdptr->get_exdacb()->SetLength(oldlen);
  term = YES;
  switch ( SDBERROR )
  {
    case  0 : 
    case  3 : 
    case  6 : break;
    default : SDBSET(1)
  }

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ReadObjectInst - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadObjectInst"

logical LACObject :: ReadObjectInst ( )
{
  DBObjectHandle ob_handle(this);
  logical        term = NO;
BEGINSEQ
  if ( object_instance->Read() )                     SDBERR(99)
  if ( object_instance->IsPIF() )
  {
    get_ExtObject()->FromPIF(YES);
    object_instance->ResetPIF();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReadVersionInst - 



\return term - Termination code

\param  version_inst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadVersionInst"

logical LACObject :: ReadVersionInst (exd &version_inst, EB_Number entnr )
{
  logical                 term = NO;
BEGINSEQ
  version_inst.InitEXD(entnr,0,NO);
  if ( version_inst.Read() )                      ERROR
  if ( version_inst.IsPIF() )
  {
    ((SDB_ObjectVE *)version_inst.GetInstance())->FromPIF(pif);
    version_inst.ResetPIF();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseField - 



\return term - Termination code

\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseField"

logical LACObject :: ReleaseField (DBFieldDef *fielddef )
{
  logical                 term = NO;
BEGINSEQ
  if ( !reserved_fields.Remove(fielddef) )           ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseFields - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseFields"

void LACObject :: ReleaseFields ( )
{

  reserved_fields.Clear();

}

/******************************************************************************/
/**
\brief  ReleaseGlobalObject - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseGlobalObject"

logical LACObject :: ReleaseGlobalObject ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !db_handle->get_net_option() )                LEAVESEQ
  if ( !global_object )                              ERROR
  
  term = global_object->Unlock();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseInstance - 




\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseInstance"

void LACObject :: ReleaseInstance (acb *acbptr )
{

  if ( acbptr )
    local_dbhandle->ReleaseInstance(acbptr);

}

/******************************************************************************/
/**
\brief  RemoveACExtent - Remove extent from extent list



\return term - Termination code

\param  acextent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveACExtent"

logical LACObject :: RemoveACExtent (ACExtend *acextent )
{

// not used anymore (before in ACExtend::Close()

  ILock(YES);
  
  acextent_list.Remove(acextent);

  IUnlock();

  return(NO);
}

/******************************************************************************/
/**
\brief  RemoveCSNode - 



\return term - Termination code

\param  nodeptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveCSNode"

logical LACObject :: RemoveCSNode (node *nodeptr )
{
  logical     term = NO;
  cs_nodes.Remove(nodeptr);
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveVersionEntries - 



\return term - Termination code

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveVersionEntries"

logical LACObject :: RemoveVersionEntries (uint16 version_nr )
{
  exd           version_inst(this,NULL,sizeof(SDB_ObjectVE));
  SDB_ObjectVE *ext_ver;
  EB_Number     entnr;
  logical       term = NO;
BEGINSEQ
  version_inst.SetIEH(sizeof(SDB_ObjectVE),2,IDB_INS,0);
  ext_ver = (SDB_ObjectVE *)version_inst.GetInstance();
  
  for ( entnr = get_ExtObject()->get_version_list();  
        !entnr.IsEmpty(pif);
        entnr = ext_ver->get_next_object_ve()        )
  {
    if ( ReadVersionInst(version_inst,entnr) )       ERROR
    if ( ext_ver->get_version_number() >= version_nr-1 )
    {
      ext_ver->Reset();
      version_inst.Write(sizeof(SDB_ObjectVE),(uint16)0);
      LEAVESEQ
    }
  }
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reserve - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  acbptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

logical LACObject :: Reserve (acb *acbptr, logical wait )
{
  logical   term = NO;
BEGINSEQ
  if ( acbptr->get_ebsnum().IsEmpty(pif) )           LEAVESEQ
  if ( !db_handle->get_net_option() )
  {
    if ( acbptr->stscwpt(1) && !TestSysVariable("__IGNORE_WPT__","Y") ) 
                                                     ERROR // extern schreibgeschützt
    LEAVESEQ
  }
  if ( local_dbhandle->Reserve(acbptr,wait) )        ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  i1 - 



\param  exdptr - 
\param  wait - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

logical LACObject :: Reserve (exd *exdptr, logical wait )
{

  return( exdptr->stscnof() ? NO : Reserve(exdptr->get_exdacb(),wait) );


}

/******************************************************************************/
/**
\brief  ReserveField - 



\return term - Termination code

\param  fielddef - Internal field defintion
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveField"

logical LACObject :: ReserveField (DBFieldDef *fielddef )
{
  logical                 term = NO;
BEGINSEQ
  if ( FieldReserved(fielddef) )                     ERROR

  reserved_fields.AddTail(fielddef);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReserveGlobalObject - 



\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveGlobalObject"

LACObject *LACObject :: ReserveGlobalObject ( )
{
  LACObject     *obhandle = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
  if ( !db_handle->get_net_option() )                
  {
    obhandle = this;
    LEAVESEQ
  }
  
  if ( !global_object )
  {
    obhandle = new LACObject(*this,YES);             SDBCERR
    if ( !obhandle )                                 SDBERR(95)
    global_object = new GlobalObject(obhandle);
    obhandle = NULL;
  }
  if ( global_object->Lock(YES) )                    ERROR

  obhandle = global_object->GetACObject();
RECOVER
  delete obhandle;
  obhandle = NULL;
  obhandle = NULL;
ENDSEQ
  return(obhandle);
}

/******************************************************************************/
/**
\brief  ReserveInstance - 



\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveInstance"

logical LACObject :: ReserveInstance (acb *acbptr )
{

//  if ( !acbptr->get_cluster_number().IsEmpty(pif)  )
  return(acbptr ? local_dbhandle->ReserveInstance(acbptr) : NO);

}

/******************************************************************************/
/**
\brief  ResetLastVersion - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetLastVersion"

logical LACObject :: ResetLastVersion ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  ResetStructAcc - 



\return term - Termination code

\param  structacc - 
\param  sid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetStructAcc"

logical LACObject :: ResetStructAcc (StructAccess *structacc, int16 sid )
{
  int16    abssid = abs(sid);
  logical  term   = NO;
BEGINSEQ
  ILock(YES);
  
  if ( !structacc )                                  ERROR
  if ( abssid >= struct_acc_list->GetSize() )        LEAVESEQ

  if ( !(*struct_acc_list)[abssid] )                 LEAVESEQ
  (*struct_acc_list)[abssid] = NULL;
RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  SaveExtentList - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveExtentList"

logical LACObject :: SaveExtentList ( )
{
  logical                 term = NO;
  if ( extend_list )
  {
    extend_list->set_refmod();
    extend_list->Save();
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SetServer - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetServer"

void LACObject :: SetServer ( )
{

  server_object = YES;

}

/******************************************************************************/
/**
\brief  SetStructAccess - 



\return term - Termination code

\param  structacc - 
\param  sid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStructAccess"

logical LACObject :: SetStructAccess (StructAccess *structacc, int16 sid )
{
  int16    abssid = abs(sid);
  logical  term   = NO;
BEGINSEQ
  ILock(YES);
  if ( !structacc )                                  ERROR
  if ( abssid >= struct_acc_list->GetSize() )
    struct_acc_list->SetAtGrow(abssid,NULL);

  if ( (*struct_acc_list)[abssid] )                   ERROR
  
  (*struct_acc_list)[abssid] = structacc;
RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  SetTA - 




\param  tabuffer - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTA"

void LACObject :: SetTA (TABuffer *tabuffer )
{

  ta_buffer = tabuffer;

}

/******************************************************************************/
/**
\brief  SetTransactionError - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTransactionError"

void LACObject :: SetTransactionError ( )
{

BEGINSEQ
  if ( !ta_buffer )                                  LEAVESEQ

  ta_buffer->SetError();

  ta_buffer->SetLastError();
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetVersion - Set current version



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical LACObject :: SetVersion (uint16 version_nr )
{
  VersionEntry           *ve_ptr;
  ACExtend               *extent;
  logical                 term = NO;
BEGINSEQ
  ILock(YES);
  if ( object_instance->IsModified() )
  {
    object_instance->Read();
    CreateVersList();
  }
  
  if ( version_nr == CUR_VERSION )
    version_nr = get_ExtObject()->get_version();

  if ( version == version_nr )                       LEAVESEQ
  if ( ta_buffer )                                   SDBERR(203)

  ve_ptr = version_list->GetEntry(version_list->GetCount());
  if ( version_nr > ve_ptr->get_version() )          SDBERR(198)

  acextent_list.Cancel();
  while ( extent = acextent_list.GetNext() )
    extent->Save();
  
  acextent_list.Cancel();
  while ( extent = acextent_list.GetNext() )
    extent->SaveReference();
  
  version = version_nr;
  
  extend_list->SetVersion(version);
  acextent_list.Cancel();
  while ( extent = acextent_list.GetNext() )
    extent->SetVersion(version_nr);
RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  date - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical LACObject :: SetVersion (dbdt date )
{

  return ( SetVersion(dttm(date,0)) );


}

/******************************************************************************/
/**
\brief  i2 - 



\param  timestamp - Date/time value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical LACObject :: SetVersion (dttm timestamp )
{

  return ( SetVersion(GetVersion(timestamp)) );

}

/******************************************************************************/
/**
\brief  StartTAIntern - 



\return talevel - Transaction level

\param  ext_TA - External transaction
\param  intern_TA - 
\param  w_maxnum - Maximum number of entries in transacktion (buffer size)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartTAIntern"

int16 LACObject :: StartTAIntern (logical ext_TA, logical intern_TA, int16 w_maxnum )
{
  TABuffer  *tabuffer = NULL;
  int16      talevel = UNDEF;
BEGINSEQ
  sdb_error->ResetError();
  
  // is dummy object
  if ( !object_instance )                            LEAVESEQ
  if ( access_mode == PI_Read )                      ERROR
  
  if ( intern_TA )
  {
    internal_ta->Start(ta_buffer,++ta_count);
    tabuffer = internal_ta;
  }
  else
  {
    if ( ext_TA )
      tabuffer = new RootBaseTA(this,ta_buffer,++ta_count);
    else  
      tabuffer = new PoolTA(this,ta_buffer,++ta_count,w_maxnum);
  }
                                                     
  if ( !tabuffer )                                   SDBERR(95)
                                                     SDBCERR
  ta_buffer = tabuffer;
  talevel   = tabuffer->get_ta_level();
RECOVER
  delete tabuffer;

ENDSEQ
  return(talevel);
}

/******************************************************************************/
/**
\brief  StopTA - Terminate transaction



\return term - Termination code

\param  talevel - Transaction level
\param  error_case_w - Error indication
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StopTA"

logical LACObject :: StopTA (int16 talevel, logical error_case_w )
{
  TABuffer  *tabuffer = ta_buffer;
  logical    ta_cancelled = NO;
  logical    term     = NO;
BEGINSEQ
  if ( !tabuffer )                                   ERROR
    
  // is dummy object
  if ( !object_instance )                            return(NO);
  if ( access_mode == PI_Read )                      return(YES);
  
  if ( tabuffer == internal_ta )
  {
    if ( talevel == AUTO && internal_ta->get_use_count() > 1 )
    {
      if ( error_case_w )
      {
        internal_ta->Cancel();
        term = 2;
      }
      internal_ta->Stop();                    
      LEAVESEQ
    }  
    else
      internal_ta->set_use_count(1);
  }
  
  if ( talevel == AUTO )
    talevel = tabuffer->get_ta_level();
    
  while ( tabuffer && talevel <= tabuffer->get_ta_level() )
  {
    ta_buffer = tabuffer->get_high_TA();
    
    if ( error_case_w || tabuffer->get_ta_error() )
      term = 2; // transaction canceled
      
    if ( tabuffer->get_ta_level() == 1 )
      local_dbhandle->LockRB();
          
    if ( ta_cancelled = (term == 2) )
      term = tabuffer->Cancel();
    else
      if ( tabuffer->IsEmpty() )
        term = NO;
      else 
        if ( tabuffer->get_ta_level() > 1 || !(term = RegisterTA()) )
        {
          term = tabuffer->Save();
          if ( tabuffer->get_ta_level() == 1 )
            UnregisterTA();
        }
    
    if ( term )
    {
      term = YES;
      if ( ta_buffer )
        ta_buffer->SetError();
      else
      {
        SDBISET(315)
        SDBError().DisplayMessage();
      }
    }
    
    if ( tabuffer->get_ta_level() == 1 )
    {
      if ( local_dbhandle->get_net_option() &&
           (tabuffer != internal_ta || internal_ta->GetCount() > 0) )
        local_dbhandle->Flush();
      local_dbhandle->UnlockRB();
      if ( !term )
        GenerateServerEvents();
      else
        server_events.Clear();
    }
    if ( tabuffer->get_ta_error() )
      tabuffer->RestoreError();
    tabuffer->Stop();
    
    if ( tabuffer != internal_ta )
    {
      delete tabuffer;
      local_dbhandle->SaveBuffer();
    }
    tabuffer = ta_buffer;
  }
RECOVER
  term = YES;
ENDSEQ
  if ( !ta_buffer )
    local_dbhandle->FlushClusterPool();
  if ( global_object && local_dbhandle->IsRBLocked() )
  {
    // hier suchen wir einen Lockfehler, 
    // wenn global_object NULL ist, ist es wahrscheinlich ein 
    // system-object und die werden asynchron aufgerufen.
    SDBSET(999)
    SDBRESET
  }
  return(ta_cancelled ? 2 : term);
}

/******************************************************************************/
/**
\brief  Unlock - 



\return term - Termination code

\param  acbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical LACObject :: Unlock (acb *acbptr )
{

  return( acbptr->get_ebsnum().IsEmpty(pif) 
          ? NO 
          : local_dbhandle->Unlock(acbptr) );

}

/******************************************************************************/
/**
\brief  UnlockInternal - 



\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockInternal"

logical LACObject :: UnlockInternal (exd *exdptr )
{

  return( exdptr->get_exdebsn().IsEmpty(pif) 
          ? NO 
          : local_dbhandle->UnlockInternal(exdptr) );

}

/******************************************************************************/
/**
\brief  UnlockKey - 



\return term - Termination code

\param  entnr - 
\param  db_index - 
\param  keyptr - 
\param  owner_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnlockKey"

logical LACObject :: UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id )
{

  return ( local_dbhandle->UnlockKey(entnr,db_index,keyptr,owner_id) );

}

/******************************************************************************/
/**
\brief  VersionCount - Get number of versions



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionCount"

int32 LACObject :: VersionCount ( )
{

  return( version_list ? version_list->GetCount() : 0 );

}

/******************************************************************************/
/**
\brief  VersionIntervall - Get version interval



\return timeint - Time interval

\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "VersionIntervall"

INTERVAL(dttm) LACObject :: VersionIntervall (uint16 version_nr )
{
  int16                   index = 0;
  INTERVAL(dttm)     timint;
  VersionEntry           *ve_ptr;
  if ( version_nr == CUR_VERSION )
    version_nr = version;

  if ( ve_ptr = version_list->GetEntry((char *)&version_nr) )
    timint.set_high(ve_ptr->get_time_stamp());
  if ( version_nr-- )  // funktioniert nur, wenn versionsnummern lückenlos
    if ( ve_ptr = version_list->GetEntry((char *)&version_nr) )
      timint.set_low(ve_ptr->get_time_stamp());

  return(timint);
}

/******************************************************************************/
/**
\brief  Write - 



\return term - Termination code

\param  exdptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical LACObject :: Write (exd *exdptr )
{
  EB_Number      entnr   = exdptr->get_exdebsn();
  exd           *wexdptr;
  logical        term    = NO;
BEGINSEQ
  if ( entnr.IsEmpty(pif) )                          ERROR
// -->SV18
//  if ( exdptr->get_reqversion() != version && 
//       exdptr->get_reqversion() != CUR_VERSION )     SDBERR(199)
  
  if ( ta_buffer )
  {
    if ( ta_buffer->Write(exdptr) )                  ERROR
  }
  else
  {
    wexdptr = exdptr->UpdatePIF();
    if ( db_handle->Write(wexdptr) )                 ERROR
    exdptr->UpdateFromPIF();
  }

RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  WriteObjectInst - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteObjectInst"

logical LACObject :: WriteObjectInst ( )
{
  DBObjectHandle ob_handle(this);
  logical        term = NO;
BEGINSEQ
  if ( pif && !object_instance->IsPIF() )
  {
    get_ExtObject()->ToPIF(YES);
    object_instance->SetPIF();
  }
  object_instance->stssmod();
  if ( object_instance->Write(sizeof(SDB_ObjectExt),(int16)0) )
                                                    SDBERR(99)
  if ( object_instance->IsPIF() )
  {
    get_ExtObject()->FromPIF(YES);
    object_instance->ResetPIF();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WriteVersionInst - 



\return term - Termination code

\param  version_inst - 
\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteVersionInst"

logical LACObject :: WriteVersionInst (exd &version_inst, EB_Number entnr )
{
  logical                 term = NO;
BEGINSEQ
  version_inst.InitEXD(entnr,0,NO);
  if ( pif )
  {
    ((SDB_ObjectVE *)version_inst.GetInstance())->ToPIF(YES);
    version_inst.SetPIF();
  }
  if ( version_inst.Write(sizeof(SDB_ObjectVE),(uint16)0) ) 
                                                     ERROR
  if ( version_inst.IsPIF() )
  {
    ((SDB_ObjectVE *)version_inst.GetInstance())->FromPIF(pif);
    version_inst.ResetPIF();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  get_ExtObject - 



\return objectinst - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "get_ExtObject"

SDB_ObjectExt *LACObject :: get_ExtObject ( )
{

  return((SDB_ObjectExt *)object_instance->GetInstance());

}

/******************************************************************************/
/**
\brief  ~LACObject - Destructor




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~LACObject"

     LACObject :: ~LACObject ( )
{
  uint16         strcount;
  uint16         dlcount;
  if ( db_handle )
    CloseObject();
      
  delete acextent_tree;
  acextent_tree = NULL;
  
  delete internal_ta;
  internal_ta = NULL;
  
  delete version_list;
  version_list = NULL;
  
  if ( original_sal )
  {
    strcount = original_sal->GetSize();
    while ( strcount-- )
      delete (*original_sal)[strcount];
    original_sal->Clear();
  }
  delete original_sal;
  original_sal = NULL;
  
  if ( shadow_sal )
  {
    strcount = shadow_sal->GetSize();
    while ( strcount-- )
      delete (*shadow_sal)[strcount];
    shadow_sal->Clear();
  }
  delete shadow_sal;
  shadow_sal = NULL;
  
  if ( dl_buffers )
    ClearDiffListBuffer();
  delete dl_buffers;
  dl_buffers = NULL;
  
  db_handle = NULL;

}


