/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    cst

\brief    


\date     $Date: 2006/03/12 19:18:30,92 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cst"

#include  <popa7.h>
#include  <cExtInstTypes.h>
#include  <sACObject.hpp>
#include  <sDBExtend.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBHandle.hpp>
#include  <sDBIndexList.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sLACObject.hpp>
#include  <sLDictionary.hpp>
#include  <sPropertyHandle.hpp>
#include  <sRefAccess.hpp>
#include  <sSDB_CSEntry.hpp>
#include  <sStructAccess.hpp>
#include  <sacc.hpp>
#include  <sexd.hpp>
#include  <scst.hpp>


/******************************************************************************/
/**
\brief  Access - 


\return instptr -
-------------------------------------------------------------------------------
\brief CSTACC_I


\param  indx0 - Position in collection
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Access"

char *cst :: Access (int32 indx0 )
{

  return ( cstcsg((int16)indx0) );


}

/******************************************************************************/
/**
\brief CSTACC_K


\param  keyval -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Access"

char *cst :: Access (char *keyval )
{

  static   int32 csval;
  
  return ( (csval = cstcvg(keyval)) == CS_U ? NULL : (char *)&csval );


}

/******************************************************************************/
/**
\brief  AddCSEntry - 


\return term - Termination code

\param  csentry -
\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddCSEntry"

logical cst :: AddCSEntry (SDB_CSEntry *csentry, int32 lindx0 )
{
  logical   extlock = stsclck();
  char      enum_inst[512];
  logical   term    = NO;
BEGINSEQ
  if ( exd_area && Lock() )                          ERROR

  memset(enum_inst,0,sizeof(enum_inst));
  memcpy(enum_inst,&csentry->value,sizeof(int16));
  if ( *base_type > ' ' )
    memcpy(enum_inst+2,csentry->type,id_size);
  SetValue(enum_inst,csentry->string);
  
  if ( lindx0 == AUTO )
    lindx0 = mvlsrt->srtcnt()+1;
  if ( lindx0 > mvlsrt->srtmax() )
    mvlsrt->srtsch(MAX(lindx0,mvlsrt->srtmax()+3));
  mvlsrt->srtiad(lindx0,enum_inst);

RECOVER
  term = YES;
ENDSEQ
  if ( exd_area && Unlock(extlock) )
    term = YES;
  return(term);

}

/******************************************************************************/
/**
\brief  GetAccess - 


\return accptr -

\param  atyp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAccess"

acc *cst :: GetAccess (int16 atyp )
{

  return ( atyp == AT_CODE || !atyp ? this : NULL );

}

/******************************************************************************/
/**
\brief  GetID - 


\return ebsnum -

\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetID"

EB_Number cst :: GetID (int32 lindx0 )
{
  int16         cval;
  EB_Number     ebsnum;
BEGINSEQ
  if ( (cval = cstcvg(lindx0)) == CS_U )             ERROR
  ebsnum = ((uint16)(cval)) + (1<<28);

  ebsnum.ToPIF(ob_handle->IsPIF());
RECOVER

ENDSEQ
  return(ebsnum);
}

/******************************************************************************/
/**
\brief  HasValues - 


\return cond

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasValues"

logical cst :: HasValues ( )
{

  return ( !cstrex.IsEmpty() || stscfil() );

}

/******************************************************************************/
/**
\brief  InitValuelist - 


\return term - Termination code

\param  count -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitValuelist"

logical cst :: InitValuelist (int32 count )
{
  logical                 term = NO;
BEGINSEQ
  if ( refsakcb->get_temporary() )
  {
    mvlsrt->srtsetm(count+10);
    if ( mvlsrt->srtini() )                        ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Refresh - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical cst :: Refresh ( )
{
  char      sortopt = cstcsort ? cstcsort : CS_VAL;
  logical   term    = NO;

BEGINSEQ
  if ( refsakcb->get_temporary() )                   LEAVESEQ
  if ( !mvlsrt )                                     ERROR
    
//if ( mvl::Refresh() )                              ERROR
  mvlsrt->stssold();
  if ( mvlchck() )
  {
    mvlsrt->srtres();     // reset count
    cstsoch(CS_VAL);
    if ( GetTable() )                                ERROR
  }
  if ( !mvlsrt->stscold() )
  {
    cstcsort = UNDEF;
    cstsoch(sortopt);
  }  

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  Save - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical cst :: Save ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( !exd_area || !refmod )                         LEAVESEQ
  
  cstsoch(CS_VAL);
  if ( mvl::Save() )                                ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SaveServer - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveServer"

logical cst :: SaveServer ( )
{
  SDB_CSEntry  csentry(0,NULL,NULL);
  char        *enum_inst;
  char         csname[ID_SIZE+1];
  int32         indx = 0;
  logical      term = NO;
BEGINSEQ
  if ( !object_handle || !refmod )                   LEAVESEQ
    
  DBObjectHandle   ob_handle(object_handle);
  PropertyHandle   cs(ob_handle,gvtxbts(csname,struct_def->smcbname,ID_SIZE),PI_Write);
      
  cs.DeleteSet();
  while ( enum_inst = (char *)mvlsrt->srtigt(++indx) )
  {
    memcpy(&csentry.value,enum_inst,sizeof(int16));
    memset(csentry.type,' ',sizeof(csentry.type));
    if ( *base_type > ' ' )
      memcpy(csentry.type,enum_inst+2,id_size);
    gvtxbts(csentry.string,enum_inst+cstval_pos,cstval_len);
    cs.Add(Instance(&csentry));
  }

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetHasValues - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetHasValues"

void cst :: SetHasValues ( )
{

  stssfil();

}

/******************************************************************************/
/**
\brief  SetValue - 



\param  enumerator_ptr -
\param  cstr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

void cst :: SetValue (char *enumerator_ptr, char *cstr )
{

  gvtxstb(enumerator_ptr+cstval_pos,cstr,cstval_len);
//  memcpy(enumerator_ptr+cstval_pos,cstr,cstval_len);

}

/******************************************************************************/
/**
\brief  cst - 


-------------------------------------------------------------------------------
\brief i01


\param  extdef - Internal extent definition
\param  obhandle - Database Object handle
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cst"

                        cst :: cst (DBExtend *extdef, ACObject *obhandle )
                     : acc(YES),
mvl(obhandle->GetLocalACObject(),NULL,0,IDB_MVLY,3,UNDEF,
    extdef->get_index_list()->GetHead(),YES),
  cstcsort(UNDF),
  cstrex(0),
  cstval_pos(0),
  cstval_len(0),
  cstval_typ(' '),
  struct_def(NULL),
  object_handle(obhandle)
{

BEGINSEQ
  memset(base_type,' ',ID_SIZE);
  id_size = obhandle->GetID_SIZE();
  
  if ( cstini(extdef->GetDBStruct(),AUTO) )          ERROR
  
  if ( refsakcb )
    refsakcb->set_temporary(YES);


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i02


\param  obhandle - Database Object handle
\param  extdef - Internal extent definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cst"

                        cst :: cst (ACObject *obhandle, DBExtend *extdef )
                     : acc(YES),
mvl(obhandle->GetLocalACObject(),NULL,0,IDB_MVLY,3,UNDEF,
    extdef->get_index_list()->GetHead(),YES),
  cstcsort(UNDF),
  cstrex(0),
  cstval_pos(0),
  cstval_len(0),
  cstval_typ(' '),
  struct_def(NULL),
  object_handle(obhandle)
{
  EB_Number   *extref;
  LACObject   *lobhandle;
  SDB_CSEntry *csentry;
  char         enum_inst[512];
  char         string[ID_SIZE+1];
  int32        lindx0 = 0;
BEGINSEQ
  memset(base_type,' ',ID_SIZE);
  id_size = obhandle->GetID_SIZE();
  
  if ( lobhandle = obhandle->GetLocalACObject() )
  {
    TypeKey  tkey(extdef->fmcbname,extdef->fmcbnsid);
    if ( !(extref = lobhandle->GetDictionary()->GetLocalDictionary()->ProvideCSRef(tkey)) )
                                                     ERROR  
    cstrex = *extref;
    struct_access = (RefAccess *)lobhandle->GetStructAccess(extdef->fmcbityp);
    if ( cstini(extdef->fmcbityp,AUTO) )             ERROR
  }

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i2


\param  lobhandle -
\param  fielddef - Internal field defintion
\param  refacc -
\param  strlen -
\param  extopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cst"

                        cst :: cst (LACObject *lobhandle, DBFieldDef *fielddef, RefAccess *refacc, int16 strlen, logical extopt )
                     : acc(YES),
mvl(lobhandle->get_db_handle()->GetLocalDBHandle(),
    NULL,0,IDB_MVLY,3,UNDEF,
    fielddef->get_index_list()->GetHead(),
    YES),
  cstcsort(UNDF),
  cstrex(0),
  cstval_pos(0),
  cstval_len(strlen),
  cstval_typ(' '),
  struct_def(NULL),
  object_handle(lobhandle)
{
  EB_Number   *extref;
BEGINSEQ
  memset(base_type,' ',ID_SIZE);
  
  TypeKey  tkey(fielddef->fmcbname,fielddef->fmcbnsid);
  if ( !(extref = lobhandle->GetExtendRef(tkey)) ) 
    if ( !(extref = lobhandle->ProvideCSRef(tkey)) ) SDBERR(129)
      
  cstrex        = *extref;
  struct_access = refacc;
  id_size = lobhandle->GetID_SIZE();
  if ( cstini(fielddef->fmcbityp,extopt) )               ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  cstadd

\return term - Termination code

\param  enumerator_ptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstadd"

logical cst :: cstadd (char *enumerator_ptr )
{
  logical   extlock = stsclck();
  int16     cval;
  logical   term    = NO;

BEGINSEQ
  if ( exd_area && Lock() )                          ERROR

  cval = *(int16 *)enumerator_ptr;  
  if ( (cval != CS_U && cstcsg(cval) ) ||
        cstcvg(enumerator_ptr+cstval_pos) != CS_U )  SDBERR(64)

  if ( !mvlchk(AUTO) )                                ERROR
  
  if ( cval == CS_U )
  {
    if ( (cval = cstcvng()) == CS_U )                ERROR
    *(int16 *)enumerator_ptr = cval;
  }
  mvlsrt->srtkad(enumerator_ptr);
  
  Modify();

RECOVER
  term = YES;
ENDSEQ
  if ( exd_area && Unlock(extlock) )
    term = YES;
  return(term);

}

/******************************************************************************/
/**
\brief  cstcsg - 


\return cstr -

\param  cval -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstcsg"

char *cst :: cstcsg (int16 cval )
{
  char     *cstr = NULL;

BEGINSEQ
  if ( Refresh() )                                     ERROR
  cstsoch(CS_VAL);

  if ( !(cstr = (char *)mvlsrt->srtigt(mvlsrt->srtssr((char *)&cval))) ) 
                                                       ERROR
  cstr += cstval_pos;

RECOVER

ENDSEQ
  return(cstr);

}

/******************************************************************************/
/**
\brief  cstcsgt - 


\return cstr -

\param  ctyp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstcsgt"

char *cst :: cstcsgt (char *ctyp )
{
  char      *cstr = NULL;
BEGINSEQ
  if ( *base_type <= ' ' )                            ERROR
  if ( Refresh() )                                    ERROR
  cstsoch(CS_TYP);

  if ( !(cstr = (char *)mvlsrt->srtigt(mvlsrt->srtssr(ctyp))) )  
                                                        ERROR
  cstr += cstval_pos;

RECOVER
  cstr = NULL;
ENDSEQ
  return(cstr);
}

/******************************************************************************/
/**
\brief  cstctg - 


\return ctyp -
-------------------------------------------------------------------------------
\brief i0


\param  cval -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstctg"

char *cst :: cstctg (int16 cval )
{
  char      *ctyp = NULL;
BEGINSEQ
  if ( *base_type <= ' ' )                            ERROR
  if ( Refresh() )                                    ERROR
  cstsoch(CS_VAL);

  if ( !(ctyp = (char *)mvlsrt->srtigt(mvlsrt->srtssr((char *)&cval))) ) 
                                                      ERROR
  ctyp += 2;
RECOVER
  ctyp = NULL;
ENDSEQ
  return(ctyp);
}

/******************************************************************************/
/**
\brief i1


\param  cstr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstctg"

char *cst :: cstctg (char *cstr )
{
  char      *ctyp = NULL;
BEGINSEQ
  if ( *base_type <= ' ' )                            ERROR
  if ( Refresh() )                                    ERROR
  cstsoch(CS_STR);

  if ( !(ctyp = (char *)mvlsrt->srtigt(mvlsrt->srtssr(cstr))) )  
                                                      ERROR
  ctyp += 2;
RECOVER
  ctyp = NULL;
ENDSEQ
  return(ctyp);
}

/******************************************************************************/
/**
\brief  cstcvg - 


\return cval -
-------------------------------------------------------------------------------
\brief CSTCVG


\param  cstr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstcvg"

int16 cst :: cstcvg (char *cstr )
{
  int16    *cvalptr; 
  char      buffer[512];
  int16     cval = CS_U;
BEGINSEQ
  if ( Refresh() )                                      ERROR
  cstsoch(CS_STR);

  gvtxstb(buffer,cstr,cstval_len);
  if ( !(cvalptr = (int16 *)mvlsrt->srtigt(mvlsrt->srtssr(buffer))) )  
                                                        ERROR
  cval = *cvalptr;

RECOVER
  cval = CS_U;
ENDSEQ
  return(cval);

}

/******************************************************************************/
/**
\brief i1


\param  lindx0 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstcvg"

int16 cst :: cstcvg (int32 lindx0 )
{
  int16    *cvalptr;   
  int16      cval = CS_U;
BEGINSEQ
  if ( Refresh() )                                      ERROR
  cstsoch(CS_VAL);

  if ( !(cvalptr = (int16 *)mvlsrt->srtigt((int16)lindx0+1)) )   
                                                        ERROR
  cval = *cvalptr;

RECOVER

ENDSEQ
  return(cval);
}

/******************************************************************************/
/**
\brief  cstcvgt - 


\return cval -

\param  ctyp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstcvgt"

int32 cst :: cstcvgt (char *ctyp )
{
  int16     *cvalptr;
  int32      cval = CS_U;
BEGINSEQ
  if ( *base_type <= ' ' )                            ERROR
  if ( Refresh() )                                    ERROR
  cstsoch(CS_TYP);

  if ( !(cvalptr = (int16 *)mvlsrt->srtigt(mvlsrt->srtssr(ctyp))) )  
                                                      ERROR
  cval = *cvalptr;

RECOVER

ENDSEQ
  return(cval);
}

/******************************************************************************/
/**
\brief  cstcvng - 


\return cval -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstcvng"

int16 cst :: cstcvng ( )
{
  int16     cval = CS_U;
  int16     indx = 0;
  int16    *cvalptr;

BEGINSEQ

  if ( Refresh() )                                     ERROR

  if ( !mvlsrt->srtcnt() )
    cval = 0;
  else
    while ( cvalptr = (int16 *)mvlsrt->srtigt(++indx) )
      cval = MAX(cval,*cvalptr);

  cval++;

RECOVER

ENDSEQ
  return(cval);

}

/******************************************************************************/
/**
\brief  cstdel - 


\return term - Termination code

\param  cstr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstdel"

logical cst :: cstdel (char *cstr )
{
  logical   extlock = stsclck();
  char      buffer[512];
  logical   term = NO;

BEGINSEQ
  if ( exd_area && Lock() )                          ERROR

  cstsoch(CS_STR);
  
  gvtxstb(buffer,cstr,cstval_len);
  if ( mvlsrt->srtidl(mvlsrt->srtssr(buffer)) )        ERROR
  
  Modify();
RECOVER
  term = YES;
ENDSEQ
  if ( exd_area && Unlock(extlock) )
    term = YES;
  return(term);

}

/******************************************************************************/
/**
\brief  cstget - 


\return enumerator_ptr -

\param  enumerator_ptr -
\param  indx -
\param  sortopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstget"

char *cst :: cstget (char *enumerator_ptr, int16 indx, char sortopt )
{
  char      *tempenum = NULL;

BEGINSEQ
  if ( Refresh() )                                     ERROR
  
  if ( sortopt )
    cstsoch(sortopt);

  if ( !indx )
    indx = 1;

  if ( !(tempenum = (char *)mvlsrt->srtigt(indx)) )      ERROR
  
//  memcpy(enumerator_ptr,tempenum,(int)struct_access->get_struct_def()->smcbtlen);
  memcpy(enumerator_ptr,tempenum,(int)struct_def->GetInstLength(NO));

RECOVER
  enumerator_ptr = NULL;
ENDSEQ
  return(enumerator_ptr);

}

/******************************************************************************/
/**
\brief  cstini - 


\return term - Termination code
-------------------------------------------------------------------------------
\brief i0


\param  ityp - Internal structure number
\param  extopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstini"

logical cst :: cstini (int16 ityp, logical extopt )
{
  logical      term = NO;
BEGINSEQ
  if ( !struct_access )                              LEAVESEQ // für interne cst's, die nicht aufgebaut werden können
  Setup(&cstrex,0,0);
  
  cstini(struct_access->get_struct_def(),extopt);
  
  if ( Refresh() )                                   ERROR // war bisher nur im zweiten Konstruktor

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief i01


\param  dbstrdef - Structure definition
\param  extopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstini"

logical cst :: cstini (DBStructDef *dbstrdef, logical extopt )
{
  fmcb        *fmcbptr;
  logical      term = NO;
BEGINSEQ
  struct_def = dbstrdef;
  
  fmcbptr = dbstrdef->GetLastEntry();
  if ( extopt == (logical)AUTO )
    cstval_pos = (int16)fmcbptr->fmcbposn;
  else
    cstval_pos    = 2 + (extopt == YES ? id_size : 0);
  
  if ( !cstval_len )
    cstval_len = fmcbptr->fmcbsize;
  switch ( fmcbptr->fmcbityp )
  {
    case T_STRING : 
    case T_CHAR   : cstval_typ = 'C';                break;
    case T_UINT   : 
    case T_INT    : cstval_typ = 'I';                break;
    default       : cstval_typ = ' ';
  }

  if ( extopt == YES ||
       (extopt == (logical)AUTO && dbstrdef->smcbfmcl->GetCount() > 2) )
    memcpy(base_type,dbstrdef->smcbfmcl->GetEntry(2)->fmcbname,ID_SIZE);

  if ( mvlcrt(2+cstval_len+(*base_type > ' ' ? id_size : 0),UNDEF,NULL) ) 
                                                     ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cstlengt - 


\return len -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstlengt"

int8 cst :: cstlengt ( )
{
  int       len = 0;

BEGINSEQ

  if ( !mvlsrt )                                      ERROR
  len = cstval_len;

RECOVER

ENDSEQ
  return(len);

}

/******************************************************************************/
/**
\brief  cstsoch - 


\return term - Termination code

\param  sortopt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstsoch"

logical cst :: cstsoch (char sortopt )
{
  logical   term = NO;

BEGINSEQ
  if ( cstcsort == sortopt )                          LEAVESEQ
  if ( !mvlsrt )                                      ERROR

  switch ( sortopt )
  {
    case CS_VAL : mvlsrt->srtsor(1,2,'I');
                  break;
    case CS_STR : mvlsrt->srtsor(cstval_pos+1,cstval_len,cstval_typ);
                  break;
    case CS_TYP : mvlsrt->srtsor(3,id_size,'C');
                  break;
    default     :                                    SDBERR(99)
  }

  cstcsort = sortopt;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  cstwptc - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstwptc"

logical cst :: cstwptc ( )
{

  return( Refresh() || 
          (exd_area && !exd_area->stscwpt() && exd_area->CheckWProtect()) );


}

/******************************************************************************/
/**
\brief  cstwptr - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstwptr"

logical cst :: cstwptr ( )
{

  return( Refresh() || exd_area->ResetWProtect());


}

/******************************************************************************/
/**
\brief  cstwpts - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cstwpts"

logical cst :: cstwpts ( )
{

  return( Refresh() || exd_area->SetWProtect());


}

/******************************************************************************/
/**
\brief  ~cst - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cst"

                        cst :: ~cst ( )
{

  if ( !object_handle )
    Save();
  else
    SaveServer();
    
  if ( stscmod() )
    ob_handle->GetDictionary()->GetLocalDictionary()->SaveExtList();

}


