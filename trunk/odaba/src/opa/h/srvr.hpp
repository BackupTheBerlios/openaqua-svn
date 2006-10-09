/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    rvr

\brief    


\date     $Date: 2006/03/12 19:15:08,34 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   rvr_HPP
#define   rvr_HPP

class     rvr;

class     acb;
class     rvre;
class     rvrh;
#include  <sEB_Number.hpp>
#pragma pack(8)

class  rvr
{
protected  :         char                                         rvrpath[65];                                               
protected  :         logical                                      rvrnet;                                                    
protected  :         uint16                                       rvrnum;                                                    
protected  :         int16                                        rvrfile;                                                   
protected  :         char                                        *rvruser;                                                   
protected  :         int16                                        rvruil;                                                    
protected  :         char                                        *rvrwork;                                                   
protected  :         int32                                        rvrpos;                                                    
protected  :         logical                                      rvrout;                                                    
protected  :         logical                                      rvrapp;                                                    
protected  :         int32                                        rvrtastart;                                                
protected  :         char                                        *rvrwint;                                                   
protected  :         int32                                        rvriwlen;                                                  

public     :
                     uint16                                       get_rvrnum() { return(rvrnum); }
                     int16                                        get_rvrfile() { return(rvrfile); }
                     int32                                        get_rvrpos() { return(rvrpos); }
                     logical                                      get_rvrapp() { return(rvrapp); }
                     char                                        *get_rvrwint() { return(rvrwint); }
                     int32                                        get_rvriwlen() { return(rvriwlen); }
public     :                                     void Close ( );
public     :                                     logical DeleteFile ( );
public     :                                     int32 GetEntryLength ( );
public     :                                     int32 GetFixedLength ( );
public     :                                     logical GetNext ( );
public     :                                     acb *GetWorkInst ( );
public     :                                     logical IsOpened ( );
public     :                                     logical Lock ( );
public     :                                     logical Open (uint16 recnum=0 );
public     :                                     char *Read (char *extinst, int32 extlen, int32 offset );
public     :                                     logical StartTA ( );
public     :                                     int64 StopTA (logical error );
public     :                                     acb *TA_Next ( );
public     :                                     logical TA_Top (int32 position );
public     :                                     logical Unlock ( );
public     :                                     logical Write (acb *acbptr, int32 extlen, char opera, int32 offset );
public     :                                                             rvr (char *recpath, uint16 recnum=0, char *userinfo=NULL, int16 uilen=0, logical w_netopt=NO, logical w_outopt=YES, logical w_app=YES );
public     :                                     uint16 rvrcrt (char *recpath, uint16 recnum=0 );
public     :                                     logical rvrfncr (char *recpath );
public     : static                              char *__cdecl rvrfngt (char *filnames, uint16 recnum=0 );
public     :                                     logical rvrfopn (char *recpath );
public     :                                     logical rvrinit ( );
public     :                                     logical rvrrdh ( );
public     :                                     void rvrsup (char *userinfo=NULL, int16 uilen=0 );
protected  :                                     logical rvrwt (void *datarea, uint16 datlen );
public     :                                                             ~rvr ( );
};

#pragma pack()
#endif
