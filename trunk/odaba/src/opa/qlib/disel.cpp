/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    disel

\brief    


\date     $Date: 2006/07/16 12:27:28,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "disel"

#include  <popa7.h>
#include  <sACGenericAttr.hpp>
#include  <sACNode.hpp>
#include  <sACObject.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sLACObject.hpp>
#include  <sStructAccess.hpp>
#include  <sexd.hpp>
#include  <smvld.hpp>
#include  <snode.hpp>
#include  <sref.hpp>
#include  <sdisel.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code

\param  global_add - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical disel :: Add (logical global_add )
{
  logical   term    = NO;
BEGINSEQ
  if ( context )
    if ( RecursiveEvents(DBP_Create) )               ERROR

if ( gvtutle0(ext_inst,struct_def->get_ext_length()) ) SDBERR(999)
//  memset(ext_inst,0,struct_def->get_ext_length());
  
  if ( SetupNewInst(global_add) )                    ERROR
  
  struct_def->IntToExt(ext_inst,iselarea,struct_access->get_pif());
  inst_index = LONGMAX;
  
  stsrini();
  stsrold();
  stssfil();
  stsssav();  // neu 26.4.99
    
  if ( context )
  {
    GenerateEvent(DBO_Created);
    GenerateEvent(DBO_Stored);
    context->get_resource()->CheckEvent(context,YES);
  }  


RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code

\param  extname - Extent name
\param  is_root - 
\param  delopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical disel :: Delete (char *extname, logical is_root, int16 delopt )
{
  logical       term = NO;
BEGINSEQ
  if ( DeleteReferences(extname,delopt,YES) )          ERROR
  GenerateEvent(DBO_Deleted);

RECOVER
  GenerateEvent(DBO_NotDeleted);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Get - 


\return term - Termination code

\param  entnr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

logical disel :: Get (EB_Number entnr )
{
  bnode    *bnode_ptr;
  int32      indx0;
  logical   term    = NO;

BEGINSEQ
  Release();  
    
  if ( (indx0 = inst_index) == AUTO )
    indx0 = ((mvld *)refptr)->EBSNumToIndex(entnr);
    
  ResetSubNodes();

  if ( refptr->ReadIndexEntry(indx0,ext_inst) ) ERROR
  struct_def->ExtToInt(iselarea,ext_inst,struct_access->get_pif());
  
  SetupInst(NO);  
  
  mod_count = GetModCount();
RECOVER
  term = YES;

ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  GetClusterNumber - 


\return clnumb - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClusterNumber"

EB_Number disel :: GetClusterNumber ( )
{

  return ( refptr->get_cluster_number() );

}

/******************************************************************************/
/**
\brief  GetExtInst - 


\return instptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExtInst"

char *disel :: GetExtInst ( )
{

  return(ext_inst);

}

/******************************************************************************/
/**
\brief  GetID - 


\return entnr - 

\param  w_indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number disel :: GetID (int32 w_indx0 )
{

  if ( refptr && !refptr->get_exd_area() )
    refptr->Refresh();
    
  return (((mvld *)refptr)->IndexToEBSNum(inst_index));

}

/******************************************************************************/
/**
\brief  GetMBNumber - 


\return mbnumber - MainBase number

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMBNumber"

int16 disel :: GetMBNumber ( )
{

  return ( refptr->get_mb_number() );

}

/******************************************************************************/
/**
\brief  GetModCount - 


\return modcount - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetModCount"

int16 disel :: GetModCount ( )
{
  int16   modcount = UNDEF;
BEGINSEQ
  if ( inst_index == AUTO )                           LEAVESEQ
  
  modcount = refptr->GetModCount();

ENDSEQ
  return(modcount);
}

/******************************************************************************/
/**
\brief  GetOBHandle - 


\return obhandle - Database Object handle

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOBHandle"

ACObject *disel :: GetOBHandle ( )
{

  return(this && refptr ? refptr->get_ob_handle() : NULL);

}

/******************************************************************************/
/**
\brief  GetOldInst - 


\return instptr - 

\param  oldinst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOldInst"

char *disel :: GetOldInst (void *oldinst )
{
  bnode    *bnode_ptr;
BEGINSEQ
  SDBRESET
  
  if ( !oldinst )
    oldinst = struct_access->get_instarea();
  
// muß später gemacht werden, wenn GetModCount einen ordentlichen Wert zurückgibt
//  if ( mod_count != GetModCount() ) 
//    if ( refptr->ReadIndexEntry(inst_index,ext_inst) ) ERROR
  struct_def->ExtToInt(oldinst,ext_inst,struct_access->get_pif());

  node_genattr.GoTop();
  while ( bnode_ptr = node_genattr.GetNextBNode() )
    if ( ((ACGenericAttr *)bnode_ptr)->get_attr_type() )
      if ( !bnode_ptr->get_bnodeinst()->GetOldInst(((char *)oldinst)+((ACGenericAttr *)bnode_ptr)->get_inst_off()) )           
                                                     SDBCERR
/*  
  if ( iselarea && identity_pos != AUTO )
  {
    SetIdentity();
    memcpy(oldinst+identity_pos,iselarea+identity_pos,sizeof(EB_Number));
  }
*/
RECOVER
  if ( oldinst && isel_init)
    struct_def->CopyInstance((char *)oldinst,struct_def,isel_init,REPL_direct,UNDEF);  
//  memcpy(oldinst,isel_init,(int32)GetInstLength());
  oldinst = NULL;
ENDSEQ
  return((char *)oldinst);
}

/******************************************************************************/
/**
\brief  GetStructAccess - 


\return struct_access - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStructAccess"

StructAccess *disel :: GetStructAccess ( )
{

  return( struct_access );

}

/******************************************************************************/
/**
\brief  IsPositioned - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPositioned"

logical disel :: IsPositioned ( )
{

//  return ( inst_index == AUTO || refptr->refcuri == AUTO ? NO : YES );
  return ( inst_index == AUTO ? NO : YES );


}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical disel :: Lock ( )
{
  logical  term = NO;
BEGINSEQ
  if ( stsclck() || inst_index == AUTO )              LEAVESEQ

  if ( refptr->Lock() )                               ERROR

  stsslck();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Reserve - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reserve"

logical disel :: Reserve ( )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void disel :: Reset ( )
{

  inst_index = AUTO;
  
  memset(ext_inst,0,struct_def->get_ext_length());
  ResetNodes();
  
  Release();  


}

/******************************************************************************/
/**
\brief  ResetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWProtect"

logical disel :: ResetWProtect ( )
{
  logical     term = NO;
BEGINSEQ
//  if ( !inst_index )                                 ERROR
  if ( refptr->get_exd_area()->ResetWProtect() )     ERROR

  Reserve();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

\param  switchopt - 
\param  overwrite - 
\param  refresh_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical disel :: Save (logical switchopt, logical overwrite, logical refresh_opt )
{
  logical                 term = NO;
BEGINSEQ
  if ( IsPositioned() && (stscmod() || stscsav()) )
    if ( StructureEvents(DBP_Store) )                ERROR
  
  if ( binti::Save(NO,NO,NO) )                       ERROR
    
  if ( IsPositioned() && (stscmod() || stscsav()) )
  {
//    if ( overwrite != YES && mod_count != GetModCount() ) 
//                                                     SDBERR(67)
    inst_index = refptr->refcuri;
    struct_def->IntToExt(ext_inst,iselarea,struct_access->get_pif());
    term = refptr->WriteIndexEntry(inst_index,ext_inst);
    
    stsrsav();
    stsrold();
    stsrmod();
    StructureEvents(DBO_Stored);
  }
  
  if ( term )                                        ERROR
  
  if ( switchopt )
    ResetReferences();

  mod_count = GetModCount();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetStructAccess - 



\param  structacc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStructAccess"

void disel :: SetStructAccess (StructAccess *structacc )
{

  struct_access = structacc;

}

/******************************************************************************/
/**
\brief  SetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWProtect"

logical disel :: SetWProtect ( )
{
  logical     term = NO;
BEGINSEQ
//  if ( !inst_index )                                 ERROR
  if ( refptr->get_exd_area()->SetWProtect() )       ERROR

  stsrwpt();
  Reserve();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical disel :: Unlock ( )
{
  logical  term = NO;
BEGINSEQ
  if ( !stsclck() || inst_index == AUTO  )            LEAVESEQ

  if ( refptr->Unlock(NO) )                           ERROR

  stsrlck();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  disel - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  nodeptr - 
\param  strdefptr - 
\param  instptr - 
\param  refptr - 
\param  crt_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "disel"

     disel :: disel (node *nodeptr, DBStructDef *strdefptr, void *instptr, ref *refptr, logical crt_opt )
                     : binti(nodeptr,NULL,strdefptr,instptr,crt_opt),
  refptr(refptr),
  ext_inst(NULL),
  struct_access(NULL)
{

  ext_inst = new char[struct_def->get_ext_length()];
  memset(ext_inst,0,struct_def->get_ext_length());



}

/******************************************************************************/
/**
\brief  i1 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "disel"

     disel :: disel ( )
                     : binti (),
  refptr(NULL),
  ext_inst(NULL),
  struct_access(NULL)
{



}

/******************************************************************************/
/**
\brief  ~disel - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~disel"

     disel :: ~disel ( )
{

  delete ext_inst;


}


