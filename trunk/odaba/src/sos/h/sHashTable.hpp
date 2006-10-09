/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    HashTable

\brief    


\date     $Date: 2006/03/12 19:20:01,98 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   HashTable_HPP
#define   HashTable_HPP

class     HashTable;

class     Recycler;
#include  <sRessourceLock.hpp>
#pragma pack(8)

class  HashTable
{
protected  :         void                                       **table;                                                     //
protected  :         uint32                                       len;                                                       //
protected  :         uint32                                       count;                                                     //
protected  :         logical                                      autoRehash;                                                //
protected  : static  Recycler                                    *recycler;                                                  //
protected  :         RessourceLock                                lock;                                                      //

public     :
public     :         SOS7ImpExp                  void Add (void *pvoidKey, void *pvoidItem );
public     :         SOS7ImpExp                  void Clear ( );
public     :         SOS7ImpExp                  logical Delete (void *pvoidKey );
public     : virtual SOS7ImpExp                  void DoAdd (void **ppvoidKey, void **ppvoidItem );
public     : virtual SOS7ImpExp                  int DoCompare (void *pvoidKey1, void *pvoidKey2 );
public     : virtual SOS7ImpExp                  void DoDelete (void *pvoidKey, void *pvoidItem );
public     : virtual SOS7ImpExp                  uint32 DoHash (void *pvoidKey );
public     :         SOS7ImpExp                  void *Find (void *pvoidKey );
public     :         SOS7ImpExp                                          HashTable (size_t len, logical fAutoRehash );
public     :         SOS7ImpExp                                          HashTable ( );
public     :         SOS7ImpExp                  void Rehash (size_t len );
public     :         SOS7ImpExp                  void *Take (void *pvoidKey );
public     : static  SOS7ImpExp                  logical __cdecl _TEST_ ( );
protected  :                                     void freeTable (void **ppvoidTable, size_t len, logical fDelete );
public     : virtual SOS7ImpExp                                          ~HashTable ( );
};

#pragma pack()
#endif
