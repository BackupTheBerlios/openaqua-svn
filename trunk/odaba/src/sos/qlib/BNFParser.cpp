/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    BNFParser

\brief    Parser for BNF strings
          A  string  according  to  a  given  BNF syntax is based on a (top) BNF
          symbol.  You may  derive a  specific BNF  parsers for each type of BNF
          you  want to  support. The  BNF is  defined in the constructor for the
          BNF  parser. Any number of spaces is  allowed between symbols in a BNF
          but  not required. Spaces are usually considered as separators between
          symbols. 
          BNF  parsers can be  referenced as symbols  in other BNF symbols. This
          allows  defining  common  BNF  symbols  e.g.  for  name and number (as
          BNFStandardSymbold).  You may  create a  hierarchy consisting of a BNF
          tree  by  passing  the  parent  (the  more  complex definition) to the
          referenced BNF or by constructing objects for referenced BNF parsers.

\date     $Date: 2006/08/27 18:20:20,50 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BNFParser"

#include  <pdefault.h>
#ifndef   DLL_BNFSymbol_HPP
#define   DLL_BNFSymbol_HPP
#include  <sBNFSymbol.hpp>
#include  <sDLL.h>
#endif
#include  <sBNFData.hpp>
#include  <sBNFElmTokens.hpp>
#include  <sBNFParser.hpp>
#include  <sBNFSymbol.hpp>
#include  <sEntryPool.hpp>
#include  <sBNFParser.hpp>


