/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:21:31,04}|(REF)
\class    ClientObject

\brief    


\date     $Date: 2006/03/12 19:21:35,35 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ClientObject_HPP
#define   ClientObject_HPP

class     ClientObject;

class     DataSourceHandle;
#include  <sCSUtilityHandle.hpp>
#include  <svcls.hpp>
#pragma pack(8)

class  ClientObject :public vcls
{
protected  :         char                                        *extent ATTR_ALIGN(4);                                      
protected  :         int32                                        max_obj;                                                   
protected  :         int32                                        id;                                                        
protected  :         CSUtilityHandle                             *utility_handle;                                            
protected  :         int32                                       *client_count;                                              
protected  :         DataSourceHandle                            *ds_handle;                                                 

public     :
                     char                                        *get_extent() { return(extent); }
                     int32                                        get_max_obj() { return(max_obj); }
                     int32                                        get_id() { return(id); }
                     CSUtilityHandle                             *get_utility_handle() { return(utility_handle); }
                     int32                                       *get_client_count() { return(client_count); }
                     DataSourceHandle                            *get_ds_handle() { return(ds_handle); }
public     :                                                             ClientObject (CSUtilityHandle &uti_handle, char *extent_name, int32 max_objects, int32 client_num, int32 *client_cnt );
public     :                                     void Close ( );
public     :                                     logical Start ( );
public     :                                                             ~ClientObject ( );
};

#pragma pack()
#endif
