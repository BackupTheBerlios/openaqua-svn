/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    exd



\date     $Date: 2006/05/01 16:02:08,20 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   exd_HPP
#define   exd_HPP

class     exd;

class     ACObject;
class     CSA_Handle;
class     CSHandleList;
class     DBHandle;
class     LACObject;
class     PCSHandle;
class     exdBBuffer;
class     exdBuffer;
#include  <sEB_Number.hpp>
#include  <sacb.hpp>
#include  <sexd.hpp>
#include  <sieh.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  exd :public sts
{
protected  :         LACObject                                   *ob_handle;                                                 
protected  :         int32                                        use_count;                                                 
protected  :         exd                                         *prev_exd;                                                  
protected  :         int32                                        ta_count;                                                  
protected  :         int32                                        read_ta;                                                   
protected  :         uint16                                       mod_count;                                                 
protected  :         int16                                        inst_sid;                                                  
protected  :         int32                                        entry_size;                                                
protected  :         int32                                        write_start;                                               
protected  :         int32                                        write_end;                                                 
protected  :         exdBuffer                                   *exd_buffer;                                                
protected  :         exd                                         *top_exd;                                                   
protected  :         uint8                                        schema_version;                                            
protected  :         logical                                      shadow_base;                                               
protected  :         logical                                      write_shadow;                                              
protected  :         exd                                         *pif_exd;                                                   
protected  :         RessourceLock                                res_lock;                                                  
public     :         EB_Number                                    exd_ebsnum;                                                
protected  :         acb                                         *exdacb;                                                    

public     :
                     LACObject                                   *get_ob_handle() { return(ob_handle); }
                     int32                                        get_use_count() { return(use_count); }
                     exd                                         *get_prev_exd() { return(prev_exd); }
                     int32                                        get_ta_count() { return(ta_count); }
                     int32                                        get_read_ta() { return(read_ta); }
                     uint16                                       get_mod_count() { return(mod_count); }
                     int16                                        get_inst_sid() { return(inst_sid); }
                     int32                                        get_entry_size() { return(entry_size); }
                     int32                                        get_write_start() { return(write_start); }
                     int32                                        get_write_end() { return(write_end); }
                     exdBuffer                                   *get_exd_buffer() { return(exd_buffer); }
                     exd                                         *get_top_exd() { return(top_exd); }
                     uint8                                        get_schema_version() { return(schema_version); }
                     logical                                      get_shadow_base() { return(shadow_base); }
                     logical                                      get_write_shadow() { return(write_shadow); }
                     exd                                         *get_pif_exd() { return(pif_exd); }
                     RessourceLock                               &get_res_lock() { return(res_lock); }
                     acb                                         *get_exdacb() { return(exdacb); }
public     :                                        void Cancel ( );
public     :                                        int32 ChangeSize (int32 longlen );
public     :                                        int32 ChangeSize ( );
public     :                                        uint8 CheckWProtect ( );
public     :                                        void CopySettings (exd *srceexd );
public     :                                        void CopyTo (exd *srceexd );
public     :                                        logical Delete (logical unlock );
public     :                                        logical FlushCluster ( );
public     :                                        int32 GetDBLength ( );
public     :                                        ieh *GetIEH ( );
public     :                                        logical ILock (logical wait, char *mod_id );
public     :                                        logical IUnlock (char *mod_id );
public     :                                        void InitEXD (EB_Number ebsnum, EB_Number clnumb, logical loc_exact, logical shadow_read=NO, logical shadow_write=NO );
public     :                                        logical Initialize (uint16 version_nr=CUR_VERSION );
public     :                                        logical IsInWork ( );
public     :                                        logical IsInstance ( );
public     :                                        int8 IsModified ( );
public     :                                        logical IsTALocked ( );
public     :                                        exd *LocateVersion (uint16 version_nr=CUR_VERSION );
public     :                                        logical Lock ( );
public     :                                        logical LockInternal (logical wait );
public     :                                        void LockUntilReserveInstance ( );
public     :                                        logical NewEntry ( );
public     :                                        exd *ProvidePIF ( );
public     :                                        logical Read (int32 w_instlen=AUTO, logical skip_ta=NO );
public     :                                        void ReleaseInstance (PCSHandle *pcs_handle );
public     :                                        void ReleasePIF ( );
public     :                                        void ReleaseTop ( );
public     :                                        logical Reserve (logical wait );
public     :                                        void ReserveInstance (PCSHandle *pcs_handle );
public     :                                        logical ReserveTop ( );
public     :                                        logical Reset ( );
public     :                                        void ResetACB (int32 tanumber );
public     :                                        logical ResetEBI ( );
public     :                                        logical ResetWProtect ( );
public     :                                        void ResetWriteLen ( );
public     :                                        void SetIEH (int32 instlen, int16 sid, char otyp, uint16 version );
public     :                                        logical SetInWork (logical workopt );
public     :                                        void SetLength (int32 longlen );
public     :                                        void SetPIF (logical pif );
public     :                                        void SetTopEXD (exd *exdarea );
public     :                                        logical SetWProtect ( );
public     :                                        logical Setup ( );
public     :                                        logical TraceUSE (logical reserve );
public     :                                        logical TraceWPT (logical reset_wpt );
public     :                                        logical Unlock ( );
public     :                                        logical UnlockInternal ( );
public     :                                        void UpdateFromPIF ( );
public     :                                        exd *UpdatePIF ( );
public     :                                        exd *VerifyVersion (uint16 version_nr=CUR_VERSION );
public     :                                        logical Write (int32 l_size, uint16 sbnumber );
public     :                                        logical Write (int32 l_size, int32 offset );
public     :                                             exd (LACObject *lobhandle, exdBuffer *exdbuf, int32 instlen, uint16 version_nr=CUR_VERSION );
public     :                                             exd (LACObject *lobhandle, acb *acbptr );
public     :                                             exd (exd &exdref );
public     :                                        uint16 get_version ( );
public     :                                        void oRegActHandles (CSHandleList *lcs_handle );
public     :                                        void oUnregActHandles (CSHandleList *lcs_handle );
public     :                                        void set_exdacb (acb *acbptr );
public     :                                        void set_exdebsn (EB_Number ebsnum );
public     :                                        exd *set_prev_exd (exd *exdptr );
public     :                                        void set_schema_ver (uint16 version );
public     :                                        void set_write (logical bwrite_opt );
public     :                                        void set_write_length (int32 longlen, int32 offset );
public     :                                             ~exd ( );
public     :                                        char *GetInstance ( ){
  return ( exdacb->GetInstance() );
}

public     :                                        int32 GetLength ( ){
  return ( this ? exdacb->get_acbieh().get_iehlen() : AUTO );
}

public     :                                        logical IsPIF ( ){

  return(exdacb->IsPIF());

}

public     :                                        void ResetPIF ( ){

  exdacb->ResetPIF();


}

public     :                                        void SetPIF ( ){

  exdacb->SetPIF();

}

public     :                                        EB_Number get_exdcln ( ){
  return(exdacb->get_cluster_number());
}

public     :                                        EB_Number get_exdebsn ( ){
  return(exdacb->get_ebsnum());
}

public     :                                        uint16 get_reqversion ( ){

  return(exdacb->get_version_number());

}

public     :                                        uint8 get_schemaver ( ){

  return ( this ? exdacb->get_acbieh().get_iehver() : AUTO );

}

public     :                                        void inc_mod_count ( ){
  mod_count++;
}

public     :                                        void set_exd_ebsnum (EB_Number entnr ){

  exd_ebsnum = entnr;

}

public     :                                        void set_exdcln (EB_Number clnumb ){
  exdacb->set_cluster_numb(clnumb);
}

public     :                                        void set_ob_handle (LACObject *lobhandle ){
  ob_handle = lobhandle;
}

public     :                                        void set_read_ta (int32 tanumber ){
  read_ta = tanumber;
}

public     :                                        void set_shadow_base (logical sdw_opt ){

  shadow_base = sdw_opt;

}

public     :                                        void set_ta_count (int32 tanumber ){
  ta_count = tanumber;
}

public     :                                        void set_use_count (int16 usecount ){
  use_count = usecount;
}

public     :                                        void set_write_shadow (logical sw_option ){

  write_shadow = sw_option;

}

};

#pragma pack()
#endif
