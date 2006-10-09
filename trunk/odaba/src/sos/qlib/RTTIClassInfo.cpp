/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    RTTIClassInfo

\brief    


\date     $Date: 2006/03/12 19:21:55,85 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "RTTIClassInfo"

#include  <pdefault.h>
#include  <czlib.h>
#include  <rtti.h>
#include  <rtti_imp.h>
#include  <sStringHashTable.hpp>
#include  <sRTTIClassInfo.hpp>

StringHashTable        *classes= 0;

/******************************************************************************/
/**
\brief  Create - 


\return term - Success
/******************************************************************************/
/**
\brief i01


\param  RTTI_castAs -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

void *RTTIClassInfo :: Create (CRTTI RTTI_castAs ) const
{

return StaticCast( RTTI_castAs, Create() );

}

/******************************************************************************/
/**
\brief  FindClass

\return term - Success

\param  cszName
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindClass"

CRTTI __cdecl RTTIClassInfo :: FindClass (const char *cszName )
{

setup();
return (CRTTI) classes->Find( (void *)cszName );

}

/******************************************************************************/
/**
\brief  Inherits

\return cond - Return value

\param  vCRTTI -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Inherits"

logical RTTIClassInfo :: Inherits (CRTTI vCRTTI ) const
{
  CRTTI         *bc;
  logical        cond = YES;
BEGINSEQ
  if ( !this )                                       ERROR
  if( vCRTTI == this )                               LEAVESEQ

  bc = baseClasses;
  while( *bc )
  {
    if( (*bc)->Inherits( vCRTTI ) )                  LEAVESEQ
    bc++;
  }
  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  RTTIClassInfo

\return term - Success

\param  names - Name
\param  pCRTTI -
\param  vTcreator -
\param  vTreplicator
\param  vTstaticCast -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RTTIClassInfo"

                        RTTIClassInfo :: RTTIClassInfo (char *names, CRTTI *pCRTTI, Tcreator vTcreator, Treplicator vTreplicator, TstaticCast vTstaticCast )
                     : className(names),
  baseClasses(pCRTTI),
  creator(vTcreator),
  staticCast(vTstaticCast)
{

setup();
classes->Add( className, this );

}

/******************************************************************************/
/**
\brief  Replicate

\return term - Success
/******************************************************************************/
/**
\brief i01


\param  RTTI_castAs -
\param  cpvoid
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Replicate"

void *RTTIClassInfo :: Replicate (CRTTI RTTI_castAs, const void *cpvoid ) const
{

return StaticCast( RTTI_castAs, Replicate( cpvoid ) );

}

/******************************************************************************/
/**
\brief  setup


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setup"

void __cdecl RTTIClassInfo :: setup ( )
{

BEGINSEQ
if( classes )                                        LEAVESEQ

classes= new StringHashTable( NO, NO );

#define RTTI_DEF_INST(a,b)
ENDSEQ

}


