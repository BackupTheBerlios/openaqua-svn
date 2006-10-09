#include "actiondocument.h"


#include "mainwindow.h"
#include "actionmodel.h"
#include <CoaDebug>
#include <CoaWorkbench>

ActionDocument::ActionDocument(const CoaString& objectName,  CoaWorkbench *const parent, Qt::WFlags flags)
: QObject(parent)
, m_docWindow (0)
, m_docDataModel (0)
, m_flags(flags)
{
   BEGIN;
   setObjectName(objectName);
}





ActionDocument::~ActionDocument()
{
   BEGIN;
}

bool ActionDocument::initialize()
{
   BEGIN;
   bool result = true;
   //m_docDataModel = new ActionModel("", this);
   //m_docWindow = new MainWindow(objectName(), this, m_flags );
   RETURN(result);
}


bool ActionDocument::slotFileSave()
{
   BEGIN;
   RETURN(false);
}


bool ActionDocument::slotFileNew()
{
   BEGIN;
   RETURN(false);
}


bool ActionDocument::slotFileClose()
{
   BEGIN;
   RETURN(false);
}


bool ActionDocument::slotFileOpen(const QIODevice &device)
{
   BEGIN;
   Q_UNUSED(device);
   RETURN(false);
}


