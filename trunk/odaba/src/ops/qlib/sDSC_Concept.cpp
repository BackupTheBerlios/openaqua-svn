/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/06|19:43:10,20}|(REF)
\class    sDSC_Concept

\brief    


\date     $Date: 2006/04/13 13:53:10,07 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sDSC_Concept"

#include  <pops7.h>
#include  <sCTX_Structure.hpp>
#include  <ssDSC_Concept.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc

\param  strctx_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sDSC_Concept :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sDSC_Concept();
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

logical sDSC_Concept :: SetLanguage ( )
{
  PropertyHandle    *dsc_pi  = GetPropertyHandle();
  PropertyHandle    *coll_pi = NULL;
  smcb              *keysmcb = NULL;
  logical            term    = NO;
  if ( !sLanguageDependend::SetLanguage() )
    if ( !old_language || ( language != CS_U && old_order != language) )
    {
      if ( (coll_pi = dsc_pi->GPH("synonyms"))   &&
           (keysmcb = coll_pi->GetSortKeySMCB()) &&
           !memcmp(keysmcb->smcbname,"sk_Name ",8) )
        coll_pi->SetOrder("sk_Name",language);
      if ( (coll_pi = dsc_pi->GPH("references")) &&
           (keysmcb = coll_pi->GetSortKeySMCB()) &&
           !memcmp(keysmcb->smcbname,"sk_Name ",8) )
        coll_pi->SetOrder("sk_Name",language);
      if ( (coll_pi = dsc_pi->GPH("referenced_in")) &&
           (keysmcb = coll_pi->GetSortKeySMCB())    &&
           !memcmp(keysmcb->smcbname,"sk_Name ",8) )
        coll_pi->SetOrder("sk_Name",language);
      if ( (coll_pi = dsc_pi->GPH("generalisations")) &&
           (keysmcb = coll_pi->GetSortKeySMCB())      &&
           !memcmp(keysmcb->smcbname,"sk_Name ",8) )
        coll_pi->SetOrder("sk_Name",language);
      if ( (coll_pi = dsc_pi->GPH("specialisations")) &&
           (keysmcb = coll_pi->GetSortKeySMCB())      &&
           !memcmp(keysmcb->smcbname,"sk_Name ",8) )
        coll_pi->SetOrder("sk_Name",language);
      if ( (coll_pi = dsc_pi->GPH("topics"))     &&
           (keysmcb = coll_pi->GetSortKeySMCB()) &&
           !memcmp(keysmcb->smcbname,"sk_name ",8) )
        coll_pi->SetOrder("sk_name",language);
      
      old_order = language;
    }
  return(term);
}

/******************************************************************************/
/**
\brief  sDSC_Concept - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sDSC_Concept"

                        sDSC_Concept :: sDSC_Concept ( )
                     : sLanguageDependend (),
  old_order(CS_U)
{



}

/******************************************************************************/
/**
\brief  ~sDSC_Concept - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sDSC_Concept"

                        sDSC_Concept :: ~sDSC_Concept ( )
{



}


