/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CodeSet

\brief    


\date     $Date: 2006/03/12 19:16:51,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CodeSet"

#include  <popa7.h>
#include  <sACObject.hpp>
#include  <sDBHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sRefAccess.hpp>
#include  <scst.hpp>
#include  <sCodeSet.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return cval -

\param  cstr -
\param  cval -
\param  ctyp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

int16 CodeSet :: Add (char *cstr, int16 cval, char *ctyp )
{
  Dictionary  *dictionary;
  DBStructDef *strdef;
  char         type_name[ID_SIZE];
  logical      ext;

BEGINSEQ
// Behandlung abgeleiteter Extends fehlt noch
  
  if ( cxchck(PI_Write) )                            ERROR
  ext = GetBaseType() ? YES : NO;
  if ( !ext && ctyp )                                SDBERR(160)

  memcpy(cxcse,&cval,sizeof(int16));
  if ( ext )
  {
    if ( !ctyp )                                     SDBERR(161)
    gvtxstb(type_name,ctyp,ID_SIZE);
    dictionary = cxsdbh->get_dictionary(); // cxcst->get_ob_handle()->GetDictionary();
/*
    if ( !(strdef = dictionary->ProvideStructDef(type_name)->GetDBStruct()) )   
                                                     SDBERR(20)
    if ( memcmp(cxcst->get_base_type(),type_name,ID_SIZE) )
      if ( !strdef->IsBasedOn(cxcst->get_base_type()) )
                                                     SDBERR(161)
*/
    memcpy(cxcse+2,type_name,cxcst->get_id_size());
  }
  
  cxcst->SetValue(cxcse,cstr);
  if ( cxcst->cstadd(cxcse) )                           ERROR
  memcpy(&cval,cxcse,sizeof(int16));


RECOVER
  cval = CS_U;
ENDSEQ
  return(cval);

}

