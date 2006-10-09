#include <SessionFactoryI.hpp>

using namespace std;

SessionFactoryI::SessionFactoryI(const SessionReapThreadPtr& reapThread) :
    reaper(reapThread)
{
}

::OPI::SessionPrx
SessionFactoryI::CreateProxy(const string& name, const Ice::Current& c)
{
    SessionIPtr session = new SessionI(name);
    ::OPI::SessionPrx proxy = ::OPI::SessionPrx::uncheckedCast(c.adapter->addWithUUID(session));
    reaper->add(proxy, session);
    return proxy;
}

void
SessionFactoryI::shutdown(const Ice::Current& c)
{
    cout << "Shutting SessionFactory down..." << endl;
    c.adapter->getCommunicator()->shutdown();
}
