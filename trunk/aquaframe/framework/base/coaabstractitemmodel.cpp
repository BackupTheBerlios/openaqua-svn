#include "coaabstractitemmodel.h"

#include <CoaDebug>
#include <CoaMainWindow>

CoaAbstractItemModel::CoaAbstractItemModel(QObject *parent)
:QAbstractItemModel(parent)
{
     BEGIN;
}



CoaAbstractItemModel::~CoaAbstractItemModel()
{
     BEGIN;
     foreach(QObject *object, m_masterSet) {
        WRN(QString("Model still has window: %1").arg(object->objectName()));
     }
     m_masterSet.clear(); //dont delete the content!
}


void CoaAbstractItemModel::addMasterWindow(QObject *const w)
{
   BEGIN;
   m_masterSet.insert(w);
}



void CoaAbstractItemModel::remMasterWindow(QObject *const window)
{
     BEGIN;
     m_masterSet.remove(window);
}


void CoaAbstractItemModel::setContentDirty(const bool)
{
     BEGIN;

/*     foreach(QObject *object, m_masterSet) {

        CoaMainWindow *window = dynamic_cast<CoaMainWindow *>(object);
        if (window != 0){
           window->setWindowModified(flag);
        }
     }
     */
}



