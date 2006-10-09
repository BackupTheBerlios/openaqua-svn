/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    ACView



\date     $Date: 2006/05/09 13:00:08,62 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACView"

#include  <popa7.h>
#ifndef   DLL_DBVFilter_HPP
#define   DLL_DBVFilter_HPP
#include  <sDBVFilter.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_DBVOrder_HPP
#define   DLL_DBVOrder_HPP
#include  <sDBVOrder.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_DBVProperty_HPP
#define   DLL_DBVProperty_HPP
#include  <sDBVProperty.hpp>
#include  <sDLL.h>
#endif
#include  <sACElmView.hpp>
#include  <sACObject.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldList.hpp>
#include  <sDBIndexList.hpp>
#include  <sDBResource.hpp>
#include  <sDBStructDef.hpp>
#include  <sDBVFilter.hpp>
#include  <sDBVOrder.hpp>
#include  <sDBVProperty.hpp>
#include  <sDictionary.hpp>
#include  <sLOperation.hpp>
#include  <sPropertyHandle.hpp>
#include  <sbnode.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <sxinti.hpp>
#include  <sACView.hpp>


/******************************************************************************/
/**
\brief  ACView - Konstruktor


-------------------------------------------------------------------------------
\brief  i0


\param  view_def - Internal view definition
\param  access_mode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACView"

     ACView :: ACView (DBViewDef &view_def, PIACC access_mode )
                     : ACNode(),
  view_base(NULL),
  last_view_index(AUTO),
  last_base_view_index(AUTO),
  last_index(AUTO),
  temp_struct(YES),
  has_references(NO),
  copy_node(NO),
  owns_nodenode(NO)
{
  char            *strnames_w = NULL;

BEGINSEQ
  nodetype = NT_ACView;
  
  if ( InitViewParent(view_def) )                    ERROR
  if ( InitViewBase(view_def,access_mode) )          ERROR
    
  if ( SetPreCondition(view_def.get_pre_condition()) )
                                                     ERROR
  if ( InitViewFilters(view_def) )                   ERROR
  if ( InitViewOrders(view_def) )                    ERROR
  if ( InitViewStructure(view_def) )                 ERROR
    
  
  if ( SetPostCondition(view_def.get_post_condition()) )
                                                     ERROR

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACView"

     ACView :: ACView ( )
                     : ACNode(),
  view_base(NULL),
  last_view_index(AUTO),
  last_base_view_index(AUTO),
  last_index(AUTO),
  temp_struct(YES),
  has_references(NO),
  copy_node(NO),
  owns_nodenode(NO)
{
}

/******************************************************************************/
/**
\brief  i02


\param  obhandle - Database Object handle
\param  dbextdef - Extent definition
\param  accmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACView"

     ACView :: ACView (ACObject *obhandle, DBExtend *dbextdef, PIACC accmode )
                     : ACNode (obhandle,NULL,dbextdef,NULL,accmode),
  view_base(NULL),
  allocations(),
  last_view_index(AUTO),
  last_base_view_index(AUTO),
  last_index(AUTO),
  temp_struct(NO),
  has_references(NO),
  copy_node(NO),
  owns_nodenode(NO)
{
  PropertyHandle    *view_pi = GetDictionary()->get_view_pi();
BEGINSEQ
  nodetype = NT_ACView;
  
  if ( !view_pi->Get(dbextdef->fmcbtype) )           SDBERR(99)
    
  if ( InitViewBase(view_pi,accmode) )               ERROR
    
  if ( SetPreCondition(view_pi->GPH("where")->GetString()) )
                                                     ERROR
//  if ( InitViewGrouping(view_pi) )                   ERROR
  if ( InitViewOrders(view_pi) )                     ERROR
  if ( InitViewStructure(view_pi) )                 ERROR
    
  
  if ( SetPostCondition(view_pi->GPH("having")->GetString()) )
                                                     ERROR

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  i03


\param  nodeptr - 
\param  dbextdef - Extent definition
\param  accmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACView"

     ACView :: ACView (node *nodeptr, DBExtend *dbextdef, PIACC accmode )
                     : ACNode (nodeptr->GetObjectHandle(),nodeptr,dbextdef,
        NULL,accmode),
  view_base(NULL),
  allocations(),
  last_view_index(AUTO),
  last_base_view_index(AUTO),
  last_index(AUTO),
  temp_struct(NO),
  has_references(NO),
  copy_node(NO),
  owns_nodenode(NO)
{
  PropertyHandle    *view_pi = GetDictionary()->get_view_pi();
BEGINSEQ
  nodetype = NT_ACView;
  
  if ( !view_pi->Get(dbextdef->fmcbtype) )           SDBERR(99)
    
  if ( !(view_base = (bnode *)nodeptr->CreateCopyNode()) )
                                                     ERROR
  nodenode = view_base->get_nodenode();
  copy_node = YES;
    
  if ( SetPreCondition(view_pi->GPH("where")->GetString()) )
                                                     ERROR
//  if ( InitViewGrouping(view_pi) )                   ERROR
  if ( InitViewOrders(view_pi) )                     ERROR
  if ( InitViewStructure(view_pi) )                 ERROR
    
  if ( SetPostCondition(view_pi->GPH("having")->GetString()) )
                                                     ERROR

RECOVER
ENDSEQ
}

/******************************************************************************/
/**
\brief  Add

\return instptr - 

\param  lindx0 - 
\param  skey - 
\param  idkey - 
\param  initinst - 
\param  global_add
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

void *ACView :: Add (int32 lindx0, char *skey, char *idkey, void *initinst, logical global_add )
{
  void                   *instptr = NULL;
BEGINSEQ
// initinst ist in diesem Fall nur zu vervenden, wenn sie alle Schlüssel enthält
// aber Add über views scheint generel etwas problematisch
// machen wir später!!!

  if ( !view_base )                                  SDBERR(99)
    
  GetInitInstance();
  if ( initinst || nodeinst->stscini() )
  {
    Initialize_intern(initinst);
    SetData();
  }  
  if ( instptr = view_base->Add(lindx0,skey,idkey,initinst,global_add) )
    nodecur = view_base->get_nodecur();
    
  GetData();
  
  last_view_index = AUTO;
  last_base_view_index = AUTO;
  


RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  Cancel

\return term - Termination code

\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical ACView :: Cancel (logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( chknode )
  {
    if ( !view_base )                                SDBERR(99)
    if ( Check(NO,NO) )                              ERROR
    term = view_base->Cancel();  // nur für echtes Cancel, nicht, wenn expression nicht erfüllt
    last_index = AUTO;
    last_view_index = AUTO;
    last_base_view_index = AUTO;
  }
  nodecur = AUTO;
  nodeinst->Reset();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ChangeBuffer

\return bufnum

\param  bufnum
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeBuffer"

int16 ACView :: ChangeBuffer (int16 bufnum )
{

  if ( has_references )
    bufnum = 1;
  else
    bufnum = ACNode::ChangeBuffer(bufnum);
  return(bufnum);
}

/******************************************************************************/
/**
\brief  Close

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ACView :: Close ( )
{
  PropAllocation         *prop_alloc;
  DBStructDef            *dbstruct;
  logical                 term = NO;
  Save(YES,NO,NO);
  
  while ( prop_alloc = allocations.RemoveTail() )
    delete prop_alloc;
    
  if ( view_base )
  {
    view_base->ResetPIRef((PropertyHandle *)&view_base);
    delete view_base;
    view_base = NULL;
  }
  ACNode::Close();

  if ( temp_struct && !origin && nodefield && (dbstruct = GetStructDef()) )
  {
    GetDictionary()->RemoveStructDef(dbstruct->smcbname);
    delete dbstruct;
  }

  delete nodefield;
  nodefield = NULL;

  if ( owns_nodenode )
    delete nodenode;
  nodenode = NULL;
  return(term);
}

/******************************************************************************/
/**
\brief  CreateExpressionBase

\return term - Termination code

\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExpressionBase"

logical ACView :: CreateExpressionBase (char *expression )
{
  PropertyHandle          source(nodenode);
  LOperation              operation(source);
  char                   *workstr = NULL;
  logical                 term = NO;
BEGINSEQ
  SDBEV1(expression,UNDEF)
  
  if ( !expression )                                 ERROR

  if ( operation.ProvExpression(object_ref->GetDictionary(),NULL,object_ref,expression) )
                                                     SDBERR(356)
  if ( operation.Execute(NULL) )                     SDBERR(356)
  if ( !operation.IsCollection() )                   SDBERR(357)
  view_base = (bnode *)operation.get_nodeptr();

  view_base->Reserve();
  copy_node = YES;

RECOVER
  term = YES;
ENDSEQ
  if ( workstr )
    free(workstr);
  return(term);
}

/******************************************************************************/
/**
\brief  CreateFields

\return fieldlist - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFields"

DBFieldList *ACView :: CreateFields ( )
{
  DBFieldList            *dbfieldlist = NULL;
  PropAllocation         *prop_alloc;
  DBFieldDef             *dbflddef;
  DBFieldDef             *db_field;
  int32                    size;
  int32                    ref_count  = 0;
  int32                    attr_count = 0;
  int32                    count      = 0;
  int32                    curindx    = 1;
  logical                 term       = NO;
BEGINSEQ
  count = allocations.GetCount();
  
  if ( !(dbfieldlist = new DBFieldList(NULL,count))) SDBERR(95)
                                                     SDBCERR
  allocations.GoTop();
  while ( prop_alloc = allocations.GetNext() )
  {
    dbflddef = dbfieldlist->GetEntry(curindx);
    if ( !(db_field = prop_alloc->GetSourceFieldDef()) )
      db_field = DBFieldDef::GetStaticFieldDef(T_STRING);
    
    if ( !prop_alloc->get_is_reference()  )          // attributes first
    {
      *dbflddef = *db_field;
      memcpy(dbflddef->fmcbname,prop_alloc->get_name(),ID_SIZE);
      if ( db_field->fmcbrlev == R_REFR )            // MEMO
      {
        dbflddef->fmcbrlev = R_DIRECT;
        dbflddef->fmcbdim  = 1;
      }
      
      switch ( prop_alloc->get_type() )
      {
        case ADT_SortKey        : dbflddef->fmcbsize = prop_alloc->get_source_pi().GetKeyLength();
                                  break;
        case ADT_SortKey_String : dbflddef->fmcbsize = 512;
                                  break;
        case ADT_GUID           : dbflddef->fmcbsize = 12;
                                  break;
        case ADT_LOID           : dbflddef->fmcbsize = 40;
                                  break;
        case ADT_Type           : dbflddef->fmcbsize = ID_SIZE;
                                  break;
        default                 : ;

      }
      if ( (size = prop_alloc->get_size()) && size < dbflddef->fmcbsize && dbflddef->IsText() )
        dbflddef->fmcbsize = size;
      curindx++;
    }
  } 

  allocations.GoTop();
  while ( prop_alloc = allocations.GetNext() )
  {
    dbflddef = dbfieldlist->GetEntry(curindx);
    if ( !(db_field = prop_alloc->GetSourceFieldDef()) )
      db_field = DBFieldDef::GetStaticFieldDef(T_STRING);
    
    if ( prop_alloc->get_is_reference()  )           // references
    {
      *dbflddef = *db_field;
      memcpy(dbflddef->fmcbname,prop_alloc->get_name(),ID_SIZE);
      dbflddef->set_transient(YES);
      curindx++;
    }
  } 
  
  dbfieldlist->srtsetc(curindx-1);

RECOVER
  dbfieldlist = NULL;
ENDSEQ
  return(dbfieldlist);
}

/******************************************************************************/
/**
\brief  CreateInti - Create instance area


\return intiptr - 

\param  nodeptr - 
\param  strdef_ptr - Internal data structure definition
\param  instptr - 
\param  init_nodes
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInti"

inti *ACView :: CreateInti (node *nodeptr, DBStructDef *strdef_ptr, void *instptr, logical init_nodes )
{
  inti                   *intiptr = NULL;
BEGINSEQ
  if ( !(intiptr = new xinti(nodeptr,NULL,strdef_ptr,instptr,init_nodes)) ) 
                                                      SDBERR(95)
                                                      SDBCERR
RECOVER
  delete intiptr;
  intiptr = NULL;
ENDSEQ
  return(intiptr);
}

/******************************************************************************/
/**
\brief  CreateScopeNode

\return term - Termination code

\param  id_string - Identifier string
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateScopeNode"

logical ACView :: CreateScopeNode (char *id_string )
{
  int32         loid;
  char        *ext_names;
  logical      term = NO;
BEGINSEQ
  SDBEV1(id_string,UNDEF)
  
  ext_names = id_string[1] == '-' ? "__OBJECT" : "VOID";
  if ( !(nodenode = object_ref->CreateNode(ext_names,PI_Read)) )
                                                     ERROR
  owns_nodenode = YES;
  if ( id_string[1] == '-' ) // GUID
    nodenode->Get(id_string,YES);
  else                       // LOID
  {
    loid = atol(id_string);
    nodenode->Get(loid);
  }
  if ( !nodenode->IsPositioned() )                   SDBERR(355)
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateStruct - 


\return dbstrdef - Structure definition

\param  strnames_w - Structure name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStruct"

DBStructDef *ACView :: CreateStruct (char *strnames_w )
{
  DBStructDef            *dbstrdef    = NULL;
  DBFieldList            *dbfieldlist = NULL;
  int32                   curindex    = 0;
  int32                   intpos      = 0;
  int32                   extpos      = 0;
  int8                    max_aligned = 1;
  DBFieldDef             *dbflddef;
BEGINSEQ
  if ( !strnames_w || *strnames_w <= ' ' || 
       !(dbstrdef = GetDictionary()->GetStructDef(strnames_w)) )
  {                                                     
    if ( !(dbfieldlist = CreateFields()) )             ERROR
    while ( (dbflddef = dbfieldlist->GetEntry(++curindex)) && dbflddef->fmcbrlev != R_REFR ) ;
    curindex--;

    if ( !(dbstrdef = GetDictionary()->ProvideStructDcl(strnames_w,
                                        ERIC,UNDEF,UNDEF,
                                        TYP_Structure,ST_USER,
                                        0,curindex,dbfieldlist->GetCount()-curindex,0,NULL)) )
                                                     ERROR
  
    dbstrdef->smcbfmcl = dbfieldlist;
    dbstrdef->smcbsts.stssusr3();
    if ( !dbstrdef->Setup(GetDictionary()) )         ERROR
  }
  nodefield = new DBFieldDef(strnames_w,strnames_w,RL_reference,dbstrdef->GetInstLength(NO),UNDEF,UNDEF,dbstrdef,NULL,NO,NULL,NULL,NULL); 
  nodefield->set_resource(new DBResource(NULL));
  nodefield->SetupField(intpos,extpos,UNDEF,max_aligned);
//  if ( dbstrdef->CreateKeyDefs(NULL,dbstrdef->smcbidky) )   
//                                                     ERROR
//  if ( dbstrdef->SetupKeyDefs(GetSystemVersion()) )  ERROR

RECOVER
  delete dbfieldlist;
  dbfieldlist = NULL;
  delete dbstrdef;
  dbstrdef = NULL;
ENDSEQ
  return(dbstrdef);
}

/******************************************************************************/
/**
\brief  Execute

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

logical ACView :: Execute ( )
{

  return(NO);
}

/******************************************************************************/
/**
\brief  FirstKey

\return keyptr - 

\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FirstKey"

char *ACView :: FirstKey (logical chknode )
{
  char                   *keyptr = NULL;
BEGINSEQ
  last_view_index = AUTO;
  last_base_view_index = AUTO;
  
  if ( !view_base )                                  ERROR
  keyptr = view_base->FirstKey();
  

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  Get

\return instptr - 
-------------------------------------------------------------------------------
\brief  NODEIG


\param  indx0 - Position in collection
\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACView :: Get (int32 indx0, logical chknode )
{
  int32                    count;
  int32                    ev_indx0;
  int16                   direction;
BEGINSEQ
  if ( chknode && Check(YES) )                       ERROR
  if ( !view_base )                                  ERROR
  
  if ( indx0 == AUTO )
    indx0 = nodecur != AUTO ? nodecur : 0;
  
  if ( indx0 == nodecur && (nodeinst->IsPositioned() || (nodecur == AUTO && nodeinst->stscini())) )
                                                     LEAVESEQ
  if ( last_index != AUTO && indx0 > last_index )    // lesen nach letzter instanz
  {
    Switch(AUTO);
    ERROR   
  }
    
  if ( inti_buffer && !stscusr3() )
  {
    Switch(AUTO);
    if ( !GetBuffer(indx0,0) )                       ERROR
    LEAVESEQ
  }
    
  if ( last_view_index == AUTO || 
       last_base_view_index == AUTO || last_base_view_index != view_base->get_nodecur() )
    ev_indx0 = AUTO;
  else
    ev_indx0 = view_base->get_nodecur() != AUTO ? view_base->get_nodecur() : AUTO;
  
  if ( indx0 == LAST_INSTANCE )
  {
    direction = BACKWARD;
    ev_indx0 = LAST_INSTANCE;
    count = 1;
  }
  else
  {
    count = indx0 - last_view_index;
    direction = count >= 0 ? FOREWARD : BACKWARD;
    if ( direction < 0 )
      count = -count;
  }
  
  Switch(AUTO);
  nodecur = indx0;
  
  if ( !count )
    last_base_view_index = view_base->GetAt(ev_indx0,direction,NO);
  else
  {
    last_base_view_index = view_base->GetAt(ev_indx0+direction,direction,NO);
    while ( last_base_view_index != AUTO && --count )
      last_base_view_index = view_base->GetAt(last_base_view_index+direction,direction,NO);
  }
  
  if ( last_base_view_index == AUTO )
  {
    if ( direction > 0 )
      last_index = nodecur - count;  // das ist fragwürdig, wenn wir in der Mitte anfangen!!
    nodecur = AUTO;
    last_view_index = AUTO;
  }

  Initialize_intern(NULL);
  GetData();    
  last_view_index = nodecur;
  if ( nodesel && CheckExpression() )              ERROR

RECOVER

ENDSEQ
  return( IsPositioned() ? nodeinst->get_iselarea() : NULL );
}

/******************************************************************************/
/**
\brief  i1


\param  skey - 
\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *ACView :: Get (char *skey, logical chknode )
{
  void                   *instptr = NULL;
BEGINSEQ
  Save(YES,NO,NO);
  
  if ( instptr = view_base->Get(skey,chknode) )
  {
    nodecur = view_base->get_nodecur();
    GetData();    
    if ( nodesel && CheckExpression() )              ERROR
  }  

    

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetCount

\return count

\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 ACView :: GetCount (logical chknode )
{
  int32                    count = ERIC;
BEGINSEQ
  if ( chknode && Check(YES,YES) )                   ERROR
  if ( !view_base )                                  ERROR
  
  if ( last_index != AUTO )
    count = last_index + 1;
  else
  // das geht so nicht!!
    count = view_base->GetCount();
RECOVER
  count = ERIC;
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  GetData

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetData"

logical ACView :: GetData ( )
{
  PropAllocation         *prop_alloc;
  logical                 term = NO;
BEGINSEQ
  if ( nodecur == AUTO )                             ERROR
    
  nodeinst->stssini();
  allocations.GoTop();
  while ( prop_alloc = allocations.GetNext() )
    prop_alloc->Get();

  nodeinst->stssfil();
  nodeinst->stsrini();
  stsrmod();

  nodeinst->set_inst_index(nodecur);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitViewBase

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0


\param  view_def - Internal view definition
\param  access_mode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitViewBase"

logical ACView :: InitViewBase (DBViewDef &view_def, PIACC access_mode )
{
  char             vpath[513];
  char             t_strname[ID_SIZE+1];
  logical          term = NO;
BEGINSEQ
  strcpy(vpath,view_def.get_view_path());
  if ( *view_def.get_view_path() <= ' ' )
  {
    if ( !(view_base = (bnode *)nodenode->CreateCopyNode()) )
                                                     ERROR
    nodenode = view_base->get_nodenode();
    copy_node = YES;
  }
  else if ( *view_def.get_view_path() == '{' )       // collection expression
  {
    if ( CreateExpressionBase(view_def.get_view_path()) )
                                                     ERROR
  }
  else
  {
    memcpy(t_strname,"#_",2);
    gvtxstb(t_strname+2,view_def.get_name(),ID_SIZE-2);
    view_base = new ACElmView(object_ref,nodenode,
                              view_def.get_view_path(),
                              access_mode,!temp_struct && *t_strname ? t_strname : NULL);
                                                     SDBCERR
  }
  view_base->SetPIRef((PropertyHandle *)&view_base);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  view_ph
\param  accmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitViewBase"

logical ACView :: InitViewBase (PropertyHandle *view_ph, PIACC accmode )
{
  char             vpath[4000];
  PropertyHandle  *vbase_ph = (PropertyHandle *)&view_base;
  DBObjectHandle   obh(object_ref);
  int32            indx0 = 0;
  logical          first = YES;
  logical          term  = NO;
BEGINSEQ
  PH(view_ph,from)

  if ( from.GetCount() == 1 )
  {
    from(FIRST_INSTANCE);
    strcpy(vpath,from.GPH("path")->GetString());
    
    if ( vpath[0] <= ' ' )
    {
      if ( !(view_base = (bnode *)nodenode->CreateCopyNode()) )
                                                     ERROR
      nodenode = view_base->get_nodenode();
      copy_node = YES;
      view_base->SetPIRef(vbase_ph);
    }
    else
      if ( vbase_ph->OpenAccessPath(obh,vpath,NULL,accmode) )
                                                     ERROR
  }
  else
  {
    strcpy(vpath,"from(");
    while( from(indx0++) )
    {
      if ( !first )
        strcat(vpath,",");
      first = NO;
      strcat(vpath,from.GPH("path")->GetString());
    }
    strcat(vpath,")");
    if ( vbase_ph->OpenAccessPath(obh,vpath,NULL,accmode) )
                                                     ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitViewFilters

\return term - Termination code

\param  view_def - Internal view definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitViewFilters"

logical ACView :: InitViewFilters (DBViewDef &view_def )
{
  DBVFilter       *filter;
  logical          term = NO;

BEGINSEQ
  DLL(DBVFilter)   filters(*view_def.get_filters());
  filters.GoTop();
  while ( filter = filters.GetNext() )
    if ( filter->SetFilter(view_base) )              ERROR
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitViewNode

\return term - Termination code

\param  obhandle - Database Object handle
\param  access_mode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitViewNode"

logical ACView :: InitViewNode (ACObject *obhandle, PIACC access_mode )
{
  PropAllocation  *prop_alloc;
  CTX_Base        *highctx;
  logical          term = NO;
BEGINSEQ
  if ( nodenode )
    highctx = nodenode->get_nodeinst()->GetContext();
  else
    highctx = obhandle->get_ocontext();
  if ( Open(object_ref,nodenode,nodefield,highctx,access_mode) )
                                                     ERROR
  if ( InitInti(GetStructDef(),NULL,YES) )           ERROR
  
  allocations.GoTop();  
  while ( prop_alloc = allocations.GetNext() )
    prop_alloc->SetTarget(this);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitViewOrders

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0


\param  view_def - Internal view definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitViewOrders"

logical ACView :: InitViewOrders (DBViewDef &view_def )
{
  DBVOrder        *order;
  logical          term = NO;

BEGINSEQ
  DLL(DBVOrder)    orders(*view_def.get_sort_orders());
  orders.GoTop();
  while ( order = orders.GetNext() )
    if ( order->SetOrder(view_base) )                ERROR
  if ( !copy_node )
    if ( view_base->SetupViewOrder() )               ERROR
    

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  view_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitViewOrders"

logical ACView :: InitViewOrders (PropertyHandle *view_ph )
{
  DBIndex                *index;
  char                    string[129];
  logical                 term = NO;
BEGINSEQ
// order_by defined as index definition
  
  
  
// if key is defined in the view base
  if ( index = nodefield->get_index_list()->GetHead() )
  {
    PH(view_ph,smcepsmc)
    if ( smcepsmc((char *)index->GetKeyName()) )
    {
      PH(smcepsmc,components)
      if ( components.GetCount() == 1 )
      {
        components(FIRST_INSTANCE);
        strcpy(string,components.GPH("member_path")->GetString());
        if ( strlen(string) <= 40 && view_base->GetKeySMCB(string) )
        {
          view_base->SetOrder(string,UNDEF,NULL);               
          LEAVESEQ
        }
      }
    }
  }


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitViewParent

\return term - Termination code

\param  view_def - Internal view definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitViewParent"

logical ACView :: InitViewParent (DBViewDef &view_def )
{
  node            *nodeptr;
  char            *strnames_w = NULL;
  char             strnames[ID_SIZE+1];
  char            *scope;
  logical          term = NO;
BEGINSEQ
  if ( !&view_def )                                  SDBERR(99)
  object_ref = view_def.get_object_handle();
  if ( nodeptr = view_def.get_property_handle().get_nodeptr() )
  {
    if ( !(nodenode = Tnodeptr) )                    SDBERR(99)
  }
  else if ( (scope = view_def.get_scope()) && *scope )
  {
    if ( CreateScopeNode(scope) )                    ERROR
  }

  if ( *view_def.get_name() > ' ' )
  {
    temp_struct = NO;
    strnames_w = view_def.get_name();
  }
  if ( !strnames_w )
  {
    strnames_w = object_ref->GetDictionary()->GetTempName(strnames);
    gvtxstb(view_def.get_name(),strnames_w,ID_SIZE);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitViewStructure

\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0


\param  view_def - Internal view definition
\param  access_mode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitViewStructure"

logical ACView :: InitViewStructure (DBViewDef &view_def, PIACC access_mode )
{
  DBVProperty     *property;
  PropAllocation  *prop_alloc;
  logical          term = NO;
BEGINSEQ
  DLL(DBVProperty) properties(*view_def.get_properties());
  properties.GoTop();
  while ( property = properties.GetNext() )
  {
    if ( !(prop_alloc = property->CreateAllocation(view_base,this,view_def.get_name())) )
                                                     ERROR
    if ( prop_alloc->get_is_reference() )
      has_references = YES;
    allocations.AddTail(prop_alloc);
  }

  if ( !CreateStruct(view_def.get_name()) )          ERROR

  if ( InitViewNode(view_def.get_object_handle(),access_mode) ) 
                                                     ERROR
  memcpy(view_def.get_name(),nodefield->fmcbname,ID_SIZE);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  view_ph
\param  accmode - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitViewStructure"

logical ACView :: InitViewStructure (PropertyHandle *view_ph, PIACC accmode )
{
  logical                 term = NO;
BEGINSEQ
// hier muss noch was passieren ...
  if ( InitViewNode(object_ref,accmode) )           ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  LocateKey

\return term - Termination code

\param  skey - 
\param  exact - 
\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

logical ACView :: LocateKey (char *skey, logical exact, logical chknode )
{
  logical    term = NO;
BEGINSEQ
  last_index = AUTO;
  last_view_index = AUTO;
  last_base_view_index = AUTO;
  
  if ( !view_base )                                  ERROR
  if ( view_base->LocateKey(skey,exact,chknode) )    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Modify

\return instptr - 

\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

void *ACView :: Modify (logical chknode )
{

  stssmod();
  return ( nodeinst->get_iselarea() );

}

/******************************************************************************/
/**
\brief  NextKey

\return keyptr - 

\param  skey - 
\param  switch_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextKey"

char *ACView :: NextKey (char *skey, int16 switch_level )
{
  void                   *instptr;
  int32                    next;
  char                   *keyptr = NULL;
BEGINSEQ
  if ( !view_base )                                  ERROR
  
  keyptr = view_base->NextKey(skey,switch_level);
  next = view_base->get_nodecur();
  
  last_index = AUTO;
  last_view_index = AUTO;
  last_base_view_index = AUTO;
  
  if ( nodesel )
  {
    while ( !(instptr = Get(next++,NO)) && view_base->get_nodecur() ) ;
    if ( !instptr || !(keyptr = view_base->bnode::ExtractKey(NULL,(void *)NULL,NO)) )
                                                     ERROR
  }

RECOVER
  keyptr = NULL;
ENDSEQ
  return(keyptr);
}

/******************************************************************************/
/**
\brief  Save

\return term - Termination code

\param  switchopt - 
\param  overwrite - 
\param  chknode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical ACView :: Save (logical switchopt, logical overwrite, logical chknode )
{
  logical                 term = NO;
BEGINSEQ
  if ( stscmod() || stscsav() )
  {
    if ( !view_base )                                  SDBERR(99)
    SetData();
    view_base->Save(switchopt,overwrite,chknode);
  }
  if ( switchopt )
    nodecur = AUTO;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetData

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetData"

logical ACView :: SetData ( )
{
  PropAllocation         *prop_alloc;
  logical                 term = NO;
  allocations.GoTop();
  while ( prop_alloc = allocations.GetNext() )
    prop_alloc->Put();
  return(term);
}

/******************************************************************************/
/**
\brief  SetOrder

\return term - Termination code

\param  strnames - Type name
\param  attrtype
\param  attrstr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOrder"

logical ACView :: SetOrder (char *strnames, int attrtype, char *attrstr )
{
  logical    term = NO;
BEGINSEQ
  if ( !view_base )                                  ERROR
  
  if ( view_base->SetOrder(strnames,attrtype,attrstr) )
                                                     ERROR
  if ( !copy_node && view_base->SetupViewOrder() )   ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetPostCondition

\return term - Termination code

\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPostCondition"

logical ACView :: SetPostCondition (char *expression )
{
  PropertyHandle          source(nodenode);
  LOperation              operation(source);
  NString                 workstr;
  char                   *last;
  logical                 term = NO;
BEGINSEQ
  SDBEV1(expression,UNDEF)
  
  if ( !expression || !*expression )                 LEAVESEQ
    
  if ( SetExpression(expression) )                   ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetPreCondition

\return term - Termination code

\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPreCondition"

logical ACView :: SetPreCondition (char *expression )
{
  PropertyHandle          source(nodenode);
  LOperation              operation(source);
  NString                 workstr;
  char                   *last;
  logical                 term = NO;
BEGINSEQ
  SDBEV1(expression,UNDEF)
  
  if ( !expression || !*expression )                 LEAVESEQ
    
  if ( view_base->SetExpression(expression) )        ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ACView - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACView"

     ACView :: ~ACView ( )
{
  if ( nodeidnt == NODE_ID )
    Close();



}


