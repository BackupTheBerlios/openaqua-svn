#ifndef __SessionReapThread__
#define __SessionReapThread__

#include <IceUtil/Thread.h>
#include <SessionI.hpp>

#include <list>
#include <utility>
typedef std::pair< ::OPI::SessionPrx, SessionIPtr > sessionpair;
typedef std::list< sessionpair > sessionlist;

class SessionReapThread : public IceUtil::Thread, public IceUtil::Monitor<IceUtil::Mutex>
{
private:
    const IceUtil::Time timeout;
    bool terminated;
    sessionlist sessions;

public:
    SessionReapThread();

    virtual void run();
    void terminate();
    void add(const ::OPI::SessionPrx&, const SessionIPtr&);

};
typedef IceUtil::Handle<SessionReapThread> SessionReapThreadPtr;

#endif
