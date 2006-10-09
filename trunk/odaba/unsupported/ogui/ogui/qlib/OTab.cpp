/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OTab

\brief    Tab-Control
          The  class defines a  tab-control, which might  consist of one or more
          tab-items.  Tabs for the items can be  arranged on top or on buttom as
          large  (round)  or  small  (triangular)  tabs. Each item is associated
          with  a  separate  control  (window),  which is shown, when the tab is
          selected.  A tab-control may contain one  fixed child window, which is
          displayed for all tab items.

\date     $Date: 2006/08/01 20:10:04,46 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OTab"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOTab.h>
#include  <sDBStructDef.hpp>
#include  <sDPixmap.hpp>
#include  <sODControl.hpp>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sOIconSet.hpp>
#include  <sOObject.hpp>
#include  <sOWidget.hpp>
#include  <sOWidgetStack.hpp>
#include  <sPropertyHandle.hpp>
#include  <sOTab.hpp>


/******************************************************************************/
/**
\brief  Activate - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical OTab :: Activate ( )
{
  logical           ini = stscini();
  QWidget          *qw;
  ODataWidget      *odw;
  QIcon            *pQIcon;
  int               indx0 = 0;
  logical           term  = NO;
  if ( !ini )
  {
    connect(ods(),SIGNAL(OnHandleOpened()),
            this,      SLOT  (SetDynamicTab()));
  }
  
  term = OFrame::Activate();
  
  while ( qw = panels->widget(indx0++) )
  {
    if ( odw = OObject::GetODW(qw) )
    {
      if ( pQIcon = odw->get_olayout()->GetIcon() )
      {
        SetTabIcon(pQIcon,odw->get_display_level());
        pQIcon = NULL;
      }
      if ( odw->Activate() )
        term = YES;
    }
    
    if ( !ini && indx0 > 1 )
      qw->hide();
  }
  
  if ( !ini )
  {
    connect(ods(),SIGNAL(OnCollectionChanged()),
            this,      SLOT  (SetDynamicTab()));
    connect(ods(),SIGNAL(OnInstanceSelected()),
            this,      SLOT  (SetDynamicTab()));
  }

  return(term);
}

/******************************************************************************/
/**
\brief  ActivateFirstTab - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateFirstTab"

void OTab :: ActivateFirstTab ( )
{

BEGINSEQ
  if ( !tabbar )                                     LEAVESEQ

  if ( !tabbar->currentIndex() )
    ActivateTab(0);
  else
    tabbar->setCurrentIndex(0);

ENDSEQ

}

/******************************************************************************/
/**
\brief  ActivateTab - 




\param  int_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateTab"

void OTab :: ActivateTab (int int_index )
{

  GenerateEvent(GEV_Select);
  if ( !panels->SetDisplayLevel(int_index) )
  {
    display_level = int_index+1;
    if ( od_control )
      od_control->set_display_level(display_level);
    GenerateEvent(GEV_Selected);
  }


}

/******************************************************************************/
/**
\brief  AddElement - Add tab item

        The function adds a tab-Item with the label to be displayed on the tab.

\return term - 

\param  child - Child to be displayed within the control/window
\param  label - Label to be displayed
\param  tab_index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddElement"

logical OTab :: AddElement (ODataWidget *child, const QString label, int32 tab_index )
{

  if ( !tab_index )     // static area
    SetFixed(child);
  else
  {
    if ( tab_index == AUTO )
      tab_index = tab_count;
    else
      tab_index--;
    
    while ( tabbar && tab_index > tabbar->count() )
      tabbar->addTab(SZ2QS("empty_tab"));
      
    if ( tabbar && tab_index == tabbar->count() )
      tabbar->addTab(label);
  
    panels->AddChild(child,tab_index);
    //j 060330 done in QWidgetStack
    //child->WidgetQ()->hide(); 
    
    if ( ++tab_index > tab_count )
      tab_count = tab_index;
  }
  
//  vlayout->invalidate();
//  vlayout->setGeometry(contentsRect());

  return(tab_index);
}

/******************************************************************************/
/**
\brief  Deactivate - 



\return term - 

\param  data_only - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deactivate"

logical OTab :: Deactivate (logical data_only )
{
  logical           ini = stscini();
  QWidget          *qw    = NULL;
  ODataWidget      *odw   = NULL;
  int               indx0 = 0;
  logical           term  = NO;
  if ( ini && !data_only )
  {
    disconnect(ods(),SIGNAL(OnCollectionChanged()),
               this,      SLOT  (SetDynamicTab()));
    disconnect(ods(),SIGNAL(OnInstanceSelected()),
               this,      SLOT  (SetDynamicTab()));
  }

  while ( qw = panels->widget(indx0++) )
    if ( odw = OObject::GetODW(qw) )
      if ( odw->Deactivate(data_only) )
        term = YES;

  if ( OFrame::Deactivate(data_only) )
    term = YES;
    
  if ( ini && !data_only )
    disconnect(ods(),SIGNAL(OnHandleOpened()),
               this,      SLOT  (SetDynamicTab()));

  return(term);
}

/******************************************************************************/
/**
\brief  FrameQ - 



\return pQFrame - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FrameQ"

QFrame *OTab :: FrameQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  GetActiveTab - 



\return pOdataWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActiveTab"

ODataWidget *OTab :: GetActiveTab ( )
{

  return ( panels->GetChild(display_level) ); 


}

/******************************************************************************/
/**
\brief  GetCurrentPropertyHandle - 



\return ph - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentPropertyHandle"

PropertyHandle *OTab :: GetCurrentPropertyHandle ( )
{
  ODataWidget            *child = NULL;
  PropertyHandle         *ph = NULL;
  ph = (child = panels->GetChild(display_level)) 
       ? child->GetCurrentPropertyHandle()
       : OFrame::GetCurrentPropertyHandle();
  return(ph);
}

/******************************************************************************/
/**
\brief  OTab - 




\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS_w - 
\param  tb_upper - Position for displaying the tabs
\param  tb_normal - Size of tabs in the tab-bar
\param  stb_upper - Position of static area for the tab-control
\param  dyn_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OTab"

     OTab :: OTab (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS_w, logical tb_upper, logical tb_normal, logical stb_upper, char dyn_opt )
                     : OFrame(pODataWidget,oODataWidget,pODS_w),
  vlayout(NULL),
  tabbar(NULL),
  panels(NULL),
  tab_top(NO),
  fix_top(NO),
  static_area(NULL),
  tab_count(0)

{

  dynamic = dyn_opt;
  
  if ( tb_normal )
    tabbar  = new QTabBar(this);
  vlayout = new QVBoxLayout(this);
  vlayout->setMargin(0);
  vlayout->setSpacing(0);
  
  panels  = new OWidgetStack(this,this,pODS_w);
//  new QGridLayout(panels);
  tab_top = tb_upper;
  fix_top = stb_upper;

  if ( tab_top )
  {
    if ( tabbar )
      vlayout->addWidget(tabbar);
//    vlayout->addWidget(panels,1);
    vlayout->addWidget(panels);
  }
  else
  {
    if ( tabbar )
      vlayout->addWidget(panels);
    vlayout->addWidget(tabbar);
  }

  if ( tb_normal == 1 ) 
    tabbar->setShape(tab_top ? QTabBar::RoundedNorth : QTabBar::RoundedSouth);
  if ( tb_normal == 2 ) 
    tabbar->setShape(tab_top ? QTabBar::TriangularNorth : QTabBar::TriangularSouth);

  if ( tabbar )
    connect(tabbar,SIGNAL(currentChanged(int)),this,SLOT(ActivateTab(int)));

}

/******************************************************************************/
/**
\brief  Panels - 



\return pOWidgetStack - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Panels"

OWidgetStack *OTab :: Panels ( )
{

  return ( panels );

}

/******************************************************************************/
/**
\brief  SetDefaultReactions - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultReactions"

logical OTab :: SetDefaultReactions ( )
{
  logical                 term = NO;
  OEHDataWidget::SetDefaultReactions();
  
  SetGUIDefReaction("SetDisplayLevel1",OEHKeyEvent(Qt::Key_1, Qt::ControlModifier) ); 
  SetGUIDefReaction("SetDisplayLevel2",OEHKeyEvent(Qt::Key_2, Qt::ControlModifier) ); 
  SetGUIDefReaction("SetDisplayLevel3",OEHKeyEvent(Qt::Key_3, Qt::ControlModifier) ); 
  SetGUIDefReaction("SetDisplayLevel4",OEHKeyEvent(Qt::Key_4, Qt::ControlModifier) ); 
  SetGUIDefReaction("SetDisplayLevel5",OEHKeyEvent(Qt::Key_5, Qt::ControlModifier) ); 
  SetGUIDefReaction("SetDisplayLevel6",OEHKeyEvent(Qt::Key_6, Qt::ControlModifier) ); 
  SetGUIDefReaction("SetDisplayLevel7",OEHKeyEvent(Qt::Key_7, Qt::ControlModifier) ); 
  SetGUIDefReaction("SetDisplayLevel8",OEHKeyEvent(Qt::Key_8, Qt::ControlModifier) ); 
  SetGUIDefReaction("SetDisplayLevel9",OEHKeyEvent(Qt::Key_9, Qt::ControlModifier) ); 
  SetGUIDefReaction("SetDisplayLevel0",OEHKeyEvent(Qt::Key_0, Qt::ControlModifier) );  

  return(term);
}

/******************************************************************************/
/**
\brief  SetDisplayLevel - 



\return term - 

\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayLevel"

logical OTab :: SetDisplayLevel (int16 dsp_level )
{

BEGINSEQ
  if ( dsp_level > 0 )
  {
//    OFrame::SetDisplayLevel(dsp_level);
    if( tabbar && (dsp_level-1 == tabbar->currentIndex()) )
      LEAVESEQ
    ActivateTab(dsp_level-1);
    if ( tabbar )
      tabbar->setCurrentIndex(dsp_level-1);
  }
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  SetDynamicTab - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDynamicTab"

void OTab :: SetDynamicTab ( )
{

//ODataWidget::SetType(GetCurrentPropertyHandle());  das geht nicht!!
  ODataWidget::SetType();

}

/******************************************************************************/
/**
\brief  SetFixed - Add fixed area to tab control

        The function creates a fixed area for the tab-control.


\param  child - Child to be displayed within the control/window
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFixed"

void OTab :: SetFixed (ODataWidget *child )
{

BEGINSEQ
  if ( !static_area )
  {
    static_area = child;
    child->WidgetQ()->setMinimumHeight(40);
//    child->WidgetQ()->setMinimumWidth(80);
    switch ( tab_top+!fix_top )
    {
      case 0  :
      case 1  : vlayout->insertWidget(tab_top+!fix_top,child->WidgetQ());
                break;
      default : vlayout->addWidget(child->WidgetQ());
    }
  }
  else
    if ( static_area != child )                      OGUIERR(99)

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetFrame - 




\param  fstyle - 
\param  lwidth - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFrame"

void OTab :: SetFrame (int64 fstyle, int64 lwidth )
{

  setFrameStyle(fstyle);
  setLineWidth(lwidth);


}

/******************************************************************************/
/**
\brief  SetMargin - 




\param  width - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetMargin"

void OTab :: SetMargin (int width )
{

  //q3:setMargin(width);
  setContentsMargins ( width, width, width, width );

}

/******************************************************************************/
/**
\brief  SetTabIcon - 




\param  pQIcon - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTabIcon"

void OTab :: SetTabIcon (QIcon *pQIcon, int16 dsp_level )
{

BEGINSEQ
  if ( !tabbar || dsp_level > tabbar->count() )  ERROR
    
  tabbar->setTabIcon(dsp_level-1,*pQIcon);
//  tabbar->layoutTabs();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetTabText - 




\param  label_text - Label text
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTabText"

void OTab :: SetTabText (char *label_text, int16 dsp_level )
{

BEGINSEQ
  if ( !this || !tabbar || dsp_level > tabbar->count() )  ERROR
    
  tabbar->setTabText(dsp_level-1,SZ2QS(label_text));

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetType - 



\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

logical OTab :: SetType (PropertyHandle *prophdl )
{
  int16             dsp_level = UNDEF;
BEGINSEQ
  if ( prophdl && dynamic )
  {
    if ( !(dsp_level = panels->SetTypeLevel(prophdl->GetCurrentType())) )
      if ( LoadDynamicControl(prophdl->GetCurrentType(),NULL,YES) )
        if ( SetType(prophdl->GetCurrentTypeDef()) ) ERROR
    dsp_level = panels->SetTypeLevel(prophdl);
  }
  if ( dsp_level )
    ActivateTab(dsp_level-1);
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

logical OTab :: SetType (char *typenames )
{
  logical           term      = NO; 
  DictionaryHandle  dictionary;
  DBStructDef      *strdef;
  int16             dsp_level = UNDEF;

BEGINSEQ
  if ( dynamic )
  {
    if ( !typenames || !*typenames )                 OGUIERR(99)
    
    if ( !(dsp_level = panels->SetTypeLevel(typenames)) )
      if ( panels->SetType(typenames) )
      {
        if ( LoadDynamicControl(typenames,NULL,YES) )
        {
          dictionary = ods()->Item()->GetObjectHandle().GetDictionary();
          if ( !(strdef = dictionary.ProvideStructureDef(typenames)) )
                                                     ERROR
          if ( SetType(strdef) )                     ERROR
        }
        dsp_level = panels->SetTypeLevel(typenames);
      }
  }
  if ( dsp_level )
    ActivateTab(dsp_level-1);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  struct_def - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetType"

logical OTab :: SetType (DBStructDef *struct_def )
{
  int32             indx0  = 0;
  char              names[ID_SIZE+1];
  DBStructDef      *strdef = NULL;
  logical           term   = NO; 

BEGINSEQ
  if ( !dynamic )                                   LEAVESEQ
  if ( !struct_def )                                OGUIERR(99)

  while ( strdef = struct_def->GetBaseStructure(indx0++) )
    if ( !SetType(gvtxbts(names,strdef->smcbname,ID_SIZE)) ) 
                                                    LEAVESEQ
  indx0 = 0;
  while ( strdef = struct_def->GetBaseStructure(indx0++) )
    if ( !SetType(strdef) )                         LEAVESEQ

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateLayout - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateLayout"

logical OTab :: UpdateLayout ( )
{
  logical                 term = NO;
//  if ( tabbar )
//    tabbar->layoutTabs();
  
//  vlayout->invalidate();
//  vlayout->setGeometry(contentsRect());

  QSizePolicy   sp = sizePolicy();
  sp.setHorizontalPolicy(QSizePolicy::Preferred);
  sp.setVerticalPolicy  (QSizePolicy::Preferred);
  panels->setSizePolicy(sp);
  

  return(term);
}

/******************************************************************************/
/**
\brief  polish - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "polish"

void OTab :: polish ( )
{

//  SetDisplayLevel(1);
  QWidget::ensurePolished();


}

/******************************************************************************/
/**
\brief  resizeEvent - 




\param  resize_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "resizeEvent"

void OTab :: resizeEvent (QResizeEvent *resize_event )
{
  int t_width	= tabbar ? tabbar->sizeHint().width() : 0;
  int w_width	= width();
  if ( tabbar )
    tabbar->resize(MAX(t_width,w_width), 30);
  
  QFrame::resizeEvent(resize_event);
//  vlayout->invalidate();
//  vlayout->setGeometry(contentsRect());



}

/******************************************************************************/
/**
\brief  show - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "show"

void OTab :: show ( )
{

  vlayout->setMargin(frameWidth());
    
  if ( static_area )
    static_area->WidgetQ()->show();
  if ( tabbar )
    tabbar->show();
  panels->show();
  QFrame::show();

  ActivateTab(display_level-1);


}

/******************************************************************************/
/**
\brief  showEvent - 




\param  show_event - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "showEvent"

void OTab :: showEvent (QShowEvent *show_event )
{

  vlayout->setMargin(frameWidth());
    
  ActivateTab(MAX(0,display_level-1));
  
  vlayout->invalidate();
  vlayout->setGeometry(contentsRect());


}

/******************************************************************************/
/**
\brief  ~OTab - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OTab"

     OTab :: ~OTab ( )
{

  delete tabbar;
  delete vlayout;
  delete panels;


}


