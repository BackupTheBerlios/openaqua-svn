/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBField_DATETIME

\brief    


\date     $Date: 2006/03/12 19:12:54,73 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBField_DATETIME_HPP
#define   DBField_DATETIME_HPP

class     DBField_DATETIME;

#include  <sdbf.hpp>
#pragma pack(8)

class  DBField_DATETIME :public dbf
{

public     :
public     :         opa7ImpExp                  logical Add (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Substract (dbf *operand1, dbf *operand2 );
};

#pragma pack()
#endif
