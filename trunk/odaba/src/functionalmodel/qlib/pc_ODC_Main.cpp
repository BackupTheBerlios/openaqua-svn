/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel
\class    pc_ODC_Main



\date     $Date: 2006/05/09 17:23:05,45 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_ODC_Main"

#include  <pfmodel.h>
#include  <spc_ODC_Main.hpp>


/******************************************************************************/
/**
\brief  GetCompileCommand

\return command

\param  nstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCompileCommand"

char *pc_ODC_Main :: GetCompileCommand (NString &nstring )
{
  return ( pc_ODC_compile_object_base::GetCompileCommand(nstring,YES,NO,NULL) );
}

/******************************************************************************/
/**
\brief  pc_ODC_Main


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_ODC_Main"

     pc_ODC_Main :: pc_ODC_Main (PropertyHandle *prophdl )
                     : pc_ODC_compile_object_base (prophdl)
{
}


