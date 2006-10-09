/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|12:36:19,39}|(REF)
\class    smcb

\brief    Structure control block
          A  structure  control  block  describes  a  complex  data  type  or an
          enumeration.  Fields  of  a  complex  data type are defined as list of
          field  control  blocks  (fmcb).  Enumerators for an enumeration can be
          accessed by the access object (smcbacc).
          The following status information are set in smcbsts:
          stserr   - stucture definition is not correct
          stsold    - old structure version (mainly for database structures in a
          dictionary) or
          __AUTOIDENT-index (for key-SMCB)
          stsnof   - identity key (for key SMCB, only)
          - otherwise: structure definition is a DBStructDef 
          stsmod - (old: key value has changed (key SMCB, only))
          stssav   - key contains multi-dimensional component (key SMCB, only)
          (old: key value has been checked for updates (key SMCB, only))
          stswpt   - key value cannot be updated (key SMCB, only)
          stslck     -  key  contains  IDENTITY  as component of a VIEW_KEY (key
          SMCB, only)
          stsusr1  - smcb has generic key component
          stsusr2  - generic keys need not to be maintained
          stsdel    - Structure inherits directly from __OBJECT
          Œ

\date     $Date: 2006/03/30 19:57:27,07 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "smcb"

#include  <pdefault.h>
#include  <csmcbdef.h>
#include  <csmcbmac.h>
#ifndef   DLL_kcb_HPP
#define   DLL_kcb_HPP
#include  <skcb.hpp>
#include  <sDLL.h>
#endif
class     DBStructDef;
#include  <sacc.hpp>
#include  <scvb.hpp>
#include  <sfld.hpp>
#include  <sfmcb.hpp>
#include  <sfmcl.hpp>
#include  <skcb.hpp>
#include  <ssmcb.hpp>
#include  <ssmcb.hpp>


