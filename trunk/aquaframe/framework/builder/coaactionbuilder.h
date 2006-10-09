#ifndef __CoaActionBuilder_h__
#define __CoaActionBuilder_h__


#include <QObject>
#include <CoaMakros>

class CoaAction;

class CoaActionBuilder: public QObject {
Q_OBJECT

public:
   CoaActionBuilder ();
   virtual ~CoaActionBuilder();
   virtual CoaAction*const       getAction(const int type);
   virtual CoaAction*const       getAction(const QString&);
   virtual bool                  checkType(const QString& type);
   virtual bool                  checkType(const int type) = 0;
   virtual bool                  mapActionString2ActionId(const QString& actionString, int *const actionId) = 0;


protected:
   virtual void setObjectName                (CoaAction*const  action, const int type) = 0;
   virtual void setDefaultShortcut           (CoaAction*const  action, const int type) = 0;
   virtual void setShortcutContext           (CoaAction*const  action, const int type) = 0;
   virtual void setIcon                      (CoaAction*const  action, const int type) = 0;
   virtual void setToolTip                   (CoaAction*const  action, const int type) = 0;
   virtual void setStatusTip                 (CoaAction*const  action, const int type) = 0;
   virtual void setText                      (CoaAction*const  action, const int type) = 0;
   virtual void setEnabledForDefaultToolbar  (CoaAction*const  action, const int type) = 0;
   virtual void setEnabledForToolbar         (CoaAction*const  action, const int type) = 0;
   virtual void setWhatsThis                 (CoaAction*const  action, const int type) = 0;
   virtual void setActionBlock               (CoaAction*const  action, const int type) = 0;


private:
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaActionBuilder);
   COAMAKRO_NO_COMPARE(CoaActionBuilder);


};



#endif //__CoaActionBuilder_h__

