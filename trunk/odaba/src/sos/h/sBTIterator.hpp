/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    BTIterator

\brief    Iterator fot  a binary tree
          The  binary  tree  iterator  allows  iterating  through a binary tree.
          Several  iterator  functions  and  operators  select  an  entry in the
          binary  tree  as  "current  entry". This allows accessing the instance
          from  the  currently  selected  entry  after  the  operation  has been
          performed (GetAt()).

\date     $Date: 2006/06/12 08:42:51,54 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BTIterator_HPP
#define   BTIterator_HPP

class     BTIterator;
#include "csosdll.h"

#define  MAX_KEYLEN                                512
class     BinTree;
#include  <sBTEntry.hpp>
#include  <sBTIterator.hpp>
class  BTIterator
{
protected  :         BinTree                                     *tree;                                                      // 
protected  :         BTEntry                                     *current_entry;                                             // 

public     :
                     BinTree                                     *get_tree() { return(tree); }
                     BTEntry                                     *get_current_entry() { return(current_entry); }
public     :                  SOSImpExp                  BTIterator (BinTree *bin_tree );
public     :                  SOSImpExp             void Cancel ( );
public     :                  SOSImpExp             void *Get (int32 lindx0 );
public     :                  SOSImpExp             void *Get (char *key_value, logical exact=NO );
public     :                  SOSImpExp             void *GetAt ( );
public     :                  SOSImpExp             int32 GetCount ( );
public     :                  SOSImpExp             void *GetHead ( );
public     :                  SOSImpExp             void *GetNext ( );
public     :                  SOSImpExp             logical GetNextEntry ( );
public     :                  SOSImpExp             int32 GetPosition (char *key_value, logical exact=NO );
public     :                  SOSImpExp             void *GetPrevious ( );
public     :                  SOSImpExp             logical GetPreviousEntry ( );
public     :                  SOSImpExp             void *GetTail ( );
public     :                  SOSImpExp             logical Insert (char *key_value );
public     :                  SOSImpExp             logical Insert (void *bt_instance );
public     :                  SOSImpExp             void *Remove (char *key_value );
public     :                  SOSImpExp             void *Remove (int32 lindx0 );
public     :                  SOSImpExp             void *Remove (void *bt_instance );
public     :                  SOSImpExp             void *RemoveAt ( );
public     :                  SOSImpExp             void *RemoveHead ( );
public     :                  SOSImpExp             void *RemoveTail ( );
public     :                                        void Reset ( );
public     :                  SOSImpExp             void SetTree (BinTree *bin_tree );
public     :                  SOSImpExp             void *operator() (int32 lindx0 );
public     :                  SOSImpExp             void *operator() (char *key_value );
public     :                  SOSImpExp             BTIterator &operator++ ( );
public     :                  SOSImpExp             BTIterator &operator-- ( );
public     :                  SOSImpExp             void *operator-> ( );
public     :                  SOSImpExp                  ~BTIterator ( );
};

#endif
