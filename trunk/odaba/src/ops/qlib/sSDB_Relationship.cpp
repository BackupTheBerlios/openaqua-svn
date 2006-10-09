/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    sSDB_Relationship

\brief    


\date     $Date: 2006/03/13 21:30:26,07 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sSDB_Relationship"

#include  <pops7.h>
#include  <sCTX_Structure.hpp>
#include  <sSDB_Relationship.hpp>
#include  <ssSDB_Relationship.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc

\param  strctx_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sSDB_Relationship :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sSDB_Relationship();
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

logical sSDB_Relationship :: SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames )
{
  PropertyHandle    *prophdl = GetPropertyHandle();
  return ( ((SDB_Relationship *)prophdl->Get().GetData())->
              Fill(dbhandle,propnames,typenames,UNDEF,NULL,NO) );


}

/******************************************************************************/
/**
\brief  sSDB_Relationship - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sSDB_Relationship"

                        sSDB_Relationship :: sSDB_Relationship ( )
                     : sSDB_Member_base ()
{



}

/******************************************************************************/
/**
\brief  ~sSDB_Relationship - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sSDB_Relationship"

                        sSDB_Relationship :: ~sSDB_Relationship ( )
{



}


