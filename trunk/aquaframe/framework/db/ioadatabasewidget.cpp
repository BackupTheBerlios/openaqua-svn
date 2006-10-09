#include "ioadatabasewidget.h"


IoaDatabaseWidget::IoaDatabaseWidget()
{
   resetDatabaseColumn();
   resetDatabaseTable();
   resetDatabaseEnabled();
   resetDatabaseHeader();
}




IoaDatabaseWidget::~IoaDatabaseWidget()
{}





void IoaDatabaseWidget::setDatabaseColumn( const int id )
{
   m_databaseColumn = id;
}




void IoaDatabaseWidget::resetDatabaseColumn()
{
   m_databaseColumn = -1;
}




int IoaDatabaseWidget::databaseColumn() const
{
   return m_databaseColumn;
}





void IoaDatabaseWidget::setDatabaseTable( const QString& t )
{
   m_databaseTable = t;
}




void IoaDatabaseWidget::resetDatabaseTable( )
{
   m_databaseTable = "";
}




QString IoaDatabaseWidget::databaseTable() const
{
   return m_databaseTable;
}


void IoaDatabaseWidget::setDatabaseEnabled( const bool t )
{
   m_databaseEnabled = t;
}
void IoaDatabaseWidget::resetDatabaseEnabled( )
{
   m_databaseEnabled = false;
}
bool IoaDatabaseWidget::databaseEnabled() const
{
   return m_databaseEnabled;
}

void IoaDatabaseWidget::setDatabaseHeader( const bool t )
{
   m_databaseHeader = t;
}
void IoaDatabaseWidget::resetDatabaseHeader( )
{
   m_databaseHeader = false;
}
bool IoaDatabaseWidget::databaseHeader() const
{
   return m_databaseHeader;
}

