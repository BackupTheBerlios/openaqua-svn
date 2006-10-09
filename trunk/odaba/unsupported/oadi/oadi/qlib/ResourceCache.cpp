/********************************* Class Source Code ***************************/
/**
\package  OADI - 
\class    ResourceCache

\brief    


\date     $Date: 2006/07/09 17:50:27,15 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ResourceCache"

#include  <poadi.h>
#include  <cmacros.h>
#include  <sBinArray.hpp>
#include  <sCTX_Control.hpp>
#include  <sCTX_GUIBase.hpp>
#include  <sOADKFactory.hpp>
#include  <sOAction.hpp>
#include  <sOApplication.hpp>
#include  <sOCBitmap.hpp>
#include  <sOConstAction.hpp>
#include  <sOEventActionControl.hpp>
#include  <sOFont_.hpp>
#include  <sOFunctAction.hpp>
#include  <sOJumpAction.hpp>
#include  <sOMenAction.hpp>
#include  <sOProject.hpp>
#include  <sOResource.hpp>
#include  <sOWinAction.hpp>
#include  <sPIStack.hpp>
#include  <sResourceEntry.hpp>
#include  <sTProjectManager.hpp>
#include  <sResourceCache.hpp>


/******************************************************************************/
/**
\brief  Clear - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void ResourceCache :: Clear ( )
{
  ResourceEntry        *resent   = NULL;
  OResource            *resource = NULL;
  int32                 count    = 0;
  int32                 objid    = 0;
  logical               term     = NO;

BEGINSEQ
  if ( !this )                                       LEAVESEQ
    
  count = GetCount();  
    
  while ( count > 0 )
    if ( !(resent = (ResourceEntry *)iterator.Get(--count)) )
term = YES;
    else      
      if ( resource = resent->get_resource() )
      {
        resource->Deleting();
        DeleteEntry(resource);
      }
      else      
      {
        objid = resent->get_obj_id();  
        BinTree::DeleteEntry((char *)&objid);
      }

ENDSEQ

}

/******************************************************************************/
/**
\brief  CreateResource - 



\return resource - 

\param  entry_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateResource"

OResource *ResourceCache :: CreateResource (uint64 entry_index )
{
  PropertyHandle      *ph       = NULL;
  OResource           *resource = NULL;
  logical              term     = NO;
BEGINSEQ
  if ( ph = current_ph )
    ph->Get();
  else
  {
    if ( !void_ph.IsValid() )
      void_ph.Open(*res_db,"VOID",PI_Read);
    if ( !void_ph.Get(entry_index) )                 ERROR
    current_ph = ph = &void_ph;
  }  
  
  if ( !(resource = ADKFACTORY(ph,OResource)) )     ERROR
//  if ( !(resource = (OResource *)OADKFactory::Factory()->New(ph,"OResource)) )
//                                                     ERROR  
  resource->set_in_cache(id);

RECOVER
  delete resource;
  resource = NULL;
ENDSEQ
  return(resource);
}

/******************************************************************************/
/**
\brief  DeleteEntry - 



\return term - 

\param  pOResource - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteEntry"

logical ResourceCache :: DeleteEntry (OResource *pOResource )
{
  int32                   objid;
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       OADIERR(99)
    
  objid = pOResource->GetID();  
  BinTree::DeleteEntry((char *)&objid);
  pOResource->set_in_cache(NO);
  delete pOResource;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExistWindow - 



\return cond - 

\param  class_names - 
\param  win_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExistWindow"

logical ResourceCache :: ExistWindow (char *class_names, char *win_names )
{
  PropertyHandle   *win_ph;
  logical           cond = YES;
BEGINSEQ
  PropertyHandle ph(*res_db,"ADK_Class",PI_Read);    OADISDBCERR
  
  if ( !ph.Get(ph.StringToKey(class_names)) )        ERROR
  
  win_ph = ph.GPH("windows");
  if ( !win_ph->Get(win_ph->StringToKey(win_names)) )
                                                     ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  FreeObjEntry - 




\param  obj_entry - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeObjEntry"

void ResourceCache :: FreeObjEntry (BinSArrayObjEntry *obj_entry )
{
  OResource               *resource;
  if ( resource = ((ResourceEntry *)obj_entry)->get_resource() )
    delete resource;



}

/******************************************************************************/
/**
\brief  GetEntry - 



\return resource - 

\param  res_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

OResource *ResourceCache :: GetEntry (int32 res_id )
{
 ResourceEntry        *resource;
 OResource            *res_inst = NULL;
  if ( resource = (ResourceEntry *)iterator.Get((char *)&res_id,YES) )
    res_inst = resource->get_resource();
      

  return(res_inst);
}

/******************************************************************************/
/**
\brief  Invalidate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Invalidate"

logical ResourceCache :: Invalidate ( )
{
  ResourceEntry        *resent;
  OResource            *resource;
  int32                 indx = 0;
  logical               term  = NO;
  while ( resent = (ResourceEntry *)iterator.Get(indx++) )
    if ( resource = resent->get_resource() )
      resource->Invalidate();


  return(term);
}

/******************************************************************************/
/**
\brief  ProvideDefaultAction - 



\return pOAction - 

\param  name - 
\param  vActionType - 
\param  ctxptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideDefaultAction"

OAction *ResourceCache :: ProvideDefaultAction (char *name, ActionType vActionType, CTX_GUIBase *ctxptr )
{
  OWinAction   *wact = NULL;
  OMenAction *mact = NULL;
  OFunctAction *fact = NULL;
  OAction      *act  = NULL;
  char         *class_names;
  switch ( vActionType )
  {
    case ACT_Constant   : 
    case ACT_Document   : 
    case ACT_Expression : 
    case ACT_Jump       : 
    case ACT_ParmAction : 
    case ACT_Program    : 
    case ACT_Extended   : break;
    case ACT_Function   : if ( ctxptr ) 
                          {
                            act = fact = new OFunctAction; 
                            fact->SetProperties(name);
                          }
                          break;
    case ACT_Menu       : if ( !strcmp(name,"UserContextMenu") )
                            if ( ctxptr ) 
                            {
                              act = mact = new OMenAction();
                              mact->SetContextMenuProperty();
                            }
                          break;
    case ACT_Window     : if ( !strcmp(name,"EditEntry") )
                            if ( ctxptr && ctxptr->GetContextType() != CTXT_Document &&
                                 (class_names = ((CTX_Control *)ctxptr)->GetCurrentPropertyHandle()->GetCurrentType()) &&
                                 ExistWindow(class_names,"Edit") )
                            {
                              act = wact = new OWinAction;
                              wact->SetEditProperty(class_names,"Edit");
                            }
                          break;
    default             : ;
  }
  return(act);
}

/******************************************************************************/
/**
\brief  ProvideEntry - 



\return resource - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  res_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEntry"

OResource *ResourceCache :: ProvideEntry (int32 res_id )
{
 ResourceEntry        *resource;
 OResource            *res_inst = NULL;
BEGINSEQ
  if ( !(resource = (ResourceEntry *)iterator.Get((char *)&res_id,YES)) )
  {
    if ( CreateEntry((char *)&res_id) )              ERROR
    resource = (ResourceEntry *)iterator.Get((char *)&res_id,YES);
  }
  if ( !(res_inst = resource->get_resource()) )
    if ( res_inst = CreateResource(res_id) )
    {
      resource->Initialize(res_inst);
      if ( res_inst->Read(current_ph) )
      {
        res_inst->set_in_cache(NO);
        resource->Free();
        ERROR
      }
    }

  if ( res_inst )
    res_inst->Reserve();
RECOVER
  res_inst = NULL;
ENDSEQ
  return(res_inst);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  ph - 
\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEntry"

OResource *ResourceCache :: ProvideEntry (PropertyHandle *ph, char *name )
{
  int32                 id = 0;
  OResource            *res_inst = NULL;
BEGINSEQ
  if ( !ph )                                         ERROR
    
  if ( name && *name )
    if ( !(ph = ph->GPH(name)) )                     ERROR
  current_ph = ph;

//  if ( ph->GetCount(NO) <= 0 )                       ERROR
  if ( !(id = ph->GetLOID()) )                       ERROR

  if ( res_inst = ProvideEntry(id) )
    if ( res_inst->get_invalid() )
    {
      res_inst->Reset();
      ph->Get();
      res_inst->Read(ph);
    }
      

RECOVER
  res_inst = NULL;
ENDSEQ
  current_ph = NULL;
  return(res_inst);
}

/******************************************************************************/
/**
\brief  ReadAction - 



\return pOAction - 

\param  name - 
\param  vActionType - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadAction"

OAction *ResourceCache :: ReadAction (char *name, ActionType vActionType )
{
  OAction      *act = NULL;
  OConstAction *cact;
  OJumpAction  *jact;
  OFunctAction *fact;
  char         *ext = NULL;
BEGINSEQ
  switch ( vActionType )
  {
    case ACT_Function   : act = fact = new OFunctAction; 
                          fact->SetFunction(name);
                          LEAVESEQ 
    case ACT_Jump       : act = jact = new OJumpAction; 
                          jact->SetTarget(name);
                          LEAVESEQ 
    case ACT_Constant   : act = cact = new OConstAction; 
                          cact->SetText(name);
                          LEAVESEQ 
    case ACT_ParmAction : ext = "ADA_ParmAction";    break;
    case ACT_Document   : ext = "ADA_DocAction";     break;
    case ACT_Expression : ext = "ADA_Expression";    break;
    case ACT_Program    : ext = "ADA_PrgAction";     break;
    case ACT_Menu       : ext = "ADA_MenAction";     break;
    case ACT_Window     : ext = "ADA_WinAction";     break;
    case ACT_Extended   : NIY(0);                    break;
  }

  if ( !ext )                                        OADIERR(99)
  PropertyHandle  ph(*res_db,ext,PI_Read);           OADISDBCERR

  if ( !ph.Get(ph.StringToKey(name)) )               ERROR
  act = ADKFACTORY(&ph,OAction);
  act->Read(&ph);
//  if ( !(act = CACHE_READ(&ph,NULL,OAction)) )       OADIERR(99)  

RECOVER
  act = NULL;
ENDSEQ
  return(act);
}

/******************************************************************************/
/**
\brief  ReadBitmap - 



\return pOCBitmap - 

\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadBitmap"

OCBitmap *ResourceCache :: ReadBitmap (char *name )
{
  OCBitmap          *pOCBitmap = NULL;
BEGINSEQ
  PropertyHandle ph(*res_db,"ADKC_Bitmap",PI_Read);  OADISDBCERR

  if ( !ph.Get(ph.StringToKey(name)) )               ERROR

  if ( !(pOCBitmap = CACHE_READ(&ph,NULL,OCBitmap))) OADIERR(99)
RECOVER
  pOCBitmap = NULL;
ENDSEQ
  return(pOCBitmap);
}

/******************************************************************************/
/**
\brief  ReadEventActionControl - 



\return pOEventActionControl - 

\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadEventActionControl"

OEventActionControl *ResourceCache :: ReadEventActionControl (char *name )
{
  OEventActionControl  *pOEventActionControl = NULL;
BEGINSEQ
  if ( !act_ph.IsValid() )
  {
    act_ph.Open(*res_db,"ADK_EventActionControl",PI_Read);  OADISDBCERR
  }
  if ( !act_ph.Get(act_ph.StringToKey(name)) )               ERROR

  if ( !(pOEventActionControl = CACHE_READ(&act_ph,NULL,OEventActionControl)) )
                                                     OADIERR(99)
RECOVER
  pOEventActionControl = NULL;
ENDSEQ
  return(pOEventActionControl);
}

/******************************************************************************/
/**
\brief  ReadFont - 



\return pOFont - 

\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadFont"

OFont_ *ResourceCache :: ReadFont (char *name )
{
  OFont_          *pOFont = NULL;
BEGINSEQ
  PropertyHandle ph(*res_db,"ADK_Font",PI_Read);     OADISDBCERR

  if ( !ph.Get(ph.StringToKey(name)) )               ERROR

  if ( !(pOFont = CACHE_READ(&ph,NULL,OFont_)) )     OADIERR(99)
RECOVER
  pOFont = NULL;
ENDSEQ
  return(pOFont);
}

/******************************************************************************/
/**
\brief  ReadProject - 



\return pOProject - 

\param  name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadProject"

OProject *ResourceCache :: ReadProject (char *name )
{
  OProject          *pOProject = NULL;
BEGINSEQ
  PropertyHandle ph(*res_db,"ADK_Project",PI_Read);  OADISDBCERR

  if ( !ph.Get(ph.StringToKey(name)) )               ERROR

  if ( !(pOProject = CACHE_READ(&ph,NULL,OProject)) )
                                                     OADIERR(99)
RECOVER
  pOProject = NULL;
ENDSEQ
  return(pOProject);
}

/******************************************************************************/
/**
\brief  ResourceCache - 




\param  resDB - 
\param  cache_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResourceCache"

     ResourceCache :: ResourceCache (DBObjectHandle *resDB, int8 cache_id )
                     : BinTree (sizeof(ResourceEntry),0,sizeof(int32),
         'I',256),
  iterator(this),
  res_db(resDB),
  void_ph(),
  current_ph(NULL),
  act_ph(),
  id(cache_id)
{



}

/******************************************************************************/
/**
\brief  ~ResourceCache - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ResourceCache"

     ResourceCache :: ~ResourceCache ( )
{

  Clear();

}


