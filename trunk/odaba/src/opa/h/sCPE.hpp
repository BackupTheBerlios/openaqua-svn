/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CPE

\brief    


\date     $Date: 2006/03/12 19:12:32,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CPE_HPP
#define   CPE_HPP

class     CPE;

class     acb;
class     cte;
class     ctr;
class     eb_Buffer;
class     eb_MainBase;
#include  <sEBI.hpp>
#include  <sEB_Number.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  CPE :public sts
{
public     :         EB_Number                                    cpeebsn ATTR_ALIGN(4);                                     
protected  :         EBI                                          cpeebsi;                                                   
protected  :         eb_Buffer                                   *cpeobuf;                                                   
protected  :         int16                                        cpeucnt;                                                   
protected  :         logical                                      cpemod;                                                    
protected  :         eb_MainBase                                 *ebsptr;                                                    
protected  :         acb                                         *ctracb;                                                    

public     :
                     EBI                                         &get_cpeebsi() { return(cpeebsi); }
                     int16                                        get_cpeucnt() { return(cpeucnt); }
                     acb                                         *get_ctracb() { return(ctracb); }
public     :                                                             CPE (eb_MainBase *mbhandle, EB_Number entnr );
public     :                                     logical Initialize ( );
public     :                                     logical Lock ( );
public     :                                     logical Refresh ( );
public     :                                     logical Unlock ( );
public     :                                     logical cpeadd (acb *acbptr );
public     :                                     logical cpedel (acb *acbptr );
public     :                                     int32 cpeget (acb *acbptr, int32 entlen );
public     :                                     logical cpeinit ( );
public     :                                     logical cpelcki ( );
public     :                                     int32 cpeleng (acb *acbptr );
public     :                                     logical cperead ( );
public     :                                     void cpermv ( );
public     :                                     logical cpeunli ( );
public     :                                     logical cpeupd (acb *acbptr, int32 length, int32 offset );
public     :                                     logical cpewrit ( );
public     :                                                             ~CPE ( );
public     :                                     int16 cpeucntd ( ){

 return (--cpeucnt);

}

public     :                                     void cpeucnti ( ){

  ++cpeucnt;

}

public     :                                     EB_Number get_cpeebsn ( ){

  return(cpeebsn);

}

};

#pragma pack()
#endif
