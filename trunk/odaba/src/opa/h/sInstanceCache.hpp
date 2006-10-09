/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    InstanceCache

\brief    


\date     $Date: 2006/03/12 19:13:25,23 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   InstanceCache_HPP
#define   InstanceCache_HPP

class     InstanceCache;

#include  <sGSRT.h>
class     ICEntry;
#include  <sDLL.h>
class     inti;
class     ICEntry;
class     inti;
#include  <sEB_Number.hpp>
#include  <sStatistic.hpp>
#include  <sbnode.hpp>
#pragma pack(8)

class  InstanceCache
{
protected  :         int8                                         size;                                                      
protected  :         DLL(inti)                                   *inti_array;                                                
protected  :         bnode                                       *node_ref;                                                  
protected  :         Statistic                                    stats;                                                     
protected  :         GSRT(ICEntry)                               *ordered_list;                                              
protected  :         uint32                                       use_count;                                                 
protected  :         int32                                        mod_count;                                                 
protected  :         int32                                        mod_max;                                                   
protected  :         int32                                        entry_len;                                                 

public     :
                     int8                                         get_size() { return(size); }
                     DLL(inti)                                   *get_inti_array() { return(inti_array); }
                     bnode                                       *get_node_ref() { return(node_ref); }
                     Statistic                                   &get_stats() { return(stats); }
                     GSRT(ICEntry)                               *get_ordered_list() { return(ordered_list); }
                     uint32                                       get_use_count() { return(use_count); }
                     int32                                        get_mod_count() { return(mod_count); }
                     int32                                        get_mod_max() { return(mod_max); }
                     int32                                        get_entry_len() { return(entry_len); }
public     :                                     ICEntry *AddEntry (inti *intiptr );
public     :                                     logical ChangeOrder ( );
public     :                                     ICEntry *Find (EB_Number entnr );
public     :                                     logical Flush (logical remove );
public     :                                                             InstanceCache (bnode *bnodeptr );
public     :                                     void *Locate (char *skey );
public     :                                     logical RemoveEntry (ICEntry *iceptr );
public     :                                     logical Resize (int16 bufnum=AUTO );
public     :                                     logical Save (inti *intiptr );
public     :                                     void SetInstance (ICEntry *iceptr );
public     :                                                             ~InstanceCache ( );
};

#pragma pack()
#endif
