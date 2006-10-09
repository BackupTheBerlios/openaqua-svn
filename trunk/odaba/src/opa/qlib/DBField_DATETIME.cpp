/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBField_DATETIME

\brief    


\date     $Date: 2006/03/12 19:17:02,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBField_DATETIME"

#include  <popa7.h>
#include  <sdbf.hpp>
#include  <sdttm.hpp>
#include  <sDBField_DATETIME.hpp>


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

logical DBField_DATETIME :: Add (dbf *operand1, dbf *operand2 )
{
  fld        intval(FIRST_INSTANCE);
  logical    term   = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_DATETIME));
  SetupDescription();
  if ( AllocateArea() )                              SDBERR(95)
 
  intval = *operand2;                                SDBCERR
 
  *(dbf *)this = *operand1;
  *(dttm *)flddata += intval.GetNormalized();

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

logical DBField_DATETIME :: Substract (dbf *operand1, dbf *operand2 )
{
  logical    resi   = operand2->GetFMCB()->fmcbityp == T_DATETIME;
  dbf        intval(FIRST_INSTANCE);
  logical    term = NO;
BEGINSEQ
  if ( resi )
    SetFMCB(DBFieldDef::GetStaticFieldDef(T_INT));
  else
    SetFMCB(DBFieldDef::GetStaticFieldDef(T_DATETIME));
  SetupDescription();
  if ( AllocateArea() )                              SDBERR(95)
 
  if ( !resi )
  {
    intval = *operand2;                                SDBCERR
    *(dbf *)this = *operand1;
    *(dttm *)flddata -= intval.GetNormalized();
  }
  else
    SetNormalized(*(dttm *)operand1->GetArea() - *(dttm *)operand2->GetArea());

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


