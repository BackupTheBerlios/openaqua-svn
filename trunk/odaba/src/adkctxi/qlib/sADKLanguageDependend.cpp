/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    sADKLanguageDependend

\brief    


\date     $Date: 2006/03/12 19:35:53,56 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sADKLanguageDependend"

#include  <padkctxi.h>
#include  <ssADKLanguageDependend.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc -

\param  strctx_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sADKLanguageDependend :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sADKLanguageDependend();
  return(NO);


}

/******************************************************************************/
/**
\brief  sADKLanguageDependend - Konstruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sADKLanguageDependend"

                        sADKLanguageDependend :: sADKLanguageDependend ( )
                     : sLanguageDependendBase ()
{



}

/******************************************************************************/
/**
\brief  ~sADKLanguageDependend - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sADKLanguageDependend"

                        sADKLanguageDependend :: ~sADKLanguageDependend ( )
{



}


