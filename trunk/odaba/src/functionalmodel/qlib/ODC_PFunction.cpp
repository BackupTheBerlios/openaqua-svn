/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel
\class    ODC_PFunction



\date     $Date: 2006/05/20 19:08:42,50 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODC_PFunction"

#include  <pfmodel.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ODC_PFunction.hpp>
#include  <sODC_PFunction.hpp>


/******************************************************************************/
/**
\brief  SetLineCount

\return term
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  linecnt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLineCount"

logical ODC_PFunction :: SetLineCount (PropertyHandle *prophdl, int32 linecnt )
{
  logical   term = NO;
  pc_ODC_PFunction   pfunct_pc(prophdl);
  term = pfunct_pc.SetLineCount(linecnt);
  return(term);
}