/******************************************************************************/
/**
\brief  AddKCB


\param  kcbptr - Key definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddKCB"

void smcb :: AddKCB (kcb *kcbptr )
{

  smcberr = 0;
  smcbskey->AddTail(kcbptr);
  if ( kcbptr->get_kcbgfmcb() )
    smcbsts.stssusr1();


}

/******************************************************************************/
/**
\brief  CheckPD

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckPD"

logical smcb :: CheckPD ( )
{
  fmcb                   *fmcbptr;
  short int               indx = 0;
  logical                 cond = YES;
  while ( (fmcbptr = GetEntry(++indx)) && 
                        !(is_pd = fmcbptr->IsPD()) ) ;

  return(is_pd);
}

/******************************************************************************/
/**
\brief  CompareIdentKey

\return cmpval - Comparision result

\param  skey1 - Key value
\param  skey2 - Key value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareIdentKey"

int8 smcb :: CompareIdentKey (char *skey1, char *skey2 )
{
  char        cmpval = ERIC;
BEGINSEQ
  if ( !this || !smcbidky )                          ERROR

  cmpval = smcbidky->CompareKeys(skey1,skey2);
RECOVER
  cmpval = ERIC;
ENDSEQ
  return(cmpval);
}

/******************************************************************************/
/**
\brief  CompareSortKey

\return cmpval - Comparision result

\param  skey1 - Key value
\param  skey2 - Key value
\param  keyname - Key name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareSortKey"

int8 smcb :: CompareSortKey (char *skey1, char *skey2, char *keyname )
{
  kcb        *kcbptr;
  char        cmpval = ERIC;
BEGINSEQ
  if ( !this || !(kcbptr = GetKCB(keyname)) )          ERROR

  cmpval = kcbptr->CompareKeys(skey1,skey2);
RECOVER

ENDSEQ
  return(cmpval);
}

/******************************************************************************/
/**
\brief  ConvertFromNet - Convert net transfer format into structure format
        When  transferring  structured  instances  between  different computers,
        those  are  converted  in  a  common  net transfer format. This function
        converts  the instance  from the  net transfer  format into the platform
        dependent internal format.


\param  netinst - Instance with net transfer format
\param  intinst - Internal instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertFromNet"

void smcb :: ConvertFromNet (char *netinst, char *intinst )
{
  fmcb          *fmcbptr;
  register int   indx = 0;
  while ( fmcbptr = smcbfmcl->GetEntry(++indx) )
    fmcbptr->ConvertDimFromNet(netinst+fmcbptr->fmcbposn,intinst+fmcbptr->fmcbposn,UNDEF);


}

/******************************************************************************/
/**
\brief  ConvertToNet - Convert to net transfer format
        When  transferring  structured  instances  between  different computers,
        those are converted in a common net transfer format.


\param  netinst - Instance with net transfer format
\param  intinst - Internal instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToNet"

void smcb :: ConvertToNet (char *netinst, char *intinst )
{
  fmcb          *fmcbptr;
  register int   indx = 0;
  while ( fmcbptr = smcbfmcl->GetEntry(++indx) )
    fmcbptr->ConvertDimToNet(netinst+fmcbptr->fmcbposn,intinst+fmcbptr->fmcbposn,UNDEF);



}

/******************************************************************************/
/**
\brief  ConvertToString

\return string - String value
-------------------------------------------------------------------------------
\brief  SMCBITS


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

char *smcb :: ConvertToString (char *instptr, char *string, char *str_sep, char *field_sep, char *block_sep, char *empty_str, int32 srlen, logical skip_trans )
{

  SeparatorDef    sep_def(str_sep,field_sep,block_sep,NULL,empty_str);
  
  return( ConvertToString(sep_def,instptr,string,srlen,skip_trans) );



}

/******************************************************************************/
/**
\brief  i01


\param  instptr - Structured instance
\param  string - String value
\param  srlen - Maximum string length
\param  skip_trans - Skip transient field
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToString"

char *smcb :: ConvertToString (char *instptr, char *string, int32 srlen, logical skip_trans )
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
\brief  i02


\param  sep_def - 
\param  instptr - Structured instance
\param  string - String value
\param  srlen - Maximum string length
\param  skip_trans - Skip transient field
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToString"

char *smcb :: ConvertToString (SeparatorDef &sep_def, char *instptr, char *string, int32 srlen, logical skip_trans )
{
  fmcb     *fmcbptr;
  int32     len    = srlen ? srlen : GetStringLength();
  int16     indx   = 0;
  int32     dim;
  int32     count = 0;
  int32     tlen;
  char     *field_inst;
  char     *retstr = string;
  logical   first  = YES;
BEGINSEQ
  if ( !string )                                     ERROR
  if ( !instptr )
  {
    *string = 0;
    LEAVESEQ    
  }
  memset(string,' ',(ushort)len);
  
  while ( len > 0 && (fmcbptr = GetEntry(++indx)) )
  {
    if ( ( fmcbptr->fmcbrlev == R_INTERN  ||
           fmcbptr->fmcbrlev == R_DIRECT  ||
           fmcbptr->fmcbrlev == R_GENERIC ||
           fmcbptr->fmcbityp == T_MEMO       ) &&
         ( !fmcbptr->fmcbtrans || !skip_trans )   )
    {
      dim = fmcbptr->fmcbdim > 0 ? fmcbptr->fmcbdim : 1;
      if ( len && dim > 1 && sep_def.block_start )
      {
        *string = sep_def.block_start;
        string++;
        len--;
      }
      
      count = 0;
      while ( len > 0 && count < dim )
      {
        field_inst = instptr+fmcbptr->fmcbposn;
        
        if ( !first && sep_def.field_stop && !sep_def.field_start )   
        {
          *string = sep_def.field_stop;
          string++;
          len--;
        }
        
        if ( len > 0 )
        {
          if ( !fmcbptr->ConvertToString(sep_def,field_inst,string,len,skip_trans) )
                                                     ERROR
          field_inst += fmcbptr->fmcbbyte;
          tlen = MIN((ushort)len,strlen(string));
          string += tlen;
          len    -= tlen;
        }  
        first = NO;
        count++;
      }
      if ( len && dim > 1 && sep_def.block_stop )
      {
        *string = sep_def.block_stop;
        string++;
        len--;
      }
      *string = 0;
    }
  }

RECOVER
  retstr = NULL;
ENDSEQ
  *string = 0;
  return(retstr);
}

/******************************************************************************/
/**
\brief  ConvertToStruct

\return instptr - Structured instance
-------------------------------------------------------------------------------
\brief  SMCBSTI


\param  string - String value
\param  instptr - Structured instance
\param  str_sep - String separator
\param  field_sep - Field separator
\param  block_sep - Block separator
\param  empty_str - String for empty values
\param  srlen - Maximum string length
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToStruct"

char *smcb :: ConvertToStruct (char *string, char *instptr, char *str_sep, char *field_sep, char *block_sep, char *empty_str, int32 srlen )
{
  fmcb     *staticfmcb = fmcb::GetStaticFMCB(T_STRING);
  fmcb      stringfmcb = *staticfmcb;
  fmcb     *fmcbptr;
  char     *end;
  int32     len        = srlen ? srlen : strlen(string);
  int32     olen       = len;
  int32     tlen;
  int16     indx       = 0;

BEGINSEQ
  Initialize(instptr);

  while ( len && (fmcbptr = GetEntry(++indx)) )
  {
    if ( fmcbptr->fmcbrlev == R_INTERN ||
         fmcbptr->fmcbrlev == R_DIRECT ||
         fmcbptr->fmcbrlev == R_GENERIC   )
    {
      end = NULL;
      if ( *string == *dfs::GetParenthesis() )
      {
        if ( end = gvtsfbp(string++,(int)len--) )
          tlen = end - string - 1;
      }
      else
//        if ( smcbfmcl->GetCount() > 1 )  22.3.2006
          if ( end = (char *)memchr(string,dfs::GetSeparator(),(ushort)len) )
            tlen = end - string;

      if ( !end )
      {
        end = string+len;
        tlen = len;
      }
      else
        if ( *end == dfs::GetSeparator() )
          end++;

      stringfmcb.fmcbbyte = (stringfmcb.fmcbsize = (ushort)tlen)+1;
      if ( cvb(&stringfmcb,fmcbptr,string,instptr+fmcbptr->fmcbposn).cvbconv(UNDEF,NO) )
                                                     ERROR
      len -= end - string;
      string = end;
    }
  }

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);

}

/******************************************************************************/
/**
\brief  i01


\param  string - String value
\param  instptr - Structured instance
\param  srlen - Maximum string length
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertToStruct"

char *smcb :: ConvertToStruct (char *string, char *instptr, int32 srlen )
{
  char      field_sep[3];
  char      block_sep[3];
  memset(field_sep,0,sizeof(field_sep));
  memset(block_sep,0,sizeof(block_sep));
  memcpy(block_sep,dfs::GetParenthesis(),2);
  *field_sep = dfs::GetSeparator();
  
  return(ConvertToStruct(string,instptr,NULL,field_sep,block_sep,NULL,srlen));

}

/******************************************************************************/
/**
\brief  CopyInstance

\return term - Success

\param  targinst - Structured instance
\param  srcesmcb - Source structure definitoin
\param  srceinst - Structured instance area
\param  replace - Replace option
\param  copy_type - Copy type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInstance"

logical smcb :: CopyInstance (char *targinst, smcb *srcesmcb, char *srceinst, int16 replace, int16 copy_type )
{
  fmcb          *srcefmcb;
  fmcb          *targfmcb;
  int32          offset;
  logical        base_struct = YES;
  char           fldnames[ID_SIZE+1];
  register int   indx = 0;
  logical        term = NO;

BEGINSEQ
  if ( !srceinst || ! targinst || !smcbfmcl || !srcesmcb->smcbfmcl )
                                                     ERROR
  smcbfmcl->stsrerr();

  while ( targfmcb = smcbfmcl->GetEntry(++indx) )
    if ( replace == -2 || memcmp(targfmcb->fmcbname,"__GUID ",7) )  // GUIDs werden bicht kopiert, wenn replace > -2!!
    {
      offset = 0;
      if ( srcefmcb = srcesmcb->SearchField(gvtxbts(fldnames,targfmcb->fmcbname,ID_SIZE),&offset) )
      {
        if ( targfmcb->fmcbicvt(srcefmcb,targinst+targfmcb->fmcbposn,
                                         srceinst+srcefmcb->fmcbposn+offset,replace,copy_type) )
          term = YES;
      }
      else 
        if ( targfmcb->fmcbbstr )
          term = targfmcb->fmcbsmcb->CopyInstance(targinst+targfmcb->fmcbposn,srcesmcb,srceinst,replace,copy_type);
    }

RECOVER
  term = YES;
ENDSEQ
  if ( term && smcbfmcl && SOSERROR )
    smcbfmcl->stsserr();
  return(term);

}

/******************************************************************************/
/**
\brief  CreateField

\return fldptr

\param  fldnames - Field name
\param  w_instptr - Structured instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateField"

fld *smcb :: CreateField (char *fldnames, char *w_instptr )
{
  fld      *fldptr = new fld();

BEGINSEQ
  fld  tempfld = GetField(fldnames,w_instptr);
  *fldptr = tempfld;
  if ( !fldptr->GetFMCB() )                           ERROR

RECOVER
  delete fldptr;
  fldptr = NULL;
ENDSEQ
  return(fldptr);

}

/******************************************************************************/
/**
\brief  ExtractIdentKey

\return idkey

\param  idkey_w - Ident key area
\param  instance - Structured instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractIdentKey"

char *smcb :: ExtractIdentKey (char *idkey_w, char *instance )
{

BEGINSEQ
  if ( !instance || !this || !smcbidky )               ERROR

  idkey_w = smcbidky->kcbkgt(instance,idkey_w);


RECOVER
  idkey_w = NULL;
ENDSEQ
  return(idkey_w);
}

/******************************************************************************/
/**
\brief  ExtractSortKey

\return skey - 

\param  skey_w - Sort key area
\param  instance - Structured instance
\param  keyname - Key name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExtractSortKey"

char *smcb :: ExtractSortKey (char *skey_w, char *instance, char *keyname )
{
  kcb        *kcbptr;
BEGINSEQ
  if ( !instance || !this || !(kcbptr = GetKCB(keyname)) ) 
                                                     ERROR
  if ( kcbptr->scbsmcb->smcbsts.stscnof() )          ERROR
  
  skey_w = kcbptr->kcbkgt(instance,skey_w);

RECOVER
  skey_w = NULL;
ENDSEQ
  return(skey_w);
}

/******************************************************************************/
/**
\brief  GetCharLength - Get length in character format
        The  function  returns  the  maximum  length  of the instance when being
        converted into the character format.

\return srlen - Maximum string length

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCharLength"

int32 smcb :: GetCharLength ( )
{
  fmcb     *fmcbptr;
  int16     indx     = 0;
  int32     chlen    = UNDEF;
  while ( fmcbptr = GetEntry(++indx) )
    if ( fmcbptr->fmcbrlev == R_INTERN  ||
         fmcbptr->fmcbrlev == R_DIRECT  ||
         fmcbptr->fmcbrlev == R_GENERIC ||
         fmcbptr->fmcbityp == T_MEMO       )
      chlen += fmcbptr->GetCharLength() 
               * (fmcbptr->fmcbdim > 0 ? fmcbptr->fmcbdim : 1);


  return(chlen);  

}

/******************************************************************************/
/**
\brief  GetEntry - Get number of elementary fields in instance
        The  function  returns  the  number  of  elementary (atomic) fields in a
        structure  instance. The function counts  fields recursively in imbedded
        structures.  References are counted as single fields. Arrays are counted
        with their dimension.

\return fmcbptr - Field definition block
-------------------------------------------------------------------------------
\brief  SMCBEG_I - Provide field definition by index
        The  function provides the field definition at the defined position. The
        first  field  definition  is  at  position 1. The function returns NULL,
        when the position exceeds the number of fields for the structure.

\param  indx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

fmcb *smcb :: GetEntry (int16 indx )
{


  return(smcbfmcl ? smcbfmcl->GetEntry(indx) : NULL);
}

/******************************************************************************/
/**
\brief  SMCBEG_N - Provide field definition by name
        The  function  provides  the  field  definition  for  the field with the
        passed  name. The function  returns NULL, when  no field with the passed
        name was found.

\param  fldnames - Field name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

fmcb *smcb :: GetEntry (char *fldnames )
{
  fmcb     *fmcbptr;

BEGINSEQ
  smcberr = 0;
  
  if ( !(fmcbptr = smcbfmcl->GetFMCB(fldnames,YES)) )    ERROR

RECOVER

ENDSEQ
  return(fmcbptr);

}

/******************************************************************************/
/**
\brief  GetEntryCount

\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntryCount"

int32 smcb :: GetEntryCount ( )
{


  return(smcbfmcl ? smcbfmcl->GetCount() : 0);
}

/******************************************************************************/
/**
\brief  GetField - Get field control block
        The  function returns a field control block  for the field with the name
        passed  in 'fldnames' with the field  definition and the field ares from
        the structure instance.

\return fldenty - 

\param  fldnames - Field name
\param  w_instptr - Structured instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetField"

fld smcb :: GetField (char *fldnames, char *w_instptr )
{

  return( fld(GetEntry(fldnames))(w_instptr) );


}

/******************************************************************************/
/**
\brief  GetIdentKeySMCB

\return smcbptr - Structure definition block

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetIdentKeySMCB"

smcb *smcb :: GetIdentKeySMCB ( )
{

  smcberr = 0;


  return(smcbidky ? smcbidky->scbsmcb : NULL);
}

/******************************************************************************/
/**
\brief  GetInstLength

\return inst_len - Instance size

\param  as_base
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstLength"

int32 smcb :: GetInstLength (logical as_base )
{
  int8    align;  
  int     unalligned;
  int32   inst_len = 0;
BEGINSEQ
  if ( !this )                                      ERROR
  
  align    = as_base ? MIN(defined_align,DEFAULT_PACK) : plattform_align;  
  inst_len = smcbtlen;

  if ( align < 2 )                                  LEAVESEQ
    
  if ( !(unalligned = smcbtlen%align) )             LEAVESEQ
  inst_len = inst_len - unalligned + align;

RECOVER

ENDSEQ
  return(inst_len);
}

/******************************************************************************/
/**
\brief  GetKCB

\return kcbptr - Key definition
-------------------------------------------------------------------------------
\brief  SMCBKG_K


\param  keynames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKCB"

kcb *smcb :: GetKCB (char *keynames )
{
  kcb      *kcbptr = NULL;  
  char      keyname[ID_SIZE];

BEGINSEQ
  if ( !this )                                        ERROR
  smcberr = 0;

  if ( !keynames || !*keynames )
    kcbptr = smcbidky;
  else
  {
    gvtxstb(keyname,keynames,ID_SIZE);

    smcbskey->GoTop();
    while ( kcbptr = smcbskey->GetNext() )
      if ( !memcmp(keyname,kcbptr->scbsmcb->smcbname,ID_SIZE) )             
        break;
  }
RECOVER

ENDSEQ
  return(kcbptr);

}

/******************************************************************************/
/**
\brief  SMCBKG_N


\param  keynum - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKCB"

kcb *smcb :: GetKCB (int16 keynum )
{
  DLL(kcb)  cursor(*smcbskey);
  kcb      *kcbptr = NULL;  

  smcberr = 0;

  cursor.GoTop();
  while ( kcbptr = cursor.GetNext() )
    if ( kcbptr->get_key_num() == keynum )             
      break;
  return(kcbptr);

}

/******************************************************************************/
/**
\brief  GetKeySMCB

\return smcbptr - Structure definition block

\param  keynames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeySMCB"

smcb *smcb :: GetKeySMCB (char *keynames )
{
  kcb      *kcbptr;

BEGINSEQ
  smcberr = 0;
  
  if ( !(kcbptr = GetKCB(keynames)) )                ERROR

RECOVER

ENDSEQ
  return ( kcbptr ? kcbptr->scbsmcb : NULL);

}

/******************************************************************************/
/**
\brief  GetLastEntry

\return fmcbptr - Field definition block

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastEntry"

fmcb *smcb :: GetLastEntry ( )
{

  return(smcbfmcl ? smcbfmcl->GetEntry(smcbfmcl->GetCount()) : NULL);


}

/******************************************************************************/
/**
\brief  GetLength - Get instance length
        The  function  returns  the  instance  length  calculated  from  field 
        definitions.

\return inst_len - Instance size

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLength"

int32 smcb :: GetLength ( )
{

  return(this ? smcbtlen : UNDEF);


}

/******************************************************************************/
/**
\brief  GetLocalSortKey

\return smcbptr - Structure definition block

\param  fldnames - Field name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLocalSortKey"

smcb *smcb :: GetLocalSortKey (char *fldnames )
{
  smcb     *smcbptr = NULL;

BEGINSEQ
  smcberr = 0;
  
  if ( !smcbacc )                                    ERROR
  if ( !(smcbptr = smcbacc->GetSortKeySMCB(fldnames)) )
                                                     ERROR

RECOVER

ENDSEQ
  return(smcbptr);

}

/******************************************************************************/
/**
\brief  GetMax

\return keynum - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMax"

int16 smcb :: GetMax ( )
{
  short int keynum = 0;
  kcb      *kcbptr; 

  smcberr = 0;

  smcbskey->GoTop();
  while ( kcbptr = smcbskey->GetNext() )
    keynum = MAX(kcbptr->scbsmcb->smcbityp,keynum );
  return(keynum);

}

/******************************************************************************/
/**
\brief  GetRecursiveFieldCount

\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetRecursiveFieldCount"

int32 smcb :: GetRecursiveFieldCount ( )
{
  int32          indx0 = 0;
  int32          count = 0;
  int32          temp_count;
  fmcb          *fmcbptr;
  while ( fmcbptr = GetEntry(++indx0) )
  {
    if ( fmcbptr->fmcbrlev == R_REFR )
      count++;
    else 
    {
      temp_count = 1;
      if ( fmcbptr->fmcbsmcb && fmcbptr->fmcbsmcb->GetEntryCount() > 0 )
        temp_count = fmcbptr->fmcbsmcb->GetRecursiveFieldCount();
      count += temp_count * MAX(fmcbptr->fmcbdim,1);
    }
  }

  return(smcbfmcl ? smcbfmcl->GetCount() : 0);
}

/******************************************************************************/
/**
\brief  GetStringLength - Get maximum string length for structure instances
        The  function  returns  the  maximum  length  of the instance when being
        converted into the standard string format.

\return srlen - Maximum string length

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringLength"

int32 smcb :: GetStringLength ( )
{
  fmcb     *fmcbptr;
  int16     indx     = 0;
  int32     stlen    = UNDEF;

  while ( fmcbptr = GetEntry(++indx) )
    if ( fmcbptr->fmcbrlev == R_INTERN ||
         fmcbptr->fmcbrlev == R_DIRECT ||
         fmcbptr->fmcbrlev == R_GENERIC   )
      stlen += (fmcbptr->GetStringLength() + 1);
  return(stlen + 1);  

}

/******************************************************************************/
/**
\brief  Initialize - Initialize structure instance
        The  function  initializes  the  passed instance area with type specific
        NULL-values.

\return term - Success

\param  instptr - Structured instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical smcb :: Initialize (char *instptr )
{

  if ( smcbtlen > 0 )
    memset(instptr,0,(uint16)smcbtlen);

  return(smcbfmcl->fmcliini(instptr));
}

/******************************************************************************/
/**
\brief  IsEmpty - Is instance empty
        The  function  checks,  whether  the  passed structure instance contains
        empty values for all fields in the structure.

\return cond - Return value

\param  instptr - Structured instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical smcb :: IsEmpty (char *instptr )
{
  fmcb                   *fmcbptr;
  short int               indx = 0;
  logical                 cond = YES;
  while ( (fmcbptr = GetEntry(++indx)) && 
          (cond = fmcbptr->IsEmpty(instptr+fmcbptr->fmcbposn)) ) ;

  return(cond);
}

/******************************************************************************/
/**
\brief  IsOdabaDescription

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOdabaDescription"

logical smcb :: IsOdabaDescription ( )
{

  return ( this && smcbsts.stscnof() ? YES : NO );


}

/******************************************************************************/
/**
\brief  IsPD - Is structure platform dependent
        The  function returns, whether the structure contains platform dependent
        values  as  'int'.  The  function  returns  YES,  when  the  structur is
        platform independent and no if not.

\return is_pd - Is platform dependent

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsPD"

logical smcb :: IsPD ( )
{

  if ( is_pd == AUTO )
    CheckPD();

  return ( is_pd );
}

/******************************************************************************/
/**
\brief  SearchField

\return fmcbptr - Field definition block

\param  fldpath - Field path
\param  offset - 
\param  w_kcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SearchField"

fmcb *smcb :: SearchField (char *fldpath, int32 *offset, kcb *w_kcbptr )
{

  return ( SearchPathField(fldpath,NO,offset,w_kcbptr) );



}

/******************************************************************************/
/**
\brief  SearchPathField

\return fmcbptr - Field definition block

\param  fldpath - Field path
\param  refr_opt
\param  offset - 
\param  w_kcbptr - 
\param  w_typsmcb
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SearchPathField"

fmcb *smcb :: SearchPathField (char *fldpath, logical refr_opt, int32 *offset, kcb *w_kcbptr, smcb **w_typsmcb )
{
  char     *pkt;
  char     *end;
  char     *par;
  char      fldname[ID_SIZE];
  char      fldnames[ID_SIZE+1];
  fmcb     *fmcbptr = NULL;
  fmcb     *tfmcbptr;
  short     indx    = 0;
  char      path[2001];
  int       len = strlen(fldpath);
BEGINSEQ
  if ( !this )                                       SOSERR(99)
  if ( len > 2000 )                                  SOSERR(99)
  SOSEV1(fldpath,UNDEF);
  
  if ( w_typsmcb )
    *w_typsmcb = NULL;
  
  strcpy(path,fldpath);
  if ( pkt = NextProperty(path,&par) )
    *pkt = 0;
  if ( par )
    *par = 0;
  gvtxstb(fldname,path,ID_SIZE);
  
  if ( !(fmcbptr = GetEntry(fldname)) ) 
  {
    gvtxbts(fldnames,fldname,ID_SIZE);
    while ( (tfmcbptr = GetEntry(++indx)) && tfmcbptr->fmcbbstr && tfmcbptr->fmcbsmcb  )
      if ( fmcbptr = tfmcbptr->fmcbsmcb->SearchPathField(fldnames,refr_opt,offset,w_kcbptr,w_typsmcb) )
      {
        *offset += tfmcbptr->fmcbposn;
        break;
      }
  }
  if ( !fmcbptr )           // jetzt schaun wir noch mal mit Klammern, sowas gibts in OMA
  {
    gvtxstb(fldname,fldpath,ID_SIZE);
    if ( !(fmcbptr = GetEntry(fldname)) )            ERROR
  }
  
  if ( w_kcbptr && fmcbptr->fmcbrlev == R_GENERIC )
    if ( w_kcbptr->SetGenField(fmcbptr,*offset) )    ERROR

  if ( pkt )
  {
    if ( !fmcbptr->fmcbsmcb )                        SOSERR(99)
    if ( fmcbptr->fmcbrlev == R_REFR || fmcbptr->fmcbrlev > 0 ) 
    {
      if ( !refr_opt )                               ERROR
      *offset = UNDEF;
    }
    else
      *offset += fmcbptr->fmcbposn;
    
    if ( !(fmcbptr = fmcbptr->fmcbsmcb->SearchPathField(pkt+1,refr_opt,offset,w_kcbptr,w_typsmcb)) )
                                                     ERROR
    *pkt = '.';
  }

  if ( w_typsmcb && !*w_typsmcb )
    *w_typsmcb = this;

RECOVER
  fmcbptr = NULL;
ENDSEQ
  return(fmcbptr);

}

/******************************************************************************/
/**
\brief  SetAllignment


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAllignment"

void smcb :: SetAllignment ( )
{

  switch ( defined_align )
  {
    case  0 : defined_align = DEFAULT_ALLIGNMENT;
              break;
    case  1 : 
    case  2 : break;
    case  3 :
    case  4 : defined_align = 4;
              break;
    case  5 :
    case  6 :
    case  7 :
    case  8 : defined_align = 8;
              break;
    default : defined_align = 16;
  }

}

/******************************************************************************/
/**
\brief  SetLength - Set instance length
        The  function  sets  the  instance  length to lastpos. When passing AUTO
        (-1)  as last position, the function claculated the instance length from
        the field definitions.


\param  lastpos - Last position in instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLength"

void smcb :: SetLength (int32 lastpos )
{
  int        indx = 0;
  fmcb      *fmcbptr;
  if ( lastpos == AUTO )
    while ( fmcbptr = GetEntry(++indx) )
      if ( lastpos < fmcbptr->fmcbposn + fmcbptr->fmcbbyte )
        lastpos = fmcbptr->fmcbposn + fmcbptr->fmcbbyte;

  if ( lastpos == AUTO )
    smcbtlen = 0;
  else
    smcbtlen = lastpos;
    
  if ( !plattform_align )
    plattform_align = 1;    
  


}

/******************************************************************************/
/**
\brief  smcb

-------------------------------------------------------------------------------
\brief  SMCB_


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "smcb"

                        smcb :: smcb ( )
                     :   smcbnsid(0), 
  smcbityp(UNDEF), 
  smcbstyp(UNDEF), 
  smcbatyp(UNDEF), 
  smcberr(NO), 
  smcbsts(),
  is_pd(AUTO),
  defined_align(DEFAULT_ALLIGNMENT),
  plattform_align(UNDEF),
  smcbtlen(0), 
  smcbfmcl(NULL), 
  smcbidky(NULL), 
  smcbskey(new lkcb), 
  smcbacc(NULL)

{

  memset(smcbname,' ',sizeof(smcbname));


}

/******************************************************************************/
/**
\brief  SMCB_C


\param  smcbptr - Structure definition block
\param  w_strnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "smcb"

                        smcb :: smcb (smcb *smcbptr, char *w_strnames )
                     :   smcbnsid(0), 
  smcbityp(smcbptr->smcbityp), 
  smcbstyp(smcbptr->smcbstyp), 
  smcbatyp(smcbptr->smcbatyp), 
  smcberr(NO),
  smcbsts(),
  is_pd(smcbptr->IsPD()),
  defined_align(smcbptr->defined_align), 
  plattform_align(smcbptr->plattform_align), 
  smcbtlen(smcbptr->smcbtlen), 
  smcbfmcl(NULL), 
  smcbidky(NULL), 
  smcbskey(new lkcb), 
  smcbacc(NULL)
{

BEGINSEQ
  if ( w_strnames )
    gvtxstb(smcbname,w_strnames,sizeof(smcbname));
  else
    memcpy(smcbname,smcbptr->smcbname,sizeof(smcbname));

  if ( smcbptr->smcbfmcl )
    if ( !(smcbfmcl = new fmcl(smcbptr->smcbfmcl)) )   
                                                   SOSERR(95)
RECOVER
  smcberr = SOSERROR;
ENDSEQ
  return;

}

/******************************************************************************/
/**
\brief  SMCB_D


\param  strnames - 
\param  nsid
\param  w_styp - 
\param  w_atyp - 
\param  w_fmclptr - 
\param  w_allign - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "smcb"

                        smcb :: smcb (char *strnames, int32 nsid, int16 w_styp, int16 w_atyp, fmcl *w_fmclptr, int16 w_allign )
                     :   smcbnsid(0), 
  smcbityp(UNDEF), 
  smcbstyp(w_styp), 
  smcbatyp(w_atyp), 
  smcberr(NO),
  smcbsts(),
  defined_align(w_allign),
  plattform_align(UNDEF),
  is_pd(AUTO),
  smcbtlen(UNDEF),
  smcbfmcl(w_fmclptr), 
  smcbidky(NULL),
  smcbskey(new lkcb),
  smcbacc(NULL)

{

  gvtxstb(smcbname,strnames ? strnames : "",sizeof(smcbname));
  smcbnsid = nsid;
  
  if ( !smcbstyp )
    smcbstyp = ST_USER;

  SetAllignment();

  
  SOSRESET


}

/******************************************************************************/
/**
\brief  SMCB_I


\param  strnames - 
\param  nsid
\param  strid - 
\param  intlen - 
\param  styp - 
\param  w_atyp - 
\param  w_allign - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "smcb"

                        smcb :: smcb (char *strnames, int32 nsid, int16 strid, int32 intlen, int16 styp, int16 w_atyp, int16 w_allign )
                     :   smcbnsid(0), 
  smcbityp(strid),
  smcbstyp(styp),
  smcbatyp(w_atyp), 
  smcberr(NO),
  smcbsts(),
  is_pd(AUTO),
  defined_align(w_allign),
  plattform_align(UNDEF),
  smcbtlen(intlen),
  smcbfmcl(NULL),
  smcbidky(NULL), 
  smcbskey(new lkcb),
  smcbacc(NULL)

{

  gvtxstb(smcbname,strnames,sizeof(smcbname));
  smcbnsid = nsid;
  smcbatyp = UNDEF;

  SetAllignment();
  
  SOSRESET


}

/******************************************************************************/
/**
\brief  smcbkchk

\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "smcbkchk"

logical smcb :: smcbkchk ( )
{
  logical       term = NO;
/*
  fmcb         *fmcbptr;
  fmcb         *keyfmcb;
  register int  indx = 0;

BEGINSEQ
  smcberr = 0;
  if ( !smcbksmc )                                   LEAVESEQ

  while ( keyfmcb = smcbksmc->GetEntry(++indx) )
  {
    if ( !(fmcbptr = GetEntry(keyfmcb->fmcbname)) )  SDBERR(41)?
    if ( keyfmcb->fmcbcmp(fmcbptr) )                 SDBSET(4)?
  }

RECOVER
  term = YES;
ENDSEQ
*/
  return(term);

}

