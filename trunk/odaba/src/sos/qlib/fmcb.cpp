/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    fmcb

\brief    Field definition block


\date     $Date: 2006/06/13 22:22:19,42 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "fmcb"

#include  <pdefault.h>
#include  <csmcbdef.h>
#include  <csmcbmac.h>
#include  <cwinsock.h>
#include  <guidstr.h>
class     DBFieldDef;
#include  <cDataFormSpec.h>
#include  <sSeparatorDef.hpp>
#include  <scvb.hpp>
#include  <sdfs.hpp>
#include  <sfmcb.hpp>
#include  <sguid.hpp>
#include  <imsm.h>
#include  <spvcls.hpp>
#include  <ssmcb.hpp>
#include  <sfmcb.hpp>


/******************************************************************************/
/**
\brief  AddSynonym - Add synonym
        The function adds a synonym to the field definition.

\return term - Success

\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddSynonym"

logical fmcb :: AddSynonym (char *names )
{
  logical                 term = NO;
BEGINSEQ
  if ( !names || !*names )                           ERROR
    
  if ( !fmcbsyns )
    fmcbsyns = new DLL(char)();

  fmcbsyns->AddTail(strdup(names));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AllocateArea - 


\return datarea - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocateArea"

void *fmcb :: AllocateArea ( )
{
  char	   *datarea = NULL;

BEGINSEQ
  if ( !fmcbbyte )
    fmcbbytc();

  if ( !fmcbbyte )                                   ERROR

  if ( !(datarea = (char *)msmgs(fmcbbyte)) )        SOSERR(95)

//  if ( !(datarea = new char[fmcbbyte]) )             SOSERR(95)
  memset(datarea,0,fmcbbyte);
  fmcbiini(datarea);

RECOVER

ENDSEQ
  return(datarea);

}

/******************************************************************************/
/**
\brief  CalculateLength - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CalculateLength"

void fmcb :: CalculateLength ( )
{

  fmcbbytc();

}

/******************************************************************************/
/**
\brief  CompareConst - 


\return term - Success

\param  instptr - Structured instance
\param  charval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareConst"

logical fmcb :: CompareConst (char *instptr, char charval )
{
  int                     indx = fmcbbyte;
  logical                 cond = NO;
BEGINSEQ
  while (indx--)
  {
    if ( *instptr != charval )                       ERROR
    instptr++;          
  }

RECOVER
  cond = YES;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  ConvertDimFromNet - 


\return term - Success

\param  netfld - 
\param  intfld - 
\param  netlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertDimFromNet"

logical fmcb :: ConvertDimFromNet (char *netfld, char *intfld, int32 netlen )
{
  int32                   dim  = fmcbdim ? fmcbdim : 1;
  int32                   len  = fmcbbyte/dim;
  int32                   i    = 0;
  logical                 term = NO;
  if ( !netlen ) 
    netlen = len;
    
  while ( i++ < dim )
  {
    ConvertFromNet(netfld,intfld);
    intfld += len;
    netfld += netlen;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  ConvertDimToNet - 


\return term - Success

\param  netfld - 
\param  intfld - 
\param  netlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertDimToNet"

logical fmcb :: ConvertDimToNet (char *netfld, char *intfld, int32 netlen )
{
  int32                   dim  = fmcbdim ? fmcbdim : 1;
  int32                   len  = fmcbbyte/dim;
  int32                   i    = 0;
  logical                 term = NO;
  if ( !netlen ) 
    netlen = len;
    
  while ( i++ < dim )
  {
    ConvertToNet(netfld,intfld);
    intfld += len;
    netfld += netlen;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  ConvertFromNet - 



\param  netfld - 
\param  intfld - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertFromNet"

void fmcb :: ConvertFromNet (char *netfld, char *intfld )
{
  int32        len = fmcbbyte / (fmcbdim ? fmcbdim : 1);
  register     int i;
  switch ( fmcbrlev )
  {
    case R_REFR    : break;
    case R_GENERIC :
    case R_INTERN  :
    case R_DIRECT  : switch ( fmcbityp )
                     {
                      case T_INT    :
                      case T_UINT   : 
                      case T_DATE   :  
                      case T_TIME   : ConvertIFromNet(netfld,intfld);
                                      break;
                      case T_REAL   : if ( fmcbbyte = 4 )
                                        LoadFloat(intfld,netfld)
                                      else
                                        LoadDouble(intfld,netfld)
                                      break;
                      case T_GUID   : memcpy(intfld,netfld,S_GUID);
                                      ((guid *)intfld)->FromPIF(YES);
                                      break;
                      case T_LO     :
                      case T_CCHAR  :
                      case T_STRING :
                      case T_CHAR   : if ( netfld != intfld )
                                        memcpy(intfld,netfld,len);  
                                      break;                     
                      
                      case T_BIT    : i = (len+1)/2;
                                      while ( i-- )
                                        *(bit *)(intfld+i*2) = ntohs(*(bit *)netfld);
                                      break;
                     
                      default       : if ( fmcbsmcb )
                                      {
                                        if ( fmcbsmcb->smcbstyp == ST_CODE )
                                          ConvertIFromNet(netfld,intfld);
                                        else
                                          fmcbsmcb->ConvertFromNet(netfld,intfld);
                                      }
                     }
                     break;
    default	   : break;
  }

}

/******************************************************************************/
/**
\brief  ConvertIFromNet - 



\param  netfld - 
\param  intfld - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertIFromNet"

void fmcb :: ConvertIFromNet (char *netfld, char *intfld )
{
  int32   len = fmcbbyte/fmcbdim;
  int16   sval;
  int32   lval;
  int64   bval;
  switch ( len )
  {
    case  1 : *(uint8 *) intfld = *(uint8 *)netfld;
              break;
    case  2 : LoadShort(sval,netfld);
              *(uint16 *)intfld = ntohs(sval);
              break;
    case  4 : LoadLong(lval,netfld);
              *(uint32 *)intfld = ntohl(lval);
              break;
    case  8 : LoadBigInt(bval,netfld);
              *(uint64 *)intfld = ntohb(bval);
              break;
    default : ;
  }


}

/******************************************************************************/
/**
\brief  ConvertIToNet - 



\param  netfld - 
\param  intfld - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertIToNet"

void fmcb :: ConvertIToNet (char *netfld, char *intfld )
{
  int     len = fmcbbyte/fmcbdim;
  int16   sval;
  int32   lval;
  int64   bval;
  switch ( len )
  {
    case  1 : *(uint8 *) netfld = *(uint8 *)intfld;
              break;
    case  2 : sval = htons(*(uint16 *)intfld);
              StoreShort(netfld,sval);
              break;
    case  4 : lval = htonl(*(uint32 *)intfld);
              StoreLong(netfld,lval);
              break;
    case  8 : bval = htonb(*(uint64 *)intfld);
              StoreBigInt(netfld,bval);
              break;
    default : ;
  }


}

/******************************************************************************/
/**
\brief  ConvertToNet - 



\param  netfld - 
\param  intfld - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToNet"

void fmcb :: ConvertToNet (char *netfld, char *intfld )
{
  int32        len = fmcbbyte / (fmcbdim ? fmcbdim : 1);
  register     int i;
  switch ( fmcbrlev )
  {
    case R_REFR    : break;
    case R_GENERIC :
    case R_INTERN  :
    case R_DIRECT  : switch ( fmcbityp )
                     {
                      case T_INT    :
                      case T_UINT   : 
                      case T_DATE   :  
                      case T_TIME   : ConvertIToNet(netfld,intfld);
                                      break;
                      case T_REAL   : if ( fmcbbyte = 4 )
                                        StoreFloat(netfld,intfld)
                                      else
                                        StoreDouble(netfld,intfld)
                                      break;
                      case T_GUID   : memcpy(netfld,intfld,S_GUID);
                                      ((guid *)netfld)->ToPIF(YES);
                                      break;
                      case T_LO     :
                      case T_CCHAR  :
                      case T_STRING :
                      case T_CHAR   : if ( netfld != intfld )
                                        memcpy(netfld,intfld,len);  
                                      break;                     
                      case T_BIT    : i = (len+1)/2;
                                      while ( i-- )
                                        *(bit *)(netfld+i*2) = htons(*(bit *)intfld);
                                      break;
                     
                      default       : if ( fmcbsmcb )
                                      {
                                        if ( fmcbsmcb->smcbstyp == ST_CODE )
                                          ConvertIToNet(netfld,intfld);
                                        else
                                          fmcbsmcb->ConvertToNet(netfld,intfld); // hier fehlen noch structure arrays
                                      }
                     }
                     break;
    default	   : break;
  }


}

/******************************************************************************/
/**
\brief  ConvertToString - 


\return string - String value
-------------------------------------------------------------------------------
\brief  SMCBITS - 


\param  instptr - Structured instance
\param  string - String value
\param  str_sep - String separator
\param  field_sep - Field separator
\param  block_sep - Block separator
\param  empty_str - String for empty values
\param  srlen - Maximum string length
\param  skip_trans - Skip transient field
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToString"

char *fmcb :: ConvertToString (char *instptr, char *string, char *str_sep, char *field_sep, char *block_sep, char *empty_str, int32 srlen, logical skip_trans )
{

  SeparatorDef    sep_def(str_sep,field_sep,block_sep,NULL,empty_str);
  
  return( ConvertToString(sep_def,instptr,string,srlen,skip_trans) );




}

/******************************************************************************/
/**
\brief  i01 - 


\param  instptr - Structured instance
\param  string - String value
\param  srlen - Maximum string length
\param  skip_trans - Skip transient field
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToString"

char *fmcb :: ConvertToString (char *instptr, char *string, int32 srlen, logical skip_trans )
{
  char      field_sep[3];
  char      block_sep[3];
  memset(field_sep,0,sizeof(field_sep));
  memset(block_sep,0,sizeof(block_sep));
  memcpy(block_sep,dfs::GetParenthesis(),2);
  *field_sep = dfs::GetSeparator();
  
  return(ConvertToString(instptr,string,NULL,field_sep,block_sep,NULL,srlen,skip_trans));

}

/******************************************************************************/
/**
\brief  i02 - 


\param  sep_def - 
\param  instptr - Structured instance
\param  string - String value
\param  srlen - Maximum string length
\param  skip_trans - Skip transient field
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToString"

char *fmcb :: ConvertToString (SeparatorDef &sep_def, char *instptr, char *string, int32 srlen, logical skip_trans )
{
  int32     len        = srlen ? srlen : GetStringLength();
  int32     tlen;
  int16     indx       = 0;
  char     *retstr     = string;
  logical   block;    

BEGINSEQ
  block = (fmcbstpg() == ST_USER ||
           fmcbstpg() == ST_KEY  || 
           fmcbstpg() == ST_SYS     ) &&
         fmcbsmcb->smcbfmcl->GetCount() > 1;
           
  if ( len > 0 && block )
  {
    if ( len && sep_def.block_start )
    {
      *string = sep_def.block_start;
      string++;
      len--;
    }
    
    fmcbsmcb->ConvertToString(sep_def,instptr,string,len,skip_trans);
    tlen = MIN((ushort)len,strlen(string));
    string += tlen;
    len    -= tlen;

    if ( len && sep_def.block_stop )
    {
      *string = sep_def.block_stop;
      string++;
      len--;
    }
  }
  else    
  {
    if ( sep_def.empty_str && fmcbempty && IsText() && IsEmpty(instptr) )
    {
      strcpy(string,sep_def.empty_str);
      tlen = MIN((ushort)len,strlen(string));
      string += tlen;
      len    -= tlen;
    }
    else
    {
      if ( len && sep_def.field_start )   
      {
        *string = sep_def.field_start;
        string++;
        len--;
      }
      
      if ( sep_def.string_start && IsText() && len )
      {
        *string = sep_def.string_start;
        string++;
        len--;
      }
       
      sep_def.stringfmcb->fmcbsize = sep_def.stringfmcb->fmcbbyte = (ushort)len;
      if ( sep_def.stringfmcb->fmcbicvt(this,string,instptr) )
                                                     ERROR
      if ( sep_def.string_repl )
      {
        InsertCharBefore(string,sep_def.string_repl,sep_def.string_start,len);
        if ( sep_def.string_start != sep_def.string_stop )
          InsertCharBefore(string,sep_def.string_repl,sep_def.string_stop,len);
      }
      if ( sep_def.field_repl )
      {
        InsertCharBefore(string,sep_def.field_repl,sep_def.field_start,len);
        if ( sep_def.field_start != sep_def.field_stop )
          InsertCharBefore(string,sep_def.field_repl,sep_def.field_stop,len);
      }
      if ( sep_def.block_repl )
      {
        InsertCharBefore(string,sep_def.block_repl,sep_def.block_start,len);
        if ( sep_def.block_start != sep_def.block_stop )
          InsertCharBefore(string,sep_def.block_repl,sep_def.block_stop,len);
      }
      
      tlen = MIN((ushort)len,strlen(string));
      string += tlen;
      len    -= tlen;

      if ( sep_def.string_stop &&IsText() && len )
      {
        *string = sep_def.string_stop;
        string++;
        len--;
      }

      if ( len && sep_def.field_start && sep_def.field_stop )   
      {
        *string = sep_def.field_stop;
        string++;
        len--;
      }
    }
  }
  *string = 0;
RECOVER
  retstr = NULL;
ENDSEQ
  return(retstr);
}

/******************************************************************************/
/**
\brief  ConvertToStruct - 


\return string - String value

\param  instptr - Structured instance
\param  string - String value
\param  srlen - Maximum string length
\param  skip_trans - Skip transient field
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToStruct"

char *fmcb :: ConvertToStruct (char *instptr, char *string, int32 srlen, logical skip_trans )
{

BEGINSEQ
  if ( !this || !fmcbsmcb )                          ERROR
    
 instptr = fmcbsmcb->ConvertToStruct(string,instptr,srlen);
RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  CopySynonyms - 



\param  synonyms - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopySynonyms"

void fmcb :: CopySynonyms (DLL(char) *synonyms )
{
  char                   *names;

BEGINSEQ
  if ( !synonyms )                                   LEAVESEQ
    
  DLL(char)     cursor(*synonyms);
  
  cursor.GoTop();
  while ( names = cursor.GetNext() )
    AddSynonym(names);
ENDSEQ

}

/******************************************************************************/
/**
\brief  DTConversion - 


\return term - Success

\param  srcefmcb - 
\param  srceinst - Structured instance area
\param  targinst - Structured instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DTConversion"

logical fmcb :: DTConversion (fmcb *srcefmcb, char *srceinst, char *targinst )
{
  logical                 term = NO;
BEGINSEQ
  if ( (fmcbityp == T_DATE || fmcbityp == T_TIME) &&
       !memcmp(srcefmcb->fmcbtype,"DATETIME  ",10)   )
  {
    switch ( fmcbityp )
    {
      case T_DATE : *(dbdt *)targinst = ((dttm *)srceinst)->GetDate();
                    break;
      case T_TIME : *(dbtm *)targinst = ((dttm *)srceinst)->GetTime();
                    break;
      default : ;
    }
    LEAVESEQ
  }
  if ( (srcefmcb->fmcbityp == T_DATE || srcefmcb->fmcbityp == T_TIME) &&
       !memcmp(fmcbtype,"DATETIME  ",10)   )
  {
    switch ( fmcbityp )
    {
      case T_DATE : ((dttm *)targinst)->SetDate(*(dbdt *)srceinst);
                    break;
      case T_TIME : ((dttm *)targinst)->SetTime(*(dbtm *)srceinst);
                    break;
      default : ;
    }
    LEAVESEQ
  }
  if ( (srcefmcb->fmcbityp == T_STRING || srcefmcb->fmcbityp == T_CHAR) )
  {
    if ( !ConvertToStruct(targinst,srceinst,fmcbbyte,YES) )
                                                     ERROR
    LEAVESEQ
  }
  ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FreeArea - 



\param  areapptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FreeArea"

void __cdecl fmcb :: FreeArea (char **areapptr )
{

  msmfs((void **)areapptr);



}

/******************************************************************************/
/**
\brief  GetAllignedPosition - 


\return position - 

\param  fldposn - 
\param  allign - 
\param  max_aligned - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAllignedPosition"

int32 fmcb :: GetAllignedPosition (int32 fldposn, int16 allign, int8 &max_aligned )
{
  int32                   position     = fldposn;
  int                     field_allign = 1;
  int                     unallign;
BEGINSEQ
  if ( !allign )
    allign = DEFAULT_ALLIGNMENT;
  if ( allign > 0 )
  {
    field_allign = GetPlattformAlign();
    max_aligned  = MAX(max_aligned,field_allign);
  }
  
  if ( allign < 2 )                                  LEAVESEQ
  if ( position%allign == 0 )                        LEAVESEQ
    
  if ( !(allign = MIN(field_allign,allign)) )
    allign = 1;
  if ( !(unallign = position%allign) )               LEAVESEQ
  position = position - unallign + allign;
ENDSEQ
  return(position);
}

/******************************************************************************/
/**
\brief  GetCharLength - 


\return srlen - Maximum string length

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCharLength"

int32 fmcb :: GetCharLength ( )
{
  int32   chlen = UNDEF;

  switch ( fmcbityp )
  {
    case T_LO     : chlen = 1;
                    break;
    case T_MEMO   : 
    case T_CHAR   :
    case T_BIT    :
    case T_CCHAR  :
    case T_STRING : chlen = fmcbsize;
                    break;
    case T_GUID   : chlen = sizeof(__guid_string);
                    break;
    case T_INT    : chlen = 1;
    case T_UINT   : chlen += fmcbsize + (fmcbprec > 0);
                    break;
    case T_REAL   : MIN(128,fmcbsize + (fmcbprec > 0)+1+5);
                    break;
    case T_TIME   : chlen = fmcbsize;
                    switch ( dfs::GetTimeFormat() )
                    {
                      case DFS_HHMMSSHH : chlen = MIN(8,chlen);              break;
                      case DFS_HHMMSS   : chlen = MIN(6,chlen);              break;
                      case DFS_HHMM     : chlen = MIN(4,chlen);              break;
                      default           : ;
                    }
                    chlen += ((chlen>=4) + (chlen>=6) + (chlen>=8));
                    break;
    case T_DATE   : chlen = fmcbsize; // 10;
                    switch ( dfs::GetDateFormat() )
                    {
                      case DFS_YYMMDD_slash :
                      case DFS_YYMMDD_point : 
                      case DFS_TTMMJJ_punkt : chlen += ((fmcbsize>=4) + (fmcbsize>=6));
                      default               : ;
                    }
                    break;
    default       : if ( fmcbsmcb && !fmcbinwk  )
                    {
                      fmcbinwk = YES;
                      chlen = fmcbsmcb->smcbstyp == ST_CODE ? ID_SIZE  // sizeof ENUM_Value::name
                                                            : fmcbsmcb->GetCharLength();
                      fmcbinwk = NO;
                    }
  }
  return(chlen);

}

/******************************************************************************/
/**
\brief  GetDescription - 


\return field_descr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDescription"

DBFieldDef *fmcb :: GetDescription ( )
{

  return((DBFieldDef *)(this && fmcbopt ? this : NULL));

}

/******************************************************************************/
/**
\brief  GetInternalType - 


\return ityp - 

\param  typenames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInternalType"

int16 __cdecl fmcb :: GetInternalType (char *typenames )
{
  char              typestr[ID_SIZE+1];
  int16             ityp = UNDEF;
  gvtxbts(typestr,typenames,ID_SIZE);
  
  if ( !strcmp(typestr,"INT") )
    ityp = T_INT;

  if ( !strcmp(typestr,"UINT") )
    ityp = T_UINT;
  
  if ( !strcmp(typestr,"CHAR") )
    ityp = T_CHAR;

  if ( !strcmp(typestr,"CCHAR") )
    ityp = T_CCHAR;

  if ( !strcmp(typestr,"BLOB") )
    ityp = T_BLOB;
  
  if ( !strcmp(typestr,"STRING") )
    ityp = T_STRING;

  if ( !strcmp(typestr,"LOGICAL") )
    ityp = T_LO;

  if ( !strcmp(typestr,"REAL") )
    ityp = T_REAL;

  if ( !strcmp(typestr,"GUID") )
    ityp = T_GUID;
  
  if ( !strcmp(typestr,"DATE") )
    ityp = T_DATE;

  if ( !strcmp(typestr,"TIME") )
    ityp = T_TIME;

  if ( !strcmp(typestr,"DATETIME") )
    ityp = T_DATETIME;

  if ( !strcmp(typestr,"VOID") || !*typestr )
    ityp = T_VOID;

  return(ityp);
}

/******************************************************************************/
/**
\brief  GetPlattformAlign - 


\return align - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPlattformAlign"

int8 fmcb :: GetPlattformAlign ( )
{
  int16    dim         = fmcbdim > 0 ? fmcbdim : 1;
  int8     field_align = 1;
BEGINSEQ
  if ( fmcbrlev == R_REFR )
    field_align = sizeof(void *); // entspricht sizeof(PropertyHandle) nd 19.11.03, fuer pack=8 ist field_alignment auf 32bit 4
  else if ( fmcbrlev > 0 )
    field_align = sizeof(void *);
  else
    switch ( fmcbityp )
    {
      case T_DATE     :
      case T_DATETIME :
      case T_TIME     : field_align = 4;
                        break;
      case T_REAL     : 
      case T_UINT     : 
      case T_INT      : field_align = fmcbbyte/dim;
                        break;
      case T_MEMO     : field_align = sizeof(void *);
                        break;
      case T_VOID     :
      case T_LO       :
      case T_CHAR     :
      case T_CCHAR    :
      case T_GUID     : 
      case T_BLOB     :
      case T_STRING   : field_align = 1;
                        break;
      case T_BIT      : field_align = sizeof(int);
                        break;
      default         : if ( !fmcbsmcb )             SOSERR(99)
                        switch ( fmcbsmcb->smcbstyp )
                        {
                          case ST_CODE : field_align = sizeof(int32);
                                         break;
                          case ST_USER :
                          case ST_SYS  :
                          case ST_VIEW :
                          case ST_KEY  : if ( !(field_align = fmcbsmcb->plattform_align) )
                                                     SOSERR(99)
                                         break;
                          default      : SOSERR(99)
                        }
    }
RECOVER
  SOSRESET
ENDSEQ
  return(field_align);
}

/******************************************************************************/
/**
\brief  GetPosition - 


\return fldpos - 

\param  setindx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosition"

uint16 fmcb :: GetPosition (int32 setindx )
{
  ushort    fpos = 0;

  if ( setindx && fmcbdim > 1 )
    fpos = setindx * (fmcbbyte/fmcbdim);
  return ( (ushort)(fmcbposn+fpos) );

}

/******************************************************************************/
/**
\brief  GetStaticFMCB - 


\return fmcbptr - Field definition block

\param  ityp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStaticFMCB"

fmcb *__cdecl fmcb :: GetStaticFMCB (int16 ityp )
{

//                              name        typ       nsid rlev     size       prec/dim/posn/byte         ityp      /ucd/var/ind/opt
  static    fmcb  lo_fmcb      ("LOGICAL" ,"LOGICAL" ,0   ,R_DIRECT,1         ,0   ,1  ,0   ,1           ,T_LO      ,NO ,NO ,YES,NO );
  static    fmcb  int_fmcb     ("INT"     ,"INT"     ,0   ,R_DIRECT,10        ,0   ,1  ,0   ,4           ,T_INT     ,NO ,NO ,YES,NO );
  static    fmcb  uint_fmcb    ("UINT"    ,"UINT"    ,0   ,R_DIRECT,10        ,0   ,1  ,0   ,4           ,T_UINT    ,NO ,NO ,YES,NO );
  static    fmcb  real_fmcb    ("REAL"    ,"REAL"    ,0   ,R_DIRECT,17        ,5   ,1  ,0   ,8           ,T_REAL    ,NO ,NO ,NO ,NO );
  static    fmcb  char_fmcb    ("CHAR"    ,"CHAR"    ,0   ,R_DIRECT,DEF_BUFLEN,0   ,1  ,0   ,DEF_BUFLEN  ,T_CHAR    ,NO ,NO ,NO ,NO );
  static    fmcb  string_fmcb  ("STRING"  ,"STRING"  ,0   ,R_DIRECT,DEF_BUFLEN,0   ,1  ,0   ,DEF_BUFLEN+1,T_STRING  ,NO ,NO ,NO ,NO );
  static    fmcb  wchar_fmcb   ("CHAR"    ,"CHAR"    ,0   ,R_DIRECT,DEF_BUFLEN,0   ,1  ,0   ,DEF_BUFLEN  ,T_CHAR    ,YES,NO ,NO ,NO );
  static    fmcb  wstring_fmcb ("STRING"  ,"STRING"  ,0   ,R_DIRECT,DEF_BUFLEN,0   ,1  ,0   ,DEF_BUFLEN+1,T_STRING  ,YES,NO ,NO ,NO );
  static    fmcb  cchar_fmcb   ("CCHAR"   ,"CCHAR"   ,0   ,R_DIRECT,DEF_BUFLEN,0   ,1  ,0   ,DEF_BUFLEN  ,T_CCHAR   ,NO ,NO ,NO ,NO );
  static    fmcb  guid_fmcb    ("GUID"    ,"GUID"    ,0   ,R_DIRECT,S_GUID    ,0   ,1  ,0   ,S_GUID      ,T_GUID    ,NO ,NO ,NO ,NO );
  static    fmcb  date_fmcb    ("DATE  "  ,"DATE  "  ,0   ,R_DIRECT,8         ,0   ,1  ,0   ,4           ,T_DATE    ,NO ,NO ,YES,NO );
  static    fmcb  time_fmcb    ("TIME  "  ,"TIME  "  ,0   ,R_DIRECT,11        ,0   ,1  ,0   ,4           ,T_TIME    ,NO ,NO ,YES,NO );
  static    fmcb  datetime_fmcb("DATETIME","DATETIME",0   ,R_DIRECT,16        ,0   ,1  ,0   ,8           ,T_DATETIME,NO ,NO ,YES,NO );

  switch ( ityp )
  {
    case T_LO       : return ( &lo_fmcb );
    case T_INT      : return ( &int_fmcb );
    case T_UINT     : return ( &uint_fmcb );
    case T_REAL     : return ( &real_fmcb );
    case T_STRING   : return ( &string_fmcb );
    case T_CHAR     : return ( &char_fmcb );
    case T_CCHAR    : return ( &cchar_fmcb );
    case T_DATE     : return ( &date_fmcb );
    case T_TIME     : return ( &time_fmcb );
    case T_DATETIME : return ( &datetime_fmcb );
    case T_GUID     : return ( &guid_fmcb );
  }
  return(NULL);

}

/******************************************************************************/
/**
\brief  GetStaticFMCB2 - 


\return fmcbptr - Field definition block

\param  ityp - 
\param  size - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStaticFMCB2"

fmcb *__cdecl fmcb :: GetStaticFMCB2 (int16 ityp, uint16 size )
{

//                              name        typ       nsid rlev     size       prec/dim/posn/byte         ityp      /ucd/var/ind/opt
  static    fmcb  lo_fmcb      ("LOGICAL" ,"LOGICAL" ,0   ,R_DIRECT,1         ,0   ,1  ,0   ,1           ,T_LO      ,NO ,NO ,YES,NO );
  static    fmcb  int_fmcb8    ("INT"     ,"INT"     ,0   ,R_DIRECT,1         ,0   ,1  ,0   ,4           ,T_INT     ,NO ,NO ,YES,NO );
  static    fmcb  int_fmcb16   ("INT"     ,"INT"     ,0   ,R_DIRECT,4         ,0   ,1  ,0   ,4           ,T_INT     ,NO ,NO ,YES,NO );
  static    fmcb  int_fmcb32   ("INT"     ,"INT"     ,0   ,R_DIRECT,10        ,0   ,1  ,0   ,4           ,T_INT     ,NO ,NO ,YES,NO );
  static    fmcb  int_fmcb64   ("INT"     ,"INT"     ,0   ,R_DIRECT,17        ,0   ,1  ,0   ,4           ,T_INT     ,NO ,NO ,YES,NO );
  static    fmcb  uint_fmcb8   ("UINT"    ,"UINT"    ,0   ,R_DIRECT,1         ,0   ,1  ,0   ,4           ,T_UINT    ,NO ,NO ,YES,NO );
  static    fmcb  uint_fmcb16  ("UINT"    ,"UINT"    ,0   ,R_DIRECT,4         ,0   ,1  ,0   ,4           ,T_UINT    ,NO ,NO ,YES,NO );
  static    fmcb  uint_fmcb32  ("UINT"    ,"UINT"    ,0   ,R_DIRECT,10        ,0   ,1  ,0   ,4           ,T_UINT    ,NO ,NO ,YES,NO );
  static    fmcb  uint_fmcb64  ("UINT"    ,"UINT"    ,0   ,R_DIRECT,17        ,0   ,1  ,0   ,4           ,T_UINT    ,NO ,NO ,YES,NO );
  static    fmcb  real_fmcb32  ("REAL"    ,"REAL"    ,0   ,R_DIRECT,7         ,5   ,1  ,0   ,8           ,T_REAL    ,NO ,NO ,NO ,NO );
  static    fmcb  real_fmcb64  ("REAL"    ,"REAL"    ,0   ,R_DIRECT,17        ,5   ,1  ,0   ,8           ,T_REAL    ,NO ,NO ,NO ,NO );
  static    fmcb  char_fmcb    ("CHAR"    ,"CHAR"    ,0   ,R_DIRECT,DEF_BUFLEN,0   ,1  ,0   ,DEF_BUFLEN  ,T_CHAR    ,NO ,NO ,NO ,NO );
  static    fmcb  string_fmcb  ("STRING"  ,"STRING"  ,0   ,R_DIRECT,DEF_BUFLEN,0   ,1  ,0   ,DEF_BUFLEN+1,T_STRING  ,NO ,NO ,NO ,NO );
  static    fmcb  wchar_fmcb   ("CHAR"    ,"CHAR"    ,0   ,R_DIRECT,DEF_BUFLEN,0   ,1  ,0   ,DEF_BUFLEN  ,T_CHAR    ,YES,NO ,NO ,NO );
  static    fmcb  wstring_fmcb ("STRING"  ,"STRING"  ,0   ,R_DIRECT,DEF_BUFLEN,0   ,1  ,0   ,DEF_BUFLEN+1,T_STRING  ,YES,NO ,NO ,NO );
  static    fmcb  cchar_fmcb   ("CCHAR"   ,"CCHAR"   ,0   ,R_DIRECT,DEF_BUFLEN,0   ,1  ,0   ,DEF_BUFLEN  ,T_CCHAR   ,NO ,NO ,NO ,NO );
  static    fmcb  guid_fmcb    ("GUID"    ,"GUID"    ,0   ,R_DIRECT,S_GUID    ,0   ,1  ,0   ,S_GUID      ,T_GUID    ,NO ,NO ,NO ,NO );
  static    fmcb  date_fmcb    ("DATE  "  ,"DATE  "  ,0   ,R_DIRECT,8         ,0   ,1  ,0   ,4           ,T_DATE    ,NO ,NO ,YES,NO );
  static    fmcb  time_fmcb    ("TIME  "  ,"TIME  "  ,0   ,R_DIRECT,11        ,0   ,1  ,0   ,4           ,T_TIME    ,NO ,NO ,YES,NO );
  static    fmcb  datetime_fmcb("DATETIME","DATETIME",0   ,R_DIRECT,16        ,0   ,1  ,0   ,8           ,T_DATETIME,NO ,NO ,YES,NO );

  switch ( ityp )
  {
    case T_LO       : return ( &lo_fmcb );
    case T_INT      : return ( size <= 2  ? &int_fmcb8  : 
                               size <= 4  ? &int_fmcb16 :
                               size <= 10 ? &int_fmcb32 :
                               &int_fmcb64  );
    case T_UINT     : return ( size <= 2  ? &uint_fmcb8  : 
                               size <= 4  ? &uint_fmcb16 :
                               size <= 10 ? &uint_fmcb32 :
                               &uint_fmcb64  );
    case T_REAL     : return ( size <= 7 ? &real_fmcb32 :
                               &real_fmcb64  );
    case T_STRING   : return ( &string_fmcb );
    case T_CHAR     : return ( &char_fmcb );
    case T_CCHAR    : return ( &cchar_fmcb );
    case T_DATE     : return ( &date_fmcb );
    case T_TIME     : return ( &time_fmcb );
    case T_DATETIME : return ( &datetime_fmcb );
    case T_GUID     : return ( &guid_fmcb );
  }
  return(NULL);

}

/******************************************************************************/
/**
\brief  GetStringLength - 


\return srlen - Maximum string length

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringLength"

int32 fmcb :: GetStringLength ( )
{
  int32  stlen = UNDEF;

  switch ( fmcbityp )
  {
    case T_LO     : stlen = 1;
                    break;
    case T_MEMO   : 
    case T_CHAR   :
    case T_BIT    :
    case T_CCHAR  :
    case T_STRING : stlen = fmcbsize;
                    break;
    case T_GUID   : stlen = sizeof(__guid_string);
                    break;
    case T_INT    : stlen = 1;
    case T_UINT   : stlen += fmcbsize + (fmcbprec > 0);
                    break;
    case T_REAL   : stlen = MIN(128,fmcbsize + (fmcbprec > 0)+1+5);
                    break;
    case T_TIME   : stlen = fmcbsize;
                    switch ( dfs::GetTimeFormat() )
                    {
                      case DFS_HHMMSSHH : stlen = MIN(8,stlen);              break;
                      case DFS_HHMMSS   : stlen = MIN(6,stlen);              break;
                      case DFS_HHMM     : stlen = MIN(4,stlen);              break;
                      default           : ;
                    }
                    stlen += ((stlen>=4) + (stlen>=6) + (stlen>=8));
                    break;
    case T_DATE   : stlen = fmcbsize; // 10;
                    switch ( dfs::GetDateFormat() )
                    {
                      case DFS_YYMMDD_slash :
                      case DFS_YYMMDD_point : 
                      case DFS_TTMMJJ_punkt : stlen += ((fmcbsize>=4) + (fmcbsize>=6));
                      default               : ;
                    }
                    break;
    default       : if ( fmcbsmcb && !fmcbinwk  )
                    {
                      fmcbinwk = YES;
                      if ( fmcbsmcb->smcbstyp == ST_CODE )
                        stlen = ID_SIZE+1;  // sizeof ENUM_Value::name
                      else
                        stlen = fmcbsmcb->GetStringLength();
                      fmcbinwk = NO;
                    }
  }
  return(stlen);

}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Success

\param  intfld - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical fmcb :: Initialize (char *intfld )
{

  return ( fmcbiini(intfld) );

}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond - Return value

\param  instptr - Structured instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical fmcb :: IsEmpty (char *instptr )
{
  ushort                  i    = 0;
  short                   dim;
  logical                 cond = YES;
BEGINSEQ
  if ( fmcbrlev != R_DIRECT && fmcbrlev != R_GENERIC && fmcbrlev != R_INTERN )
  {
    if ( fmcbrlev != R_REFR )
      if ( CompareConst(instptr,0) )                 ERROR
    LEAVESEQ // für Referenzen wird vorerst immer leer angenommen
  }  

  switch ( fmcbityp )
  {
    case T_BIT      :
    case T_DATE     :
    case T_TIME     :
    case T_INT      :
    case T_UINT     :
    case T_REAL     :
    case T_LO       : if ( CompareConst(instptr,0) )   ERROR
                      LEAVESEQ
    case T_STRING   : if ( fmcbbyte > 0 && *instptr )  ERROR
                      LEAVESEQ
    case T_CCHAR    : 
    case T_CHAR     : if ( CompareConst(instptr,' ') ) ERROR
                      LEAVESEQ
    case T_GUID     : if ( !((guid *)instptr)->IsEmpty() )
                                                     ERROR
                      LEAVESEQ
  }
  
  dim = fmcbrlev == R_GENERIC ? 1 : fmcbdim;
  for (i=0; i < dim; i++, instptr+=fmcbbyte/dim )
  {
    if ( !fmcbsmcb )                                 LEAVESEQ
    if ( fmcbsmcb->smcbstyp == ST_CODE )
    {
      if ( CompareConst(instptr,0) )                 ERROR
    }
    else
      if ( !fmcbsmcb->IsEmpty(instptr) )             ERROR
  }    

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsEnumerator - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEnumerator"

logical fmcb :: IsEnumerator ( )
{

  return ( this && fmcbsmcb && fmcbsmcb->smcbstyp == ST_CODE );

}

/******************************************************************************/
/**
\brief  IsGenericType - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsGenericType"

logical fmcb :: IsGenericType ( )
{

  return(fmcbgentype);

}

/******************************************************************************/
/**
\brief  IsInteger - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsInteger"

logical fmcb :: IsInteger ( )
{

  return( fmcbityp == T_INT             ||
          fmcbityp == T_UINT            ||
          fmcbityp == T_DATE            ||
          fmcbityp == T_TIME            ||
          fmcbityp == T_UINT            ||
          fmcbityp == T_BIT               );


}

/******************************************************************************/
/**
\brief  IsNoField - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNoField"

logical fmcb :: IsNoField ( )
{

  return ( !this || fmcbdim == AUTO );


}

/******************************************************************************/
/**
\brief  IsPD - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPD"

logical fmcb :: IsPD ( )
{
  logical                 cond = NO;
BEGINSEQ
  if ( fmcbbyte == 1 )                               LEAVESEQ
    
  switch ( fmcbrlev )
  {
    case R_REFR    : break;
    case R_GENERIC :
    case R_INTERN  :
    case R_DIRECT  : switch ( fmcbityp )
                     {
                       case T_CHAR   :
                       case T_CCHAR  :
                       case T_MEMO   :                         // fuer dereferenzierte
                       case T_BLOB   :                         // fuer dereferenzierte
                       case T_STRING : 
                       case T_REAL   : 
                       case T_LO     : break;
                       
                       case T_GUID   :
                       case T_DATE   :  
                       case T_TIME   : 
                       case T_INT    :
                       case T_UINT   : 
                       case T_BIT    : cond = YES;
                                       break;
                       default       : if ( fmcbsmcb )
                                       {
                                         if ( fmcbsmcb->smcbstyp == ST_CODE )
                                           cond = YES;
                                         else 
                                           cond = fmcbsmcb->IsPD();
                                       }
                     }
                     break;
  }
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsSynonym - 


\return cond - Return value

\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSynonym"

logical fmcb :: IsSynonym (char *names )
{
  char                    string[ID_SIZE+1];
  logical                 cond = YES;
BEGINSEQ
  if ( !fmcbsyns )                                   ERROR
  if ( !names || !*names )                           ERROR
    
  gvtxbts(string,names,sizeof(string)-1);
    
  DLL(char)     cursor(*fmcbsyns);
  cursor.GoTop();
  while ( names = cursor.GetNext() )
    if ( !strcmp(string,names) )                     LEAVESEQ
      
  ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsText - Is field a text field
        The  function  returns,  whether  the  field  contains text data or not.
        Numeric,  logical  or  structured  fields  are  not  considered  as text
        fields.  Enumerated  fields  are  considered  as  text fields as well as
        string or charachter fields.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsText"

logical fmcb :: IsText ( )
{
  logical                 cond = NO;
  switch ( fmcbityp )
  {
    case T_CHAR    :
    case T_CCHAR   :
    case T_STRING  :
    case T_MEMO    : cond = YES;
                     break;   
    default        : if ( fmcbsmcb && fmcbsmcb->smcbstyp == ST_CODE )
                       cond = YES;
                     else
                       cond = NO;
                     break;
  }  

  return(cond);
}

/******************************************************************************/
/**
\brief  RemoveSynonyms - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveSynonyms"

void fmcb :: RemoveSynonyms ( )
{
  char                   *string;

BEGINSEQ
  if ( !fmcbsyns )                                   LEAVESEQ
    
  while ( string = fmcbsyns->RemoveTail() )
    free(string);

  delete fmcbsyns;
  fmcbsyns = NULL;

ENDSEQ

}

/******************************************************************************/
/**
\brief  SetInternalType - 


\return ityp - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInternalType"

int16 fmcb :: SetInternalType ( )
{

  return( fmcbityp = GetInternalType(fmcbtype) );


}

/******************************************************************************/
/**
\brief  SetNoField - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetNoField"

logical fmcb :: SetNoField ( )
{
  logical                 term = NO;
  gvtxstb(fmcbtype,"VOID",ID_SIZE);
  SetInternalType();
  fmcbrlev = R_DIRECT;
  fmcbbytc();

  return(term);
}

/******************************************************************************/
/**
\brief  fmcb - 


-------------------------------------------------------------------------------
\brief  FMCB_ - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcb"

     fmcb :: fmcb ( )
{

  fmcbini();
  SOSRESET


}

/******************************************************************************/
/**
\brief  FMCB_I - 


\param  fldnames - Field name
\param  fldtypes - 
\param  nsid - 
\param  rlev - 
\param  fsize - 
\param  prec - 
\param  dim - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcb"

     fmcb :: fmcb (char *fldnames, char *fldtypes, int32 nsid, int16 rlev, uint32 fsize, int16 prec, uint32 dim )
{

  fmcbini();

  gvtxstb(fmcbname,fldnames,sizeof(fmcbname));
  gvtxstb(fmcbtype,fldtypes,sizeof(fmcbtype));

  fmcbsize = fsize;
  fmcbdim  = dim;
  fmcbprec = prec;
  fmcbrlev = rlev;
  fmcbnsid = nsid;


}

/******************************************************************************/
/**
\brief  FMCB_S - 


\param  fldnames - Field name
\param  fldtypes - 
\param  nsid - 
\param  rlev - 
\param  fsize - 
\param  prec - 
\param  dim - 
\param  posn - Position relative 0
\param  byte - 
\param  ityp - 
\param  unicode - 
\param  var - 
\param  trans - 
\param  opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcb"

     fmcb :: fmcb (char *fldnames, char *fldtypes, int32 nsid, int16 rlev, uint32 fsize, int16 prec, uint32 dim, int32 posn, uint32 byte, int16 ityp, logical unicode, logical var, char trans, logical opt )
                     :   fmcbnsid(nsid),
  fmcbsize(fsize), fmcbdim(dim),
  fmcbprec(prec), fmcbrlev(rlev),
  fmcbposn(posn), fmcbbyte(byte),
  fmcbityp(ityp), fmcbsmcb(NULL),
  fmcberr(0), fmcbold(NO),
  fmcbbstr(NO),  fmcbunicode(unicode), fmcbvar(var),
  fmcbtrans(trans),  fmcbopt(opt), fmcbempty(YES),
  fmcbcnst(NO),  fmcbvirt(NO), fmcbstat(NO), 
  fmcbinit(NO),  fmcbic(NO),   fmcbdesc(NO), 
  fmcballoc_opt(NO), fmcbsensi(NO), fmcbsyns(NULL),
  fmcbgentype(NO)
{

  gvtxstb(fmcbname,fldnames,sizeof(fmcbname));
  gvtxstb(fmcbtype,fldtypes,sizeof(fmcbtype));


}

/******************************************************************************/
/**
\brief  i3 - 


\param  smcbptr - Structure definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcb"

     fmcb :: fmcb (smcb *smcbptr )
{
  int8      max_aligned = 1;
  fmcbini();

  memcpy(fmcbname,smcbptr->smcbname,sizeof(fmcbname));
  memcpy(fmcbtype,smcbptr->smcbname,sizeof(fmcbtype));

  fmcbdim  = 1;
  fmcbesu(smcbptr,0,0,max_aligned);


}

/******************************************************************************/
/**
\brief  i4 - 


\param  fmcbref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcb"

     fmcb :: fmcb (fmcb &fmcbref )
{

  fmcbini();
  *this = fmcbref;

}

/******************************************************************************/
/**
\brief  fmcbbase - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbbase"

logical fmcb :: fmcbbase ( )
{

  return (fmcbityp < 0 && fmcbityp != T_DATETIME && fmcbityp > ERIC ? YES : NO);



}

/******************************************************************************/
/**
\brief  fmcbbytc - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbbytc"

void fmcb :: fmcbbytc ( )
{
  fmcbbyte = 0;
  fmcbunicode  = NO;
  fmcbvar  = NO;
  if ( !fmcbityp && !fmcbsmcb )
    SetInternalType();
    
  switch ( fmcbrlev )
  {
    case R_REFR    : fmcbbyte = sizeof(void *);
                     break;
    case R_GENERIC :
    case R_INTERN  :
    case R_DIRECT  : switch ( fmcbityp )
                     {
                       case T_LO     : fmcbsize = fmcbbyte = 1;
                                       break;
                       case T_BIT    : fmcbbyte = (fmcbsize+7)/8;
                                       break;
                       case T_BLOB   :                        // fuer dereferenzierte
                       case T_CHAR   :
                       case T_CCHAR  : fmcbbyte = fmcbsize;
                                       break;
                       case T_MEMO   :                         // fuer dereferenzierte
                       case T_STRING : fmcbbyte = fmcbsize+1;
                                       break;
                       case T_INT    :
                       case T_UINT   : fmcbbyte = ( fmcbsize > 10 ? 8 :
                                                    fmcbsize >  4 ? 4 : 
                                                    fmcbsize >  2 ? 2 : 1);
                                       break;
                       case T_REAL   : fmcbbyte = ( fmcbsize > 7 ? 8 : 4 );
                                       break;
                       case T_GUID   : fmcbbyte = sizeof(guid);
                                       break;
                       case T_DATE   :  
                       case T_TIME   : if ( !fmcbsize )
                                         fmcbsize = 8;
                                       fmcbbyte = 4;
                                       break;
                       case T_VOID   : fmcbbyte = fmcbsize = 0; 
                                       fmcbdim = -1;            // "NoData" - fmcb
                                       break;
                       default       : if ( fmcbsmcb )
                                       {
                                         fmcbsize = fmcbbyte = fmcbsmcb->GetInstLength(fmcbbstr);
                                         if ( fmcbsmcb->smcbstyp == ST_CODE )
                                           fmcbbyte = sizeof(int32);
                                       }
                     }
                     break;
    default	   : fmcbbyte = sizeof(void *);
  }

  if ( !fmcbsize )
    fmcbvar = YES;


}

/******************************************************************************/
/**
\brief  fmcbchk - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbchk"

logical fmcb :: fmcbchk ( )
{
  logical   term = NO;

BEGINSEQ
  switch ( fmcbityp )
  {
    case T_UINT    :
    case T_INT	   : if ( !fmcbsize || fmcbsize > 10 )	   SOSERR(38)
       		     if ( abs(fmcbprec) >= fmcbsize )	   SOSERR(38)
		     if ( fmcbrlev < R_INTERN )		   SOSERR(36)
                     break;
    case T_REAL	   : if ( !fmcbsize || fmcbsize > 64 )	   SOSERR(38)
		     if ( fmcbrlev < R_INTERN )		   SOSERR(36)
                     break;
    case T_LO      : 
    case T_CHAR    :
    case T_BIT     :
    case T_CCHAR   :
    case T_STRING  :
                     if ( !fmcbsize )			   SOSERR(38)
		     if ( fmcbrlev < R_INTERN )		   SOSERR(36)
                     break;
    case T_VOID    : if ( fmcbrlev < R_INTERN )		   SOSERR(36)
                     break;
    case T_MEMO    : if ( fmcbrlev != R_REFR )		   SOSERR(36)
		     if ( !fmcbsize ) 			   SOSERR(38)
		     if ( fmcbdim != 1 )		   SOSERR(39)
                     break;   
    default        : if ( fmcbsmcb && fmcbsmcb->smcbstyp == ST_CODE )
                     { 
                       if ( !fmcbsize )			   SOSERR(38)
		       if ( fmcbrlev < R_INTERN )	   SOSERR(36)
                     }
                     break;
  }  

RECOVER

  term = YES;

ENDSEQ

  return(term);

}

/******************************************************************************/
/**
\brief  fmcbcmp - 


\return term - Success

\param  fmcbptr - Field definition block
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbcmp"

logical fmcb :: fmcbcmp (fmcb *fmcbptr )
{

  return (  memcmp(fmcbtype,fmcbptr->fmcbtype,sizeof(fmcbtype))	||
            fmcbsize != fmcbptr->fmcbsize      ||
            fmcbdim  != fmcbptr->fmcbdim       ||
            fmcbprec != fmcbptr->fmcbprec      ||
            fmcbrlev != fmcbptr->fmcbrlev            );


}

/******************************************************************************/
/**
\brief  fmcbesu - 


\return term - Success

\param  typsmcb - 
\param  fldposn - 
\param  allign - 
\param  max_aligned - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbesu"

logical fmcb :: fmcbesu (smcb *typsmcb, int32 fldposn, int16 allign, int8 &max_aligned )
{

  if ( typsmcb )
  {
    fmcbityp = typsmcb->smcbityp;
    if ( !fmcbnsid && typsmcb->smcbnsid > 0 )
      fmcbnsid = typsmcb->smcbnsid;

    switch ( typsmcb->smcbstyp )
    {
      case ST_BASE : if ( fmcbityp == T_MEMO || fmcbityp == T_BLOB )
                       fmcbsmcb = typsmcb;
                     else
                       fmcbsmcb = NULL;      
                     break;     
      case ST_SYS  :
      case ST_KEY  :
      case ST_USER : 
      case ST_CODE : 
      default      : fmcbsmcb = typsmcb;
    }  
  }
  
  fmcbbytc();
  if ( fldposn >= 0 )
    fmcbposn = GetAllignedPosition(fldposn,allign,max_aligned);
  if ( fmcbdim > 1 && (fmcbrlev == R_DIRECT || fmcbrlev == R_INTERN) )
    fmcbbyte *= fmcbdim;
  return ( typsmcb ? NO : YES );

}

/******************************************************************************/
/**
\brief  fmcbicmp - 


\return cmpval - Comparision result

\param  srcefmcb - 
\param  fldtarg - 
\param  fldsrce - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbicmp"

int fmcb :: fmcbicmp (fmcb *srcefmcb, char *fldtarg, char *fldsrce )
{
  int       cmpval      = UNDEF;
  char      skey[256];
  char      tkey[256];
  int32     len = fmcbbyte / (MAX(fmcbdim,1));
  int8      max_aligned = 1;
  static    char  smemo[8001];  // Memoschlüssel dürfen nicht größer als 8000 sein!
  static    char  tmemo[8001];
BEGINSEQ
  SOSRESET

  if ( !fmcbityp && fmcbsmcb && fmcbsmcb->smcbityp )
    fmcbesu(fmcbsmcb,fmcbposn,1,max_aligned);
    
  if ( !srcefmcb->fmcbityp && srcefmcb->fmcbsmcb && srcefmcb->fmcbsmcb->smcbityp )
    srcefmcb->fmcbesu(srcefmcb->fmcbsmcb,srcefmcb->fmcbposn,1,max_aligned);
  
  if ( (!fmcbsmcb || fmcbsmcb->smcbstyp != ST_CODE) ||
       (!srcefmcb->fmcbsmcb || srcefmcb->fmcbsmcb->smcbstyp != ST_CODE) )
    if (  fmcbityp != srcefmcb->fmcbityp ||
          fmcbbyte != srcefmcb->fmcbbyte ||
        ( !fmcbbase() && ( !fmcbsmcb || !srcefmcb->fmcbsmcb )) )  ERROR

  if ( srcefmcb->fmcbic )
  {
    fldsrce = (char *)memcpy(skey,fldsrce,srcefmcb->fmcbsize);
    skey[srcefmcb->fmcbsize] = 0;
    gvtsupr(skey);
  }

  if ( fmcbic )
  {
    fldtarg = (char *)memcpy(tkey,fldtarg,fmcbsize);
    tkey[fmcbsize] = 0;
    gvtsupr(tkey);
  }

  if ( fmcbrlev > 0 || fmcbrlev == R_REFR ) // Pointer 
  {
    cmpval = memcmp(fldtarg,fldsrce,sizeof(void *));   LEAVESEQ
  }
  
  switch ( fmcbityp )
  {
    case T_DATE   :
    case T_TIME   :
    case T_INT    : switch ( len )
                    { 
                      case 1 : cmpval = ( (*fldtarg > *fldsrce) -
                                          (*fldtarg < *fldsrce) );
                               break;     
                      case 2 : cmpval = ( (*(int16 *)fldtarg > *(int16 *)fldsrce) -
                                          (*(int16 *)fldtarg < *(int16 *)fldsrce) );
                               break;     
                      case 4 : cmpval = ( (*(int32 *)fldtarg > *(int32 *)fldsrce) -
			                  (*(int32 *)fldtarg < *(int32 *)fldsrce) );
                               break;
                      case 8 : cmpval = ( (*(int64 *)fldtarg > *(int64 *)fldsrce) -
			                  (*(int64 *)fldtarg < *(int64 *)fldsrce) );
                               break;
                      default : ;
                    }           
                    break;
    case T_UINT   : switch ( len )
                    { 
                      case 1 : cmpval = ( (*(uint8 *)fldtarg > *(uint8 *)fldsrce) -
                                          (*(uint8 *)fldtarg < *(uint8 *)fldsrce) );
                               break;     
                      case 2 : cmpval = ( (*(uint16 *)fldtarg > *(uint16 *)fldsrce) -
                                          (*(uint16 *)fldtarg < *(uint16 *)fldsrce) );
                               break;     
                      case 4 : cmpval = ( (*(uint32 *)fldtarg > *(uint32 *)fldsrce) -
			                  (*(uint32 *)fldtarg < *(uint32 *)fldsrce) );
                               break;
                      case 8 : cmpval = ( (*(uint64 *)fldtarg > *(uint64 *)fldsrce) -
			                  (*(uint64 *)fldtarg < *(uint64 *)fldsrce) );
                               break;
                      default : ;
                    }           
                    break;
    case T_MEMO   : fmcbirtd(this,smemo,fldsrce,NO);
                    fmcbirtd(this,tmemo,fldtarg,NO);
                    cmpval = strncmp(tmemo,smemo,fmcbbyte);
                    break;
    case T_REAL   : switch ( len )
                    { 
                      case 4 : cmpval = ( (*(float *)fldtarg > *(float *)fldsrce) -
                                          (*(float *)fldtarg < *(float *)fldsrce) );
                               break;     
                      case 8 : 
//                               {
//                                 double  val = (*(double *)fldtarg - *(double *)fldsrce);
//                                 cmpval = val == 0 ? 0 : val > 0 ? 1 : -1;
//                               }
                               cmpval = ( (*(double *)fldtarg > *(double *)fldsrce) -
                                          (*(double *)fldtarg < *(double *)fldsrce) );
                               break;     
                      default : ;
                    }           
                    break;
    case T_LO     :
    case T_CHAR   :
    case T_CCHAR  :
    case T_GUID   : cmpval = memcmp(fldtarg,fldsrce,len);
                    break;
    case T_STRING : cmpval = strncmp(fldtarg,fldsrce,len);
                    break;
    case T_BIT    : cmpval = 0;  // no comparision of bit strings
                    break;
    default       : if ( !fmcbsmcb || !srcefmcb->fmcbsmcb )        SOSERR(99)
                    if ( fmcbsmcb->smcbstyp == ST_CODE )
#ifdef __unix__  // unter unix gibt es noch keine mvld für gen. Attribute
  	              cmpval = ( (*(int32 *)fldtarg > *(int32 *)fldsrce) -
			         (*(int32 *)fldtarg < *(int32 *)fldsrce) );
#else            // für gen. Attribute werden in den mvld's die externen Werte verglichen
   	              cmpval = ( (*(int16 *)fldtarg > *(int16 *)fldsrce) -
			         (*(int16 *)fldtarg < *(int16 *)fldsrce) );
#endif
                    if ( fmcbsmcb->smcbstyp == ST_USER ||
                         fmcbsmcb->smcbstyp == ST_SYS  ||
                         fmcbsmcb->smcbstyp == ST_KEY     )
                      cmpval = fmcbsmcb->smcbfmcl->fmclicmp(srcefmcb->fmcbsmcb->smcbfmcl,fldtarg,fldsrce);
  }
RECOVER

ENDSEQ
  if ( cmpval )
    cmpval = cmpval < 0 ? -1 : 1;
  return( fmcbdesc ? -cmpval : cmpval);
}

/******************************************************************************/
/**
\brief  fmcbicpy - 


\return term - Success

\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbicpy"

logical fmcb :: fmcbicpy (fmcb *srcefmcb, char *targfld, char *srcefld )
{
  ushort  i;
  ushort  count;
  ushort  slen;
  ushort  tlen;
  ushort  len;

  if ( fmcbrlev == R_DIRECT ) 
  {  
    count = MIN(fmcbdim,srcefmcb->fmcbdim);
    tlen  = fmcbbyte/fmcbdim;
    slen  = srcefmcb->fmcbbyte/srcefmcb->fmcbdim;
    len   = MIN(slen,tlen);

    for (i=0; i < count; i++, srcefld+=slen, targfld+=tlen )
      if ( !srcefmcb->fmcbsmcb || !fmcbsmcb )
      {
        if ( len < tlen )
          fmcbiini(targfld);
        memcpy(targfld,srcefld,len);
        if ( fmcbityp == T_STRING )
          gvtxbts(targfld,targfld,tlen-1);
      }    
      else
        switch ( fmcbsmcb->smcbstyp )
        {
          case ST_CODE : memcpy(targfld,srcefld,len);
                         break;
          case ST_USER :
          case ST_SYS  :
          case ST_KEY  : fmcbsmcb->smcbfmcl->fmclicpy(srcefmcb->fmcbsmcb->smcbfmcl,
                                                      targfld,srcefld);
                         break;
          default      :;
        }
  }
  return(NO);

}

/******************************************************************************/
/**
\brief  fmcbicvt - 


\return term - Success

\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
\param  replace - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbicvt"

logical fmcb :: fmcbicvt (fmcb *srcefmcb, char *targfld, char *srcefld, int16 replace, int16 copy_type )
{
  logical   term = NO;

//  if ( memcmp(fmcbtype,"SDB_Structure ",14) )    
    switch ( (fmcbrlev == R_REFR) + 2*(srcefmcb->fmcbrlev == R_REFR) )
    {
      case 0 : term = fmcbidtd(srcefmcb,targfld,srcefld,replace,copy_type);
               break;
      case 1 : term = fmcbidtr(srcefmcb,targfld,srcefld,replace,copy_type); 
               break;
      case 2 : term = fmcbirtd(srcefmcb,targfld,srcefld,replace,copy_type); 
               break;
      case 3 : term = fmcbirtr(srcefmcb,targfld,srcefld,replace,copy_type); 
               break;
    }
  return(term);

}

/******************************************************************************/
/**
\brief  fmcbidtd - 


\return term - Success

\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
\param  replace - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbidtd"

logical fmcb :: fmcbidtd (fmcb *srcefmcb, char *targfld, char *srcefld, int16 replace, int16 copy_type )
{
  logical   term  = NO;
  short     tdim  = fmcbrlev == R_GENERIC ? 1 : fmcbdim;
  short     sdim  = srcefmcb->fmcbrlev == R_GENERIC ? 1 : srcefmcb->fmcbdim;
  short     dim   = MIN(tdim,sdim);
  ushort    tlen  = tdim ? fmcbbyte/tdim : 0;
  ushort    slen  = sdim ? srcefmcb->fmcbbyte/sdim : 0;
  short int i;

BEGINSEQ
  if ( fmcbrlev > 0 || srcefmcb->fmcbrlev > 0 )      LEAVESEQ
    
  if ( fmcbstpg() == ST_BASE && fmcbityp == srcefmcb->fmcbityp &&
       fmcbityp != T_MEMO && fmcbityp != T_BLOB                   )
  {
    term = fmcbicpy(srcefmcb,targfld,srcefld);
    LEAVESEQ
  }

//  fmcbiini(targfld);

  if ( replace || !fmcbold )
    for (i=0; i < dim; i++, srcefld+=slen, targfld+=tlen )
      if ( cvb(srcefmcb,this,srcefld,targfld).cvbconv(replace,NO,copy_type) )
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  fmcbidtr - 


\return term - Success

\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
\param  replace - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbidtr"

logical fmcb :: fmcbidtr (fmcb *srcefmcb, char *targfld, char *srcefld, int16 replace, int16 copy_type )
{
  logical   term = NO;

BEGINSEQ
  if ( srcefmcb->fmcbrlev > 0 )                        LEAVESEQ
  
  if ( replace > AUTO && fmcbsmcb )
    term = fmcbsmcb->smcbacc->DirToRef(this,srcefmcb,targfld,srcefld,replace,copy_type);
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  fmcbiini - 


\return term - Success

\param  intfld - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbiini"

logical fmcb :: fmcbiini (char *intfld )
{
  ushort     i    = 0;
  short      dim;
  logical    term = NO;

BEGINSEQ
  if ( fmcbgentype || 
       (fmcbrlev != R_DIRECT && fmcbrlev != R_GENERIC && fmcbrlev != R_INTERN) )
  {
    if ( fmcbrlev != R_REFR )
      memset(intfld,0,fmcbbyte);                         
    LEAVESEQ
  }  

  switch ( fmcbityp )
  {
    case T_BIT    :
    case T_DATE   :
    case T_INT    :
    case T_UINT   :
    case T_REAL   :
    case T_LO     :
    case T_STRING : 
    case -99      : memset(intfld,0,fmcbbyte);       LEAVESEQ  // internal structures
    case T_CHAR   : memset(intfld,' ',fmcbbyte);     LEAVESEQ
    case T_CCHAR  : memset(intfld,' ',fmcbbyte);
                    gvtxbtc(intfld,fmcbbyte,intfld,fmcbbyte);
                                                     LEAVESEQ
    case T_TIME   : ((dbtm *)intfld)->Clear();       LEAVESEQ
    case T_DATETIME:((dttm *)intfld)->Clear();       LEAVESEQ
    case T_GUID   : memset(intfld,0,fmcbbyte);       LEAVESEQ
  }
  
  dim = fmcbrlev == R_GENERIC ? 1 : fmcbdim;
  for (i=0; i < dim; i++, intfld+=fmcbbyte/dim )
  {
    if ( !fmcbsmcb )                                 SOSERR(99)
    if ( fmcbsmcb->smcbstyp == ST_CODE || fmcbgentype )
      memset(intfld,0,fmcbbyte);
    else
      fmcbsmcb->smcbfmcl->fmcliini(intfld);
  }    

RECOVER
  term = YES;

ENDSEQ

  return(term);

}

/******************************************************************************/
/**
\brief  fmcbini - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbini"

void fmcb :: fmcbini ( )
{

  memset(this,0,sizeof(fmcb));


}

/******************************************************************************/
/**
\brief  fmcbirtd - 


\return term - Success

\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
\param  replace - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbirtd"

logical fmcb :: fmcbirtd (fmcb *srcefmcb, char *targfld, char *srcefld, int16 replace, int16 copy_type )
{
  logical   term = NO;

BEGINSEQ
  fmcbiini(targfld);
  if ( fmcbrlev > 0 )                                 LEAVESEQ

  if ( replace > AUTO && srcefmcb->fmcbsmcb )
    term = srcefmcb->fmcbsmcb->smcbacc->RefToDir(this,srcefmcb,targfld,srcefld,replace,copy_type);
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  fmcbirtr - 


\return term - Success

\param  srcefmcb - 
\param  targfld - 
\param  srcefld - 
\param  replace - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbirtr"

logical fmcb :: fmcbirtr (fmcb *srcefmcb, char *targfld, char *srcefld, int16 replace, int16 copy_type )
{
  logical   term = NO;

  if ( srcefmcb->fmcbsmcb )
    if ( replace > AUTO )
      term = srcefmcb->fmcbsmcb->smcbacc->RefToRef(this,srcefmcb,targfld,srcefld,replace,copy_type);
//    else  
//      memset(targfld,0,4);
  return(term);

}

/******************************************************************************/
/**
\brief  fmcbkfil - 


\return term - Success

\param  fmcbptr - Field definition block
\param  fldposn - 
\param  allign - 
\param  max_aligned - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbkfil"

logical fmcb :: fmcbkfil (fmcb *fmcbptr, int32 fldposn, int16 allign, int8 &max_aligned )
{
  logical   term = NO;

BEGINSEQ
  memcpy(fmcbname,fmcbptr->fmcbname,ID_SIZE);
  memcpy(fmcbtype,fmcbptr->fmcbtype,ID_SIZE);

  fmcbdim  = 1;
  fmcbrlev = fmcbityp != T_MEMO && fmcbityp != T_BLOB ? R_DIRECT : R_REFR;
  fmcbsize = fmcbptr->fmcbsize;
  fmcbprec = fmcbptr->fmcbprec;
  fmcbityp = fmcbptr->fmcbityp;
  fmcbsmcb = fmcbityp != T_MEMO ? fmcbptr->fmcbsmcb : new smcb(fmcbsmcb);
  fmcbbyte = 0;
  fmcbposn = 0;
  fmcberr  = 0;

  if ( fmcbic && fmcbityp != T_MEMO && fmcbityp != T_BLOB &&
       fmcbityp != T_CHAR  && fmcbityp != T_STRING && fmcbityp != T_CCHAR )
    fmcbic = NO;

  if ( fmcbsmcb )
    switch ( fmcbsmcb->smcbstyp )
    {
      case ST_SYS :
      case ST_USER: if ( !(fmcbsmcb = fmcbsmcb->GetIdentKeySMCB()) )
                                                 SOSERR(99)
      default     : ;
    }

   fmcbesu(fmcbsmcb,fldposn,allign,max_aligned);

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  fmcbkgt - 


\return term - Success

\param  fldsrce - 
\param  fldkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbkgt"

logical fmcb :: fmcbkgt (char *fldsrce, char *fldkey )
{
  short int styp = !fmcbsmcb ? ST_BASE : fmcbsmcb->smcbstyp;
  logical   term = NO;
BEGINSEQ
  if ( fmcbrlev != R_DIRECT && fmcbrlev != R_INTERN ) LEAVESEQ

  switch ( styp )
  {
    case ST_BASE :
    case ST_CODE : if ( !fmcbdim )                   ERROR
                   if ( fmcbityp == T_MEMO )
                     fmcbirtd(this,fldkey,fldsrce,NO);
                   else 
                     memcpy(fldkey,fldsrce,fmcbbyte/fmcbdim);
                   break;
    case ST_KEY  : memcpy(fldkey,fldsrce,fmcbsmcb->GetLength());
                   break;
    case ST_SYS  :
    case ST_USER : fmcbsmcb->smcbidky->kcbkgt(fldsrce,fldkey);
                   break;
    default      :                                   ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  fmcbkpt - 


\return term - Success

\param  fldsrce - 
\param  fldkey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbkpt"

logical fmcb :: fmcbkpt (char *fldsrce, char *fldkey )
{
  short int styp = !fmcbsmcb ? ST_BASE : fmcbsmcb->smcbstyp;
  logical   term = NO;

BEGINSEQ
  if ( fmcbrlev != R_DIRECT )                        LEAVESEQ

  switch ( styp )
  {
    case ST_BASE :
    case ST_CODE : if ( fmcbityp == T_MEMO )
                     fmcbidtr(this,fldsrce,fldkey,NO);
                   else 
                     memcpy(fldsrce,fldkey,fmcbbyte);
                   break;
    case ST_KEY  : memcpy(fldsrce,fldkey,fmcbsmcb->GetLength());
                   break;
    case ST_SYS  :
    case ST_USER : fmcbsmcb->smcbidky->kcbkpt(fldsrce,fldkey);
                   break;
    default      :                                   ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  fmcbligt - 


\return lval - 

\param  fldsrce - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbligt"

int64 fmcb :: fmcbligt (char *fldsrce )
{
  int64    lival = 0;

BEGINSEQ
  if ( !fldsrce || !fmcbdim )                        ERROR
    
  switch ( fmcbbyte/fmcbdim )
  {
    case 1  : lival = *fldsrce;
              break;
    case 2  : lival = *(int16 *)fldsrce;
              break;
    case 4  : lival = *(int32 *)fldsrce;
              break;
    case 8  : lival = *(int64 *)fldsrce;
              break;
    default : ;        
  }

RECOVER

ENDSEQ
  return (lival);

}

/******************************************************************************/
/**
\brief  fmcblist - 



\param  fldtarg - 
\param  val64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcblist"

void fmcb :: fmcblist (char *fldtarg, int64 val64 )
{

BEGINSEQ
  if ( !fldtarg || !fmcbdim )                        ERROR
    
  switch ( fmcbbyte/fmcbdim )
  {
    case 1  : *fldtarg = (char)val64;
              break;
    case 2  : *(int16 *)fldtarg = (int16)val64;
              break;
    case 4  : *(int32 *)fldtarg = (int32)val64;
              break;
    case 8  : *(int64 *)fldtarg = val64;
              break;
    default : ;        
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  fmcblnu - 


\return len - 

\param  srcefmcb - 
\param  w_entry_area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcblnu"

uint16 fmcb :: fmcblnu (fmcb *srcefmcb, void *w_entry_area )
{
  int         size = 0;
  if ( this != srcefmcb && fmcbvar && (fmcbrlev == R_INTERN || fmcbrlev == R_DIRECT) )
    switch ( fmcbityp )
    {
      case T_CHAR    :
      case T_CCHAR   :
      case T_STRING  : if ( srcefmcb->fmcbityp == T_MEMO )
		         size = w_entry_area ? MAX(fmcbsize,(ushort)gvtutle0((char *)w_entry_area,srcefmcb->fmcbsize)) :
                                                   srcefmcb->fmcbsize;
                       else
                         size = (ushort)srcefmcb->GetStringLength();                       
                       break;
      default        : ;
    }

  if ( size > fmcbsize )
  {
    fmcbsize = size;
    fmcbbytc();
    fmcbvar = YES;
  }

  return(size);

}

/******************************************************************************/
/**
\brief  fmcblugt - 


\return luval - 

\param  fldsrce - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcblugt"

uint32 fmcb :: fmcblugt (char *fldsrce )
{
  uint32     luval = 0;

BEGINSEQ
  if ( !fldsrce || !fmcbdim )                        ERROR
  
  switch ( fmcbbyte/fmcbdim )
  {
    case 1  : luval = *(uint8 *)fldsrce;
              break;
    case 2  : luval = *(uint16 *)fldsrce;
              break;
    case 4  : luval = *(uint32 *)fldsrce;
              break;
    case 8  : luval = (uint32)*(uint64 *)fldsrce;
              break;
    default : ;        
  }
RECOVER

ENDSEQ
  return(luval);

}

/******************************************************************************/
/**
\brief  fmcbrgt - 


\return rval - 

\param  fldsrce - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbrgt"

double fmcb :: fmcbrgt (char *fldsrce )
{

  return(fmcbbyte == 8 ? *(double *)fldsrce : (double)*(float *)fldsrce);


}

/******************************************************************************/
/**
\brief  fmcbstpg - 


\return styp - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcbstpg"

int16 fmcb :: fmcbstpg ( )
{

  return ( !fmcbsmcb ? UNDEF : fmcbsmcb->smcbstyp );


}

/******************************************************************************/
/**
\brief  operator= - 


\return fmcbref - 

\param  fmcbref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

fmcb &fmcb :: operator= (fmcb &fmcbref )
{
  logical       opt       = fmcbopt;

  RemoveSynonyms();
  
  memcpy(this,&fmcbref,sizeof(fmcb));
  fmcbopt = opt;
  
  if ( fmcbsyns )
  {
    fmcbsyns = NULL;
    CopySynonyms(fmcbref.fmcbsyns);
  }

  return(*this);
}

/******************************************************************************/
/**
\brief  set_fmcbgentype - 



\param  generic_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_fmcbgentype"

void fmcb :: set_fmcbgentype (logical generic_opt )
{

  fmcbgentype = generic_opt;

}

/******************************************************************************/
/**
\brief  ~fmcb - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~fmcb"

     fmcb :: ~fmcb ( )
{
 

  RemoveSynonyms();

}


