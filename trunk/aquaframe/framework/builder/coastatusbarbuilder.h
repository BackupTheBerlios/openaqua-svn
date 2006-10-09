#ifndef __CoaStatusBarBuilder_h__
#define __CoaStatusBarBuilder_h__


#include <CoaFile>

#include <QObject>


class CoaStatusBar;
class CoaMainWindow;


class CoaStatusBarBuilder: public QObject {

   Q_OBJECT
   Q_CLASSINFO("Version", "1.0.0")


public:
   CoaStatusBarBuilder();
   virtual CoaStatusBar* load(CoaFile* file, CoaMainWindow *parent);

};


#endif

