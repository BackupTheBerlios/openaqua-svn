/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/20|15:35:34,34}|(REF)
\class    sLanguageDependendBase

\brief    


\date     $Date: 2006/04/13 15:29:42,79 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sLanguageDependendBase"

#include  <padkctxi.h>
#include  <ssLanguageDependendBase.hpp>


/******************************************************************************/
/**
\brief  DBCreated - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreated"

logical sLanguageDependendBase :: DBCreated ( )
{

  return ( SetLanguage() );

}

/******************************************************************************/
/**
\brief  DBOpened - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBOpened"

logical sLanguageDependendBase :: DBOpened ( )
{
  PropertyHandle  *adk_pi = GetPropertyHandle();
  logical          term   = NO;
BEGINSEQ
  if ( !adk_pi || adk_pi->IsAttribute() )            LEAVESEQ
  
  if ( sLanguageDependendBase::SetLanguage() )       ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBRead - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRead"

logical sLanguageDependendBase :: DBRead ( )
{

  return ( SetLanguage() );

}

/******************************************************************************/
/**
\brief  SetLanguage - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLanguage"

logical sLanguageDependendBase :: SetLanguage ( )
{
  PropertyHandle *adk_pi   = GetPropertyHandle();
  char           *lang     = GetSysVariable("DSC_Language");
  char            buffer[64];
  logical         term = NO;
BEGINSEQ
  while ( adk_pi && adk_pi->IsAttribute() )
    adk_pi = adk_pi->GetParentProperty();
  if ( !adk_pi )                                     LEAVESEQ

  if ( UserState1() )                                LEAVESEQ
  SetUserState1(YES);
  if ( !lang )                                       ERROR
    
  old_language = adk_pi->GetGenAttrType("text_definitions");
  if ( !languages )
  {
    languages = new PropertyHandle(adk_pi->GetDBHandle(),"Language",PI_Read); 
                                                     SDBCERR
  }
  language = languages->GetID(lang);
    
  if ( !old_language || ( language != CS_U && old_language != language) )
    adk_pi->SetGenAttribute(lang,"text_definitions");
    
/* das kann wieder raus, wenn die texte nun ordentlich gespeichert werden ...
  adk_pi = GetPropertyHandle();
  if ( !adk_pi->IsPositioned() && !adk_pi->IsInitInstance() && adk_pi->GetMode() > PI_Read ) 
    adk_pi->SetGenAttribute(lang,"text_definitions");
*/
  
  SetUserState1(NO);

RECOVER
  SetUserState1(NO);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sLanguageDependendBase - Konstruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sLanguageDependendBase"

                        sLanguageDependendBase :: sLanguageDependendBase ( )
                     : CTX_Structure (),
  languages(NULL),
  language(0),
  old_language(0)
{



}

/******************************************************************************/
/**
\brief  ~sLanguageDependendBase - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sLanguageDependendBase"

                        sLanguageDependendBase :: ~sLanguageDependendBase ( )
{

  delete languages;
  languages = NULL;

}


