/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cLanguageDependend

\brief    


\date     $Date: 2006/06/14 14:39:33,68 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cLanguageDependend"

#include  <pdesign.h>
#include  <scLanguageDependend.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return  - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cLanguageDependend :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cLanguageDependend();
  return(NO);


}

/******************************************************************************/
/**
\brief  DoBeforeFillData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoBeforeFillData"

int8 cLanguageDependend :: DoBeforeFillData ( )
{
  CTX_Control     *ctx_lang = GetControlContext("language");
  PropertyHandle  *prophdl  = GetPropertyHandle();
  char             language[33];
BEGINSEQ
  if ( !ctx_lang )                                   LEAVESEQ
  
//  if ( prophdl->Exist() )
  if ( prophdl->IsSelected() )
    strcpy(language,prophdl->GPH("language")->GetString());
  else
    strcpy(language,"undefined");  
    
  ctx_lang->SearchKey(language);

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  cLanguageDependend - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cLanguageDependend"

     cLanguageDependend :: cLanguageDependend ( )
                     : CTX_Control ()
{



}

/******************************************************************************/
/**
\brief  ~cLanguageDependend - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cLanguageDependend"

     cLanguageDependend :: ~cLanguageDependend ( )
{



}


