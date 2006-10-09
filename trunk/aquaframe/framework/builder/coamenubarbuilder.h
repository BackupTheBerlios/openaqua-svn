#ifndef __CoaMenuBarBuilder_h__
#define __CoaMenuBarBuilder_h__


#include <CoaFile>

#include <QObject>
#include <QDomNode>


class CoaMenu;
class CoaMenuBar;


class CoaMenuBarBuilder: public QObject {
  Q_OBJECT

public:
   CoaMenuBarBuilder(QObject *parent = 0);
   virtual CoaMenuBar*const getMenuBar(CoaFile *const file);


protected:
   virtual void             parseMenu(const QDomNode &node, CoaMenu*const menu);

};


#endif

