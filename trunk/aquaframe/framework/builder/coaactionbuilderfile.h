#ifndef __CoaActionBuilderFile_h__
#define __CoaActionBuilderFile_h__


#include <CoaActionBuilder>
#include <CoaMakros>

class CoaAction;

class CoaActionBuilderFile: public CoaActionBuilder {
Q_OBJECT

public:
   virtual bool mapActionString2ActionId(const QString& actionString, int *const actionId);
   virtual bool                  checkType (const int type);

protected:
   virtual void setObjectName                (CoaAction*const  action, const int type);
   virtual void setDefaultShortcut           (CoaAction*const  action, const int type);
   virtual void setShortcutContext           (CoaAction*const  action, const int type);
   virtual void setIcon                      (CoaAction*const  action, const int type);
   virtual void setToolTip                   (CoaAction*const  action, const int type);
   virtual void setStatusTip                 (CoaAction*const  action, const int type);
   virtual void setText                      (CoaAction*const  action, const int type);
   virtual void setEnabledForDefaultToolbar  (CoaAction*const  action, const int type);
   virtual void setEnabledForToolbar         (CoaAction*const  action, const int type);
   virtual void setWhatsThis                 (CoaAction*const  action, const int type);
   virtual void setActionBlock               (CoaAction*const  action, const int type);

private:
   COAMAKRO_DEKLARE_SINGLETONMETHODS(CoaActionBuilderFile);
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaActionBuilderFile);
   COAMAKRO_NO_COMPARE(CoaActionBuilderFile);

};



#endif //__CoaActionBuilderFile_h__

