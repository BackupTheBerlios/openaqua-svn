/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBField_TIME

\brief    


\date     $Date: 2006/03/12 19:17:02,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBField_TIME"

#include  <popa7.h>
#include  <sdbf.hpp>
#include  <sDBField_TIME.hpp>


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

logical DBField_TIME :: Add (dbf *operand1, dbf *operand2 )
{
  fld        intval(FIRST_INSTANCE);
  logical    term   = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_TIME));
 
  if ( AllocateArea() )                              SDBERR(95)
  intval = *operand2;                                SDBCERR
 
  SetNormalized(operand1->GetNormalized()+intval.GetNormalized());

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

logical DBField_TIME :: Divide (dbf *operand1, dbf *operand2 )
{
  fld        intval(FIRST_INSTANCE);
  logical    term   = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_TIME));
 
  if ( AllocateArea() )                              SDBERR(95)
  intval = *operand2;                                 SDBCERR
 
  SetNormalized(operand1->GetNormalized()/intval.GetNormalized());

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

logical DBField_TIME :: Multiply (dbf *operand1, dbf *operand2 )
{
  fld        intval(FIRST_INSTANCE);
  logical    term   = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_TIME));
 
  if ( AllocateArea() )                              SDBERR(95)
  intval = *operand2;                                SDBCERR
 
  SetNormalized(operand1->GetNormalized()*intval.GetNormalized());

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
\param  operand2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Substract"

logical DBField_TIME :: Substract (dbf *operand1, dbf *operand2 )
{
  dbf        intval(FIRST_INSTANCE);
  logical    term   = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_TIME));
 
  if ( AllocateArea() )                              SDBERR(95)
  intval = *operand2;                                 SDBCERR
 
  SetNormalized(operand1->GetNormalized()-intval.GetNormalized());

  if ( GetNormalized() < 0 )
    SetNormalized(0);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


