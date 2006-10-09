/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBField_TIME

\brief    


\date     $Date: 2006/03/12 19:12:55,21 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBField_TIME_HPP
#define   DBField_TIME_HPP

class     DBField_TIME;

#include  <sdbf.hpp>
#pragma pack(8)

class  DBField_TIME :public dbf
{

public     :
public     :         opa7ImpExp                  logical Add (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Divide (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Multiply (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Substract (dbf *operand1, dbf *operand2 );
};

#pragma pack()
#endif
