/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    sSDB_Reference

\brief    


\date     $Date: 2006/03/13 21:30:25,95 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sSDB_Reference"

#include  <pops7.h>
#include  <sCTX_Structure.hpp>
#include  <sSDB_Reference.hpp>
#include  <ssSDB_Reference.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc

\param  strctx_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sSDB_Reference :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sSDB_Reference();
  return(NO);

}

/******************************************************************************/
/**
\brief  SetDefaultsForSpecialType - 


\return term

\param  dbhandle -
\param  propnames -
\param  typenames -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDefaultsForSpecialType"

logical sSDB_Reference :: SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames )
{
  PropertyHandle    *prophdl = GetPropertyHandle();
  return ( ((SDB_Reference *)prophdl->Get().GetData())->
              Fill(dbhandle,propnames,typenames,UNDEF)     );


}

/******************************************************************************/
/**
\brief  sSDB_Reference - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sSDB_Reference"

                        sSDB_Reference :: sSDB_Reference ( )
                     : sSDB_Member_base ()
{



}

/******************************************************************************/
/**
\brief  ~sSDB_Reference - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sSDB_Reference"

                        sSDB_Reference :: ~sSDB_Reference ( )
{



}


