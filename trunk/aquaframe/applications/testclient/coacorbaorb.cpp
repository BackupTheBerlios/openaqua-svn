#include "coacorbaorb.h"
#include <cassert>
#include "orbsvcs/CosNamingC.h"
#include "ace/streams.h"
#include <CoaApplication>


#include <QMutex>



COAMAKRO_DEFINE_SINGLETONMETHODS( CoaCorbaOrb );

CoaCorbaOrb::CoaCorbaOrb()
      : QObject( 0 )
      , m_valid( false )

{
   BEGIN;
   //recreate the argc  argv pattern
   int argc = COAAPP->arguments().size();
   INF( QString( "CoaApplication Object has %1 arguments" ).arg( argc ) );
   if (argc == 0)
   {
      ++argc;
   }
   char *argv[ argc ];


   argv[ 0 ] = new char[ 50 ];
   strcpy( argv[ 0 ], "./testclient" );

   for ( int i = 1; i < argc; ++i )
   {
      const QByteArray array = qApp->arguments().at( i ).toLocal8Bit ();
      argv[ i ] = new char[ array.length() + 1 ];
      strcpy( argv[ i ], array.constData() );
   }


   //init the corba objects
   try
   {
      for ( int j = 0; j < argc; ++j )
      {
         ERR( QString( "argv[%1]: %2" ).arg( j ).arg( argv[ j ] ) );
      }
      //init the orb
      m_orb = CORBA::ORB_init ( argc , argv, "" /* the ORB name, it can be anything! */ );
      m_valid = true;

   }
   catch ( CORBA::Exception & )
   {
      ERR ( "CORBA exception raised: Cannot init the ORB" );
      m_valid = false;
   }

   //free argc argv pattern
   for ( int i = 0; i < argc; ++i )
      delete[] argv[ i ]; //reicht das fuers loeschen des speichers????

}


CORBA::Object_var CoaCorbaOrb::getCorbaObject( const CoaString& )
throw ( CORBA::Exception )
{
   BEGIN;
   // get the nameserver
   CORBA::Object_var naming_context_object = m_orb->resolve_initial_references ( "NameService" );
   CosNaming::NamingContext_var naming_context = CosNaming::NamingContext::_narrow ( naming_context_object.in () );

   //create object name
   CosNaming::Name name ( 1 );
   name.length ( 1 );
   name[ 0 ].id = CORBA::string_dup ( "Contact_Factory" );

   //resolve name
   return naming_context->resolve ( name );

}

CoaCorbaOrb::~CoaCorbaOrb()
{
   m_orb->destroy();
   INSTANCE = 0;
}


CORBA::ORB_var& CoaCorbaOrb::getOrbInterface()
throw ( CORBA::Exception )
{
   return m_orb;
}

bool CoaCorbaOrb::isValid() const
{
   BEGIN;
   RETURN( m_valid );
}

