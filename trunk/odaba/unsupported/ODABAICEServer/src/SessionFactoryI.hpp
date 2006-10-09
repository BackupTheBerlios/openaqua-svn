#ifndef __SessionFactoryI__
#define __SessionFactoryI__

#include <Ice/Ice.h>
#include <OPI.h>
#include <SessionI.hpp>
#include <SessionReapThread.hpp>

class SessionFactoryI : public ::OPI::SessionFactory
{
private:
    SessionReapThreadPtr reaper;

public:
    SessionFactoryI(const SessionReapThreadPtr&);
    virtual ~SessionFactoryI(){ std::cout << "~SFI"<<std::endl;}


    virtual ::OPI::SessionPrx CreateProxy(const std::string&, const Ice::Current&);
    virtual void shutdown(const Ice::Current&);

};

#endif
