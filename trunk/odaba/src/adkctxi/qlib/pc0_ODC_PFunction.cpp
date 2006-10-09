/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    pc0_ODC_PFunction



\date     $Date: 2006/03/12 19:35:46,85 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc0_ODC_PFunction"

#include  <padkctxi.h>
#include  <sPropertyHandle.hpp>
#include  <spc0_ODC_FunctImp.hpp>
#include  <spc0_ODC_PFunction.hpp>


/******************************************************************************/
/**
\brief  IsIFFunction

\return cond -

\param  if_imp_praefix -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsIFFunction"

logical pc0_ODC_PFunction :: IsIFFunction (char *if_imp_praefix )
{
  long       indx0 = 0;
  logical    cond  = YES;
BEGINSEQ
  pc0_ODC_FunctImp   implementations(GPH("implementations"));
  
  while ( implementations(indx0++) )
    if ( implementations.IsIFImplement(if_imp_praefix) )
                                                     LEAVESEQ

  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  pc0_ODC_PFunction - 



\param  prophdl - Property handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc0_ODC_PFunction"

                        pc0_ODC_PFunction :: pc0_ODC_PFunction (PropertyHandle *prophdl )
                     : PropertyHandle (prophdl)
{



}


