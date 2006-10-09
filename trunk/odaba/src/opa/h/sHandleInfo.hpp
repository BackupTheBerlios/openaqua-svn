/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    HandleInfo

\brief    


\date     $Date: 2006/03/12 19:13:23,82 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   HandleInfo_HPP
#define   HandleInfo_HPP

class     HandleInfo;

#include  <sGSRT.h>
class     HandleInfo;
class     CClient;
#include  <sCS_Handle.hpp>
#include  <sODABAClient.hpp>
#pragma pack(8)

class  HandleInfo
{
public     :         char                                         number[5];                                                 
public     :         char                                         name[129];                                                 
public     :         char                                         type[41];                                                  
public     :         uint32                                       calls;                                                     
public     :         uint32                                       calls_time;                                                
public     :         uint32                                       all_calls;                                                 
public     :         uint32                                       all_calls_time;                                            
public     :         logical                                      is_active;                                                 
public     :         int32                                        n_sub_handles;                                             
protected  :         int32                                        level;                                                     
public     :         CClient                                     *cclient;                                                   
public     :         CS_Handle                                    cs_handle;                                                 
public     :         GSRT(HandleInfo)                            *sub_handles;                                               

public     :
                     int32                                        get_level() { return(level); }
public     :         opa7ImpExp                  logical Build (PropertyHandle &ph );
public     :         opa7ImpExp                  logical BuildList (PropertyHandle &ph );
public     :                                     logical CreateSubHandleList ( );
public     :         opa7ImpExp                  logical Disconnect ( );
public     :                                     CS_Handle *GetClientHandle (int32 indx0 );
public     :         opa7ImpExp                                          HandleInfo (HandleInfo *parent_info, CS_Handle *ch );
public     :         opa7ImpExp                                          HandleInfo (ODABAClient &client, char *server_name, char *port_name );
public     :         opa7ImpExp                                          HandleInfo ( );
public     :         opa7ImpExp                  logical Kill ( );
public     :         opa7ImpExp                  logical Print (FILE *filehdl );
public     :         opa7ImpExp                  HandleInfo &operator= (HandleInfo &hi_ref );
public     :         opa7ImpExp                                          ~HandleInfo ( );
};

#pragma pack()
#endif
