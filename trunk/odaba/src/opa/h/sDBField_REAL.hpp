/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBField_REAL

\brief    


\date     $Date: 2006/03/12 19:12:54,95 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBField_REAL_HPP
#define   DBField_REAL_HPP

class     DBField_REAL;

#include  <sdbf.hpp>
#pragma pack(8)

class  DBField_REAL :public dbf
{

public     :
public     :         opa7ImpExp                  logical Add (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Divide (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Modulo (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Multiply (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Power (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Substract (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Substract (dbf *operand1 );
};

#pragma pack()
#endif
