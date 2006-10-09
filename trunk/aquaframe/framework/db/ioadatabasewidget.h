#ifndef __IoaDatabaseWidget_h__
#define __IoaDatabaseWidget_h__

#include <CoaString>


/**
@interface IoaDatabaseWidget

@brief makes widgets database aware

common properties:

@code
   Q_PROPERTY( bool databaseEnabled  READ databaseEnabled WRITE setDatabaseEnabled RESET resetDatabaseEnabled STORED true )
   Q_PROPERTY( bool databaseHeader   READ databaseHeader  WRITE setDatabaseHeader  RESET resetDatabaseHeader  STORED true )
   Q_PROPERTY( int databaseColumn    READ databaseColumn WRITE setDatabaseColumn   RESET resetDatabaseColumn  STORED true )
   Q_PROPERTY( QString databaseTable READ databaseTable WRITE setDatabaseTable     RESET resetDatabaseTable   STORED true )
@endcode
*/

class IoaDatabaseWidget
{
public:
   IoaDatabaseWidget();
   virtual ~IoaDatabaseWidget();

   virtual void setDatabaseColumn( const int id );
   virtual void resetDatabaseColumn();
   virtual int databaseColumn() const;

   virtual void setDatabaseTable( const QString& t );
   virtual void resetDatabaseTable( );
   virtual QString databaseTable() const;

   virtual void setDatabaseEnabled( const bool t );
   virtual void resetDatabaseEnabled( );
   virtual bool databaseEnabled() const;

   virtual void setDatabaseHeader( const bool t );
   virtual void resetDatabaseHeader( );
   virtual bool databaseHeader() const;

private:
   int m_databaseColumn;
   QString m_databaseTable;
   bool m_databaseHeader;
   bool m_databaseEnabled;

};





#endif //__IoaDatabaseWidget_h__

