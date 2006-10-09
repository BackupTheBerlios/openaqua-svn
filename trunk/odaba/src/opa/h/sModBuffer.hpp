/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ModBuffer

\brief    


\date     $Date: 2006/03/12 19:13:40,43 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ModBuffer_HPP
#define   ModBuffer_HPP

class     ModBuffer;

class     DBHandle;
class     LACObject;
class     exd;
#include  <sEB_Number.hpp>
#include  <sexdBuffer.hpp>
#pragma pack(8)

class  ModBuffer :public exdBuffer
{

public     :
public     :                                     logical AddEntry (exd *exdarea );
public     :                                     logical Clear (logical marksave=NO );
public     :                                                             ModBuffer (LACObject *lobhandle );
public     :                                     logical Reset ( );
public     :                                                             ~ModBuffer ( );
};

#pragma pack()
#endif
