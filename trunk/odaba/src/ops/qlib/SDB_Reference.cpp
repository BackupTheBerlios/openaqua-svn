/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    SDB_Reference

\brief    References
          References  are  used  to  describe any sort of reference collections.
          Thus,  the  reference  definition  is  the  base  for  defining  local
          collections (references or relationships) as well as extents.

\date     $Date: 2006/05/11 16:10:01,09 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Reference"

#include  <pops7.h>
#include  <cutimac.h>
#include  <sDBFieldDef.hpp>
#include  <sDBIndex.hpp>
#include  <sDBIndexList.hpp>
#include  <sSDB_Index.hpp>
#include  <sSDB_Structure.hpp>
#include  <sSDB_Reference.hpp>


/******************************************************************************/
/**
\brief  Fill

\return term

\param  dbhandle - 
\param  propnames
\param  proptypes
\param  dim
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical SDB_Reference :: Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes, uint16 dim )
{
  logical                 term = NO;
BEGINSEQ
//  Initialize();
  SDB_Property::Fill(dbhandle,propnames,proptypes);
  if ( memcmp(proptypes,"MEMO ",5) )
    ddedim[0] = (uint32) dim;

  memcpy(ddegent,"PI",2);
  ddetrans        = NO;
  owning          = YES;
  create          = YES;
  clustered       = YES;
  mb_number       = 0;
  week_typed      = NO;
  update          = NO;
  multikey        = NO;
  ddeatyp         = AT_ODABA;
    
  if ( !*proptypes )
  {
    PI(SDB_Structure)  str_pi(dbhandle,"SDB_Structure",PI_Read);  
                                                     SDBCERR
    if ( str_pi(sys_ident) )
      memcpy(ddetype,sys_ident,sizeof(ddetype));
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetAlignInfo

\return term

\param  propname
\param  size_info
\param  offset_info
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAlignInfo"

logical SDB_Reference :: GetAlignInfo (char *propname, int16 &size_info, int16 &offset_info )
{
  char            propnames[ID_SIZE+1];
  logical         term = NO;
  size_info   = 0;
  offset_info = 0;
  
  if ( !propname )
    size_info   = sizeof(SDB_Reference);
  else          
  {
    gvtxbts(propnames,propname,sizeof(propnames)-1);
    if ( !strcmp("SDB_Property",propnames) )
    {
      size_info   = sizeof(*(SDB_Property *)this);
      offset_info = (char *)(SDB_Property *)this - (char *)this;
    }
    else if ( !strcmp("owning",propnames) )
    {
      size_info   = sizeof(owning);
      offset_info = (char *)&owning - (char *)this;
    }
    else if ( !strcmp("create",propnames) )
    {
      size_info   = sizeof(create);
      offset_info = (char *)&create - (char *)this;
    }
    else if ( !strcmp("clustered",propnames) )
    {
      size_info   = sizeof(clustered);
      offset_info = (char *)&clustered - (char *)this;
    }
    else if ( !strcmp("mb_number",propnames) )
    {
      size_info   = sizeof(mb_number);
      offset_info = (char *)&mb_number - (char *)this;
    }
    else if ( !strcmp("week_typed",propnames) )
    {
      size_info   = sizeof(week_typed);
      offset_info = (char *)&week_typed - (char *)this;
    }
    else if ( !strcmp("update",propnames) )
    {
      size_info   = sizeof(update);
      offset_info = (char *)&update - (char *)this;
    }
    else if ( !strcmp("multikey",propnames) )
    {
      size_info   = sizeof(multikey);
      offset_info = (char *)&multikey - (char *)this;
    }
    else if ( !strcmp("ddeatyp",propnames) )
    {
      size_info   = sizeof(ddeatyp);
      offset_info = (char *)&ddeatyp - (char *)this;
    }
    else if ( !strcmp("ddeindx",propnames) )
    {
      size_info   = sizeof(ddeindx);
      offset_info = (char *)&ddeindx - (char *)this;
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize

\return term
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical SDB_Reference :: Initialize ( )
{

  SDB_Property::Initialize();

  gvtxstb(ddetype,"MEMO",ID_SIZE);
  memcpy(ddegent,"PI",2);
  ddetrans        = NO;
  owning          = YES;
  create          = YES;
  clustered       = YES;
  mb_number       = 0;
  week_typed      = NO;
  update          = NO;
  multikey        = NO;
  ddeatyp         = AT_ODABA;
  return(NO);
}

/******************************************************************************/
/**
\brief  i1


\param  dbhandle - 
\param  strname
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical SDB_Reference :: Initialize (DatabaseHandle &dbhandle, char *strname )
{
  logical                 term = NO;
BEGINSEQ
  PI(SDB_Structure)   dbs_pi(dbhandle,"SDB_Structure",PI_Read);
                                                     SDBCERR
  if ( !dbs_pi(strname) )                            SDBERR(20)
  
  Initialize();
  
  memcpy(ddetype,strname,ID_SIZE);
  ddedim[0]  = (uint32) UNDEF;
  ddetrans   = NO;
  
  create     = YES;
  clustered  = NO;

  if ( *dbs_pi->get_smceiksm() > ' ') 
  {
    ddeindx.Provide(dbs_pi->get_smceiksm());       SDBCERR
    ddeindx->Initialize(dbs_pi->get_smceiksm(),SET_LARG,YES,YES);
    ddeindx.Modify();
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SDB_Reference

-------------------------------------------------------------------------------
\brief  i0


\param  sdbmem
\param  transopt
\param  ver
\param  ownopt
\param  create_opt
\param  cluster_opt
\param  mbnumber
\param  week_opt
\param  dbilistptr
\param  dbicount
\param  update_opt
\param  mkey_opt
\param  glob_identity
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Reference"

     SDB_Reference :: SDB_Reference (SDB_Member sdbmem, logical transopt, uint8 ver, logical ownopt, logical create_opt, logical cluster_opt, int16 mbnumber, logical week_opt, SDB_Index *dbilistptr, int16 dbicount, logical update_opt, logical mkey_opt, logical glob_identity )
                     : SDB_Property(sdbmem,transopt,ver),
  owning(ownopt),
  create(create_opt),
  clustered(cluster_opt),
  mb_number(mbnumber),
  week_typed(week_opt), 
  update(update_opt),
  multikey(mkey_opt),
  ddeindx(),
  ddeatyp(AT_ODABA)
{
  if ( dbilistptr )
  {
    ddeprec         = (uint16)dbicount;
    ddeindx.set_nodeptr((node *)dbilistptr);
  }
  global_identity = glob_identity;
}

/******************************************************************************/
/**
\brief  i1


\param  dbr_refc
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Reference"

     SDB_Reference :: SDB_Reference (const SDB_Reference &dbr_refc )
{
  node      *nodeptr = dbr_refc.ddeindx.get_nodeptr();
  if ( dbr_refc.ddeprec )  // is *SDB_Index
    (const_cast<SDB_Reference&>(dbr_refc)).ddeindx.set_nodeptr(NULL);
    
  *this = dbr_refc;

  if ( dbr_refc.ddeprec )
  {
    (const_cast<SDB_Reference&>(dbr_refc)).ddeindx.set_nodeptr(nodeptr);
    ddeindx.set_nodeptr(nodeptr);
  }
}

/******************************************************************************/
/**
\brief  i2


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Reference"

     SDB_Reference :: SDB_Reference ( )
                     : SDB_Property(),
  owning(UNDEF),
  create(YES),
  clustered(UNDEF),
  mb_number(AUTO),
  week_typed(UNDEF),
  update(NO),
  multikey(NO),
  ddeindx(),
  ddeatyp(AT_NONE)
{
}

/******************************************************************************/
/**
\brief  set_create


\param  create_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_create"

void SDB_Reference :: set_create (logical create_opt )
{

  create = create_opt;

}

/******************************************************************************/
/**
\brief  set_ddeatyp


\param  acctype
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_ddeatyp"

void SDB_Reference :: set_ddeatyp (SDB_AT acctype )
{
  ddeatyp = acctype;
}

/******************************************************************************/
/**
\brief  set_owning


\param  owning_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_owning"

void SDB_Reference :: set_owning (logical owning_opt )
{
  owning = owning_opt;
}

/******************************************************************************/
/**
\brief  ~SDB_Reference


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SDB_Reference"

     SDB_Reference :: ~SDB_Reference ( )
{
  ddeindx.set_nodeptr(NULL);

}


