#include <SessionFactoryI.hpp>
#include <Ice/Application.h>

using namespace std;


class OPIServer : public Ice::Application
{
public:

    virtual int run(int, char*[]);
};

int
main(int argc, char* argv[])
{
    OPIServer app;
    return app.main(argc, argv);
}

int
OPIServer::run(int argc, char* argv[]){
    SessionReapThreadPtr reaper = new SessionReapThread();
    reaper->start();
    Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("OPI");
    adapter->add(new SessionFactoryI(reaper), Ice::stringToIdentity("session"));
    adapter->activate();
    communicator()->waitForShutdown();
    return EXIT_SUCCESS;
}
