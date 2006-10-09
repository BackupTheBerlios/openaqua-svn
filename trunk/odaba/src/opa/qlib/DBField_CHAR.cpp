/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    DBField_CHAR

\brief    


\date     $Date: 2006/06/25 17:21:06,64 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DBField_CHAR"

#include  <popa7.h>
#include  <sdbf.hpp>
#include  <sDBField_CHAR.hpp>


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

logical DBField_CHAR :: Add (dbf *operand1, dbf *operand2 )
{
  char      *oper1 = NULL;
  char      *oper2 = NULL;
  char      *string;
  fmcb      *fmcbptr;
  fmcb      *fmcbptr1;
  int        maxsize;
  logical    term = NO;
BEGINSEQ
  if ( InitResult(operand1,operand2) )               ERROR
    
  fmcbptr = GetFMCB();    
  fmcbptr1 = operand1->GetFMCB();
  
  maxsize = fmcbptr1->fmcbbyte + fmcbptr->fmcbbyte+1;
  if ( !(oper1 = new char[maxsize]) ||
       !(oper2 = new char[fmcbptr->fmcbbyte+1]) )    SDBERR(95)
  memset(oper1,0,maxsize);
  memset(oper2,0,fmcbptr->fmcbbyte+1);
  
  if ( fmcbptr1->fmcbbyte != fmcbptr1->fmcbsize )  // 0-terminated
    strncpy(oper1,operand1->GetArea(),fmcbptr1->fmcbbyte);
  else
    gvtxbts(oper1,operand1->GetArea(),fmcbptr1->fmcbbyte);
  
  if ( fmcbptr->fmcbbyte != fmcbptr->fmcbsize )    // 0-terminated
    strncpy(oper2,GetArea(),fmcbptr->fmcbbyte);
  else
    gvtxbts(oper2,GetArea(),fmcbptr->fmcbbyte);
  gvtssin(oper1+strlen(oper1),oper2,maxsize-1-strlen(oper1));
  
  if ( strlen(oper1) > fmcbptr->fmcbbyte-1 )
  {
    if ( !fldfaloc )
      CopyDescription(GetDescription());  // Beschreibung lokalisieren
    
    fmcbptr->fmcbbyte = strlen(oper1)+1;
    fmcbptr->fmcbsize = GetFMCB()->fmcbbyte;
    if ( fmcbptr->fmcbityp == T_STRING )
      fmcbptr->fmcbsize--;
    SetArea(NULL);
    AllocateArea();
  }

  switch ( fmcbptr->fmcbityp )
  {
    case T_STRING : strcpy(GetArea(),oper1);
                    break;
    default       : gvtxstb(GetArea(),oper1,fmcbptr->fmcbbyte);
  }
RECOVER
  term = YES;
ENDSEQ
  delete oper1;
  delete oper2;
  return(term);
}

/******************************************************************************/
/**
\brief  Substract - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 


\param  operand1 - 
\param  operand2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Substract"

logical DBField_CHAR :: Substract (dbf *operand1, dbf *operand2 )
{
  char      *oper1 = NULL;
  char      *oper2 = NULL;
  logical    term = NO;
BEGINSEQ
  if ( InitResult(operand1,operand2) )               ERROR
    
  if ( !(oper1 = new char[operand1->GetFMCB()->fmcbbyte+1]) ||
       !(oper2 = new char[GetFMCB()->fmcbbyte+1])             )
                                                     SDBERR(95)

  gvtxbts(oper1,operand1->GetArea(),operand1->GetFMCB()->fmcbbyte);
  gvtxbts(oper2,GetArea(),GetFMCB()->fmcbbyte);
  gvtsexc(oper1,oper2,"",GetFMCB()->fmcbbyte);
  
  switch ( GetFMCB()->fmcbityp )
  {
    case T_STRING : strcpy(GetArea(),oper1);
                    break;
    default       : gvtxstb(GetArea(),oper1,GetFMCB()->fmcbbyte);
  }
RECOVER
  term = YES;
ENDSEQ
  delete oper1;
  delete oper2;
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  operand1 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Substract"

logical DBField_CHAR :: Substract (dbf *operand1 )
{
  logical                 term = NO;
BEGINSEQ
  if ( InitResult(operand1,operand1) )               ERROR
    
  gvtxbts(operand1->GetArea(),operand1->GetArea(),operand1->GetFMCB()->fmcbbyte);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


