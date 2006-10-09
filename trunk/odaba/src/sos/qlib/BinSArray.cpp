/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BinSArray

\brief    


\date     $Date: 2006/03/12 19:21:19,95 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BinSArray"

#include  <pdefault.h>
#include  <sBinArrayIdxEntry.hpp>
#include  <sBinSArrayObjEntry.hpp>
#include  <sBinSArray.hpp>


/******************************************************************************/
/**
\brief  BinSArray

-------------------------------------------------------------------------------
\brief i0


\param  size -
\param  blockcount -
\param  level_num
\param  autoreorg -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BinSArray"

                        BinSArray :: BinSArray (uint16 size, uint16 blockcount, int32 level_num, logical autoreorg )
                     : RessourceLock (YES),
  obj_entry_size(size),
  obj_entry_pool(size,blockcount ? blockcount : 1024),
  idx_entry_pool(sizeof(BinArrayIdxEntry),256),
  levels(level_num),
  top_entry(NULL),
  frequency(0),
  count_prov(0),
  stop_prov(0),
  auto_reorg(autoreorg)
{

//  QueryPerformanceFrequency( (LARGE_INTEGER*) &frequency );
  
  top_entry = (BinArrayIdxEntry *)idx_entry_pool.ReserveEntry();

}

/******************************************************************************/
/**
\brief i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BinSArray"

                        BinSArray :: BinSArray ( )
                     : RessourceLock (YES),
  obj_entry_size(0),
  obj_entry_pool(0,0),
  idx_entry_pool(0,0),
  levels(8),
  top_entry(NULL),
  frequency(0),
  count_prov(0),
  stop_prov(0),
  auto_reorg(YES)
{



}

/******************************************************************************/
/**
\brief  Clear - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void BinSArray :: Clear ( )
{
  BinSArrayObjEntry    *obj_entry;
  uint32                indx0 = 0;
  ILock();
  
  obj_entry_pool.GoTop();
  while ( obj_entry = (BinSArrayObjEntry *)obj_entry_pool.GetNext() )
  {
    FreeObjEntry(obj_entry);
    indx0++;
  }
  
  IUnlock();


}

/******************************************************************************/
/**
\brief  FreeObjEntry - 



\param  obj_entry -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeObjEntry"

void BinSArray :: FreeObjEntry (BinSArrayObjEntry *obj_entry )
{



}

/******************************************************************************/
/**
\brief  GetCount

\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 BinSArray :: GetCount ( )
{

  return ( obj_entry_pool.GetEntryCount() );

}

/******************************************************************************/
/**
\brief  GetEntry

\return obj_entry -

\param  lindx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

BinSArrayObjEntry *BinSArray :: GetEntry (int32 lindx )
{

  return ( (BinSArrayObjEntry *)obj_entry_pool(lindx-1) );

}

/******************************************************************************/
/**
\brief  GetLevelIndex - 



\param  entry_index -
\param  buffer -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLevelIndex"

void BinSArray :: GetLevelIndex (uint64 entry_index, char *buffer )
{

  switch ( levels )
  {
    case 16 : buffer[15] = (char)((entry_index & 0xf000000000000000)>>60);
    case 15 : buffer[14] = (char)((entry_index & 0xf00000000000000)>>56);
    case 14 : buffer[13] = (char)((entry_index & 0xf0000000000000)>>52);
    case 13 : buffer[12] = (char)((entry_index & 0xf000000000000)>>48);
    case 12 : buffer[11] = (char)((entry_index & 0xf00000000000)>>44);
    case 11 : buffer[10] = (char)((entry_index & 0xf0000000000)>>40);
    case 10 : buffer[9]  = (char)((entry_index & 0xf000000000)>>36);
    case  9 : buffer[8]  = (char)((entry_index & 0xf00000000)>>32);
    case  8 : buffer[7]  = (char)((entry_index & 0xf0000000)>>28);
    case  7 : buffer[6]  = (char)((entry_index & 0xf000000)>>24);
    case  6 : buffer[5]  = (char)((entry_index & 0xf00000)>>20);
    case  5 : buffer[4]  = (char)((entry_index & 0xf0000)>>16);
    case  4 : buffer[3]  = (char)((entry_index & 0xf000)>>12);
    case  3 : buffer[2]  = (char)((entry_index & 0xf00)>>8);
    case  2 : buffer[1]  = (char)((entry_index & 0xf0)>>4);
    case  1 : buffer[0]  = (char)(entry_index  & 0xf);
    default : ;
  }


}

/******************************************************************************/
/**
\brief  GetUsedCount

\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetUsedCount"

int32 BinSArray :: GetUsedCount ( )
{

  return ( obj_entry_pool.GetUsedEntryCount() );

}

/******************************************************************************/
/**
\brief  InitObjEntry - 



\param  obj_entry -
\param  entry_index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitObjEntry"

void BinSArray :: InitObjEntry (BinSArrayObjEntry *obj_entry, uint64 entry_index )
{

  obj_entry->SetIndex(entry_index);


}

/******************************************************************************/
/**
\brief  ProvideEntry

\return obj_entry -

\param  entry_index -
\param  create -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideEntry"

BinSArrayObjEntry *BinSArray :: ProvideEntry (uint64 entry_index, logical create )
{
  BinArrayIdxEntry       *index_entry = top_entry;
  BinArrayIdxEntry       *last_entry = top_entry;
  BinSArrayObjEntry      *obj_entry;
  char                    buffer[16];
  logical                 locked = NO;
  int                     i;
BEGINSEQ
  ILock();
  
  GetLevelIndex(entry_index,buffer);
  
  for ( i=levels; index_entry && i--; )
    index_entry = (*index_entry)(buffer[i]);
  
  if ( !index_entry )                                 
  {
    if ( !create )                                   ERROR
    obj_entry = (BinSArrayObjEntry *)obj_entry_pool.ReserveEntry(auto_reorg);
    
    for ( index_entry = top_entry, i=levels; index_entry && --i; )
    {
      last_entry = index_entry; 
      if ( !(index_entry = (*last_entry)(buffer[i])) )
        index_entry = *(*last_entry)[buffer[i]] = (BinArrayIdxEntry *)idx_entry_pool.ReserveEntry();
    }
    
    if ( !index_entry )                              SOSERR(99)
      
    index_entry = *(*index_entry)[buffer[0]] = (BinArrayIdxEntry *)obj_entry;
    InitObjEntry(obj_entry,entry_index);
  }


RECOVER
  index_entry = NULL;
ENDSEQ
  IUnlock();
  return((BinSArrayObjEntry *)index_entry);
}

/******************************************************************************/
/**
\brief  RemoveEntry - 


\return obj_entry -

\param  entry_index -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveEntry"

BinSArrayObjEntry *BinSArray :: RemoveEntry (uint64 entry_index )
{
  BinArrayIdxEntry       *index_entry  = top_entry;
  BinArrayIdxEntry       *level[16];
  char                    buffer[16];
  int                     i;
  logical                 term = NO;
BEGINSEQ
  ILock();
  
  GetLevelIndex(entry_index,buffer);

  for ( i=levels; index_entry && i--; )
  {
    level[i] = index_entry;
    index_entry = (*index_entry)(buffer[i]);
  }
  
  if ( !index_entry )                                ERROR

  obj_entry_pool.ReleaseEntry(index_entry);
  *(*level[0])[buffer[0]] = NULL;
  
  i = 1;
  for ( i=1; i<levels && level[i]->IsEmpty(); i++ )
  {
    idx_entry_pool.ReleaseEntry(level[i]);
    *(*level[i])[buffer[i]] = NULL;
  }


RECOVER
  index_entry = NULL;
ENDSEQ
  IUnlock();
  return((BinSArrayObjEntry *)index_entry);
}

/******************************************************************************/
/**
\brief  ~BinSArray


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BinSArray"

                        BinSArray :: ~BinSArray ( )
{

  Clear();

}


