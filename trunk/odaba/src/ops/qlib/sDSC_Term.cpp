/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    sDSC_Term

\brief    


\date     $Date: 2006/04/11 12:35:17,76 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sDSC_Term"

#include  <pops7.h>
#include  <sCTX_Structure.hpp>
#include  <ssDSC_Term.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc

\param  strctx_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sDSC_Term :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sDSC_Term();
  return(NO);


}

/******************************************************************************/
/**
\brief  sDSC_Term - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sDSC_Term"

                        sDSC_Term :: sDSC_Term ( )
                     : sLanguageDependend ()
{



}

/******************************************************************************/
/**
\brief  ~sDSC_Term - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sDSC_Term"

                        sDSC_Term :: ~sDSC_Term ( )
{



}


