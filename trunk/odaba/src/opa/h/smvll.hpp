/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvll

\brief    


\date     $Date: 2006/03/12 19:14:37,17 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   mvll_HPP
#define   mvll_HPP

class     mvll;

class     DBHandle;
class     DBIndex;
class     LACObject;
class     exd;
class     mven;
class     mvlp;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <smvlx.hpp>
#pragma pack(8)

class  mvll :public mvlx
{
protected  :         int16                                        mvlllev ATTR_ALIGN(4);                                     

public     :
public     : virtual                             int32 AddExt (EB_Number ebsnum, char *skey, int32 lindx0 );
public     : virtual                             logical DelExt (int32 lindx0 );
public     : virtual                             int32 GetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                             char *GetKey (int32 lindx0, char *keyptr );
public     : virtual                             logical Refresh ( );
public     :                                     logical Repair ( );
public     :                                                             mvll (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, int16 level, logical globind );
public     :                                                             mvll (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, mvlp *mvlpptr, int16 level, logical globind );
public     :                                     logical mvllap (mven *mvennew, EB_Number ebsnum, char *skey );
public     : static                              mvlp *__cdecl mvllcrt (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, int16 level, logical globind, uint16 version_nr=CUR_VERSION );
public     :                                     logical mvllead (mven *mvennew );
public     :                                     logical mvllprv (char *skey, mven *mvennew );
public     : virtual                                                     ~mvll ( );
};

#pragma pack()
#endif
