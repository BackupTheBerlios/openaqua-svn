/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODSTree

\brief    


\date     $Date: 2006/03/13 21:35:30,20 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODSTree"

#include  <pogui7.h>
#include  <mODSTree.h>
#include  <sItemData.hpp>
#include  <sODSItem.hpp>
#include  <sODSRegion.hpp>
#include  <sODSTreeHandler.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHControlData.hpp>
#include  <sOEHControlList.hpp>
#include  <sOEHDataWidget.hpp>
#include  <sOListCtl.hpp>
#include  <sOTreeLayout.hpp>
#include  <sODSTree.hpp>


/******************************************************************************/
/**
\brief  AfterDataFill - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AfterDataFill"

void ODSTree :: AfterDataFill ( )
{

  GetListControl()->GenerateEvent(DEV_Filled);

}

/******************************************************************************/
/**
\brief  AfterDataSet - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AfterDataSet"

void ODSTree :: AfterDataSet ( )
{

  GetListControl()->GenerateEvent(DEV_AfterDataSet);

}

/******************************************************************************/
/**
\brief  BeforeDataFill - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BeforeDataFill"

logical ODSTree :: BeforeDataFill ( )
{
  logical    term = NO;
  emit OnBeforeDataFill(&term);
  
  if ( !term )
    term =   GetListControl()->GenerateEvent(DEV_Fill) == YES 
           ? YES 
           : NO;
  return(term);
}

/******************************************************************************/
/**
\brief  BeforeDataSet - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BeforeDataSet"

logical ODSTree :: BeforeDataSet ( )
{
  logical     term = NO;
  emit OnBeforeDataSet(&term);
  
  if ( !term )
    term =   GetListControl()->GenerateEvent(DEV_BeforeDataSet) == YES
           ? YES 
           : NO;
  return(term);
}

/******************************************************************************/
/**
\brief  GetListControl - 


\return pOListCtl -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetListControl"

OListCtl *ODSTree :: GetListControl ( ) const
{

  return(   this && handler 
          ? handler->GetListControl() 
          : NULL );

}

/******************************************************************************/
/**
\brief  IsCurItem

\return cond -

\param  pItemData - ItemData
\param  recursive -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsCurItem"

logical ODSTree :: IsCurItem (ItemData *pItemData, logical recursive )
{

  return ( GetListControl()->IsCurItem(pItemData,recursive) );

}

/******************************************************************************/
/**
\brief  IsItemExpanded

\return cond -

\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsItemExpanded"

logical ODSTree :: IsItemExpanded (ItemData *pItemData )
{
  OListCtl   *list_ctl = GetListControl();
  return (   list_ctl 
           ? list_ctl->IsItemExpanded(pItemData)
           : NO );

}

/******************************************************************************/
/**
\brief  ODSTree - 


-------------------------------------------------------------------------------
\brief  i0


\param  pOEHControlData -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSTree"

                        ODSTree :: ODSTree (OEHControlData *pOEHControlData )
                     : ODSRegion (this),
  handler(NULL)
{

  data_widget = pOEHControlData;

}

/******************************************************************************/
/**
\brief  i01


\param  pOEHControlData -
\param  pOTreeLayout - Tree layout definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSTree"

                        ODSTree :: ODSTree (OEHControlData *pOEHControlData, OTreeLayout *pOTreeLayout )
                     : ODSRegion (this),
  handler(NULL)
{

  data_widget = pOEHControlData;

  SetLayout(pOTreeLayout);

}

/******************************************************************************/
/**
\brief  ResetCurItem - 



\param  pItemData - ItemData
\param  recursive -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetCurItem"

void ODSTree :: ResetCurItem (ItemData *pItemData, logical recursive )
{

  if ( IsCurItem(pItemData,recursive) )
    SetCurItem(NULL);

}

/******************************************************************************/
/**
\brief  SetCurItem - 



\param  pItemData - ItemData
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCurItem"

void ODSTree :: SetCurItem (ItemData *pItemData )
{

  GetListControl()->set_cur_item(pItemData);

}

/******************************************************************************/
/**
\brief  SetHandler - 



\param  pODSTreeHandler -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHandler"

void ODSTree :: SetHandler (ODSTreeHandler *pODSTreeHandler )
{

  handler = pODSTreeHandler;

}

/******************************************************************************/
/**
\brief  SetLastID - 



\param  inst_id -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastID"

void ODSTree :: SetLastID (int32 inst_id )
{

  GetListControl()->SetLastID(inst_id);


}

/******************************************************************************/
/**
\brief  ~ODSTree - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODSTree"

                        ODSTree :: ~ODSTree ( )
{



}


