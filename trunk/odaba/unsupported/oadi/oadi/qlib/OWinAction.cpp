/********************************* Class Source Code ***************************/
/**
\package  OADI
\class    OWinAction



\date     $Date: 2006/05/15 16:37:58,95 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OWinAction"

#include  <poadi.h>
#include  <cmacros.h>
#include  <cqt.h>
#include  <sCTX_Control.hpp>
#include  <sCTX_GUIBase.hpp>
#include  <sOADKFactory.hpp>
#include  <sODControl.hpp>
#include  <sODesktop.hpp>
#include  <sOFieldControl.hpp>
#include  <sOStyleAction.hpp>
#include  <sOWindow.hpp>
#include  <sPropertyHandle.hpp>
#include  <sTControlFactory.hpp>
#include  <sTProjectManager.hpp>
#include  <sTWidgetControl.hpp>
#include  <sTWindow.hpp>
#include  <iigui.h>
#include  <ioadii.h>
#include  <sOWinAction.hpp>


/******************************************************************************/
/**
\brief  CastPointer

\return pointer

\param  typenames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CastPointer"

void *OWinAction :: CastPointer (char *typenames )
{

  return (   !typenames                      ? NULL
           : !strcmp(typenames,"OWinAction") ? this
                                             : OAction::CastPointer(typenames) );

}

/******************************************************************************/
/**
\brief  CreateInstance

\return rc

\param  instptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

int32 OWinAction :: CreateInstance (void **instptrp )
{

  *instptrp = new OWinAction();
  return(0);

}

/******************************************************************************/
/**
\brief  Execute

\return executed - How was function exetuted

\param  ctxptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Execute"

char OWinAction :: Execute (CTX_GUIBase *ctxptr )
{
  ODataSource    *odsource;
  TWidgetControl *pTWidgetControl;
  int8            executed = AUTO;
BEGINSEQ
//OADIResources();
//OGUIResources();
//OPAResources();
//SOSResources();
  SetContext(ctxptr);

  ReplaceSysVariable(_class,ID_SIZE);
  ReplaceSysVariable(window,ID_SIZE);

  OADIEV1(sys_ident,0)
  OADIEV2(_class,0)
  OADIEV3(window,0)
    
  SetBusy(YES);
  pTWidgetControl = OpenWindow(ctxptr);
  SetBusy(NO);
  
  if ( !win )                                        ERROR
  
  if ( win->get_ds_having() )
    if ( odsource = &win->get_ds_having()->get_dataSource() )
      if ( odsource->get_dataPH().IsValid() )
        if ( pTWidgetControl )
          pTWidgetControl->SetPropertyHandle(&odsource->get_dataPH(),NO);
  
  if ( pTWidgetControl )
    executed = pTWidgetControl->get_complexWidget()->Execute();

RECOVER
  executed = YES;
  OADIError().DisplayMessage();
ENDSEQ
  return(executed);
}

/******************************************************************************/
/**
\brief  OWinAction

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OWinAction"

     OWinAction :: OWinAction ( )
                     : OAction (),
  win(NULL)
{

  memset(window,0,sizeof(window));    // ID_SIZE

}

/******************************************************************************/
/**
\brief  i01


\param  bcOAction
\param  swindow
\param  pOWindow
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OWinAction"

     OWinAction :: OWinAction (OAction bcOAction, char *swindow, OWindow *pOWindow )
                     : OAction (bcOAction),
  window(),
  win(pOWindow)
{
  memset(window,0,sizeof(window));
  strncpy(window,swindow,sizeof(window));
/*
  "OWinAction("
  + ADK_Action::Generate()
  + ", \"" + window + "\""
  + ", NULL" // not set in READ
  + ")";
*/
}

