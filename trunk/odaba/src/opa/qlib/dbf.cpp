/********************************* Class Source Code ***************************/
/**
\package  OPA - 
\class    dbf

\brief    


\date     $Date: 2006/07/24 14:13:10,65 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "dbf"

#include  <popa7.h>
#include  <coctp.h>
#ifndef   DLL_Operation_HPP
#define   DLL_Operation_HPP
#include  <sOperation.hpp>
#include  <sDLL.h>
#endif
#include  <sACObject.hpp>
#include  <sDBFieldDef.hpp>
#include  <sDBField_CHAR.hpp>
#include  <sDBField_DATE.hpp>
#include  <sDBField_INT.hpp>
#include  <sDBField_REAL.hpp>
#include  <sDBField_TIME.hpp>
#include  <sDBHandle.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sObjectReferenceHandle.hpp>
#include  <sOperation.hpp>
#include  <sParmList.hpp>
#include  <scvb.hpp>
#include  <sfmcb.hpp>
#include  <snode.hpp>
#include  <ssmcb.hpp>
#include  <ssvel.hpp>
#include  <sdbf.hpp>

int32 dbf_count = 0;

/******************************************************************************/
/**
\brief  AllocDescription - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocDescription"

logical dbf :: AllocDescription ( )
{
  logical   term = NO;
BEGINSEQ
  DelDescription();
  if ( !(fldfmcb = new DBFieldDef()) )               SDBERR(95)
  fldfaloc = YES;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AllocateArea - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AllocateArea"

logical dbf :: AllocateArea ( )
{
  logical     term = NO;
BEGINSEQ
  if ( fld::AllocateArea() )                        ERROR
  nodecur = 0;
RECOVER
  nodecur = AUTO;
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Cancel - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Cancel"

logical dbf :: Cancel ( )
{

BEGINSEQ
  if ( !this || !fldfmcb || !flddata )                 ERROR
  if ( nodecur == AUTO )                               LEAVESEQ

  Get(0);
  nodecur = AUTO;
RECOVER

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  CompareType - 



\return term - Termination code

\param  dbfptr - 
\param  convert - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompareType"

logical dbf :: CompareType (dbf *dbfptr, logical convert )
{
  char      *srce_type;
  char      *targ_type;
  logical    term = NO;
BEGINSEQ
  srce_type = GetFMCB()->fmcbtype;
  targ_type = dbfptr->GetFMCB()->fmcbtype;
  if ( !GetFMCB() )
  {
    if ( !dbfptr->GetFMCB() )                        LEAVESEQ
    else                                             ERROR
  }

  if ( !memcmp(srce_type,targ_type,ID_SIZE) )        LEAVESEQ

  if ( !convert )                                    ERROR

  if ( !cvb(dbfptr->GetFMCB(),GetFMCB(),NULL,NULL).cvbconv(UNDEF,YES) )
                                                     LEAVESEQ
    
// hier muß noch die Konvertierbarkeit von Strukturen geprüft werden
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Connect - 




\param  nodptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Connect"

void dbf :: Connect (node *nodptr )
{
  fmcb       *fmcbptr;
BEGINSEQ
  while ( nodptr && (fmcbptr = nodptr->GetFieldDef())
                 && fmcbptr->fmcbrlev != R_REFR )
    nodptr = nodptr->get_nodenode();
  
  if ( !fmcbptr )   // node nicht gültig
    nodptr = NULL;
      
  fmcbptr = fldfmcb;
  if ( highnod )
  {
    if ( highnod == nodptr )                        LEAVESEQ
    Disconnect();
  }
    
  if ( nodptr )
  {
    highnod = nodptr;
    if ( !fldfaloc )
      fldfmcb = fmcbptr;
  }

ENDSEQ

}

/******************************************************************************/
/**
\brief  ConversionError - 



\return term - Termination code

\param  fldenty - 
\param  targtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ConversionError"

logical __cdecl dbf :: ConversionError (fld &fldenty, char *targtype )
{
  logical                 term = NO;
BEGINSEQ
  if ( !SOSERROR )                               LEAVESEQ
  
  if (  fldenty.GetFMCB() ) {
     SDBEV2(fldenty.GetFMCB()->fmcbtype,ID_SIZE)
  } else {
     SDBEV2( "",ID_SIZE)
  }
  if (targtype ) {
     SDBEV3(targtype ,ID_SIZE)
  } else {
     SDBEV3( "",ID_SIZE)
  }
  
  switch ( SOSERROR )
  {
    case 50 : SDBSET(91)                    break;
    case 51 : SDBSET(92)                    break;
    default : SDBSET(99)
  }
  
  SOSRESET
  SDBRESET
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Copy - 



\return term - Termination code

\param  dbfenty_c - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

logical dbf :: Copy (const dbf *dbfenty_c )
{
  logical                 term = NO;
BEGINSEQ
  *this = *(fld *)dbfenty_c;                      SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyDBF - 




\param  dbfref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyDBF"

void dbf :: CopyDBF (dbf &dbfref )
{

BEGINSEQ
  if ( dbfref.fldfaloc )
  {
    if ( CopyDescription(dbfref.GetFMCB()) )   ERROR
  }
  else
    fldfmcb = dbfref.GetFMCB(); 
  
  if ( dbfref.flddaloc )
  {
    if ( AllocateArea() )                            SDBERR(95)
    memcpy(flddata,dbfref.GetArea(),fldfmcb->fmcbbyte);
    if ( fldfmcb->fmcbrlev == R_REFR && *(node **)flddata )
      (*(node **)flddata)->Reserve((ObjectReferenceHandle *)flddata);
  }
  else
    flddata = dbfref.GetArea();
  
  if ( dbfref.get_highnod() )
    Connect(dbfref.get_highnod());
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  CopyDescription - 



\return term - Termination code

\param  fmcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyDescription"

logical dbf :: CopyDescription (fmcb *fmcbptr )
{
  logical                 term = NO;
  char                    fldname[ID_SIZE];
BEGINSEQ
  if ( !fmcbptr )
    fmcbptr = fldfmcb;
    
  if ( fldfaloc && fmcbptr == GetDescription() )      LEAVESEQ
  if ( fldfmcb )
    memcpy(fldname,fldfmcb->fmcbname,sizeof(fldname));
  else
    *fldname = 0;
      
  AllocDescription();
  if ( !fmcbptr )                                    LEAVESEQ
    
  if ( fmcbptr->fmcbopt )
    *(DBFieldDef *)fldfmcb = *(DBFieldDef *)fmcbptr;  
  else
  {
    *fldfmcb = *fmcbptr;  // nur Übernahme des fmcb-Teils
    ((DBFieldDef *)fldfmcb)->set_transient(YES);
  }
  fldfmcb->fmcbopt = YES;
  
  if ( *fldname )  // alten Namen wiederherstellen
    memcpy(fldfmcb->fmcbname,fldname,sizeof(fldname));

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CopyInstanceArea - 



\return term - Termination code

\param  dbfptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyInstanceArea"

logical dbf :: CopyInstanceArea (dbf *dbfptr )
{
  logical                 term = NO;
BEGINSEQ
  if ( !fldfmcb )                                    ERROR
  if ( !flddata )
    AllocateArea();

  if ( !dbfptr->flddata )                            ERROR
  
  memcpy(flddata,dbfptr->flddata,fldfmcb->fmcbbyte);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DelDescription - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DelDescription"

void dbf :: DelDescription ( )
{
  DBFieldDef     *dbfdef;
  if ( fldfmcb && fldfaloc )
  {
    if ( fldfmcb->fmcbopt )
    {
      dbfdef = (DBFieldDef *)fldfmcb;
      delete dbfdef;
    }
    else 
      delete fldfmcb;
  }
  fldfmcb  = NULL;
  fldfaloc = NO;


}

/******************************************************************************/
/**
\brief  Dereference - 



\return term - Termination code

\param  dbfptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Dereference"

logical dbf :: Dereference (dbf *dbfptr )
{
  char                   *gentype;
  int32                   intpos = 0;
  int32                   extpos = 0;
  int32                   netpos = 0;
  int8                    max_aligned = 1;
  logical                 term = NO;
BEGINSEQ
  if ( dbfptr )
    CopyDescription(dbfptr->GetDescription());
  else
    if ( !fldfaloc )
      CopyDescription(NULL);
      
  if ( GetDescription() )
  {
    fldfmcb->fmcbrlev = R_DIRECT;
    fldfmcb->fmcbdim  = 1;
    switch ( fldfmcb->fmcbityp )
    {
      case T_MEMO : fldfmcb->fmcbbyte = fldfmcb->fmcbsize +1;
                    break;
      case T_VOID : fldfmcb->fmcbbyte = fldfmcb->fmcbsize = 0;
                    break;
      default     : if ( !fldfmcb )                  SDBERR(99)
                    fldfmcb->fmcbsize = fldfmcb->fmcbbyte = (uint16)fldfmcb->fmcbsmcb->GetInstLength(fldfmcb->fmcbbstr);
    }
    if ( fldfmcb->fmcbopt )
      if ( (gentype = (char *)fldfmcb->GetDescription()->get_gen_type()) && !memcmp(gentype,"PI ",3) )
        memset(gentype,' ',8);
    if ( fldfmcb->fmcbityp != T_MEMO && fldfmcb->fmcbsmcb )
      fldfmcb->fmcbesu(fldfmcb->fmcbsmcb,fldfmcb->fmcbposn,AUTO,max_aligned);
    
    if ( fldfmcb->fmcbopt )
    {
      intpos = fldfmcb->fmcbposn;
      fldfmcb->GetDescription()->SetupAttribute(intpos,extpos,netpos,AUTO,max_aligned);
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Disconnect - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Disconnect"

void dbf :: Disconnect ( )
{




}

/******************************************************************************/
/**
\brief  Get - 



\return instptr - 

\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Get"

char *dbf :: Get (int32 lindx0 )
{
  int32            diff;
  char           *instptr = NULL;
BEGINSEQ
  if ( !this || !fldfmcb || !flddata )               ERROR
    
  if ( lindx0 >= (int32)GetFMCB()->fmcbdim )         ERROR

  if ( lindx0 == AUTO )
    if ( (lindx0 = nodecur) == AUTO )
      lindx0 = 0;
  
  diff = nodecur == AUTO ? lindx0 : lindx0-nodecur;
  if ( instptr = GetArea() )
    SetArea(instptr += (GetFMCB()->fmcbbyte*diff/GetFMCB()->fmcbdim));
  nodecur = lindx0;

RECOVER
  instptr = NULL;
ENDSEQ
  return(instptr);
}

/******************************************************************************/
/**
\brief  GetDate - 



\return date_val - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDate"

dbdt dbf :: GetDate ( )
{
  dbdt       result;
BEGINSEQ
  result = fld::GetDate();
  if ( ConversionError(*this,"DATE") )               ERROR
RECOVER

ENDSEQ
  return(result);
}

/******************************************************************************/
/**
\brief  GetDateTime - 



\return datetime_val - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDateTime"

dttm dbf :: GetDateTime ( )
{
  dttm        result;
BEGINSEQ
  result = fld::GetDateTime();
  if ( ConversionError(*this,"DATETIME") )               ERROR
RECOVER

ENDSEQ
  return(result);
}

/******************************************************************************/
/**
\brief  GetDescription - 



\return fmcbptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDescription"

fmcb *dbf :: GetDescription ( )
{

  return(GetFMCB());

}

/******************************************************************************/
/**
\brief  GetDouble - 



\return dbl_value - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDouble"

double dbf :: GetDouble ( )
{
  double      result = 0;
BEGINSEQ
  result = fld::GetDouble();
  if ( ConversionError(*this,"REAL") )               ERROR
RECOVER

ENDSEQ
  return(result);
}

/******************************************************************************/
/**
\brief  GetField - 



\return dbfenty - 

\param  fldnames - Property name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetField"

dbf dbf :: GetField (char *fldnames )
{
  dbf tdbf(GetFMCB() ? GetFMCB()->fmcbsmcb : (smcb*)NULL,fldnames,GetArea());
  return(tdbf);


}

/******************************************************************************/
/**
\brief  GetHighPropertyHandle - 



\return pi_ptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHighPropertyHandle"

PropertyHandle *dbf :: GetHighPropertyHandle ( )
{

  return ( highnod ? (PropertyHandle *)&highnod : NULL);

}

/******************************************************************************/
/**
\brief  GetInt - 



\return int_val - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetInt"

int32 dbf :: GetInt ( )
{
  int32       result = 0;
BEGINSEQ
  result = fld::GetLong();
  if ( ConversionError(*this,"INT") )                ERROR
RECOVER

ENDSEQ
  return(result);
}

/******************************************************************************/
/**
\brief  GetOperationPtr - 



\return op - 

\param  expression - Expression
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetOperationPtr"

Operation **dbf :: GetOperationPtr (char *expression )
{
  Operation  **pop = NULL;
  char        *expr_string;
BEGINSEQ
  if ( !operations )                                 LEAVESEQ 
  
  operations->GoTop();
  while ( (pop = &operations->GetNext()) && *pop )
    if ( (expr_string = (*pop)->get_expression()) &&
         !strcmp(expression,expr_string) )
      break;

  if ( pop && !*pop ) 
    pop = NULL;
ENDSEQ
  return(pop);
}

/******************************************************************************/
/**
\brief  GetString - 



\return string - 

\param  string - 
\param  lsize - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *dbf :: GetString (char *string, int32 lsize )
{
  char      *ret_string;
BEGINSEQ
  switch ( fldfmcb->fmcbityp )
  {
    case T_STRING : ret_string = GetArea();
                    break;
    case T_MEMO   : ret_string = fldfmcb->fmcbrlev == R_REFR 
                             ? ((PI(mem) *)GetArea())->Get(0L)->memo
                             : GetArea();
                    break;
    default       : 
                    fld      string_fld(string,lsize);
                    string_fld = *(fld *)this;
                    ret_string = string;
                    if ( ConversionError(*this,"STRING") )  
                                                     ERROR
  }
RECOVER
  ret_string = "";
ENDSEQ
   if (ret_string ) return ret_string ;
   else return "";
}

/******************************************************************************/
/**
\brief  GetTime - 



\return time_val - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTime"

dbtm dbf :: GetTime ( )
{
  dbtm       result;
BEGINSEQ
  result = fld::GetTime();
  if ( ConversionError(*this,"TIME") )               ERROR

RECOVER

ENDSEQ
  return(result);
}

/******************************************************************************/
/**
\brief  InitResult - 



\return term - Termination code
-------------------------------------------------------------------------------
\brief  i0 - 



\param  operand1 - 
\param  operand2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical dbf :: InitResult (dbf *operand1, dbf *operand2 )
{
  logical     term = NO;
BEGINSEQ
  if ( CopyDescription(operand1->GetFMCB()) )        ERROR
  fldfmcb->fmcbvar = YES;

  AllocateArea();
  *this = *operand2;                                 SDBCERR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 



\param  dictptr - Dictionary handle
\param  scoped_name - 
\param  fldsize - Size of property
\param  fldprec - Precision of property
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitResult"

logical dbf :: InitResult (Dictionary *dictptr, char *scoped_name, uint32 fldsize, uint16 fldprec )
{
  TypeKey  tkey(dictptr,scoped_name);
  smcb    *smcbptr;
  int8     max_aligned = 1;
  logical  term        = NO;
BEGINSEQ
  SetFMCB(new fmcb(tkey.Name(),tkey.Name(),tkey.GetID(),R_DIRECT,fldsize,fldprec,1));
  fldfaloc = YES;
    
  if ( !(smcbptr = dictptr->GetSMCB(tkey)) )        SDBERR(20)
  GetDescription()->fmcbesu(smcbptr,0,AUTO,max_aligned); 
  
  SetArea(NULL);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - Termination code

\param  pi_handle - 
\param  fldnames - Property name
\param  offset - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical dbf :: Initialize (PropertyHandle &pi_handle, char *fldnames, int32 offset )
{
  smcb        *smcbptr    = pi_handle.GetCurrentTypeDef();
  void        *entry_area;
  fmcb        *fmcbptr    = NULL;
  int32         offset_int = 0;
  logical      term       = NO;
BEGINSEQ
  if ( !smcbptr || !(fmcbptr = smcbptr->SearchField(fldnames,&offset_int)) )
                                                     SDBERR(109)
  
  if ( offset_int + offset )
  {
    CopyDescription(fmcbptr);
    fldfmcb->fmcbposn += offset_int;
  }
  else
    fldfmcb = fmcbptr;

  if ( entry_area = &pi_handle.GetInstance() )
    flddata = (char *)entry_area + fldfmcb->fmcbposn;
    
  if ( offset )  
    fldfmcb->fmcbposn += offset;
  
  Connect(pi_handle.get_nodeptr());
RECOVER
  UtilityHandle::StructFieldError(fldnames,pi_handle.GetType());
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsReference - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsReference"

logical dbf :: IsReference ( )
{

  return ( (highnod && this == (dbf *) highnod ) ||
           (fldfmcb && fldfmcb->fmcbrlev == R_REFR)
            ? YES : NO );


}

/******************************************************************************/
/**
\brief  IsUnused - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsUnused"

logical dbf :: IsUnused ( )
{

  return ( !this || (!fldfmcb && !flddata) ? YES : NO );

}

/******************************************************************************/
/**
\brief  Modify - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Modify"

void dbf :: Modify ( )
{

  if ( highnod && highnod->IsWrite() )
    if ( !IsReference() )
      highnod->Modify();

}

/******************************************************************************/
/**
\brief  OwnsData - 



\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OwnsData"

logical dbf :: OwnsData ( )
{

  return(flddaloc);

}

/******************************************************************************/
/**
\brief  RemoveOperation - 



\return term - Termination code

\param  op - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveOperation"

logical dbf :: RemoveOperation (Operation *op )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this || !operations )                     LEAVESEQ
  
  if ( operations->Find(op) )
    operations->RemoveAt();

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveOperations - 



-------------------------------------------------------------------------------
\brief  DBF~ - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveOperations"

void dbf :: RemoveOperations ( )
{
  Operation    *oper;
  if ( operations )
  {
    operations->GoTop();
    while ( oper = operations->RemoveTail() )
    {
      oper->SetCallingObject(NULL);
      delete oper;
    }
    delete operations;
    operations = NULL;
  }

}

/******************************************************************************/
/**
\brief  i01 - 



\param  pibptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveOperations"

void dbf :: RemoveOperations (PropertyHandle *pibptr )
{
  Operation  **pop = NULL;

BEGINSEQ
  if ( !this || !operations )                     LEAVESEQ 
  
  DLL(Operation)    cursor(*operations);
  cursor.GoTop();
  while ( (pop = &cursor.GetNext()) && *pop )
    if ( pibptr == (*pop)->get_calling_object() ) 
    {
      cursor.GetPrev();
      delete *pop;
    }

ENDSEQ

}

/******************************************************************************/
/**
\brief  Reset - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

logical dbf :: Reset ( )
{
  logical                 term = NO;
  highnod = NULL;
  if ( !flddaloc )
    flddata = NULL;
  if ( !fldfaloc )
    fldfmcb = NULL;
  return(term);
}

/******************************************************************************/
/**
\brief  Search - 



\return curpos - 

\param  string - 
\param  curpos - 
\param  case_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Search"

int32 dbf :: Search (char *string, int32 curpos, logical case_opt )
{
  char     *sarea     = NULL;
  char     *skey      = NULL;
  char     *datarea;
  int32      maxlen;
  logical   alloc_opt = NO;
BEGINSEQ
  if ( !fldfmcb || !flddata )                        ERROR

  switch ( fldfmcb->fmcbrlev )
  {
    case R_REFR   : 
    case R_DIRECT : 
    case R_INTERN : break;
    default       : ERROR
  }
  
  switch ( fldfmcb->fmcbityp )
  {
    case T_MEMO   : datarea = (char *)((PropertyHandle *)flddata)->Get(0L).GetData();
                    maxlen  = ((PropertyHandle *)flddata)->GetSizeOf();
                    break;
    case T_CHAR   : 
    case T_CCHAR  : datarea = flddata;
                    maxlen  = fldfmcb->fmcbbyte;
                    break;
    case T_STRING : datarea = flddata;
                    maxlen  = MIN(fldfmcb->fmcbsize,strlen(flddata));
    default       : ERROR
  }
  
  if ( !datarea )                                          ERROR
  if ( curpos + strlen(string) > maxlen )                  ERROR

  if ( case_opt )
  {
    sarea = datarea+curpos;
    skey  = string;
  }  
  else
  {
    sarea = new char[maxlen-curpos+1];
    memcpy(sarea,datarea+curpos,maxlen-curpos);
    sarea[maxlen-curpos] = 0;
    gvtsupr(sarea);
    skey  = new char[strlen(string)+1];
    strcpy(skey,string);
    gvtsupr(skey);
    alloc_opt = YES;
  }  
  
  curpos = gvtussr(sarea,skey,maxlen-curpos);
RECOVER
  curpos = AUTO;

ENDSEQ
  if ( alloc_opt )
  {
    delete sarea;
    delete skey;
  }
  return(curpos);

}

/******************************************************************************/
/**
\brief  SetArea - 



\return instptr - 

\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetArea"

void *dbf :: SetArea (void *datarea )
{

  if ( this )
    nodecur = fld::SetArea((char *)datarea) ? 0 : AUTO;
  return( this ? datarea : NULL );
}

/******************************************************************************/
/**
\brief  SetDescription - 




\param  fmcbptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDescription"

void dbf :: SetDescription (fmcb *fmcbptr )
{
  fmcb      *local_fmcb;
BEGINSEQ
  if ( local_fmcb = GetDescription() )
  {
    if ( fmcbptr == local_fmcb )                     LEAVESEQ
    DelDescription();
  }
  SetFMCB(fmcbptr);

  if ( fmcbptr && !fmcbptr->fmcbopt )     // not a DBFieldDef
    SetupDescription();
ENDSEQ

}

/******************************************************************************/
/**
\brief  SetInitValue - 



\return term - Termination code

\param  init_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInitValue"

logical dbf :: SetInitValue (char *init_value )
{
  fmcb       *fmcbptr = GetFMCB();
  logical     term = NO;
BEGINSEQ
  if ( fmcbptr && init_value && *init_value &&
       ( fmcbptr->fmcbbase() || 
        (fmcbptr->fmcbsmcb && fmcbptr->fmcbsmcb->smcbstyp == ST_CODE) ) )
  {
    if ( strcmp(init_value,"(NULL)") )
    {
      if ( AllocateArea() )                          ERROR
      *(fld *)this = init_value;
    }
    GetFMCB()->fmcbinit = YES;
    nodecur = 0;
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetInstance - 



\return areaptr - 

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetInstance"

char *dbf :: SetInstance (void *instptr )
{

  (*this)(instptr);
  return(GetArea());

}

/******************************************************************************/
/**
\brief  SetTemp - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTemp"

void dbf :: SetTemp ( )
{

  if ( fldfaloc )
    fldfaloc = AUTO;

  if ( flddaloc )
    flddaloc = AUTO;

}

/******************************************************************************/
/**
\brief  SetupDescription - 



\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupDescription"

logical dbf :: SetupDescription ( )
{
  fmcb                   *fmcbptr  = fldfmcb;
  DBFieldDef             *fielddef = fmcbptr && fmcbptr->fmcbopt ? (DBFieldDef *)fmcbptr : NULL;
  int32                   intpos;
  int32                   extpos;
  int32                   netpos;
  int8                    max_aligned = 1;
  logical                 del_opt  = NO;
  logical                 term     = NO;
BEGINSEQ
  if ( !fmcbptr  )                                   ERROR
  if ( fielddef && fielddef->get_net_length() )      LEAVESEQ
  
  if ( !fielddef )
  {
    if ( del_opt = fldfaloc )
    {
      fldfmcb  = NULL;
      fldfaloc = NO;
    }

    if ( AllocDescription() )                        ERROR
    *fldfmcb = *fmcbptr;
  }
  
  intpos = fmcbptr->fmcbposn;
  extpos  = fielddef ? fielddef->get_offset_ext() : 0;
  netpos = fielddef ? fielddef->get_net_pos() : 0;
  
  if ( IsReference() )
    ((DBFieldDef *)fldfmcb)->SetupReference(intpos,extpos,netpos,1,max_aligned);
  else
    ((DBFieldDef *)fldfmcb)->SetupAttribute(intpos,extpos,netpos,1,max_aligned);
    
  if ( del_opt )
    if ( fielddef )
      delete fielddef;
    else 
      delete fmcbptr;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  dbf - 



-------------------------------------------------------------------------------
\brief  BigInt - 



\param  int64_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (int64 int64_val )
                     : fld (int64_val),
ObjectReference (NO),
  highnod(NULL),
  nodecur(0),
  operations(NULL)
{

  SetupDescription();
  AllocateArea();
  memcpy(GetArea(),&int64_val,sizeof(int32));


dbf_count++;
}

/******************************************************************************/
/**
\brief  Boolean - 



\param  logval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (logical logval )
                     : fld (logval),
ObjectReference (NO),
  highnod(NULL),
  nodecur(0),
  operations(NULL)
{

  SetupDescription();
  AllocateArea();
  *GetArea() = logval;

dbf_count++;
}

/******************************************************************************/
/**
\brief  Copy - 



\param  dbfenty_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (const dbf &dbfenty_refc )
                     : fld (),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{

  CopyDBF(*(dbf *)&dbfenty_refc);
dbf_count++;
}

/******************************************************************************/
/**
\brief  DBF_A - 



\param  fmcbptr - 
\param  datarea - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (fmcb *fmcbptr, void *datarea )
                     : fld(fmcbptr,datarea),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{

  SetupDescription();
  if ( datarea )
    nodecur = 0;
dbf_count++;
}

/******************************************************************************/
/**
\brief  Date - 



\param  date_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (dbdt date_val )
                     : fld (date_val),
ObjectReference (NO),
  highnod(NULL),
  nodecur(0),
  operations(NULL)
{

  SetupDescription();
  AllocateArea();
  memcpy(flddata,&date_val,sizeof(dbdt));  

dbf_count++;
}

/******************************************************************************/
/**
\brief  Dummy - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf ( )
                     : fld (),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{


dbf_count++;
}

/******************************************************************************/
/**
\brief  FieldDef1 - 



\param  dbfield_ptr - Property definition
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (DBFieldDef *dbfield_ptr )
                     : fld(dbfield_ptr,NULL),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{


dbf_count++;
}

/******************************************************************************/
/**
\brief  FieldDef2 - 



\param  dictptr - Dictionary handle
\param  fmcbptr - 
\param  init_string - 
\param  init_opt - 
\param  const_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (Dictionary *dictptr, fmcb *fmcbptr, char *init_string, logical init_opt, logical const_opt )
                     : fld (),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{
  smcb    *smcbptr;
  int8     max_aligned = 1;
BEGINSEQ
  SetFMCB(fmcbptr);
//  fldfaloc = YES;
    
  if ( !(smcbptr = dictptr->GetSMCB(fmcbptr->fmcbtype,fmcbptr->fmcbnsid)) )
                                                     SDBERR(20)
  fmcbptr->fmcbesu(smcbptr,0,AUTO,max_aligned); 
  fmcbptr->fmcbinit = init_opt;
  fmcbptr->fmcbcnst = const_opt;
  
  SetupDescription();
  SetInitValue(init_string);
RECOVER
UtilityHandle::StructFieldError(fmcbptr->fmcbname,fmcbptr->fmcbtype);

ENDSEQ
dbf_count++;
}

/******************************************************************************/
/**
\brief  FieldName - 



\param  dictptr - Dictionary handle
\param  scoped_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (Dictionary *dictptr, char *scoped_name )
                     : fld (),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{
  fmcb     *field_ptr;
  TypeKey   tkey(dictptr,scoped_name);
//  logical   extent;  25.1.2004, wegen Expressions
  char      type_name[ID_SIZE];
  int8      max_aligned = 1;
BEGINSEQ
//  extent = dictptr->get_extend_pi()->Get(tkey.GetKey()) ? YES : NO;
  SetFMCB(new fmcb(tkey.Name(),tkey.Name(),tkey.GetID(),R_DIRECT,UNDEF,0,1));
  fldfaloc = YES;
    
  field_ptr = GetDescription();
  TypeKey   skey(field_ptr->fmcbtype,field_ptr->fmcbnsid);
  if ( field_ptr->fmcbesu(dictptr->ProvideStructDef(skey),0,AUTO,max_aligned) )
                                                     SDBERR(20)
  SetupDescription();

RECOVER
  UtilityHandle::StructFieldError(NULL,scoped_name);
ENDSEQ
dbf_count++;
}

/******************************************************************************/
/**
\brief  Float - 



\param  dbl_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (double dbl_value )
                     : fld(dbl_value),
ObjectReference (NO),
  highnod(NULL),
  nodecur(0),
  operations(NULL)
{

  SetupDescription();
  AllocateArea();
  memcpy(GetArea(),&dbl_value,sizeof(double));  

dbf_count++;
}

/******************************************************************************/
/**
\brief  Init1 - 



\param  dictptr - Dictionary handle
\param  fldnames - Property name
\param  fldtypes - Property type
\param  fldnsid - 
\param  fldreflev - Property reference level
\param  fldsize - Size of property
\param  fldprec - Precision of property
\param  flddim - Dimension of property
\param  init_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (Dictionary *dictptr, char *fldnames, char *fldtypes, int32 fldnsid, SDB_RLEV fldreflev, uint32 fldsize, uint16 fldprec, uint32 flddim, char *init_value )
                     : fld (),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{
  smcb      *smcbptr;
  int8       max_aligned = 1;
BEGINSEQ
  AllocDescription();
//jgcc4.1.1 cast  *fldfmcb = (fmcb &)fmcb(fldnames,fldtypes,fldnsid,fldreflev,fldsize,fldprec,flddim);
  fmcb tfmcb(fldnames,fldtypes,fldnsid,fldreflev,fldsize,fldprec,flddim);
  *fldfmcb = tfmcb;
    
  if ( dictptr )
  {
    if ( !(smcbptr = dictptr->GetSMCB(fldfmcb->fmcbtype,fldfmcb->fmcbnsid)) )
                                                     SDBERR(20)
  }
  fldfmcb->fmcbrlev = ((FieldDef *)fldfmcb)->FMCBRefLevel(fldreflev,YES);
  fldfmcb->fmcbesu(smcbptr,0,AUTO,max_aligned); 
  SetupDescription();  
  
  AllocateArea();            // neu 5.4.01 fuer CNode retval aus expr.
  SetInitValue(init_value);

RECOVER
  UtilityHandle::StructFieldError(fldnames,fldtypes);

ENDSEQ
dbf_count++;
}

/******************************************************************************/
/**
\brief  Init2 - 



\param  fldnames - Property name
\param  fldtypes - Property type
\param  fldnsid - 
\param  fldreflev - Property reference level
\param  fldsize - Size of property
\param  fldprec - Precision of property
\param  flddim - Dimension of property
\param  init_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (char *fldnames, char *fldtypes, int32 fldnsid, SDB_RLEV fldreflev, uint32 fldsize, uint16 fldprec, uint32 flddim, char *init_value )
                     : fld (new DBFieldDef(fldnames,fldtypes,fldnsid,fldreflev,fldsize,fldprec,flddim,NULL,NULL,UNDEF,NULL,NULL,NULL)),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{
  int8          max_aligned = 1;
  fldfaloc = YES;
  
  fldfmcb->SetInternalType();
  fldfmcb->fmcbrlev = ((FieldDef *)fldfmcb)->FMCBRefLevel(fldreflev,YES);
  fldfmcb->fmcbesu(NULL,0,AUTO,max_aligned);
  
  SetupDescription();
  AllocateArea();            // neu 5.4.01 - kompatibel zu i11
  SetInitValue(init_value);

dbf_count++;
}

/******************************************************************************/
/**
\brief  Instance - 



\param  fmcbptr - 
\param  init_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (fmcb *fmcbptr, char *init_value )
                     : fld(fmcbptr),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{

  SetupDescription();
      
  SetInitValue(init_value);
dbf_count++;
}

/******************************************************************************/
/**
\brief  Integer - 



\param  int_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (int32 int_val )
                     : fld (int_val),
ObjectReference (NO),
  highnod(NULL),
  nodecur(0),
  operations(NULL)
{

  SetupDescription();
  AllocateArea();
  memcpy(GetArea(),&int_val,sizeof(int32));


dbf_count++;
}

/******************************************************************************/
/**
\brief  Node - 



\param  nodptr - 
\param  fldnames - Property name
\param  term_dbf - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (node *nodptr, char *fldnames, logical term_dbf )
                     : fld(nodptr->GetCurrentTypeDef(),
    fldnames,nodptr->GetArea()),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{

BEGINSEQ
  if ( !GetFMCB() )                                  SDBERR(109)
  
  Connect(nodptr);
  
  if ( fldfaloc && term_dbf )
    fldfaloc = AUTO;

RECOVER
  UtilityHandle::StructFieldError(fldnames,nodptr->GetType());

ENDSEQ
dbf_count++;
}

/******************************************************************************/
/**
\brief  PH - 



\param  pi_handle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (PropertyHandle &pi_handle )
                     : fld (),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{
  DBFieldDef     *field_ptr;

  SetFMCB(NULL);
  
  if ( &pi_handle && pi_handle.get_nodeptr() )
  {
    field_ptr  = new DBFieldDef();
    *field_ptr = *pi_handle.GetDescription();
    SetFMCB(field_ptr);
    fldfaloc = YES;
    
    if ( field_ptr->fmcbsmcb = pi_handle.GetStructDef() )
      field_ptr->fmcbityp = (int16)field_ptr->fmcbsmcb->smcbityp;
//  field_ptr->fmcbsize = sizeof(PropertyHandle);

    if ( IsReference() )
      SetArea((char *)&pi_handle);
    else
      SetArea((char *)pi_handle.GetInstance().GetData());
  }

dbf_count++;
}

/******************************************************************************/
/**
\brief  SizedString - 



\param  string - 
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (char *string, uint16 len )
                     : fld (),
ObjectReference (NO),
  highnod(NULL),
  nodecur(0),
  operations(NULL)
{
  static  fmcb  *strfmcb = fmcb::GetStaticFMCB(T_STRING);
  fmcb          *fmcbptr = NULL;    

  AllocDescription();
  *fldfmcb = *strfmcb;
  fmcbptr = GetDescription();
  fmcbptr->fmcbsize = (fmcbptr->fmcbbyte = len) -1;
  
  SetupDescription();
  if ( string )
    SetArea(string);
  else
    AllocateArea();


dbf_count++;
}

/******************************************************************************/
/**
\brief  String - 



\param  string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (char *string )
                     : fld (),
ObjectReference (NO),
  highnod(NULL),
  nodecur(0),
  operations(NULL)
{
  static     fmcb     *strfmcb = fmcb::GetStaticFMCB(T_STRING);

  AllocDescription();
  *fldfmcb = *strfmcb;
  fldfmcb->fmcbbyte = (fldfmcb->fmcbsize = string ? strlen(string) : 255) + 1;
  
  SetupDescription();
  AllocateArea();
  if ( string )
    memcpy(GetArea(),string,fldfmcb->fmcbbyte);
  else
    fldfmcb->fmcbvar = YES;

dbf_count++;
}

/******************************************************************************/
/**
\brief  Structure - 



\param  smcbptr - Pointer to general structure definition
\param  fldnames - Property name
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (smcb *smcbptr, char *fldnames, void *instptr )
                     : fld(),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{
  int32         offset    = 0;
  DBFieldDef  *field_def = NULL;
BEGINSEQ
  if ( !smcbptr ||
       !(fldfmcb = smcbptr->SearchField(fldnames,&offset)) )
                                                     SDBERR(109)
  if ( offset )
  {  
    field_def  = new DBFieldDef();
    if ( fldfmcb->fmcbopt )
      field_def->CopyDescription(*fldfmcb->GetDescription()); 
    else
      *(fmcb *)field_def = *fldfmcb;
    field_def->fmcbposn += offset;
    SetFMCB(field_def);
    fldfaloc = YES;
  }
  
  if ( instptr )
  {
    flddata = (char *)instptr + fldfmcb->fmcbposn;
    nodecur = 0;
  }
RECOVER
  UtilityHandle::StructFieldError(fldnames,smcbptr->smcbname);
ENDSEQ
dbf_count++;
}

/******************************************************************************/
/**
\brief  Time - 



\param  time_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (dbtm time_val )
                     : fld (time_val),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{

  SetupDescription();
  AllocateArea();
  memcpy(flddata,&time_val,sizeof(dbtm));

dbf_count++;
}

/******************************************************************************/
/**
\brief  i14 - 



\param  smcbptr - Pointer to general structure definition
\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbf"

     dbf :: dbf (smcb *smcbptr, void *instptr )
                     : fld (),
ObjectReference (NO),
  highnod(NULL),
  nodecur(AUTO),
  operations(NULL)
{

BEGINSEQ
  if ( !smcbptr )                                    SDBERR(20)
  
  AllocDescription();
//jgcc4.1.1 cast  *fldfmcb = (fmcb &)fmcb(smcbptr);
  fmcb tfmcb(smcbptr);
  *fldfmcb = tfmcb;
  
  SetupDescription();
  SetArea((char *)instptr);
  if ( instptr )
    nodecur = 0;
RECOVER

ENDSEQ
dbf_count++;
}

/******************************************************************************/
/**
\brief  dbffmcbc - 



\return term - Termination code

\param  dbhandle - Database handle
\param  fldnames - Property name
\param  fldtypes - Property type
\param  fldnsid - 
\param  fldrlev - 
\param  fldsize - Size of property
\param  fldprec - Precision of property
\param  flddim - Dimension of property
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "dbffmcbc"

logical dbf :: dbffmcbc (DBHandle *dbhandle, char *fldnames, char *fldtypes, int32 fldnsid, int16 fldrlev, uint32 fldsize, uint16 fldprec, uint32 flddim )
{
  smcb     *smcbptr;
  int8      max_aligned = 1;
  logical   term = NO;

BEGINSEQ
  if ( !(smcbptr = dbhandle->GetSMCB(fldtypes,fldnsid)) )    SDBCERR

  if ( AllocDescription() )                          ERROR
//jgcc4.1.1  *fldfmcb = (fmcb &)fmcb(fldnames,fldtypes,fldnsid,fldrlev,fldsize,fldprec,flddim);
  fmcb tfmcb(fldnames,fldtypes,fldnsid,fldrlev,fldsize,fldprec,flddim);
  *fldfmcb = tfmcb;
  
  fldfmcb->fmcbesu(smcbptr,UNDEF,AUTO,max_aligned);

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  operator() - 



\return dbfenty - 

\param  instptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator()"

dbf &dbf :: operator() (void *instptr )
{
  int32       lindx0 = nodecur;
  SetArea(NULL);
  
  if ( fldfmcb && instptr )
  {
    SetArea((char *)instptr + fldfmcb->fmcbposn);
    if ( nodecur > 0 )
    {
      nodecur = 0;
      Get(lindx0);
    }
  }  
  
  return(*this);


}

/******************************************************************************/
/**
\brief  operator= - 



\return dbfref - 
-------------------------------------------------------------------------------
\brief  DBFASN - 



\param  fldenty - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

dbf &dbf :: operator= (fld &fldenty )
{

BEGINSEQ
  *((fld *)this) = fldenty;                            SOSCERR    

RECOVER
  ConversionError(fldenty,fldfmcb ? fldfmcb->fmcbtype : NULL);
ENDSEQ
  return(*this);

}

/******************************************************************************/
/**
\brief  i2 - 



\param  dbfenty_refc - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

dbf &dbf :: operator= (const dbf &dbfenty_refc )
{
  logical   connect = GetArea() ? NO : YES;
  if ( !GetFMCB() )
  {
    if ( dbfenty_refc.fldfaloc )
      CopyDescription(dbfenty_refc.GetFMCB());
    else
      fldfmcb = dbfenty_refc.GetFMCB();
  }

  *this = *(fld *)&dbfenty_refc;

  if ( !GetArea() && highnod )
    Disconnect();
  else
    if ( connect && !flddaloc && dbfenty_refc.highnod ) // das klappt nicht, wenn die Instanz selbst eine Referenz ist!!
      Connect(dbfenty_refc.highnod);

  return (*this);
}

/******************************************************************************/
/**
\brief  ~dbf - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~dbf"

     dbf :: ~dbf ( )
{
  Operation    *oper;
  Disconnect();
  
  if ( flddaloc && fldfmcb && fldfmcb->fmcbrlev == R_REFR && flddata )
    ((PropertyHandle *)flddata)->Close();
    
  DelDescription();

  RemoveOperations();
dbf_count--;
}


