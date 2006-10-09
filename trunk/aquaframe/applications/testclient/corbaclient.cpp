#include "corbaclient.h"
#include <CoaDebug>

//corba stuff
#include "orbsvcs/CosNamingC.h"
#include "ace/streams.h"
#include "coacorbaorb.h"


//other stuff
#include <iostream>


CorbaClient::CorbaClient( CoaDataSetModel& dataSetModel, QObject *const parent )
      : QObject( parent )
      , m_valid ( false )
      , m_dataSetModel( dataSetModel )
{
   BEGIN;
}


CorbaClient::~CorbaClient ( )
{
   BEGIN;

}


void CorbaClient::initialize(  )
{
   BEGIN;
   m_valid = false;
   try
   {
      if ( CoaCorbaOrb::getInstance()->isValid() )
      {
         CORBA::Object_var factory_object = CoaCorbaOrb::getInstance() -> getCorbaObject( "Contact_Factory" );
         // Now downcast the object reference to the appropriate type
         m_contact_Factory = XENON::Contact_Factory::_narrow ( factory_object.in () );
         m_valid = true;
      }
   }
   catch ( XENON::Invalid_Contact_ID & )
   {
      ERR( QString( "Invalid_Contact_ID %1" ).arg( 1 ) );
   }
   catch ( CORBA::Exception & )
   {
      ERR ( "CORBA exception raised!" );
   }
}


void CorbaClient::getData()
{
   BEGIN;

   if ( !m_valid )
      return ;
   try
   {
      m_valueMap.clear();

      XENON::Contact_var contact = m_contact_Factory->getContact ( );

      m_valueMap[ "e1" ] = contact->e1();
      m_valueMap[ "e2" ] = contact->e2();
      m_valueMap[ "e3" ] = contact->e3();
      m_valueMap[ "e4" ] = contact->e4();
      m_valueMap[ "e5" ] = contact->e5();

      m_dataSetModel.updateWidgets( "contact", m_valueMap );

   }
   catch ( XENON::Invalid_Contact_ID & )
   {
      ERR( QString( "Invalid_Contact_ID %1" ).arg( 1 ) );
   }
   catch ( CORBA::Exception & )
   {
      ERR ( "CORBA exception raised!" );
   }
}

void CorbaClient::slotGotoFirst()
{
   BEGIN;
   if ( !m_valid )
      return ;
   try
   {
      m_contact_Factory->gotoFirstContact ( );
      getData();
   }
   catch ( XENON::Invalid_Contact_ID & )
   {
      ERR( QString( "Invalid_Contact_ID %1" ).arg( 1 ) );
   }
   catch ( CORBA::Exception & )
   {
      ERR ( "CORBA exception raised!" );
   }
}


void CorbaClient::slotGotoPrev()
{
   BEGIN;
   if ( !m_valid )
      return ;
   try
   {
      m_contact_Factory->gotoPrevContact ( );
      getData();
   }
   catch ( XENON::Invalid_Contact_ID & )
   {
      ERR( QString( "Invalid_Contact_ID %1" ).arg( 1 ) );
   }
   catch ( CORBA::Exception & )
   {
      ERR ( "CORBA exception raised!" );
   }
}


void CorbaClient::slotGotoNext()
{
   BEGIN;
   if ( !m_valid )
      return ;
   try
   {
      m_contact_Factory->gotoNextContact ( );
      getData();
   }
   catch ( XENON::Invalid_Contact_ID & )
   {
      ERR( QString( "Invalid_Contact_ID %1" ).arg( 1 ) );
   }
   catch ( CORBA::Exception & )
   {
      ERR ( "CORBA exception raised!" );
   }
}


void CorbaClient::slotGotoLast()
{
   BEGIN;
   if ( !m_valid )
      return ;
   try
   {
      m_contact_Factory->gotoLastContact ( );
      getData();
   }
   catch ( XENON::Invalid_Contact_ID & )
   {
      ERR( QString( "Invalid_Contact_ID %1" ).arg( 1 ) );
   }
   catch ( CORBA::Exception & )
   {
      ERR ( "CORBA exception raised!" );
   }
}


bool CorbaClient::isValid() const
{
   BEGIN;
   RETURN(m_valid);
}

