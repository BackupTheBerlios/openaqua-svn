/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    BTIterator

\brief    Iterator fot  a binary tree
          The  binary  tree  iterator  allows  iterating  through a binary tree.
          Several  iterator  functions  and  operators  select  an  entry in the
          binary  tree  as  "current  entry". This allows accessing the instance
          from  the  currently  selected  entry  after  the  operation  has been
          performed (GetAt()).

\date     $Date: 2006/06/12 08:42:56,21 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BTIterator"

#include  <pdefault.h>
#include  <sBinTree.hpp>
#include  <sBTIterator.hpp>


/******************************************************************************/
/**
\brief  BTIterator - Constructor
        The iterator is constructed with a related binary tree.


\param  bin_tree - Pointer to a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BTIterator"

     BTIterator :: BTIterator (BinTree *bin_tree )
                     : tree(NULL),
  current_entry(NULL)
{

  SetTree(bin_tree);

}

/******************************************************************************/
/**
\brief  Cancel - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

void BTIterator :: Cancel ( )
{

  current_entry = NULL;

}

/******************************************************************************/
/**
\brief  Get - Get instance from binary tree
        The  function  locates  an  entry  in  the  binary  tree and returns the
        instance  when  being  located  successfully. When not being successful,
        the function returns NULL.

\return bt_instance - Instance returned from a binary tree
-------------------------------------------------------------------------------
\brief  i00 - Locate instance by index
        The  implementation  tries  to  locate  an  instance  in  a  binary tree
        according to the position passed to the function.

\param  lindx0 - Index position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *BTIterator :: Get (int32 lindx0 )
{
  void                   *bt_instance = NULL;
BEGINSEQ
  if ( !tree )                                       ERROR
  
  if ( current_entry = tree->GetEntry(lindx0) )
    bt_instance = current_entry->get_instance();

RECOVER
  bt_instance = NULL;
ENDSEQ
  return(bt_instance);
}

/******************************************************************************/
/**
\brief  i01 - Locate instance by key value
        The  implementation  tries  to  locate  an  instance  in  a  binary tree
        according  to  the  key  value  passed to the function. When no instance
        with  the  key  passed  could  be found in the binary tree, the function
        returns  NULL, but  the iterator  is set  to the next available entry in
        the tree.

\param  key_value - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

void *BTIterator :: Get (char *key_value, logical exact )
{
  void                   *bt_instance = NULL;
BEGINSEQ
  if ( !tree )                                       ERROR
  
  if ( (current_entry = tree->GetEntry(key_value)) && 
       (!exact || !tree->stscerr()) )
    bt_instance = current_entry->get_instance();

RECOVER
  bt_instance = NULL;
ENDSEQ
  return(bt_instance);
}

/******************************************************************************/
/**
\brief  GetAt - Get instance at current position
        The  function returns  a pointer  to the  instance currently selected in
        the iterator. When no instance is selected, the function returns NULL.

\return bt_instance - Instance returned from a binary tree

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAt"

void *BTIterator :: GetAt ( )
{

  return ( current_entry 
           ? current_entry->get_instance() : NULL );

}

/******************************************************************************/
/**
\brief  GetCount - Get number of instances in the collection


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 BTIterator :: GetCount ( )
{
  int32                   count = 0;
BEGINSEQ
  if ( !tree )                                       ERROR

  count = tree->GetCount();
RECOVER
  count = AUTO;
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  GetHead - Get first instance from binary tree
        The  function selects the first entry in the binary tree and returns the
        instance  from  the  first  entry.  When  the tre is empty, the function
        returns NULL.

\return bt_instance - Instance returned from a binary tree

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHead"

void *BTIterator :: GetHead ( )
{
  void                   *bt_instance = NULL;
BEGINSEQ
  if ( !tree )                                       ERROR
  
  if ( current_entry = tree->GetFirstEntry() )
    bt_instance = current_entry->get_instance();

RECOVER
  bt_instance = NULL;
ENDSEQ
  return(bt_instance);
}

/******************************************************************************/
/**
\brief  GetNext - Get next instance
        The  function selects the entry with the  next higher key value. When no
        current  entry  is  selected  in  the iterator, the function selects the
        first  entry.  Finally,  the  function  returns  the  instance  from the
        selected  entry. When no  entry could be  selected, the function returns
        NULL.

\return bt_instance - Instance returned from a binary tree

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNext"

void *BTIterator :: GetNext ( )
{
  void                   *bt_instance = NULL;
BEGINSEQ
  if ( GetNextEntry() )                              ERROR

  bt_instance = current_entry->get_instance();
RECOVER
  bt_instance = NULL;
ENDSEQ
  return(bt_instance);
}

/******************************************************************************/
/**
\brief  GetNextEntry - Locate next entry
        The  function selects the entry with the  next higher key value. When no
        current  entry  is  selected  in  the iterator, the function selects the
        first  entry. When no  entry could be  selected, the function returns an
        error (YES).

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNextEntry"

logical BTIterator :: GetNextEntry ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !tree )                                       ERROR

  if ( !(current_entry = !current_entry 
                         ? tree->GetFirstEntry() 
                         : current_entry->GetNext()) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetPosition - 


\return lindx0 - Index position

\param  key_value - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosition"

int32 BTIterator :: GetPosition (char *key_value, logical exact )
{
  int32                   lindx0 = AUTO;
BEGINSEQ
  if ( !tree )                                       ERROR
  
  if ( (current_entry = tree->GetEntry(key_value)) && 
       (!exact || !tree->stscerr()) )
    lindx0 = current_entry->GetPosition();

RECOVER
  lindx0 = AUTO;
ENDSEQ
  return(lindx0);
}

/******************************************************************************/
/**
\brief  GetPrevious - Get previous instance
        The  function selects the  entry with the  next lower key value. When no
        current  entry  is  selected  in  the iterator, the function selects the
        last  entry.  Finally,  the  function  returns  the  instance  from  the
        selected  entry. When no  entry could be  selected, the function returns
        NULL.

\return bt_instance - Instance returned from a binary tree

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPrevious"

void *BTIterator :: GetPrevious ( )
{
  void                   *bt_instance = NULL;
BEGINSEQ
  if ( GetPreviousEntry() )                           ERROR

  bt_instance = current_entry->get_instance();
RECOVER
  bt_instance = NULL;
ENDSEQ
  return(bt_instance);
}

/******************************************************************************/
/**
\brief  GetPreviousEntry - Locate previous entry
        The  function selects the  entry with the  next lower key value. When no
        current  entry  is  selected  in  the iterator, the function selects the
        last  entry. When  no entry  could be  selected, the function returns an
        error (YES).

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPreviousEntry"

logical BTIterator :: GetPreviousEntry ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !(current_entry = !current_entry 
                         ? tree->GetLastEntry() 
                         : current_entry->GetPrevious()) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetTail - Get last instance from binary tree
        The  function selects the last entry in  the binary tree and returns the
        instance  from  the  last  entry.  When  the  tre is empty, the function
        returns NULL.

\return bt_instance - Instance returned from a binary tree

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTail"

void *BTIterator :: GetTail ( )
{
  void                   *bt_instance = NULL;
BEGINSEQ
  if ( !tree )                                       ERROR
  
  if ( current_entry = tree->GetLastEntry() )
    bt_instance = current_entry->get_instance();

RECOVER
  bt_instance = NULL;
ENDSEQ
  return(bt_instance);
}

/******************************************************************************/
/**
\brief  Insert - 


\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - 


\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

logical BTIterator :: Insert (char *key_value )
{

  return ( tree->CreateEntry(key_value) );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  bt_instance - Instance returned from a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

logical BTIterator :: Insert (void *bt_instance )
{

  return ( tree->CreateEntry(bt_instance) );

}

/******************************************************************************/
/**
\brief  Remove - 


\return bt_instance - Instance returned from a binary tree
-------------------------------------------------------------------------------
\brief  i00 - 


\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *BTIterator :: Remove (char *key_value )
{

  return ( Get(key_value,YES) ? RemoveAt() : NULL );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  lindx0 - Index position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *BTIterator :: Remove (int32 lindx0 )
{

  return ( Get(lindx0) ? RemoveAt() : NULL );

}

/******************************************************************************/
/**
\brief  i02 - 


\param  bt_instance - Instance returned from a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Remove"

void *BTIterator :: Remove (void *bt_instance )
{
  char                keyarea[MAX_KEYLEN];
BEGINSEQ
  if ( !tree->GetKey(bt_instance,keyarea) )          ERROR

  bt_instance = Remove(keyarea);
RECOVER
  bt_instance = NULL;
ENDSEQ
  return(bt_instance);
}

/******************************************************************************/
/**
\brief  RemoveAt - 


\return bt_instance - Instance returned from a binary tree

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveAt"

void *BTIterator :: RemoveAt ( )
{
  void                   *bt_instance = NULL;
BEGINSEQ
  if ( !current_entry )                              ERROR
  
  if ( !current_entry->get_instance_owner() )
    bt_instance = current_entry->get_instance();
    
  tree->RemoveEntry(current_entry);
  current_entry = NULL;

RECOVER
  bt_instance = NULL;
ENDSEQ
  return(bt_instance);
}

/******************************************************************************/
/**
\brief  RemoveHead - 


\return bt_instance - Instance returned from a binary tree

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveHead"

void *BTIterator :: RemoveHead ( )
{

  return ( GetHead() ? RemoveAt() : NULL );

}

/******************************************************************************/
/**
\brief  RemoveTail - 


\return bt_instance - Instance returned from a binary tree

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveTail"

void *BTIterator :: RemoveTail ( )
{

  return ( GetTail() ? RemoveAt() : NULL );

}

/******************************************************************************/
/**
\brief  Reset - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void BTIterator :: Reset ( )
{

  tree = NULL;
  current_entry = NULL;

}

/******************************************************************************/
/**
\brief  SetTree - 



\param  bin_tree - Pointer to a binary tree
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTree"

void BTIterator :: SetTree (BinTree *bin_tree )
{

  if ( tree )
    tree->UnregisterIterator(*this);
  
  if ( tree = bin_tree )
    tree->RegisterIterator(*this);

}

/******************************************************************************/
/**
\brief  operator() - Position operator
        The  operator  locates  an  entry  in  the  binary  tree and returns the
        instance  when  being  located  successfully. When not being successful,
        the function returns NULL.

\return bt_instance - Instance returned from a binary tree
-------------------------------------------------------------------------------
\brief  i00 - Locate instance by index
        The  implementation  tries  to  locate  an  instance  in  a  binary tree
        according to the position passed to the function.

\param  lindx0 - Index position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator()"

void *BTIterator :: operator() (int32 lindx0 )
{

  return( Get(lindx0) );

}

/******************************************************************************/
/**
\brief  i01 - Locate instance by key value
        The  implementation  tries  to  locate  an  instance  in  a  binary tree
        according  to  the  key  value  passed to the function. When no instance
        with  the  key  passed  could  be found in the binary tree, the function
        returns  NULL, but  the iterator  is set  to the next available entry in
        the tree.

\param  key_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator()"

void *BTIterator :: operator() (char *key_value )
{

  return( Get(key_value) );

}

/******************************************************************************/
/**
\brief  operator++ - Locate next entry
        The  operator selects the entry with the  next higher key value. When no
        current  entry  is  selected  in  the iterator, the function returns the
        first entry.

\return bt_iterator - Iterator for a binary tree

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator++"

BTIterator &BTIterator :: operator++ ( )
{

  GetNextEntry();
  return(*this);
}

/******************************************************************************/
/**
\brief  operator-- - Locare previous entry
        The  operator selects the  entry with the  next lower key value. When no
        current  entry  is  selected  in  the iterator, the function returns the
        last entry.

\return bt_iterator - Iterator for a binary tree

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator--"

BTIterator &BTIterator :: operator-- ( )
{

  GetPreviousEntry();
  return(*this);
}

/******************************************************************************/
/**
\brief  operator-> - 


\return bt_instance - Instance returned from a binary tree

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator->"

void *BTIterator :: operator-> ( )
{

  return( GetAt() );

}

/******************************************************************************/
/**
\brief  ~BTIterator - Destructur



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BTIterator"

     BTIterator :: ~BTIterator ( )
{

  SetTree(NULL);

}


