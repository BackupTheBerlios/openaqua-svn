/********************************* Class Source Code ***************************/
/**
\package  OPS - 
\class    SDB_Structure

\brief    Structure definition
          A  structure  represents  a  complex  view to a given object type. The
          structure  provides  usually  a  subset  of the characteristics of the
          object  type  considered.  A  structure represents the structural part
          for  an object type, while the functional  part is defined in the more
          specific  class  definition.  An  ODABA structure definition contains,
          however,  also dynamic model elements,  which allow defining reactions
          on system or user-defined events. 
          The  structure properties are defined  as properties of four different
          categories:    base    structures,    attributes,    references    and
          relationships.  Other members defined on the structure level are keys.
          A  structure may define  any number of  keys based on attribute values
          of the structure. 
          Structures  of different types can be defined depending on the purpose
          of  use.  Usually,  structures  are  user-defined  types.  Internally,
          however,  key  structures  are  created  from  key  definitions  for a
          structure.  System structures refer  to structure definitions provided
          by  ODABA.  View  structures  are structures, which are implemented as
          views. 
          One  may  refer  to  structures  as type of different sort of members.
          Before  being able to  store instances for  a structure, the structure
          itself  and all  types referenced  by its  members must be checked and
          free  from errors.  In order  to store  instances, the structure state
          must be ready.

\date     $Date: 2006/06/13 22:43:54,09 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Structure"

#include  <pops7.h>
#include  <cutimac.h>
#ifndef   P_CAU_Action_HPP
#define   P_CAU_Action_HPP
#include  <sPI.hpp>
class       CAU_Action;
PI_dcl     (CAU_Action)
#endif
#ifndef   P_SDB_KeyComponent_HPP
#define   P_SDB_KeyComponent_HPP
#include  <sPI.hpp>
class       SDB_KeyComponent;
PI_dcl     (SDB_KeyComponent)
#endif
#ifndef   P_SDB_Property_HPP
#define   P_SDB_Property_HPP
#include  <sPI.hpp>
class       SDB_Property;
PI_dcl     (SDB_Property)
#endif
#ifndef   P_SDB_Structure_HPP
#define   P_SDB_Structure_HPP
#include  <sPI.hpp>
class       SDB_Structure;
PI_dcl     (SDB_Structure)
#endif
#ifndef   P_SDB_Type_HPP
#define   P_SDB_Type_HPP
#include  <sPI.hpp>
class       SDB_Type;
PI_dcl     (SDB_Type)
#endif
#ifndef   DLL_kcb_HPP
#define   DLL_kcb_HPP
#include  <skcb.hpp>
#include  <sDLL.h>
#endif
#include  <sACObject.hpp>
#include  <sBNFData.hpp>
#include  <sDBHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sSDB_Attribute.hpp>
#include  <sSDB_BaseStruct.hpp>
#include  <sSDB_Extend.hpp>
#include  <sSDB_Key.hpp>
#include  <sSDB_KeyComponent.hpp>
#include  <sSDB_Member.hpp>
#include  <sSDB_Reference.hpp>
#include  <sSDB_Relationship.hpp>
#include  <sSDB_ResourceRef.hpp>
#include  <sSDB_Structure.hpp>


/******************************************************************************/
/**
\brief  CheckExtentPath - 


\return type_name - 

\param  property_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckExtentPath"

char *SDB_Structure :: CheckExtentPath (char *property_path )
{
  static      char        type_name[ID_SIZE];  
  BNFData                *bdata          = NULL;
  BNFData                *path_extension = NULL;
  BNFData                *member_elm     = NULL;
  BNFData                *acp            = NULL;
  SDB_Structure          *sdb_struct     = NULL;
  SDB_Type               *sdb_type       = NULL;
  SDB_Member             *sdbmem         = NULL;
  char                   *ptype          = NULL;
  char                   *ext_names      = NULL;
  int                     indx0 = 0;
BEGINSEQ
  if ( !property_path || !*property_path )           SDBERR(651)
  SDBEV2(property_path,UNDEF);
    
  if ( !(bdata = members.GetDictionary().ParseExpression(property_path,"access_path")) )
                                                     SDBERR(652)
  if ( bdata->IsSymbol("pname") ) 
    member_elm = bdata;
  else
  {
    if ( !(acp = bdata->GetSymbol("access_path")) )  SDBERR(652)
    if ( !(member_elm = acp->GetElement(indx0++)) )  SDBERR(652)
  }
  
  ext_names = member_elm->GetElement("pname")->GetStringValue(NULL,NULL);
  PI(SDB_Extend)   ext(members.GetDBHandle(),"SDB_Extend",PI_Read);
  TypeKey          ext_key(ext_names,0);
  if ( !(sdbmem = ext(ext_key.GetKey())) )           SDBERR(657)
  
  while ( acp && (path_extension = acp->GetElement(indx0++)) )
  {
    member_elm = (BNFData *)path_extension->GetElement(1);
    SDBEV3(member_elm->GetElement("pname")->GetStringValue(NULL,NULL),UNDEF)
    SDBEV4(sdbmem->get_sys_ident(),ID_SIZE)
    
    if ( !(sdb_type = sdbmem->GetTypeDef()) )
    {
      SDBSET(655)   // incomplete check
      ptype = (char *)memcpy(type_name,sdbmem->get_ddetype(),ID_SIZE);
      SDBError().DisplayMessage();
      LEAVESEQ
    }
    if ( !(sdb_struct = sdbmem->GetStructDef()) ) SDBERR(656)
    if ( !(sdbmem = sdb_struct->CheckMember(member_elm)) ) 
                                                     ERROR
  }
  if ( !sdbmem )                                     ERROR
  ptype = (char *)memcpy(type_name,sdbmem->get_ddetype(),ID_SIZE);
RECOVER
  SDBError().DisplayMessage();
  ptype = NULL;
ENDSEQ
  return(ptype);
}

/******************************************************************************/
/**
\brief  CheckMember - 


\return sdbmem - 

\param  bdata - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckMember"

SDB_Member *SDB_Structure :: CheckMember (BNFData *bdata )
{
  BNFData                *name  = NULL;
  char                    mname[ID_SIZE];
  SDB_Member             *sdbmem = NULL;
BEGINSEQ
  if ( bdata->IsSymbol("pname") )                    // a
    name = bdata;
  else if ( bdata->IsSymbol("path_name") )           // a[3] 
  {
    bdata = bdata->GetElement(0);                    // path_operand
    name = bdata = bdata->GetElement(0);             // path_name
    if ( !bdata->IsSymbol("pname") )                 // a[3]
    {
      name  = bdata->GetElement(0);
      bdata = bdata->GetElement(1);                  // name_index
      bdata = bdata->GetElement(1);                  // operand
      if ( !bdata->IsSymbol("std_constant") )        
      {
        SDBEV3(bdata->GetStringValue(NULL,NULL),UNDEF)
        SDBERR(653)
      }
    }
  }
  else                                               // a(3), a()
  {
    name  = bdata->GetElement(0);                    // path_operand
    if ( !name->IsSymbol("pname") )                  SDBERR(652)
    bdata = bdata->GetElement(1);                    // operand_list
    bdata = bdata->GetElement(1);                    // parm_list or ')'
    if ( !bdata->IsA(")") )                          // a(), a(3)                                    // a(3)
      if ( !bdata->IsSymbol("std_constant") && !bdata->IsSymbol("*") )
      {
        SDBEV3(bdata->GetStringValue(NULL,NULL),UNDEF)
        SDBERR(653)
      }
  }
  if ( !(sdbmem = GetSDBMember(name->GetStringValue(NULL,NULL))) ) 
  {
    SDBEV3(bdata->GetStringValue(NULL,NULL),UNDEF)
    SDBEV4(sys_ident,ID_SIZE)
    SDBERR(654)
  }
RECOVER
  sdbmem = NULL;
ENDSEQ
  return(sdbmem);
}

/******************************************************************************/
/**
\brief  CheckPropertyPath - 


\return type_name - 

\param  property_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckPropertyPath"

char *SDB_Structure :: CheckPropertyPath (char *property_path )
{
  BNFData                *bdata          = NULL;
  BNFData                *path_extension = NULL;
  BNFData                *member_elm     = NULL;
  BNFData                *acp            = NULL;
  SDB_Structure          *sdb_struct     = NULL;
  SDB_Type               *sdb_type       = NULL;
  SDB_Member             *sdbmem         = NULL;
  char                   *type_name      = NULL;
  int                     indx0          = 0;
BEGINSEQ
  SDBEV1(sys_ident,ID_SIZE);
  if ( !property_path || !*property_path )           SDBERR(651)
  SDBEV2(property_path,UNDEF);
    
  if ( !(bdata = members.GetDictionary().ParseExpression(property_path,"access_path")) )
                                                     SDBERR(652)
  if ( bdata->IsSymbol("pname") ) 
    member_elm = bdata;
  else
  {
    if ( !(acp = bdata->GetSymbol("access_path")) )  SDBERR(652)
    if ( !(member_elm = acp->GetElement(indx0++)) )  SDBERR(652)
  }
  sdb_struct = this;
  
  while ( member_elm && sdb_struct )
  {
    SDBEV3(member_elm->GetElement("pname")->GetStringValue(NULL,NULL),UNDEF)
    if ( !(sdbmem = sdb_struct->CheckMember(member_elm)) ) 
                                                     ERROR
    SDBEV4(sdbmem->get_sys_ident(),ID_SIZE)
    member_elm = NULL;
    if ( acp && (path_extension = acp->GetElement(indx0++)) )
      member_elm = (BNFData *)path_extension->GetElement(1);
    
    if ( member_elm )
    {
      if ( !(sdb_type = sdbmem->GetTypeDef()) )
      {
        SDBSET(655)   // incomplete check
        type_name = sdbmem->get_ddetype();
        SDBError().DisplayMessage();
        LEAVESEQ
      }
      if ( !(sdb_struct = sdbmem->GetStructDef()) )  SDBERR(656)
    }
  }
  if ( !sdbmem )                                     ERROR
  type_name = sdbmem->get_ddetype();
RECOVER
  SDBError().DisplayMessage();
  type_name = NULL;
ENDSEQ
  return(type_name);
}

/******************************************************************************/
/**
\brief  Check_Member - 


\return cond - 

\param  member_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check_Member"

logical SDB_Structure :: Check_Member (char *member_names )
{


  return(GetMember(member_names,NULL) ? YES : NO);
}

/******************************************************************************/
/**
\brief  Check_MemberList - 


\return cond - 

\param  member_names - 
\param  type_names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check_MemberList"

logical SDB_Structure :: Check_MemberList (char *member_names, char *type_names )
{
  char              member_name[40];
  char              type_name[40];
  char             *type;
  PI(SDB_Property) *prop_pi;
  logical           term = NO;
BEGINSEQ
  gvtxstb(member_name,member_names,ID_SIZE);
  gvtxstb(type_name,type_names,ID_SIZE);
  
  if ( !members(member_name) )                       LEAVESEQ

  type = members.GetCurrentTypeDef()->smcbname;
  if ( !memcmp(type,type_name,ID_SIZE) )             LEAVESEQ
    
  if ( prop_pi = GetMember(member_names,NULL) )      ERROR
  if ( members.Delete() )                            ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetAction - 


\return act_pi - 

\param  action_names - 
\param  dbs_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAction"

PI(CAU_Action) *SDB_Structure :: GetAction (char *action_names, PI(SDB_Structure) *dbs_ptr )
{
  PI(CAU_Action)        *act_pi = NULL;
  SDB_Structure         *dbsptr;
BEGINSEQ
  if ( act_pi = LocateAction(action_names) )         LEAVESEQ
  
  if ( dbs_ptr )               // recursivly search in base structures
  {
    smcebase.Cancel();         
    while ( (++smcebase).Exist() )
    {
      SDBEV1(smcebase.Get()->get_ddetype(),ID_SIZE)
      TypeKey    type_key(smcebase.Get()->get_ddetype(),0);
      if ( !(dbsptr = dbs_ptr->Get(type_key.GetKey())) )
                                                     SDBERR(20)
      if ( act_pi = dbsptr->GetAction(action_names,dbs_ptr) )
      {
        SDBRESET                                     LEAVESEQ
      }
    }
  }
RECOVER

ENDSEQ
  return(act_pi);
}

/******************************************************************************/
/**
\brief  GetMember - 


\return prop_pi - 

\param  member_names - 
\param  dbs_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMember"

PI(SDB_Property) *SDB_Structure :: GetMember (char *member_names, PI(SDB_Structure) *dbs_ptr )
{
  PI(SDB_Property)      *prop_pi = NULL;
  char                   member_name[ID_SIZE];
  SDB_Structure         *dbsptr;
BEGINSEQ
// --> pc_SDB_Structure::GetMember(prop_path)
  gvtxstb(member_name,member_names,ID_SIZE);

  prop_pi = (PI(SDB_Property) *)&smcepdde;
  smcepdde.Cancel();
  while ( (++smcepdde).Exist() )
    if (  !memcmp(smcepdde->get_sys_ident(),member_name,ID_SIZE) )
                                                           LEAVESEQ
  prop_pi = (PI(SDB_Property) *)&smcepref;
  smcepref.Cancel();
  while ( (++smcepref).Exist() )
    if (  !memcmp(smcepref->get_sys_ident(),member_name,ID_SIZE) )
                                                           LEAVESEQ
  prop_pi = (PI(SDB_Property) *)&smcershp;
  smcershp.Cancel();
  while ( (++smcershp).Exist() )
    if (  !memcmp(smcershp->get_sys_ident(),member_name,ID_SIZE) )
                                                           LEAVESEQ
  prop_pi = (PI(SDB_Property) *)&smcebase;
  smcebase.Cancel();
  while ( (++smcebase).Exist() )
    if (  !memcmp(smcebase->get_sys_ident(),member_name,ID_SIZE) )
                                                           LEAVESEQ
  if ( dbs_ptr )               // recursivly search in base structures
  {
    smcebase.Cancel();         
    while ( (++smcebase).Exist() )
    {
      SDBEV1(smcebase.Get()->get_ddetype(),ID_SIZE)
      TypeKey    type_key(smcebase.Get()->get_ddetype(),0);
      if ( !(dbsptr = dbs_ptr->Get(type_key.GetKey())) )
                                                     SDBERR(20)
      if ( prop_pi = dbsptr->GetMember(member_name,dbs_ptr) )
      {
        SDBRESET                                     LEAVESEQ
      }
    }
  }
  prop_pi = NULL;

RECOVER
  prop_pi = NULL;
ENDSEQ
  return(prop_pi);
}

/******************************************************************************/
/**
\brief  GetMemberPath - 


\return prop_pi - 

\param  prop_path - 
\param  dbs_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMemberPath"

PI(SDB_Property) *SDB_Structure :: GetMemberPath (char *prop_path, PI(SDB_Structure) *dbs_ptr )
{
  SDB_Structure         *dbsptr  = this;
  PI(SDB_Property)      *prop_pi = NULL;
  char                  *string_ptr = strdup(prop_path);
  char                  *string     = string_ptr;
  char                   mnames[ID_SIZE+1];
  char                  *pos;
BEGINSEQ
  memset(mnames,0,sizeof(mnames));
  while ( string && *string )
  {
    strncpy(mnames,string,ID_SIZE);
    if ( string = strchr(string,'.') )
    {
      string++;
      if ( !(pos = strchr(mnames,'.')) )             ERROR
        *pos = 0;
    }
    if ( !(prop_pi = dbsptr->GetMember(mnames,dbs_ptr)) )
                                                     ERROR
    if ( string )
      if ( !(dbsptr = dbs_ptr->Get(prop_pi->Get()->get_ddetype())) )
                                                     ERROR
  }

RECOVER
  prop_pi = NULL;
ENDSEQ
  if ( string_ptr )
    free(string_ptr);
  return(prop_pi);
}

/******************************************************************************/
/**
\brief  GetResID - 


\return resid - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResID"

int32 SDB_Structure :: GetResID ( )
{

  return (   res_id >= 0 
           ? res_id  
           : resource_ref.Get(FIRST_INSTANCE)
           ? resource_ref->GetResID() : 0  );


}

/******************************************************************************/
/**
\brief  GetSDBMember - 


\return sdbmem - 

\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSDBMember"

SDB_Member *SDB_Structure :: GetSDBMember (char *names )
{
  SDB_Structure          *sdb_struct;
  SDB_Member             *sdbmem = NULL;
  char                    mname[ID_SIZE];
  int32                   indx0 = 0;
  logical                 cond  = YES;
BEGINSEQ
  gvtxstb(mname,names,ID_SIZE);
  if ( (sdbmem = smcepdde(mname)) ||
       (sdbmem = smcepref(mname)) ||
       (sdbmem = smcershp(mname)) ||
       (sdbmem = smcebase(mname))    )               LEAVESEQ
  
  while ( sdbmem = smcebase(indx0++) )
    if ( sdb_struct = sdbmem->GetStructDef() )
      if ( sdbmem = sdb_struct->GetSDBMember(mname) )
        LEAVESEQ
  
  ERROR
RECOVER
  sdbmem = NULL;
ENDSEQ
  return(sdbmem);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - 

\param  strnames - 
\param  dbhandle - 
\param  create_tid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical SDB_Structure :: Initialize (char *strnames, DatabaseHandle &dbhandle, logical create_tid )
{
  logical                 term = NO;
BEGINSEQ
  if ( strnames )
    gvtxstb(sys_ident,strnames,ID_SIZE);
    
  if ( !itype )
  {
    if ( create_tid )
      if ( !(itype = dbhandle->GetNewTypeID()) )    ERROR
    typetype = TYP_Structure;
    smcestyp = create_tid ? ST_USER : ST_CLASS;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsBasedOn - 


\return cond - 

\param  dbs_pi - 
\param  strnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBasedOn"

logical SDB_Structure :: IsBasedOn (PI(SDB_Structure) &dbs_pi, char *strnames )
{
  PI(SDB_Structure)       struct_pi(dbs_pi);
  SDB_BaseStruct         *baseptr;
  int32                   indx0 = 0;
  char                    strname[ID_SIZE];
  logical                 cond = NO;
  gvtxstb(strname,strnames,ID_SIZE);
  while ( baseptr = smcebase(indx0++) )
  {
    TypeKey    type_key(baseptr->get_ddetype(),0);
    if ( cond = !memcmp(strname,baseptr->get_ddetype(),ID_SIZE) ||
                ( struct_pi(type_key.GetKey()) && 
                  struct_pi->IsBasedOn(struct_pi,strnames) ) )
      break;  
  }
  return(cond);
}

/******************************************************************************/
/**
\brief  Reset - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical SDB_Structure :: Reset ( )
{
  logical                 term = NO;
  checked  = NO;
  ready    = NO;
  modified = YES;
  
  if ( !itype && version )
  {
    version = 0;
    SDBRESET
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SDB_Structure - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Structure"

     SDB_Structure :: SDB_Structure ( )
                     : SDB_NameSpace (),
CAU_Causality (),
  res_id(UNDEF),
  modified(NO),
  checked(NO),
  ready(NO),
  version(CUR_VERSION),
  local(NO),
  vf_opt(NO),
  versioning(NO),
  allignment(UNDEF),
  compress(NO),
  global_identity(NO),
  last_key_num(UNDEF)
{



}

/******************************************************************************/
/**
\brief  SetCreate - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCreate"

logical SDB_Structure :: SetCreate ( )
{
  int32                    indx0 = 0;
  logical                 term = NO;
  while ( smcepref.Get(indx0++) )
  {
    smcepref->set_create(YES);
    smcepref.Modify();
    smcepref.Save();
  }

  indx0 = 0;
  while ( smcershp.Get(indx0++) )
  {
    smcershp->set_create(YES);
    smcershp.Modify();
    smcershp.Save();
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SetModified - 


\return term - 

\param  check - 
\param  mod_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetModified"

logical SDB_Structure :: SetModified (logical check, StructModLevel mod_level )
{
  logical   cond = NO;
BEGINSEQ
  if ( check )
  {
    if ( modified )                                  LEAVESEQ
    if ( !smceodaba.Get(FIRST_INSTANCE) )            LEAVESEQ
  }   
      
  modified = YES;
  ready    = NO;
  checked  = NO;
  cond     = YES;
  // für 'imbedded' und 'key' müssen nun noch alle Strukturen markiert werden, 
  // die Attributes oder exclusive BaseStructs dieses Typs besitzen (YES,mod_level). 
  // Für 'key' müssen außerdem noch alle diejenigen markiert werden, die sortierte 
  // References dieses Types besitzen. Außerdem müssen für 'key' alle abgeleiteten 
  // Strukturen markiert werden, die die Structure als Schlüsselkomponente referenzieren.
  // Und das ist immer noch nicht alles, Uff!!!!!
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  SetOwning - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetOwning"

logical SDB_Structure :: SetOwning ( )
{
  int32                    indx0 = 0;
  logical                 term = NO;
  while ( smcepref.Get(indx0++) )
  {
    smcepref->set_owning(YES);
    smcepref.Modify();
    smcepref.Save();
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SetReady - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetReady"

logical SDB_Structure :: SetReady ( )
{
  logical                 term = NO;
  if ( (!ready || modified) && checked )
  {
    modified = NO;
    version  = smceodaba.GetObjectHandle().GetVersion();
    ready    = YES;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  SetVersion - 


\return term - 

\param  dbs_dpi - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetVersion"

logical SDB_Structure :: SetVersion (PI(SDB_Structure) dbs_dpi )
{
  SDB_Property           *property;
  int32                    indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  while ( property = smcebase.Get(indx0++) )
    if ( !property->get_ddetrans() )
    {
      TypeKey   type_key(property->get_ddetype(),0);    
      if ( dbs_dpi(type_key.GetKey()) )
        dbs_dpi->SetVersion(dbs_dpi);
      if ( dbs_dpi->get_version() > version )
      {
        version = smceodaba.GetObjectHandle().GetVersion();
        LEAVESEQ
      }
    }

  indx0 = 0;
  while ( property = smcepdde.Get(indx0++) )
    if ( !property->get_ddetrans() && property->get_reference_level() <= RL_direct )
    {
      if ( dbs_dpi(property->get_ddetype()) )
        dbs_dpi->SetVersion(dbs_dpi);
      if ( dbs_dpi->get_version() > version )
      {
        version = smceodaba.GetObjectHandle().GetVersion();
        LEAVESEQ
      }
    }


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  set_checked - 



\param  checkopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_checked"

void SDB_Structure :: set_checked (logical checkopt )
{

  checked = checkopt;

}

/******************************************************************************/
/**
\brief  set_modified - 


\return term - 

\param  mod_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_modified"

logical SDB_Structure :: set_modified (logical mod_opt )
{
  logical                 term = NO;

  return(term);
}

/******************************************************************************/
/**
\brief  set_ready - 



\param  readyopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_ready"

void SDB_Structure :: set_ready (logical readyopt )
{

  ready = readyopt;

}

/******************************************************************************/
/**
\brief  set_smcestyp - 



\param  str_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_smcestyp"

void SDB_Structure :: set_smcestyp (SDB_ST str_type )
{

  smcestyp = str_type;

}

/******************************************************************************/
/**
\brief  set_typetype - 



\param  metatype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_typetype"

void SDB_Structure :: set_typetype (TYP_TYPES metatype )
{

  typetype = metatype;

}

/******************************************************************************/
/**
\brief  set_version - 



\param  version_nr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_version"

void SDB_Structure :: set_version (uint16 version_nr )
{

  version = version_nr;

}


