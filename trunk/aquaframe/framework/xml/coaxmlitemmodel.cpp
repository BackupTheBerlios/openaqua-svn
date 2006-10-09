#include "coaxmlitemmodel.h"
#include <CoaDebug>

#include <CoaIODevice>
#include <CoaXmlItemModelReference>

#include <QDomElement>



const int SLEEP=50000;
#include <unistd.h>


CoaXmlItemModel::CoaXmlItemModel(QObject *parent)
: CoaAbstractItemModel(parent)
, m_domTree(0)
{
   BEGIN;
   reset();
}



void CoaXmlItemModel::reset ()
{
   delete m_domTree;
   QDomNode node = m_domDocument.documentElement();
   m_domTree = new CoaXmlItemModelReference(node, 0, 0, 0);
   CoaAbstractItemModel::reset();
}




CoaXmlItemModel::~CoaXmlItemModel()
{
   BEGIN;
   delete m_domTree;
}



/**

The method simply reads the device content in a CoaDomDocument and calls
loadXmlData (CoaDomDocument const * const doc) for further parsing.

If you want to check for certain information like correct xml version then
overwrite this method, do the checks and call loadXmlData (CoaDomDocument const * const doc)

@result successfull or not use lastError() to get more information in case of an error
*/
bool CoaXmlItemModel::loadXmlData (CoaIODevice * const device)
{
   BEGIN;
   bool result = false;
   //some checks
   if (device == 0){
      setLastError(tr("given Device for xml loading is a NULL pointer"));
      ERR(lastError());
      RETURN(result);
   }

   CoaString       errorStr;
   int             errorLine;
   int             errorColumn;


   //read the source
   result = m_domDocument.setContent(device, &errorStr, &errorLine, &errorColumn);
   if (result != true) {
      CoaString error = CoaString(tr("Error while reading xml file in Line %1, Col %2: %3").arg(errorLine).arg(errorColumn).arg(errorStr));
      setLastError(error);
   }

   reset();
   RETURN(result);
}//


bool CoaXmlItemModel::saveXmlData (CoaIODevice * const device)
{
   BEGIN;
   bool result = false;
   //some checks
   if (device == 0){
      setLastError(tr("given Device for xml loading is a NULL pointer"));
      ERR(lastError());
      RETURN(result);
   }

   device->open(QIODevice::WriteOnly);
   qint64 i = device->write(m_domDocument.toByteArray(3));
   if (i < 0){
      setLastError(tr("Cannot write "));
      ERR(lastError());
      RETURN(result);
   } else {
      result = true;
   }


   RETURN(result);
}


/**

@warning by default the method creates just a reference.

@param doc the Xml Document
@param deepCopy make a real, deep copy
*/
bool CoaXmlItemModel::loadXmlData (const CoaDomDocument& doc, const bool deepCopy)
{
   BEGIN;
   if (deepCopy == true) {
      m_domDocument = doc.cloneNode(true).toDocument();
   } else {
      m_domDocument = doc;
   }
   reset();
   RETURN(true);
}


/**

The string is meant to be used in a GUI, so it should be human readable
@see setLastError(const CoaString& lastError)
*/
const CoaString CoaXmlItemModel::lastError() const
{
   BEGIN;
   RETURN(m_lastError);
}


/**

The string is meant to be used in a GUI, so it should be human readable
@see lastError() const
*/
void CoaXmlItemModel::setLastError(const CoaString& lastError)
{
   BEGIN;
   m_lastError = lastError;
}




/**
@brief Returns the index of the item in the model specified by the given row, column and parent index.
*/
QModelIndex CoaXmlItemModel::index(int row, int col, const QModelIndex &parent) const
{
   //usleep(SLEEP);
   CoaXmlItemModelReference *parentItem;
   if (!parent.isValid())   parentItem = m_domTree;
   else                     parentItem = static_cast<CoaXmlItemModelReference*>(parent.internalPointer());

   CoaXmlItemModelReference *childItem = parentItem->child(row);
   if (childItem)  return createIndex(row, col, childItem);
   else            return QModelIndex();
}





