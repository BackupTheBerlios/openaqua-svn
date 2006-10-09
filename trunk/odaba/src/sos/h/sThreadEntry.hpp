/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ThreadEntry

\brief    


\date     $Date: 2006/03/12 19:20:18,95 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ThreadEntry_HPP
#define   ThreadEntry_HPP

class     ThreadEntry;

#ifndef   GSRT_ThreadEntry_HPP
#define   GSRT_ThreadEntry_HPP
#include  <sThreadEntry.hpp>
#include  <sGSRT.h>
#endif
class     ProcessVariables;
class     ThreadEntry;
#include  <sProcessInfo.hpp>
#pragma pack(8)

class  ThreadEntry
{
public     :         thread_t                                     thread_id;                                                 
protected  :         ProcessInfo                                 *process_info;                                              
protected  :         int32                                        use_count;                                                 
protected  :         logical                                      deleting;                                                  
protected  :         DLL(RessourceLock)                          *ilock_list;                                                

public     :
                     ProcessInfo                                 *get_process_info() { return(process_info); }
                     int32                                        get_use_count() { return(use_count); }
                     logical                                      get_deleting() { return(deleting); }
                     DLL(RessourceLock)                          *get_ilock_list() { return(ilock_list); }
public     : static  SOS7ImpExp                  ProcessInfo *__cdecl CreateCurProcInfo (ProcessVariables *proc_variables );
public     : static  SOS7ImpExp                  void __cdecl CreateEntry ( );
public     : static                              logical __cdecl DeleteEntry ( );
public     : static  SOS7ImpExp                  int16 __cdecl GetCount ( );
public     : static  SOS7ImpExp                  ProcessInfo *__cdecl GetCurProcInfo (ProcVariableTypes proc_vt=PVT_undefined );
public     : static  SOS7ImpExp                  DLL(RessourceLock) *__cdecl GetLockList (ProcVariableTypes proc_vt=PVT_undefined );
public     : static  SOS7ImpExp                  int32 __cdecl GetProcessUseCount ( );
public     : static  SOS7ImpExp                  thread_t __cdecl GetThreadID ( );
public     : static                              void __cdecl Initialize ( );
public     :                                     logical IsDeleting ( );
public     : static                              ThreadEntry *__cdecl LocateEntry ( );
public     : static                              logical __cdecl Lock ( );
public     :         SOS7ImpExp                  void RegisterLock (RessourceLock *res_lock );
public     : static  SOS7ImpExp                  void __cdecl ReleaseLocks ( );
public     : static                              logical __cdecl RemoveEntry ( );
public     : static  SOS7ImpExp                  logical __cdecl SetCurProcInfo (ProcessInfo *procinfo );
public     :                                                             ThreadEntry ( );
public     : static                              void __cdecl Uninitialize (ProcessInfo *proc_info, DLL(RessourceLock) *locklist );
public     : static                              logical __cdecl Unlock ( );
public     :         SOS7ImpExp                  void UnregisterLock (RessourceLock *res_lock );
public     :                                     DLL(RessourceLock) *reset_ilock_list ( );
public     :                                     ProcessInfo *reset_process_info ( );
public     :                                     void set_use_count (int16 count );
public     :                                                             ~ThreadEntry ( );
};

#pragma pack()
#endif
