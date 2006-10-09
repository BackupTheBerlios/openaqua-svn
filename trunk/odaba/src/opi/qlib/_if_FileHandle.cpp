/********************************* Interface Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|08:38:31,48}|(REF)
\class    FileHandle

\brief    


\date     $Date: 2006/03/13 08:38:38,00 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    IF_Class
#define    OBJ_ID  "_IF_FileHandle"

#include  <pdefault.h>
#include  <s_if_FileHandle.hpp>


#undef     MOD_ID
#define    MOD_ID  "AlignText"

logical __cdecl AlignText                               ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype)
{
  FileHandle       *CO      = (FileHandle *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  static DBFieldDef flddef;
  TextAlignment     align_type = TA_undefined;
  uint16            indent  = 0;
  int32             size    = 80;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                    ERROR 
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->SetDescription(flddef.InitField(T_LO,NO,NO,NO));
         break;
         
    case ET_First      : 
    
         *retval = YES;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 4 : align_type = (TextAlignment)(*parmlist)[3]->GetInt();
           case 3 : indent     = (*parmlist)[2]->GetInt();
           case 2 : size       = (*parmlist)[1]->GetInt();
           case 1 : *retval = CO->AlignText((*parmlist)[0]->GetString(),size,indent,align_type);
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
#define    MOD_ID  "Close"

logical __cdecl Close                                   ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype)
{
  FileHandle       *CO      = (FileHandle *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  static DBFieldDef flddef;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                     ERROR 
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->SetDescription(flddef.InitField(T_LO,NO,NO,NO));
         break;
         
    case ET_First      : 
    
         *retval = YES;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->Close();
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
#define    MOD_ID  "CurrentLine"

logical __cdecl CurrentLine                             ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype)
{
  FileHandle       *CO      = (FileHandle *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  static DBFieldDef flddef;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                     ERROR 
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->SetDescription(flddef.InitField(T_INT,NO,NO,NO));
         break;
         
    case ET_First      : 
    
         *retval = 0;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->CurrentLine();
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
#define    MOD_ID  "IsOpened"

logical __cdecl IsOpened                                ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype)
{
  FileHandle       *CO      = (FileHandle *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  static DBFieldDef flddef;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                    ERROR 
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->SetDescription(flddef.InitField(T_LO,NO,NO,NO));
         break;
         
    case ET_First      : 
    
         *retval = YES;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 0 : *retval = CO->IsOpened();
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
#define    MOD_ID  "LinePosition"

logical __cdecl LinePosition                            ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype)
{
  FileHandle       *CO      = (FileHandle *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  static DBFieldDef flddef;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                    ERROR 
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->SetDescription(flddef.InitField(T_LO,NO,NO,NO));
         break;
         
    case ET_First      : 
    
         *retval = YES;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 1 : 
           case 2 : *retval = CO->LinePosition((*parmlist)[0]->GetInt(),
                                               parmcnt > 1 ? (*parmlist)[1]->GetInt() : AUTO);
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
#define    MOD_ID  "Open"

logical __cdecl Open                                    ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype)
{
  FileHandle       *CO      = (FileHandle *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  static DBFieldDef flddef;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                     ERROR 
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->SetDescription(flddef.InitField(T_LO,NO,NO,NO));
         break;
         
    case ET_First      : 
    
         *retval = YES;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 1 :
           case 2 : *retval = CO->Open((*parmlist)[0]->GetString(),
                                       parmcnt > 1 ? (PIACC)(*parmlist)[1]->GetInt() : PI_Write);
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
#define    MOD_ID  "Out"

logical __cdecl Out                                     ( DBField *co, DBField *retval, ParmList *parmlist, char *impname, ExecutionTypes exectype)
{
  FileHandle       *CO      = (FileHandle *)co->GetArea();
  int               parmcnt = parmlist ? parmlist->GetSize() : 0;
  static DBFieldDef flddef;
  logical           term    = NO;
BEGINSEQ
  if ( !retval )                                      ERROR 
  
  switch ( exectype )
  {
    case ET_Initialize : 
         
         retval->SetDescription(flddef.InitField(T_LO,NO,NO,NO));
         break;
         
    case ET_First      : 
    
         *retval = YES;
         if ( !co->IsSelected() )                    ERROR
         switch ( parmcnt )   
         {
           case 1 : 
           case 2 : 
           case 3 : 
           case 4 : 
           case 5 : 
           case 6 : 
           case 7 : 
           case 8 : 
           case 9 : 
           case 10: 
           case 11: 
           case 12: 
           case 13: 
           case 14: 
           case 15: 
           case 16: 
           case 17: *retval = CO->Out((*parmlist)[0]->GetString(),
                                      parmcnt > 1  ? (*parmlist)[1]->GetString() : NULL,
                                      parmcnt > 2  ? (*parmlist)[2]->GetString() : NULL,
                                      parmcnt > 3  ? (*parmlist)[3]->GetString() : NULL,
                                      parmcnt > 4  ? (*parmlist)[4]->GetString() : NULL,
                                      parmcnt > 5  ? (*parmlist)[5]->GetString() : NULL,
                                      parmcnt > 6  ? (*parmlist)[6]->GetString() : NULL,
                                      parmcnt > 7  ? (*parmlist)[7]->GetString() : NULL,
                                      parmcnt > 8  ? (*parmlist)[8]->GetString() : NULL,
                                      parmcnt > 9  ? (*parmlist)[9]->GetString() : NULL,
                                      parmcnt > 10 ? (*parmlist)[10]->GetString() : NULL,
                                      parmcnt > 11 ? (*parmlist)[11]->GetString() : NULL,
                                      parmcnt > 12 ? (*parmlist)[12]->GetString() : NULL,
                                      parmcnt > 13 ? (*parmlist)[13]->GetString() : NULL,
                                      parmcnt > 14 ? (*parmlist)[14]->GetString() : NULL,
                                      parmcnt > 15 ? (*parmlist)[15]->GetString() : NULL,
                                      parmcnt > 16 ? (*parmlist)[16]->GetString() : NULL);
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

