/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    KeyCache

\brief    


\date     $Date: 2006/03/12 19:13:27,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   KeyCache_HPP
#define   KeyCache_HPP

class     KeyCache;

class     BinTree;
class     DBIndex;
class     KeyCacheIndex;
#include  <sBTIterator.hpp>
#include  <sEB_Number.hpp>
#include  <sKeyCacheBase.hpp>
class  KeyCache :public KeyCacheBase,
public BTIterator
{
protected  :         BinTree                                     *tree;                                                      //

public     :
                     BinTree                                     *get_tree() { return(tree); }
public     :                                     KeyCacheIndex *GetIndex (EB_Number entnr );
public     :                                     KeyCacheIndex *GetIndex (int32 indx0 );
public     :                                     logical ILock ( );
public     :                                     logical IUnlock ( );
public     :                                                             KeyCache ( );
public     :                                     logical LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     :                                     void RemoveIndex (KeyCacheIndex *kc_index );
public     :                                     logical UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     :                                                             ~KeyCache ( );
};

#endif
