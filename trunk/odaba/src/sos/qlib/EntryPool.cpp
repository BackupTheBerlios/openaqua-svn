/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    EntryPool

\brief    


\date     $Date: 2006/06/03 15:59:02,12 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EntryPool"

#include  <pdefault.h>
#include  <sBinArray.hpp>
#include  <sEntryPoolBlock.hpp>
#include  <sEntryPool.hpp>


/******************************************************************************/
/**
\brief  CreatePoolBlock - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePoolBlock"

logical EntryPool :: CreatePoolBlock ( )
{
  EntryPoolBlock         *pbl   = NULL;
  char                   *entry_area;
  ushort                  count = block_count;
  logical                 term = NO;
BEGINSEQ
  SOSRESET
  pbl = new EntryPoolBlock(entry_size,block_count);  SOSCERR

  blocks.AddTail(pbl);

  entry_area = (char *)pbl->get_entries();
  while ( count-- )
  {
    unused_entries.AddTail(entry_area);
    entry_area += entry_size;
  }
RECOVER
  delete pbl;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  EntryPool - 



\param  size - 
\param  blockcount - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EntryPool"

     EntryPool :: EntryPool (uint16 size, uint16 blockcount )
                     : blocks(),
  entry_size(size ? size : 1),
  block_count(blockcount ? blockcount : 1024),
  unused_entries(blockcount ? blockcount : 1024),
  bin_array(NULL),
  current_block(NULL),
  current_entry(0)

{



}

/******************************************************************************/
/**
\brief  FreeEntryNext - 


\return entry_area - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeEntryNext"

void *EntryPool :: FreeEntryNext ( )
{

  return(this ? unused_entries.GetNext() : NULL);

}

/******************************************************************************/
/**
\brief  FreeEntryTop - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeEntryTop"

void EntryPool :: FreeEntryTop ( )
{

  unused_entries.GoTop();

}

/******************************************************************************/
/**
\brief  GetEntryCount - 


\return entry_count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntryCount"

uint32 EntryPool :: GetEntryCount ( )
{

  return( blocks.GetCount()*block_count );

}

/******************************************************************************/
/**
\brief  GetNext - 


\return entry_area - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNext"

void *EntryPool :: GetNext ( )
{
  void                   *entry_area = NULL;
  if ( !current_block )
  {
    current_block = blocks.GetHead();
    current_entry = 0;
  }
  else if ( current_entry >= block_count )
  {
    blocks.Find(current_block);
    current_block = blocks.GetNext();
    current_entry = 0;
  }
  
  if ( current_block )
  {
    entry_area = ((char *)current_block->get_entries())+current_entry*entry_size;
    current_entry++;
  }
  return(entry_area);
}

/******************************************************************************/
/**
\brief  GetUsedEntryCount - 


\return entry_count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetUsedEntryCount"

uint32 EntryPool :: GetUsedEntryCount ( )
{

  return( blocks.GetCount()*block_count - unused_entries.GetCount() );

}

/******************************************************************************/
/**
\brief  GoTop - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GoTop"

void EntryPool :: GoTop ( )
{

  current_block = NULL;
  current_entry = 0;

}

/******************************************************************************/
/**
\brief  ReleaseEntry - 



\param  entry_area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseEntry"

void EntryPool :: ReleaseEntry (void *entry_area )
{

  unused_entries.AddTail(entry_area);
  memset(entry_area,1,entry_size);

}

/******************************************************************************/
/**
\brief  ReserveEntry - 


\return entry_area - 

\param  reorg - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReserveEntry"

void *EntryPool :: ReserveEntry (logical reorg )
{
  void                   *entry_area;
BEGINSEQ
  if ( entry_area = unused_entries.RemoveHead() )    LEAVESEQ

  if ( reorg )
  {
    if ( bin_array )
      bin_array->Reorganize();
    if ( entry_area = unused_entries.RemoveHead() )  LEAVESEQ
  }

  CreatePoolBlock();
  entry_area = unused_entries.RemoveHead();
  if ( entry_area < *(char **)blocks.GetTail() || entry_area > (*(char **)blocks.GetTail())+(entry_size*block_count) )
                                                     ERROR
RECOVER
  entry_area = NULL;
ENDSEQ
  if ( entry_area )
    memset(entry_area,0,entry_size);
  return(entry_area);
}

/******************************************************************************/
/**
\brief  operator() - 


\return entry_area - 

\param  lindx0 - Index position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator()"

void *EntryPool :: operator() (int32 lindx0 )
{
  EntryPoolBlock         *pbl;
  void                   *entry_area = NULL;
  blocks.GoTop();
  while ( (pbl = blocks.GetNext()) && lindx0 >= block_count )
    lindx0 -= block_count;
  
  if ( pbl )
    entry_area = ((char *)pbl->get_entries())+lindx0*entry_size;

  return(entry_area);
}

/******************************************************************************/
/**
\brief  set_bin_array - 



\param  array - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_bin_array"

void EntryPool :: set_bin_array (BinArray *array )
{

  bin_array = array;


}

/******************************************************************************/
/**
\brief  ~EntryPool - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~EntryPool"

     EntryPool :: ~EntryPool ( )
{
  EntryPoolBlock         *pbl   = NULL;
  while ( pbl = blocks.RemoveTail() )
    delete pbl;



}


