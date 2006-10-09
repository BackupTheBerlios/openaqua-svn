/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc_ClassInputHelp

\brief    


\date     $Date: 2006/06/13 23:00:44,87 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ClassInputHelp"

#include  <pdesign.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ClassFunctImpInputHelp.hpp>
#include  <spc_ClassMemberInputHelp.hpp>
#include  <spc_ClassInputHelp.hpp>


/******************************************************************************/
/**
\brief  DeinitHandles - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeinitHandles"

void pc_ClassInputHelp :: DeinitHandles ( )
{

  member.DeinitHandles();
  
  filled.Close();
  source.Close();
  ident.Close();
  
  Close();

}

/******************************************************************************/
/**
\brief  InitHandles - 


\return term - 

\param  dbhandle - 
\param  prjnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitHandles"

logical pc_ClassInputHelp :: InitHandles (DatabaseHandle &dbhandle, char *prjnames )
{
  char           *strnames     = "ClassInputHelp";
  char            tempextnames[2*ID_SIZE+2];
  logical         term         = NO;
BEGINSEQ
  strcat(strcat(strcpy(tempextnames,strnames),"_"),prjnames);
  
  if ( IsValid() )
  {
    if ( !strcmp(tempextnames,GetExtentName()) )     LEAVESEQ
    DeinitHandles();
  }
  
  if ( !dbhandle.GetDictionary().CreateTempExtent(strnames,tempextnames,"ik",NULL,NO,YES) )
                                                     P_SDBCERR
  Open(dbhandle,tempextnames,PI_Write);              P_SDBCERR
  
  ident.Open(GPH("ident"));
  source.Open(GPH("source"));
  filled.Open(GPH("filled"));
  
  member.InitHandles(this);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsFilled - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsFilled"

logical pc_ClassInputHelp :: IsFilled ( )
{

  return ( coll_filled );

}

/******************************************************************************/
/**
\brief  ProvideFunctionInputHelp - 


\return funct_input_pc - 

\param  funct_ph - 
\param  refresh_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideFunctionInputHelp"

pc_ClassFunctImpInputHelp *pc_ClassInputHelp :: ProvideFunctionInputHelp (PropertyHandle *funct_ph, logical refresh_opt )
{
  TypeKey                  type_key(funct_ph->GetParentProperty()->GetString("sys_ident"),
                                    funct_ph->GetParentProperty()->GetInt("namespace_id"));
  pc_ClassFunctImpInputHelp *funct_input_pc = NULL;
BEGINSEQ
  if ( !type_key )                                   ERROR
    
  Provide(type_key.GetKey());                        P_SDBCERR

  funct_input_pc = member.ProvideFunctionInputHelp(funct_ph,refresh_opt);
RECOVER
  funct_input_pc = NULL;
ENDSEQ
  return(funct_input_pc);
}

/******************************************************************************/
/**
\brief  ProvideMemberInputHelp - 


\return member_input_pc - 

\param  impcls_ph - 
\param  refresh_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideMemberInputHelp"

pc_ClassMemberInputHelp *pc_ClassInputHelp :: ProvideMemberInputHelp (PropertyHandle *impcls_ph, logical refresh_opt )
{
  TypeKey                  type_key(impcls_ph->GetString("sys_ident"),
                                    impcls_ph->GetInt("namespace_id"));
  pc_ClassMemberInputHelp *member_input_pc  = &member;
BEGINSEQ
  if ( !type_key )                                   ERROR
    
  if ( Get(type_key.GetKey()) )
  {
    if ( !refresh_opt )                              LEAVESEQ
    member.DeleteSet();
    filled = NO;
    Save();
  }
  else
    Add(type_key.GetKey());
                                      
  P_SDBCERR
RECOVER
  member_input_pc = NULL;
ENDSEQ
  return(member_input_pc);
}

/******************************************************************************/
/**
\brief  SetFilled - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilled"

logical pc_ClassInputHelp :: SetFilled ( )
{
  logical    term = NO;
BEGINSEQ
  coll_filled = YES;

  if ( !IsValid() )                                  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupList - 


\return term - 

\param  class_ph - 
\param  base_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupList"

logical pc_ClassInputHelp :: SetupList (PropertyHandle *class_ph, logical base_opt )
{
  PropertyHandle *prj_ident = class_ph->GetParentProperty()->GPH("sys_ident");
  Key             key;
  logical         term     = NO;
  class_ph->ToTop();
  while ( key = class_ph->NextKey() )
    if ( !Get(key) )
    {
      Add(key);
      if ( base_opt && prj_ident )
      {
        source = *prj_ident;
        Save();
      }
    }
  return(term);
}

/******************************************************************************/
/**
\brief  pc_ClassInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ClassInputHelp"

     pc_ClassInputHelp :: pc_ClassInputHelp ( )
                     : PropertyHandle (),
  ident(),
  source(),
  filled(),
  member(),
  coll_filled(NO)
{



}

/******************************************************************************/
/**
\brief  ~pc_ClassInputHelp - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pc_ClassInputHelp"

     pc_ClassInputHelp :: ~pc_ClassInputHelp ( )
{

  DeinitHandles();

}


