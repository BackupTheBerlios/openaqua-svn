/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODWindow

\brief    Complex Window
          Complex  windows  usually  consists  of  several  QT  widgets,  which 
          describe different areas within the window.

\date     $Date: 2006/06/27 12:53:54,96 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODWindow"

#include  <pogui7.h>
#include  <sDPixmap.hpp>
#include  <sOButtonGroup.hpp>
#include  <sODControl.hpp>
#include  <sODTabControl.hpp>
#include  <sODataWidget.hpp>
#include  <sODialog.hpp>
#include  <sODockArea.hpp>
#include  <sOEHActionHandler.hpp>
#include  <sOFrame.hpp>
#include  <sOGroupBox.hpp>
#include  <sOScrollView.hpp>
#include  <sOSplitter.hpp>
#include  <sOToolBar.hpp>
#include  <sOWorkspace.hpp>
#include  <sODWindow.hpp>


/******************************************************************************/
/**
\brief  Activate - Activate data for window
        The window is activated.

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Activate"

logical ODWindow :: Activate ( )
{
  PropertyHandle  *ph = GetDSPropertyHandle();
  logical          term = NO;
  term = ODControl::Activate();
  
  if ( ph && !ph->IsSelected() && 
       ph->IsCollection() && ph->GetDimension() == 1 &&
       ph->GetMode() >= PI_Update )
    ph->GetInitInstance();

  return(term);
}

/******************************************************************************/
/**
\brief  CreateButtonGroup - 


\return term - 

\param  vertical - 
\param  exclusive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateButtonGroup"

logical ODWindow :: CreateButtonGroup (logical vertical, logical exclusive )
{
  OButtonGroup   *obuttongroup  = NULL;
  logical         term          = NO;
BEGINSEQ
  //,vertical,exclusive not supported anymore
  if ( !(obuttongroup = new OButtonGroup( ClientWidgetParent(),
                                          WidgetOwner(),NO)) )
                                                     OGUIERR(95)
                                                     OGUICERR
  clientWidget = obuttongroup;
  obuttongroup = NULL;

RECOVER
  delete obuttongroup;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateClientArea - 


\return term - 

\param  control_name - 
\param  is_workspace - 
\param  dsp_level - 
\param  is_control - 
\param  win_type - 
\param  vertical - 
\param  exclusive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateClientArea"

logical ODWindow :: CreateClientArea (char *control_name, logical is_workspace, int16 dsp_level, logical is_control, OWindowTypes win_type, logical vertical, logical exclusive )
{
  OFrame         *oframe     = NULL;
  logical         term       = NO;
BEGINSEQ
  if ( !is_workspace && is_control )
    InitControlWidget();
  else
    RemoveControlWidget();
  
  if ( !(oframe = new OFrame( ClientWidgetParent(),
                              WidgetOwner(),odw_ods)) )
                                                     OGUIERR(95)
                                                     OGUICERR
  ODWindow::win_type = win_type;
  
  controlWidget = oframe;
  oframe        = NULL;
  BindClientWidget(controlWidget,controlWidget);

  if ( control_name )
    controlWidget->WidgetQ()->setObjectName(control_name);
    
  switch ( win_type )
  {
    case WT_Splitter   : if ( CreateSplitterWindow(vertical) )
                                                     ERROR
                         break;
//    case WT_Hierarchy  :
    case WT_Normal     : if ( CreateSimpleWindow(is_workspace) ) 
                                                     ERROR
                         break;
    case WT_ButtonGroup: if ( CreateButtonGroup(vertical,exclusive) )  
                                                     ERROR
                         break;
    case WT_GroupBox   : if ( CreateGroupBox(vertical) )  
                                                     ERROR
                         break;
    default : ;
  }

  BindClientWidget(clientWidget,clientWidget);
  if ( !is_workspace && is_control )
    RegisterControlWidget(control_name,parent->GetControlList(),dsp_level);
  
  if ( !controlWidget->get_od_control() )
    controlWidget->set_od_control(this);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateGroupBox - 


\return term - 

\param  vertical - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateGroupBox"

logical ODWindow :: CreateGroupBox (logical vertical )
{
  OGroupBox   *ogroupbox  = NULL;
  logical         term       = NO;
BEGINSEQ
  //,vertical not supported anymore
  if ( !(ogroupbox = new OGroupBox( ClientWidgetParent(),
                                    WidgetOwner(),NO)) )
                                                     OGUIERR(95)
                                                     OGUICERR
  clientWidget = ogroupbox;
  ogroupbox    = NULL;

RECOVER
  delete ogroupbox;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateLabel - 


\return term - 

\param  dsize - 
\param  verti_pos - Vertical position
\param  hori_pos - Horizontal position
\param  label_text - Label text
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateLabel"

logical ODWindow :: CreateLabel (DSize &dsize, ADK_VertPos verti_pos, ADK_HoriPos hori_pos, char *label_text )
{
  logical                 term = NO;
  switch ( win_type )
  {
    case WT_GroupBox    :
    case WT_ButtonGroup : SetTitle(label_text);
                          break;
    default             : ODControl::CreateLabel(dsize,verti_pos,hori_pos,label_text);
  }

  return(term);
}

/******************************************************************************/
/**
\brief  CreateLayout - 



\param  grid_size - 
\param  dmargin - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateLayout"

void ODWindow :: CreateLayout (DSize &grid_size, DMargin &dmargin )
{

  switch ( win_type )
  {
    case WT_GroupBox    :
    case WT_Splitter    :
    case WT_ButtonGroup : grid_control = 0;
                          break;
    default             : ODControl::CreateLayout(grid_size,dmargin);
  }


}

/******************************************************************************/
/**
\brief  CreateSimpleWindow - 


\return term - 

\param  is_workspace - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSimpleWindow"

logical ODWindow :: CreateSimpleWindow (logical is_workspace )
{
  OWorkspace     *ows        = NULL;
  OScrollView    *oscroll    = NULL;
  logical         term       = NO;
BEGINSEQ
  if ( is_workspace )
  {
    if ( !(ows = new OWorkspace(ClientWidgetParent(),controlWidget,NO)) )
                                                     OGUIERR(95)
                                                     OGUICERR
    clientWidget = ows;
  }
  else 
  {
    if ( !(oscroll = new OScrollView(ClientWidgetParent(),controlWidget,NO)) )
                                                     OGUIERR(95)
                                                     OGUICERR
// in Qt4 nicht verfuegbar
//    oscroll->viewport()->setBackgroundMode(Qt::PaletteBackground);
//    oscroll->setBackgroundRole(QPalette::Dark);
    clientWidget = oscroll;
  }

RECOVER
  delete ows;
  delete oscroll;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateSplitterWindow - 


\return term - 

\param  vertical - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSplitterWindow"

logical ODWindow :: CreateSplitterWindow (logical vertical )
{
  OSplitter      *osplitter  = NULL;
  logical         term       = NO;
BEGINSEQ
  if ( !(osplitter = new OSplitter( ClientWidgetParent(),
                                    WidgetOwner(),NO)) )
                                                     OGUIERR(95)
                                                     OGUICERR

  osplitter->setOrientation( vertical ? Qt::Vertical 
                                      : Qt::Horizontal );

  clientWidget = osplitter;
  osplitter    = NULL;

RECOVER
  delete osplitter;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateWindowArea - 


\return term - 

\param  control_name - 
\param  is_modal - 
\param  win_style - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateWindowArea"

logical ODWindow :: CreateWindowArea (char *control_name, logical is_modal, OWindowTypes win_style )
{
  ODialog         *odlg   = NULL;
  QObject         *parent = NULL;
  ODataWidget     *odw;
  logical          term   = NO;
BEGINSEQ
/*
  switch ( win_type )
  {
    case WT_Dialog    : if ( !(odlg = new ODialog(ClientWidgetParent(),WidgetOwner(),
                                                  YES,"ControlFrame",is_modal)) )      
                                                     OGUIERR(95)
                                                     OGUICERR
                        odw = frameInnerWidget = odlg;
                        break;
    case WT_Hierarchy : if ( !(omain = new ODockArea(ClientWidgetParent(),WidgetOwner(),YES) )      
                                                     OGUIERR(95)
                                                     OGUICERR
                        odw = frameInnerWidget = omain;
                        break;
    case WT_Popup     :
    case WT_Tool      :
    default : ;
  }
*/
  if ( !(odlg = new ODialog(ClientWidgetParent(),WidgetOwner(),
                            NULL,is_modal)) )      
                                                     OGUIERR(95)
                                                     OGUICERR
  odw = frameInnerWidget = odlg;
  frameOuterWidget = frameInnerWidget;
  clientInnerWidget = odw;

  parent_odw = NULL;
