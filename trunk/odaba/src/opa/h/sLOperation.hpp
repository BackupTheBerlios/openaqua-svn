/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    LOperation

\brief    


\date     $Date: 2006/03/12 19:13:39,92 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   LOperation_HPP
#define   LOperation_HPP

class     LOperation;

class     ACObject;
class     DBHandle;
class     Dictionary;
class     ParmList;
#include  <sDBObjectHandle.hpp>
#include  <sOperation.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  LOperation :public Operation
{

public     :
public     :                                                             LOperation (PropertyHandle &prophdl_ref );
public     : virtual                                                     ~LOperation ( );
};

#pragma pack()
#endif
