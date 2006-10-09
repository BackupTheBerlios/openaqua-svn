/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    pc_TopicFromOldStyle

\brief    


\date     $Date: 2006/03/13 21:30:42,73 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_TopicFromOldStyle"

#include  <pfmodel.h>
#include  <sPropertyHandle.hpp>
#include  <spc_TopicFromOldStyle.hpp>


/******************************************************************************/
/**
\brief  Check

\return srce_description

\param  prophdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

PropertyHandle *pc_TopicFromOldStyle :: Check (PropertyHandle *prophdl )
{
  PropertyHandle   *srce_resource_ref = prophdl->GPH("resource_ref");
  PropertyHandle   *srce_description  = srce_resource_ref->GPH("description");
  logical           term              = NO;
BEGINSEQ
  if ( !IsPositioned() )                             ERROR
  
  if ( !srce_resource_ref->Get(FIRST_INSTANCE) ||
       !srce_description->Get(FIRST_INSTANCE)     )  ERROR
       

RECOVER
  srce_description = NULL;
ENDSEQ
  return(srce_description);
}

/******************************************************************************/
/**
\brief  Setup_ODC_FunctImp

\return term

\param  prophdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup_ODC_FunctImp"

logical pc_TopicFromOldStyle :: Setup_ODC_FunctImp (PropertyHandle *prophdl )
{
  PropertyHandle  *description = prophdl->GPH("description");
  logical          term        = NO;
  description->Get(FIRST_INSTANCE);
  Setup_SDB_Resource(description);
  
  pc_TopicFromOldStyle  parameters(GPH("parameters"));
  parameters.Setup_collection(prophdl->GPH("parm_description"));
  return(term);
}

/******************************************************************************/
/**
\brief  Setup_ODC_ImpClass

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup_ODC_ImpClass"

logical pc_TopicFromOldStyle :: Setup_ODC_ImpClass ( )
{
 PropertyHandle ref_dsc_class(GetDBHandle(),"ODS_Class",PI_Read); 
  PropertyHandle  *fct_descriptions = ref_dsc_class.GPH("fct_descriptions");
  int32            indx0            = 0;
  logical             term          = NO;
BEGINSEQ
  if ( !ref_dsc_class.Get(ExtractKey()) )            LEAVESEQ
    
  if ( Setup_SDB_Structure() )                       ERROR
  
  pc_TopicFromOldStyle  pfunctions(GPH("pfunctions"));
  while ( pfunctions.Get(indx0++) )
    if ( fct_descriptions->Get(pfunctions.ExtractKey()) )
      pfunctions.Setup_ODC_PFunction(fct_descriptions);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Setup_ODC_PFunction

\return term

\param  prophdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup_ODC_PFunction"

logical pc_TopicFromOldStyle :: Setup_ODC_PFunction (PropertyHandle *prophdl )
{
  PropertyHandle  *imp_parms   = prophdl->GPH("imp_parms");
  PropertyHandle  *retval      = prophdl->GPH("retval");
  PropertyHandle  *retval_name = GPH("retval_name");
  int32            indx0       = 0;
  logical          term        = NO;
BEGINSEQ
  if ( Setup_SDB_Resource(prophdl) )                 ERROR
  *GPH("action") = *prophdl->GPH("action");
  
  pc_TopicFromOldStyle  implementations(GPH("implementations"));
  while ( implementations.Get(indx0++) )
    if ( imp_parms->Get(implementations.ExtractKey()) )
      implementations.Setup_ODC_FunctImp(imp_parms);

  if ( *retval_name->GetString()     &&
        retval->Get(FIRST_INSTANCE)  &&
       *retval_name == *retval->GPH("sys_ident") )
  {
    PropertyHandle       var_ph(GetDBHandle(),"ODC_Variable",PI_Write);
    pc_TopicFromOldStyle variables(&var_ph);
    if ( variables.Get(*retval_name) )
      variables.Setup_SDB_Resource(retval);
  }

  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Setup_SDB_Resource

\return term

\param  prophdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup_SDB_Resource"

logical pc_TopicFromOldStyle :: Setup_SDB_Resource (PropertyHandle *prophdl )
{
  PropertyHandle   *resource_ref      = GPH("resource_ref");
  PropertyHandle   *description       = resource_ref->GPH("description");
  PropertyHandle   *srce_description  = NULL;
  int32             empty_num         = 0;
  int               repl_opt          = TestSysVariable("REPLACE_DESCRIPTIONS","YES") ? YES :
                                        TestSysVariable("REPLACE_DESCRIPTIONS","NO")  ? NO  : AUTO;
  logical           term              = NO;
BEGINSEQ
  if ( !(srce_description = Check(prophdl)) )        ERROR
    
  if ( !resource_ref->Get(FIRST_INSTANCE) )
    resource_ref->Add(Key((char *)&empty_num));
  
  if ( description->Get(FIRST_INSTANCE) )
  {
    if ( *description == *srce_description )         LEAVESEQ
    if ( repl_opt == NO ||
         (repl_opt == AUTO && !SDBError().GetDecision(992,GPH("sys_ident")->GetString(),"different despription topic does already exist in structure/implementation.\nOverwrite from old style desctiption? ")) )
                                                     LEAVESEQ
    description->Delete();
  }
  
  *description = *srce_description;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Setup_SDB_Structure

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup_SDB_Structure"

logical pc_TopicFromOldStyle :: Setup_SDB_Structure ( )
{
 PropertyHandle ref_dsc_class(GetDBHandle(),"ODS_Class",PI_Read); 
  logical          term             = NO;
BEGINSEQ
  if ( !ref_dsc_class.Get(ExtractKey()) )          LEAVESEQ
    
  Setup_SDB_Resource(&ref_dsc_class);

  pc_TopicFromOldStyle   smcebase(GPH("smcebase"));
  smcebase.Setup_collection(ref_dsc_class.GPH("bas_descriptions"));

  pc_TopicFromOldStyle   smcepdde(GPH("smcepdde"));
  smcepdde.Setup_collection(ref_dsc_class.GPH("atr_descriptions"));

  pc_TopicFromOldStyle   smcepref(GPH("smcepref"));
  smcepref.Setup_collection(ref_dsc_class.GPH("ref_descriptions"));

  pc_TopicFromOldStyle   smcershp(GPH("smcershp"));
  smcershp.Setup_collection(ref_dsc_class.GPH("rsp_descriptions"));

  pc_TopicFromOldStyle   smcepsmc(GPH("smcepsmc"));
  smcepsmc.Setup_collection(ref_dsc_class.GPH("sor_descriptions"));

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Setup_SDB_ValueList

\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup_SDB_ValueList"

logical pc_TopicFromOldStyle :: Setup_SDB_ValueList ( )
{
 PropertyHandle ref_dsc_class(GetDBHandle(),"ODS_Class",PI_Read); 
 PropertyHandle sys_ident(GPH("sys_ident"));
 PropertyHandle V8("V8");
 PropertyHandle sv;
 int32          indx0 = 0;
 logical        term  = NO;
BEGINSEQ
  if ( !ref_dsc_class.Get(ExtractKey()) )            LEAVESEQ
  DBObjectHandle dbh(GetDBHandle());
  PropertyHandle    vl(dbh,"SDB_ValueList",PI_Write);
  sv = sys_ident + V8;
  if ( !vl.Provide(sv) )                 ERROR
  pc_TopicFromOldStyle   vlist(&vl);
  Setup_SDB_Resource(&ref_dsc_class);
  
  PH(&vl,values)
  pc_TopicFromOldStyle   pc_values(&values);
  PH(&ref_dsc_class,val_descriptions);

  if ( !dict.IsValid() )
    dict.Open(GetDBHandle());
  PropertyHandle    cs(dict,sys_ident.GetString(),PI_Read);
  while ( cs.Get(indx0++) )
  {
    values.Add(*cs.GPH("string"));
    *values.GPH("__AUTOIDENT") = cs.GPH("value");
    *values.GPH("type") = cs.GPH("type");
    if ( val_descriptions.Get(*values.GPH("sys_ident")) )
      pc_values.Setup_SDB_Resource(&val_descriptions);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Setup_collection

\return term

\param  prophdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup_collection"

logical pc_TopicFromOldStyle :: Setup_collection (PropertyHandle *prophdl )
{
  int32            indx0             = 0;
  logical          term              = NO;
  while ( Get(indx0++) )
    if ( prophdl->Get(ExtractKey()) )
      Setup_SDB_Resource(prophdl);

  return(term);
}

/******************************************************************************/
/**
\brief  pc_TopicFromOldStyle - 



\param  prophdl -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_TopicFromOldStyle"

                        pc_TopicFromOldStyle :: pc_TopicFromOldStyle (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl),
  dict()
{



}


