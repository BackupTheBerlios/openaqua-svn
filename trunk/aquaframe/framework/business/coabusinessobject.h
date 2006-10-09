#ifndef __CoaBusinessObject_h__
#define __CoaBusinessObject_h__

#include <CoaMakros>

#include <QString>
#include <QObject>

class CoaMainThreadMaker;
class CoaWorkspace;

/**
@interface CoaBusinessObject
*/
class CoaBusinessObject: public QObject {
Q_OBJECT

public:
   CoaBusinessObject(const CoaMainThreadMaker *maker, const QString& objectname);
   virtual ~CoaBusinessObject();
   virtual void show();
   virtual void createMainMenu();
   virtual void createMainWindow();



signals:
   void isInitialized();

protected:
   inline CoaWorkspace    *getWorkspace();

private:
   void initialize();
   void initWorkspace();

private:
   CoaWorkspace    *m_workspace;
   bool             m_isInitialized;

   COAMAKRO_NO_COPYCONSTRUCTOR(CoaBusinessObject);
   COAMAKRO_NO_COMPARE(CoaBusinessObject);

};

inline CoaWorkspace* CoaBusinessObject::getWorkspace(){
   return m_workspace;
}

#endif //__CoaBusinessObject_h__

