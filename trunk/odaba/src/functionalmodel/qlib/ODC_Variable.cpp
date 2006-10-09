/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel
\class    ODC_Variable



\date     $Date: 2006/05/20 19:08:20,79 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODC_Variable"

#include  <pfmodel.h>
#include  <sNString.hpp>
#include  <spc_ODC_Variable.hpp>
#include  <sODC_Variable.hpp>


/******************************************************************************/
/**
\brief  GetCastType

\return string
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  nstring
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCastType"

char *ODC_Variable :: GetCastType (PropertyHandle *prophdl, NString &nstring )
{

  nstring = "";
  return ( pc_ODC_Variable(prophdl).GetCastType(nstring) );

}