/******************************************************************************/
/**
\brief  CheckCS - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckCS"

logical CodeSet :: CheckCS ( )
{

  return ( !this || memcmp(cxidnt,"CS  ",4) ? YES : NO );


}

/******************************************************************************/
/**
\brief  CheckWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckWProtect"

logical CodeSet :: CheckWProtect ( )
{

  return ( cxchck(PI_Update) || !cxcst || cxcst->cstwptc() ); 

 

}

/******************************************************************************/
/**
\brief  Close


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void CodeSet :: Close ( )
{

  if ( cxcst )
  {
    cxcst->SaveServer();
    cxcst->accdcr(cxacopt==PI_Read ? RD : WT);
    cxcst = NULL;
  }
  delete cxcse;
  cxcse = NULL;

}

/******************************************************************************/
/**
\brief  CodeSet - 


-------------------------------------------------------------------------------
\brief CX_


\param  dbhandle - Database handle
\param  csnames -
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CodeSet"

                        CodeSet :: CodeSet (DBHandle *dbhandle, char *csnames, PIACC accopt )
                     : sts(),
  cxsdbh(dbhandle),
  cxcst(NULL),
  cxcse(NULL),
  cxacopt(accopt),
  cxindx(UNDF)

{

BEGINSEQ
  if ( !dbhandle->IsValid() )                       SDBERR(9)
  
  Initialize(dbhandle->get_dictionary(),csnames,accopt);
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief i02


\param  dbhdl - Database handle
\param  csnames -
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CodeSet"

                        CodeSet :: CodeSet (DatabaseHandle &dbhdl, char *csnames, PIACC accopt )
                     : sts (),
  cxsdbh(dbhdl.get_dbhandle()),
  cxcst(NULL),
  cxcse(NULL),
  cxacopt(accopt),
  cxindx(UNDF)
{

  Initialize(dbhdl.GetDictionary().get_dictionary(),csnames,accopt);

}

/******************************************************************************/
/**
\brief i03


\param  dict_hdl - Dictionary handle
\param  csnames -
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CodeSet"

                        CodeSet :: CodeSet (DictionaryHandle &dict_hdl, char *csnames, PIACC accopt )
                     : sts (),
  cxsdbh(dict_hdl.get_dictionary()),
  cxcst(NULL),
  cxcse(NULL),
  cxacopt(accopt),
  cxindx(UNDF)
{

  Initialize(dict_hdl.get_dictionary(),csnames,accopt);

}

/******************************************************************************/
/**
\brief i1


\param  dictionary -
\param  csnames -
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CodeSet"

                        CodeSet :: CodeSet (Dictionary *dictionary, char *csnames, PIACC accopt )
                     : sts (),
  cxsdbh(dictionary),
  cxcst(NULL),
  cxcse(NULL),
  cxacopt(accopt),
  cxindx(UNDF)
{

  Initialize(dictionary,csnames,accopt);    


}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Termination code

\param  cstr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical CodeSet :: Delete (char *cstr )
{
  logical   term = NO;

BEGINSEQ
// Behandlung abgeleiteter Extends fehlt noch
  

  if ( cxchck(PI_Write) )                              ERROR

  if ( cxcst->cstdel(cstr) )                           ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  GetBaseType - 


\return ctyp -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetBaseType"

char *CodeSet :: GetBaseType ( )
{

  return ( cxchck(PI_Read) || !cxcst     ? NULL : 
           *cxcst->get_base_type() > ' ' ? cxcst->get_base_type() 
                                         : NULL);

}

/******************************************************************************/
/**
\brief  GetCodeString - 


\return cstr -
-------------------------------------------------------------------------------
\brief CXSTRGT


\param  cval -
\param  w_cstr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCodeString"

char *CodeSet :: GetCodeString (int16 cval, char *w_cstr )
{
  char     *mvlcstr;

BEGINSEQ
  if ( cxchck(PI_Read) || !cxcst )                     ERROR

  if ( !(mvlcstr = cxcst->cstcsg(cval)) )              ERROR

  if ( !w_cstr )
    w_cstr = cxcse + cxcst->get_cstval_pos();

  memcpy(w_cstr,mvlcstr,GetStringLength());

RECOVER
  w_cstr = NULL;
ENDSEQ
  return(w_cstr);

}

/******************************************************************************/
/**
\brief i1


\param  ctyp -
\param  w_cstr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCodeString"

char *CodeSet :: GetCodeString (char *ctyp, char *w_cstr )
{
  char     *mvlcstr;
BEGINSEQ
  if ( cxchck(PI_Read) || !cxcst )                     ERROR

  if ( !(mvlcstr = cxcst->cstcsgt(ctyp)) )             ERROR

  if ( !w_cstr )
    w_cstr = cxcse + cxcst->get_cstval_pos();

  memcpy(w_cstr,mvlcstr,GetStringLength());

RECOVER
  w_cstr = NULL;
ENDSEQ
  return(w_cstr);
}

/******************************************************************************/
/**
\brief  GetCodeValue - 


\return cval -

\param  cstr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCodeValue"

int16 CodeSet :: GetCodeValue (char *cstr )
{

  return ( cxchck(PI_Read) || !cxcst ? CS_U : cxcst->cstcvg(cstr) ); 

 

}

/******************************************************************************/
/**
\brief  GetCount - 


\return count -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 CodeSet :: GetCount ( )
{

  return ( cxchck(PI_Read) ? AUTO : 
           !cxcst          ? 0    : cxcst->GetCount() ); 



}

/******************************************************************************/
/**
\brief  GetEnumType - 


\return ctyp -
-------------------------------------------------------------------------------
\brief i0


\param  cval -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEnumType"

char *CodeSet :: GetEnumType (int16 cval )
{
  char       *ctyp = NULL;
BEGINSEQ
  if ( cxchck(PI_Read) || !cxcst )                     ERROR

  if ( !(ctyp = cxcst->cstctg(cval)) )                 ERROR

  ctyp = (char *)memcpy(cxcse+2,ctyp,cxcst->get_id_size());

RECOVER

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
#define    MOD_ID  "GetEnumType"

char *CodeSet :: GetEnumType (char *cstr )
{
  char       *ctyp = NULL;
BEGINSEQ
  if ( cxchck(PI_Read) || !cxcst )                     ERROR

  if ( !(ctyp = cxcst->cstctg(cstr)) )                 ERROR

  ctyp = (char *)memcpy(cxcse+2,ctyp,cxcst->get_id_size());

RECOVER

ENDSEQ
  return(ctyp);
}

/******************************************************************************/
/**
\brief  GetStringLength - 


\return len -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringLength"

int8 CodeSet :: GetStringLength ( )
{

  return ( cxchck(PI_Read) || !cxcst ? UNDEF : cxcst->cstlengt() ); 

 

}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - Termination code

\param  dictionary -
\param  csnames -
\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical CodeSet :: Initialize (Dictionary *dictionary, char *csnames, PIACC accopt )
{
  DBExtend     *extdef;
  logical       term = NO;
BEGINSEQ
  SDBRESET
  if ( !dictionary )                                 SDBERR(99)
 
  if ( !(extdef = dictionary->ProvideExtendDef(csnames)) )
                                                     SDBERR(20)
  if ( !(cxcst = (cst *)extdef->fmcbsmcb->smcbacc->GetAccess(AT_CODE)) )   
                                                     SDBERR(84)
  cxcst->accinc(accopt==PI_Read ? RD : WT);
  if ( !(cxcse = new char[(int)extdef->fmcbsmcb->GetInstLength(NO)+2]) )
					             SDBERR(95)
  memcpy(cxidnt,"CS  ",4);

RECOVER
  memcpy(cxidnt,"    ",4);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Lock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Lock"

logical CodeSet :: Lock ( )
{



  return( cxchck(PI_Read) || !cxcst || cxcst->Lock() );



}

/******************************************************************************/
/**
\brief  ResetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetWProtect"

logical CodeSet :: ResetWProtect ( )
{
 

  return ( cxchck(PI_Update) || !cxcst || cxcst->cstwptr() ); 

 

}

/******************************************************************************/
/**
\brief  SetWProtect - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWProtect"

logical CodeSet :: SetWProtect ( )
{

  return ( cxchck(PI_Update) || !cxcst || cxcst->cstwpts() ); 


}

/******************************************************************************/
/**
\brief  Unlock - 


\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Unlock"

logical CodeSet :: Unlock ( )
{

  return( cxchck(PI_Read) || !cxcst || cxcst->Unlock(NO) );


}

/******************************************************************************/
/**
\brief  UpdateType - 


\return term - Termination code

\param  cstr -
\param  ctyp -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateType"

logical CodeSet :: UpdateType (char *cstr, char *ctyp )
{
  char        oldtyp[ID_SIZE]; 
  int16       cval = CS_U;
  logical     term = NO;
BEGINSEQ
  if ( cxchck(PI_Update) )                           ERROR
  if ( !GetBaseType() )                              SDBERR(160)
  
  if ( (cval = GetCodeValue(cstr)) == CS_U )         ERROR
  
  memcpy(oldtyp,GetEnumType(cstr),cxcst->get_id_size());
  
  if ( Delete(cstr) )                                ERROR
  if ( Add(cstr,cval,ctyp) == CS_U ) 
  {
    Add(cstr,cval,oldtyp);                           ERROR
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  UpdateValue - 


\return term - Termination code

\param  cstr -
\param  cval -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateValue"

logical CodeSet :: UpdateValue (char *cstr, int16 cval )
{
  char       ctyp[ID_SIZE];
  logical    ext;
  logical    term = NO;
BEGINSEQ
  if ( cxchck(PI_Update) )                           ERROR
  
  if ( GetCodeString(cval) )                         SDBERR(64)
  
  ext = GetBaseType() != NULL;
  memset(ctyp,' ',sizeof(ctyp));
  if ( ext && GetCodeValue(cstr) )
    memcpy(ctyp,GetEnumType(cstr),cxcst->get_id_size());
  
  if ( Delete(cstr) || (Add(cstr,cval,ext ? ctyp : (char *)NULL) == CS_U) )    ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cxchck - 


\return term - Termination code

\param  accopt - Access mode
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cxchck"

logical CodeSet :: cxchck (PIACC accopt )
{
  logical   term = NO;

BEGINSEQ
  if ( CheckCS() )                                  SDBERR(85)

  if ( accopt > PI_Read )
    if ( cxcst->cstwptc() )                         SDBERR(3)

  if ( !accopt )
    accopt = PI_Update;
    
  if ( accopt > cxacopt )                           SDBERR(28)

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  cxegti - 


\return cstr -

\param  indx0 - Position in collection
\param  cvalptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cxegti"

char *CodeSet :: cxegti (int32 indx0, int16 *cvalptr )
{
  char     *cstr = NULL;

BEGINSEQ
  if ( cxchck(PI_Read) || !cxcst )                      ERROR

  if ( !cxcst->cstget(cxcse,(int16)++indx0,CS_STR) )    ERROR

  cstr = cxcse + cxcst->get_cstval_pos();

  if ( cvalptr )
    memcpy(cvalptr,cxcse,sizeof(int16));

RECOVER

ENDSEQ
  return(cstr);

}

/******************************************************************************/
/**
\brief  operator() - 


\return cstr -

\param  indx0 - Position in collection
\param  cvalptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator()"

char *CodeSet :: operator() (int32 indx0, int16 *cvalptr )
{

 return (cxegti(indx0,cvalptr));

}

/******************************************************************************/
/**
\brief  ~CodeSet - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CodeSet"

                        CodeSet :: ~CodeSet ( )
{

  Close();

}


