/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EntryHandle

\brief    


\date     $Date: 2006/03/12 19:13:20,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EntryHandle_HPP
#define   EntryHandle_HPP

class     EntryHandle;

class     LACObject;
class     LNode;
class     PCSHandle;
class     StructAccess;
class     exd;
#include  <sEB_Number.hpp>
#pragma pack(8)

class  EntryHandle
{
protected  :         LACObject                                   *ob_handle;                                                 
protected  :         StructAccess                                *struct_access;                                             
protected  :         exd                                         *exd_area;                                                  
protected  :         int16                                        mb_number;                                                 
protected  :         EB_Number                                    cluster_number;                                            
protected  :         uint16                                       mod_count;                                                 
protected  :         uint16                                       version;                                                   
protected  :         PCSHandle                                   *active_handle;                                             

public     :
                     LACObject                                   *get_ob_handle() { return(ob_handle); }
                     StructAccess                                *get_struct_access() { return(struct_access); }
                     exd                                         *get_exd_area() { return(exd_area); }
                     int16                                        get_mb_number() { return(mb_number); }
                     EB_Number                                   &get_cluster_number() { return(cluster_number); }
                     uint16                                       get_mod_count() { return(mod_count); }
                     uint16                                       get_version() { return(version); }
public     :                                     exd *CreateInstance (int32 instlen );
public     :                                                             EntryHandle (LACObject *lobhandle, int16 mbnumber, EB_Number clnumb, PCSHandle *pcs_handle );
public     :                                                             EntryHandle ( );
public     :                                     EB_Number GetExtInstID ( );
public     :                                     logical GetInstance (void *instptr, EB_Number entnr, int32 instlen, logical *p_update );
public     :                                     logical GetInstance (char *extinst );
public     :                                     uint16 GetVersion ( );
public     :                                     logical HasWorkspace ( );
public     :                                     logical PutInstance (void *instptr, int32 instlen, logical overwrite=NO, logical refresh_opt=NO );
public     :                                     logical ResetEntry ( );
public     :                                     logical SetInstance (exd *exdptr );
public     :                                     logical SetInstance (char *extinst );
public     :                                     void SetShadowRead ( );
public     :                                     void SetShadowWrite (logical shadow_write=NO );
public     : virtual                             void SetVersion (uint16 version_nr=CUR_VERSION );
public     :                                     void set_cluster_numb (EB_Number clnumb );
public     :                                     void set_exd_area (exd *exdptr );
public     :                                     void set_mb_number (int16 mbnumber );
public     :                                     void set_mod_count (int16 modcount );
public     :                                     void set_struct_acc (StructAccess *structacc );
public     :                                                             ~EntryHandle ( );
public     :                                     void set_version (uint16 version_nr=CUR_VERSION ){

  version = version_nr;

}

};

#pragma pack()
#endif
