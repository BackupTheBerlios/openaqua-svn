#include "ioadatasetwidget.h"


IoaDataSetWidget::IoaDataSetWidget()
   : m_dataSet()
   , m_dataSetColumn()
{
}




IoaDataSetWidget::~IoaDataSetWidget()
{}




void IoaDataSetWidget::setDataSetName( const QString& s)
{
   m_dataSet =s;
}


void IoaDataSetWidget::resetDataSetName()
{
   m_dataSet.clear();
}


const QString& IoaDataSetWidget::dataSetName() const
{
   return m_dataSet;
}



void IoaDataSetWidget::setDataSetColName( const QString& s)
{
   m_dataSetColumn = s;
}


void IoaDataSetWidget::resetDataSetColName()
{
   m_dataSetColumn.clear();
}


const QString& IoaDataSetWidget::dataSetColName() const
{
   return m_dataSetColumn;
}




