/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    pc0_ODC_ImpClass



\date     $Date: 2006/03/12 19:35:46,39 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_ODC_ImpClass"

#include  <padkctxi.h>
#include  <cCompileStates.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_ODC_PFunction.hpp>
#include  <spc0_ODC_ImpClass.hpp>


/******************************************************************************/
/**
\brief  IsIFClass - 


\return cond -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIFClass"

logical pc0_ODC_ImpClass :: IsIFClass ( )
{

  return( IsIFClass_Pref("_IF_") );

}

/******************************************************************************/
/**
\brief  IsIFClass_Pref - 


\return cond -

\param  if_imp_praefix -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIFClass_Pref"

logical pc0_ODC_ImpClass :: IsIFClass_Pref (char *if_imp_praefix )
{
  long        indx0 = 0;
  logical     cond  = YES;
BEGINSEQ
  pc0_ODC_PFunction  pfunctions(GPH("pfunctions"));
  
  while ( pfunctions(indx0++) )
    if ( pfunctions.IsIFFunction(if_imp_praefix) )  LEAVESEQ

  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ResCompileState - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResCompileState"

void pc0_ODC_ImpClass :: ResCompileState ( )
{

  *GPH("req_compile") = "CPS_undefined";

}

/******************************************************************************/
/**
\brief  pc0_ODC_ImpClass - 



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_ODC_ImpClass"

                        pc0_ODC_ImpClass :: pc0_ODC_ImpClass (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{



}


