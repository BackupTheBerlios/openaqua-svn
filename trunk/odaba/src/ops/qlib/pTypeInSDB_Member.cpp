/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    pTypeInSDB_Member

\brief    


\date     $Date: 2006/03/13 21:30:24,78 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pTypeInSDB_Member"

#include  <pops7.h>
#include  <sCTX_Property.hpp>
#include  <spTypeInSDB_Member.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc

\param  propctx_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pTypeInSDB_Member :: Create (CTX_Property **propctx_ptrp )
{

  *propctx_ptrp = new pTypeInSDB_Member();
  return(NO);

}

/******************************************************************************/
/**
\brief  DBOpened - 


\return term

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBOpened"

logical pTypeInSDB_Member :: DBOpened ( )
{
  logical                 term = NO;
//  GPH("impl_ref")->SetType("SDB_Structure"); // das ist nur wegen OGUI, dort brauchen wir eine SDB_Structure. Nicht gut hier, aber hilft
  return(term);
}

/******************************************************************************/
/**
\brief  pTypeInSDB_Member - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pTypeInSDB_Member"

                        pTypeInSDB_Member :: pTypeInSDB_Member ( )
                     : CTX_Property ()
{



}

/******************************************************************************/
/**
\brief  ~pTypeInSDB_Member - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pTypeInSDB_Member"

                        pTypeInSDB_Member :: ~pTypeInSDB_Member ( )
{



}


