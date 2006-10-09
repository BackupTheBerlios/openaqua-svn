/********************************* Class Declaration ***************************/
/**
\package  OPA
\class    SC_Handle



\date     $Date: 2006/05/09 15:20:23,81 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SC_Handle_HPP
#define   SC_Handle_HPP

class     SC_Handle;

#include  <sDLL.h>
class     SC_Handle;
class     CSInstanceList;
class     CS_Connection;
class     SC_Handle;
class     ServerConnection;
#include  <sCSA_Handle.hpp>
#include  <sCSHandle.hpp>
#pragma pack(8)

class  SC_Handle :public CSHandle
{
protected  :         ServerConnection                            *connection;                                                
protected  :         SC_Handle                                   *parent;                                                    
protected  :         uint32                                       calls;                                                     
protected  :         int64                                        start_time;                                                
protected  :         int64                                        total_time;                                                
protected  :         int64                                        perf_freq;                                                 
protected  :         DLL(SC_Handle)                              *sub_handles;                                               
protected  :         int32                                        current_index;                                             
public     :         uint32                                       all_calls;                                                 
public     :         int64                                        all_time;                                                  

public     :
                     ServerConnection                            *get_connection() { return(connection); }
                     SC_Handle                                   *get_parent() { return(parent); }
                     uint32                                       get_calls() { return(calls); }
                     int64                                        get_start_time() { return(start_time); }
                     int64                                        get_total_time() { return(total_time); }
                     int64                                        get_perf_freq() { return(perf_freq); }
                     DLL(SC_Handle)                              *get_sub_handles() { return(sub_handles); }
                     int32                                        get_current_index() { return(current_index); }
public     :                  OPAImpExp             void AddHandleToParentList (SC_Handle *parent_handle );
public     :                                        logical CheckHandle (uint32 dwServiceClass, uint32 dwServiceFunc );
public     :                                        logical FillResult (CSInstanceList *result );
public     : virtual                                logical FireEvent (CSA_Events event_id, char *parmstring );
public     : virtual                                char *GetName ( );
public     :                                        SC_Handle *GetSubHandle (int32 indx0 );
public     : virtual                                char *GetTypeName ( );
public     :                                        void InitHandle (ServerConnection *sconnection, int64 client_handle );
public     :                                        logical IsClosing (uint32 dwServiceClass, uint32 dwServiceFunc );
public     :                                        void MSG_Closed ( );
public     :                                        void MSG_Dirty ( );
public     :                                        void Remove (SC_Handle *sc_handle );
public     :                                        void Reparent (SC_Handle *sc_handle );
public     :                  OPAImpExp                  SC_Handle (CS_Connection *cs_connection, SC_Handle *parent_handle, int64 client_handle );
public     :                                        void SetParent (SC_Handle *sc_handle );
public     :                                        logical Start ( );
public     :                                        void Stop (uint32 dwServiceClass, uint32 dwServiceFunc );
public     :                                        void set_current_index (int32 index );
public     : virtual          OPAImpExp                  ~SC_Handle ( );
};

#pragma pack()
#endif
