/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    LookupList

\brief    


\date     $Date: 2006/03/13 21:33:43,60 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   LookupList_HPP
#define   LookupList_HPP

class     LookupList;

#include  <sBinaryList.hpp>
#include  <sCLPosition.hpp>
#pragma pack(4)

class  LookupList :public BinaryList
{
protected  :         CLPosition                                   posCache ATTR_ALIGN(4);                                    //
protected  :         logical                                      posCacheValid;                                             //
protected  :         size_t                                       posCacheIndex;                                             //

public     :
public     :         OGUI7ImpExp                 logical Add (void *pkey, void *pobj );
public     :         OGUI7ImpExp                 void *GetByIndex (int index );
public     :         OGUI7ImpExp                 void *GetByKey (void *pkey );
public     :         OGUI7ImpExp                 void *GetKeyByIndex (int index );
public     :         OGUI7ImpExp                                         LookupList ( );
public     :                                     void OnAddItem (void *pitem );
public     :                                     void OnCopyKey (void *pkey );
protected  : virtual OGUI7ImpExp                 void OnDeleteItem (void *pitem, logical fFree=NO );
protected  : virtual OGUI7ImpExp                 void OnFree (void *pkey, void *pobj );
protected  : virtual OGUI7ImpExp                 void *OnGetKey (void *pitem );
protected  : virtual                             void OnInsert (void **ppitem, void **ppkey );
protected  : virtual                             void OnInsertItem (void *pitem );
protected  :                                     void *_GetByIndex (int index );
public     :         OGUI7ImpExp                 logical CheckOrderIntegrity ( ){

  return BinaryList::CheckOrderIntegrity();

}

public     :         OGUI7ImpExp                 logical DeleteByKey (void *pkey ){

  posCacheValid = NO;

  return BinaryList::DeleteByKey(pkey);

}

public     :         OGUI7ImpExp                 logical FreeByKey (void *pkey ){

  posCacheValid = NO;

  return BinaryList::FreeByKey(pkey);

}

public     :         OGUI7ImpExp                 int GetCount ( ){

  return BinaryList::GetCount();

}

};

#pragma pack()
#endif
