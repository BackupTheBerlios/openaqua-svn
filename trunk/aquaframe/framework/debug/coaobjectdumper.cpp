#include <iostream>
#include <CoaIoStream>
#include "coaobjectdumper.h"
using namespace std;

void CoaObjectDumper::Dump(const QDomNode& n, const int indentLevel)
{
   CoaString spaces;
   spaces.fill(' ', indentLevel * 3);

   //dump null nodes
   if (n.isNull()) {
      cout << spaces << "QDomNode(NULL)" << endl;
      return;
   }

   const QDomNodeList list     = n.childNodes();
   const QDomElement e         = n.toElement();

   //open tag
   cout << spaces << '<' << e.tagName();

   //dump attributes
   const QDomNamedNodeMap nodeMap = n.attributes ();
   for (uint i = 0; i <= nodeMap.length(); ++i){
      const QDomAttr attr = nodeMap.item(i).toAttr();
      if (!attr.isNull()){
         cout << " " << attr.name() << "=\"" << attr.value() << '\"';
      }
   }

   //close tag
   if (list.count() == 0) cout << " / >" << endl;
   else                   cout << '>'    << endl;


   //dump sub nodes
   for (uint i = 0; i < list.length(); ++i)
   {
      CoaObjectDumper::Dump(list.item(i), indentLevel + 1);
   }

   if (list.count() > 0)
      cout << spaces << "</" << e.tagName() << '>' << endl;

}


void CoaObjectDumper::Dump(const QDomElement& e, const int indentLevel)
{
   Q_UNUSED(e);
   Q_UNUSED(indentLevel);
   cout << "unsupported dump" <<endl;

}



void CoaObjectDumper::Dump(const QModelIndex& e, const int indentLevel)
{
   Q_UNUSED(indentLevel);

   if (e.isValid() ) {
      cout << CoaString("row=%1 col=%2 int=%3").arg(e.row()).arg(e.column()).arg(e.internalId());
   } else {
      cout << "invalid";
   }
}


void CoaObjectDumper::Dump(const QRegion& e, const int indentLevel)
{
   Q_UNUSED(indentLevel);
   if (e.isEmpty()) {
      cout << "QRegion(empty)" << endl;
   } else {
      //cout << CoaString ("QRegion(x=%1, y=%2, )").arg(e.;
   }
}



void CoaObjectDumper::Dump(const QRect& e, const int indentLevel)
{
   Q_UNUSED(indentLevel);
   if (e.isNull()) {
      cout << "QPoint(NULL)" << endl;
   } else {
      cout << CoaString ("QPoint(x=%1, y=%2)").arg(e.x()).arg(e.y());
   }
}


CoaString CoaObjectDumper::Dump2String(const QPoint& e) 
{
   if (e.isNull()) {
      return(CoaString( "QPoint(NULL)"));
   } else {
      CoaString r = CoaString ("QPoint(x=%1, y=%2)").arg(e.x()).arg(e.y());
      return r;
   }
}


void CoaObjectDumper::Dump(const QPoint& e, const int indentLevel)
{
   Q_UNUSED(indentLevel);
   cout << Dump2String(e) << endl;
}





