#ifndef __CoaActionGroup_h__
#define __CoaActionGroup_h__

#include <QActionGroup>
#include <QList>

class QObject;
class CoaAction;
class CoaSignal;

class CoaActionGroup: public QActionGroup
{
   Q_OBJECT

public:

   CoaActionGroup( QObject * parent);
   virtual ~CoaActionGroup();

   CoaAction* addAction (CoaAction*);


public slots:
   virtual void handleSignal(CoaSignal const*const);
//   virtual void sendOutSignals(CoaSignal const*const);

signals:
   //send to all receivers, execpt the own Actions
   void signal(CoaSignal const*const);

   //send to its own actions
   void signalIntern(CoaSignal const*const);

private:
   //not implemented
   CoaActionGroup( );

};

#endif //__CoaActionGroup_h__
