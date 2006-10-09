#ifndef __OaSimpleCorba_h__
#define __OaSimpleCorba_h__

#include "tao/Utils/ORB_Manager.h"
#include "orbsvcs/Naming/Naming_Client.h"
#include "ace/Get_Opt.h"
#include "ace/Read_Buffer.h"

template <class Servant>
class OaSimpleServer
{
  // = TITLE
  //   A set of useful class Templates for using the TAO CORBA
  //   implementation.
  //
  // = DESCRIPTION
  //   A template server definition. This template can be used by
  //   single server/client projects for defintion of their
  //   server/clients.  See the directories time, bank, echo for
  //   further details of implemenatation.
public:
  // = Initialization and termination methods.

  OaSimpleServer (void);
  // Constructor.

  ~OaSimpleServer (void);
  // Destructor.


  // Initialize the Server state - parsing arguments and waiting.
  // interface_name is the name used to register the Servant.
  int init (const char *servant_name,
            int argc,
            char *argv[]
            ACE_ENV_ARG_DECL);

  // After calling <init>, this method will register the server with
  // the TAO Naming Service using the servant_name passed to <init>.
  int register_name (void);


  // Run the orb.
  int run (ACE_ENV_SINGLE_ARG_DECL);

  // Ignore this method if you are not testing the InterOperable
  // Naming Service.
  int test_for_ins (CORBA::String_var ior);

protected:
  Servant servant_;
  // Servant class

  const char *name;
  // name of the servant to be used for TAO Naming Service

  int parse_args (void);
  // Parses the commandline arguments.

  TAO_ORB_Manager orb_manager_;
  // The ORB manager - a helper class for accessing the POA and
  // registering objects.

  TAO_Naming_Client naming_client_;
  // helper class for getting access to Naming Service.

  FILE *ior_output_file_;
  // File where the IOR of the server object is stored.

  int naming_;
  // Flag to indicate whether naming service could be used

  char *ins_;
  // Used test the INS.

  int argc_;
  // Number of command line arguments.

  char **argv_;
  // The command line arguments.
};



template <class INTERFACE_OBJECT, class Var>
class OaSimpleClient
{
  // = TITLE
  //   Template Client class
  //
  // = DESCRIPTION
  //   A template client implementation for a single server/client
  //   model. The example usage of these usage can be found in the
  //   sub-directories below
public:

  // = Initialization and termination methods.
  OaSimpleClient (void);
  // Constructor.

  ~OaSimpleClient (void);
  // Destructor.


  int init (const char *name,int argc, char *argv[]);
  // Initialize the client communication endpoint with server.

  INTERFACE_OBJECT *operator-> () { return server_.in ();};
  // Return the interface object pointer.

  int shutdown (void );
  // Returns the shutdown flag.

  void shutdown (int);
  // Fills in the shutdwon flag.

  int obtain_initial_references (ACE_ENV_SINGLE_ARG_DECL);
  // Initialize naming service

  CORBA::ORB_ptr orb (void) {return this->orb_.in ();}

protected:
  CORBA::ORB_var orb_;
  // Remember our orb.

  int read_ior (char *filename);
  // Function to read the server IOR from a file.

  int parse_args (void);
  // Parses the arguments passed on the command line.

  TAO_Naming_Client naming_client_;
  // helper class for getting access to Naming Service.

  int argc_;
  // # of arguments on the command line.

  char **argv_;
  // arguments from command line.

  char *ior_;
  // IOR of the obj ref of the server.

  char *name_;
  // Name to be usred for the naming service

  Var server_;
  // Server object

  int naming_;
  // Flag to use the naming service

  int shutdown_;
  // Flag for shutting down the server
};

#include "oasimplecorba.cpp"

#endif //__OaSimpleCorba_h__


