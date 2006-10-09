#ifndef CONTACTI_H_
#define CONTACTI_H_

#include "contactS.h"
#include <string>

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class Contact : public virtual POA_XENON::Contact
{
public:
   // Constructor
   Contact ( void );

   // Destructor
   virtual ~Contact ( void );

   virtual char * e1 ( ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void e1 ( const char * e1 ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void e1 ( const std::string& ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );

   virtual char * e2 ( ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void e2 ( const char * e1 ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void e2 ( const std::string& ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );

   virtual char * e3 ( ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void e3 ( const char * e1 ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void e3 ( const std::string& ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );

   virtual char * e4 ( ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void e4 ( const char * e1 ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void e4 ( const std::string& ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );

   virtual char * e5 ( ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void e5 ( const char * e1 ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void e5 ( const std::string& ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );

private:
   std::string m_e1;
   std::string m_e2;
   std::string m_e3;
   std::string m_e4;
   std::string m_e5;

};

class XENON_Contact_Factory_i : public virtual POA_XENON::Contact_Factory
{
public:
   // Constructor
   explicit XENON_Contact_Factory_i ();

   // Destructor
   virtual ~XENON_Contact_Factory_i ( void );

   //finish the server
   virtual void shutdown ( ACE_ENV_SINGLE_ARG_DECL )
   ACE_THROW_SPEC ( ( CORBA::SystemException ) );

   // Set the ORB pointer.
   void orb ( CORBA::ORB_ptr o );

   virtual ::XENON::Contact_ptr getContact ( ) ACE_THROW_SPEC ( ( ::CORBA::SystemException, ::XENON::Invalid_Contact_ID ) );
   virtual void gotoFirstContact ( ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void gotoPrevContact ( ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void gotoNextContact ( ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void gotoLastContact ( ) ACE_THROW_SPEC ( ( ::CORBA::SystemException ) );
   virtual void gotoContact ( ::CORBA::Long Contact_ID ) ACE_THROW_SPEC ( ( ::CORBA::SystemException, ::XENON::Invalid_Contact_ID ) );

private:
   void resetContact();

   CORBA::ORB_var m_orb;
   Contact m_currContact;
   long m_curr;
   long m_max;

};



#endif /* CONTACTI_H_  */

