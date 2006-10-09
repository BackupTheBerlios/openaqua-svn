/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    StringKeyList



\date     $Date: 2006/03/13 21:34:53,43 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   StringKeyList_HPP
#define   StringKeyList_HPP

class     StringKeyList;

#include  <sLookupList.hpp>
#pragma pack(4)

class  StringKeyList :public LookupList
{
protected  :         logical                                      ignoreCase ATTR_ALIGN(4);                                  //
protected  :         logical                                      freeKey;                                                   //
protected  :         logical                                      freeObj;                                                   //
protected  :         logical                                      copyKey;                                                   //

public     :
public     : virtual OGUI7ImpExp                 int32 OnCompare (void *pkey1, void *pkey2 );
public     : virtual OGUI7ImpExp                 void OnFree (void *pkey, void *pobj );
protected  : virtual                             void OnInsert (void **ppkey, void **ppitem );
public     :         OGUI7ImpExp                                         StringKeyList (logical fIgnoreCase, logical fCopyKey=NO, logical fFreeKey=NO, logical fFreeObj=NO );
};

#pragma pack()
#endif
