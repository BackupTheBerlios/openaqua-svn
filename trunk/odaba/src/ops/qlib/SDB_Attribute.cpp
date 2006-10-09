/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    SDB_Attribute

\brief    Attribute definition
          Attribute  definitions are used to define the attributes for a complex
          data type (structure).

\date     $Date: 2006/05/11 16:06:16,48 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Attribute"

#include  <pops7.h>
#include  <sDBFieldDef.hpp>
#include  <sSDB_Attribute.hpp>


/******************************************************************************/
/**
\brief  Fill

\return term

\param  dbhandle - 
\param  propnames
\param  proptypes
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical SDB_Attribute :: Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes )
{

  SDB_Property::Fill(dbhandle,propnames,proptypes);

  ddetrans = NO;
  return(NO);
}

/******************************************************************************/
/**
\brief  SDB_Attribute

-------------------------------------------------------------------------------
\brief  i0


\param  sdbmem
\param  transopt
\param  ver
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Attribute"

     SDB_Attribute :: SDB_Attribute (SDB_Member sdbmem, logical transopt, uint8 ver )
                     : SDB_Property(sdbmem,transopt,ver)
{
}

/******************************************************************************/
/**
\brief  i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Attribute"

     SDB_Attribute :: SDB_Attribute ( )
                     : SDB_Property ()
{
}


