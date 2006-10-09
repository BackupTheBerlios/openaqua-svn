/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel
\class    ODC_FunctImp



\date     $Date: 2006/05/20 19:08:52,39 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODC_FunctImp"

#include  <pfmodel.h>
#ifndef   P_ODC_Include_HPP
#define   P_ODC_Include_HPP
#include  <sPI.hpp>
class       ODC_Include;
PI_dcl     (ODC_Include)
#endif
#ifndef   P_ODC_Main_HPP
#define   P_ODC_Main_HPP
#include  <sPI.hpp>
class       ODC_Main;
PI_dcl     (ODC_Main)
#endif
#ifndef   P_ODC_PFunction_HPP
#define   P_ODC_PFunction_HPP
#include  <sPI.hpp>
class       ODC_PFunction;
PI_dcl     (ODC_PFunction)
#endif
#ifndef   P_SDB_Member_HPP
#define   P_SDB_Member_HPP
#include  <sPI.hpp>
class       SDB_Member;
PI_dcl     (SDB_Member)
#endif
#include  <sODC_PFunction.hpp>
#include  <sODC_Variable.hpp>
#include  <sPropertyHandle.hpp>
#include  <sSDB_Member.hpp>
#include  <spc_ODC_FunctImp.hpp>
#include  <spc_ODC_Variable.hpp>
#include  <sODC_FunctImp.hpp>


/******************************************************************************/
/**
\brief  GetCIFunctName

\return fctnames
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  nstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCIFunctName"

char *ODC_FunctImp :: GetCIFunctName (PropertyHandle *prophdl, NString &nstring )
{

  nstring = ""; 
  return ( pc_ODC_FunctImp(prophdl).GetCIFunctionName(nstring) );

}

/******************************************************************************/
/**
\brief  GetCIRetValue

\return retval_string
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  nstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCIRetValue"

char *ODC_FunctImp :: GetCIRetValue (PropertyHandle *prophdl, NString &nstring )
{

  nstring = ""; 
  return ( pc_ODC_FunctImp(prophdl).GetCIReturnValue(nstring) );

}

/******************************************************************************/
/**
\brief  GetCOMParmList

\return parm_string
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  nstring
\param  prototyp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCOMParmList"

char *ODC_FunctImp :: GetCOMParmList (PropertyHandle *prophdl, NString &nstring, logical prototyp )
{

  nstring = ""; 
  return ( pc_ODC_FunctImp(prophdl).GetCOMParmList(nstring,prototyp,NO) );

}

/******************************************************************************/
/**
\brief  GetParmCallList

\return parm_string
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  nstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmCallList"

char *ODC_FunctImp :: GetParmCallList (PropertyHandle *prophdl, NString &nstring )
{

  nstring = ""; 
  return ( pc_ODC_FunctImp(prophdl).GetParmCallList(nstring) );
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetParmList

\return parm_string
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  nstring
\param  prototyp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmList"

char *ODC_FunctImp :: GetParmList (PropertyHandle *prophdl, NString &nstring, logical prototyp )
{

  nstring = ""; 
  return ( pc_ODC_FunctImp(prophdl).GetCParmList(nstring,prototyp) );

}

/******************************************************************************/
/**
\brief  IsIFImplement

\return cond - 
/******************************************************************************/
/**
\brief  i00


\param  if_imp_praefix
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIFImplement"

logical ODC_FunctImp :: IsIFImplement (char *if_imp_praefix )
{

  return ( !strncmp(sys_ident,if_imp_praefix,MIN(sizeof(sys_ident),strlen(if_imp_praefix))) );

}

/******************************************************************************/
/**
\brief  SetLineCount

\return term
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  propnames
\param  line_cnt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineCount"

logical ODC_FunctImp :: SetLineCount (PropertyHandle *prophdl, char *propnames, int16 line_cnt )
{
  logical    term = NO;
  pc_ODC_FunctImp    imp(prophdl);
  term = imp.SetLineCount(propnames,line_cnt);
  return(term);
}

/******************************************************************************/
/**
\brief  UpdatePrototype

\return term
/******************************************************************************/
/**
\brief  i00


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdatePrototype"

logical ODC_FunctImp :: UpdatePrototype (PropertyHandle *prophdl )
{

  pc_ODC_FunctImp  impl_pc(prophdl);
  impl_pc.Headline(YES);

//  return ( UpdateHeadline(clsnames,memb_ph,constret,slot_opt,signal_opt,YES) );

  return(NO);
}

/******************************************************************************/
/**
\brief  UpdateSource

\return term
/******************************************************************************/
/**
\brief  i00


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateSource"

logical ODC_FunctImp :: UpdateSource (PropertyHandle *prophdl )
{

  pc_ODC_FunctImp  impl_pc(prophdl);
  impl_pc.Headline(NO);
  
//  return ( UpdateHeadline(clsnames,pfunct_ph,constret,NO,NO,NO) );
  return(NO);
}


