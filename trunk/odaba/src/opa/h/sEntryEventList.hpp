/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EntryEventList

\brief    


\date     $Date: 2006/03/12 19:13:20,17 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EntryEventList_HPP
#define   EntryEventList_HPP

class     EntryEventList;

#ifndef   GSRT_EntryEvent_HPP
#define   GSRT_EntryEvent_HPP
#include  <sEntryEvent.hpp>
#include  <sGSRT.h>
#endif
class     BinTree;
#include  <sBTIterator.hpp>
#include  <sEB_Number.hpp>
#include  <sEntryEvent.hpp>
class  EntryEventList :public BTIterator
{
protected  :         BinTree                                     *entry_tree;                                                //

public     :
                     BinTree                                     *get_entry_tree() { return(entry_tree); }
public     :                                     logical AddEvent (EB_Number entnr, CSA_Events event_id, int16 sid, logical is_inst );
public     :                                     logical AddEvent (EntryEvent &entry_event );
public     :                                     void Clear ( );
public     :                                                             EntryEventList ( );
public     :                                     EntryEvent *Get (int32 lindx0 );
public     :                                     EntryEvent *Get (EB_Number &entnr_ref );
public     :                                                             ~EntryEventList ( );
};

#endif
