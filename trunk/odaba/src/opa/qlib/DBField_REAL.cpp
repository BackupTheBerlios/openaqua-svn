/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBField_REAL

\brief    


\date     $Date: 2006/03/12 19:17:02,60 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBField_REAL"

#include  <popa7.h>
#include  <math.h>
#include  <sdbf.hpp>
#include  <sDBField_REAL.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term - Termination code

\param  operand1 -
\param  operand2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical DBField_REAL :: Add (dbf *operand1, dbf *operand2 )
{
  double     oper1;
  double     oper2;
  logical    term = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_REAL));
  if ( AllocateArea() )                              SDBERR(95)
  
  oper1 = operand1->GetDouble();                     SDBCERR
  oper2 = operand2->GetDouble();                     SDBCERR
  SetDouble(oper1+oper2);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Divide - 


\return term - Termination code

\param  operand1 -
\param  operand2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Divide"

logical DBField_REAL :: Divide (dbf *operand1, dbf *operand2 )
{
  double     oper1;
  double     oper2;
  logical    term = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_REAL));
  if ( AllocateArea() )                              SDBERR(95)
  
  oper1 = operand1->GetDouble();                     SDBCERR
  oper2 = operand2->GetDouble();                     SDBCERR
  SetDouble(oper1/oper2);

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

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

logical DBField_REAL :: Modulo (dbf *operand1, dbf *operand2 )
{
  double     oper1;
  double     oper2;
  logical    term = NO;
BEGINSEQ
  if ( InitResult(operand1,operand2) )               ERROR
   
  oper1 = operand1->GetDouble();                     SDBCERR
  oper2 = GetDouble();                               SDBCERR
 
  SetDouble(operand1->GetDouble()-oper2*(int32)(oper1/oper2));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Multiply - 


\return term - Termination code

\param  operand1 -
\param  operand2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Multiply"

logical DBField_REAL :: Multiply (dbf *operand1, dbf *operand2 )
{
  double     oper1;
  double     oper2;
  logical    term = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_REAL));
  if ( AllocateArea() )                              SDBERR(95)
  
  oper1 = operand1->GetDouble();                     SDBCERR
  oper2 = operand2->GetDouble();                     SDBCERR
  SetDouble(oper1*oper2);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Power - 


\return term - Termination code

\param  operand1 -
\param  operand2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Power"

logical DBField_REAL :: Power (dbf *operand1, dbf *operand2 )
{
  double     oper1;
  double     oper2;
  logical    term = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_REAL));
  if ( AllocateArea() )                              SDBERR(95)
  
  oper1 = operand1->GetDouble();                     SDBCERR
  oper2 = operand2->GetDouble();                     SDBCERR
  SetDouble(pow (oper1,oper2) );

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Substract - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief i0


\param  operand1 -
\param  operand2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Substract"

logical DBField_REAL :: Substract (dbf *operand1, dbf *operand2 )
{
  double     oper1;
  double     oper2;
  logical    term = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_REAL));
  if ( AllocateArea() )                              SDBERR(95)
  
  oper1 = operand1->GetDouble();                     SDBCERR
  oper2 = operand2->GetDouble();                     SDBCERR
  SetDouble(oper1-oper2);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i1


\param  operand1 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Substract"

logical DBField_REAL :: Substract (dbf *operand1 )
{
  double     oper1;
  logical    term = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_REAL));
  if ( AllocateArea() )                              SDBERR(95)
  
  oper1 = operand1->GetDouble();                     SDBCERR
  SetDouble(-oper1);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


