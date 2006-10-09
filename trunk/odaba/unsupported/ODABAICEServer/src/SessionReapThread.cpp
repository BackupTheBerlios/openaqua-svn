#include <SessionReapThread.hpp>

using namespace std;

SessionReapThread::SessionReapThread() :
    timeout(IceUtil::Time::seconds(5)),
    terminated(false)
{
}

void
SessionReapThread::run()
{
    Lock sync(*this);
    string name;
    sessionlist::iterator it;
    while(!terminated)
    {
	it = sessions.begin();
	while(it != sessions.end())
	{
	    try
	    {
		if((IceUtil::Time::now() > it->second->getTimeOut()))
		{
		    name = it->first->getName();
		    it->first->Destroy();
    	    	    it = sessions.erase(it);
		}
		else
		{
		    it++;
    	    	}
	    }
	    catch(const Ice::ObjectNotExistException&)
	    {
	        it = sessions.erase(it);
	    }
	}
	timedWait(timeout);
    }
}

void
SessionReapThread::terminate()
{
    Lock sync(*this);

    terminated = true;
    notify();

    for(sessionlist::iterator it = sessions.begin(); it != sessions.end(); it++)
    {
	try
	{
	    it->first->Destroy();
	}
	catch(const Ice::Exception&)
	{
	    // Ignore.
	}
    }

    sessions.clear();
}

void
SessionReapThread::add(const ::OPI::SessionPrx& proxy, const SessionIPtr& session)
{
    Lock sync(*this);
    sessions.push_back(sessionpair(proxy, session));
}
