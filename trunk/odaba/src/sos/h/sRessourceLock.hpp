/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    RessourceLock

\brief    


\date     $Date: 2006/03/12 19:20:16,39 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   RessourceLock_HPP
#define   RessourceLock_HPP

class     RessourceLock;

#include  <sDLL.h>
class     RessourceLock;
#include  <sCRITICAL_SECTION.hpp>
#include  <svcls.hpp>
#pragma pack(8)

class  RessourceLock :public vcls
{
protected  :         CRITICAL_SECTION                             lock_object ATTR_ALIGN(4);                                 //
protected  :         DLL(RessourceLock)                          *thread_locks;                                              //

public     :
                     CRITICAL_SECTION                            &get_lock_object() { return(lock_object); }
                     DLL(RessourceLock)                          *get_thread_locks() { return(thread_locks); }
public     :         SOS7ImpExp                  void ActivateLockList ( );
public     :         SOS7ImpExp                  logical ActiveLockList ( );
public     :         SOS7ImpExp                  void DeactivateLockList ( );
public     :         SOS7ImpExp                  logical ILock (logical wait=YES );
public     :         SOS7ImpExp                  logical IUnlock ( );
public     :         SOS7ImpExp                  void Initialize ( );
public     :         SOS7ImpExp                  logical IsLocked (logical wait=YES );
public     :         SOS7ImpExp                                          RessourceLock (logical activate_llist );
public     :         SOS7ImpExp                  void Uninitialize ( );
public     :         SOS7ImpExp                                          ~RessourceLock ( );
};

#pragma pack()
#endif