/******************************************************************************/
/**
\brief  smcbmult

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "smcbmult"

logical smcb :: smcbmult ( )
{
  smcb     *smcbptr;
  fmcb     *fmcbptr;
  int       indx = 0;
  logical   cond = YES;

BEGINSEQ
  smcberr = 0;

  while ( fmcbptr = GetEntry(++indx) )
  {
    if ( fmcbptr->fmcbdim != 1 )                     LEAVESEQ
    if ( smcbptr = fmcbptr->fmcbsmcb )
      switch ( smcbptr->smcbstyp )
      {
        case ST_USER : smcbptr = smcbptr->smcbidky->scbsmcb;
        case ST_KEY  : if ( smcbptr->smcbmult())     LEAVESEQ
                       break;
        default      : ;                       
      }
  }

  cond = NO;

ENDSEQ
  return(cond);

}

/******************************************************************************/
/**
\brief  ~smcb


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~smcb"

                        smcb :: ~smcb ( )
{
  kcb      *kcbptr;
  delete smcbacc;
  delete smcbfmcl;

  if ( smcbskey )
  {
    while ( kcbptr = smcbskey->RemoveTail() )
    {
      delete kcbptr->scbsmcb;
      kcbptr->scbsmcb = NULL;
      delete kcbptr;
    }  
  
    delete smcbskey;
    smcbskey = NULL;
  }

}


