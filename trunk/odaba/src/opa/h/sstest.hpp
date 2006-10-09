/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    stest

\brief    


\date     $Date: 2006/03/12 19:15:11,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   stest_HPP
#define   stest_HPP

class     stest;

#include  <sCTX_Structure.hpp>
#pragma pack(8)

class  stest :public CTX_Structure
{

public     :
public     : virtual                             logical ExecuteFunction (char *fname );
public     :                                     logical Test1 ( );
public     :                                                             stest ( );
public     : virtual                                                     ~stest ( );
};

#pragma pack()
#endif
