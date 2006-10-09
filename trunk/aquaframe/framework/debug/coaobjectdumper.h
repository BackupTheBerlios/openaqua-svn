#ifndef __CoaObjectDumper_h__
#define __CoaObjectDumper_h__


#include <QDomNode>
#include <QDomElement>
#include <QModelIndex>
#include <QRegion>
#include <QRect>
#include <QPoint>
#include <CoaString>



class CoaObjectDumper {
public:
   static void Dump(const QDomNode& n,      const int indentLevel=0) ;
   static void Dump(const QDomElement& e,   const int indentLevel=0) ;
   static void Dump(const QModelIndex& e,   const int indentLevel=0) ;
   static void Dump(const QRegion& e,       const int indentLevel=0) ;
   static void Dump(const QRect& e,         const int indentLevel=0) ;
   static CoaString Dump2String(const QPoint& e) ;
   static void Dump(const QPoint& e,        const int indentLevel=0) ;
};




#endif // __CoaObjectDumper_h__

