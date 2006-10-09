#ifndef __CoaToolBarBuilder_h__
#define __CoaToolBarBuilder_h__


#include <CoaFile>

#include <QObject>
#include <QDomNode>

class CoaMenu;
class CoaToolBar;


class CoaToolBarBuilder: public QObject {
  Q_OBJECT

public:
   CoaToolBarBuilder(QObject *parent = 0);
   virtual CoaToolBar*const getToolBar(CoaFile *const file);

protected:
   virtual void addMenu      (const QDomNode& element, CoaToolBar *const toolBar);
   virtual void addAction    (const QDomNode& element, CoaToolBar *const toolBar);
   virtual void addGroup     (const QDomNode& element, CoaToolBar *const toolBar);
   virtual void addSeparator (const QDomNode& element, CoaToolBar *const toolBar);
   virtual void parseMenu    (const QDomNode &node, CoaMenu* const menu);
};


#endif

