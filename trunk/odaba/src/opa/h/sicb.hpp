/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    icb

\brief    


\date     $Date: 2006/03/12 19:14:24,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   icb_HPP
#define   icb_HPP

class     icb;

class     DBHandle;
class     DBIndex;
class     LACObject;
class     exd;
class     icbe;
class     mven;
class     mvlp;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <sRessourceLock.hpp>
#include  <srefs.hpp>
#pragma pack(8)

class  icb :public refs
{
protected  :         icbe                                        *icbicbe ATTR_ALIGN(4);                                     
protected  :         mvlp                                        *icbmvlp;                                                   
protected  :         mven                                        *icbmven;                                                   
protected  :         mven                                        *icbfst;                                                    
protected  :         mven                                        *icbsec;                                                    
protected  :         int16                                        index_lev;                                                 
protected  :         RessourceLock                                res_lock;                                                  

public     :
                     int16                                        get_index_lev() { return(index_lev); }
public     : virtual                             int32 AddExt (EB_Number ebsnum, char *skey, int32 lindx0 );
public     : virtual                             logical CheckIndex (NString &nresult, logical repair );
public     :                                     logical CheckVersion6 ( );
public     : virtual                             logical CheckWProtect ( );
public     : virtual                             logical DelExt (int32 lindx0 );
public     : virtual                             int32 GetCount ( );
public     : virtual                             EB_Number GetID (int32 lindx0 );
public     : virtual                             int32 GetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                             char *GetKey (int32 lindx0, char *keyptr );
public     : virtual                             int16 GetModCount ( );
public     :                                     logical ILock ( );
public     :                                     logical IUnlock ( );
public     :                                     logical InitICB ( );
public     : virtual                             exd *ProvideEXD ( );
public     :                                     logical ReadICBE ( );
public     : virtual                             logical ReadIndexEntry (int32 lindx0, void *instptr );
public     :                                     logical Recover ( );
public     : virtual                             logical Refresh ( );
public     : virtual                             logical Repair ( );
public     : virtual                             logical Reset ( );
public     : virtual                             logical Save ( );
public     :                                     EB_Number WriteICBE (EB_Number ebsnum );
public     : virtual                             logical WriteIndexEntry (int32 lindx0, void *instptr );
public     :                                                             icb (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, DBIndex *akcbptr, logical globind );
public     :                                     logical icbini ( );
public     :                                     logical icbrefr ( );
public     :                                     logical icbres ( );
public     : virtual                                                     ~icb ( );
};

#pragma pack()
#endif
