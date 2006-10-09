#include "coaxmlitemmodelreference.h"
#include <CoaDebug>

#include <CoaList>


CoaXmlItemModelReference::CoaXmlItemModelReference()
: QObject(0)
, m_domNode()
, m_row(0)
, m_level(0)
{
   BEGIN;
}




CoaXmlItemModelReference::CoaXmlItemModelReference(QDomNode& node, int row, int level, CoaXmlItemModelReference* const parent)
: QObject(parent)
, m_domNode(node)
, m_row(row)
, m_level(level)
{
   //BEGIN;
   QDomElement e = node.toElement();
   //INF(CoaString("create CoaXmlItemModelReference for tag %1 <%2>").arg(CoaString().fill(' ', level * 3)).arg(e.tagName()));
   refreshChilds();
}




CoaXmlItemModelReference::~CoaXmlItemModelReference()
{
   //BEGIN;
   QDomElement e = m_domNode.toElement();
   //INF(CoaString("delete CoaXmlItemModelReference for tag %1 <%2>").arg(CoaString().fill(' ', level() * 3)).arg(e.tagName()));
}




const bool CoaXmlItemModelReference::isValid() const
{
   return !m_domNode.isNull();
}






CoaXmlItemModelReference*const CoaXmlItemModelReference::child(const int row)
{
   if (!isValid()) return 0;
   if (row > countChildren()) return 0;
   return static_cast<CoaXmlItemModelReference*> (children().value(row));

   //maybe using at() -> its faster
   //return static_cast<CoaXmlItemModelReference*> (children().at(row));
}




const bool CoaXmlItemModelReference::hasChildren() const
{
   if (!isValid()) return false;
   if (countChildren() > 0) return true;
   else return false;
}




const int CoaXmlItemModelReference::level() const
{
   return m_level;
}



const int CoaXmlItemModelReference::row() const
{
   return m_row;
}


const int CoaXmlItemModelReference::countChildren() const
{
   if (!isValid())         return -1;
   else                    return children().count();
}



const int CoaXmlItemModelReference::countAttributes() const
{
   if (!isValid())         return -1;
   return m_domNode.attributes().count();
}



const CoaString CoaXmlItemModelReference::tagName() const
{
   if (!isValid())         return "";
   return m_domNode.toElement().tagName();
}





QDomNamedNodeMap CoaXmlItemModelReference::attributes()
{
   QDomElement e = m_domNode.toElement();
   return e.attributes();
}





QDomElement CoaXmlItemModelReference::toElement()
{
   return m_domNode.toElement();
}





void CoaXmlItemModelReference::refreshChilds()
{
   //BEGIN;
   if (!isValid()) return;

   //delete all children
   QObjectList listOfAllChildren = children();
   while (!listOfAllChildren.isEmpty()) delete listOfAllChildren.takeFirst();

   //create a list of new children
   QDomNodeList list = m_domNode.childNodes();
   for (int i = 0 ; i < list.count(); ++i){
      QDomNode n = list.item(i);
      if (n.isNull()) break;
      new CoaXmlItemModelReference(n, i, m_level+1, this); //ignore the result!
   }

}




void CoaXmlItemModelReference::dump() const
{
   BEGIN;
   CoaString valid;
   if (isValid()) valid = "true";
   else           valid = "false";

   CoaString d = CoaString("row=%1 level=%2 valid=%3 tagName=%4 attr=%5").arg(row()).arg(level()).arg(valid).arg(tagName()).arg(countAttributes());
   INF(d);
}

