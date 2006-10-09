/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    SystemDict

\brief    


\date     $Date: 2006/04/11 13:37:58,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SystemDict_HPP
#define   SystemDict_HPP

class     SystemDict;

#define  J                                         1
#define  N                                         0
#define  SYS_NSID                                  0
#define  Y                                         1
class     DBExtend;
#include  <cPIACC.h>
#include  <sDictionary.hpp>
#include  <sSDB_Reference.hpp>
#pragma pack(8)

class  SystemDict :public Dictionary
{

public     :
public     :                                     DBExtend *ProvideExtendDef (SDB_Reference sdbref, logical disjopt=NO, logical unionopt=NO, logical intersopt=NO, logical contr_opt=NO );
public     :                                     logical Start ( );
public     :                                     logical StartBegin ( );
public     :                                     logical StartCurrent ( );
public     :                                     logical StartCurrentX ( );
public     :                                     logical StartExtra ( );
public     :                                                             SystemDict (char *cpath, PIACC accopt, logical w_netopt=NO, char sysenv=NO );
public     :                                                             ~SystemDict ( );
};

#pragma pack()
#endif
