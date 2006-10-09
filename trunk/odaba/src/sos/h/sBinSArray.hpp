/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BinSArray

\brief    


\date     $Date: 2006/03/12 19:19:38,12 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BinSArray_HPP
#define   BinSArray_HPP

class     BinSArray;

class     BinArrayIdxEntry;
class     BinSArrayObjEntry;
#include  <sEntryPool.hpp>
#include  <sRessourceLock.hpp>
#pragma pack(8)

class  BinSArray :public RessourceLock
{
protected  :         int32                                        obj_entry_size ATTR_ALIGN(4);                              
protected  :         EntryPool                                    obj_entry_pool;                                            
protected  :         EntryPool                                    idx_entry_pool;                                            
protected  :         int16                                        levels;                                                    
protected  :         BinArrayIdxEntry                            *top_entry;                                                 
protected  :         int64                                        frequency;                                                 
protected  :         int64                                        stop_prov;                                                 
protected  :         uint32                                       count_prov;                                                
protected  :         logical                                      auto_reorg;                                                

public     :
                     int32                                        get_obj_entry_size() { return(obj_entry_size); }
                     EntryPool                                   &get_obj_entry_pool() { return(obj_entry_pool); }
                     EntryPool                                   &get_idx_entry_pool() { return(idx_entry_pool); }
                     int16                                        get_levels() { return(levels); }
                     BinArrayIdxEntry                            *get_top_entry() { return(top_entry); }
                     int64                                        get_frequency() { return(frequency); }
                     int64                                        get_stop_prov() { return(stop_prov); }
                     uint32                                       get_count_prov() { return(count_prov); }
                     logical                                      get_auto_reorg() { return(auto_reorg); }
public     :         SOS7ImpExp                                          BinSArray (uint16 size, uint16 blockcount, int32 level_num, logical autoreorg=YES );
public     :         SOS7ImpExp                                          BinSArray ( );
public     :         SOS7ImpExp                  void Clear ( );
public     : virtual SOS7ImpExp                  void FreeObjEntry (BinSArrayObjEntry *obj_entry );
public     :         SOS7ImpExp                  int32 GetCount ( );
public     :         SOS7ImpExp                  BinSArrayObjEntry *GetEntry (int32 lindx );
public     :         SOS7ImpExp                  void GetLevelIndex (uint64 entry_index, char *buffer );
public     :         SOS7ImpExp                  int32 GetUsedCount ( );
public     : virtual SOS7ImpExp                  void InitObjEntry (BinSArrayObjEntry *obj_entry, uint64 entry_index );
public     :         SOS7ImpExp                  BinSArrayObjEntry *ProvideEntry (uint64 entry_index, logical create=YES );
public     :         SOS7ImpExp                  BinSArrayObjEntry *RemoveEntry (uint64 entry_index );
public     :         SOS7ImpExp                                          ~BinSArray ( );
};

#pragma pack()
#endif
