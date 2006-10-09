#include "coadatasetmodel.h"
#include <CoaDebug>


CoaDataSetModel::CoaDataSetModel( QObject * parent)
   :   CoaThread("dsetmodl", parent)
{
   BEGIN;
}


CoaDataSetModel::~CoaDataSetModel()
{
   BEGIN;
   m_widgets.clear();//not really useful, but good for syntax checker
}

void CoaDataSetModel::registerWidget(IoaDataSetWidget* const w)
{
   BEGIN;
   if (w==0) return;

   //INF(QString("register widget %1").arg(dynamic_cast<QWidget*>(w)->objectName()));

   if (!m_widgets.contains(w))
   {
      QWriteLocker locker(&m_Lock);
      m_widgets.insert(w);
   }
}


void CoaDataSetModel::unregisterWidget(IoaDataSetWidget* const w)
{
   BEGIN;
   if (w==0) return;

   if (m_widgets.contains(w))
   {
      QWriteLocker locker(&m_Lock);
      m_widgets.remove(w);
   }
}



void CoaDataSetModel::registerWidgets( QWidget const*const w)
{
   if (w == 0)return;
   BEGIN;
   foreach(QObject *o, w->children ())
   {
      registerWidget(dynamic_cast<IoaDataSetWidget *>(o));
      registerWidgets(dynamic_cast<QWidget *>(o));
   }
}


void CoaDataSetModel::unregisterWidgets( QWidget const*const w)
{
   if (w == 0)return;
   BEGIN;
   foreach(QObject *o, w->children ())
   {
      unregisterWidget(dynamic_cast<IoaDataSetWidget *>(o));
      unregisterWidgets(dynamic_cast<QWidget *>(o));
   }
}


void CoaDataSetModel::registerWidgets( const CoaMainWindow& mw)
{
   BEGIN;
   registerWidgets (mw.centralWidget());
}


void CoaDataSetModel::unregisterWidgets( const CoaMainWindow& mw)
{
   BEGIN;
   unregisterWidgets (mw.centralWidget());
}






void CoaDataSetModel::updateWidgets(const CoaString& dataSetName, const ValueMap& valueMap)
{
   BEGIN;

   //iterate over widgets and update them
   foreach(IoaDataSetWidget* const w, m_widgets)
   {
      if(dataSetName == w->dataSetName())
      {
         const ValueMap::const_iterator pos=valueMap.find(w->dataSetColName() );
         if (pos != valueMap.end())
         {
            //QWidget  *const foo = dynamic_cast<QWidget*>(w);
            //if (foo != 0){
            //   INF(QString("update widget %1").arg(foo->objectName()));
            //}
            w->updateValue(pos.value());
         }
      } else {
         //INF(QString("%1 != %2").arg(dataSetName ).arg(w->dataSetName()));
      }
   }
   //INF("fertig");
}

