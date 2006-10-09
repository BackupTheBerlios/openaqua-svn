/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CSHandleList

\brief    


\date     $Date: 2006/03/12 19:12:33,79 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CSHandleList_HPP
#define   CSHandleList_HPP

class     CSHandleList;

#include  <sDLL.h>
class     PCSHandle;
#ifndef   DLL_CSA_Handle_HPP
#define   DLL_CSA_Handle_HPP
#include  <sCSA_Handle.hpp>
#include  <sDLL.h>
#endif
class     CSA_Handle;
class     CS_Message;
class     EntryEvent;
class     PCSHandle;
class     acb;
#include  <sCSHandleList.hpp>
#include  <sRessourceLock.hpp>
#pragma pack(8)

class  CSHandleList
{
protected  :         DLL(PCSHandle)                              *conn_handle;                                               //
protected  :         RessourceLock                                res_lock;                                                  //

public     :
                     RessourceLock                               &get_res_lock() { return(res_lock); }
public     :                                     logical Add (PCSHandle *pcs_handle );
public     :                                                             CSHandleList ( );
public     :                                     logical Clear ( );
public     :                                     void Close ( );
public     :                                     logical Copy (const CSHandleList &hdl_list_refc );
public     :                                     logical GenerateEvent (EntryEvent *ev_ptr );
public     :                                     logical ILock (logical wait );
public     :                                     logical IUnlock ( );
public     :                                     void Initialize ( );
public     :                                     logical Move (CSHandleList &hdl_list_ref );
public     :                                     CSA_Handle *Remove (PCSHandle *pcs_handle );
public     :                                     void Uninitialize ( );
public     :                                     DLL(PCSHandle) *get_conn_handle ( ) const;
public     :                                     void set_conn_handle (DLL(PCSHandle) *pcs_handle_list );
public     :                                                             ~CSHandleList ( );
};

#pragma pack()
#endif
