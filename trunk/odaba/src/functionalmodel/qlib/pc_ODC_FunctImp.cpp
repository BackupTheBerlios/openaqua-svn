/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    pc_ODC_FunctImp

\brief    


\date     $Date: 2006/07/12 19:09:46,46 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_FunctImp"

#include  <pfmodel.h>
#include  <spc_ODC_PFunction.hpp>
#include  <spc_ODC_Variable.hpp>
#include  <spc_ODC_FunctImp.hpp>


/******************************************************************************/
/**
\brief  CI_Headline - 


\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CI_Headline"

char *pc_ODC_FunctImp :: CI_Headline (logical prototyp )
{
  PropertyHandle  *head_line = GPH("head_line");
  NString          nstring;
  *head_line = CI_Headline(nstring,prototyp);
  return(head_line->GetString());
}

/******************************************************************************/
/**
\brief  i01 - 


\param  nstring - 
\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CI_Headline"

char *pc_ODC_FunctImp :: CI_Headline (NString &nstring, logical prototyp )
{
  pc_ODC_PFunction   funct_pc(GetParentProperty());

  GetCIReturnValue(nstring);
  nstring.Append("__cdecl ");
  GetCIFunctionName(nstring);

  GetCParmList(nstring,NO,YES);

  if ( prototyp && funct_pc.IsConst() )
    nstring += " const";
  return(nstring);
}

/******************************************************************************/
/**
\brief  CPP_Headline - 


\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CPP_Headline"

char *pc_ODC_FunctImp :: CPP_Headline (logical prototyp )
{
  PropertyHandle  *head_line = GPH("head_line");
  NString          nstring;
  *head_line = CPP_Headline(nstring,prototyp);
  return(head_line->GetString());
}

/******************************************************************************/
/**
\brief  i01 - 


\param  nstring - 
\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CPP_Headline"

char *pc_ODC_FunctImp :: CPP_Headline (NString &nstring, logical prototyp )
{
  pc_ODC_PFunction funct_pc(GetParentProperty());
  funct_pc.FunctionTypeCPPString(nstring,prototyp);
  GetCParmList(nstring,prototyp,YES);

  if ( funct_pc.IsConst() )
    nstring += " const";   

  return(nstring);
}

/******************************************************************************/
/**
\brief  CPP_Headline_COM - 


\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CPP_Headline_COM"

char *pc_ODC_FunctImp :: CPP_Headline_COM (logical prototyp )
{
  PropertyHandle  *head_line = GPH("head_line");
  NString          nstring;
  *head_line = CPP_Headline_COM(nstring,prototyp);
  return(head_line->GetString());
}

/******************************************************************************/
/**
\brief  i01 - 


\param  nstring - 
\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CPP_Headline_COM"

char *pc_ODC_FunctImp :: CPP_Headline_COM (NString &nstring, logical prototyp )
{
  pc_ODC_PFunction   funct_pc(GetParentProperty());
  PropertyHandle    *sys_ident = GPH("sys_ident");
  funct_pc.FunctionTypeCOMString(nstring,prototyp,
                                 *sys_ident == "COMP" ? YES : NO,
                                 *sys_ident == "COMG" ? YES : NO);
  
  GetCOMParmList(nstring,prototyp);


  return(nstring);
}

/******************************************************************************/
/**
\brief  CPP_Headline_IF - 


\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CPP_Headline_IF"

char *pc_ODC_FunctImp :: CPP_Headline_IF (logical prototyp )
{
  PropertyHandle  *head_line = GPH("head_line");
  NString          nstring;
  *head_line = CPP_Headline_IF(nstring,prototyp);
  return(head_line->GetString());
}

/******************************************************************************/
/**
\brief  i01 - 


\param  nstring - 
\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CPP_Headline_IF"

char *pc_ODC_FunctImp :: CPP_Headline_IF (NString &nstring, logical prototyp )
{
  pc_ODC_PFunction funct_pc(GetParentProperty());
  nstring.Append("logical ");
  nstring.Append("__cdecl ");
  nstring.Append(funct_pc.GPH("sys_ident")->GetString());
  GetCParmList(nstring,prototyp,YES);


  return(nstring);
}

/******************************************************************************/
/**
\brief  C_Headline - 


\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "C_Headline"

char *pc_ODC_FunctImp :: C_Headline (logical prototyp )
{
  PropertyHandle  *head_line = GPH("head_line");
  NString          nstring;
  *head_line = C_Headline(nstring,prototyp);
  return(head_line->GetString());
}

/******************************************************************************/
/**
\brief  i01 - 


\param  nstring - 
\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "C_Headline"

char *pc_ODC_FunctImp :: C_Headline (NString &nstring, logical prototyp )
{
  pc_ODC_PFunction funct_pc(GetParentProperty());
  funct_pc.FunctionTypeCString(nstring,prototyp);
  GetCParmList(nstring,NO,YES);

  if ( prototyp && funct_pc.IsConst() )
    nstring += " const";
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetCIFunctionName - 


\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCIFunctionName"

char *pc_ODC_FunctImp :: GetCIFunctionName (NString &nstring )
{
  pc_ODC_PFunction   funct_pc(GetParentProperty());
  PropertyHandle    *sys_ident = GPH("sys_ident");
  funct_pc.GetCIFunctionName(nstring);
  
  if ( *sys_ident != "i0" && *sys_ident != "i00" )
    nstring += sys_ident->GetString();

  return(nstring);
}

/******************************************************************************/
/**
\brief  GetCIReturnValue - 


\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCIReturnValue"

char *pc_ODC_FunctImp :: GetCIReturnValue (NString &nstring )
{
  pc_ODC_PFunction   funct_pc(GetParentProperty());
  funct_pc.GetCIReturnValue(nstring);
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetCOMParmList - 


\return string - 

\param  nstring - 
\param  prototyp - 
\param  par_opt_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCOMParmList"

char *pc_ODC_FunctImp :: GetCOMParmList (NString &nstring, logical prototyp, logical par_opt_w )
{
  pc_ODC_Variable  parm_pc(GPH("parameters"));
  PropertyHandle  *sys_ident   = GPH("sys_ident");
  PropertyHandle  *funct_ph    = NULL;
  PropertyHandle  *retval_name = NULL;
  int32            indx0       = 0;
  logical          first       = YES;
BEGINSEQ
  if ( par_opt_w )
    nstring += " (";
  
  parm_pc.GetParmList(nstring,YES,prototyp);
  
  if ( funct_ph && !funct_ph->GPH("ddetype")->IsEmpty() )
  {
    if ( !first )
      nstring.Append(", ");

    pc_SDB_Member   funct_member(funct_ph);
    funct_member.DataTypeCOMString(nstring,*sys_ident != "COMP" ? YES : NO);
                                                      ERROR
    if ( *(retval_name = funct_ph->GPH("retval_name")) == "term" )
      nstring += "vb_term";
    else
      nstring += retval_name->GetString();
  }
  
  if ( par_opt_w )
    nstring += " )";
RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetCParmList - 


\return string - 

\param  nstring - 
\param  prototyp - 
\param  par_opt_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCParmList"

char *pc_ODC_FunctImp :: GetCParmList (NString &nstring, logical prototyp, logical par_opt_w )
{
  PropertyHandle  *sys_ident  = GPH("sys_ident");
  PropertyHandle  *parameters = GPH("parameters");
  PropertyHandle  *glob_impl  = NULL;
BEGINSEQ
  if ( !parameters->GetCount() && GetParentProperty() )
  {
    glob_impl = new PropertyHandle(GetDBHandle(),"ODC_FunctImp",PI_Read);
    if ( !SDBERROR )
    {
      if ( glob_impl->Get(*sys_ident) )
        parameters = glob_impl->GPH("parameters");
      if ( !parameters->GetCount() && *sys_ident == "_IF_" )
      {
        if ( par_opt_w )
          nstring.Append("( ");
        nstring += "PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype";
        if ( par_opt_w )
          nstring.Append(" )");
        LEAVESEQ
      }
    }
  }
  
  if ( par_opt_w )
    nstring += " (";
  
  pc_ODC_Variable  parm_pc(parameters);
  parm_pc.GetParmList(nstring,NO,prototyp);

  if ( par_opt_w )
    nstring += " )";

RECOVER

ENDSEQ
  delete glob_impl;
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetPFunction - 


\return prophdl - 

\param  pos_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPFunction"

PropertyHandle *pc_ODC_FunctImp :: GetPFunction (logical pos_opt )
{
  PropertyHandle   *pfunct_ph = GetParentProperty();
BEGINSEQ
  if ( pfunct_ph->Inherits("ODC_PFunction") )       LEAVESEQ
  
  pfunct_ph = GPH("function");
  if ( !pos_opt )                                   LEAVESEQ
  
  if ( !pfunct_ph->Get(FIRST_INSTANCE) )            ERROR
RECOVER
  pfunct_ph = NULL;
ENDSEQ
  return(pfunct_ph);
}

/******************************************************************************/
/**
\brief  GetParmCallList - 


\return string - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmCallList"

char *pc_ODC_FunctImp :: GetParmCallList (NString &nstring )
{
  pc_ODC_Variable  parm_pc(GPH("parameters"));
  nstring += "(";
  parm_pc.GetParmCallList(nstring);
  nstring += ")";
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetProgramLanguage - 


\return plang - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProgramLanguage"

ProgramLanguage pc_ODC_FunctImp :: GetProgramLanguage ( )
{
  pc_ODC_PFunction   pfunct(GetPFunction(YES));
  PropertyHandle    *ph;
  if ( !(ph = pfunct.GetImpClass(YES)) )
    ph = pfunct.GetExecutable();

  return (   ph 
           ? (ProgramLanguage)ph->GPH("opt_language")->GetInt()
           : PL_undefined );

}

/******************************************************************************/
/**
\brief  HasIFImplement - 


\return cond - 

\param  if_imp_praefix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasIFImplement"

logical pc_ODC_FunctImp :: HasIFImplement (char *if_imp_praefix )
{
  int32     curidx  = GetCurrentIndex();
  int32     indx0   = 0;
  logical   started = StartRTA() ? YES : NO;
  logical   cond    = YES;
BEGINSEQ
  while ( Get(indx0++) )
    if ( IsIFImplement(if_imp_praefix) )            LEAVESEQ
    
  ERROR

RECOVER
  cond = NO;
ENDSEQ
  if ( curidx != AUTO )
    Get(curidx);
  StopRTA(started);
  return(cond);
}

/******************************************************************************/
/**
\brief  Headline - 


\return string - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Headline"

char *pc_ODC_FunctImp :: Headline (logical prototyp )
{
  PropertyHandle  *head_line = GPH("head_line");
  NString          nstring;
  *head_line = Headline(nstring,prototyp);
  return(head_line->GetString());
}

/******************************************************************************/
/**
\brief  i01 - 


\param  nstring - 
\param  prototyp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Headline"

char *pc_ODC_FunctImp :: Headline (NString &nstring, logical prototyp )
{
  PropertyHandle  *sys_ident = GPH("sys_ident");
BEGINSEQ
  nstring = "";
  
  if ( TestSysVariable("C_INTERFACE","Y") )
    CI_Headline(nstring,prototyp);
  else
    switch ( GetProgramLanguage() )
    {
      case PL_CORBA_IDL:
      case PL_COM_IDL  :
      case PL_CPP      : 
           if ( *sys_ident == "_IF_" )
             CPP_Headline_IF(nstring,prototyp); 
           else if ( *sys_ident == "COM" )
             CPP_Headline_COM(nstring,prototyp);
           else
             CPP_Headline(nstring,prototyp);
           break;
      case PL_C        : 
           C_Headline(nstring,prototyp);
           break;
      default     : 
           SDBERR(60)
    }
RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  IsIFImplement - 


\return cond - 

\param  if_imp_praefix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIFImplement"

logical pc_ODC_FunctImp :: IsIFImplement (char *if_imp_praefix )
{
  PropertyHandle    *sys_ident = GPH("sys_ident");
  logical            cond      = YES;
BEGINSEQ
  if ( !if_imp_praefix )                             ERROR
  if ( strlen(sys_ident->GetString()) < strlen(if_imp_praefix) )
                                                     ERROR
  if ( memcmp(sys_ident->GetString(),if_imp_praefix,strlen(if_imp_praefix)) )
                                                     ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Merge - 


\return term - 

\param  srce_ph - 
\param  replace - 
\param  replace_parms - 
\param  replace_sys - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Merge"

logical pc_ODC_FunctImp :: Merge (PropertyHandle *srce_ph, logical replace, logical replace_parms, logical replace_sys )
{
  PropertyHandle  *pfunct_ph   = GetParentProperty(); 
  PropertyHandle  *tparameters = GPH("parameters");
  PropertyHandle  *sparameters = srce_ph->GPH("parameters");
  int32            indx0       = 0;
  logical          term        = NO;
BEGINSEQ
  SetSysVariable("IMPLEMENTATION",GPH("sys_ident")->GetString());
  
  pfunct_ph->ExecuteInstanceAction("ParmCallList",NULL);
  SetSysVariable("PARMLIST",pfunct_ph->GetActionResult());
  
  if ( MergeCode(GPH("init_code") ,srce_ph->GPH("init_code") ,replace) ||
       MergeCode(GPH("start_code"),srce_ph->GPH("start_code"),replace) ||
       MergeCode(GPH("code")      ,srce_ph->GPH("code")      ,replace) ||
       MergeCode(GPH("error_code"),srce_ph->GPH("error_code"),replace) ||
       MergeCode(GPH("term_code") ,srce_ph->GPH("term_code") ,replace)    )
                                                      ERROR
  *GPH("sequence") = *srce_ph->GPH("sequence");
  *GPH("recover")  = *srce_ph->GPH("recover");

  if ( replace_parms )
  {
    tparameters->DeleteSet();
    while ( sparameters->Get(indx0++) )    
    {
      tparameters->Add(sparameters->Get());           SDBCERR
      tparameters->Save();
      tparameters->ToTop(); 
    }
  }

  if ( replace_sys )
  {
    GPH("init_code")->ReplaceSysVariables();
    GPH("start_code")->ReplaceSysVariables();
    GPH("code")->ReplaceSysVariables();
    GPH("error_code")->ReplaceSysVariables();
    GPH("term_code")->ReplaceSysVariables();
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  MergeCode - 


\return term - 

\param  targ_ph - 
\param  srce_ph - 
\param  replace - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MergeCode"

logical pc_ODC_FunctImp :: MergeCode (PropertyHandle *targ_ph, PropertyHandle *srce_ph, logical replace )
{
  logical    term = NO;
BEGINSEQ
  if ( replace )
    *targ_ph = "";

  if ( !srce_ph->Get(0L) || srce_ph->IsEmpty() )     LEAVESEQ
  
  if ( replace )
    *targ_ph = *srce_ph;
  else
    *targ_ph = *targ_ph + "\n// merged\n" + *srce_ph;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetLineCount - 


\return term - 

\param  propnames - 
\param  line_cnt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineCount"

logical pc_ODC_FunctImp :: SetLineCount (char *propnames, int16 line_cnt )
{
  logical    term = NO;
BEGINSEQ
  if ( NoWrite() || !propnames )                     ERROR

  *GPH(propnames) = line_cnt;                        SDBCERR
  Save();                                            SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupCodeBlockOptions - 
        xxx

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCodeBlockOptions"

logical pc_ODC_FunctImp :: SetupCodeBlockOptions ( )
{
  char         *code   = GPH("code")->GetString();
  logical       seqopt = NO;
  logical       recopt = NO;
  logical       term   = NO;
BEGINSEQ
  if ( NoWrite() )                                   ERROR
    
  if ( strstr(code,"ERR") )
  {
    seqopt = YES;
    recopt = YES;
  }
  else if ( strstr(code,"LEAVESEQ") )
    seqopt = YES;

  *GPH("sequence") = seqopt;
  *GPH("recover")  = recopt;
  
  Save();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupCodeBlocks - 


\return term - 

\param  glob_opt - global option
\param  glob_ident - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCodeBlocks"

logical pc_ODC_FunctImp :: SetupCodeBlocks (char glob_opt, char *glob_ident )
{
  PropertyHandle *pfunct_ph   = GetParentProperty(); 
  PropertyHandle *impclass_ph = pfunct_ph->GetParentProperty(); 
  PropertyHandle *start_code  = GPH("start_code");
  PropertyHandle *error_code  = GPH("error_code");
  PropertyHandle *term_code   = GPH("term_code");
  PropertyHandle *memb_ph     = GetParentProperty()->GPH("SDB_Member");
  PropertyHandle *retval_name = GetParentProperty()->GPH("retval_name");
  PropertyHandle *ddeinit     = GetParentProperty()->GPH("ddeinit");
  PropertyHandle *errorcase   = GetParentProperty()->GPH("errorcase");
  int32           indx0       = 0;
  std::string     data("");
  logical         term        = NO;
BEGINSEQ
  if ( NoWrite() )                                   ERROR
    
  if ( !SetupCodeBlocksFromGlobal(glob_opt,glob_ident) )
                                                    LEAVESEQ

  if ( *impclass_ph->GPH("sys_ident") == *pfunct_ph->GPH("sys_ident") )
    SetupInitCode(impclass_ph,YES);
  
  if ( *retval_name->GetString() > ' ' )
  {
    data = "  ";
    if ( !memb_ph->ExecuteInstanceAction("DataTypeCString",NULL) )
    {
      data.append(memb_ph->GetActionResult());
      data.append("   ");
    }
    data.append(retval_name->GetString());
    if ( *ddeinit->GetString() > ' ' )
    {
      data.append(" = ");
      data.append(ddeinit->GetString());
    }
    data.append(";");
    *start_code = (char *)data.c_str();
      
    if ( *errorcase->GetString() > ' ' )
    {
      data = "  ";
      data.append(retval_name->GetString());
      data.append(" = ");
      data.append(errorcase->GetString());
      data.append(";");
      *error_code = (char *)data.c_str();
    }

    data = "  ";
    data.append("return(");
    data.append(retval_name->GetString());
    data.append(");");
    *term_code = (char *)data.c_str();
  }    
    
  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupCodeBlocksFromGlobal - 


\return term - 

\param  glob_opt - global option
\param  glob_ident - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCodeBlocksFromGlobal"

logical pc_ODC_FunctImp :: SetupCodeBlocksFromGlobal (char glob_opt, char *glob_ident )
{
  char       *ident = NULL;
  int         len   = 0;
  logical     term  = NO;
BEGINSEQ
  if ( !glob_opt )                                   ERROR
  if ( NoWrite() )                                   ERROR

  PropertyHandle    global_impl_ph(GetDBHandle(),"ODC_FunctImp",PI_Read);
                                                     SDBCERR
  if ( !glob_ident || !*glob_ident )
    glob_ident = GPH("sys_ident")->GetString();
  PropertyHandle phglob_ident(glob_ident);
  if ( !global_impl_ph.Get(phglob_ident) )
  {
    if ( glob_opt == YES )                          ERROR
    ident = strdup(glob_ident);
    while ( (len = strlen(ident)) > 1 )
    {
      ident[len-1] = 0;
      PropertyHandle phident(ident);
      if ( global_impl_ph.Get(phident) )
        break;
    }
    free(ident);
  }
  if ( !global_impl_ph.IsPositioned() )             ERROR
  
  *GPH("head_line") = "";
  Merge(&global_impl_ph,YES,NO,YES);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupInitCode - 


\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 


\param  class_ph - 
\param  clear_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInitCode"

logical pc_ODC_FunctImp :: SetupInitCode (PropertyHandle *class_ph, logical clear_opt )
{
  NString           nstring;
  PropertyHandle   *init_code = GPH("init_code");
  PropertyHandle   *base_ph   = NULL;
  void             *base_inst = NULL;
  char              string[513];
  int32             curidx    = 0;
  int32             indx0     = 0;
  int32             pindx0    = 0;
  logical           firstp    = YES;
  logical           first     = YES;
  logical           term      = NO;
BEGINSEQ
  if ( NoWrite() )                                   ERROR
    
  if ( !class_ph )
    class_ph = GetParentProperty()->GetParentProperty();
  
  if ( !clear_opt && !init_code->IsEmpty() )
  {
    nstring  = init_code->GetString();
    nstring += "\r\n//** new **\r\n\r\n";
  }
  
  base_ph = class_ph->GPH("smcebase");
  if ( base_ph->GetCount() > 0 )
  {
    PropertyHandle     imp_classes(GetDBHandle(),"ODC_ImpClass",PI_Read);
    PropertyHandle    *pfuncts = imp_classes.GPH("pfunctions");
    PropertyHandle    *impls   = pfuncts->GPH("implementations");
    PropertyHandle    *parms   = impls->GPH("parameters");

    PropertyHandle    *base_memb    = base_ph->GPH("SDB_Member");
    PropertyHandle    *base_ddetype = base_ph->GPH("ddetype");
    PropertyHandle    *base_ddegent = base_ph->GPH("ddegent");
  
    curidx  = base_ph->GetCurrentIndex();
    base_ph->ToTop();
    while ( base_ph->Get(indx0++) )
    {
      if  ( !first )
        nstring += ",\r\n";
  
      if ( !base_memb->ExecuteInstanceAction("DataTypeCString",NULL) )
        nstring += base_memb->GetActionResult();
      nstring += "(";
  
      if ( base_ddegent->IsEmpty()      &&
           imp_classes(*base_ddetype)   &&
           pfuncts->Get(*base_ddetype)  &&
           impls->Get(FIRST_INSTANCE)                 )
      {
        firstp = YES;
        pindx0 = 0;
        while ( parms->Get(pindx0++) )
        {
          if ( !firstp )
            nstring += ",";
          nstring += parms->GPH("sys_ident")->GetString();
          firstp = NO;
        }
      }
      
      nstring += ")";
      first = NO;
    }
  }
  if ( curidx != AUTO )
    base_ph->Get(curidx);
  
  SetupInitCode(nstring,class_ph->GPH("smcepdde"),first,YES);
  SetupInitCode(nstring,class_ph->GPH("smcepref"),first,NO);
  SetupInitCode(nstring,class_ph->GPH("smcershp"),first,NO);

  *init_code = (char *)nstring;
  Save();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  nstring - 
\param  prophdl - 
\param  first_ref - 
\param  init_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupInitCode"

logical pc_ODC_FunctImp :: SetupInitCode (NString &nstring, PropertyHandle *prophdl, logical &first_ref, logical init_opt )
{
  int32      curidx  = prophdl->GetCurrentIndex();
  int32      indx0   = 0;
  prophdl->ToTop();
  while ( prophdl->Get(indx0++) )
  {
    if  ( !first_ref )
      nstring += ",\r\n";
    
    nstring += ' ';
    nstring += ' ';
    nstring += prophdl->GPH("sys_ident")->GetString();
    nstring += "(";
    if ( init_opt )
      nstring += prophdl->GPH("ddeinit")->GetString();
    nstring += ")";
    
    first_ref = NO;
  }

  if ( curidx != AUTO )
    prophdl->Get(curidx);
  return(NO);

}

/******************************************************************************/
/**
\brief  pc_ODC_FunctImp - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_FunctImp"

     pc_ODC_FunctImp :: pc_ODC_FunctImp (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{



}


