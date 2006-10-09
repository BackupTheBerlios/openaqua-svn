/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBField_INT

\brief    


\date     $Date: 2006/03/12 19:17:02,50 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBField_INT"

#include  <popa7.h>
#include  <intmac.h>
#include  <sdbf.hpp>
#include  <sDBField_INT.hpp>


/******************************************************************************/
/**
\brief  Modulo - 


\return term - Termination code

\param  operand1 -
\param  operand2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modulo"

logical DBField_INT :: Modulo (dbf *operand1, dbf *operand2 )
{
  logical    term = NO;
BEGINSEQ
 if ( InitResult(operand1,operand2) )                ERROR
 SetNormalized(operand1->GetNormalized()%GetNormalized());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Substract - 


\return term - Termination code

\param  operand1 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Substract"

logical DBField_INT :: Substract (dbf *operand1 )
{
  logical                 term = NO;
BEGINSEQ
  if ( InitResult(operand1,operand1) )               ERROR
  SetNormalized(-operand1->GetNormalized());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}


