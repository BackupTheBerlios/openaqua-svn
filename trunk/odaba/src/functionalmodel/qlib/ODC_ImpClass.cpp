/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel
\class    ODC_ImpClass



\date     $Date: 2006/05/20 19:07:56,73 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODC_ImpClass"

#include  <pfmodel.h>
#include  <cclrkey.h>
#include  <sPropertyHandle.hpp>
#include  <ifmi.h>
#include  <spc_ODC_ImpClass.hpp>
#include  <sODC_ImpClass.hpp>


/******************************************************************************/
/**
\brief  ExpressionsOnly

\return cond - 
/******************************************************************************/
/**
\brief  i00


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExpressionsOnly"

logical ODC_ImpClass :: ExpressionsOnly (PropertyHandle *prophdl )
{

  return ( pc_ODC_ImpClass(prophdl).ExpressionsOnly() );


}

/******************************************************************************/
/**
\brief  GetDocFileName

\return filnames
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  nstring
\param  doc_type
\param  if_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDocFileName"

char *ODC_ImpClass :: GetDocFileName (PropertyHandle *prophdl, NString &nstring, char *doc_type, logical if_opt )
{

  return ( pc_ODC_ImpClass(prophdl).GetDocFileName(nstring,doc_type,if_opt) );

}

/******************************************************************************/
/**
\brief  IsExprClass

\return cond - 
/******************************************************************************/
/**
\brief  i00


\param  prophdl
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsExprClass"

logical ODC_ImpClass :: IsExprClass (PropertyHandle *prophdl )
{

  return ( pc_ODC_ImpClass(prophdl).IsExprClass() );


}

/******************************************************************************/
/**
\brief  IsIFClass

\return cond - 
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  if_imp_praefix
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIFClass"

logical ODC_ImpClass :: IsIFClass (PropertyHandle *prophdl, char *if_imp_praefix )
{
  pc_ODC_ImpClass   class_pc(prophdl);
  logical           cond = NO;
  if ( if_imp_praefix  )
    cond = class_pc.IsIFClass_Pref(if_imp_praefix );
  else
    cond = class_pc.IsIFClass_Pref("_IF_") ||
           class_pc.IsIFClass_Pref("COM");
  return(cond);
}

/******************************************************************************/
/**
\brief  LanguageExt

\return extension

\param  nstring
\param  dbhandle - 
\param  clsnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LanguageExt"

char *__cdecl ODC_ImpClass :: LanguageExt (NString &nstring, DatabaseHandle &dbhandle, char *clsnames )
{
  ODC_ImpClass *ociptr    = NULL;
  char          clsname[ID_SIZE];
BEGINSEQ
  nstring = "";
  gvtxstb(clsname,clsnames,ID_SIZE);

  PI(ODC_ImpClass)  oci_pi(dbhandle,"ODC_ImpClass",PI_Read);  
                                                     SDBCERR
  if ( !(ociptr = oci_pi(clsname)) )                 SDBERR(99)

  if ( !ProgramLanguageExtension(nstring,dbhandle,ociptr->get_opt_language()) )
                                                     ERROR

RECOVER

ENDSEQ
  return(nstring);
}


