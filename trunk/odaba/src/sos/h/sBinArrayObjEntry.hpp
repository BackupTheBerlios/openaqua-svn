/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BinArrayObjEntry

\brief    


\date     $Date: 2006/03/12 19:19:37,35 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BinArrayObjEntry_HPP
#define   BinArrayObjEntry_HPP

class     BinArrayObjEntry;

#define  CYCL                                      5
class     BinArray;
class     BinArrayObjEntry;
#include  <sBinSArrayObjEntry.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  BinArrayObjEntry :public BinSArrayObjEntry,
public sts
{
protected  :         uint16                                       use_count ATTR_ALIGN(1);                                   //
protected  :         int32                                        last_use;                                                  //
protected  :         BinArrayObjEntry                            *free_entry;                                                //
protected  :         thread_t                                     owner;                                                     //

public     :
                     uint16                                       get_use_count() { return(use_count); }
                     int32                                        get_last_use() { return(last_use); }
                     BinArrayObjEntry                            *get_free_entry() { return(free_entry); }
public     :                                     void Initialize ( );
public     :                                     logical IsCandidate (uint32 release_num );
public     :                                     logical IsLocked ( );
public     :                                     logical Lock (BinArray *array, logical wait=YES );
public     :                                     logical LockInternal (BinArray *array, logical wait=YES );
public     :                                     logical ReleaseLock (thread_t threadid );
public     :                                     void ResetUseCount ( );
public     :                                     logical Unlock ( );
public     :                                     logical UnlockInternal ( );
public     :                                     logical Wait (int32 timeout );
public     :                                     logical WaitInternal (int32 timeout );
public     :                                     logical Release (uint32 luse ){

  last_use = luse;
  return ( --use_count ? NO : YES );

}

public     :                                     void Reserve ( ){

  use_count++;

}

public     :                                     void SetIndex (uint64 entry_index ){

  BinSArrayObjEntry::SetIndex(entry_index);
  
  use_count  = 0;
  last_use   = 0;
  owner      = 0;
  free_entry = NULL;
  
  *(sts *)this = sts();  
  stssfil();

}

public     :                                     void SetLastUse (uint32 luse ){

  last_use = luse;

}

public     :                                     void SetPrevious (BinArrayObjEntry *object_entry ){

  free_entry = object_entry;

}

};

#pragma pack()
#endif
