/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    KeyCacheBase

\brief    


\date     $Date: 2006/03/12 19:13:27,29 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   KeyCacheBase_HPP
#define   KeyCacheBase_HPP

class     KeyCacheBase;

class     DBIndex;
#include  <sEB_Number.hpp>
class  KeyCacheBase
{

public     :
public     :                                                             KeyCacheBase ( );
public     : virtual                             logical LockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     : virtual                             logical UnlockKey (EB_Number entnr, DBIndex *db_index, char *keyptr, int32 owner_id );
public     : virtual                                                     ~KeyCacheBase ( );
};

#endif
