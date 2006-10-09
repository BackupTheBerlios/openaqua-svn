#ifndef __CoaActionBuilderDebug_h__
#define __CoaActionBuilderDebug_h__


#include <CoaActionBuilder>
#include <CoaMakros>
#include <CoaDefaultActions>

class CoaAction;

class CoaActionBuilderDebug: public CoaActionBuilder {
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
   CoaDefaultActions::actionDebug  mapInt2Enum(const int i, bool *works=0) const;
   
   
   COAMAKRO_DEKLARE_SINGLETONMETHODS(CoaActionBuilderDebug);
   COAMAKRO_NO_COPYCONSTRUCTOR(CoaActionBuilderDebug);
   COAMAKRO_NO_COMPARE(CoaActionBuilderDebug);

};



#endif //__CoaActionBuilderDebug_h__

