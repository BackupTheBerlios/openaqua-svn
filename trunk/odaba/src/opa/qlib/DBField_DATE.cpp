/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBField_DATE

\brief    


\date     $Date: 2006/03/12 19:17:02,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBField_DATE"

#include  <popa7.h>
#include  <sdbf.hpp>
#include  <sDBField_DATE.hpp>


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

logical DBField_DATE :: Add (dbf *operand1, dbf *operand2 )
{
  fld        intval(FIRST_INSTANCE);
  logical    term   = NO;
BEGINSEQ
  SetFMCB(DBFieldDef::GetStaticFieldDef(T_DATE));
 
  if ( AllocateArea() )                              SDBERR(95)
  intval = *operand2;                                 SDBCERR
 
  SetNormalized(operand1->GetNormalized()+intval.GetNormalized());

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

logical DBField_DATE :: Substract (dbf *operand1, dbf *operand2 )
{
  logical    resi   = operand2->GetFMCB()->fmcbityp == T_DATE;
  dbf        intval(FIRST_INSTANCE);
  logical    term = NO;
BEGINSEQ
  if ( resi )
    SetFMCB(DBFieldDef::GetStaticFieldDef(T_INT));
  else
    SetFMCB(DBFieldDef::GetStaticFieldDef(T_DATE));
 
  if ( AllocateArea() )                              SDBERR(95)
  intval = *operand2;                                SDBCERR
 
  SetNormalized(operand1->GetNormalized()-intval.GetNormalized());
 
 if ( !resi && GetNormalized() < 0 )
   SetNormalized(0);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


