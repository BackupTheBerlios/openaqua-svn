
#include "contact_Factory_i.h"
#include <sstream>

// Implementation skeleton constructor
XENON_Contact_Factory_i::XENON_Contact_Factory_i ( )
      : m_currContact()
      , m_curr( 1 )
      , m_max( 100 )

{
   resetContact();
}

// Implementation skeleton destructor
XENON_Contact_Factory_i::~XENON_Contact_Factory_i ( void )
{}


//finish the server
void XENON_Contact_Factory_i::shutdown( ACE_ENV_SINGLE_ARG_DECL )
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   ACE_DEBUG ((LM_DEBUG, "Server shutdown called:\n"));
   this->m_orb->shutdown ();
}

// Set the ORB pointer.
void XENON_Contact_Factory_i::orb ( CORBA::ORB_ptr o )
{
   this->m_orb = CORBA::ORB::_duplicate ( o );
}


::XENON::Contact_ptr XENON_Contact_Factory_i::getContact ()
ACE_THROW_SPEC ( ( ::CORBA::SystemException, ::XENON::Invalid_Contact_ID ) )
{
   return m_currContact._this();
}

void XENON_Contact_Factory_i::gotoFirstContact ()
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_curr = 1;
   resetContact();

}

void XENON_Contact_Factory_i::gotoPrevContact ()
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   if ( m_curr <= 1 )
      m_curr = 1;
   else
      m_curr = m_curr - 1;

   resetContact();
}

void XENON_Contact_Factory_i::gotoNextContact ()
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   if ( m_curr >= m_max )
      m_curr = m_max;
   else
      m_curr = m_curr + 1;

   resetContact();
}

void XENON_Contact_Factory_i::gotoLastContact ( )
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_curr = m_max;
   resetContact();
}

void XENON_Contact_Factory_i::gotoContact ( ::CORBA::Long Contact_ID )
ACE_THROW_SPEC ( ( ::CORBA::SystemException, ::XENON::Invalid_Contact_ID ) )
{
   if ( Contact_ID > m_max )
      m_curr = m_max;
   else if ( Contact_ID < 1 )
      m_curr = 1;
   else
      m_curr = Contact_ID;
   resetContact();
}

void XENON_Contact_Factory_i::resetContact()
{
   std::stringstream ssStream;
   ssStream << "currPos: " << m_curr;

   m_currContact.e1( "E1: " + ssStream.str() );
   m_currContact.e2( "E2: " + ssStream.str() );
   m_currContact.e3( "E3: " + ssStream.str() );
   m_currContact.e4( "E4: " + ssStream.str() );
   m_currContact.e5( "E5: " + ssStream.str() );
}

// Implementation skeleton constructor
Contact::Contact ( void )
{}

// Implementation skeleton destructor
Contact::~Contact ( void )
{}

char * Contact::e1 ()
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   return CORBA::string_dup ( this->m_e1.c_str () );
}

void Contact::e1 ( const char * e1 )
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_e1 = e1;
}

char * Contact::e2 () ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   return CORBA::string_dup ( this->m_e2.c_str () );
}

void Contact::e2 ( const char * e2 )
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_e2 = e2;
}

char * Contact::e3 ()
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   return CORBA::string_dup ( this->m_e3.c_str () );
}

void Contact::e3 ( const char * e3 )
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_e3 = e3;
}

char * Contact::e4 ()
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   return CORBA::string_dup ( this->m_e4.c_str () );
}

void Contact::e4 ( const char * e4 )
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_e4 = e4;
}

char * Contact::e5 ()
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   return CORBA::string_dup ( this->m_e5.c_str () );
}

void Contact::e5 ( const char * e5 )
ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_e5 = e5;
}

void Contact::e1 ( const std::string& s ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_e1 = s;
}

void Contact::e2 ( const std::string& s ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_e2 = s;
}

void Contact::e3 ( const std::string& s ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_e3 = s;
}

void Contact::e4 ( const std::string& s ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_e4 = s;
}

void Contact::e5 ( const std::string& s ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) )
{
   m_e5 = s;
}
