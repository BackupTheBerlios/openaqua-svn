/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OResource



\date     $Date: 2006/04/27 13:41:56,21 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OResource_HPP
#define   OResource_HPP

class     OResource;

class     PropertyHandle;
#include  <sOPersistent.hpp>
#include  <sOResource.hpp>
#include  <sObjectInfo.hpp>
#pragma pack(4)

class  OResource :public OPersistent,
public ObjectInfo
{
protected  :         char                                         sys_ident[41];                                             
protected  :         char                                         contextClass[41];                                          
protected  :         int32                                        res_id;                                                    
protected  :         int32                                        use_count;                                                 
protected  :         int8                                         in_cache;                                                  
protected  :         int8                                         invalid;                                                   

public     :
                     char                                        *get_sys_ident() { return(sys_ident); }
                     char                                        *get_contextClass() { return(contextClass); }
                     int32                                        get_res_id() { return(res_id); }
                     int8                                         get_in_cache() { return(in_cache); }
                     int8                                         get_invalid() { return(invalid); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        logical Deleting ( );
public     :                                        void Invalidate ( );
public     :                                             OResource ( );
public     :                                             OResource (OPersistent bcOPersistent, char *ssys_ident, char *scontextClass, int32 ires_id, int32 iuse_count, int8 iin_cache, int8 iinvalid );
public     :                                        logical Read (PropertyHandle *ph );
public     :                                        void Release ( );
public     :                                        void Reserve ( );
public     : virtual                                void Reset ( );
public     :                                        OResource *Resource ( );
public     :                                        OResource &operator= (OResource &rOResource );
public     :                                        void set_in_cache (logical cache_opt );
public     :                                        void set_name (char *name );
public     :                                        void set_res_id (int resource_id=AUTO );
public     :                                             ~OResource ( );
};

#pragma pack()
#endif
