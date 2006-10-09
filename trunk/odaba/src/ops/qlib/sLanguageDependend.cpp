/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    sLanguageDependend

\brief    


\date     $Date: 2006/04/13 13:49:41,71 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sLanguageDependend"

#include  <pops7.h>
#include  <sPropertyHandle.hpp>
#include  <ssLanguageDependend.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc

\param  strctx_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sLanguageDependend :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sLanguageDependend();
  return(NO);

  return(NO);
}

/******************************************************************************/
/**
\brief  DBCreated - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreated"

logical sLanguageDependend :: DBCreated ( )
{

  return ( SetLanguage() );

}

/******************************************************************************/
/**
\brief  DBOpened - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBOpened"

logical sLanguageDependend :: DBOpened ( )
{
  PropertyHandle  *dsc_pi = GetPropertyHandle();
  logical          term   = NO;
BEGINSEQ
  if ( !dsc_pi || dsc_pi->IsAttribute() )            LEAVESEQ
  
  if ( sLanguageDependend::SetLanguage() )           ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBRead - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRead"

logical sLanguageDependend :: DBRead ( )
{

  return ( SetLanguage() );

}

/******************************************************************************/
/**
\brief  SetLanguage - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLanguage"

logical sLanguageDependend :: SetLanguage ( )
{
  PropertyHandle *dsc_pi   = GetPropertyHandle();
  char           *lang     = GetSysVariable("DSC_Language");
  char            buffer[64];
  logical         term = NO;
BEGINSEQ
  if ( !dsc_pi->IsServer() )                         LEAVESEQ
    
  while ( dsc_pi && dsc_pi->IsAttribute() )
    dsc_pi = dsc_pi->GetParentProperty();
  if ( !dsc_pi )                                     LEAVESEQ

  if ( UserState1() )                                LEAVESEQ
  SetUserState1(YES);
  
  if ( !lang || !*lang )
    lang = "English";
    
  old_language = dsc_pi->GetGenAttrType("definition");
  if ( !languages )
  {
    languages = new PropertyHandle(dsc_pi->GetDictionary(),"Language",PI_Read); 
                                                     SDBCERR
  }
  language = languages->GetID(lang);
    
  if ( !old_language || ( language != CS_U && old_language != language) )
    dsc_pi->SetGenAttribute(lang,"definition");

  SetUserState1(NO);

RECOVER
  SetUserState1(NO);
  term = YES;

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sLanguageDependend - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sLanguageDependend"

                        sLanguageDependend :: sLanguageDependend ( )
                     : CTX_Structure (),
  languages(NULL),
  language(CS_U),
  old_language(0)
{



}

/******************************************************************************/
/**
\brief  ~sLanguageDependend - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sLanguageDependend"

                        sLanguageDependend :: ~sLanguageDependend ( )
{

  delete languages;
  languages = NULL;

}


