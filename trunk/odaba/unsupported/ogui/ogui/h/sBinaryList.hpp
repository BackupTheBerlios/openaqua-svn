/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    BinaryList

\brief    


\date     $Date: 2006/03/22 15:19:45,79 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BinaryList_HPP
#define   BinaryList_HPP

class     BinaryList;

#include  <sCLPosition.hpp>
#include  <sClusteredList.hpp>
#pragma pack(4)

class  BinaryList :public ClusteredList
{

public     :
public     :         OGUIImpExp                  logical Add (void *pitem );
public     :         OGUIImpExp                                          BinaryList (size_t sizeItem=sizeof(void*), logical fSignalDelete=NO );
public     :         OGUIImpExp                  logical CheckOrderIntegrity ( );
public     :         OGUIImpExp                  logical DeleteByKey (void *pkey, logical fFree=NO );
public     :         OGUIImpExp                  void *GetByKey (void *pkey );
public     : virtual OGUIImpExp                  logical GetPositionByItem (CLPosition &rCLPosition, void *pitem );
public     :         OGUIImpExp                  logical GetPositionByKey (CLPosition &rCLPosition, void *pkey );
protected  : virtual OGUIImpExp                  int32 OnCompare (void *pkey1, void *pkey2 );
protected  : virtual OGUIImpExp                  void *OnGetKey (void *pitem );
public     :         OGUIImpExp                  logical FreeByKey (void *pkey ){
  logical                 term = NO;
BEGINSEQ
  if ( DeleteByKey(pkey,YES) )                       ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

};

#pragma pack()
#endif
