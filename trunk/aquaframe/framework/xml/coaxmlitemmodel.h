#ifndef __CoaXmlItemModel_h__
#define __CoaXmlItemModel_h__

#include <CoaAbstractItemModel>
#include <CoaDomDocument>
#include <CoaMap>
#include <CoaString>

#include <QModelIndex>
#include <QDomElement>
#include <QDomNode>


#include <CoaIODevice>
class CoaXmlItemModelReference;


class CoaXmlItemModel: public CoaAbstractItemModel
{
Q_OBJECT
public:
   //!@brief constructor
   CoaXmlItemModel(QObject *parent=0);

   //!@brief destructor
   virtual ~CoaXmlItemModel();

   void reset ();

   //!@brief try to load xml data from a CoaIODevice
   virtual bool loadXmlData (CoaIODevice * const device);

   //!@brief load data from a XML Dom Document
   virtual bool loadXmlData (const CoaDomDocument& doc, const bool deepCopy = false);

   //!@brief try to save xml data from a CoaIODevice
   virtual bool saveXmlData (CoaIODevice * const device);

   //!returns a formated (and maybe translated string) with the last error
   const CoaString lastError() const;

   //!returns set a formated (and maybe translated string) with the last error
   void setLastError(const CoaString& lastError);


   //Access methods


   //Item access
   virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
   virtual QModelIndex parent(const QModelIndex &child) const;
   CoaXmlItemModelReference * const index2reference(const QModelIndex &index) const;


   //Reading
   virtual QVariant data ( const QModelIndex & index, int role ) const;
   virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
   virtual int rowCount ( const QModelIndex & parent = QModelIndex()) const;
   virtual int columnCount ( const QModelIndex & parent ) const;


   //document handling
   const CoaString documentType() const;
   const CoaString documentVersion() const;
   void setDocumentType(const CoaString& doctype);
   void setDocumentVersion(const CoaString& version);

   //Editing
   virtual bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );



protected:
   QDomNode          index2DomNode(const QModelIndex & index) const;
   QDomElement       index2DomElement(const QModelIndex & index) const;
   const CoaString   index2TagName(const QModelIndex & index) const;

   void setAttributeAndId(const CoaString& tagName, const CoaString& attrName, const int columnId);
   const int       mapAttributeName2Column(const CoaString& tagName, const CoaString& attrName, const int defaultValue=-1) const;
   const CoaString mapColumn2AttributeName(const CoaString& tagName, const int columnId, const CoaString& defaultValue =CoaString()) const;
   const CoaString mapIndex2AttributeName (const QModelIndex & index, const CoaString& defaultValue=CoaString()) const;

private:

   //!A paralel tree for the QDomDocument Tree
   CoaXmlItemModelReference                  *m_domTree;

   //!may have an string with the last error.
   CoaString                                  m_lastError;

   //!The document itself
   CoaDomDocument                             m_domDocument;

   //!a mapping column ID <-> Attribute Name
   CoaMap<CoaString, CoaMap<CoaString, int> > m_xmlAttribute2Id;
   CoaMap<CoaString, CoaMap<int, CoaString> > m_xmlId2Attribute;


};

#endif //__CoaXmlItemModel_h__

