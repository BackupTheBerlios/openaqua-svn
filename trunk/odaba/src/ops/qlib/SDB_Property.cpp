/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    SDB_Property

\brief    Property
          Properties   of   a   structure   definition   define base structures,
          attributes, references and relationships for a structure.

\date     $Date: 2006/05/11 16:09:00,78 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Property"

#include  <pops7.h>
#include  <sDBFieldDef.hpp>
#include  <sSDB_Property.hpp>


/******************************************************************************/
/**
\brief  CreateFieldDef

\return fieldptr

\param  fieldptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFieldDef"

FieldDef *SDB_Property :: CreateFieldDef (FieldDef *fieldptr )
{
  SDB_Member::CreateFieldDef(fieldptr);
  return(fieldptr);
}

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

logical SDB_Property :: Fill (DatabaseHandle &dbhandle, char *propnames, char *proptypes )
{
  logical                 term = NO;
  Initialize();
  SDB_Member::Fill(dbhandle,propnames,proptypes);
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

logical SDB_Property :: GetAlignInfo (char *propname, int16 &size_info, int16 &offset_info )
{
  char            propnames[ID_SIZE+1];
  logical         term = NO;
  size_info   = 0;
  offset_info = 0;
  
  if ( !propname )
    size_info   = sizeof(*this);
  else          
  {
    gvtxbts(propnames,propname,sizeof(propnames)-1);
    if ( !strcmp("SDB_Member",propnames) )
    {
      size_info   = sizeof(*(SDB_Member *)this);
      offset_info = (char *)(SDB_Member *)this - (char *)this;
    }
    else if ( !strcmp("CAU_Causality",propnames) )
    {
      size_info   = sizeof(*(CAU_Causality *)this);
      offset_info = (char *)(CAU_Causality *)this - (char *)this;
    }
    else if ( !strcmp("ddetrans",propnames) )
    {
      size_info   = sizeof(ddetrans);
      offset_info = (char *)&ddetrans - (char *)this;
    }
    else if ( !strcmp("shared",propnames) )
    {
      size_info   = sizeof(shared);
      offset_info = (char *)&shared - (char *)this;
    }
    else if ( !strcmp("version",propnames) )
    {
      size_info   = sizeof(version);
      offset_info = (char *)&version - (char *)this;
    }
  }
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void SDB_Property :: Initialize ( )
{
  SDB_Member::Initialize();
  
  shared  = NO;
  ddetrans = YES;
  version  = UNDEF;
}

/******************************************************************************/
/**
\brief  InitializeBase


\param  gentype
\param  privileg
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeBase"

void SDB_Property :: InitializeBase (char *gentype, char privileg )
{
  Initialize();
  ddetrans = NO;
    
  if ( gentype )
    memcpy(ddegent,gentype,8);
  memcpy(ddetype,sys_ident,ID_SIZE);
  
  switch ( privileg )
  {
    case 'S'  : ddeprv = ODC_private;                      break;
    case 'R'  : ddeprv = ODC_protected;                    break;
    default   : ddeprv = ODC_public;                       break;
  }
}

/******************************************************************************/
/**
\brief  SDB_Property

-------------------------------------------------------------------------------
\brief  i0


\param  dbmref
\param  transopt
\param  ver
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Property"

     SDB_Property :: SDB_Property (SDB_Member &dbmref, logical transopt, uint8 ver )
                     : SDB_Member(&dbmref), 
CAU_Causality (),
  ddetrans(transopt),
  shared(NO),
  version(ver)
{
}

/******************************************************************************/
/**
\brief  i2


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Property"

     SDB_Property :: SDB_Property ( )
                     : SDB_Member(),
CAU_Causality (),
  ddetrans(NO),
  shared(NO),
  version(UNDEF)
{
}

/******************************************************************************/
/**
\brief  ~SDB_Property


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~SDB_Property"

     SDB_Property :: ~SDB_Property ( )
{
}


