/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACStructure

\brief    


\date     $Date: 2006/03/12 19:16:13,87 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ACStructure"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sDBHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sEB_Number.hpp>
#include  <sLACObject.hpp>
#include  <sexd.hpp>
#include  <sexdBuffer.hpp>
#include  <sisel.hpp>
#include  <sACStructure.hpp>


/******************************************************************************/
/**
\brief  ACStructure - 


-------------------------------------------------------------------------------
\brief i0


\param  lobhandle -
\param  strdefptr -
\param  maxcount -
\param  shadow_read -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACStructure"

                        ACStructure :: ACStructure (LACObject *lobhandle, DBStructDef *strdefptr, int16 maxcount, logical shadow_read )
                     : RefAccess(lobhandle,strdefptr,maxcount,shadow_read),
          struct_buffer(NULL)
{

BEGINSEQ
  if ( strdefptr->GetLength() )
  {
    if ( !(instarea = new char[strdefptr->GetInstLength(NO)])) 
                                                     SDBERR(95)
    memset(instarea,0,strdefptr->GetInstLength(NO));
  }
  if ( !(struct_buffer = new exdBuffer(lobhandle,
                                       maxcount,(int16)strdefptr->get_ext_length(),
                                       strdefptr->smcbityp,
                                       strdefptr->get_schema_ver(),
                                       shadow_read,!shadow_read)) )
                                                     SDBERR(95)
/*  
  if ( !(struct_buffer = new exdBBuffer(lobhandle,
                                       maxcount,(int16)strdefptr->get_ext_length(),
                                       strdefptr->smcbityp,
                                       strdefptr->get_schema_ver())) )
*/

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ACStructure"

                        ACStructure :: ACStructure ( )
                     : RefAccess (NULL,NULL,0,UNDEF),
struct_buffer(NULL)
{



}

