/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    DBInfo



\date     $Date: 2006/05/09 12:22:45,56 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DBInfo_HPP
#define   DBInfo_HPP

class     DBInfo;

#define  LICENCE_MASK_LEN                          12
#define  MAXCHECKS                                 10
class     DBHandle;
#pragma pack(8)

class  DBInfo
{
protected  :         char                                         db_ident[10];                                              
protected  :         char                                         owner[128];                                                
protected  :         char                                         licence_number[12];                                        
protected  :         uint16                                       max_users;                                                 
protected  :         dbdt                                         expiration_date;                                           
protected  :         char                                         version_string[10];                                        // 
protected  :         uint16                                       version;                                                   // 
protected  :         uint16                                       sub_version;                                               // 
protected  :         logical                                      licenced;                                                  
protected  :         uint8                                        month_limit;                                               
protected  :         int32                                        check_count;                                               
protected  :         int32                                        db_number;                                                 

public     :
                     char                                        *get_db_ident() { return(db_ident); }
                     char                                        *get_owner() { return(owner); }
                     uint16                                       get_max_users() { return(max_users); }
                     dbdt                                         get_expiration_date() { return(expiration_date); }
                     uint16                                       get_version() { return(version); }
                     uint16                                       get_sub_version() { return(sub_version); }
                     logical                                      get_licenced() { return(licenced); }
                     uint8                                        get_month_limit() { return(month_limit); }
                     int32                                        get_db_number() { return(db_number); }
public     :                  OPAImpExp             logical CheckLicence (DBHandle *dbhandle, char *lic_owner, char *lic_number, char *applname_w=NULL );
public     :                  OPAImpExp                  DBInfo (DBHandle *dbhandle, char *applname_w=NULL );
public     :                  OPAImpExp                  DBInfo (PropertyHandle *piptr, char *applname_w=NULL );
public     :                                        char *GetDBIdent ( );
public     :                  OPAImpExp             char *GetLicenceMask (char *applname_w=NULL, char *licence_mask=NULL );
public     :                                        int16 GetMaxUsers ( );
public     :                                        char *GetVersionString ( );
public     :                                        logical Initialize (PropertyHandle *piptr, char *applname_w=NULL );
public     :                                        logical IsExpired ( );
public     :                  OPAImpExp             logical IsLicenced ( );
public     :                                        logical SetLicence (DBHandle *dbhandle, char *lic_owner );
public     :                  OPAImpExp                  ~DBInfo ( );
};

#pragma pack()
#endif
