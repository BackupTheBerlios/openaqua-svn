#ifndef __CorbaClient__h__
#define __CorbaClient__h__

#include <CoaDataSetModel>
#include <CoaMap>

#include "contactC.h"

#include <QObject>
#include <QVariant>

class CorbaClient: public QObject
{
   Q_OBJECT
   public:
      explicit CorbaClient(CoaDataSetModel& m_dataSetModel, QObject *const parent = 0);
      virtual ~CorbaClient ( );
      virtual bool isValid() const;
      void initialize();

   public slots:
      void slotGotoFirst();
      void slotGotoPrev();
      void slotGotoNext();
      void slotGotoLast();


   protected slots:
      void getData();

   private:
      bool m_valid;
      XENON::Contact_Factory_var m_contact_Factory;
      CoaDataSetModel         &m_dataSetModel;
      CoaDataSetModel::ValueMap m_valueMap;


};

#endif //__CorbaClient__h__