/**
@brief @return the parent for the given index.

@result returns an inValid QModelIndex if there is no parent!
*/
QModelIndex CoaXmlItemModel::parent(const QModelIndex &index) const
{
   if (!index.isValid())   return QModelIndex();
   //usleep(SLEEP);

   CoaXmlItemModelReference *childItem =  static_cast<CoaXmlItemModelReference*>(index.internalPointer());
   CoaXmlItemModelReference *parentItem = static_cast<CoaXmlItemModelReference*>(childItem->parent());

   if (parentItem == m_domTree) return QModelIndex();
   return createIndex(parentItem->row(), 0, parentItem);
}


/**

@param tagName the string within the brackets <tagName>
@param attrName the attribute name <tagName attributeName="foo">
@param an identifier.

Example:
@code
   setAttributeId("action", "name", 1);
   setAttributeId("action", "type", 2);
   setAttributeId("folder", "name", 1);
@endcode

*/
void CoaXmlItemModel::setAttributeAndId(const CoaString& tagName, const CoaString& attrName, const int columnId)
{
   //some checks
   if (tagName.isEmpty()) return;
   if (attrName.isEmpty()) return;

   //update the ID to Attributename mapping
   CoaMap<int, CoaString> mapI2A = m_xmlId2Attribute.value(tagName);
   mapI2A[columnId] = attrName;
   m_xmlId2Attribute[tagName] = mapI2A;

   //update the Attributename to ID mapping
   CoaMap< CoaString, int> mapA2I = m_xmlAttribute2Id.value(tagName);
   mapA2I[attrName] = columnId;
   m_xmlAttribute2Id[tagName] = mapA2I;
}



const int CoaXmlItemModel::mapAttributeName2Column(const CoaString& tagName, const CoaString& attrName, const int defaultValue) const
{
   //some checks
   if (tagName.isEmpty()) return defaultValue;
   if (attrName.isEmpty()) return defaultValue;

   //do the lookup
   CoaMap<CoaString, CoaMap<CoaString, int> >::const_iterator it = m_xmlAttribute2Id.find(tagName);
   if (it == m_xmlAttribute2Id.end()) return defaultValue;
   return it->value(attrName, defaultValue);

}



/**
@Maps the column() from a QModelIndex to a

*/
const CoaString CoaXmlItemModel::mapColumn2AttributeName(const CoaString& tagName, const int columnId, const CoaString& defaultValue) const
{
   //some checks
   if (tagName.isEmpty()) return defaultValue;
   if (columnId < 0) return defaultValue;

   //do the lookup
   CoaMap<CoaString, CoaMap<int, CoaString> >::const_iterator it = m_xmlId2Attribute.find(tagName);
   if (it == m_xmlId2Attribute.end()) return defaultValue;
   return it->value(columnId, defaultValue);
}

/**
@brief Maps the column() from a QModelIndex to a attributeName

*/
const CoaString CoaXmlItemModel::mapIndex2AttributeName(const QModelIndex & index, const CoaString& defaultValue) const
{
   CoaXmlItemModelReference * ref = index2reference(index);
   if (ref == 0) return defaultValue;
   return mapColumn2AttributeName(ref->tagName(), index.column(), defaultValue);
}



QVariant CoaXmlItemModel::data ( const QModelIndex & index, int role ) const
{
   switch( role )
   {
   case Qt::DisplayRole:
   case Qt::EditRole:
   {
      usleep(SLEEP);
      //get the reference
      CoaXmlItemModelReference * const ref = index2reference(index);

      //check the reference
      if (ref == 0)        return QVariant();
      if (!ref->isValid()) return QVariant();


      QDomElement e = ref->toElement();

      //column 0 -> tagname
      if (index.column() == 0){
         return e.tagName();
      }

      //column > 0 -> attribute
      if (index.column() > 0 ){
         const CoaString attribute = mapIndex2AttributeName(index, "");
         if (attribute.isEmpty()){
            //default handling
            QDomNamedNodeMap map = ref->attributes ();
            QDomAttr a = map.item(index.column()-1).toAttr();
            if (a.isNull()) return QVariant();
            return a.value();
         } else {
            return e.attribute(attribute, "");
         }
      }

      //bye bye
      break;
    }
   }

   return(QVariant());

}


