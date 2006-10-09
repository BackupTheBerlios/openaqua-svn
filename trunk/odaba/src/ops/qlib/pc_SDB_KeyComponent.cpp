/********************************* Class Source Code ***************************/
/**
\package  OPS - 
\class    pc_SDB_KeyComponent

\brief    


\date     $Date: 2006/07/12 19:10:37,00 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pc_SDB_KeyComponent"

#include  <pops7.h>
#include  <sErrorProtocol.hpp>
#include  <sfmcb.hpp>
#include  <spc_SDB_Member.hpp>
#include  <spc_SDB_Structure.hpp>
#include  <ssmcb.hpp>
#include  <spc_SDB_KeyComponent.hpp>


/******************************************************************************/
/**
\brief  Check - 


\return term - 

\param  protocol - 
\param  prop_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical pc_SDB_KeyComponent :: Check (ErrorProtocol *protocol, char *prop_path )
{

  if ( !prop_path )
    prop_path = GPH("member_path")->GetString();

  pc_SDB_Structure    str_pc(GetParentProperty()->GetParentProperty());
  return ( str_pc.CheckKeyField(protocol,prop_path,NO,NO,YES,YES) );


}

/******************************************************************************/
/**
\brief  CheckAll - 


\return term - 

\param  protocol - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckAll"

logical pc_SDB_KeyComponent :: CheckAll (ErrorProtocol *protocol )
{
  int32       indx0 = 0;
  logical     term  = NO;
  while ( Get(indx0++) )
    if ( Check(protocol,NULL) )
      term = YES;

  return(term);
}

/******************************************************************************/
/**
\brief  IsKeyComponent - 


\return cond - 

\param  fldnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsKeyComponent"

logical pc_SDB_KeyComponent :: IsKeyComponent (char *fldnames )
{
  PropertyHandle  *member_path = GPH("member_path");
  char            *string      = NULL;
  char            *pos         = NULL;
  int32            indx0       = 0;
  logical          cond        = NO;
  while ( !cond && Get(indx0++) )
  {
    if ( pos = strchr((string = member_path->GetString()),'.') )
      *pos = 0;
  
    if ( !strcmp(fldnames,string) )
      cond = YES;
  
    if ( pos )
      *pos = '.';
  }

  return(cond);
}

/******************************************************************************/
/**
\brief  KeyDataDecl - 


\return string - 

\param  nstring - 
\param  dbs_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "KeyDataDecl"

char *pc_SDB_KeyComponent :: KeyDataDecl (NString &nstring, PropertyHandle *dbs_ph )
{
  PropertyHandle   *prop_ph  = NULL;
  SDB_Member       *dbmptr   = NULL;
BEGINSEQ
  nstring = "";
  
  if ( !dbs_ph->Inherits("SDB_Structure") )          SDBERR(99)
  
  pc_SDB_Structure struct_pc(GetDBHandle(),PI_Read); SDBCERR
  pc_SDB_Member    memb_pc(struct_pc.GetMember(GPH("member_path")->GetString(),YES,YES));
 
  if ( !memb_pc.IsPositioned() )                     SDBERR(99)

  nstring.Append(' ',14);
  memb_pc.KeyTypeCString(nstring,NULL);
  nstring += prop_ph->GPH("sys_ident")->GetString();
  memb_pc.CharSize(nstring);

RECOVER

ENDSEQ
  return(nstring);
}

/******************************************************************************/
/**
\brief  Store - 


\return term - 

\param  fmcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical pc_SDB_KeyComponent :: Store (fmcb *fmcbptr )
{
  char        string[ID_SIZE+1];
  logical     term = NO;
BEGINSEQ
  if ( NoWrite() )                                  ERROR

  *GPH("member_path") = gvtxbts(string,fmcbptr->fmcbname,ID_SIZE);
  *GPH("ignore_case") = fmcbptr->fmcbic;
  *GPH("descending")  = fmcbptr->fmcbdesc;
  
  Save();                                           SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  StoreAll - 


\return term - 

\param  keysmcb - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreAll"

logical pc_SDB_KeyComponent :: StoreAll (smcb *keysmcb )
{
  fmcb      *keyfmcb = NULL;
  int32      indx0   = 0;
  logical    term    = NO;
BEGINSEQ
  while ( keyfmcb = keysmcb->GetEntry(++indx0) )
  {
    ToTop();
    Add();                                           SDBCERR
    if ( Store(keyfmcb) )
      term = YES;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  pc_SDB_KeyComponent - 



\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pc_SDB_KeyComponent"

     pc_SDB_KeyComponent :: pc_SDB_KeyComponent (PropertyHandle *prophdl )
                     : PropertyHandle(prophdl)
{



}


