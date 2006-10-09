#ifndef __TcpProxy__h__
#define __TcpProxy__h__
#include <CoaAbstractTcpProxyModel>
#include <CoaIODevice>

#include <CoaTcpSocket>
#include <CoaDomDocument>
#include <CoaString>

#include "actionmodel.h"



class TcpProxy: public CoaAbstractTcpProxyModel {
Q_OBJECT
public:
   TcpProxy(QObject* const parent = 0);
   virtual ~TcpProxy();

   virtual QModelIndex mapFromSource ( const QModelIndex & sourceIndex ) const;
   virtual QModelIndex mapToSource ( const QModelIndex & proxyIndex ) const;


   //Item access
   virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
   virtual QModelIndex parent(const QModelIndex &child) const;
   //CoaXmlItemModelReference * const index2reference(const QModelIndex &index) const;


   //Reading
   virtual QVariant data ( const QModelIndex & index, int role ) const;
   virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
   virtual int rowCount ( const QModelIndex & parent = QModelIndex()) const;
   virtual int columnCount ( const QModelIndex & parent ) const;


   //!@brief try to load xml data from a CoaIODevice
   virtual bool loadXmlData (CoaIODevice * const device);
   virtual bool saveXmlData (CoaIODevice * const device);

   const CoaString lastError() const;

private:
   CoaTcpSocket m_socket;
   ActionModel  *m_actionModel;
};

#endif //__TcpProxy__h__

