/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    StructDef

\brief    Internal ODABA2 type definition
          Based   on   this   class   ODABA2   type   definitions   (see {\b {.r
          DBStructDef}})  are provided in the  main storage dictionary. The case
          class  {\b {.r smcb}} provides basic information about a data type and
          its structure.
          The  class itself has no information or functionallity of interest for
          an ODABA2 application programer.

\date     $Date: 2006/05/09 14:26:33,04 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "StructDef"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sfmcb.hpp>
#include  <sStructDef.hpp>


/******************************************************************************/
/**
\brief  GetDBStruct

\return strdefptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDBStruct"

DBStructDef *StructDef :: GetDBStruct ( )
{
  DBStructDef  *strdefptr = NULL;
  if ( this && smcbsts.stscnof() )
    strdefptr = (DBStructDef *)this;

  return(strdefptr);
}

/******************************************************************************/
/**
\brief  Setup

\return term - Termination code

\param  dictionary - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Setup"

logical StructDef :: Setup (Dictionary *dictionary )
{
  smcb                   *smcbptr;
  fmcb                   *fmcbptr;
  int32                    fldposn = 0;
  int16                   indx = 0;
  logical                 term = NO;
BEGINSEQ
  while ( fmcbptr = GetEntry(++indx) )
  {
    if ( fmcbptr->fmcbinwk )                         SDBERR(87)
    fmcbptr->fmcbinwk = YES;
    smcbptr = dictionary->ProvideStructDef(fmcbptr->fmcbtype);
    fmcbptr->fmcbinwk = NO;
    
    if ( !smcbptr )                                  SDBERR(20)
    
    if ( smcbptr->smcbstyp != ST_BASE || smcbptr->smcbityp == T_MEMO || smcbptr->smcbityp == T_BLOB )
      fmcbptr->fmcbsmcb = smcbptr;
    
    fmcbptr->fmcbesu(smcbptr,fldposn,defined_align,plattform_align);
    fldposn = fmcbptr->fmcbposn + fmcbptr->fmcbbyte;
  }
  
  smcb::SetLength(fldposn);

RECOVER
  term = YES;
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  StructDef


\param  strname - Type name
\param  nsid
\param  strsid - Internal structure number
\param  intlen - Internal length
\param  metatype - Meta type for a type definition
\param  strtype - Structure meta type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StructDef"

     StructDef :: StructDef (char *strname, int32 nsid, int16 strsid, int32 intlen, TYP_TYPES metatype, SDB_ST strtype )
                     : acc(UNDEF),
smcb(strname,nsid,
     strsid,intlen,strtype)
{
  switch ( metatype )
  {
    case TYP_Codeset   : smcbstyp = ST_CODE;              
                         smcbatyp = AT_CODE;              break;
    case TYP_Base      : smcbstyp = ST_BASE;              break;
//  case TYP_Structure : smcbstyp = strtype;              break;
    default            : ;
  }
}

/******************************************************************************/
/**
\brief  ~StructDef - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~StructDef"

     StructDef :: ~StructDef ( )
{
}


