/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    pc_ODC_Executable

\brief    


\date     $Date: 2006/07/12 19:12:37,98 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_Executable"

#include  <pfmodel.h>
#include  <cProgramLanguage.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ODC_PFunction.hpp>
#include  <spc_ODC_Project.hpp>
#include  <spc_SDB_Structure.hpp>
#include  <spc_SDB_TypeRef_fm.hpp>
#include  <spc_ODC_Executable.hpp>


/******************************************************************************/
/**
\brief  GetCompileCommand - 


\return command - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCompileCommand"

char *pc_ODC_Executable :: GetCompileCommand (NString &nstring )
{

  return ( pc_ODC_compile_object_base::GetCompileCommand(nstring,YES,NO,NULL) );

}

/******************************************************************************/
/**
\brief  GetLinkCommand - 


\return command - 

\param  nstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLinkCommand"

char *pc_ODC_Executable :: GetLinkCommand (NString &nstring )
{
  pc_ODC_Project    project_pc(GetProject());

  nstring = "";

  project_pc.GetLinkCommand(nstring,GPH("opt_debug")->IsTrue());
  
  nstring += ' ';
  nstring += GetString("sys_ident");

  return(nstring);
}

/******************************************************************************/
/**
\brief  pc_ODC_Executable - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_Executable"

     pc_ODC_Executable :: pc_ODC_Executable (PropertyHandle *prophdl )
                     : pc_ODC_compile_object_base (prophdl)
{



}


