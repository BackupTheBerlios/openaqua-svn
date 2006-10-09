/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    sSDB_Attribute

\brief    


\date     $Date: 2006/03/13 21:30:25,34 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sSDB_Attribute"

#include  <pops7.h>
#include  <sCTX_Structure.hpp>
#include  <sSDB_Attribute.hpp>
#include  <ssSDB_Attribute.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc

\param  strctx_ptrp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sSDB_Attribute :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sSDB_Attribute();
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

logical sSDB_Attribute :: SetDefaultsForSpecialType (DatabaseHandle &dbhandle, char *propnames, char *typenames )
{
  PropertyHandle    *prophdl = GetPropertyHandle();
  return ( ((SDB_Attribute *)prophdl->Get().GetData())->
              Fill(dbhandle,propnames,typenames)         );


}

/******************************************************************************/
/**
\brief  sSDB_Attribute - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sSDB_Attribute"

                        sSDB_Attribute :: sSDB_Attribute ( )
                     : sSDB_Member_base ()
{



}

/******************************************************************************/
/**
\brief  ~sSDB_Attribute - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sSDB_Attribute"

                        sSDB_Attribute :: ~sSDB_Attribute ( )
{



}


