#ifndef __CoaXmlItemModelReference_h__
#define __CoaXmlItemModelReference_h__

#include <QDomNode>


class CoaIODevice;
class CoaDomDocument;
class CoaXmlItemModel;

class CoaXmlItemModelReference: public QObject {
Q_OBJECT
public:
   CoaXmlItemModelReference();
   CoaXmlItemModelReference(QDomNode& node, int row=0, int level=0, CoaXmlItemModelReference* const parent=0);
   void refreshChilds();
   const bool isValid() const;

   CoaXmlItemModelReference*const child(const int row);
   const int countChildren() const;
   const int countAttributes() const;
   const bool hasChildren() const;
   const int level() const;
   const int row() const;
   const CoaString tagName() const;
   QDomNamedNodeMap attributes();
   QDomElement toElement();
   inline QDomNode& domNode() ;

protected:
   void dump() const;

private:
   friend class CoaXmlItemModel;
   virtual ~CoaXmlItemModelReference();
   QDomNode m_domNode;
   int      m_row;
   int      m_level;
};


QDomNode& CoaXmlItemModelReference::domNode()
{
   return m_domNode;
}




#endif //__CoaXmlItemModelReference_h__

