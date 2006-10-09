/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    BTEntry

\brief    Binary tree entry
          An  entry in a binary  tree refers to a  tree instance and its related
          entries.

\date     $Date: 2006/06/11 16:20:29,10 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BTEntry_HPP
#define   BTEntry_HPP

#include "csosdll.h"
class     BinTree;
class  BTEntry
{
protected  :         void                                        *instance;                                                  // 
protected  :         BTEntry                                     *parent;                                                    // 
protected  :         BTEntry                                     *left;                                                      // 
protected  :         BTEntry                                     *right;                                                     // 
protected  :         int32                                        count;                                                     // 
protected  :         int16                                        max_level;                                                 // 
protected  :         logical                                      instance_owner;                                            // 

public     :
                     void                                        *get_instance() { return(instance); }
                     BTEntry                                     *get_parent() { return(parent); }
                     BTEntry                                     *get_left() { return(left); }
                     BTEntry                                     *get_right() { return(right); }
                     int32                                        get_count() { return(count); }
                     logical                                      get_instance_owner() { return(instance_owner); }
public     :                                        logical AddEntry (BTEntry *bt_entry, BinTree *bin_tree );
public     :                                             BTEntry ( );
public     :                                        int32 Count ( );
public     :                                        BTEntry *GetEntry (int32 lindx0 );
public     :                                        BTEntry *GetEntry (char *key_value, BinTree *bin_tree );
public     :                                        BTEntry *GetEntry (void *bt_instance, BinTree *bin_tree );
public     :                                        BTEntry *GetLeftParent ( );
public     :                                        BTEntry *GetMajor ( );
public     :                                        BTEntry *GetMinor ( );
public     :                                        BTEntry *GetNext ( );
public     :                  SOSImpExp             int32 GetPosition ( );
public     :                                        BTEntry *GetPrevious ( );
public     :                                        BTEntry *GetRightParent ( );
public     :                                        BTEntry *GetTop ( );
public     :                                        logical HasLeftParent ( );
public     :                                        logical HasRightParent ( );
public     :                                        void Initialize ( );
public     :                                        int32 Level ( );
public     :                                        logical Print (FILE *fileptr, int32 level );
public     :                                        logical Remove (BinTree *bin_tree );
public     :                                        void Reparent (BTEntry *bt_entry );
public     :                                        logical Reset (BinTree *bin_tree );
public     :                                        logical RotateLeft (logical recursive=YES );
public     :                                        logical RotateRight (logical recursive=YES );
public     :                                        logical UpdateCounts ( );
public     :                                        logical UpdateCountsRecursive ( );
public     :                                        void set_instance (void *bt_instance );
public     :                                        void set_instance_owner (logical owner_opt ){

  instance_owner = owner_opt;

}

};

#endif
