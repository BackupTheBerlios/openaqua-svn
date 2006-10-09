/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OListLayout

\brief    


\date     $Date: 2006/08/24 14:56:37,95 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OListLayout"

#include  <pogui7.h>
#ifndef   DLL_OListLayout_HPP
#define   DLL_OListLayout_HPP
#include  <sOListLayout.hpp>
#include  <sDLL.h>
#endif
#include  <sDPixmap.hpp>
#include  <sOFont.hpp>
#include  <sOIconSet.hpp>
#include  <sOPixmap.hpp>
#include  <sOTreeLayout.hpp>
#include  <sOListLayout.hpp>


/******************************************************************************/
/**
\brief  AddColumn - 



\return pOListLayout - 
-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddColumn"

OListLayout *OListLayout :: AddColumn ( )
{
  OListLayout   *new_col = NULL;
  SetDirty();
  if ( !columns )
    columns = new DLL(OListLayout);
    
  new_col = new OListLayout(this);
  columns->AddTail(new_col);
  new_col->set_intern_id(GetTreeLayout()->IncreaseID());
  
// should emit slotLayoutChanged();
  return(new_col);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  prop_path - Property path
\param  strname - 
\param  is_collection - Is referenced path pointing to a collection
\param  sort_index_name - 
\param  prop_type - Property path  type
\param  accmode_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddColumn"

OListLayout *OListLayout :: AddColumn (char *prop_path, char *strname, logical is_collection, char *sort_index_name, ODSPropertyType prop_type, PIACC accmode_w )
{
  OListLayout   *pOListLayout = NULL;
BEGINSEQ
  if ( !(pOListLayout = AddColumn()) )                  ERROR
  
  pOListLayout->SetPath(prop_path,strname,is_collection,
                        sort_index_name,prop_type,accmode_w);
RECOVER

ENDSEQ
  return(pOListLayout);
}

/******************************************************************************/
/**
\brief  Column - 



\return pOListLayout - 

\param  column - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Column"

OListLayout *OListLayout :: Column (int column )
{
  OListLayout   *pOListLayout = NULL;
  OListLayout   *col;
  int32          idx = AUTO;
BEGINSEQ
  if ( !columns || column < 0 )                          ERROR

  columns->GoTop();
  while ( col = columns->GetNext() )
  {
    idx++;
    if ( !col->get_columns() || col->get_columns()->GetCount() <= 0 )
    {
      if ( idx == column )  
      {
        pOListLayout = col;
        LEAVESEQ
      }
    }
    else
    {
      if ( pOListLayout = col->Column(column-idx) )   LEAVESEQ
      if ( (idx += col->ColumnCount()-1) < column )   ERROR
    }

  }
RECOVER
  pOListLayout = NULL;
ENDSEQ
  return(pOListLayout);
}

/******************************************************************************/
/**
\brief  ColumnCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ColumnCount"

int32 OListLayout :: ColumnCount ( )
{
  OListLayout   *col   = NULL;
  int32          count = 0;
BEGINSEQ
  if ( !columns )                                    ERROR
    
  columns->GoTop();
  while ( col = columns->GetNext() )
    count += col->ColumnCount();

  if ( count <= 0 )
    count = 1;
RECOVER

ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  Copy - 



\return term - 

\param  list_layout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical OListLayout :: Copy (OListLayout *list_layout )
{
  logical                 term = NO;
BEGINSEQ
  if ( !list_layout )                                ERROR
    
  SetPath(*list_layout);
    
  parent         = list_layout->get_parent();
  intern_id      = list_layout->get_intern_id();
  width          = list_layout->get_width();
  widthGrowRate  = list_layout->get_widthGrowRate();
  height         = list_layout->get_height();
  heightGrowRate = list_layout->get_heightGrowRate();
  header_width   = list_layout->get_header_width();
  header_height  = list_layout->get_header_height();
  
  CopyColumns(list_layout);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyColumns - 



\return term - 

\param  list_layout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyColumns"

logical OListLayout :: CopyColumns (OListLayout *list_layout )
{
  OListLayout   *column = NULL;
  logical        term   = NO;
BEGINSEQ
  if ( !list_layout )                                ERROR
  if ( !list_layout->get_columns() )                 LEAVESEQ
    
  if ( !columns )
    columns = new DLL(OListLayout);
  
  list_layout->get_columns()->GoTop();
  while ( column = list_layout->get_columns()->GetNext() )
    columns->AddTail(new OListLayout(*column));
  
  SetDirty();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DisplayHeader - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayHeader"

logical OListLayout :: DisplayHeader ( )
{
  OListLayout  *column = NULL;
  logical       cond   = YES;
BEGINSEQ
  if ( !this || !columns )                           ERROR

  columns->GoTop();
  while ( column = columns->GetNext() )
    if ( (column->get_szStaticText() && *column->get_szStaticText()) ||
         column->DisplayHeader() )                   LEAVESEQ

  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  FindColumn - 



\return pOListLayout - 

\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindColumn"

OListLayout *OListLayout :: FindColumn (int32 column_id )
{
  OListLayout         *column = NULL;
BEGINSEQ
  columns->GoTop();
  if ( columns )
    while ( column = columns->GetNext() )
      if ( column->intern_id == column_id )         
        LEAVESEQ

ENDSEQ
  return(column);
}

/******************************************************************************/
/**
\brief  GetStaticText - 



\return szText - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStaticText"

char *OListLayout :: GetStaticText ( )
{

  return ( this ? szStaticText : NULL );

}

/******************************************************************************/
/**
\brief  GetTreeLayout - 



\return pOTreeLayout - Tree layout definition

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTreeLayout"

OTreeLayout *OListLayout :: GetTreeLayout ( )
{

  return( this && parent ? parent->GetTreeLayout() : NULL);

}

/******************************************************************************/
/**
\brief  OListLayout - 



-------------------------------------------------------------------------------
\brief  i0 - 



\param  pOListLayout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OListLayout"

     OListLayout :: OListLayout (OListLayout *pOListLayout )
                     : ODSPropPath (),
ODataLayoutRef(YES),
  parent(pOListLayout),
  intern_id(0),
  columns(NULL),
  width(AUTO),
  widthGrowRate(1),
  height(AUTO),
  heightGrowRate(1),
  header_width(AUTO),
  header_height(AUTO),
  szStaticText(NULL)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  rcOListLayout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OListLayout"

     OListLayout :: OListLayout (const OListLayout &rcOListLayout )
                     : ODSPropPath (),
ODataLayoutRef(YES),
  parent(NULL),
  intern_id(0),
  columns(NULL),
  width(AUTO),
  widthGrowRate(1),
  height(AUTO),
  heightGrowRate(1),
  header_width(AUTO),
  header_height(AUTO),
  szStaticText(NULL)
{

  Copy((OListLayout *)&rcOListLayout);

}

/******************************************************************************/
/**
\brief  i02 - 



\param  pOListLayout - 
\param  prop_path - Property path
\param  col_width - 
\param  grow_rate - 
\param  prop_type - Property path  type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OListLayout"

     OListLayout :: OListLayout (OListLayout *pOListLayout, char *prop_path, int32 col_width, int32 grow_rate, ODSPropertyType prop_type )
                     : ODSPropPath (),
ODataLayoutRef(YES),
  parent(pOListLayout),
  intern_id(0),
  columns(NULL),
  width(col_width),
  widthGrowRate(grow_rate),
  height(AUTO),
  heightGrowRate(1),
  header_width(AUTO),
  header_height(AUTO),
  szStaticText(NULL)
{

  SetPath(prop_path,prop_type);

}

/******************************************************************************/
/**
\brief  i03 - 



\param  pOListLayout - 
\param  oprop_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OListLayout"

     OListLayout :: OListLayout (OListLayout *pOListLayout, ODSPropPath *oprop_path )
                     : ODSPropPath (*oprop_path),
ODataLayoutRef(YES),
  parent(pOListLayout),
  intern_id(0),
  columns(NULL),
  width(AUTO),
  widthGrowRate(1),
  height(AUTO),
  heightGrowRate(1),
  header_width(AUTO),
  header_height(AUTO),
  szStaticText(NULL)
{



}

/******************************************************************************/
/**
\brief  RemoveColumn - 



\return term - 

\param  column_id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveColumn"

logical OListLayout :: RemoveColumn (int32 column_id )
{
  OListLayout         *column = FindColumn(column_id);
  logical              term = NO;
BEGINSEQ
  SetDirty();
  if ( !column )                                    ERROR

  columns->Remove(column);
  delete column;


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveColumns - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveColumns"

void OListLayout :: RemoveColumns ( )
{
  OListLayout         *column;

  if ( columns )
  {
    while ( column = columns->RemoveTail() )
      delete column;
    
    delete columns;
    columns = NULL;
  }


}

/******************************************************************************/
/**
\brief  SetDirty - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDirty"

void OListLayout :: SetDirty ( )
{

  GetTreeLayout()->TopRegion()->set_dirty();

}

/******************************************************************************/
/**
\brief  SetFont - 



\return term - 

\param  pDFont - 
\param  column_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFont"

logical OListLayout :: SetFont (DFont *pDFont, int column_w )
{
  OListLayout   *layout = this;
  logical        term   = NO;
BEGINSEQ
  if ( column_w < 0 )
    SetLayout(pDFont);
  else
  {
    if ( !(layout = Column(column_w)) )              OGUIERR(99)
    term = layout->SetFont(pDFont,AUTO);
  }
  SetDirty();    // kann vielleicht weg

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetHeaderSize - 




\param  col_width - 
\param  col_height - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHeaderSize"

void OListLayout :: SetHeaderSize (int32 col_width, int32 col_height )
{

  header_width  = col_width;
  header_height = col_height;




}

/******************************************************************************/
/**
\brief  SetHeight - 




\param  col_height - 
\param  grow_rate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHeight"

void OListLayout :: SetHeight (int32 col_height, int32 grow_rate )
{

  height         = col_height;
  heightGrowRate = grow_rate;  



}

/******************************************************************************/
/**
\brief  SetStaticText - 




\param  szText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetStaticText"

void OListLayout :: SetStaticText (char *szText )
{

BEGINSEQ
  if ( !szText )                                     ERROR
  if ( !(szStaticText = strdup(szText)) )            ERROR
  
  SetDirty();

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetWidth - 




\param  col_width - 
\param  grow_rate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWidth"

void OListLayout :: SetWidth (int32 col_width, int32 grow_rate )
{

  width         = col_width;
  widthGrowRate = grow_rate;  



}

/******************************************************************************/
/**
\brief  set_intern_id - 




\param  id - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_intern_id"

void OListLayout :: set_intern_id (int id )
{

  GetTreeLayout()->SetupLastID(intern_id = id);

}

/******************************************************************************/
/**
\brief  set_parent - 




\param  list_layout - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_parent"

void OListLayout :: set_parent (OListLayout *list_layout )
{

  parent = list_layout;

}

/******************************************************************************/
/**
\brief  xx_Paint - 




\param  rcOListLayoutPS - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xx_Paint"

void OListLayout :: xx_Paint (const char &rcOListLayoutPS ) const
{

//  PaintChildren(rcOListLayoutPS,rcOListLayoutPS.rect.width());

}

/******************************************************************************/
/**
\brief  ~OListLayout - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OListLayout"

     OListLayout :: ~OListLayout ( )
{
  OListLayout         *column;
// war von OListLayoutItem und ...s abgeleitet
  RemoveColumns();
  
  if ( szStaticText )
  {
    free(szStaticText);
    szStaticText = NULL;
  }



}


