/********************************* Class Source Code ***************************/
/**
\package  OPI
\class    ExecAlloc



\date     $Date: 2006/04/29 20:53:42,39 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ExecAlloc"

#include  <pdefault.h>
#include  <sExecStruct.hpp>
#include  <sPropertyHandle.hpp>
#include  <sUCA_Action.hpp>
#include  <sExecAlloc.hpp>


/******************************************************************************/
/**
\brief  CheckError

\return term - Termination code

\param  srcefield
\param  srce_inst
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckError"

logical ExecAlloc :: CheckError (ExecStruct &srcefield, void *srce_inst )
{
  char           string[120];
  logical        term = NO;
BEGINSEQ
  if ( SDBERROR )
  {  
    strcat(gvtxbts(string,srcefield.get_field()->GetDescription()->fmcbtype,ID_SIZE),": ");
    srcefield.get_field()->GetDescription()->fmcbsmcb->ConvertToString((char *)srce_inst,string+strlen(string),sizeof(string)-20);       
    SDBError().SetStatText(string);
    if ( SDBError().DisplayMessage() == YES )        ERROR
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyCollections

\return term - Termination code

\param  targ_inst
\param  srce_inst
\param  exp_opt - 
\param  new_inst - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyCollections"

logical ExecAlloc :: CopyCollections (void *targ_inst, void *srce_inst, logical exp_opt, logical new_inst )
{
  int32            indx0 = 0;
  logical         term  = NO;
BEGINSEQ
  while ( indx0 < field_allocs.GetSize() )
    if ( field_allocs[indx0++] )
      if ( field_allocs[indx0-1]->CopyCollection(targ_inst,srce_inst,exp_opt,new_inst) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyDirect

\return term - Termination code

\param  targ_inst
\param  srce_inst
\param  exp_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyDirect"

logical ExecAlloc :: CopyDirect (void *targ_inst, void *srce_inst, logical exp_opt )
{
  int32            indx0 = 0;
  logical         term  = NO;
BEGINSEQ
  if ( !srce_inst )                                  LEAVESEQ
    
  while ( indx0 < field_allocs.GetSize() )
    if ( field_allocs[indx0++] )
      if ( field_allocs[indx0-1]->CopyDirect(targ_inst,srce_inst,exp_opt) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecAlloc

-------------------------------------------------------------------------------
\brief  i0


\param  alloc_pi - 
\param  intfield - 
\param  extfield - 
\param  w_topalc
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecAlloc"

     ExecAlloc :: ExecAlloc (PropertyHandle &alloc_pi, PropertyHandle *intfield, PropertyHandle *extfield, logical w_topalc )
                     : int_field(alloc_pi.GetPropertyHandle("extent"),
          intfield),
ext_field(alloc_pi.GetPropertyHandle("relation"),
          extfield),
  field_allocs(),
  top_alloc(w_topalc)

{
  PropertyHandle        *falloc_pi;
  ExecFieldAlloc *fld_alloc = NULL;
  int32            indx0     = -1;

BEGINSEQ
  falloc_pi = alloc_pi.GetPIPointer("allocations");
  while ( falloc_pi->Get(++indx0) )
    if ( !falloc_pi->GetPropertyHandle("ignore")->IsTrue() )
    {
      if ( !(fld_alloc = new ExecFieldAlloc(*falloc_pi,int_field.get_field(),ext_field.get_field()) ) )
                                                     SDBERR(95)
                                                     SDBCERR
      field_allocs.SetAtGrow(indx0,fld_alloc);
      fld_alloc = NULL;
    }
    
  SDBRESET  

RECOVER
  if ( SDBERROR > 0 )
    SDBError().DisplayMessage();
  delete fld_alloc;
  SDBISET(-99)
ENDSEQ
}

/******************************************************************************/
/**
\brief  i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecAlloc"

     ExecAlloc :: ExecAlloc ( )
                     :   int_field(),
  ext_field(),
  field_allocs(),
  top_alloc(NO)
{
}

/******************************************************************************/
/**
\brief  Execute

\return term - Termination code

\param  exp_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical ExecAlloc :: Execute (logical exp_opt )
{
  void          *srce_inst;
  void          *targ_inst;
  void          *initinst;
  char          *key;
  char           keyarea[MAX_KEYLEN];
  char           string[120];
  ExecStruct    &targfield = exp_opt ? ext_field : int_field;
  ExecStruct    &srcefield = exp_opt ? int_field : ext_field;
  PropertyHandle       *targ_pi;
  UCA_Action    *imp_filter= NULL;
  UCA_Action    *exp_filter= NULL;
  UCA_Action    *handler   = NULL;
  int32           indx0     = 0;
  int16          ta_level  = 0;
  logical        genattr   = NO;
  logical        newinst;
  logical        term      = NO;
BEGINSEQ
  if ( top_alloc )
  {  
    if ( !targfield.get_field() || targfield.get_field()->ValidateNode(YES) || 
         !srcefield.get_field() || srcefield.get_field()->ValidateNode(YES)    )
                                                     SDBERR(99)
    SDBEV1(int_field.get_field()->GetDescription()->fmcbname,ID_SIZE)
    SDBEV1(ext_field.get_field()->GetDescription()->fmcbname,ID_SIZE)
    SDBError().DisplayMessage(exp_opt ? -211 : -212);
    if ( targfield.get_field()->GetDBHandle().IsShared() )
      ta_level = targfield.get_field()->GetObjectHandle().BeginTransaction(NO,300);
  }  
  
  if ( targfield.get_recreate() )   // reaktiviert am 30.6.98 für BELAMI SAP
    targfield.get_field()->DeleteSet();
  
  if ( targfield.get_struct_context() )
    targfield.get_struct_context()->SetRefContext(srcefield.get_struct_context());
  if ( srcefield.get_struct_context() )
    srcefield.get_struct_context()->SetRefContext(targfield.get_struct_context());
  
  exp_filter = srcefield.CreateExpFilter();
  imp_filter = targfield.CreateImpFilter();
  handler    = targfield.CreateHandler();
  
  if (  targ_pi = targfield.get_field() )
    genattr = targ_pi->HasGenericAttributes();
  
  while ( srce_inst = &srcefield.get_field()->Get(indx0++) )
  {
    if ( top_alloc )
      SDBError().SetStatField(gvtxltoa(indx0,string,10));
    
    if ( exp_filter && exp_filter->Execute() )
      continue;
    
    targ_inst = NULL;
    newinst   = NO;
    if (  targ_pi && targ_pi->IsCollection() )
    {
      if ( !(initinst = &targ_pi->GetInitInstance()) )
                                                     ERROR
      if ( targ_pi->GetSortKeySMCB() || targ_pi->GetKeySMCB() )
      {
         if ( CopyDirect(initinst,srce_inst,exp_opt) )
                                                     ERROR
         if ( !imp_filter || !imp_filter->Execute() )
         {
           if ( key = targ_pi->ExtractSortKey(keyarea,Instance(initinst)) )
             targ_pi->Cancel(), targ_inst = &targ_pi->Get(key); // jetzt ist die initinst überschrieben
           else if ( targ_pi->HasIndex() )
             targ_pi->Cancel(), targ_inst = &targ_pi->Get(indx0-1);
           else
             targ_inst = NULL;  

           if ( targ_inst )
           {
             if ( genattr )
             {
               CopyDirect(targ_inst,srce_inst,exp_opt);
               targ_pi->ProvGenAttribute();
             }
           }
           else if ( targfield.get_create() )
           {
             initinst = &targ_pi->GetInitInstance();
             CopyDirect(initinst,srce_inst,exp_opt);
             targ_inst = &targ_pi->Add(initinst);
             newinst   = targ_pi->IsNewInstance();    // war bisher YES, 5.5.2004
           }
         }
      }
      else  
        targ_inst = targfield.get_create() ? &targ_pi->Provide(indx0-1) : &targ_pi->Get(indx0-1); // ggf. muß durch fieldalloc eingestellter Index benutzt werden
      if ( CheckError(srcefield,srce_inst) )         ERROR
    }    
    else
      targ_inst = targfield.get_field()->GetArea();
      
    if ( targ_inst )
    {
      if ( CopyCollections(targ_inst,srce_inst,exp_opt,newinst) || CheckError(srcefield,srce_inst) )
                                                     ERROR
      targ_pi->Modify();
      if ( handler )
        handler->Execute();
      if ( CheckError(srcefield,srce_inst) )         ERROR
    }
  }  
  if ( targ_inst )
    targ_pi->Save();
  targ_pi->Cancel();

RECOVER
  term = YES;
ENDSEQ
  if ( ta_level )
    targfield.get_field()->GetObjectHandle().CommitTransaction();
  return(term);
}

/******************************************************************************/
/**
\brief  ~ExecAlloc - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ExecAlloc"

     ExecAlloc :: ~ExecAlloc ( )
{
  int16     indx0 = 0;
  while ( indx0 < field_allocs.GetSize() )
    delete field_allocs[indx0++];
  
  if ( top_alloc )
  {
    delete int_field.get_field();
    delete ext_field.get_field();
  }
  

}


