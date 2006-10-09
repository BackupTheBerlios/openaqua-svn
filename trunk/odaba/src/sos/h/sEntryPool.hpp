/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    EntryPool

\brief    


\date     $Date: 2006/03/12 19:19:55,76 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EntryPool_HPP
#define   EntryPool_HPP

class     EntryPool;

#ifndef   DLL_EntryPoolBlock_HPP
#define   DLL_EntryPoolBlock_HPP
#include  <sEntryPoolBlock.hpp>
#include  <sDLL.h>
#endif
class     BinArray;
class     EntryPoolBlock;
#include  <sQuList.hpp>
#pragma pack(8)

class  EntryPool
{
protected  :         DLL(EntryPoolBlock)                          blocks;                                                    
protected  :         uint16                                       entry_size;                                                
protected  :         uint16                                       block_count;                                               
protected  :         QuList                                       unused_entries;                                            
protected  :         BinArray                                    *bin_array;                                                 
protected  :         EntryPoolBlock                              *current_block;                                             
protected  :         uint16                                       current_entry;                                             

public     :
                     DLL(EntryPoolBlock)                         &get_blocks() { return(blocks); }
                     uint16                                       get_entry_size() { return(entry_size); }
                     uint16                                       get_block_count() { return(block_count); }
                     QuList                                      &get_unused_entries() { return(unused_entries); }
                     BinArray                                    *get_bin_array() { return(bin_array); }
                     EntryPoolBlock                              *get_current_block() { return(current_block); }
                     uint16                                       get_current_entry() { return(current_entry); }
public     :                                     logical CreatePoolBlock ( );
public     :                                                             EntryPool (uint16 size, uint16 blockcount );
public     :                                     void *FreeEntryNext ( );
public     :                                     void FreeEntryTop ( );
public     :                                     uint32 GetEntryCount ( );
public     :                                     void *GetNext ( );
public     :                                     uint32 GetUsedEntryCount ( );
public     :                                     void GoTop ( );
public     :                                     void ReleaseEntry (void *entry_area );
public     :                                     void *ReserveEntry (logical reorg=NO );
public     :                                     void *operator() (int32 lindx0 );
public     :                                     void set_bin_array (BinArray *array );
public     :                                                             ~EntryPool ( );
};

#pragma pack()
#endif
