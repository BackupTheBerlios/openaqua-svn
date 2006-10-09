/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    OPAGlobals

\brief    


\date     $Date: 2006/03/12 19:13:42,28 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPAGlobals_HPP
#define   OPAGlobals_HPP

class     OPAGlobals;

#ifndef   DLL_RootBaseEntry_HPP
#define   DLL_RootBaseEntry_HPP
#include  <sRootBaseEntry.hpp>
#include  <sDLL.h>
#endif
class     RessourceLock;
class     eb_RootBase;
#pragma pack(8)

class  OPAGlobals
{
protected  :         DLL(RootBaseEntry)                          *rootbase_list;                                             
protected  :         RessourceLock                               *reslock;                                                   
protected  :         int32                                       *active_transactions;                                       
protected  :         logical                                      paused;                                                    

public     :
                     RessourceLock                               *get_reslock() { return(reslock); }
                     int32                                       *get_active_transactions() { return(active_transactions); }
                     logical                                      get_paused() { return(paused); }
public     :                                     logical ILockGlobal ( );
public     :                                     logical IUnlockGlobal ( );
public     :                                                             OPAGlobals ( );
public     :                                     db_RootBase *ProvideRootBase (char *database_id, char *cpath );
public     :                                     void RegisterRootBase (db_RootBase *rootbase, char *database_id, char *cpath );
public     :                                     logical RegisterTA ( );
public     :                                     logical RootBaseShared ( );
public     :                                     void ShareRootBase ( );
public     :                                     logical StartPause (int32 wait_sec=300 );
public     :                                     void StopPause ( );
public     :                                     void UnregisterRootBase (db_RootBase *rootbase );
public     :                                     void UnregisterTA ( );
public     :                                                             ~OPAGlobals ( );
};

#pragma pack()
#endif
