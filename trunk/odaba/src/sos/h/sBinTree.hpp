/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BinTree

\brief    Binary tree
          A  binary  tree  provides  fast  maintenance  features  for  ordered 
          collections.  The  order  is  defined  by  an elementary value and its
          position  in the instance or by complex keys consisting of one or more
          key attributes.

\date     $Date: 2006/03/12 19:19:38,73 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BinTree_HPP
#define   BinTree_HPP

class     BinTree;

#ifndef   DLL_BTIterator_HPP
#define   DLL_BTIterator_HPP
#include  <sBTIterator.hpp>
#include  <sDLL.h>
#endif
class     BTEntry;
class     kcb;
#include  <sBTIterator.hpp>
#include  <sEntryPool.hpp>
#include  <sRessourceLock.hpp>
#include  <ssts.hpp>
class  BinTree :public sts
{
protected  :         kcb                                         *key_definition ATTR_ALIGN(1);                              //
protected  :         int32                                        entry_length;                                              //
protected  :         int32                                        key_length;                                                //
protected  :         int32                                        key_position;                                              //
protected  :         char                                         key_type;                                                  //
protected  :         BTEntry                                     *top_entry;                                                 //
protected  :         EntryPool                                    entry_pool;                                                //
protected  :         EntryPool                                    instance_pool;                                             //
protected  :         RessourceLock                                resource_lock;                                             //
protected  :         DLL(BTIterator)                              iterators;                                                 //
protected  :         logical                                      optimizing;                                                //

public     :
                     kcb                                         *get_key_definition() { return(key_definition); }
                     int32                                        get_entry_length() { return(entry_length); }
                     int32                                        get_key_length() { return(key_length); }
                     int32                                        get_key_position() { return(key_position); }
                     char                                         get_key_type() { return(key_type); }
                     BTEntry                                     *get_top_entry() { return(top_entry); }
                     EntryPool                                   &get_entry_pool() { return(entry_pool); }
                     EntryPool                                   &get_instance_pool() { return(instance_pool); }
                     RessourceLock                               &get_resource_lock() { return(resource_lock); }
                     DLL(BTIterator)                             &get_iterators() { return(iterators); }
                     logical                                      get_optimizing() { return(optimizing); }
public     :                                     logical AddEntry (BTEntry *bt_entry );
public     :         SOS7ImpExp                                          BinTree (kcb *keydef, int32 entry_size, int32 block_size=256 );
public     :         SOS7ImpExp                                          BinTree (int32 entry_size, int32 key_pos, int32 key_len, char key_typ, int32 block_size=256 );
public     :         SOS7ImpExp                  void Clear ( );
public     :                                     int8 Compare (const void *entry1, const void *entry2 );
public     :                                     int8 CompareInst (void *bt_instance1, void *bt_instance2 );
public     :                                     int8 CompareKey (char *key_value, void *bt_instance );
public     :         SOS7ImpExp                  logical CreateEntry (void *bt_instance );
public     :         SOS7ImpExp                  logical CreateEntry (char *key_value );
public     :         SOS7ImpExp                  logical DeleteEntry (void *bt_instance );
public     :         SOS7ImpExp                  logical DeleteEntry (char *key_value );
public     :         SOS7ImpExp                  int32 GetCount ( );
public     :                                     BTEntry *GetEntry (int32 lindx0 );
public     :                                     BTEntry *GetEntry (char *key_value );
public     :                                     BTEntry *GetEntry (void *bt_instance );
public     :                                     BTEntry *GetFirstEntry ( );
public     :                                     char *GetKey (void *bt_instance, char *key_value );
public     :                                     BTEntry *GetLastEntry ( );
public     :         SOS7ImpExp                  logical Lock (logical wait=YES );
public     :         SOS7ImpExp                  logical Print (char *cpath );
public     :                                     void RegisterIterator (BTIterator &bt_iterator );
public     :                                     logical RemoveEntry (BTEntry *bt_entry );
public     :                                     logical SetKey (void *bt_instance, char *key_value );
public     :                                     void SetTop (BTEntry *bt_entry );
public     :         SOS7ImpExp                  logical Unlock ( );
public     :                                     void UnregisterIterator (BTIterator &bt_iterator );
public     :         SOS7ImpExp                                          ~BinTree ( );
};

#endif
