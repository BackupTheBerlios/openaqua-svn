/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OApplicationO

\brief    


\date     $Date: 2006/08/30 17:35:21,35 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OApplicationO"

#include  <pogui7.h>
#include  <sDAction.hpp>
#include  <sDActionList.hpp>
#include  <sODSItem.hpp>
#include  <sODesktopO.hpp>
#include  <igvts.h>
#include  <sOApplicationO.hpp>


/******************************************************************************/
/**
\brief  AddDefaultAction - 



\return pDAction - 

\param  pDAction - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddDefaultAction"

DAction *OApplicationO :: AddDefaultAction (DAction *pDAction )
{

BEGINSEQ
  if ( default_actions->Insert(pDAction) )            ERROR
  pDAction = default_actions->Get(pDAction->get_name(),YES);
RECOVER
  pDAction = NULL;
ENDSEQ
  return(pDAction);
}

/******************************************************************************/
/**
\brief  ArgumentCount - Returns the Argument Count

        Wraps the QT Call For OADI

\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ArgumentCount"

int8 OApplicationO :: ArgumentCount ( )
{

  return QCoreApplication::arguments().size();

}

/******************************************************************************/
/**
\brief  CheckQueryOption - 



\return term - 

\param  option_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckQueryOption"

logical OApplicationO :: CheckQueryOption (char *option_string )
{
  static char  *values[] = {"QL_Store", "QL_Delete", "QL_Close", "QL_Exit"};
  char         *qval = NULL;
  logical       cond = NO;
  if ( qval = GetSysVariable("QUERY_LEVEL") )
    cond = STRToPosition(qval,sizeof(values)/sizeof(values[0]),values) <=
           STRToPosition(option_string,sizeof(values)/sizeof(values[0]),values);


  return(cond);
}

/******************************************************************************/
/**
\brief  GetDefaultAction - 



\return pDAction - 

\param  act_namesc - Action name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDefaultAction"

DAction *OApplicationO :: GetDefaultAction (const char *act_namesc )
{
  char        buffer[ID_SIZE];
  DAction    *pDAction = NULL;
  gvtxstb(buffer,act_namesc,ID_SIZE);

  pDAction = default_actions->Get(buffer,YES);
  return(pDAction);
}

/******************************************************************************/
/**
\brief  GetLastFocusWidget - 



\return pODataWidget - Parent data widget

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastFocusWidget"

ODataWidget *OApplicationO :: GetLastFocusWidget ( )
{

  return(last_focus_out);


}

/******************************************************************************/
/**
\brief  OApplicationO - 




\param  argc - 
\param  argv - 
\param  gui_app - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OApplicationO"

     OApplicationO :: OApplicationO (int &argc, char **argv, logical gui_app )
                     : QApplication(argc,argv,gui_app),
ODataWidget(NULL,NULL,YES),
  desk_top(NULL),
  last_focus_out(NULL),
  default_actions(NULL)
  ,argv(argv)
{

  ODSItem::InitStatic();
  
  desk_top = new ODesktopO(this,NO);
  
  default_actions = new DActionList();


}

/******************************************************************************/
/**
\brief  SetLastFocusWidget - 




\param  pODataWidget - Parent data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastFocusWidget"

void OApplicationO :: SetLastFocusWidget (ODataWidget *pODataWidget )
{

  last_focus_out = pODataWidget;

}

/******************************************************************************/
/**
\brief  WidgetQ - 



\return qwidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *OApplicationO :: WidgetQ ( )
{

  return(QApplication::desktop());

// oder lieber NULL?
// QApplication ist nur ein QObject

}

/******************************************************************************/
/**
\brief  desktop - 



\return desktop - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "desktop"

ODesktopO *OApplicationO :: desktop ( )
{

  return(desk_top);

}

/******************************************************************************/
/**
\brief  ~OApplicationO - 



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OApplicationO"

     OApplicationO :: ~OApplicationO ( )
{

  delete default_actions;
  default_actions = NULL;

}


