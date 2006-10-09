/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODSList

\brief    


\date     $Date: 2006/08/03 18:57:11,32 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODSList"

#include  <pogui7.h>
#ifndef   DLL_ODSList_HPP
#define   DLL_ODSList_HPP
#include  <sODSList.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_OListLayout_HPP
#define   DLL_OListLayout_HPP
#include  <sOListLayout.hpp>
#include  <sDLL.h>
#endif
#include  <sODS.hpp>
#include  <sODSList.hpp>
#include  <sODSRegion.hpp>
#include  <sODSTree.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHControlData.hpp>
#include  <sOEHDataWidget.hpp>
#include  <sOFont.hpp>
#include  <sOListLayout.hpp>
#include  <sODSList.hpp>


/******************************************************************************/
/**
\brief  Activate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

void ODSList :: Activate ( )
{
  ODSList        *col;
  SetActive(YES);
    
  if ( columns )
  {
    columns->GoTop();
    while ( col = columns->GetNext() )
      col->Activate(); 
  }

  stssini();

}

/******************************************************************************/
/**
\brief  BlockSignals - 




\param  block_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BlockSignals"

void ODSList :: BlockSignals (logical block_opt )
{
  ODSList        *col = NULL;
  ODS::BlockSignals(block_opt);  
  
  if ( columns )
  {
    columns->GoTop();
    while ( col = columns->GetNext() )
      col->BlockSignals(block_opt); 
  }

}

/******************************************************************************/
/**
\brief  Clear - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Clear"

void ODSList :: Clear ( )
{
  ODSList        *olist;
  if ( columns )
  {
    columns->GoTop();
    while ( olist = columns->RemoveTail() )
      delete olist;
  }

}

/******************************************************************************/
/**
\brief  Column - 



\return pODSList - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Column"

ODSList *ODSList :: Column (int column )
{
  ODSList       *pODSList = NULL;
  ODSList       *col;
  int32          idx = 0;
BEGINSEQ
  if ( !columns || column < 0 )                          ERROR

  columns->GoTop();
  while ( col = columns->GetNext() )
  {
    if ( !col->get_columns() || col->get_columns()->GetCount() <= 0 )
    {
      if ( idx == column )  
      {
        pODSList = col;
        LEAVESEQ
      }
      idx++;
    }
    else
    {
      if ( pODSList = col->Column(column-idx) )       LEAVESEQ
      if ( (idx += col->ColumnCount()) > column )     ERROR
    }
  }
RECOVER

ENDSEQ
  return(pODSList);
}

/******************************************************************************/
/**
\brief  ColumnCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColumnCount"

int32 ODSList :: ColumnCount ( )
{
  ODSList       *col       = NULL;
  int32          sub_count = 0;
  int32          count     = 0;

BEGINSEQ
  if ( !this || !columns )                            LEAVESEQ
    
  columns->GoTop();
  while ( col = columns->GetNext() )
    if ( sub_count = col->ColumnCount() )
      count += sub_count;
    else
      count++;
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  Deactivate - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

void ODSList :: Deactivate ( )
{
  ODSList        *col;
  if ( columns )
  {
    columns->GoTop();
    while ( col = columns->GetNext() )
      col->Deactivate(); 
  }

  SetActive(NO);

}

/******************************************************************************/
/**
\brief  GetBackgroundColor - 



\return pQColor - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBackgroundColor"

QColor *ODSList :: GetBackgroundColor ( )
{

  return ( this ? layout->GetBackgroundColor() : NULL );

}

/******************************************************************************/
/**
\brief  GetFont - 



\return pQFont - QT - Font

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFont"

QFont *ODSList :: GetFont ( )
{

  return ( this ? layout->GetFont() : NULL );

}

/******************************************************************************/
/**
\brief  GetHelp - 



\return szText - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHelp"

char *ODSList :: GetHelp ( )
{

  return ( this ? layout->GetHelp() : NULL);

}

/******************************************************************************/
/**
\brief  GetIcon - 



\return pQIcon - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIcon"

QIcon *ODSList :: GetIcon ( )
{

  return ( this ? layout->GetIcon() : NULL );

}

/******************************************************************************/
/**
\brief  GetStaticText - 



\return szText - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStaticText"

char *ODSList :: GetStaticText ( )
{

  return ( this ? layout->GetStaticText() : NULL);

}

/******************************************************************************/
/**
\brief  GetTextColor - 



\return pQColor - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextColor"

QColor *ODSList :: GetTextColor ( )
{

  return ( this ? layout->GetTextColor() : NULL );

}

/******************************************************************************/
/**
\brief  GetToolTip - 



\return szText - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetToolTip"

char *ODSList :: GetToolTip ( )
{

  return ( this ? layout->GetToolTip() : NULL);

}

/******************************************************************************/
/**
\brief  ListODS - 



\return pODSList - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListODS"

ODSList *ODSList :: ListODS ( )
{

  return(this);

}

/******************************************************************************/
/**
\brief  ODSList - 



\return term - 

\param  col_pos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODSList"

     ODSList :: ODSList (int16 col_pos )
                     : ODS(),
bsts (),
  layout(NULL),
  columns(NULL),
  data_widget(NULL),
  pos(col_pos)

{



}

/******************************************************************************/
/**
\brief  RemoveDataWidget - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveDataWidget"

void ODSList :: RemoveDataWidget ( )
{
  ODSRegion   *reg;
BEGINSEQ
  if ( !data_widget )                                LEAVESEQ
  
  if ( !(reg = RegionODS()) || reg != reg->get_tree() )
    delete data_widget;
  data_widget = NULL;

ENDSEQ

}

/******************************************************************************/
/**
\brief  ResetChildStates - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetChildStates"

void ODSList :: ResetChildStates ( )
{
  ODSList        *col = NULL;
  if ( columns )
  {
    columns->GoTop();
    while ( col = columns->GetNext() )
      col->ResetStates(); 
  }

}

/******************************************************************************/
/**
\brief  ResetStates - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetStates"

void ODSList :: ResetStates ( )
{

  SetItemState();
  ResetChildStates();


}

/******************************************************************************/
/**
\brief  SetControlData - 




\param  pOEHControlData - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetControlData"

void ODSList :: SetControlData (OEHControlData *pOEHControlData )
{

  data_widget = pOEHControlData;

}

/******************************************************************************/
/**
\brief  SetDataWidget - 



\return term - 

\param  pOEHControlData - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataWidget"

logical ODSList :: SetDataWidget (OEHControlData *pOEHControlData )
{
  logical                 term = NO;
  data_widget = pOEHControlData;
  return(term);
}

/******************************************************************************/
/**
\brief  SetLayout - 



\return term - 

\param  pOListLayout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLayout"

logical ODSList :: SetLayout (OListLayout *pOListLayout )
{
  OListLayout            *ll;
  ODSList                *ol;
  int16                   col_no = 0;
  logical                 term = NO;
  Clear();
  
  if ( !(layout = pOListLayout) )
    SetPath(NULL,PT_undefined);
  else
  {
    SetPath(*layout);
    
    if ( layout->get_columns() )
    {
      DLL(OListLayout) cursor(*layout->get_columns());
      if ( cursor.GetCount() > 0 )
      {
        if ( !columns )
          columns = new DLL(ODSList);
        cursor.GoTop();
        while ( ll = cursor.GetNext() )
        {
          ol = new ODSList(col_no);
          ol->SetLayout(ll);
          ol->SetParentODS(this);
          ol->SetActive(YES);
          columns->AddTail(ol);
          col_no++;
        }
      }
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  ~ODSList - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODSList"

     ODSList :: ~ODSList ( )
{

  RemoveDataWidget();
  
  Clear();
  
  delete columns;
  columns = NULL;

}


