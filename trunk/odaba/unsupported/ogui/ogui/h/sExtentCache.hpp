/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ExtentCache

\brief    


\date     $Date: 2006/03/13 21:33:38,98 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ExtentCache_HPP
#define   ExtentCache_HPP

class     ExtentCache;

#include  <sHashTable.hpp>
class  ExtentCache :public HashTable
{

public     :
public     :                                     void DoAdd (void **ppkey, void **ppitem );
public     : virtual                             int DoCompare (void *pkey1, void *pkey2 );
public     :                                     void DoDelete (void *pkey, void *pitem );
public     : virtual                             uint32 DoHash (void *pkey );
};

#endif
