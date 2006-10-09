#ifndef __Session__
#define __Session__

#include <Ice/Ice.h>
#include <OPI.h>

#include <OPIFactoryI.hpp>

class SessionI : public ::OPI::Session, public IceUtil::Mutex
{
private:
    const std::string name;
    IceUtil::Time timeout;
    ::OPI::OPIFactoryPrx factory;
    bool destroy;
public:

    SessionI(const std::string&);

    virtual ::OPI::OPIFactoryPrx CreateSession(const Ice::Current&);
    virtual void Destroy(const Ice::Current&);
    virtual void TimeOut(const Ice::Int, const Ice::Current&);

    virtual std::string getName(const Ice::Current&);
    IceUtil::Time getTimeOut() const;
    virtual ~SessionI();
};
typedef IceUtil::Handle<SessionI> SessionIPtr;

#endif
