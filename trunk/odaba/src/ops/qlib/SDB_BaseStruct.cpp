/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    SDB_BaseStruct

\brief    Base structure
          Base  structures implement the generic part  of a complex data type. A
          structure  may  be  derived  from  any number of base structures. Base
          structures  can  be  defined  as  shared or exclusive base structures.
          Shared  base  structures  allow  deriving any number of instances from
          one  base instance. Exclusive base  structure instances can be derived
          to  maximum  one  instance  and  exist as long as the derived instance
          exists.

\date     $Date: 2006/05/13 18:12:26,62 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_BaseStruct"

#include  <pops7.h>
#include  <cutimac.h>
#include  <sDBFieldDef.hpp>
#include  <sSDB_Extend.hpp>
#include  <sSDB_Member.hpp>
#include  <sSDB_Structure.hpp>
#include  <sSDB_BaseStruct.hpp>


/******************************************************************************/
/**
\brief  Fill

\return term

\param  dbhandle - 
\param  propnames
\param  proptypes
\param  inverse
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical SDB_BaseStruct :: Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes, char *inverse )
{
  SDB_Structure  *dbsptr = NULL;
  logical         term   = NO;
BEGINSEQ
//SDB_Reference::Fill(dbhandle,propnames,proptypes,1);
  SDB_Relationship::Fill(dbhandle,propnames,proptypes,1,inverse,NO);

  memset(ddegent,' ',sizeof(ddegent));
  clustered       = NO;
  ddesecr         = NO;
  ddeprv          = ODC_public;

  if ( inverse )
  {
    gvtxstb(ddeinv,inverse,ID_SIZE);    
    
    TypeKey            type_key(ddetype,0);
    PI(SDB_Structure)  dbs_pi(dbhandle,"SDB_Structure",PI_Read);
                                                     SDBCERR
    if ( (dbsptr = dbs_pi(type_key.GetKey())) && 
         *dbsptr->get_smceiksm() > ' '            )
    {
      if ( SDB_Extend::ProvideStrRoot(dbhandle,ddetype) )
                                                     ERROR
      memcpy(ddeext,ddetype,ID_SIZE);     
      owning          = NO;
    }
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SDB_BaseStruct


\param  sdbrel
\param  domopt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_BaseStruct"

     SDB_BaseStruct :: SDB_BaseStruct (SDB_Relationship sdbrel, logical domopt )
                     : SDB_Relationship (sdbrel),
  smcedom(domopt)
{
  ddedim[0] = 1;
}

/******************************************************************************/
/**
\brief  ~SDB_BaseStruct


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SDB_BaseStruct"

     SDB_BaseStruct :: ~SDB_BaseStruct ( )
{

}


