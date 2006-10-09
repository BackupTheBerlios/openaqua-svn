/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc_ClassMemberInputHelp

\brief    


\date     $Date: 2006/06/13 23:00:09,25 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ClassMemberInputHelp"

#include  <pdesign.h>
#include  <sBNFData.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc_ClassMemberInputHelp.hpp>


/******************************************************************************/
/**
\brief  CreateVariables - 


\return term - 

\param  codestring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateVariables"

logical pc_ClassMemberInputHelp :: CreateVariables (char *codestring )
{
  BNFData           *bdata       = NULL;
  BNFData           *member      = NULL;
  int32              indx0       = 0;
  logical            term        = NO;
BEGINSEQ
// members               := member(*)
// member                := [_global] type_spec declarators ';'
LEAVESEQ  // muss noch gemacht werden
  if ( !codestring || !*codestring )                      LEAVESEQ
  if ( bdata = GetDictionary().ParseExpression(codestring,"members") )
  {
    while ( member = bdata->GetElement(indx0++) )
    { 
//      if ( member->GetElement("simple_type_spec") ) // type_spec is simple_type_spec
//  add to vlist      
    }
  }
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DeinitHandles - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeinitHandles"

void pc_ClassMemberInputHelp :: DeinitHandles ( )
{

  funct_impls.DeinitHandles();
  
  ident.Close();
  source.Close();
  type.Close();
  filled.Close();

  Close();


}

/******************************************************************************/
/**
\brief  InitHandles - 


\return term - 

\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitHandles"

logical pc_ClassMemberInputHelp :: InitHandles (PropertyHandle *prophdl )
{
  logical                 term = NO;
  Open(prophdl->GPH("member"));

  funct_impls.InitHandles(this);
    
  ident.Open(GPH("ident"));
  source.Open(GPH("source"));  
  type.Open(GPH("type"));
  filled.Open(GPH("filled"));
  return(term);
}

/******************************************************************************/
/**
\brief  IsFilled - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsFilled"

logical pc_ClassMemberInputHelp :: IsFilled ( )
{

  return ( GetParentProperty()->GPH("filled")->IsTrue() );

}

/******************************************************************************/
/**
\brief  ProvideFunctionInputHelp - 


\return member_input_pc - 

\param  funct_ph - 
\param  refresh_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideFunctionInputHelp"

pc_ClassFunctImpInputHelp *pc_ClassMemberInputHelp :: ProvideFunctionInputHelp (PropertyHandle *funct_ph, logical refresh_opt )
{
  PropertyHandle            *funct_id       = funct_ph->GPH("sys_ident");
  pc_ClassFunctImpInputHelp *funct_input_pc = &funct_impls;
BEGINSEQ
  if ( Get(*funct_id) )
  {
    if ( !refresh_opt )                              LEAVESEQ
    funct_impls.DeleteSet();
    filled = NO;
    Save();
  }
  else
    Add(*funct_id);
                                      
  P_SDBCERR
RECOVER
  funct_input_pc = NULL;
ENDSEQ
  return(funct_input_pc);
}

/******************************************************************************/
/**
\brief  ResetLocals - 


\return term - 

\param  memb_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetLocals"

logical pc_ClassMemberInputHelp :: ResetLocals (PropertyHandle *memb_ph )
{
  int32              indx0 = 0;
  logical            term  = NO;
  while ( memb_ph->Get(indx0++) )
    if ( type.GetInt() == OT_Parameter || type.GetInt() == OT_LocalVariable )
      if ( !memb_ph->Delete() )
        indx0--;

  return(term);
}

/******************************************************************************/
/**
\brief  SetFilled - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilled"

logical pc_ClassMemberInputHelp :: SetFilled ( )
{
  logical     term = NO;
BEGINSEQ
  *GetParentProperty()->GPH("filled") = YES;
  Save();                                            P_SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupList - 


\return term - 

\param  memb_ph - 
\param  ode_objtype - 
\param  base_opt - 
\param  direct_access - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupList"

logical pc_ClassMemberInputHelp :: SetupList (PropertyHandle *memb_ph, ODE_OBJECTTYPE ode_objtype, logical base_opt, logical direct_access )
{
  PropertyHandle    *class_ident = memb_ph->GetParentProperty()->GPH("sys_ident");
  PropertyHandle    *privilege   = memb_ph->GPH("ddeprv");
  PropertyHandle     key((char *)NULL);
  std::string        ident_string;
  char              *string      = NULL;
  int32              indx0       = 0;
  logical            term        = NO;
  while ( memb_ph->Get(indx0++) )
  {
    if ( (!base_opt && direct_access) || *privilege == "ODC_public" || *privilege == "ODC_protected" )
    {
      if ( *(string = memb_ph->GPH("sys_ident")->GetString()) != '~' )
      { 
        ident_string.clear();
        ident_string.append(string);
        if ( !direct_access && ode_objtype != OT_Function && *privilege != "ODC_public" )
        {
          ident_string.insert(0,"get_");
          ident_string.append("()");
        }
      
        key = (char *)ident_string.c_str();
        if ( !Get(key) )
        {
          GetInitInstance();
          type  = (int32)ode_objtype;
          ident = (char *)ident_string.c_str();
          if ( base_opt && class_ident )
            source = *class_ident;
          Save();
        }
      }
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  SetupVariables - 


\return term - 

\param  codestring - 
\param  ode_objtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupVariables"

logical pc_ClassMemberInputHelp :: SetupVariables (char *codestring, ODE_OBJECTTYPE ode_objtype )
{
  PropertyHandle     vname;
  int32              indx0       = 0;
  logical            term        = NO;
BEGINSEQ
// members               := member(*)
// member                := [_global] type_spec declarators ';'
LEAVESEQ  // muss noch gemacht werden
  if ( CreateVariables(codestring) )                      ERROR

//  while ( member = vlist(indx0++) )
//  { 
//      if ( member->GetElenebt("simple_type_spec") ) // type_spec is simple_type_spec
      
      if ( !Get(vname) )
      {
        GetInitInstance();
        type  = (int32)ode_objtype;
        ident = vname;
        Save();
      }
//  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ClassMemberInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ClassMemberInputHelp"

     pc_ClassMemberInputHelp :: pc_ClassMemberInputHelp ( )
                     : PropertyHandle (),
  ident(),
  source(),
  type(),
  filled(),
  funct_impls()
{



}


