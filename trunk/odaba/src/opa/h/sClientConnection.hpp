/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ClientConnection

\brief    Client Connection


\date     $Date: 2006/03/12 19:12:45,32 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ClientConnection_HPP
#define   ClientConnection_HPP

class     ClientConnection;

#ifndef   DLL_CSInstanceList_HPP
#define   DLL_CSInstanceList_HPP
#include  <sCSInstanceList.hpp>
#include  <sDLL.h>
#endif
class     CS_Handle;
class     CS_Message;
class     IFClass;
class     Instance;
#include  <sCSInstance.hpp>
#include  <sCSInstanceList.hpp>
#include  <sCS_Client.hpp>
#pragma pack(8)

class  ClientConnection :public CS_Client
{
protected  :         logical                                      is_local ATTR_ALIGN(4);                                    // Indicates local resources
protected  :         IFClass                                     *function_table;                                            //
protected  :         CSInstanceList                               send_parms;                                                //
protected  :         CSInstanceList                               send_result;                                               //
protected  :         CSInstanceList                               rec_parms;                                                 //
protected  :         CSInstanceList                              *rec_result;                                                //
protected  :         logical                                      error_check;                                               //
protected  :         CSInstanceList                               save_result;                                               //
protected  :         uint32                                       connected;                                                 //
protected  :         DLL(CSInstanceList)                          msg_stack;                                                 //
protected  :         int32                                        last_class;                                                //
protected  :         int32                                        last_function;                                             //
protected  :         int32                                        last_answer;                                               //
protected  :         ObjectReference                             *client_reference;                                          //

public     :
                     logical                                      get_is_local() { return(is_local); }
                     IFClass                                     *get_function_table() { return(function_table); }
                     CSInstanceList                              &get_send_parms() { return(send_parms); }
                     CSInstanceList                              &get_send_result() { return(send_result); }
                     CSInstanceList                              &get_rec_parms() { return(rec_parms); }
                     CSInstanceList                              *get_rec_result() { return(rec_result); }
                     logical                                      get_error_check() { return(error_check); }
                     CSInstanceList                              &get_save_result() { return(save_result); }
                     uint32                                       get_connected() { return(connected); }
                     ObjectReference                             *get_client_reference() { return(client_reference); }
public     :                                     logical Check ( );
public     :                                                             ClientConnection ( );
public     :         opa7ImpExp                  void Disconnect ( );
public     : virtual opa7ImpExp                  logical DisplayMessage (uint32 msg_type, void *cso_ptr, CSInstanceList *csparms );
public     : virtual                             logical Execute (uint32 dwServiceClass, uint32 dwServiceFunc, CS_Message *cpParams, CS_Message *cpResult, logical *errptr );
public     :                                     logical GenerateEvent (uint32 dwServiceFunc, void *cso_ptr, CSInstanceList *csparms );
public     :                                     ODABAClient &GetClient ( );
public     :         opa7ImpExp                  logical IsConnected ( );
public     :                                     logical PopResult ( );
public     :                                     logical PushResult ( );
public     : virtual opa7ImpExp                  logical SendCSMessage (CS_Handle *handle, uint32 dwServiceClass, uint32 dwServiceFunc );
public     :                                     logical SetResult (void *datarea, int32 instlen );
public     : virtual                                                     ~ClientConnection ( );
};

#pragma pack()
#endif