/******************************************************************************/
/**
\brief  OpenWindow

\return pTWidgetControl

\param  ctxptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenWindow"

TWidgetControl *OWinAction :: OpenWindow (CTX_GUIBase *ctxptr )
{
  TControl       *parent;
  TControl       *tc;
  TWidgetControl *pTWidgetControl = NULL;

BEGINSEQ
{
  DBObjectHandle pdbh=GetPersistentDBHandle();
  PropertyHandle ph(pdbh,"ADK_Class",PI_Read);
  PropertyHandle phClass(_class);
  PropertyHandle phWindow(window);

  if ( !ph.Get(phClass) )                            OADIERR(100)
  if ( !ph.GPH("windows")->Get(phWindow) )           OADIERR(101)
  if ( !(win = CACHE_READ(&ph,"windows",OWindow)) )  OADIERR(101)
}
  win->SetDataSourceHaving(this);  
  
  if ( !ctxptr || !(parent = ctxptr->GetControlContext()->get_control()) )
                                                     OADIERR(99)
  statistics5.TraceMessage("Create",YES);
  statistics4.TraceMessage("SetView",NO);
  statistics0.Initialize();
  statistics4.Initialize();
  statistics5.Initialize();
  statistics6.Initialize();
  statistics0.Start();
  if ( !(tc = win->Open("OWindow",parent,NO)) )      ERROR
  statistics0.Stop();
  statistics0.TraceMessage("WIN-Open",NO);
  statistics5.TraceMessage("Create",NO);
  statistics4.TraceMessage("SetView",NO);
  statistics6.TraceMessage("DefReact",NO);

  if ( !(pTWidgetControl = OI_CAST(TWidgetControl,tc)) )
                                                     OADIERR(99)
  pTWidgetControl->SetupParentDataSource();
  tc->Activate();
  


RECOVER
  OADIError().DisplayMessage();
  delete pTWidgetControl;
  pTWidgetControl = NULL;
ENDSEQ
  return(pTWidgetControl);
}

/******************************************************************************/
/**
\brief  Read

\return term

\param  ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Read"

logical OWinAction :: Read (PropertyHandle *ph )
{
  logical                 term = NO;
  OAction::Read(ph);

  strncpy(window,ph->GetString("window"),ID_SIZE);
  return(term);
}

/******************************************************************************/
/**
\brief  Reset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void OWinAction :: Reset ( )
{

  if ( win )
    win->Release();
  win = NULL;

  OAction::Reset();

}

/******************************************************************************/
/**
\brief  SetContext


\param  ctxptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetContext"

void OWinAction :: SetContext (CTX_GUIBase *ctxptr )
{
  CTX_Control     *ctl_ctx;
  char            *curtype;
BEGINSEQ
  if ( *_class && *window )                          LEAVESEQ
    
  if ( !(ctl_ctx = ctxptr->GetControlContext()) )    LEAVESEQ
  if ( !(curtype = ctl_ctx->GetCurrentPropertyHandle()->GetCurrentType()) )
                                                     LEAVESEQ
  if ( !*_class )      
    strncpy(_class,curtype,ID_SIZE);

  if ( !*window )
    strncpy(window,curtype,ID_SIZE);
ENDSEQ
}

/******************************************************************************/
/**
\brief  SetEditProperty


\param  class_names
\param  win_names
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetEditProperty"

void OWinAction :: SetEditProperty (char *class_names, char *win_names )
{

  strcpy(sys_ident,"EditEntry");
  
  strncpy(_class,class_names ? class_names : "",ID_SIZE);
  strncpy(window,win_names ? win_names : "",ID_SIZE);

  dataSource.SetEditProperty();

}

/******************************************************************************/
/**
\brief  SetProperties

\return term

\param  class_names
\param  win_names
\param  as_collection
\param  prophdl
\param  ctxptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProperties"

logical OWinAction :: SetProperties (char *class_names, char *win_names, logical as_collection, PropertyHandle *prophdl, CTX_GUIBase *ctxptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( OAction::SetProperties(class_names,as_collection,prophdl) )      
                                                    ERROR
  strncpy(window,win_names ? win_names : "",ID_SIZE);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~OWinAction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OWinAction"

     OWinAction :: ~OWinAction ( )
{

  if ( !Deleting() )
    Reset();

}


