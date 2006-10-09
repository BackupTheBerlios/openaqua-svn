/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    ODE_Project



\date     $Date: 2006/05/23 19:36:08,85 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODE_Project"

#include  <pdesign.h>
#ifndef   GSRT_ODE_Project_HPP
#define   GSRT_ODE_Project_HPP
#include  <sODE_Project.hpp>
#include  <sGSRT.h>
#endif
#include  <sBNFData.hpp>
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <ifil.h>
#include  <igvts.h>
#include  <spODE.hpp>
#include  <spc1_ODC_ImpClass.hpp>
#include  <spc1_ODC_PFunction.hpp>
#include  <spc_ClassFunctImpInputHelp.hpp>
#include  <spc_ClassMemberInputHelp.hpp>
#include  <sODE_Project.hpp>


/******************************************************************************/
/**
\brief  ClosePHs


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ClosePHs"

void ODE_Project :: ClosePHs ( )
{

  enums.Close();
  structures.Close();
  impclasses.Close();
  project_classes.Close();
  project.Close();

}

/******************************************************************************/
/**
\brief  DeinitRefProjects

\return 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeinitRefProjects"

logical ODE_Project :: DeinitRefProjects ( )
{
  ODE_Project     *odeprj = NULL;
  int32            indx0  = 0;
  logical          term   = NO;
  while ( odeprj = ref_projects->GetEntry(++indx0) )
    odeprj->Deinitialize();
  
  if ( ref_projects )
  {
    ref_projects->Clear();
    ref_projects->stsrfil();
  }

  return(term);
}

/******************************************************************************/
/**
\brief  Deinitialize


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinitialize"

void ODE_Project :: Deinitialize ( )
{

  input_help.DeinitHandles();
  DeinitRefProjects();
  
  ClosePHs();
  db_handle.Close();
  memset(project_name,' ',sizeof(project_name));
  implemented = NO;

  ODE_Helper::Deinitialize();

}

/******************************************************************************/
/**
\brief  GetClassInputHelpPH

\return prophdl - Property handle

\param  refresh_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClassInputHelpPH"

PropertyHandle *ODE_Project :: GetClassInputHelpPH (logical refresh_opt )
{
  pc_ClassInputHelp    *class_input_pc = &input_help;
BEGINSEQ
  if ( input_help.InitHandles(db_handle,project_name) )
                                                     ERROR
  if ( !refresh_opt )
    if ( input_help.IsFilled() )                     LEAVESEQ

  InitRefProjects();
  
  project_classes.SetupClassList(class_input_pc,ref_projects,NO);
  if ( input_help.SetFilled() )                      ERROR

RECOVER
  class_input_pc = NULL;
ENDSEQ
  return(class_input_pc);
}

/******************************************************************************/
/**
\brief  GetFunctionInputHelpPH

\return prophdl - Property handle

\param  type_key
\param  codestring
\param  textpos
\param  refresh_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFunctionInputHelpPH"

PropertyHandle *ODE_Project :: GetFunctionInputHelpPH (TypeKey &type_key, char *codestring, int32 textpos, logical refresh_opt )
{
  char                      *accpath        = NULL;
  char                       lookup_type    = ' ';
  PropertyHandle            *funct_ph       = NULL;
  pc1_ODC_ImpClass          *impcls_pc      = NULL;
  pc_ClassFunctImpInputHelp *funct_input_pc = NULL;
BEGINSEQ
  if ( input_help.InitHandles(db_handle,project_name) )
                                                     ERROR
  if ( !(accpath = GetPath(codestring,textpos,lookup_type)) )
                                                     ERROR
  if ( !(funct_ph = GetTargetFunction(type_key,accpath,lookup_type)) )
                                                     ERROR
  if ( !(impcls_pc = GetImplementedClass(funct_ph->GetParentProperty())) )
                                                     ERROR
  if ( !(funct_input_pc = input_help.ProvideFunctionInputHelp(funct_ph,refresh_opt)) )
                                                     ERROR
  
  if ( funct_input_pc->IsFilled() )                  LEAVESEQ
  impcls_pc->SetupFunctImpList(funct_ph->GetString("sys_ident"),funct_input_pc,this,NO);
  if ( funct_input_pc->SetFilled() )                  ERROR

RECOVER
  funct_input_pc = NULL;
ENDSEQ
  if ( accpath )
    free(accpath);
  return(funct_input_pc);
}

/******************************************************************************/
/**
\brief  GetImplementedClass

\return impcls_pc
-------------------------------------------------------------------------------
\brief  i0


\param  type_key
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImplementedClass"

pc1_ODC_ImpClass *ODE_Project :: GetImplementedClass (TypeKey &type_key )
{
  ODE_Project      *odeprj    = NULL;
  int32             indx0     = 0;
  pc1_ODC_ImpClass *impcls_pc = &project_classes;
BEGINSEQ
  if ( project_classes.IsImplemented(type_key,NO) )  LEAVESEQ
    
  InitRefProjects();
  
  while ( odeprj = ref_projects->GetEntry(++indx0) )
    if ( odeprj->get_project_classes().IsImplemented(type_key,NO) )
    {
      impcls_pc = &odeprj->get_project_classes();
      LEAVESEQ
    }
   ERROR
RECOVER
  impcls_pc = NULL;
ENDSEQ
  return(impcls_pc);
}

/******************************************************************************/
/**
\brief  i01


\param  class_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetImplementedClass"

pc1_ODC_ImpClass *ODE_Project :: GetImplementedClass (PropertyHandle *class_ph )
{
  ODE_Project      *odeprj    = NULL;
  int32             indx0     = 0;
  pc1_ODC_ImpClass *impcls_pc = &project_classes;
BEGINSEQ
  if ( project_classes.Is(*class_ph) )               LEAVESEQ

  if ( !ref_projects )                               ERROR
  while ( odeprj = ref_projects->GetEntry(++indx0) )
    if ( odeprj->get_project_classes().Is(*class_ph) )
    {
      impcls_pc = &odeprj->get_project_classes();
      LEAVESEQ
    }
   ERROR
RECOVER
  impcls_pc = NULL;
ENDSEQ
  return(impcls_pc);
}

/******************************************************************************/
/**
\brief  GetMemberInputHelpPH

\return memb_input_pc

\param  type_key
\param  codestring
\param  offset
\param  refresh_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMemberInputHelpPH"

pc_ClassMemberInputHelp *ODE_Project :: GetMemberInputHelpPH (TypeKey &type_key, char *codestring, int32 offset, logical refresh_opt )
{
  char                    *accpath       = NULL;
  char                     lookup_type   = 'M';
  logical                  direct_acc    = UNDEF;
  pc1_ODC_ImpClass        *impcls_pc     = NULL;
  pc_ClassMemberInputHelp *memb_input_pc = NULL;

BEGINSEQ
  if ( input_help.InitHandles(db_handle,project_name) )
                                                     ERROR
  if ( codestring )
  {
    if ( !(accpath = GetPath(codestring,offset,lookup_type)) )
                                                     ERROR
    if ( *gvtxbts(accpath,accpath,strlen(accpath)) )
      impcls_pc = GetImplementedClass(GetTargetClass(type_key,accpath,lookup_type));
  }

  if ( !impcls_pc )
  {
    direct_acc = YES;
    impcls_pc  = GetImplementedClass(type_key);
  }
    
  if ( !(memb_input_pc = input_help.ProvideMemberInputHelp(impcls_pc,refresh_opt)) )
                                                     ERROR
  
  if ( memb_input_pc->IsFilled() )                   LEAVESEQ
  impcls_pc->SetupMemberList(memb_input_pc,this,NO,direct_acc);
  if ( memb_input_pc->SetFilled() )                  ERROR

RECOVER
  memb_input_pc = NULL;
ENDSEQ
  if ( accpath )
    free(accpath);
  return(memb_input_pc);
}

/******************************************************************************/
/**
\brief  InitRefProjects

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitRefProjects"

logical ODE_Project :: InitRefProjects ( )
{
  PropertyHandle  *ref_projects_ph = NULL;
  ODE_Project     *odeprj          = NULL;
  int32            indx0           = 0;
  logical          term            = NO;
BEGINSEQ
  if ( !ref_projects )
    if ( !(ref_projects = new GSRT(ODE_Project)(10,sizeof(ODE_Project),ID_SIZE,1,'S',YES)) )
                                                     P_ERR(95)
  
  if ( !ref_projects->stscfil() && project.IsPositioned() )
  {
    ref_projects_ph = project.GPH("ref_projects");
    while ( ref_projects_ph->Get(indx0++) )
    {
      odeprj = ref_projects->AddFreeEntry();
      odeprj->Initialize(ref_projects_ph);
    }
    ref_projects->stssfil();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize

\return term - 

\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ODE_Project :: Initialize (PropertyHandle *prophdl )
{
  char           cpath[1025];
  logical        term = NO;
BEGINSEQ
  Deinitialize();

  if ( !prophdl->IsPositioned() )                    LEAVESEQ

  strncpy(project_name,prophdl->GPH("sys_ident")->GetString(),ID_SIZE);
  
  strcpy(cpath,prophdl->GPH("proj_path")->GetString());
  strcat(cpath,"/");
  strcat(cpath,prophdl->GPH("resource_base")->GetString());
  
  if ( implemented = pc1_ODC_Project(prophdl).IsImplemented(NO) )
    db_handle = prophdl->GetDBHandle();
  else
    if ( db_handle.Open(prophdl->GetDictionary(),cpath,PI_Write,YES,YES) )
    {
      P_SDBCERR
      P_ERR(ODABA_ERROR)
    }
  
  if ( OpenPHs(implemented ? project_name : project_name+2,PI_Read) )
                                                     ERROR
  ODE_Helper::Initialize(this);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitializePFunction

\return cond - 

\param  pfunct_pc
\param  type_key
\param  ode_ctx
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializePFunction"

logical ODE_Project :: InitializePFunction (pc1_ODC_PFunction *pfunct_pc, TypeKey &type_key, pODE *ode_ctx )
{
  PropertyHandle   *pfuncts = impclasses.GPH("pfunctions");
  logical           cond    = YES;
BEGINSEQ
  if ( !impclasses.IsImplemented(type_key,NO) )      ERROR
    
  if ( pfuncts->Get(pfunct_pc->ExtractSortKey()) )
  {
    if ( pfunct_pc->InitializePFunction(pfuncts) )   ERROR
  }
  else
  {
    if ( !ode_ctx )                                  ERROR
    if ( !pfunct_pc->InitializePFunction(&impclasses,ode_ctx) )
                                                     ERROR
  }
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ODE_Project


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODE_Project"

     ODE_Project :: ODE_Project ( )
                     : ODE_Helper(),
  implemented(NO),
  db_handle(),
  ref_projects(NULL),
  project(NULL),
  project_classes(NULL),
  impclasses(NULL),
  structures(NULL),
  enums(),
  input_help()
{
  Deinitialize();

}

/******************************************************************************/
/**
\brief  OpenPHs

\return term - 

\param  prjnames
\param  accopt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenPHs"

logical ODE_Project :: OpenPHs (char *prjnames, PIACC accopt )
{
  PropertyHandle   idkey(prjnames);
  char             fname[ID_SIZE+1];
  char             fext[ID_SIZE+1];
  logical          term    = NO;
BEGINSEQ
  if ( !db_handle.IsValid() )                        ERROR
    
  if ( !impclasses.IsValid() )
    if ( impclasses.Open(db_handle,"ODC_ImpClass",accopt) )
                                                     ERROR
  if ( !structures.IsValid() )
    if ( structures.Open(db_handle,"SDB_Structure",accopt) )
                                                     ERROR  
  if ( !enums.IsValid() )
    if ( enums.Open(db_handle,"SDB_ValueList",accopt) )
                                                     ERROR
  if ( !project.IsValid() )
  {
    if ( project.Open(db_handle,"ODC_Project",accopt) )
                                                     ERROR
    if ( idkey.IsEmpty() )
      idkey = GetFileNameInfo(db_handle.GetPath(),fname,fext,sizeof(fname),sizeof(fext));

    if ( project.GetCount() )
      project.Get(idkey);
  }

  if ( !project_classes.IsValid() )
    if ( project_classes.Open(project.GPH("classes")) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideType

\return term - 

\param  type_key
\param  impcls_pc
\param  cs_ph
\param  no_struct
\param  high_ctx
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideType"

logical ODE_Project :: ProvideType (TypeKey &type_key, pc1_ODC_ImpClass *impcls_pc, PropertyHandle *cs_ph, logical no_struct, CTX_Control *high_ctx )
{
  logical         term           = NO;
BEGINSEQ
  if ( impclasses.IsImplemented(type_key,NO) )
  {
    if ( impcls_pc )
    {
      if ( impcls_pc->ProvideReferencedClass(&impclasses,project_name,high_ctx) )
                                                     ERROR
    }
    LEAVESEQ
  }
  
  if ( enums.Get(type_key.GetKey()) )
  {
    if ( cs_ph )
    {
      cs_ph->Add(type_key.GetKey());                  P_SDBCERR
    }
    LEAVESEQ
  }

  if ( !no_struct && structures.Get(type_key.GetKey()) )      LEAVESEQ
  
  ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~ODE_Project


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODE_Project"

     ODE_Project :: ~ODE_Project ( )
{
  Deinitialize();

  delete ref_projects;
  ref_projects = NULL;
}


