#include <SessionI.hpp>

using namespace std;
SessionI::~SessionI(){
}
 
SessionI::SessionI(const string& name) :
    name(name)
    ,timeout(IceUtil::Time::now()+IceUtil::Time::seconds(30))
    ,factory(NULL)
    ,destroy(false)
{
}

::OPI::OPIFactoryPrx
SessionI::CreateSession(const Ice::Current& current)
{
    Lock sync(*this);
    if(factory)
    {
	throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }
    if(destroy)
    {
	throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }

    factory = ::OPI::OPIFactoryPrx::uncheckedCast(current.adapter->addWithUUID(new OPIFactoryI()));
    return factory;
}

void 
SessionI::TimeOut(const Ice::Int seconds, const Ice::Current& current){
    Lock sync(*this);
    if(destroy)
    {
	throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }
    timeout = IceUtil::Time::now() + IceUtil::Time::seconds(seconds); 
}


std::string
SessionI::getName(const Ice::Current&) 
{
    Lock sync(*this);
    if(destroy)
    {
	throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }

    return name;
}

void
SessionI::Destroy(const Ice::Current& c)
{
    Lock sync(*this);
    if(destroy)
    {
	throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }

    destroy = true;

    try
    {
	factory->Destroy();
	c.adapter->remove(c.id);
        c.adapter->remove(factory->ice_getIdentity());
    }
    catch(const Ice::ObjectAdapterDeactivatedException&)
    {
	// This method is called on shutdown of the server, in which
	// case this exception is expected.
    }
}

IceUtil::Time
SessionI::getTimeOut() const
{
    Lock sync(*this);
    if(destroy)
    {
	throw Ice::ObjectNotExistException(__FILE__, __LINE__);
    }
    return timeout;
}
