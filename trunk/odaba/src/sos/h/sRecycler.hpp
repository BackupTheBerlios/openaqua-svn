/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    Recycler

\brief    


\date     $Date: 2006/03/12 19:20:14,89 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Recycler_HPP
#define   Recycler_HPP

class     Recycler;

class     HashEntry;
#include  <sRessourceLock.hpp>
#pragma pack(8)

class  Recycler
{
protected  :         RessourceLock                                lock;                                                      
protected  :         HashEntry                                   *head;                                                      
protected  :         int                                          count;                                                     

public     :
public     :                                     void Add (HashEntry *hash_entry );
public     :                                                             Recycler ( );
public     :                                     HashEntry *Take ( );
public     :                                                             ~Recycler ( );
};

#pragma pack()
#endif
