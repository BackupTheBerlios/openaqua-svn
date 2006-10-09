/********************************* Interface Class Source Code ***************************/
/**
\package  OPA - 
\class    SystemClass

\brief    


\date     $Date: 2006/08/25 14:41:31,00 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_SystemClass"

#include  <popa7.h>
#include  <s_if_SystemClass.hpp>


#undef     MOD_ID
#define    MOD_ID  "Date"

logical __cdecl Date( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  dbdt              curdate;
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  static DBFieldDef flddef;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                    ERROR 
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->SetDescription(flddef.InitField(T_DATE,NO,YES,NO));
         break;
         
    case ET_First      : 
    
         *retval = dbdt();
         switch ( parmcnt )   
         {
           case 0  : curdate.SetDate();
                     *retval = curdate;
                     break;
           default : ERROR
         }
         break;
         
    case ET_Next       :
    default            : 
         
         ERROR;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "GetSYSDB"

logical __cdecl GetSYSDB( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  static DBFieldDef flddef;
  logical           term    = NO;

BEGINSEQ
  if ( !retval ||  !sdbuptr )                        ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : 
      
         retval->SetDescription(flddef.InitField("DatabaseHandle",sdbuptr->sdbusys->dbhandle.GetStructDef("DatabaseHandle"),NO,YES,NO));
         break;
    
    case ET_First      : 
      
         if ( !retval->ProvideArea() )               ERROR
         *((DatabaseHandle *)retval->GetArea()) = DatabaseHandle();
         
         switch ( parmcnt )   
         {
           case 0 : if ( !sdbuptr )                  ERROR
                    *((DatabaseHandle *)retval->GetArea()) = sdbuptr->sdbusys->dbhandle;
                    break;
           default: ERROR
         }
         break;
     
    case ET_Next       :
      
         break;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "Message"

logical __cdecl Message( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  int                parmcnt  = parmlist ? parmlist->GetSize() : 0;
  char              *string;
  static DBFieldDef  flddef;
  logical            term     = NO;
BEGINSEQ
  if ( !retval )                                  ERROR
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->SetDescription(flddef.InitField(T_LO,NO,YES,NO));
         break;
         
    case ET_First      : 
    
         *retval = YES;
         switch ( parmcnt )   
         {
           case 1 : SDBError().ResetErrorVariables();
                    string = (*parmlist)[0]->GetString();
                    ReplaceControlSequences(string,UNDEF,NO);
                    *retval = SDBError().DisplayMessage(AUTO,string);
                    break;
           default: ERROR
         }
         break;
    
    case ET_Next       :
    default            : 
         
         ERROR;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}


#undef     MOD_ID
#define    MOD_ID  "Time"

logical __cdecl Time( PropertyHandle *co, PropertyHandle *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype )
{
  dbtm              curtime;
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  static DBFieldDef flddef;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                       ERROR  
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->SetDescription(flddef.InitField(T_TIME,NO,YES,NO));
         break;
         
    case ET_First      : 
    
         *retval = dbtm();
         switch ( parmcnt )   
         {
           case 0 : curtime.SetTime();
                    *retval = curtime;
                    break;
           default: ERROR
         }
         break;
         
    case ET_Next       :
    default            : 
         
         ERROR;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

