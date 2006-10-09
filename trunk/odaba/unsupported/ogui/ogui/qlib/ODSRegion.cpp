/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODSRegion

\brief    


\date     $Date: 2006/08/26 17:48:26,92 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODSRegion"

#include  <pogui7.h>
#include  <mODSRegion.h>
#ifndef   DLL_ODSRegion_HPP
#define   DLL_ODSRegion_HPP
#include  <sODSRegion.hpp>
#include  <sDLL.h>
#endif
#include  <cItemCandidateTypes.h>
#include  <sODSItem.hpp>
#include  <sODSPropPath.hpp>
#include  <sODSRegion.hpp>
#include  <sODSTree.hpp>
#include  <sOFont.hpp>
#include  <sOListCtl.hpp>
#include  <sOListLayout.hpp>
#include  <sOTreeLayout.hpp>
#include  <sPropertyHandle.hpp>
#include  <sODSRegion.hpp>


/******************************************************************************/
/**
\brief  Activate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

void ODSRegion :: Activate ( )
{
  logical          ini = stscini();
  ODSRegion       *reg;
  if ( !ini )
  {
    connect(this,SIGNAL(OnInstanceInserted()),this,SLOT(slotInstanceInserted()));
    connect(this,SIGNAL(OnInstanceRemoved()),this,SLOT(slotInstanceRemoved()));
    connect(this,SIGNAL(OnInstanceUpdated()),this,SLOT(slotInstanceUpdated()));
    connect(this,SIGNAL(OnInstanceSelected()),this,SLOT(slotInstanceSelected()));
    
    connect(this,SIGNAL(OnCollectionUpdated()),this,SLOT(slotCollectionChanged()));
    connect(this,SIGNAL(OnCollectionChanged()),this,SLOT(slotCollectionChanged()));//,SLOT(doColOpened()));
    connect(this,SIGNAL(OnCollectionReset()),this,SLOT(slotCollectionReset()));
  }
  ODSList::Activate();
  
  if ( sub_regions )
  {
    sub_regions->GoTop();
    while ( reg = sub_regions->GetNext() )
      reg->Activate(); 
  }



}

/******************************************************************************/
/**
\brief  BlockSignals - 




\param  block_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BlockSignals"

void ODSRegion :: BlockSignals (logical block_opt )
{
  ODSRegion       *reg = NULL;
  ODSList::BlockSignals(block_opt);
  
  if ( sub_regions )
  {
    sub_regions->GoTop();
    while ( reg = sub_regions->GetNext() )
      reg->BlockSignals(block_opt); 
  }

}

/******************************************************************************/
/**
\brief  Clear - 




\param  reset_columns - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void ODSRegion :: Clear (logical reset_columns )
{
  ODSRegion          *reg;
  sub_regions_initialized = NO; 

  if ( sub_regions )
  {
    while ( reg = sub_regions->RemoveTail() )
      delete reg;
  }  
  
  if ( reset_columns )
    ODSList::Clear();

}

/******************************************************************************/
/**
\brief  Deactivate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

void ODSRegion :: Deactivate ( )
{
  ODSRegion       *reg;
  ODSList::Deactivate();
  
  if ( sub_regions )
  {
    sub_regions->GoTop();
    while ( reg = sub_regions->GetNext() )
      reg->Deactivate(); 
  }

}

/******************************************************************************/
/**
\brief  GetLayout - 



\return pOTreeLayout - Tree layout definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLayout"

OTreeLayout *ODSRegion :: GetLayout ( )
{

  return ( (OTreeLayout *)layout );

}

/******************************************************************************/
/**
\brief  GetPropertyHandle - 



\return prop_hdl - 

\param  pODSPropPath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPropertyHandle"

PropertyHandle *ODSRegion :: GetPropertyHandle (ODSPropPath *pODSPropPath )
{
  int                     ireg = 0;
  ODSRegion              *reg  = NULL;
  PropertyHandle         *prop_hdl = NULL;
  if ( layout == pODSPropPath )
    prop_hdl = Handle();
  else
    while( reg = Region(ireg++) )
      if ( prop_hdl = reg->GetPropertyHandle(pODSPropPath) )
        break;

  return(prop_hdl);
}

/******************************************************************************/
/**
\brief  HasData - Enthält die ODS Hierarchie wenigstens eine Instanz?



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasData"

logical ODSRegion :: HasData ( )
{
  ODSRegion     *reg;
  int            ireg = 0;
  logical        cond = YES;
BEGINSEQ
  if ( ColGetCount() > 0 )                           LEAVESEQ
    
  while ( reg = Region(ireg++) )
    if ( reg->HasData() )                            LEAVESEQ

  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  HasSubRegions - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasSubRegions"

logical ODSRegion :: HasSubRegions ( )
{

  return (   this && sub_regions && sub_regions->GetCount() > 0  
           ? YES 
           : NO );


}

/******************************************************************************/
/**
\brief  ODSRegion - 



\return term - 

\param  pODSTree - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSRegion"

     ODSRegion :: ODSRegion (ODSTree *pODSTree )
                     : ODSList(0),
  tree(pODSTree),
  sub_regions(NULL),
  sub_regions_initialized(NO),
  dirty(YES)

{





}

/******************************************************************************/
/**
\brief  ParentRegion - 



\return reg - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParentRegion"

ODSRegion *ODSRegion :: ParentRegion ( )
{

  return (   (ODSRegion *)tree != this 
           ? (ODSRegion *)parentODS
           : NULL  );

}

/******************************************************************************/
/**
\brief  i1 - 



\param  searchRegion - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ParentRegion"

ODSRegion *ODSRegion :: ParentRegion (ODSRegion *searchRegion )
{
  ODSRegion    *child   = NULL;
  ODSRegion    *parent  = NULL;
  int           index0  = 0;
  

BEGINSEQ
  while ( child = Region(index0++) )
  {
    parent = this;
    if ( child == searchRegion )                       LEAVESEQ
    if ( parent = child->ParentRegion(searchRegion) )  LEAVESEQ
  }

  ERROR
RECOVER
  parent = NULL;
ENDSEQ
  return(parent);
}

/******************************************************************************/
/**
\brief  RefreshRegion - 



\return term - 

\param  region_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RefreshRegion"

logical ODSRegion :: RefreshRegion (int32 region_id )
{
  ODSRegion             *sub_reg;
  logical                term = NO;
  if ( !region_id || layout->get_intern_id() == region_id )
    SetLayout();
  else  
//if ( region_id )
  {
    sub_regions->GoTop();
    while ( sub_reg = sub_regions->GetNext() )
      sub_reg->RefreshRegion(region_id);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Region - 



\return pODSRegion - 

\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Region"

ODSRegion *ODSRegion :: Region (int index )
{

  return (sub_regions ? sub_regions->GetObjectInst(index) : NULL);

}

/******************************************************************************/
/**
\brief  RegionODS - 



\return pODSRegion - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegionODS"

ODSRegion *ODSRegion :: RegionODS ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  RemoveRegion - 




\param  parent_id - 
\param  region_id - 
\param  reset_columns - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveRegion"

void ODSRegion :: RemoveRegion (int32 parent_id, int32 region_id, logical reset_columns )
{
  ODSRegion           *reg;
  if ( !region_id ) 
    Clear(reset_columns);
  else if ( sub_regions )
  {
    sub_regions->GoTop();
    while ( reg = sub_regions->GetNext() )
    {
      if ( reg->GetLayout()->get_intern_id() == region_id )
      {
        sub_regions->RemoveAt();
        delete reg;
      }
    }
  }  


}

/******************************************************************************/
/**
\brief  ResetChildStates - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetChildStates"

void ODSRegion :: ResetChildStates ( )
{
  ODSRegion  *reg = NULL;
  if ( sub_regions )
  {
    sub_regions->GoTop();
    while ( reg = sub_regions->GetNext() )
      reg->ResetStates(); 
  }

}

/******************************************************************************/
/**
\brief  ResetStates - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetStates"

void ODSRegion :: ResetStates ( )
{

  ODSList::ResetStates();
  ResetChildStates();

}

/******************************************************************************/
/**
\brief  SetFilter - 



\return term - 

\param  expression - 
\param  enable_opt - Enable option
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilter"

logical ODSRegion :: SetFilter (char *expression, logical enable_opt )
{
  OListCtl     *list = tree ? tree->GetListControl() : NULL;
  logical       term = NO;
  term = ODSList::SetFilter(expression,enable_opt);
  
  if ( list )
    list->get_listCache().FilterChanged(this);
  return(term);
}

/******************************************************************************/
/**
\brief  SetLayout - 



\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pOTreeLayout - Tree layout definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLayout"

logical ODSRegion :: SetLayout (OTreeLayout *pOTreeLayout )
{
  logical                 term = NO;
BEGINSEQ
  ODSList::SetLayout(pOTreeLayout);

  if ( SetupLayout() )                               ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLayout"

logical ODSRegion :: SetLayout ( )
{
  OTreeLayout       *olayout = GetLayout();
  logical            term = NO;
BEGINSEQ
  Clear(YES);
  if ( SetLayout(olayout) )                          ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupLayout - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupLayout"

logical ODSRegion :: SetupLayout ( )
{
  OTreeLayout            *my_tl;
  OTreeLayout            *tl;
  ODSRegion              *reg;
  logical                 term = NO;
BEGINSEQ
  if ( sub_regions_initialized )                     LEAVESEQ
  sub_regions_initialized = YES; 
  
  if ( !layout )                                     LEAVESEQ
    
  my_tl = (OTreeLayout *)layout;
     
  if ( my_tl->get_regions() )
  {
    DLL(OTreeLayout)  cursor(*my_tl->get_regions());
    if ( cursor.GetCount() > 0 )
    {
      if ( !sub_regions )
        sub_regions = new DLL(ODSRegion);
      cursor.GoTop();
      while ( tl = cursor.GetNext() )
      {
        if ( !tl->get_columns() )
          tl->CopyColumns(my_tl);
        reg = new ODSRegion(tree);
        reg->SetParentODS(this);
        reg->SetActive(YES);
//      reg->ODSList::SetLayout(tl);
//j 051201 directory.files.tags
        if ( !tl->IsRecursive() )
          reg->SetLayout(tl);
        sub_regions->AddTail(reg);
      }
    }
  }


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateTreeLayout - 



\return term - 

\param  tree_layout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateTreeLayout"

logical ODSRegion :: UpdateTreeLayout (OTreeLayout *tree_layout )
{
  ODSRegion              *reg;
  logical                 term = NO;
  if ( tree_layout->get_intern_id() == layout->get_intern_id() )
  {
    Clear(YES);
    SetLayout(tree_layout);
  }
  else if ( sub_regions )
  {
    sub_regions->GoTop();
    while ( reg = sub_regions->GetNext() )
      reg->UpdateTreeLayout(tree_layout); 
  }
  return(term);
}

/******************************************************************************/
/**
\brief  set_dirty - sets the dirty variable




\param  bdirty - 
\param  brecursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_dirty"

void ODSRegion :: set_dirty (logical bdirty, logical brecursive )
{
  ODSRegion  *reg = NULL;
  if ( brecursive && sub_regions)
  {
    sub_regions->GoTop();
    while ( reg = sub_regions->GetNext() )
      reg->set_dirty(bdirty,brecursive);
  }
    
  dirty = bdirty;

}

/******************************************************************************/
/**
\brief  slotCollectionChanged - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotCollectionChanged"

void ODSRegion :: slotCollectionChanged ( )
{
  OListCtl  *list = tree ? tree->GetListControl() : NULL;

  if ( list && tree == this )
  {
    list->ListChanged(YES);
    list->updateSelection();
  }

}

/******************************************************************************/
/**
\brief  slotCollectionReset - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotCollectionReset"

void ODSRegion :: slotCollectionReset ( )
{
  OListCtl  *list = tree ? tree->GetListControl() : NULL;

  if ( list && tree == this )
    list->ListReset();
  


}

/******************************************************************************/
/**
\brief  slotInstanceInserted - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotInstanceInserted"

void ODSRegion :: slotInstanceInserted ( )
{
  OListCtl  *list      = tree ? tree->GetListControl() : NULL;
  ItemData  *new_item  = NULL;
BEGINSEQ
  if ( !list )                                       ERROR
    
  if ( new_item = list->get_listCache().InsertItem(this) )
  {  
    list->FlushEventCache();
    list->SetCurrentItem(new_item);
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  slotInstanceRemoved - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotInstanceRemoved"

void ODSRegion :: slotInstanceRemoved ( )
{
  OListCtl  *list      = tree ? tree->GetListControl() : NULL;
  ItemData  *next_item = NULL;
BEGINSEQ
  if ( !list )                                       ERROR
    
  if ( next_item = list->get_listCache().RemoveItem(this,lastObjID) )
  {  
    list->FlushEventCache();
    list->SetCurrentItem(next_item);
  }
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  slotInstanceSelected - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotInstanceSelected"

void ODSRegion :: slotInstanceSelected ( )
{
  OListCtl    *list      = tree ? tree->GetListControl() : NULL;
  int32        objid     = Item()->GetLastObjID();
  ItemData    *pItemData = NULL;
BEGINSEQ
  if ( !list || objid <= 0 )                          LEAVESEQ
    
// hier ev. doch provide = YES, aber nicht fuer uebergeordnete level  
  
  if ( pItemData = list->get_listCache().ItemByLOID(this,objid,NO) )
    list->SetCurrentItem(pItemData);
ENDSEQ

}

/******************************************************************************/
/**
\brief  slotInstanceUpdated - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotInstanceUpdated"

void ODSRegion :: slotInstanceUpdated ( )
{
  OListCtl    *list      = tree ? tree->GetListControl() : NULL;
  int32        objid     = Item()->GetLastObjID();
  ItemData    *pItemData = NULL;

BEGINSEQ
  if ( !list || objid <= 0 )                          LEAVESEQ
    
  if ( pItemData = list->get_listCache().ItemByLOID(this,objid,NO) )
  {
    pItemData->Setup();
    list->get_listCache().UpdateData(pItemData,NULL);
  }
ENDSEQ

}

/******************************************************************************/
/**
\brief  ~ODSRegion - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODSRegion"

     ODSRegion :: ~ODSRegion ( )
{
  ODSRegion       *reg;
  Clear(YES);
    
  RemoveDataWidget();

}


