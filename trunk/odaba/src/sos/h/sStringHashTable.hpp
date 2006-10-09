/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    StringHashTable



\date     $Date: 2006/03/12 19:20:18,23 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   StringHashTable_HPP
#define   StringHashTable_HPP

class     StringHashTable;

#include  <sHashTable.hpp>
#pragma pack(8)

class  StringHashTable :public HashTable
{

public     :
public     : virtual SOS7ImpExp                  int DoCompare (void *pvoidKey1, void *pvoidKey2 );
public     : virtual SOS7ImpExp                  uint32 DoHash (void *pvoidKey );
public     :         SOS7ImpExp                                          StringHashTable ( );
public     :         SOS7ImpExp                                          StringHashTable (size_t len, logical fAutoRehash );
};

#pragma pack()
#endif
