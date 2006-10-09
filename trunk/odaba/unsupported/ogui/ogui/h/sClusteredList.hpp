/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ClusteredList

\brief    Clustered list
          The  list does administrate a  set of items of  any type. Items can be
          accessed  by  index  or  by  position. The list can be browsed in both
          directions. 
          The  list moves the  items into clusters  with a minimum and a maximum
          size.  The minimum size is used for cluster reorganisation, when items
          have been deleted. 
          The  list generates several on-events, which  can be overloaded by the
          application to free or allocate resources.
          t

\date     $Date: 2006/03/13 21:33:34,20 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ClusteredList_HPP
#define   ClusteredList_HPP

class     ClusteredList;

#include  <sCLEnumerator.hpp>
#include  <sCLPosition.hpp>
#pragma pack(4)

class  ClusteredList
{
protected  :         size_t                                       count;                                                     //
protected  :         void                                        *clusters;                                                  //
protected  :         size_t                                       clusterCount;                                              //
protected  :         size_t                                       itemSize;                                                  //
protected  :         logical                                      signalDelete;                                              //
protected  :         size_t                                       lower;                                                     //
protected  :         size_t                                       upper;                                                     //

public     :
                     size_t                                      &get_count() { return(count); }
public     :         OGUI7ImpExp                 size_t Append (void *pitem );
public     :         OGUI7ImpExp                 logical CanGetAt (CLPosition &rCLPosition );
public     :         OGUI7ImpExp                 logical CanWriteAt (CLPosition &rCLPosition );
public     :         OGUI7ImpExp                                         ClusteredList (size_t sizeItem=sizeof(void*), logical fSignalDelete=NO, size_t sizeLower_64=64, size_t sizeUpper_256=256 );
public     :                                     logical Delete (void *pitem, logical fFree_NO=NO );
public     :         OGUI7ImpExp                 logical DeleteAll (logical fFree_NO=NO );
public     :         OGUI7ImpExp                 logical DeleteAt (CLPosition &rCLPosition, logical fFree_NO=NO );
public     :                                     logical DeleteByIndex (int index, logical fFree_NO=NO );
public     :         OGUI7ImpExp                 logical Enumerate (CLEnumerator &rCLEnumerator );
public     :                                     logical Free (void *pObj );
public     :         OGUI7ImpExp                 logical FreeAll ( );
public     :         OGUI7ImpExp                 logical FreeAt (CLPosition &rCLPosition );
public     :                                     logical FreeByIndex (int index );
public     :         OGUI7ImpExp                 void *GetAt (CLPosition &rCLPosition );
public     :         OGUI7ImpExp                 void *GetByIndex (int index );
public     :         OGUI7ImpExp                 size_t GetCount ( );
public     :         OGUI7ImpExp                 logical GetHeadPosition (CLPosition &rCLPosition );
public     :         OGUI7ImpExp                 size_t GetIndexByPosition (CLPosition &rCLPosition );
public     :         OGUI7ImpExp                 void *GetNext (CLPosition &rCLPosition );
public     :         OGUI7ImpExp                 logical GetNextPosition (CLPosition &rCLPosition );
public     :         OGUI7ImpExp                 logical GetPositionByIndex (CLPosition &rCLPosition, int index );
public     : virtual OGUI7ImpExp                 logical GetPositionByItem (CLPosition &rCLPosition, void *pitem );
public     :         OGUI7ImpExp                 void *GetPrev (CLPosition &rCLPosition );
public     :         OGUI7ImpExp                 logical GetPrevPosition (CLPosition &rCLPosition );
public     :                                     logical GetTailPosition (CLPosition &rCLPosition );
public     :         OGUI7ImpExp                 logical InsertAt (void *pitem, CLPosition &rCLPosition );
protected  :                                     void *MakeCluster ( );
protected  : virtual OGUI7ImpExp                 void OnDeleteItem (void *pitem, logical fFree=NO );
protected  : virtual OGUI7ImpExp                 void OnInsertItem (void *pitem );
public     :                                                             ~ClusteredList ( );
};

#pragma pack()
#endif
