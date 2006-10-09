/********************************* Class Source Code ***************************/
/**
\package  OPS - 
\class    ENUM_ValueList

\brief    


\date     $Date: 2006/06/05 13:41:22,15 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ENUM_ValueList"

#include  <pops7.h>
#ifndef   GSRT_ENUM_Value_HPP
#define   GSRT_ENUM_Value_HPP
#include  <sENUM_Value.hpp>
#include  <sGSRT.h>
#endif
#include  <sDBExtend.hpp>
#include  <sDBStructDef.hpp>
#include  <sENUM_Value.hpp>
#include  <sPropertyHandle.hpp>
#include  <sENUM_ValueList.hpp>


/******************************************************************************/
/**
\brief  Access - 


\return instptr - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  lindx0 - 
\param  string - 
\param  maxlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Access"

char *ENUM_ValueList :: Access (int32 lindx0, char *string, int32 maxlen )
{

// this function does not really what it is intended to do. Instead of 
// accessing entry indx0 in the list, it returns the code for the entry
// having indx0 as code!!

  return( GetString(lindx0,string,maxlen) );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  keyptr - 
\param  int_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Access"

char *ENUM_ValueList :: Access (char *keyptr, int32 &int_ref )
{
  char          cur_order = 0;
  ENUM_Value   *eval      = NULL;


BEGINSEQ
// this function does not really what it is intended to do. Instead of 
// returning entry indx0 in the list, it returns the code for the entry
// having indx0 as code!!

  int_ref = CS_U;
  if ( !this )                                      ERROR

  value_list->Lock(YES);
  cur_order = order;
  ChangeOrder(CS_STR);

  if ( eval = GetEntry(keyptr) )  
    int_ref = eval->code;
    
  ChangeOrder(cur_order);
  value_list->Unlock();

RECOVER

ENDSEQ
  return((char *)&int_ref);
}

/******************************************************************************/
/**
\brief  AddValue - 


\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  val_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddValue"

logical ENUM_ValueList :: AddValue (PropertyHandle *val_ph )
{
  logical     term = NO;
BEGINSEQ
  if ( !val_ph->IsPositioned() )                           SDBERR(99)

  ENUM_Value  eval(val_ph);
  AddValue(&eval);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  cval - 
\param  cname - 
\param  btype - 
\param  clabel - 
\param  ctitle - 
\param  cdescr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddValue"

logical ENUM_ValueList :: AddValue (int32 cval, char *cname, char *btype, char *clabel, char *ctitle, char *cdescr )
{
  ENUM_Value eval(cval,cname,btype,clabel,ctitle,cdescr);
  logical    term    = NO;
BEGINSEQ
  if ( !cname )                                   SDBERR(99)

  AddValue(&eval);   

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 


\param  eval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddValue"

logical ENUM_ValueList :: AddValue (ENUM_Value *eval )
{
  int32       count = 0;
  logical     term = NO;
  ChangeOrder(CS_STR);
  
  if ( !value_list )
    count = 3;
  else if ( value_list->srtcnt() == value_list->srtmax() )
    count = value_list->srtcnt()+3;
  if ( count )
    Resize(count);
    
  value_list->AddEntry(eval);
  eval->Clear(); 
   

  return(term);
}

/******************************************************************************/
/**
\brief  ChangeOrder - 


\return term - 

\param  sortopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ChangeOrder"

logical ENUM_ValueList :: ChangeOrder (char sortopt )
{
  logical     term = NO;
BEGINSEQ
  if ( order == sortopt )                           LEAVESEQ
  if ( !value_list )                                ERROR

  switch ( sortopt )
  {
    case CS_VAL : value_list->srtsor(1+offsetof(ENUM_Value,code),4,'I');
                  break;
    case CS_STR : value_list->srtsor(1+offsetof(ENUM_Value,name),ID_SIZE,'C');
                  break;
    case CS_TYP : value_list->srtsor(1+offsetof(ENUM_Value,type),ID_SIZE,'v');
                  break;
    case CS_DSP : value_list->srtsor(1+offsetof(ENUM_Value,display_name),128,'v');
                  break;
    case CS_TIT : value_list->srtsor(1+offsetof(ENUM_Value,title),512,'v');
                  break;
    default     :                                    SDBERR(99)
  }

  order = sortopt;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ENUM_ValueList - 


-------------------------------------------------------------------------------
\brief  i00 - 


\param  val_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ENUM_ValueList"

     ENUM_ValueList :: ENUM_ValueList (PropertyHandle *val_ph )
                     : acc(YES),
  order(UNDEF),
  value_list(NULL)
{

BEGINSEQ
  memset(basetype,' ',sizeof(basetype));
  if ( Initialize(val_ph) )                                           ERROR

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i01 - 


\param  enum_list - 
\param  btype - 
\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ENUM_ValueList"

     ENUM_ValueList :: ENUM_ValueList (ENUM_Value **enum_list, char *btype, int32 count )
                     : acc(YES),
  order(UNDEF),
  value_list(NULL)
{

  memset(basetype,' ',sizeof(basetype));
  if ( btype )
    gvtxstb(basetype,btype,sizeof(basetype));
  Initialize(enum_list,count);

}

/******************************************************************************/
/**
\brief  i02 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ENUM_ValueList"

     ENUM_ValueList :: ENUM_ValueList ( )
                     : acc(YES),
  order(UNDEF),
  value_list(NULL)
{

  memset(basetype,' ',sizeof(basetype));


}

/******************************************************************************/
/**
\brief  GetCode - 


\return int_val - 

\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCode"

int32 ENUM_ValueList :: GetCode (char *keyptr )
{
  ENUM_Value   *eval = NULL;
  int32         code = CS_U;
BEGINSEQ
  if ( !this )                                      ERROR
  
  value_list->Lock(YES);
  if ( eval = value_list->GetEntry(keyptr) )
    code = eval->code;
  value_list->Unlock();

RECOVER
  code = CS_U;
ENDSEQ
  return(code);
}

/******************************************************************************/
/**
\brief  GetCount - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCount"

int32 ENUM_ValueList :: GetCount ( )
{

  return( value_list ? value_list->srtcnt() : 0 );

}

/******************************************************************************/
/**
\brief  GetCurrentIndex - 


\return indx0 - 

\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentIndex"

int32 ENUM_ValueList :: GetCurrentIndex (char *keyptr )
{
  char          buffer[ID_SIZE];
  int32         indx0 = AUTO;
  if ( order == CS_STR )
    keyptr = gvtxstb(buffer,keyptr,ID_SIZE);

  indx0 = value_list->srtssr(keyptr) - 1;

  return(indx0);
}

/******************************************************************************/
/**
\brief  GetEntry - 


\return eval - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  lindx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

ENUM_Value *ENUM_ValueList :: GetEntry (int32 lindx0 )
{
  ENUM_Value   *eval;
  eval = value_list->GetEntry(lindx0+1);

  return(eval);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  keyptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEntry"

ENUM_Value *ENUM_ValueList :: GetEntry (char *keyptr )
{
  char          buffer[ID_SIZE];
  ENUM_Value   *eval;
  if ( order == CS_STR )
    keyptr = gvtxstb(buffer,keyptr,ID_SIZE);
    
  eval = value_list->GetEntry(keyptr);

  return(eval);
}

/******************************************************************************/
/**
\brief  GetKeyLength - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyLength"

int32 ENUM_ValueList :: GetKeyLength ( )
{
  ENUM_Value  *eval = NULL;
  return( sizeof(eval->code) );


}

/******************************************************************************/
/**
\brief  GetName - 


\return string - 

\param  eval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *ENUM_ValueList :: GetName (ENUM_Value *eval )
{
  char           *string = NULL;
BEGINSEQ
  if ( !eval )                                       ERROR

  result.SetString(eval->name,ID_SIZE);
  string = result;


RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetSortKey - 


\return string - 

\param  eval - 
\param  sortopt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKey"

char *ENUM_ValueList :: GetSortKey (ENUM_Value *eval, char sortopt )
{
  char           *string = NULL;
BEGINSEQ
  if ( !eval )                                       ERROR

  if ( !sortopt )
    sortopt = order;

  switch ( sortopt )
  {
    case CS_VAL : string = (char *)&eval->code;
                  break;
    case CS_STR : string = GetName(eval);
                  break;
    case CS_TYP : string = eval->type;
                  break;
    case CS_DSP : string = eval->display_name;
                  break;
    case CS_TIT : string = eval->title;
                  break;
    default     :                                    SDBERR(99)
  }

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetSortKeyLength - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSortKeyLength"

int32 ENUM_ValueList :: GetSortKeyLength ( )
{
  int32        klen = 0;
  ENUM_Value  *eval = NULL;
BEGINSEQ
  switch ( order )
  {
    case CS_VAL : klen = sizeof(eval->code);
                  break;
    case CS_STR : klen = sizeof(eval->name);
                  break;
    case CS_TYP : klen = 128;
                  break;
    case CS_DSP : klen = 128;
                  break;
    case CS_TIT : klen = 512;
                  break;
    default     :                                    SDBERR(99)
  }

RECOVER
  klen = 0;
ENDSEQ
  return(klen);
}

/******************************************************************************/
/**
\brief  GetString - 


\return string - 

\param  int_val - 
\param  string - 
\param  maxlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *ENUM_ValueList :: GetString (int32 int_val, char *string, int32 maxlen )
{
  char          cur_order = 0;
  char         *str       = NULL;
  ENUM_Value   *eval      = NULL;
BEGINSEQ
  if ( !this || !string || maxlen <= 0 )            ERROR
  
  memset(string,0,maxlen);
  
  value_list->Lock(YES);
  cur_order = order;
  ChangeOrder(CS_VAL);

  if ( eval = value_list->GetEntry((char *)&int_val) ) 
    if ( str = GetSortKey(eval,cur_order) )
      strncpy(string,str,maxlen-1);

  ChangeOrder(cur_order);
  value_list->Unlock();

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  HasValues - 


\return cond - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasValues"

logical ENUM_ValueList :: HasValues ( )
{

  return( value_list ? value_list->srtcnt() > 0 : NO);

}

/******************************************************************************/
/**
\brief  InitValueList - 


\return term - 

\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitValueList"

logical ENUM_ValueList :: InitValueList (int32 count )
{
  logical     term = NO;
BEGINSEQ
  if ( count <= 0 )                                 LEAVESEQ
  
  if ( !value_list )
    value_list = new GSRT(ENUM_Value)(count,sizeof(ENUM_Value),4,1+offsetof(ENUM_Value,code),'I',YES);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  val_ph - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ENUM_ValueList :: Initialize (PropertyHandle *val_ph )
{
  int32       indx0 = 0;
  logical     term = NO;
BEGINSEQ
  if ( !val_ph )                                   ERROR
  
  Resize(val_ph->GetCount());
  
  while( val_ph->Get(indx0++) )
    AddValue(val_ph);
    
  ChangeOrder(CS_STR);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  enum_list - 
\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical ENUM_ValueList :: Initialize (ENUM_Value **enum_list, int32 count )
{
  int32     indx0 = 0;
  logical   term = NO;
  Resize(count);
  
  if ( enum_list )
  { 
    while( indx0 < count )
      AddValue(enum_list[indx0++]);
  
    ChangeOrder(CS_STR);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  LocateKey - 


\return indx0 - 

\param  keyptr - 
\param  exact - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateKey"

int32 ENUM_ValueList :: LocateKey (char *keyptr, logical exact )
{
  char            buffer[ID_SIZE];
  int32           indx0 = 0;
BEGINSEQ
  if ( !value_list )                                ERROR

  if ( order == CS_STR )
    keyptr = gvtxstb(buffer,keyptr,ID_SIZE);

  if ( !(indx0 = value_list->srtbsr(keyptr)) )       ERROR
  if ( exact && value_list->stscerr() )             ERROR
  
  indx0 -= 1; // this index is relative 1
RECOVER
  indx0 = 0;
ENDSEQ
  return(indx0);
}

/******************************************************************************/
/**
\brief  NextCode - 


\return code - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextCode"

int32 ENUM_ValueList :: NextCode ( )
{
  ENUM_Value   *eval;
  int32         count;
  int32         code = 1;
BEGINSEQ
  if ( (count = GetCount()) <= 0 )                   LEAVESEQ
  
  ChangeOrder(CS_VAL);
  eval = GetEntry(count-1);
  
  code = eval->code + 1;

ENDSEQ
  return(code);
}

/******************************************************************************/
/**
\brief  Resize - 


\return term - 

\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Resize"

logical ENUM_ValueList :: Resize (int32 count )
{
  logical     term = NO;
  if ( !value_list )
    InitValueList(count);
  else if ( count > value_list->srtmax() )
    value_list->srtsch(count);

  return(term);
}

/******************************************************************************/
/**
\brief  ~ENUM_ValueList - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ENUM_ValueList"

     ENUM_ValueList :: ~ENUM_ValueList ( )
{
  int32             indx0 = 0;
  ENUM_Value       *eval;
  if ( value_list )
  {
    while ( eval = GetEntry(indx0++) )
      eval->ReleaseEntry();
   
    delete value_list; 
    value_list = NULL;
  }

}


