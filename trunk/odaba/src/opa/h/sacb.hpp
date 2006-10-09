/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    acb

\brief    


\date     $Date: 2006/06/18 12:56:47,42 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   acb_HPP
#define   acb_HPP

class     acb;

#define  ACB                                       sizeof(acb)
#define  S_ACB                                     (ACB-IEH)
class     CSA_Handle;
class     PCSHandle;
class     eb_SubBase;
#include  <sCSHandleList.hpp>
#include  <sEBI.hpp>
#include  <sEB_Number.hpp>
#include  <sacb.hpp>
#include  <sieh.hpp>
#pragma pack(8)

class  acb :public EBI
{
protected  :         EB_Number                                    ebsnum;                                                    // 
protected  :         EB_Number                                    mb_ebsnum;                                                 // 
protected  :         int64                                        ebi_position;                                              // 
protected  :         EB_Number                                    cluster_number;                                            // 
protected  :         uint16                                       version_number;                                            // 
protected  :         int16                                        mb_number;                                                 // 
protected  :         CSHandleList                                 active_handles;                                            // 
protected  :         uint8                                        ws_level;                                                  // 
protected  :         logical                                      locate_exact;                                              // 
protected  :         int32                                        ws_number;                                                 // 
protected  :         logical                                      is_pif;                                                    // 
protected  :         uint64                                       reserved;                                                  // 
protected  :         char                                         reserve;                                                   // 
protected  :         ieh                                          acbieh;                                                    // 

public     :
                     EB_Number                                   &get_ebsnum() { return(ebsnum); }
                     EB_Number                                   &get_mb_ebsnum() { return(mb_ebsnum); }
                     EB_Number                                   &get_cluster_number() { return(cluster_number); }
                     uint16                                       get_version_number() { return(version_number); }
                     int16                                        get_mb_number() { return(mb_number); }
                     CSHandleList                                &get_active_handles() { return(active_handles); }
                     uint8                                        get_ws_level() { return(ws_level); }
                     logical                                      get_locate_exact() { return(locate_exact); }
                     int32                                        get_ws_number() { return(ws_number); }
                     uint64                                       get_reserved() { return(reserved); }
                     ieh                                         &get_acbieh() { return(acbieh); }
public     :                                        logical CheckVersion ( );
public     :                                        void CopyTo (acb *srceacb );
public     : static                                 acb *__cdecl Create (int32 longlen, uint16 version_nr=CUR_VERSION );
public     :                                        logical GenerateEvent (EntryEvent *ev_ptr );
public     :                                        logical ILock (logical wait );
public     :                                        logical IUnlock ( );
public     :                                        logical IsInstance ( );
public     :                                        void RegActHandles (PCSHandle *pcs_handle );
public     :                                        void Remove ( );
public     :                                        void ResetACB ( );
public     :                                        void SetIEH (int32 instlen, int16 sid, char otyp, uint16 version );
public     :                                        void SetLength (int32 instlen );
public     :                                        void Uninitialize ( );
public     :                                        void UnregActHandles (PCSHandle *pcs_handle );
public     :                                             acb (EB_Number entnr, EB_Number clnumb, uint16 version_nr=CUR_VERSION );
public     :                                             acb (EB_Number entnr, EB_Number clnumb, uint8 wslevel, int32 wsnumber, logical loc_exact, uint16 version_nr=CUR_VERSION );
public     :                                             acb (acb &acbref );
public     :                                        int64 get_ebi_position ( );
public     :                                        acb &operator= (const acb &acb_refc );
public     :                                        acb &operator= (acb *acbptr );
public     :                                        void set_ebi_position (int64 ebipos64 );
public     :                                        void set_ebsnum (EB_Number entnr );
public     :                                        void set_locate_exact (logical loc_exact );
public     :                                        uint8 set_reserved (logical is_reserved );
public     :                                        void set_version (uint16 version_nr=CUR_VERSION );
public     :                                        void set_ws_level (uint8 wslevel, int32 wsnumber_w=AUTO );
public     :                                             ~acb ( );
public     :                                        char *GetInstance ( ){

  return ( (char *)((&acbieh)+1) );

}

public     :                                        int32 GetLength ( ){

  return(acbieh.get_iehlen());

}

public     :                                        int16 GetSID ( ){

  return(acbieh.get_iehsid());

}

public     :                                        logical IsPIF ( ){


  return(is_pif);
}

public     :                                        void ResetPIF ( ){

  is_pif = NO;

}

public     :                                        void SetPIF ( ){

  is_pif = YES;

}

public     :                                        void set_cluster_numb (EB_Number clnumb ){

  cluster_number = clnumb;

}

public     :                                        void set_mb_ebsnum (EB_Number entnr ){

  mb_ebsnum = entnr;

}

public     :                                        void set_mb_number (int16 mbnumber ){

  mb_number = mbnumber;

}

public     :                                        void set_version_number (uint16 version_nr=CUR_VERSION ){

  version_number = version_nr;

}

};

#pragma pack()
#endif
