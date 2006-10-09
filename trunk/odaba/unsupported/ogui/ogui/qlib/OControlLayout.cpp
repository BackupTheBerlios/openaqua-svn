/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OControlLayout

\brief    Controls the Layout of items


\date     $Date: 2006/03/13 21:35:13,73 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OControlLayout"

#include  <pogui7.h>
#include  <cADK_HoriPos.h>
#include  <cADK_VertPos.h>
#include  <sODataWidget.hpp>
#include  <sOHorLayout.hpp>
#include  <sOVerLayout.hpp>
#include  <sOControlLayout.hpp>


/******************************************************************************/
/**
\brief  OControlLayout - Konstruktor



\param  pODataWidget - Parent data widget
\param  margin_pix -
\param  space_pix -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OControlLayout"

                        OControlLayout :: OControlLayout (ODataWidget *pODataWidget, int32 margin_pix, int32 space_pix )
                     : QGridLayout (pODataWidget->WidgetQ()),
  top_layout(NULL),
  bottom_layout(NULL),
  left_layout(NULL),
  right_layout(NULL),
  corner_layout(),
  spacing(space_pix)
{

  memset(corner_layout,0,sizeof(corner_layout));
  
  setSpacing(space_pix);
  setMargin(margin_pix);
  
  spacer_items[1] = new QSpacerItem(0,0,QSizePolicy::Fixed,QSizePolicy::Fixed);
  addItem(spacer_items[1],1,0,1,5);         // top

  spacer_items[0] = new QSpacerItem(0,0,QSizePolicy::Fixed,QSizePolicy::Fixed);
  addItem(spacer_items[0],0,1,5,1);         // left

  spacer_items[3] = new QSpacerItem(0,0,QSizePolicy::Fixed,QSizePolicy::Fixed);
  addItem(spacer_items[3],3,0,1,5);         // bottom
  
  spacer_items[2] = new QSpacerItem(0,0,QSizePolicy::Fixed,QSizePolicy::Fixed);
  addItem(spacer_items[2],0,3,5,1);         // right


}

/******************************************************************************/
/**
\brief  PositionElement - 


\return term -

\param  pODataWidget - Parent data widget
\param  verti_pos - Vertical position
\param  hori_pos - Horizontal position
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PositionElement"

logical OControlLayout :: PositionElement (ODataWidget *pODataWidget, ADK_VertPos verti_pos, ADK_HoriPos hori_pos )
{
  QBoxLayout            *layout = NULL;
  logical                term   = NO;
  switch ( verti_pos )
  {
    case VPS_OuterTop : 
         switch ( hori_pos )
         {
           case HPS_OuterLeft  : layout = ProvideCornerLayout(0,Qt::AlignBottom | Qt::AlignRight);
                                 break;
           case HPS_OuterRight : layout = ProvideCornerLayout(1,Qt::AlignBottom | Qt::AlignLeft);
                                 break;
           case HPS_InnerLeft  : layout = ProvideTopLayout(Qt::AlignLeft);
                                 break;
           case HPS_InnerRight : layout = ProvideTopLayout(Qt::AlignRight);
                                 break;
           default             : ;
         }
         break;
    
    case VPS_InnerTop :
         switch ( hori_pos )
         {
           case HPS_OuterLeft  : layout = ProvideLeftLayout(Qt::AlignTop);
                                 break;
           case HPS_OuterRight : layout = ProvideRightLayout(Qt::AlignTop);
                                 break;
           default             : ;
         }
         break;
    
    case VPS_InnerBottom :
         switch ( hori_pos )
         {
           case HPS_OuterLeft  : layout = ProvideLeftLayout(Qt::AlignBottom);
                                 break;
           case HPS_OuterRight : layout = ProvideRightLayout(Qt::AlignBottom);
                                 break;
           default             : ;
         }
         break;
    
    case VPS_OuterBottom : 
         switch ( hori_pos )
         {
           case HPS_OuterLeft  : layout = ProvideCornerLayout(2,Qt::AlignTop | Qt::AlignRight);
                                 break;
           case HPS_OuterRight : layout = ProvideCornerLayout(3,Qt::AlignTop | Qt::AlignLeft);
                                 break;
           case HPS_InnerLeft  : layout = ProvideBottomLayout(Qt::AlignLeft);
                                 break;
           case HPS_InnerRight : layout = ProvideBottomLayout(Qt::AlignRight);
                                 break;
           default             : ;
         }
    break;
    default : ;
  }

  if ( layout && layout->indexOf(pODataWidget->WidgetQ()) < 0 )
    layout->addWidget(pODataWidget->WidgetQ());

  return(term);
}

/******************************************************************************/
/**
\brief  ProvideBottomLayout - 


\return pQBoxLayout -

\param  hor_align -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideBottomLayout"

QBoxLayout *OControlLayout :: ProvideBottomLayout (Qt::AlignmentFlag hor_align )
{

  if ( !bottom_layout )
  {
    bottom_layout = new OHorLayout(Qt::AlignTop,spacing);
    addLayout(bottom_layout,4,2);
  }

  return(hor_align == Qt::AlignLeft ? bottom_layout->get_left()
                                    : bottom_layout->get_right());

}

/******************************************************************************/
/**
\brief  ProvideCornerLayout - 


\return pQBoxLayout -

\param  num -
\param  qt_align -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideCornerLayout"

QBoxLayout *OControlLayout :: ProvideCornerLayout (int32 num, Qt::Alignment qt_align )
{
  logical   on_top  = num <= 1 ? YES : NO;
  logical   on_left = num == 0 || num == 2;
  if ( !corner_layout[num] )
  {
    corner_layout[num] = new QHBoxLayout();
    corner_layout[num]->setSpacing(spacing);
    corner_layout[num]->setAlignment(qt_align);
    addLayout(corner_layout[num],
              on_top  ? 0 : 4,on_left ? 0 : 4);
  }

  return(corner_layout[num]);
}

/******************************************************************************/
/**
\brief  ProvideLeftLayout - 


\return pQBoxLayout -

\param  ver_align -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideLeftLayout"

QBoxLayout *OControlLayout :: ProvideLeftLayout (Qt::AlignmentFlag ver_align )
{

  if ( !left_layout )
  {
    left_layout = new OVerLayout(Qt::AlignRight,spacing);
    addLayout(left_layout,2,0);
  }

  return(ver_align == Qt::AlignTop ? left_layout->get_top()
                                   : left_layout->get_bottom());

}

/******************************************************************************/
/**
\brief  ProvideRightLayout - 


\return pQBoxLayout -

\param  ver_align -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideRightLayout"

QBoxLayout *OControlLayout :: ProvideRightLayout (Qt::AlignmentFlag ver_align )
{

  if ( !right_layout )
  {
    right_layout = new OVerLayout(Qt::AlignLeft,spacing);
    addLayout(right_layout,2,4);
  }

  return(ver_align == Qt::AlignTop ? right_layout->get_top()
                                   : right_layout->get_bottom());

}

/******************************************************************************/
/**
\brief  ProvideTopLayout - 


\return pQBoxLayout -

\param  hor_align -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideTopLayout"

QBoxLayout *OControlLayout :: ProvideTopLayout (Qt::AlignmentFlag hor_align )
{

  if ( !top_layout )
  {
    top_layout = new OHorLayout(Qt::AlignBottom,spacing);
    addLayout(top_layout,0,2);
  }

  return(hor_align == Qt::AlignLeft ? top_layout->get_left()
                                    : top_layout->get_right());

}

/******************************************************************************/
/**
\brief  SetInnerMargin - 



\param  rcDMargin -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInnerMargin"

void OControlLayout :: SetInnerMargin (const DMargin &rcDMargin )
{

  if ( rcDMargin.Left > 0 )
    spacer_items[0]->changeSize(rcDMargin.Left,0,QSizePolicy::Fixed);

  if ( rcDMargin.Right > 0 )
    spacer_items[2]->changeSize(rcDMargin.Right,0,QSizePolicy::Fixed);

  if ( rcDMargin.Top > 0 )
    spacer_items[1]->changeSize(0,rcDMargin.Top,QSizePolicy::Minimum,QSizePolicy::Fixed);

  if ( rcDMargin.Bottom > 0 )
    spacer_items[3]->changeSize(0,rcDMargin.Bottom,QSizePolicy::Minimum,QSizePolicy::Fixed);


}

/******************************************************************************/
/**
\brief  SetMargin - 



\param  margin_pix -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMargin"

void OControlLayout :: SetMargin (int32 margin_pix )
{

  setMargin(margin_pix);

}

/******************************************************************************/
/**
\brief  ~OControlLayout - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OControlLayout"

                        OControlLayout :: ~OControlLayout ( )
{



}


