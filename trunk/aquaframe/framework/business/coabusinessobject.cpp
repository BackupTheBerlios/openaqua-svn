#include "coabusinessobject.h"

#include <CoaDebug>
#include <CoaMainThreadMaker>
#include <CoaWorkspace>
#include <CoaApplication>


CoaBusinessObject::CoaBusinessObject(const CoaMainThreadMaker *maker, const QString& objectname)
: QObject(0)
, m_workspace(0)
, m_isInitialized(false)
{
   BEGIN;
   Q_UNUSED(maker);
   setObjectName(objectname);
   initialize();
}


void CoaBusinessObject::show()
{
   BEGIN;
   m_workspace->show();
}



CoaBusinessObject::~CoaBusinessObject()
{
   BEGIN;

}


void  CoaBusinessObject::initialize()
{
   BEGIN;
   if (m_isInitialized == true) return;

   initWorkspace();
   createMainMenu();

   m_isInitialized = true;
   emit isInitialized();
}


void  CoaBusinessObject::initWorkspace()
{
   BEGIN;
   if (m_workspace != 0) return;

   m_workspace = new CoaWorkspace(0);
   m_workspace->setWindowTitle(COAAPP->applicationName ());

}

void CoaBusinessObject::createMainMenu()
{
   BEGIN;
}


void CoaBusinessObject::createMainWindow()
{
   BEGIN;
}



