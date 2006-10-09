/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ObjectEntryList

\brief    


\date     $Date: 2006/03/12 19:13:43,09 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ObjectEntryList_HPP
#define   ObjectEntryList_HPP

class     ObjectEntryList;

class     BinArrayObjEntry;
class     BinSArrayObjEntry;
class     CSLHandleList;
class     InstanceDescriptor;
class     InstancePool;
class     ObjectEntry;
class     acb;
class     db_RootBase;
class     eb_RootBase;
#include  <sBinArray.hpp>
#include  <sEB_Number.hpp>
#include  <sEvent.hpp>
#include  <sRessourceLock.hpp>
#include  <sStatistic.hpp>
#include  <svcls.hpp>
#pragma pack(8)

class  ObjectEntryList :public BinArray
{
protected  :         eb_RootBase                                 *root_base ATTR_ALIGN(4);                                   //
protected  :         logical                                      statistics;                                                //
protected  :         logical                                      flush_stop;                                                //
protected  :         int32                                        flush_interval;                                            //
protected  :         int16                                        release_quote;                                             //
protected  :         uint32                                       release_size;                                              //
protected  :         InstancePool                                *instance_pool;                                             //
protected  :         FILE                                        *intermediate;                                              //
protected  :         char                                        *intermediate_path;                                         //
protected  :         Statistic                                    total_stats;                                               //
protected  :         Statistic                                    provide_stats;                                             //
protected  :         Statistic                                    locate_stats;                                              //
protected  :         Statistic                                    write_stats;                                               //
protected  :         Statistic                                    flush_stats;                                               //
protected  :         Event                                        term_event;                                                //

public     :
                     eb_RootBase                                 *get_root_base() { return(root_base); }
                     logical                                      get_statistics() { return(statistics); }
                     int32                                        get_flush_interval() { return(flush_interval); }
                     int16                                        get_release_quote() { return(release_quote); }
                     uint32                                       get_release_size() { return(release_size); }
                     InstancePool                                *get_instance_pool() { return(instance_pool); }
                     FILE                                        *get_intermediate() { return(intermediate); }
                     char                                        *get_intermediate_path() { return(intermediate_path); }
                     Statistic                                   &get_total_stats() { return(total_stats); }
                     Statistic                                   &get_provide_stats() { return(provide_stats); }
                     Statistic                                   &get_locate_stats() { return(locate_stats); }
                     Statistic                                   &get_write_stats() { return(write_stats); }
                     Statistic                                   &get_flush_stats() { return(flush_stats); }
public     :                                     logical BuildIntermediate ( );
public     :                                     logical Flush ( );
public     : virtual                             void FreeObjEntry (BinSArrayObjEntry *obj_entry );
public     :                                     ObjectEntry *GetEntry (acb *acbptr );
public     :                                     logical GetInstance (BinArrayObjEntry *object_entry );
public     : virtual                             void InitObjEntry (BinSArrayObjEntry *obj_entry, uint64 entry_index );
public     :                                     logical Lock (acb *acbptr, logical wait );
public     :                                     logical LockInternal (acb *acbptr, logical wait );
public     :                                                             ObjectEntryList (eb_RootBase *erootbase );
public     :                                     InstanceDescriptor *ProvideEntry (acb *acbptr, logical create );
public     : virtual                             void RelObjEntry (BinSArrayObjEntry *obj_entry );
public     :                                     void ReleaseEntry (acb *acbptr );
public     :                                     logical RemoveIntermediate ( );
public     :                                     ObjectEntry *ReserveEntry (acb *acbptr, logical upd_ebi );
public     :                                     InstanceDescriptor *SetupEntry (acb *acbptr, InstanceDescriptor *inst_descr );
public     :                                     logical StartFlushThread ( );
public     :                                     logical StopFlushThread ( );
public     :                                     logical StoreIntermediate ( );
public     :                                     void StoreObjEntry (BinArray *array, BinSArrayObjEntry *obj_entry );
public     :                                     logical Unlock (acb *acbptr );
public     :                                     logical UnlockInternal (acb *acbptr );
public     :                                     logical Watch ( );
public     :                                                             ~ObjectEntryList ( );
};

#pragma pack()
#endif
