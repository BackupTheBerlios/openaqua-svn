/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OControlLayout

\brief    Controls the Layout of items


\date     $Date: 2006/03/13 21:33:46,93 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OControlLayout_HPP
#define   OControlLayout_HPP

class     OControlLayout;

class     ODataWidget;
class     OHorLayout;
class     OVerLayout;
#include  <cADK_HoriPos.h>
#include  <cADK_VertPos.h>
#include  <sDMargin.hpp>
class  OControlLayout :public QGridLayout
{
protected  :         OHorLayout                                  *top_layout;                                                //
protected  :         OHorLayout                                  *bottom_layout;                                             //
protected  :         OVerLayout                                  *left_layout;                                               //
protected  :         OVerLayout                                  *right_layout;                                              //
protected  :         QHBoxLayout                                 *corner_layout[4];                                          //
protected  :         int32                                        spacing;                                                   //
protected  :         QSpacerItem                                 *spacer_items[4];                                           //

public     :
                     OHorLayout                                  *get_top_layout() { return(top_layout); }
                     OHorLayout                                  *get_bottom_layout() { return(bottom_layout); }
                     OVerLayout                                  *get_left_layout() { return(left_layout); }
                     OVerLayout                                  *get_right_layout() { return(right_layout); }
                     int32                                        get_spacing() { return(spacing); }
public     :                                                             OControlLayout (ODataWidget *pODataWidget, int32 margin_pix, int32 space_pix );
public     :                                     logical PositionElement (ODataWidget *pODataWidget, ADK_VertPos verti_pos, ADK_HoriPos hori_pos );
public     :                                     QBoxLayout *ProvideBottomLayout (Qt::AlignmentFlag hor_align );
public     :                                     QBoxLayout *ProvideCornerLayout (int32 num, Qt::Alignment qt_align );
public     :                                     QBoxLayout *ProvideLeftLayout (Qt::AlignmentFlag ver_align );
public     :                                     QBoxLayout *ProvideRightLayout (Qt::AlignmentFlag ver_align );
public     :                                     QBoxLayout *ProvideTopLayout (Qt::AlignmentFlag hor_align );
public     :                                     void SetInnerMargin (const DMargin &rcDMargin );
public     :                                     void SetMargin (int32 margin_pix );
public     :                                                             ~OControlLayout ( );
};

#endif