bool CoaXmlItemModel::setData ( const QModelIndex & index, const QVariant & value, int role)
{
   BEGIN;
   if (role != Qt::EditRole) return false;
   if (!index.isValid()) return false;
   //usleep(SLEEP);
   const CoaString attr = mapIndex2AttributeName(index, "");
   if (attr.isEmpty()) return false;

   QDomElement e = index2DomElement(index);
   if (e.isNull()) return false;

   e.setAttribute(attr, value.toString());
   return true;

}


QVariant CoaXmlItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   switch( role )
   {
   case Qt::DisplayRole:
      //usleep(SLEEP);
      if( orientation == Qt::Horizontal ) {
         return (CoaString("Col %1").arg(section));
      } else {
         return (CoaString("Row %1").arg(section));
      }
   }
   return QVariant();
}





int CoaXmlItemModel::rowCount ( const QModelIndex & parent) const
{
   CoaXmlItemModelReference *parentItem;

   //usleep(SLEEP);
   if (!parent.isValid()) parentItem = m_domTree;
   else                   parentItem = static_cast<CoaXmlItemModelReference*>(parent.internalPointer());

   if (parentItem == 0) return 0;
   else                 return parentItem->countChildren();
}





/**
@result returns the amount of attributes plus 1 (for the tagName)
*/
int CoaXmlItemModel::columnCount ( const QModelIndex & parent ) const
{

   CoaXmlItemModelReference *parentItem;
   //usleep(SLEEP);

   if (!parent.isValid()) parentItem = m_domTree;
   else                   parentItem = static_cast<CoaXmlItemModelReference*>(parent.internalPointer());

   assert(parentItem);
   return  1 + parentItem->countAttributes();

#if 0
   //iterates over the children and get the max columncount
   int result = parentItem->countAttributes();
   foreach (QObject *object, parentItem->children()){
      CoaXmlItemModelReference *child = static_cast<CoaXmlItemModelReference*>(object);
      assert(child);
      if (child != 0){
         result = qMax(result, child->countAttributes());
      }
   }

   result += 1; //tagname + attributes
   return result;
#endif
}




CoaXmlItemModelReference * const CoaXmlItemModel::index2reference(const QModelIndex &index) const
{
   if (!index.isValid())   return 0;
   return static_cast<CoaXmlItemModelReference*>(index.internalPointer());
}




QDomNode CoaXmlItemModel::index2DomNode(const QModelIndex & index) const
{
   if (index.isValid())
      return static_cast<CoaXmlItemModelReference*>(index.internalPointer())->domNode();
   else
      return m_domTree->domNode();

}


QDomElement CoaXmlItemModel::index2DomElement(const QModelIndex & index) const
{
   return index2DomNode(index).toElement();
}


const CoaString   CoaXmlItemModel::index2TagName(const QModelIndex & index) const
{
   return index2DomElement(index).tagName();
}


const CoaString CoaXmlItemModel::documentType() const
{
   BEGIN;
   assert(m_domTree);
   QDomElement root = m_domDocument.documentElement();
   if (root.isNull()) {
      RETURN(CoaString(""));
   } else {
      RETURN(root.tagName());
   }
}


const CoaString CoaXmlItemModel::documentVersion() const
{
   BEGIN;
   assert(m_domTree);
   QDomElement root = m_domDocument.documentElement();
   if (root.isNull() || !root.hasAttribute("version")) {
      RETURN(CoaString(""));
   } else {
      RETURN(root.attribute("version"));
   }
}


void CoaXmlItemModel::setDocumentType(const CoaString& doctype)
{
   BEGIN;
   assert(m_domTree);
   QDomElement root = m_domDocument.documentElement();
   if (root.isNull()) {
      QDomElement root = m_domDocument.createElement(doctype);
      m_domDocument.appendChild(root);
   } else {
      root.setTagName(doctype);
   }
}


void CoaXmlItemModel::setDocumentVersion(const CoaString& version)
{
   BEGIN;
   assert(m_domTree);
   QDomElement root = m_domDocument.documentElement();
   if (root.isNull()) {
      ERR("No root element in XML document");
   } else {
      root.setAttribute("version", version);
   }
}




