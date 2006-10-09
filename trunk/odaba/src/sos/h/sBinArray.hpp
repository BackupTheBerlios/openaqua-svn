/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    BinArray



\date     $Date: 2006/05/28 16:17:57,18 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BinArray_HPP
#define   BinArray_HPP

class     BinArray;
#include "csosdll.h"

#ifndef   DLL_BinArrayObjEntry_HPP
#define   DLL_BinArrayObjEntry_HPP
#include  <sBinArrayObjEntry.hpp>
#include  <sDLL.h>
#endif
class     BinArray;
class     BinArrayIdxEntry;
class     BinArrayObjEntry;
class     BinSArrayObjEntry;
#include  <sBinSArray.hpp>
#include  <sEntryPool.hpp>
#include  <sRessourceLock.hpp>
#pragma pack(8)

class  BinArray :public BinSArray
{
protected  :         int16                                        hight;                                                     
protected  :         DLL(BinArrayObjEntry)                        updated_entries;                                           
protected  :         uint32                                       last_used;                                                 
protected  :         uint32                                       unused_entries;                                            
protected  :         BinArrayObjEntry                            *first_free_entry;                                          
protected  :         BinArrayObjEntry                            *last_free_entry;                                           
protected  :         uint32                                       last_reorg;                                                

public     :
                     int16                                        get_hight() { return(hight); }
                     DLL(BinArrayObjEntry)                       &get_updated_entries() { return(updated_entries); }
                     uint32                                       get_last_used() { return(last_used); }
                     uint32                                       get_unused_entries() { return(unused_entries); }
                     BinArrayObjEntry                            *get_first_free_entry() { return(first_free_entry); }
                     BinArrayObjEntry                            *get_last_free_entry() { return(last_free_entry); }
                     uint32                                       get_last_reorg() { return(last_reorg); }
public     :                  SOSImpExp                  BinArray (uint16 size, uint16 blockcount, int32 level_num, logical autoreorg=YES );
public     :                  SOSImpExp                  BinArray ( );
public     :                  SOSImpExp             void Clear ( );
public     :                  SOSImpExp             logical Flush ( );
public     :                  SOSImpExp             BinArrayObjEntry *FreeEntry (uint64 entry_index );
public     : virtual          SOSImpExp             void FreeObjEntry (BinSArrayObjEntry *obj_entry );
public     :                  SOSImpExp             BinArrayObjEntry *GetNext ( );
public     :                  SOSImpExp             void GoTop ( );
public     : virtual          SOSImpExp             void InitObjEntry (BinSArrayObjEntry *obj_entry, uint64 entry_index );
public     :                  SOSImpExp             logical Lock (uint64 entry_index, logical wait=YES );
public     :                  SOSImpExp             logical LockInternal (uint64 entry_index, logical wait=YES );
public     :                  SOSImpExp             BinArrayObjEntry *ProvideEntry (uint64 entry_index, logical create=YES );
public     :                  SOSImpExp             BinArrayObjEntry *ProvideEntryIntern (uint64 entry_index, logical create=YES );
public     :                  SOSImpExp             void RegUnusedEntry (BinArrayObjEntry *object_entry );
public     : virtual          SOSImpExp             void RelObjEntry (BinSArrayObjEntry *obj_entry );
public     :                  SOSImpExp             BinArrayObjEntry *ReleaseEntry (uint64 entry_index );
public     :                  SOSImpExp             logical ReleaseLockedEntries (thread_t threadid );
public     :                  SOSImpExp             BinArrayObjEntry *RemoveEntry (uint64 entry_index );
public     :                  SOSImpExp             logical Reorganize (uint32 start_num=0 );
public     :                  SOSImpExp             BinArrayObjEntry *ReserveEntry (uint64 entry_index, logical lock );
public     : virtual          SOSImpExp             void StoreObjEntry (BinArray *array, BinSArrayObjEntry *obj_entry );
public     :                  SOSImpExp             logical Unlock (uint64 entry_index );
public     :                  SOSImpExp             logical UnlockInternal (uint64 entry_index );
public     :                  SOSImpExp             void UpdateEntry (uint64 entry_index );
public     :                  SOSImpExp             logical WaitForEntry (BinArrayObjEntry *object_entry );
public     :                  SOSImpExp                  ~BinArray ( );
};

#pragma pack()
#endif
