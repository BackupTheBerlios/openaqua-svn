/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    pc_ODC_ImpClass

\brief    


\date     $Date: 2006/06/04 11:29:10,78 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_ImpClass"

#include  <pfmodel.h>
#include  <cProgramLanguage.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ODC_PFunction.hpp>
#include  <spc_ODC_Project.hpp>
#include  <spc_SDB_Structure.hpp>
#include  <spc_SDB_TypeRef_fm.hpp>
#include  <spc_ODC_ImpClass.hpp>


/******************************************************************************/
/**
\brief  DeleteExternalResources - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteExternalResources"

logical pc_ODC_ImpClass :: DeleteExternalResources ( )
{
  PropertyHandle    *mod_level = GPH("mod_level");
  NString            nstring;     
  logical            term      = NO;
BEGINSEQ
  if ( !IsPositioned() )                             ERROR
  
  remove(GetDocFilePath(nstring,"Include",NO));
  remove(GetDocFilePath(nstring,"Include",YES));
  remove(GetDocFilePath(nstring,"Source",NO));
  remove(GetDocFilePath(nstring,"Source",YES));
  remove(GetDocFilePath(nstring,"Expression",UNDEF));
  remove(GetDocFilePath(nstring,"COM_Include",UNDEF));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExpressionsOnly - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExpressionsOnly"

logical pc_ODC_ImpClass :: ExpressionsOnly ( )
{

  return (   IsPositioned() 
           ? pc_ODC_PFunction(GPH("pfunctions")).HasExpressions(YES)
           : NO );


}

/******************************************************************************/
/**
\brief  GetCompileCommand - 


\return command - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCompileCommand"

char *pc_ODC_ImpClass :: GetCompileCommand (NString &nstring )
{

  return ( pc_ODC_compile_object_base::GetCompileCommand(nstring,NO,IsIFClass(),NULL) );

}

/******************************************************************************/
/**
\brief  HasActions - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasActions"

logical pc_ODC_ImpClass :: HasActions ( )
{


  return (   IsPositioned() 
           ? pc_ODC_PFunction(GPH("pfunctions")).HasActions()
           : NO );


}

/******************************************************************************/
/**
\brief  HasProperty - 


\return cond - 

\param  propnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasProperty"

logical pc_ODC_ImpClass :: HasProperty (char *propnames )
{
  logical          cond  = YES;
BEGINSEQ
  if ( !IsPositioned() )                             ERROR
  
  if ( pc_SDB_Structure(this).GetMember(NULL,propnames,NO,NO) )
                                                     LEAVESEQ
  if ( pc_ODC_PFunction(GPH("pfunctions")).HasFunction(propnames) )
                                                     LEAVESEQ
  ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsExprClass - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExprClass"

logical pc_ODC_ImpClass :: IsExprClass ( )
{

  return (   IsPositioned() 
           ? pc_ODC_PFunction(GPH("pfunctions")).HasExpressions(NO)
           : NO );


}

/******************************************************************************/
/**
\brief  IsIFClass - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIFClass"

logical pc_ODC_ImpClass :: IsIFClass ( )
{

  return( IsIFClass_Pref("_IF_") );

}

/******************************************************************************/
/**
\brief  IsIFClass_Pref - 


\return cond - 

\param  if_imp_praefix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIFClass_Pref"

logical pc_ODC_ImpClass :: IsIFClass_Pref (char *if_imp_praefix )
{

  return (   IsPositioned() 
           ? pc_ODC_PFunction(GPH("pfunctions")).HasIFFunctions(if_imp_praefix)
           : NO );

}

/******************************************************************************/
/**
\brief  PC_ClassAttr_Setup - 


\return term - 

\param  attr_ph - 
\param  srce_member - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PC_ClassAttr_Setup"

logical pc_ODC_ImpClass :: PC_ClassAttr_Setup (PropertyHandle *attr_ph, PropertyHandle *srce_member )
{
  PropertyHandle   *srce_ident = srce_member->GPH("sys_ident");
  PropertyHandle   *attr_ident = attr_ph->GPH("sys_ident");
  PropertyHandle   *attr_type  = attr_ph->GPH("ddetype");
  PropertyHandle   *attr_dim   = attr_ph->GPH("ddedim");
  PropertyHandle   *attr_init  = attr_ph->GPH("ddeinit");
  char              string[128];
  int32             indx0      = 0;
  logical           term       = NO;
BEGINSEQ
  while ( srce_member->Get(indx0++) )
  {
    if ( !attr_ph->Get(*srce_ident) )
    {
      attr_ph->Add();                                SDBCERR
      *attr_ident = *srce_ident;
    }
    if ( attr_type->IsEmpty() )
    {
      *attr_type  = "PropertyHandle";
      *attr_dim   = 1;
      *attr_init  = strcat(strcat(strcpy(string,"\""),srce_ident->GetString()),"\"");
      attr_ph->Save();                               SDBCERR
    }
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PC_Class_Setup - 


\return term - 

\param  str_ph - PropertyHandle of type SDB_Structure
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PC_Class_Setup"

logical pc_ODC_ImpClass :: PC_Class_Setup (PropertyHandle *str_ph )
{
  PropertyHandle      PropertyHandle_ph("PropertyHandle");
  PropertyHandle     *attr_ph   = GPH("smcepdde");
  PropertyHandle     *base_ph   = GPH("smcebase");
  PropertyHandle     *base_type = base_ph->GPH("ddetype");
  logical             term      = NO;
BEGINSEQ
  if ( NoWrite() || !str_ph->IsPositioned() )        ERROR

  if ( !base_ph->Get(FIRST_INSTANCE) )
    base_ph->Add(PropertyHandle_ph); 

  if ( base_type->IsEmpty() )
    *base_type = "PropertyHandle";
    
  PC_ClassAttr_Setup(attr_ph,str_ph->GPH("smcepdde"));
  PC_ClassAttr_Setup(attr_ph,str_ph->GPH("smcepref"));
  PC_ClassAttr_Setup(attr_ph,str_ph->GPH("smcershp"));
  
  Save();                                            SDBCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupReferences - 


\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReferences"

logical pc_ODC_ImpClass :: SetupReferences ( )
{
  pc_SDB_TypeRef_fm    type_references(GPH("type_references"));
  PropertyHandle      *pfunctions      = GPH("pfunctions");
  PropertyHandle      *implementations = pfunctions->GPH("implementations");
  PropertyHandle      *parameters      = implementations->GPH("parameters");
  PropertyHandle      *globals         = implementations->GPH("globals");
  int32                indx0           = 0;
  int32                iindx0          = 0;
  int32                vindx0          = 0;
  logical              term            = NO;

BEGINSEQ
  if ( SetupReferences(GPH("smcebase"),YES) )
    term = YES;
  
  if ( SetupReferences(GPH("smcepdde"),NO) )
    term = YES;
  
  if ( SetupReferences(GPH("smcepref"),NO) )
    term = YES;
  
  if ( SetupReferences(GPH("smcershp"),NO) )
    term = YES;

  while ( pfunctions->Get(indx0++) )
  {
    if ( type_references.ProvideReference(pfunctions) )
      term = YES;
    iindx0 = 0;
    while ( implementations->Get(iindx0++) )
    {
      vindx0 = 0;
      while ( parameters->Get(vindx0++) )
        if ( type_references.ProvideReference(parameters) )
          term = YES;
      vindx0 = 0;
      while ( globals->Get(vindx0++) )
        if ( type_references.ProvideReference(globals) )
          term = YES;
    } 
  }

  SetCompileState(CPS_requested);
  SetIncludeState(YES);
  Save();                                            SDBCERR 
   

RECOVER

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  member_ph - 
\param  base_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReferences"

logical pc_ODC_ImpClass :: SetupReferences (PropertyHandle *member_ph, logical base_opt )
{
  pc_SDB_TypeRef_fm    type_references(GPH("type_references"));
  int32                indx0 = 0;
  logical              term  = NO;
  while ( member_ph->Get(indx0++) )
  {
    if ( type_references.ProvideReference(member_ph) )
      term = YES;
    if ( base_opt )
      if ( type_references.SetupReference(IRL_SensiRef,IRL_undefined,YES) )
        term = YES;
  }  

  return(term);
}

/******************************************************************************/
/**
\brief  pc_ODC_ImpClass - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_ImpClass"

     pc_ODC_ImpClass :: pc_ODC_ImpClass (PropertyHandle *prophdl )
                     : pc_ODC_compile_object_base (prophdl)
{



}


