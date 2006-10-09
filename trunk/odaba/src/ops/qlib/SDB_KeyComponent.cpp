/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    SDB_KeyComponent

\brief    Key component
          A  key component defines refers to a single attribute, a key or a base
          structure. Key components can be referenced in different ways:
          -  by referring  to an  attribute of  the structure or one of its base
          structures using the attribute name
          - by referring to a near attribute property using a property path
          -  by  referring  to  a  key  name defined for a base structure, which
          provides the attributes defined for the referenced key
          -  by referring to a base  structure, which provides the attributes of
          its identifying key as key attributes
          When  a key component  refers to a  transient attribute, indexes based
          on  such keys are  not updated automatically,  i.e. the application is
          responsible  to update the index, when  the value of a transient field
          changes, which is defined as key component.

\date     $Date: 2006/05/11 13:12:30,46 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_KeyComponent"

#include  <pops7.h>
#include  <sPropertyHandle.hpp>
#include  <sSDB_Member.hpp>
#include  <sSDB_Property.hpp>
#include  <sSDB_Structure.hpp>
#include  <spc_SDB_KeyComponent.hpp>
#include  <sSDB_KeyComponent.hpp>


/******************************************************************************/
/**
\brief  KeyDataDecl

\return string
/******************************************************************************/
/**
\brief  i00


\param  prophdl
\param  nstring
\param  dbs_ph
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyDataDecl"

char *SDB_KeyComponent :: KeyDataDecl (PropertyHandle *prophdl, NString &nstring, PropertyHandle *dbs_ph )
{

  return ( pc_SDB_KeyComponent(prophdl).KeyDataDecl(nstring,dbs_ph) );

}


