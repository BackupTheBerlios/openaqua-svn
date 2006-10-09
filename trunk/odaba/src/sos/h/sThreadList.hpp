/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ThreadList

\brief    


\date     $Date: 2006/03/12 19:20:20,40 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ThreadList_HPP
#define   ThreadList_HPP

class     ThreadList;

#ifndef   GSRT_ThreadEntry_HPP
#define   GSRT_ThreadEntry_HPP
#include  <sThreadEntry.hpp>
#include  <sGSRT.h>
#endif
class     RessourceLock;
class     ThreadEntry;
#pragma pack(8)

class  ThreadList :public GSRT(ThreadEntry)
{
protected  :         RessourceLock                               *res_lock ATTR_ALIGN(4);                                    
protected  :         int32                                        locked;                                                    

public     :
                     RessourceLock                               *get_res_lock() { return(res_lock); }
                     int32                                        get_locked() { return(locked); }
public     :                                     void Initialize ( );
public     :                                     logical IsInitialized ( );
public     :                                     logical IsLocked ( );
public     :                                     logical Lock ( );
public     : static  SOS7ImpExp                  void __cdecl Reset ( );
public     :                                                             ThreadList ( );
public     :                                     logical Unlock ( );
public     :                                                             ~ThreadList ( );
};

#pragma pack()
#endif
