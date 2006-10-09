/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|18:19:36,78}|(REF)
\class    CSAccess

\brief    


\date     $Date: 2006/04/03 18:41:55,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CSAccess"

#include  <popa7.h>
#include  <sDBFieldDef.hpp>
#include  <sDBHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sLACObject.hpp>
#include  <sSDB_CSEntry.hpp>
#include  <scst.hpp>
#include  <sexd.hpp>
#include  <sexdBuffer.hpp>
#include  <sCSAccess.hpp>


/******************************************************************************/
/**
\brief  AddInstance - 


\return term - Termination code

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddInstance"

logical CSAccess :: AddInstance (void *instptr )
{
  SDB_CSEntry            *csentry = NULL;
  char                    enum_inst[512];
  logical                 term = NO;
BEGINSEQ
  if ( !(csentry = (SDB_CSEntry *)instptr) )         ERROR
    
  memset(enum_inst,0,sizeof(enum_inst));
  
//2.1.05 sonst geht Kopieren von entries mit -1 nicht
//  if ( csentry->value == AUTO )
//    csentry->value = CS_U;
    
  memcpy(enum_inst,&csentry->value,sizeof(int16));
  if ( *cs_table->get_base_type() > ' ' )
    memcpy(enum_inst+2,csentry->type,cs_table->get_id_size());
  
  cs_table->SetValue(enum_inst,csentry->string);
  if ( cs_table->cstadd(enum_inst) )                    ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CSAccess - 



\param  lobhandle - 
\param  fielddef - Internal field defintion
\param  len - 
\param  extopt - 
\param  cstptr
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CSAccess"

                        CSAccess :: CSAccess (LACObject *lobhandle, DBFieldDef *fielddef, uint16 len, logical extopt, cst *cstptr )
                     : RefAccess (lobhandle,fielddef->GetDBStruct(),1),
  cs_table(cstptr),
  cs_entry(NULL),
  id_size(ID_SIZE),
  owns_table(cstptr ? NO : YES)
{
  logical        exist = YES;

BEGINSEQ
  id_size = lobhandle->GetID_SIZE();  
    
  ref_buffer->set_sid(fielddef->fmcbityp);
  if ( !(cs_entry = new exd(lobhandle,NULL,sizeof(SDB_CSEntry))) )
                                                     SDBERR(95)
  cs_entry->stsstrans();  // indicate codeset entry
  cs_entry->SetIEH(sizeof(SDB_CSEntry),fielddef->fmcbityp,UNDEF,UNDEF);
  
  exist = lobhandle->SetStructAccess(this,fielddef->fmcbityp);
  
  if ( !cs_table )
    if ( !(cs_table = new cst(lobhandle,fielddef,this,len,extopt)) )
                                                     SDBERR(95)
                                                     SDBCERR
RECOVER

ENDSEQ
  if ( !exist )
    lobhandle->ResetStructAcc(this,fielddef->fmcbityp);
}

/******************************************************************************/
/**
\brief  GetInstance - 


\return exdarea - 
-------------------------------------------------------------------------------
\brief  i0


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

exd *CSAccess :: GetInstance (EB_Number ebsnum, EB_Number clnumb, void *instptr, exd *exdarea, int32 instlen, uint16 version, logical *p_update )
{
  char        *valstr;
  SDB_CSEntry *entry = (SDB_CSEntry *)cs_entry->GetInstance();
BEGINSEQ
  cs_entry->set_exdebsn(ebsnum);
  ebsnum.FromPIF(ob_handle->IsPIF());
    
  if ( !(valstr = cs_table->cstcsg((int16)ebsnum.get_ebsnum())) )
                                                     ERROR
  entry->value = (int16)ebsnum.get_ebsnum();
  
  memset(entry->type,' ',id_size);
  if ( *cs_table->get_base_type() > ' ' )
    memcpy(entry->type,cs_table->cstctg(entry->value),id_size);
  gvtxbts(entry->string,valstr,cs_table->cstlengt());
    
  exdarea = cs_entry;
  struct_def->ExtToInt((char *)instptr,exdarea->GetInstance(),NO);
RECOVER
  exdarea = NULL;
ENDSEQ
  return(exdarea);
}

/******************************************************************************/
/**
\brief  i1


\param  instptr - 
\param  exdarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInstance"

exd *CSAccess :: GetInstance (void *instptr, exd *exdarea )
{


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

logical CSAccess :: PutInstance (void *instptr, exd *exdarea, int32 instlen, logical refresh_opt )
{
  char                    sval[257];
  char                   *valstr;
  int16                   cval;
  EB_Number               ebsnum;
  logical                 term = NO;
  ebsnum = cs_entry->get_exdebsn();
  ebsnum.FromPIF(ob_handle->IsPIF());
  
  cval = ebsnum.get_ebsnum();
  if ( cval != CS_U )
    if ( valstr = cs_table->cstcsg(cval) )
      cs_table->cstdel((char *)memcpy(sval,valstr,cs_table->get_id_size()));
  
  AddInstance(instptr);    
  exdarea = cs_entry;
  cs_entry->get_exdebsn() = ((uint16)(cval)) + (1<<28);
  cs_entry->get_exdebsn().ToPIF(ob_handle->IsPIF());
  return(term);
}

/******************************************************************************/
/**
\brief  ~CSAccess - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CSAccess"

                        CSAccess :: ~CSAccess ( )
{

  delete cs_entry;
  cs_entry = NULL;
  
  if ( owns_table )
    delete cs_table;
  cs_table = NULL;

}


