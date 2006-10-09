/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ObjectEntry

\brief    


\date     $Date: 2006/03/12 19:13:42,82 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ObjectEntry_HPP
#define   ObjectEntry_HPP

class     ObjectEntry;

class     CSHandleList;
class     EntryEvent;
class     InstancePool;
class     acb;
#include  <sBinArrayObjEntry.hpp>
#include  <sCSLHandleList.hpp>
#include  <sEBI.hpp>
#include  <sEB_Number.hpp>
#include  <sInstanceDescriptor.hpp>
#include  <sObjectEntryList.hpp>
#include  <sRessourceLock.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  ObjectEntry :public BinArrayObjEntry,
public InstanceDescriptor,
public RessourceLock
{
protected  :         CSLHandleList                                active_handles ATTR_ALIGN(4);                              //

public     :
                     CSLHandleList                               &get_active_handles() { return(active_handles); }
public     :                                     void Free (InstancePool *instance_pool );
public     :                                     logical GenerateEvent (EntryEvent *ev_ptr );
public     :                                     void Initialize (acb *acbptr );
public     :                                     void Release (CSHandleList *lcs_handle );
public     :                                     void ReleaseLocked (InstancePool *instance_pool );
public     :                                     void Reserve (CSHandleList *lcs_handle );
};

#pragma pack()
#endif
