#include "contact_Factory_i.h"
#include "ace/streams.h"
#include "orbsvcs/CosNamingC.h"
#include <iostream>
using namespace std;

#include "oasimplecorba.h"


int main ( int argc, char *argv[] )
{
   OaSimpleServer<XENON_Contact_Factory_i> server;

   ACE_DEBUG ( ( LM_DEBUG, "\n\tCheckpoint Event_Types server\n\n" ) );

   ACE_DECLARE_NEW_CORBA_ENV;

   ACE_TRY
   {
      if ( server.init ( "Contact_Factory", argc, argv ACE_ENV_ARG_PARAMETER ) == -1 )
   {
      return 1;
   }
   else
   {
      server.run ( ACE_ENV_SINGLE_ARG_PARAMETER );
         ACE_TRY_CHECK;
      }
   }
   ACE_CATCH ( CORBA::SystemException, sysex )
   {
      ACE_PRINT_EXCEPTION ( sysex, "System Exception" );
      return -1;
   }
   ACE_CATCH ( CORBA::UserException, userex )
   {
      ACE_PRINT_EXCEPTION ( userex, "User Exception" );
      return -1;
   }
   ACE_ENDTRY;

   return 0;
}


#if 0
int main2 ( int argc, char* argv[] )
{
   try
   {
      //init the orb
      CORBA::ORB_var orb = CORBA::ORB_init ( argc , argv, "" /* the ORB name, it can be anything! */ );


      // First initialize the ORB, that will remove some arguments...
      CORBA::Object_var poa_object = orb->resolve_initial_references ( "RootPOA" );
      PortableServer::POA_var poa = PortableServer::POA::_narrow ( poa_object.in () );

      PortableServer::POAManager_var poa_manager = poa->the_POAManager ();
      poa_manager->activate ();

      //create policies for children
      CORBA::PolicyList policies ( 2 );
      policies.length ( 2 );
      policies[ 0 ] = poa->create_id_assignment_policy ( PortableServer::USER_ID );
      policies[ 1 ] = poa->create_implicit_activation_policy ( PortableServer::NO_IMPLICIT_ACTIVATION );


      PortableServer::POA_var contact_factory_poa = poa->create_POA ( "ContactFactoryPoa", poa_manager.in (), policies );
      for ( CORBA::ULong i = 0; i != policies.length (); ++i )
      {
         policies[ i ] ->destroy ();
      }


      // Create the servant
      XENON_Contact_Factory_i contact_factory_i( contact_factory_poa.in () );

      // Activate it to obtain the object reference
      XENON::Contact_Factory_var contact_factory = contact_factory_i._this ();

      // get the nameserver
      CORBA::Object_var naming_context_object = orb->resolve_initial_references ( "NameService" );
      CosNaming::NamingContext_var naming_context = CosNaming::NamingContext::_narrow ( naming_context_object.in () );

      //create object name
      CosNaming::Name name ( 1 );
      name.length ( 1 );
      name[ 0 ].id = CORBA::string_dup ( "Contact_Factory" );

      // Bind the object  at the nameserver
      naming_context->bind ( name, contact_factory.in () );

      orb->run ();

      // Destroy the POA, waiting until the destruction terminates
      poa->destroy ( 1, 1 );
      orb->destroy ();
   }
   catch ( CORBA::Exception & ex )
   {
      std::cerr << "CORBA exception raised!" << std::endl;
   }
   return 0;
}

#endif





