/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    cka

\brief    


\date     $Date: 2006/03/12 19:14:07,64 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cka_HPP
#define   cka_HPP

class     cka;

class     kfc;
#include  <scke.hpp>
#pragma pack(8)

class  cka :public cke
{

public     :
public     : virtual                             logical CloseCKE ( );
public     : virtual                             char *GetKey (char *keyptr, void *instptr, int16 indx );
public     : virtual                             int16 OpenCKE (void *instptr, logical refopt=NO );
public     :                                                             cka (kfc *kfcptr );
public     :                                                             ~cka ( );
};

#pragma pack()
#endif
