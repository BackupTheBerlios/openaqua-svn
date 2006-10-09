#ifndef __CoaDataSetModel_h__
#define __CoaDataSetModel_h__

#include <CoaThread>
#include <IoaDataSetWidget>
#include <CoaSet>
#include <CoaMap>
#include <CoaString>
#include <CoaMainWindow>


#include <QWriteLocker>
#include <QVariant>

//#include <set>



class CoaDataSetModel: public CoaThread
{
      Q_OBJECT

   public:
      typedef CoaMap<CoaString, QVariant> ValueMap;
      //typedef std::set<CoaString const&, QVariant const&> stdValueMap;

      CoaDataSetModel( QObject * parent = 0 );
      virtual ~CoaDataSetModel();

      //! @brief register a  IoaDataSetWidget widget
      void registerWidget( IoaDataSetWidget* const );
      //! @brief unregister a  IoaDataSetWidget widget
      void unregisterWidget( IoaDataSetWidget* const );

      //! @brief register all IoaDataSetWidget sub widgets
      void registerWidgets( QWidget const*const);
      //! @brief unregister all IoaDataSetWidget sub widgets
      void unregisterWidgets( QWidget const*const );
      
      //! @brief register all IoaDataSetWidget sub widgets
      void registerWidgets( const CoaMainWindow& );
      //! @brief unregister all IoaDataSetWidget sub widgets
      void unregisterWidgets( const CoaMainWindow& );
      
   
   public slots:
      virtual void updateWidgets( const CoaString& dataSetName, const ValueMap& );
      //virtual void updateWidgets( const CoaString& dataSetName, stdValueMap );

   private:
      QReadWriteLock m_Lock;
      CoaSet<IoaDataSetWidget* const> m_widgets;

};


#endif //__CoaDataSetModel_h__

