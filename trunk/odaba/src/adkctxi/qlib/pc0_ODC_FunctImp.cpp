/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    pc0_ODC_FunctImp



\date     $Date: 2006/03/12 19:35:46,14 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_ODC_FunctImp"

#include  <padkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_ODC_FunctImp.hpp>


/******************************************************************************/
/**
\brief  IsIFImplement - 


\return cond -

\param  if_imp_praefix -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIFImplement"

logical pc0_ODC_FunctImp :: IsIFImplement (char *if_imp_praefix )
{

  return ( !memcmp(GetString("id8"),if_imp_praefix,strlen(if_imp_praefix)) );

}

/******************************************************************************/
/**
\brief  pc0_ODC_FunctImp - 



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_ODC_FunctImp"

                        pc0_ODC_FunctImp :: pc0_ODC_FunctImp (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{



}