/******************************************************************************/
/**
\brief  ConvertInstance - 


\return term - Termination code

\param  exdarea -
\param  instptr -
\param  instlen -
\param  p_update -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConvertInstance"

logical ACStructure :: ConvertInstance (exd *exdarea, void *instptr, int32 instlen, logical *p_update )
{
  DBStructDef            *old_struct;
  logical                 term = NO;
BEGINSEQ
  ILock(YES);
  if ( struct_def->smcbityp == T_MEMO )
  {
    memset(instptr,0,instlen);
    strncpy((char *)instptr,exdarea->GetInstance(),MIN(instlen,exdarea->GetLength()));
  }
  else if ( struct_def->smcbityp == T_BLOB )
  {
    memset(instptr,0,instlen);
    memcpy((char *)instptr,exdarea->GetInstance(),MIN(instlen,exdarea->GetLength()));
  }
  else
  {
    if ( struct_def->get_schema_ver() > exdarea->get_schemaver() )
    {
#ifdef __sun__
               // versionierung auf UNIX muss bezueglich der ausrichtungsschwierigkeiten 
  SDBERR(999)  // externer Instanzen noch ueberarbeitet werden
               // DBFieldDef::CopyExtInst(_dtd)
#endif
      if ( !(old_struct = struct_def->GetStrDefVersion(ob_handle->GetDictionary(),exdarea->get_schemaver())) )
                                                     SDBERR(99)
if ( ob_handle->GetDBVersion() >= 6 )  // upgrade6, only
{
      if ( struct_def->get_ext_length() < old_struct->get_ext_length() )  // instance read not complete
      {
        exdarea->stsrfil();
        if ( exdarea->Read(old_struct->get_ext_length()) )                // read again
                                                     ERROR
      }
      else
        if ( !exdarea->ChangeSize(struct_def->get_ext_length()) )
                                                     ERROR
}      
      if ( struct_def->ConvInstVersion(ob_handle,exdarea->GetInstance(),exdarea->get_schemaver(),p_update) )
                                                     ERROR
      memcpy(exdarea->GetInstance(),struct_def->get_ext_area(),struct_def->get_ext_length());
      exdarea->SetLength(struct_def->get_ext_length());
      exdarea->set_schema_ver(struct_def->get_schema_ver());
    }
    struct_def->ExtToInt((char *)instptr,exdarea->GetInstance(),pif);
  } 

RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  CreateEXD - 


\return exdarea -

\param  extarea -
\param  instlen -
\param  version -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateEXD"

exd *ACStructure :: CreateEXD (char *extarea, int32 instlen, uint16 version )
{
  exd        *exdarea = NULL;
BEGINSEQ
  if ( !(exdarea = CreateInstance(0,0,instlen,CUR_VERSION)) )
                                                     ERROR
  exdarea->set_schema_ver(version);
  memcpy(exdarea->GetInstance(),extarea,instlen);
  exdarea->stssmod();
  exdarea->Write(AUTO,AUTO);

RECOVER

ENDSEQ
  return(exdarea);
}

/******************************************************************************/
/**
\brief  CreateInstance - 


\return exdarea -

\param  mbnumber - MainBase number
\param  clnumb -
\param  instlen -
\param  version_nr - Internal version number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateInstance"

exd *ACStructure :: CreateInstance (int16 mbnumber, EB_Number clnumb, int32 instlen, uint16 version_nr )
{
  exd      *exdarea = NULL;
  EB_Number entnr;
BEGINSEQ
  if ( (entnr = CreateEBI(mbnumber,clnumb,struct_def->get_sb_number(),version_nr)).IsEmpty() ) 
                                                       ERROR

  if ( struct_def->smcbityp != T_MEMO && struct_def->smcbityp != T_BLOB)
    instlen = struct_def->get_ext_length();
    
  if ( !(exdarea = struct_buffer->Locate(entnr,clnumb,IDB_INS,instlen,version_nr)) )  
                                                       ERROR
  exdarea->LockUntilReserveInstance();
  exdarea->NewEntry();
  exdarea->SetLength(instlen);
  memset(exdarea->GetInstance(),0,instlen);
  if ( pif ) 
    exdarea->SetPIF();
RECOVER

ENDSEQ
  return(exdarea);
}

/******************************************************************************/
/**
\brief  GetEXD - 


\return exdptr -

\param  exdarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEXD"

exd *ACStructure :: GetEXD (exd *exdarea )
{
  exd                    *exdptr = NULL;
  if ( !(exdptr = RefAccess::GetEXD(exdarea)) )
    exdptr = struct_buffer->Locate(exdarea->get_exdebsn(),exdarea->get_shadow_base(),exdarea->get_exdacb()->get_version());
  return(exdptr);
}

/******************************************************************************/
/**
\brief  GetInstLength - 


\return instlen -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstLength"

int32 ACStructure :: GetInstLength ( )
{


  return(struct_buffer->get_inst_length());
}

/******************************************************************************/
/**
\brief  GetInstance - 


\return exdarea -
-------------------------------------------------------------------------------
\brief i0


\param  ebsnum -
\param  clnumb -
\param  instptr -
\param  exdarea -
\param  instlen -
\param  version -
\param  p_update -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

exd *ACStructure :: GetInstance (EB_Number ebsnum, EB_Number clnumb, void *instptr, exd *exdarea, int32 instlen, uint16 version, logical *p_update )
{

BEGINSEQ
  if ( !exdarea )
  {
    if ( !(exdarea = struct_buffer->Locate(ebsnum,clnumb,IDB_INS,instlen,version)) )
                                                     ERROR
    exdarea->LockUntilReserveInstance();
  }
  else
    exdarea = exdarea->VerifyVersion(version);
  
  if ( !instlen )
    instlen = struct_buffer->get_inst_length();
    
  if ( !ReadInstance(exdarea,instlen) )              ERROR
  
  if ( exdarea->NewEntry() )
  {
    exdarea->SetLength(instlen);
    memset(exdarea->GetInstance(),0,instlen);
  }

  if ( !exdarea->IsInstance() )                      SDBERR(105)
  if ( ConvertInstance(exdarea,instptr,instlen,p_update) ) ERROR
RECOVER
  struct_def->smcbfmcl->fmcliini((char *)instptr);
  if ( exdarea )
    exdarea->ReleaseInstance(NULL);
  exdarea = NULL;

ENDSEQ
  return(exdarea);
}

/******************************************************************************/
/**
\brief i1


\param  instptr -
\param  exdarea -
\param  p_update -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

exd *ACStructure :: GetInstance (void *instptr, exd *exdarea, logical *p_update )
{

BEGINSEQ
  if ( !exdarea )                                    ERROR
  
  if ( ReadInstance(exdarea,AUTO) )                  ERROR
  
  if ( ConvertInstance(exdarea,instptr,UNDEF,p_update) ) ERROR
RECOVER
  exdarea = NULL;
ENDSEQ
  return(exdarea);
}

/******************************************************************************/
/**
\brief  PutInstance - 


\return term - Termination code

\param  instptr -
\param  exdarea -
\param  instlen -
\param  refresh_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PutInstance"

logical ACStructure :: PutInstance (void *instptr, exd *exdarea, int32 instlen, logical refresh_opt )
{
  int32      len = 0;
  int32      lenadd;
  logical   term = NO;
BEGINSEQ
  ILock(YES);
  if ( !exdarea || exdarea->LockInternal(YES) )     ERROR

  if ( struct_def->smcbityp == T_MEMO )
  {
    len = 0;
    if ( instlen > 0)
      if ( len = gvtutle0((char *)instptr,instlen-1) )
        memcpy(exdarea->GetInstance(),instptr,len);
    *(exdarea->GetInstance()+len) = 0;    
    
    exdarea->SetLength(len);
    if ( len > exdarea->get_exdacb()->get_entry_length() )
    {
      lenadd = MIN(len/5,100);
      len = MIN(instlen-1,len+lenadd);
    }
  }
  else if ( struct_def->smcbityp == T_BLOB )
  {
    memcpy(exdarea->GetInstance(),instptr,len);
  }
  else
  {
    if ( refresh_opt ) 
      if ( exdarea->Read(AUTO) )                     ERROR
    if ( struct_def->IntToExt(exdarea->GetInstance(),(char *)instptr,pif) )
                                                     ERROR
    if ( pif )
      exdarea->SetPIF();
    len = struct_def->get_ext_length();
    exdarea->set_schema_ver(struct_def->get_schema_ver());
  }
  
  if ( exdarea->Write(len,(int16)AUTO) )             ERROR
RECOVER
  term = YES;
ENDSEQ
  IUnlock();
  return(term);
}

/******************************************************************************/
/**
\brief  ReadInstance

\return exdarea -

\param  exdarea -
\param  instlen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadInstance"

exd *ACStructure :: ReadInstance (exd *exdarea, int32 instlen )
{
  DBStructDef       *strdef;
  DBStructDef       *srce_struct;
  logical           update = NO;
BEGINSEQ
  if ( exdarea->Read(instlen) )                         ERROR
  
  if ( !exdarea->stscini() && struct_def->smcbityp > 0 && ob_handle->GetDBVersion() < 6 )
  {
    strdef = struct_def;
    if ( strdef->get_schema_ver() > exdarea->get_schemaver() )
    {
      if ( !(strdef = strdef->GetStrDefVersion(ob_handle->GetDictionary(),exdarea->get_schemaver())) )
                                                     SDBERR(99)
      if ( struct_def->get_ext_length() < strdef->get_ext_length() )  // instance read not complete
      {
        exdarea->stsrfil();
        if ( exdarea->Read(strdef->get_ext_length()) )                // read again
                                                     ERROR
      }
    }
    srce_struct = strdef->ProvideV5StructDef();
    memcpy(srce_struct->get_ext_area(),exdarea->GetInstance(),srce_struct->get_ext_length());
    strdef->CopyExtInst(ob_handle,srce_struct,&update);
    exdarea->ChangeSize(strdef->get_ext_length());
    memcpy(exdarea->GetInstance(),strdef->get_ext_area(),strdef->get_ext_length());
    exdarea->SetLength(strdef->get_ext_length());
    exdarea->stssetini();
  }


RECOVER
  exdarea = NULL;
ENDSEQ
  return(exdarea);
}

/******************************************************************************/
/**
\brief  ~ACStructure - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ACStructure"

                        ACStructure :: ~ACStructure ( )
{

  delete instarea;
  delete struct_buffer;

}


