/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DBField_CHAR

\brief    


\date     $Date: 2006/03/12 19:12:54,50 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBField_CHAR_HPP
#define   DBField_CHAR_HPP

class     DBField_CHAR;

#include  <sdbf.hpp>
#pragma pack(8)

class  DBField_CHAR :public dbf
{

public     :
public     :         opa7ImpExp                  logical Add (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Substract (dbf *operand1, dbf *operand2 );
public     :         opa7ImpExp                  logical Substract (dbf *operand1 );
};

#pragma pack()
#endif
