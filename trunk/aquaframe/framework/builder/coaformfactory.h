#ifndef __CoaFormFactory_h__
#define __CoaFormFactory_h__


#include <QString>
#include <QObject>

class CoaMainWindow;
class CoaDialog;
class CoaWidget;


/**
@brief creates a GUI widget from a Designer ui file
*/
class CoaFormFactory: public QObject
{
Q_OBJECT
public:
   CoaFormFactory(CoaMainWindow* const parent);
   CoaFormFactory(CoaWidget* const parent);
   CoaFormFactory(CoaDialog* const parent);
   virtual ~CoaFormFactory();

   /**
   @param filename filename from where the Factory builds a GUI
   @param parent the parent Widgets (regulary a CoaMainWindow)
   */
   virtual bool formBuild      (QString filename);
   virtual void statusBarBuild (QString filename);
   virtual void toolBarBuild   (QString filename);
   virtual void menuBarBuild   (QString filename);


private:
   CoaFormFactory();
   QWidget* getParentWidget();
   QWidget* m_parentWidget;
};



#endif
