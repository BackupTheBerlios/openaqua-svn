/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    kfcl

\brief    


\date     $Date: 2006/03/12 19:20:52,04 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   kfcl_HPP
#define   kfcl_HPP

class     kfcl;

#ifndef   GSRT_kfc_HPP
#define   GSRT_kfc_HPP
#include  <skfc.hpp>
#include  <sGSRT.h>
#endif
class     smcb;
#include  <skfc.hpp>
#pragma pack(8)

class  kfcl :public GSRT(kfc)
{

public     :
public     :                                     void Deinitialize ( );
public     :                                     logical kfclesu (smcb *smcbptr, logical ignore=NO );
public     :                                     int kfclkcp (char *area1, char *area2, char cmptyp=UNDEF );
public     :                                     void kfclkgt (char *instptr, char *keyptr );
public     :                                     void kfclkpt (char *instptr, char *keyptr );
};

#pragma pack()
#endif
