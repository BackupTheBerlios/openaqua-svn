#ifndef __ActionDocument_h__
#define __ActionDocument_h__

#include <QObject>

class MainWindow;
class ActionModel;
class CoaWorkbench;

class ActionDocument: public QObject
{
Q_OBJECT
public:
   ActionDocument(const CoaString& objectName,  CoaWorkbench *const parent=0, Qt::WFlags flags=0);
   virtual ~ActionDocument();
   bool initialize();

public slots:
   virtual bool slotFileSave();
   virtual bool slotFileNew();
   virtual bool slotFileClose();
   virtual bool slotFileOpen(const QIODevice &device);



private:
   MainWindow   *m_docWindow;
   ActionModel  *m_docDataModel;
   Qt::WFlags   m_flags;

};


#endif //__ActionDocument_h__

