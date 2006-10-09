/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    sDSC_Topic

\brief    


\date     $Date: 2006/04/13 13:52:28,35 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sDSC_Topic"

#include  <pops7.h>
#include  <sCTX_Structure.hpp>
#include  <ssDSC_Topic.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc

\param  strctx_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sDSC_Topic :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sDSC_Topic();
  return(NO);


}

/******************************************************************************/
/**
\brief  SetLanguage - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLanguage"

logical sDSC_Topic :: SetLanguage ( )
{
  PropertyHandle    *dsc_pi  = GetPropertyHandle();
  PropertyHandle    *coll_pi = NULL;
  smcb              *keysmcb = NULL;
  logical            term    = NO;
  if ( !sLanguageDependend::SetLanguage() )
    if ( !old_language || ( language != CS_U && old_order != language) )
    {
      if ( (coll_pi = dsc_pi->GPH("sub_topics")) &&
           (keysmcb = coll_pi->GetSortKeySMCB()) &&
           !memcmp(keysmcb->smcbname,"sk_name ",8) )
        coll_pi->SetOrder("sk_name",language);
        
      if ( (coll_pi = dsc_pi->GPH("descriptors")) &&
           (keysmcb = coll_pi->GetSortKeySMCB()) &&
           !memcmp(keysmcb->smcbname,"sk_Name ",8) )
        coll_pi->SetOrder("sk_Name",language);
        
      old_order = language;
    }

  return(term);
}

/******************************************************************************/
/**
\brief  sDSC_Topic - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sDSC_Topic"

                        sDSC_Topic :: sDSC_Topic ( )
                     : sLanguageDependend (),
  old_order(CS_U)
{



}

/******************************************************************************/
/**
\brief  ~sDSC_Topic - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sDSC_Topic"

                        sDSC_Topic :: ~sDSC_Topic ( )
{



}