RECOVER
  delete odlg;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ODWindow - Konstruktor



\param  pODControl - 
\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODWindow"

     ODWindow :: ODWindow (ODControl *pODControl, char *names )
                     : ODControl (pODControl,pODControl,YES,names),
  clientWidget(NULL),
  win_type(WT_Normal)
{

//  enableEventHandling();


}

/******************************************************************************/
/**
\brief  UpdateLayout - 



\param  position - 
\param  inner_dist - 
\param  outer_dist - 
\param  dsize - 
\param  frame_size - 
\param  dalign - 
\param  dsp_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateLayout"

void ODWindow :: UpdateLayout (DPoint &position, int16 inner_dist, int16 outer_dist, DSize &dsize, DSize &frame_size, DAlign &dalign, int16 dsp_level )
{
  ODataWidget       *odw = NULL;
  QWidget           *usedWidget = NULL;
BEGINSEQ
  ODControl::UpdateLayout(position,inner_dist,outer_dist,dsize,frame_size,
                          dalign,dsp_level);
  
  if ( !(odw = dock_area ? dock_area
                         : clientInnerWidget ? clientInnerWidget 
                                              : clientWidget     ) ) 
                                                     LEAVESEQ
  usedWidget = odw->WidgetQ();
  if ( !usedWidget->parentWidget() )                 LEAVESEQ
  QRect rect = ((OFrame *)usedWidget->parentWidget())->contentsRect();
  usedWidget->setGeometry(rect);
  if ( usedWidget->parentWidget()->layout() )
    usedWidget->parentWidget()->layout()->setMargin(outer_dist + 
                             ((OFrame *)usedWidget->parentWidget())->frameWidth());

  if(usedWidget->inherits("QScrollArea"))
    ((OScrollView*)odw)->SetMargin(inner_dist);
ENDSEQ

}

/******************************************************************************/
/**
\brief  UpdateScrollBars - 



\param  has_hscroll - 
\param  has_vscroll - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateScrollBars"

void ODWindow :: UpdateScrollBars (logical has_hscroll, logical has_vscroll )
{

  if ( this && clientWidget )
    clientWidget->UpdateScrollBars(has_hscroll,has_vscroll);

}

/******************************************************************************/
/**
\brief  ~ODWindow - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODWindow"

     ODWindow :: ~ODWindow ( )
{



}


