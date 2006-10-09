/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    EBI



\date     $Date: 2006/05/04 19:21:30,85 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EBI_HPP
#define   EBI_HPP

class     EBI;

#define  S_EBI                                     sizeof(EBI)
class     EBI;
class     EBIo;
class     db_RootBase;
class     eb_SubBase;
#include  <sEB_Number.hpp>
#pragma pack(1)

class  EBI :public bsts
{
protected  :         uint16                                       mod_count;                                                 
protected  :         int32                                        entry_length;                                              
protected  :         int64                                        da_position;                                               
protected  :         int64                                        version_list;                                              
protected  :         uint16                                       version;                                                   
protected  :         uint16                                       access_rights;                                             
protected  :         int16                                        da_number;                                                 
protected  :         uint16                                       sb_number;                                                 

public     :
                     uint16                                       get_mod_count() { return(mod_count); }
                     int32                                        get_entry_length() { return(entry_length); }
                     int64                                        get_da_position() { return(da_position); }
                     int64                                        get_version_list() { return(version_list); }
                     uint16                                       get_version() { return(version); }
                     uint16                                       get_access_rights() { return(access_rights); }
                     int16                                        get_da_number() { return(da_number); }
                     uint16                                       get_sb_number() { return(sb_number); }
public     :                                        logical CheckError ( );
public     :                                        void Clear ( );
public     :                                        void ConvertTo3 (eb_SubBase *odbptr, EBIo *old_ebi, logical pif );
public     :                                        uint64 CreatePrevVersion (eb_SubBase *odbptr, uint16 version_nr=CUR_VERSION, logical pif_opt=NO );
public     :                                        logical CreateVersionEBI (eb_SubBase *odbptr, uint16 version_nr=CUR_VERSION, logical pif_opt=NO );
public     :                                        logical DeleteVersionEBI (eb_SubBase *odbptr );
public     :                                             EBI ( );
public     :                                        void FromPIF (logical pif );
public     :                                        int64 GetPosition ( );
public     :                                        logical GetPrevEBI (eb_SubBase *odbptr, uint16 version_nr=CUR_VERSION, logical pif_opt=NO );
public     :                                        logical GetPrevEBI (db_RootBase *rootbase, uint16 version_nr=CUR_VERSION, logical pif_opt=NO );
public     :                                        int16 GetStatus ( );
public     :                                        logical HasData ( );
public     :                                        logical NewEntry ( );
public     :                                        void ResetVersionList ( );
public     :                                        void ResetWProtect ( );
public     :                                        void SetDANumber (uint16 danumber );
public     :                                        void SetPosition (uint64 position64 );
public     :                                        void SetSBNumber (uint16 sbnumber );
public     :                                        void SetVersion (uint16 version_nr=CUR_VERSION );
public     :                                        void SetVersionList (uint64 position64 );
public     :                                        void SetWProtect ( );
public     :                                        void ToPIF (logical pif );
public     :                                        void UpdateModCount (int16 modcount );
public     :                                        logical GetWProtect ( ){

  return ( stscwpt(1)  ? YES : NO );


}

public     :                                        void IncModCount ( ){
 mod_count = (char)(((uint8)mod_count)+1);
 if ( !mod_count )
   mod_count = 1;
}

public     :                                        void SetEBILen (int32 odblen ){
 entry_length = odblen;
}

public     :                                        void SetModCount (int16 modcount ){
  mod_count = (char)modcount;
}

};

#pragma pack()
#endif
