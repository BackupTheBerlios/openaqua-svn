/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ckm

\brief    


\date     $Date: 2006/03/12 19:14:08,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ckm_HPP
#define   ckm_HPP

class     ckm;

class     ACReference;
class     kfc;
#include  <scke.hpp>
#pragma pack(8)

class  ckm :public cke
{
protected  :         ACReference                                 *ckmnode ATTR_ALIGN(4);                                     

public     :
public     : virtual                             logical CheckMod ( );
public     : virtual                             logical CloseCKE ( );
public     : virtual                             char *GetKey (char *keyptr, void *instptr, int16 indx );
public     : virtual                             int16 OpenCKE (void *instptr, logical refopt=NO );
public     :                                                             ckm (kfc *kfcptr );
public     :                                                             ~ckm ( );
};

#pragma pack()
#endif
