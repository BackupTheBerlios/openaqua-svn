/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    igui

\brief    Static service functions
          This  class summerizes  a number  of static service functions availble
          for GUI applications.

\date     $Date: 2006/07/24 21:05:05,29 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "igui"

#include  <pogui7.h>
#include  <exthrde.h>
class     OListView;
#include  <sOApplicationO.hpp>
#include  <sODataWidget.hpp>
#include  <sOEHDataWidget.hpp>
#include  <sOGUIVariables.hpp>
#include  <sThreadEntry.hpp>

#include  <iigui.h>

/******************************************************************************/
/**
\brief  FlushEvents - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FlushEvents"

void __cdecl FlushEvents ( )
{

//  QApplication::eventLoop()->processEvents(QEventLoop::ExcludeUserInput);
QCoreApplication::instance()->processEvents(QEventLoop::ExcludeUserInputEvents);


}

/******************************************************************************/
/**
\brief  GetApplication - 


\return pOApplicationO - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetApplication"

OApplicationO *__cdecl GetApplication ( )
{

  return( (OApplicationO *)qApp );

}

/******************************************************************************/
/**
\brief  GetFilePath - 


\return string - Character string

\param  caption - Caption text
\param  cpath - 
\param  filter - 
\param  write_opt - 
\param  parent_widget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFilePath"

char *__cdecl GetFilePath (char *caption, char *cpath, char *filter, logical write_opt, ODataWidget *parent_widget )
{
  QWidget            *parent = GetGUIParent(parent_widget);
  QString             filepath;
  static QByteArray   static_qba;
  bool                ok     = true;

BEGINSEQ
  static_qba = "";
    
  if ( write_opt )
    filepath = QFileDialog::getSaveFileName(GetGUIParent(parent_widget),
                                            SZ2QS(caption),
                                            SZ2QS(cpath),
                                            SZ2QS(filter));
  else
    filepath = QFileDialog::getOpenFileName(GetGUIParent(parent_widget),
                                            SZ2QS(caption),
                                            SZ2QS(cpath),
                                            SZ2QS(filter));

  if ( filepath.isEmpty() )                         ERROR

  QS2SZ_P(filepath,static_qba);
RECOVER
  ok = false;
ENDSEQ
  return(ok ? static_qba.data() : NULL);
}

/******************************************************************************/
/**
\brief  GetGUIParent - 


\return qwidget - 

\param  parent_widget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGUIParent"

QWidget *__cdecl GetGUIParent (ODataWidget *parent_widget )
{
  QWidget            *parent = parent_widget ? parent_widget->WidgetQ() : NULL;

BEGINSEQ
// ist noch nicht schoen, aber Workspace geht nicht

  if ( !parent )                                    ERROR

  if ( !strncmp(parent->metaObject()->className(),"QWorkspace",10) )
    parent = NULL;    

RECOVER

ENDSEQ
  return(parent);
}

/******************************************************************************/
/**
\brief  GetOGUIErrorObject - Get error object
        The  function  returns  the  error  object  for the provect named in the
        project variable (pv_name).

\return error - Error Object

\param  pv_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOGUIErrorObject"

Error &__cdecl GetOGUIErrorObject (ProcessVariableNames pv_name )
{
  ProcessInfo *proc_info = ThreadEntry::GetCurProcInfo(PVT_OGUI);
  Error       *error     = NULL;
BEGINSEQ
  if ( !proc_info )
    if ( !(proc_info = OGUIInitProcessInfo()) )          ERROR
 
  error = (Error *)proc_info->GetProcessVariable(pv_name);

RECOVER

ENDSEQ
return *error;
}

/******************************************************************************/
/**
\brief  GetSearchString - 


\return term - 

\param  pOEHDataWidget - 
\param  caption - Caption text
\param  clabel - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSearchString"

logical __cdecl GetSearchString (OEHDataWidget *pOEHDataWidget, char *caption, char *clabel )
{
  bool       ok     = false;
  logical    cond   = YES;

BEGINSEQ
  if ( !pOEHDataWidget )                             ERROR
  QString  &find_text = pOEHDataWidget->get_find_text();
    
  if ( !caption )
    caption = "Find";
  if ( !clabel )
    clabel = "Enter Text to Find";
    
  find_text = QInputDialog::getText(pOEHDataWidget->WidgetQ(),
                                    SZ2QS(caption), 
                                    SZ2QS(clabel),
                                    QLineEdit::Normal,
                                    find_text,
                                    &ok);
  if ( !ok || find_text.isEmpty() )                  ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  GetString - Get string
        The  function pops up with a dialogue requesting a string value from the
        user.

\return string - Character string

\param  caption - Caption text
\param  clabel - 
\param  init_string - Initial string
\param  parent_widget - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *__cdecl GetString (char *caption, char *clabel, char *init_string, ODataWidget *parent_widget )
{
  QString             text;
  static QByteArray   static_qba;
  bool                ok     = false;

  static_qba = "";
  
  text = QInputDialog::getText(GetGUIParent(parent_widget),
                               SZ2QS(caption),
                               SZ2QS(clabel),
                               QLineEdit::Normal,
                               SZ2QS(init_string),
                               &ok);
  if ( ok && !text.isEmpty() )  
    QS2SZ_P(text,static_qba);
  return(ok ? static_qba.data() : NULL);
}

/******************************************************************************/
/**
\brief  IsBusy - 


\return cond - 

\param  wait_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsBusy"

logical __cdecl IsBusy (logical wait_opt )
{
  QCursor   *cursor = QApplication::overrideCursor();
  return (   cursor &&  cursor->shape() == Qt::WaitCursor 
           ? YES : NO );

}

/******************************************************************************/
/**
\brief  OGUIError - Get GUI-Error
        The function returns the GUI error object.

\return error - Error Object

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OGUIError"

Error &__cdecl OGUIError ( )
{

  return ( GetOGUIErrorObject(PVN_GUIError) );

}

/******************************************************************************/
/**
\brief  OGUIInitProcessInfo - Get Process Information


\return proc_info - Process information

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OGUIInitProcessInfo"

ProcessInfo *__cdecl OGUIInitProcessInfo ( )
{
  ProcessInfo   *proc_info;
  if ( thread_list )
    if ( !(proc_info = ThreadEntry::GetCurProcInfo()) )
      proc_info = ThreadEntry::CreateCurProcInfo(NULL);
  
  if ( proc_info && !proc_info->GetVariableManager(PVT_OGUI) )
  {
    proc_info->SetVariableManager(new OGUIVariables(proc_info->GetProcessVariables()));
  }
  return(proc_info);
}

/******************************************************************************/
/**
\brief  OGUIResources - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OGUIResources"

void __cdecl OGUIResources ( )
{
  extern        int32 dw_count;
  extern        int32 dw_max;
  extern        int32 dw_total;
  extern        int32 is_count;
  extern        int32 is_max;
  extern        int32 is_total;
  extern        int32 ods_count;
  extern        int32 ods_max;
  extern        int32 ods_total;
  extern        int32 odsi_count;
  extern        int32 odsi_max;
  extern        int32 odsi_total;
  extern        int32 oeh_count;
  extern        int32 oeh_total;
  extern        int32 oact_count;
  extern        int32 oact_max;
  extern        int32 oact_total;
  extern        int32 widg_count;
  char          string[31];
  SDBError().TraceMessage("dw count  : ",gvtxltoa(dw_count,string,10));
  dw_count = 0;
  SDBError().TraceMessage("dw total  : ",gvtxltoa(dw_total,string,10));
  dw_total = 0;
  SDBError().TraceMessage("widg count: ",gvtxltoa(widg_count,string,10));
  widg_count = 0;
  SDBError().TraceMessage("is count  : ",gvtxltoa(is_count,string,10));
  is_count = 0;
  SDBError().TraceMessage("is total  : ",gvtxltoa(is_total,string,10));
  is_total = 0;
  SDBError().TraceMessage("ods count : ",gvtxltoa(ods_count,string,10));
  ods_count = 0;
  SDBError().TraceMessage("ods total : ",gvtxltoa(ods_total,string,10));
  ods_total = 0;
  SDBError().TraceMessage("odsi count: ",gvtxltoa(odsi_count,string,10));
  odsi_count = 0;
  SDBError().TraceMessage("odsi total: ",gvtxltoa(odsi_total,string,10));
  odsi_total = 0;
  SDBError().TraceMessage("oeh count : ",gvtxltoa(oeh_count,string,10));
  oeh_count = 0;
  SDBError().TraceMessage("oeh total : ",gvtxltoa(oeh_total,string,10));
  oeh_total = 0;
  SDBError().TraceMessage("oact count: ",gvtxltoa(oact_count,string,10));
  oact_count = 0;
  SDBError().TraceMessage("oact total: ",gvtxltoa(oact_total,string,10));
  oact_total = 0;


}

/******************************************************************************/
/**
\brief  Quit - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Quit"

logical __cdecl Quit ( )
{
  logical                 term = NO;
  qApp->quit();
  return(term);
}

/******************************************************************************/
/**
\brief  SetBusy - 



\param  wait_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBusy"

void __cdecl SetBusy (logical wait_opt )
{

  if ( wait_opt )
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
  else
    QApplication::restoreOverrideCursor();


}

