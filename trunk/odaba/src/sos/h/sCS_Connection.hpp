/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    CS_Connection

\brief    


\date     $Date: 2006/08/27 18:23:13,17 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CS_Connection_HPP
#define   CS_Connection_HPP

class     CS_Connection;
#include "csosdll.h"

#define  APL_MSG_ERROR                             3
#define  APL_MSG_INFO                              1
#define  APL_MSG_UNDEFINED                         0
#define  APL_MSG_WARNING                           2
#define  CS_CYCLE_TIME                             30
#define  CS_MSG_ALIVE                              3
#define  CS_MSG_BYE                                666
#define  CS_MSG_MESSAGE                            1
#define  CS_MSG_REQUEST                            2
class     CS_Handle;
class     CS_Message;
#include  <cMachineTypes.h>
#include  <sCS_Buffer.hpp>
#include  <sEvent.hpp>
#include  <sRessourceLock.hpp>
#include  <svcls.hpp>
#include  <swinsock.hpp>
#pragma pack(8)

class  CS_Connection :public vcls
{
public     :         int32                                        connect_id;                                                // 
protected  :         int16                                        pointer_size;                                              // 
protected  :         MachineTypes                                 machine_type;                                              // 
protected  :         logical                                      conversion;                                                // 
protected  :         logical                                      threadTerm;                                                // 
protected  :         logical                                      threadExec;                                                // 
protected  :         logical                                      shutting_down;                                             // 
protected  :         thread_t                                     threadExecID;                                              // 
protected  :         int64                                        perf_frq;                                                  // 
protected  :         int64                                        perf_total;                                                // 
protected  :         int64                                        perf_send;                                                 // 
protected  :         int64                                        perf_wait;                                                 // 
protected  :         int64                                        perf_build;                                                // 
protected  :         int64                                        perf_recv;                                                 // 
protected  :         int64                                        perf_exec;                                                 // 
protected  :         int64                                        perf_rwait;                                                // 
protected  :         logical                                      threadSpool;                                               // 
protected  :         thread_t                                     threadSpoolID;                                             // 
public     :         SOCKET                                       m_in_sock;                                                 // 
protected  :         RessourceLock                                m_in_sock_lock;                                            // 
protected  :         CS_Buffer                                    m_in_in;                                                   // 
protected  :         int64                                        m_in_in_pos;                                               // 
protected  :         CS_Buffer                                    m_in_out;                                                  // 
protected  :         int64                                        m_in_out_pos;                                              // 
protected  :         RessourceLock                                m_in_lock;                                                 // 
protected  :         logical                                      m_in_conn;                                                 // 
protected  :         CS_Buffer                                   *m_in_work;                                                 // 
protected  :         CS_Buffer                                    m_in_in_oob;                                               // 
protected  :         int64                                        m_in_in_oob_pos;                                           // 
public     :         SOCKET                                       m_out_sock;                                                // 
protected  :         RessourceLock                                m_out_sock_lock;                                           // 
protected  :         CS_Buffer                                    m_out_in;                                                  // 
protected  :         int64                                        m_out_in_pos;                                              // 
protected  :         CS_Buffer                                    m_out_out;                                                 // 
protected  :         int64                                        m_out_out_pos;                                             // 
protected  :         RessourceLock                                m_out_lock;                                                // 
protected  :         logical                                      m_out_conn;                                                // 
protected  :         CS_Buffer                                   *m_out_work;                                                // 
public     :         logical                                      closedbypeer;                                              // 
protected  :         logical                                      closing;                                                   // 
protected  :         size_t                                       compressThreshold;                                         // 
protected  :         int32                                        compressLevel;                                             // 
protected  :         logical                                      socketError;                                               // 
protected  :         RessourceLock                                m_send_lock;                                               // 
protected  :         logical                                      stopSockets;                                               // 

public     :
                     int16                                        get_pointer_size() { return(pointer_size); }
                     MachineTypes                                 get_machine_type() { return(machine_type); }
                     logical                                      get_conversion() { return(conversion); }
                     logical                                      get_shutting_down() { return(shutting_down); }
                     CS_Buffer                                   *get_m_in_work() { return(m_in_work); }
                     CS_Buffer                                   *get_m_out_work() { return(m_out_work); }
                     logical                                      get_closing() { return(closing); }
public     :                  SOSImpExp                  CS_Connection ( );
protected  : virtual          SOSImpExp             logical DoConnect ( );
protected  :                                        logical ExecThread ( );
public     : virtual          SOSImpExp             logical Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *pParams, CS_Message *pResult, logical *pError );
public     :                  SOSImpExp             logical Flush ( );
public     :                  SOSImpExp             char *GetConnectionName (char *server_name, int32 maxlen );
public     :                                        logical HandshakeC (SOCKET socket, SOCKET socket2 );
public     :                                        logical HandshakeS (SOCKET socket, SOCKET socket2 );
public     : virtual          SOSImpExp             logical InitConnection ( );
public     :                                        void Initialize ( );
public     :                  SOSImpExp             logical IsAlive ( );
public     :                  SOSImpExp             void LockExecute ( );
public     :                  SOSImpExp             void LockSend ( );
public     : virtual          SOSImpExp             logical OnExecTerm ( );
public     :                  SOSImpExp             logical Output (char *fstring, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL, char *parm6=NULL );
public     :                                        logical ReceiveCSMessage ( );
protected  :                                        logical SendCSBye ( );
public     : virtual          SOSImpExp             logical SendCSMessage (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *pParams, CS_Message *pResult );
public     :                  SOSImpExp             void SetCompress (size_t threshold, int level_AUTO=AUTO );
protected  :                                        logical SocketError ( );
protected  :                                        logical SpoolThread ( );
public     :                                        logical StartThreads ( );
public     :                                        logical StopThreads ( );
public     :                  SOSImpExp             void UnlockExecute ( );
public     :                  SOSImpExp             void UnlockSend ( );
protected  :                                        logical checkInInOOB ( );
protected  :                                        logical execute (int64 stopat_int64 );
protected  :                                        logical getInIn (logical fIn );
protected  :                                        logical getOutIn ( );
protected  :                                        void putInOut (CS_Buffer *pCS_Buffer );
protected  :                                        void putOutOut (CS_Buffer *pCS_Buffer );
protected  :                                        logical recvInIn (int32 timeout );
protected  :                                        logical recvOutIn (int32 timeout );
protected  :                                        logical sendCSAlive ( );
protected  :                                        logical sendInOut ( );
protected  :                                        logical sendOutOut ( );
public     :                                        void set_shutting_down (char shut_down_opt );
public     : static           SOSImpExp             logical __cdecl sock_recv (SOCKET sock, void *buf, size_t len, logical &rfStopSocket );
public     : static           SOSImpExp             logical __cdecl sock_select (SOCKET sock, int32 timeout, logical *pfError, logical fForWrite, logical &rfStopSocket );
public     : static           SOSImpExp             logical __cdecl sock_send (SOCKET sock, void *buf, size_t len, logical &rfStopSocket );
public     : static           SOSImpExp             logical __cdecl sock_waitfor (SOCKET sock, int32 timeout, logical *pfError, logical &rfStopSocket );
public     : virtual          SOSImpExp                  ~CS_Connection ( );
};

#pragma pack()
#endif
