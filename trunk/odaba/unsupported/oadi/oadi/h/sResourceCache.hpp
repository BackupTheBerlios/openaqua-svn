/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    ResourceCache

\brief    


\date     $Date: 2006/07/09 14:32:56,79 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ResourceCache_HPP
#define   ResourceCache_HPP

class     ResourceCache;

class     CTX_GUIBase;
class     OAction;
class     OCBitmap;
class     OEventActionControl;
class     OFont_;
class     OProject;
class     OResource;
class     ResourceEntry;
#include  <cActionType.h>
#include  <sBinArray.hpp>
#include  <sBinSArrayObjEntry.hpp>
#include  <sBinTree.hpp>
#include  <sPropertyHandle.hpp>
class  ResourceCache :public BinTree
{
protected  :         BTIterator                                   iterator;                                                  // 
protected  :         DBObjectHandle                              *res_db;                                                    // 
protected  :         PropertyHandle                               void_ph;                                                   // 
protected  :         PropertyHandle                              *current_ph;                                                // 
protected  :         PropertyHandle                               act_ph;                                                    // 
protected  :         int8                                         id;                                                        // 

public     :
                     BTIterator                                  &get_iterator() { return(iterator); }
                     DBObjectHandle                              *get_res_db() { return(res_db); }
                     PropertyHandle                              &get_void_ph() { return(void_ph); }
                     PropertyHandle                              &get_act_ph() { return(act_ph); }
public     :                                        void Clear ( );
public     :                                        OResource *CreateResource (uint64 entry_index );
public     :                                        logical DeleteEntry (OResource *pOResource );
public     :                                        logical ExistWindow (char *class_names, char *win_names );
public     :                                        void FreeObjEntry (BinSArrayObjEntry *obj_entry );
public     :                                        OResource *GetEntry (int32 res_id );
public     :                                        logical Invalidate ( );
public     :                                        OAction *ProvideDefaultAction (char *name, ActionType vActionType, CTX_GUIBase *ctxptr );
public     :                                        OResource *ProvideEntry (int32 res_id );
public     :                                        OResource *ProvideEntry (PropertyHandle *ph, char *name );
public     :                                        OAction *ReadAction (char *name, ActionType vActionType );
public     :                                        OCBitmap *ReadBitmap (char *name );
public     :                                        OEventActionControl *ReadEventActionControl (char *name );
public     :                                        OFont_ *ReadFont (char *name );
public     :                                        OProject *ReadProject (char *name );
public     :                                             ResourceCache (DBObjectHandle *resDB, int8 cache_id );
public     :                                             ~ResourceCache ( );
};

#endif
