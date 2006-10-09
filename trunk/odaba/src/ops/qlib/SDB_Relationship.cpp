/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    SDB_Relationship

\brief    Relationship
          Relationships  are  defined  for  referring  to  instances  form other
          collections  or extents. A relationship may  also own the instances in
          the  collection. Relationships  define several  properties for setting
          different  types  of  dependencies,  inverse  relationships  and  base
          collections.

\date     $Date: 2006/05/11 16:10:49,09 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Relationship"

#include  <pops7.h>
#include  <cutimac.h>
#ifndef   P_SDB_BaseStruct_HPP
#define   P_SDB_BaseStruct_HPP
#include  <sPI.hpp>
class       SDB_BaseStruct;
PI_dcl     (SDB_BaseStruct)
#endif
#include  <sSDB_BaseStruct.hpp>
#include  <sSDB_Extend.hpp>
#include  <sSDB_Index.hpp>
#include  <sSDB_Structure.hpp>
#include  <sSDB_Relationship.hpp>


/******************************************************************************/
/**
\brief  Fill

\return term

\param  dbhandle - 
\param  propnames
\param  proptypes
\param  dim
\param  inverse
\param  secrefr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical SDB_Relationship :: Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes, uint16 dim, char *inverse, logical secrefr )
{
  SDB_Structure  *dbsptr = NULL;
  logical         term   = NO;
BEGINSEQ
  SDB_Reference::Fill(dbhandle,propnames,proptypes,dim);

  clustered = NO;  
  ddesecr   = secrefr;

  TypeKey            type_key(ddetype,0);
  PI(SDB_Structure)  dbs_pi(dbhandle,"SDB_Structure",PI_Read);
                                                     SDBCERR
  if ( (dbsptr = dbs_pi(type_key.GetKey())) && *dbsptr->get_smceiksm() > ' ' )
  {
    if ( SDB_Extend::ProvideStrRoot(dbhandle,ddetype) ) ERROR
    gvtxbts(ddeext,ddetype,ID_SIZE);     
    owning          = NO;
    
    ddeindx.Add(dbsptr->get_smceiksm());             SDBCERR
    ddeindx->Initialize(dbsptr->get_smceiksm(),SET_SMAL,YES,YES);
    ddeindx.Modify();
    ddeindx.Save();
  }

  if ( inverse )
  {
    gvtxstb(ddeinv,inverse,ID_SIZE);
    update          = YES;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void SDB_Relationship :: Initialize ( )
{
  SDB_Reference::Initialize();

  ddesecr = NO;
  dderlog = NO;
  depend  = NO;

  memset(ddeinv,' ',sizeof(ddeinv));
  memset(ddeext,0,sizeof(ddeext));

}

/******************************************************************************/
/**
\brief  SDB_Relationship

-------------------------------------------------------------------------------
\brief  i0


\param  sdbref
\param  secrefr
\param  logrefr
\param  irefname
\param  depopt
\param  extnames
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Relationship"

     SDB_Relationship :: SDB_Relationship (SDB_Reference sdbref, logical secrefr, logical logrefr, char *irefname, logical depopt, char *extnames )
                     : SDB_Reference (sdbref),
  ddesecr(secrefr),
  dderlog(logrefr),
  event_list()
{
  gvtxstb(ddeinv,irefname,ID_SIZE);
  
  memset(ddeext,0,sizeof(ddeext));
  strncpy(ddeext,extnames,sizeof(ddeext)-1);
  depend = depopt;

}

/******************************************************************************/
/**
\brief  i1


\param  dbp_refc
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Relationship"

     SDB_Relationship :: SDB_Relationship (const SDB_Relationship &dbp_refc )
                     : SDB_Reference ()
{
  *this = dbp_refc;
}

/******************************************************************************/
/**
\brief  i2


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Relationship"

     SDB_Relationship :: SDB_Relationship ( )
                     : SDB_Reference ()

{
}

/******************************************************************************/
/**
\brief  ~SDB_Relationship - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SDB_Relationship"

     SDB_Relationship :: ~SDB_Relationship ( )
{

}