/******************************************************************************/
/**
\brief  AddSymbol - 




\param  bsymbol - BNF Symbol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddSymbol"

void BNFParser :: AddSymbol (BNFSymbol *bsymbol )
{

  if ( this )
  {
    if ( first_referenced )
    {
      symbols.Find(first_referenced);
      symbols.InsertBefore(bsymbol);
    }
    else
      symbols.AddTail(bsymbol);
  }



}

/******************************************************************************/
/**
\brief  Analyze - Analyse string

        The  function analyses  the string  and creates  a hierarchy of BNF data
        elements.  Each BNF  data element  refers to  the string, that describes
        the  data  element  and  to  the  symbol  or  token defined for the data
        element.
        The  function will parse  the string according  to the syntax defined in
        the BNF (top-aymbol) or according to a given symbol of the syntax.

\return bdata - Pointer to BNF Node
-------------------------------------------------------------------------------
\brief  i00 - 



\param  string - String value
\param  skip_sep - Skip separators
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Analyze"

BNFData *BNFParser :: Analyze (char *string, logical skip_sep )
{

  return ( AnalyzeSymbol(this,string,skip_sep) );


}

/******************************************************************************/
/**
\brief  i01 - 



\param  string - String value
\param  symbol - Symbol name
\param  skip_sep - Skip separators
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Analyze"

BNFData *BNFParser :: Analyze (char *string, char *symbol, logical skip_sep )
{
  BNFData            *bdata = NULL;
  BNFSymbol          *bsymbol;
BEGINSEQ
  bsymbol = !symbol || !*symbol ? this : GetSymbol(symbol);
    
  SOSEV1(symbol ? symbol : "(NULL)", UNDEF);
  if ( !bsymbol )                                    SOSERR(21)
 
  bdata = AnalyzeSymbol(bsymbol,string,skip_sep);

RECOVER
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  AnalyzeFile - 



\return bdata - Pointer to BNF Node
-------------------------------------------------------------------------------
\brief  i00 - 



\param  path - Complete path
\param  skip_sep - Skip separators
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AnalyzeFile"

BNFData *BNFParser :: AnalyzeFile (char *path, logical skip_sep )
{

  return ( AnalyzeFile(path,NULL,skip_sep) );


}

/******************************************************************************/
/**
\brief  i01 - 



\param  path - Complete path
\param  symbol - Symbol name
\param  skip_sep - Skip separators
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AnalyzeFile"

BNFData *BNFParser :: AnalyzeFile (char *path, char *symbol, logical skip_sep )
{
  BNFData            *bdata;
BEGINSEQ
  ReleaseExpression();
  
  filread(path,(void **)&expression);
  
  if ( !(bdata = Analyze(expression,symbol,skip_sep)) )    ERROR
RECOVER
  ReleaseExpression();
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  AnalyzeSymbol - 



\return bdata - Pointer to BNF Node

\param  bsymbol - BNF Symbol
\param  string - String value
\param  skip_sep - Skip separators
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AnalyzeSymbol"

BNFData *BNFParser :: AnalyzeSymbol (BNFSymbol *bsymbol, char *string, logical skip_sep )
{
  BNFData            *bdata;
  logical             term = NO;
BEGINSEQ
  res_lock.ILock();
  
  bdata = new BNFData(this,string,UNDEF);
  ResetLastError();
  ResetError();
  
  if ( skip_sep )
    bdata->SkipSpaces();
        
  if ( !(term = bsymbol->Analyze(bdata,YES) > 2) )
  {
    bdata->UpdatePosition(skip_sep);
    bdata->SetLength(UNDEF);
    if ( bdata->CurrentToken() )
      term = YES;
  }

  if ( term )
  {
    GenerateError(bdata); 
    PrintError();                                  
    ERROR
  }

RECOVER
  delete bdata;
  bdata = NULL;
ENDSEQ
  res_lock.IUnlock();
  return(bdata);
}

/******************************************************************************/
/**
\brief  BNFParser - 




\param  names - Name
\param  bs_parent - Parent parser
\param  skip_new_line - New line as separator
\param  term_opt - Terminate symbol
\param  trace_path - Trace file location
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFParser"

     BNFParser :: BNFParser (char *names, BNFParser *bs_parent, logical skip_new_line, logical term_opt, char *trace_path )
                     : BNFSymbol (bs_parent,names,term_opt),
  symbols(),
  elementary_tokens(),
  data_pool(NULL),
  err_position(NULL),
  first_referenced(NULL),
  skip_nl(skip_new_line),
  trace_file(NULL),
  last_error(NULL),
  expression(NULL),
  init_comment(NULL),
  res_lock(YES)
{

  if ( bs_parent )
  {
    bs_parent->RemoveSymbol(this);
    bs_parent->get_sub_parser().AddTail(this);
  }
    
  if ( !trace_path )
    trace_path = GetSysVariable("BNFTrace");
  if ( trace_path && *trace_path )
    trace_file = fopen(trace_path,"w");
    
  if ( !top_symbol )
  {
    top_symbol = this;
    InitCTokens();
    data_pool = new EntryPool(sizeof(BNFData),256);  
  }
  else
  {
    elementary_tokens = top_symbol->elementary_tokens;
    data_pool         = top_symbol->data_pool;
  }


}

/******************************************************************************/
/**
\brief  Check - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical BNFParser :: Check ( )
{
  BNFExpression      *bexpressions[EXP_VECT_SIZE];
  BNFSymbol          *bsymbol;
  int                 count;
  BNFData             bdata(NULL);
  logical             first = YES;
  logical             term = NO;
  symbols.GoTop();
  while ( bsymbol = symbols.GetNext() )
    if ( count = bsymbol->LocateExpressions(bsymbol,bexpressions,&bdata,0,YES,YES) > 0 )
    {
      if ( first ) 
        Output("\nRecursion error(s) in BNF ");
      first = NO;
      Output("\n      Recursion for symbol '%s' via:",bsymbol->get_name());
      while ( count-- )
      {
        bsymbol = bexpressions[count]->get_symbol();
        Output("\n              '%s'",bsymbol->get_name());
      }
    }
  return(term);
}

/******************************************************************************/
/**
\brief  CreateChild - 



\return bdata - Pointer to BNF Node

\param  bparent - 
\param  bsymbol - BNF Symbol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateChild"

BNFData *BNFParser :: CreateChild (BNFData *bparent, BNFSymbol *bsymbol )
{
  BNFData       *child;
  child = (BNFData *)data_pool->ReserveEntry(NO);
  child->InitChild(bparent,bsymbol);
  
  if ( trace_file && !child->HasTerminator() )
    child->Print(trace_file,NO,NO);
//  return( new BNFData(bparent) );
  return(child);
}

/******************************************************************************/
/**
\brief  ElementaryToken - 



\return bsymbol - BNF Symbol

\param  ctoken - Elementary token
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ElementaryToken"

BNFSymbol *BNFParser :: ElementaryToken (uint8 ctoken )
{

  return(elementary_tokens->Get(ctoken));

}

/******************************************************************************/
/**
\brief  GenerateError - 



\return term - Success

\param  bdata - Pointer to BNF Node
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateError"

logical BNFParser :: GenerateError (BNFData *bdata )
{
  BNFData                *err_bdata;
  char                   *pos;
  char                   *next = NULL;
  char                    string[41];
  int                     line = 1;
  int                     column;
  logical                 term = NO;
BEGINSEQ
  if ( !last_error )
    last_error = new char[1024];
    
  err_bdata = err_position.Position() ? &err_position : bdata;
  err_bdata->GetTextPosition(bdata,line,column,YES);
  
  if ( !(pos = err_bdata->Position()) )
  {
    sprintf(last_error,"\nUndefined error in expression");
    LEAVESEQ
  }
  
  if ( next = strchr(pos,'\n') )
    *next = 0;
  
  sprintf(last_error,"\nError at line %i, column %i",line,column);
  
  gvtxbts(string,pos,sizeof(string)-1);
  if ( !err_position.Position() )
    sprintf(last_error+strlen(last_error),"\nUnexpected data after: ... '%s'",string);
  else
  {
    sprintf(last_error+strlen(last_error),"\nNo match for '%s' at: ... %s",err_position.Name(),string);
    bdata = err_position.get_parent();
    while ( bdata && bdata->get_parent() )
    {
      sprintf(last_error+strlen(last_error),"\n   in: %s",bdata->Name());
      bdata = bdata->get_parent();  
    }
  }
  
  if ( next )
    *next = '\n';
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetLastError - 



\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastError"

char *BNFParser :: GetLastError ( )
{

  return( last_error && *last_error ? last_error : NULL);

}

/******************************************************************************/
/**
\brief  GetSymbol - Get symbol

        The  functio returns the BNFSymbol instance for the symbol name (symbol)
        passed.

\return bsymbol - BNF Symbol

\param  symbol - Symbol name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSymbol"

BNFSymbol *BNFParser :: GetSymbol (char *symbol )
{
  BNFSymbol              *bsymbol;
  res_lock.ILock();
  
  symbols.GoTop();
  while ( bsymbol = symbols.GetNext() )
    if ( !strcmp(symbol,bsymbol->get_name()) )
      break;

  if ( !bsymbol && !strcmp(symbol,name) )
    bsymbol = this;
    
  if ( bsymbol && bsymbol->get_osymbol() )
    bsymbol = bsymbol->get_osymbol();
  res_lock.IUnlock();
  return(bsymbol);
}

/******************************************************************************/
/**
\brief  GetSymbolCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSymbolCount"

int16 BNFParser :: GetSymbolCount ( )
{

  return ( symbols.GetCount() + 1 );

}

/******************************************************************************/
/**
\brief  InitCTokens - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitCTokens"

void BNFParser :: InitCTokens ( )
{

  elementary_tokens = new BNFElmTokens(this);

}

/******************************************************************************/
/**
\brief  IsValidString - 



\return cond - Return value

\param  symbol_name - 
\param  string - String value
\param  string_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValidString"

logical BNFParser :: IsValidString (char *symbol_name, char *string, int32 string_len )
{
  logical                 cond = YES;

  return(cond);
}

/******************************************************************************/
/**
\brief  ListSymbols - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ListSymbols"

logical BNFParser :: ListSymbols ( )
{
  BNFSymbol              *bsymbol;
  logical                 term = NO;
  Output("\nSymbol list");
  
  symbols.GoTop();
  while ( bsymbol = symbols.GetNext() )
  {
    if ( trace_file )
      fprintf(trace_file,"\n    '%s'",bsymbol->get_name());
    else
      Output("\n    '%s'",bsymbol->get_name());
  }
  return(term);
}

/******************************************************************************/
/**
\brief  MoveElementarySymbol - 



\return term - Success

\param  bsymbol - BNF Symbol
\param  symbol_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveElementarySymbol"

logical BNFParser :: MoveElementarySymbol (BNFSymbol *bsymbol, DLL(BNFSymbol) *symbol_list )
{
  DLL(BNFExpression)   *expressions = bsymbol->get_expressions();
  BNFExpression        *bexpression;
  logical               term = NO;
BEGINSEQ
  if ( expressions )
  {
    expressions->GoTop();
    while ( bexpression = expressions->GetNext() )
      if ( !bexpression->IsElementary() )             ERROR
  }

  symbols.RemoveAt();
  if ( bsymbol->get_osymbol() ) // delete aliases
  {
    delete bsymbol;                                  
    LEAVESEQ
  }

  symbol_list->AddTail(bsymbol);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  MoveIdentifiedSymbol - 



\return term - Success

\param  bsymbol - BNF Symbol
\param  symbol_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MoveIdentifiedSymbol"

logical BNFParser :: MoveIdentifiedSymbol (BNFSymbol *bsymbol, DLL(BNFSymbol) *symbol_list )
{
  DLL(BNFExpression)   *expressions = bsymbol->get_expressions();
  BNFExpression        *expression;
  logical               term = NO;
BEGINSEQ
  if ( expressions )
  {
    expressions->GoTop();
    while ( expression = expressions->GetNext() )
      if ( !expression->IsIdentified() )             ERROR
  }

  symbols.RemoveAt();
  if ( bsymbol->get_osymbol() ) // delete aliases
  {
    delete bsymbol;                                  
    LEAVESEQ
  }

  symbol_list->AddTail(bsymbol);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PrintError - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrintError"

logical BNFParser :: PrintError ( )
{
  logical                 term = NO;
  if ( trace_file )
    fprintf(trace_file,last_error);
    
  SOSError().OutputMessage("SOS", "Error", last_error);
  return(term);
}

/******************************************************************************/
/**
\brief  ReleaseExpression - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleaseExpression"

void BNFParser :: ReleaseExpression ( )
{

  if ( expression )
    free(expression);
  expression = NULL;


}

/******************************************************************************/
/**
\brief  RemoveChild - 



\return term - Success

\param  bchild - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveChild"

logical BNFParser :: RemoveChild (BNFData *bchild )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       ERROR
    
  res_lock.ILock();
  
  bchild->Reset(this);
  data_pool->ReleaseEntry(bchild);
//  delete bchild;

  res_lock.IUnlock();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveSymbol - 




\param  bsymbol - BNF Symbol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveSymbol"

void BNFParser :: RemoveSymbol (BNFSymbol *bsymbol )
{

  if ( this )
    if ( symbols.Find(bsymbol) )
      symbols.RemoveAt();




}

/******************************************************************************/
/**
\brief  ReorderSymbol - 



\return term - Success

\param  bsymbol - BNF Symbol
\param  symbol_list - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReorderSymbol"

logical BNFParser :: ReorderSymbol (BNFSymbol *bsymbol, DLL(BNFSymbol) *symbol_list )
{
  DLL(BNFExpression)     *derived_symbols;
  BNFExpression          *bexpression;
  BNFSymbol              *derived_symbol;
  logical                 term = NO;
BEGINSEQ
  if ( !symbols.Find(bsymbol) )  
  {
    if ( trace_file )
      Output("\nAmbiguity might be caused by symbol '%s'",bsymbol->get_name());
    LEAVESEQ
  }
  
  symbols.RemoveAt();
  if ( bsymbol->get_osymbol() ) // delete aliases
  {
    delete bsymbol;                                  
    LEAVESEQ
  }

  if ( (derived_symbols = bsymbol->get_starting_symbol_in()) && 
       derived_symbols->GetCount() > 0                          )
  {
    derived_symbols->GoTop();
    while ( bexpression = derived_symbols->GetNext() )
    {
      derived_symbol = bexpression->get_symbol();
      if ( !symbol_list->Find(derived_symbol) )
        ReorderSymbol(derived_symbol,symbol_list);
    }
  }
  
  symbol_list->AddTail(bsymbol);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReorderSymbols - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReorderSymbols"

logical BNFParser :: ReorderSymbols ( )
{
  DLL(BNFSymbol)      new_list;
  BNFSymbol          *bsymbol;
  int                 i = 0;
  logical             term = NO;
  SetupStartingSymbols();   // top-symbol
  symbols.GoTop();
  while ( bsymbol = symbols.GetNext() )
    bsymbol->SetupStartingSymbols();
  
  i = 0;
  symbols.GoTop();
  while ( bsymbol = symbols.GetNext() )
  {
    if ( bsymbol->IsKeyword() )
    {
      new_list.AddTail(bsymbol);
      symbols.RemoveAt();
      if ( i > 0 )
        symbols.FindIndex(i-1);
      else
        symbols.GoTop();
    }
    else
      i++;
  }

  i = 0;
  symbols.GoTop();
  while ( bsymbol = symbols.GetNext() )
  {
    if ( MoveElementarySymbol(bsymbol,&new_list) )
      i++;
    else if ( i > 0 )
      symbols.FindIndex(i-1);
    else
      symbols.GoTop();
  }
  
  i = 0;
  symbols.GoTop();
  while ( bsymbol = symbols.GetNext() )
  {
    if ( MoveIdentifiedSymbol(bsymbol,&new_list) )
      i++;
    else if ( i > 0 )
      symbols.FindIndex(i-1);
    else
      symbols.GoTop();
  }

  while ( bsymbol = symbols.GetHead() )
    ReorderSymbol(bsymbol,&new_list);

  symbols.Clear();
  symbols.Copy(new_list);

  i = 0;
  symbols.GoBottom();
  while ( bsymbol = symbols.GetPrev() )
    bsymbol->SetPriority(++i);

  symbols.GoTop();
  while ( bsymbol = symbols.GetNext() )
    bsymbol->Optimize();

  elementary_tokens->Optimize();
  return(term);
}

/******************************************************************************/
/**
\brief  ResetError - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetError"

void BNFParser :: ResetError ( )
{

  err_position.RemoveParent();
  err_position.Reset(this);



}

/******************************************************************************/
/**
\brief  ResetLastError - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetLastError"

void BNFParser :: ResetLastError ( )
{

  if ( last_error )
    *last_error = 0;
  


}

/******************************************************************************/
/**
\brief  SetCC - 




\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCC"

void BNFParser :: SetCC (char *string )
{

  if ( init_comment )
    free(init_comment);
  init_comment = NULL;
  
  if ( string )
    init_comment = strdup(string);

}

/******************************************************************************/
/**
\brief  SetError - 




\param  bdata - Pointer to BNF Node
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetError"

void BNFParser :: SetError (BNFData *bdata )
{

  if ( err_position.Position() < bdata->Position() )
  {
    err_position.RemoveParent();
    err_position = bdata;
    err_position.CopyParent(bdata);
  }
  if ( trace_file )
    bdata->Print(trace_file,NO,YES);


}

/******************************************************************************/
/**
\brief  SetFirst - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFirst"

logical BNFParser :: SetFirst ( )
{
  logical                 term = NO;
  if ( symbols.GetCount() > 1 )   // has referenced symbols
    first_referenced = symbols.GetObjectInst(1);
  return(term);
}

/******************************************************************************/
/**
\brief  SkipSeparators - 



\return term - Success

\param  bdata - Pointer to BNF Node
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SkipSeparators"

logical BNFParser :: SkipSeparators (BNFData *bdata )
{

  if ( bdata )
    bdata->SkipSpaces();
  return(NO);
}

/******************************************************************************/
/**
\brief  ~BNFParser - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BNFParser"

     BNFParser :: ~BNFParser ( )
{
  BNFParser        *bparser;
  BNFSymbol        *bsymbol;
  BNFData          *bdata;
  if ( last_error )
    delete last_error;
  last_error = NULL;
  
  if ( trace_file )
    fclose(trace_file);
  trace_file = NULL;  
  
  if ( init_comment )
    free(init_comment);
  init_comment = NULL;
  
  err_position.RemoveParent();
  err_position.Reset(this);
  ReleaseExpression();
    
  if ( top_symbol == this )  // top parser
  {
/*
    data_pool->GoTop();
    while ( bdata = (BNFData *)data_pool->GetNext() )
      bdata->Deinitialize();
    data_pool->FreeEntryTop();
    while ( bdata = (BNFData *)data_pool->FreeEntryNext() )
      bdata->Deinitialize();
*/
    delete data_pool;
    data_pool = NULL;
  }
  
  symbols.GoTop();
  while ( bsymbol = symbols.RemoveTail() )
    if ( bsymbol != this )
      delete bsymbol;

  sub_parser.GoTop();
  while ( bparser = sub_parser.RemoveTail() )
    delete bparser;
  
  if ( top_symbol == this )  // top parser
  {
    delete elementary_tokens;
    elementary_tokens = NULL;
  }


}


