/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EntryEventList

\brief    


\date     $Date: 2006/03/12 19:17:31,54 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "EntryEventList"

#include  <popa7.h>
#include  <sBinTree.hpp>
#include  <sEntryEventList.hpp>


/******************************************************************************/
/**
\brief  AddEvent - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief i0


\param  entnr -
\param  event_id - Ivend type
\param  sid -
\param  is_inst -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEvent"

logical EntryEventList :: AddEvent (EB_Number entnr, CSA_Events event_id, int16 sid, logical is_inst )
{
  EntryEvent              ev(entnr,event_id,sid,is_inst);

  logical                 term = NO;
  return ( AddEvent(ev) );

}

/******************************************************************************/
/**
\brief i01


\param  entry_event -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddEvent"

logical EntryEventList :: AddEvent (EntryEvent &entry_event )
{
  EntryEvent             *ev_ptr;
  logical                 term = NO;
BEGINSEQ
  if ( !(ev_ptr = Get(entry_event.ebsnum)) )
  {
    entry_tree->CreateEntry((char *)&entry_event.ebsnum);
    if ( !(ev_ptr = Get(entry_event.ebsnum)) )       SDBERR(99)
  }
  ev_ptr->Copy(entry_event);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Clear


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void EntryEventList :: Clear ( )
{

  entry_tree->Clear();

}

/******************************************************************************/
/**
\brief  EntryEventList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "EntryEventList"

                        EntryEventList :: EntryEventList ( )
                     : BTIterator(NULL),
  entry_tree(NULL)

{

  entry_tree = new BinTree(sizeof(EntryEvent),offsetof(EntryEvent,ebsnum),sizeof(EB_Number),'I',256);
  SetTree(entry_tree);

}

/******************************************************************************/
/**
\brief  Get

\return entry_event -
-------------------------------------------------------------------------------
\brief i0


\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

EntryEvent *EntryEventList :: Get (int32 lindx0 )
{

  return((EntryEvent *)BTIterator::Get(lindx0));

}

/******************************************************************************/
/**
\brief i01


\param  entnr_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

EntryEvent *EntryEventList :: Get (EB_Number &entnr_ref )
{

  return((EntryEvent *)BTIterator::Get((char *)&entnr_ref,YES));

}

/******************************************************************************/
/**
\brief  ~EntryEventList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~EntryEventList"

                        EntryEventList :: ~EntryEventList ( )
{

  SetTree(NULL);
  delete entry_tree;
  entry_tree = NULL;

}


