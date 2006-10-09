/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ICEntry

\brief    


\date     $Date: 2006/03/12 19:17:36,14 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ICEntry"

#include  <popa7.h>
#include  <sICEntry.hpp>
#include  <sbnode.hpp>
#include  <sinti.hpp>
#include  <snode.hpp>
#include  <sICEntry.hpp>


/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code

\param  bnodeptr -
\param  intiptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ICEntry :: Initialize (bnode *bnodeptr, inti *intiptr )
{
  logical                 term = NO;
  entry_number = bnodeptr->get_objid();
  entry_number.ToPIF(bnodeptr->GetPIF());
  last_use     = 0;
  inti_ref     = intiptr;
  bnodeptr->ExtractSortKey(key,intiptr->get_iselarea(),NO);
  return(term);
}

/******************************************************************************/
/**
\brief  SetLastUse - 



\param  count -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLastUse"

void ICEntry :: SetLastUse (int32 count )
{

  last_use = count;

}


