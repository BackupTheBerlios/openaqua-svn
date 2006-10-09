/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    BNFData

\brief    BNF data element
          A  BNF data  element contains  the data  for a  given symbol in an BNF
          expression.  BNF  data  elements  form  a  hierarchie down to symbols,
          which have been defined as relevant symbols.

\date     $Date: 2006/08/28 12:38:35,75 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BNFData"

#include  <pdefault.h>
#include  <fileacc.h>
#ifndef   DLO_BNFData_HPP
#define   DLO_BNFData_HPP
#include  <sBNFData.hpp>
#include  <sDLO.h>
#endif
#include  <sBNFDefinition.hpp>
#include  <sBNFExpression.hpp>
#include  <sBNFParser.hpp>
#include  <sBNFSpecialSymbols.hpp>
#include  <sBNFStandardSymbols.hpp>
#include  <sBNFSymbol.hpp>
#include  <sBNFData.hpp>


/******************************************************************************/
/**
\brief  AddChild - 



\param  bdata - Pointer to BNF Node
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddChild"

void BNFData :: AddChild (BNFData *bdata )
{

  if ( !elements )
    elements = new DLO(BNFData)();

  elements->AddTail(bdata);

}

/******************************************************************************/
/**
\brief  BNFData - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  bsymbol - BNF Symbol
\param  string - String value
\param  string_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFData"

     BNFData :: BNFData (BNFSymbol *bsymbol, char *string, int32 string_len )
                     : parent(NULL),
  symbol(bsymbol),
  value(string),
  value_len(string_len),
  elements(NULL),
  current_pos(string),
  level(0),
  separated(NO),
  pool_entry(NO)
{

  if ( !value_len )
    value_len = strlen(value);

}

/******************************************************************************/
/**
\brief  i01 - 


\param  bparent - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFData"

     BNFData :: BNFData (BNFData *bparent )
                     : parent(bparent),
  symbol(NULL),
  value(NULL),
  value_len(0),
  elements(NULL),
  current_pos(NULL),
  level(0),
  separated(NO),
  pool_entry(NO)
{

  if ( parent )
  {
    parent->AddChild(this);
    level = parent->get_level()+1;
  }


}

/******************************************************************************/
/**
\brief  i02 - 


\param  bdata_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFData"

     BNFData :: BNFData (const BNFData &bdata_ref )
                     : parent(bdata_ref.parent),
  symbol(bdata_ref.symbol),
  value(bdata_ref.value),
  value_len(bdata_ref.value_len),
  elements(NULL),
  current_pos(bdata_ref.current_pos),
  level(bdata_ref.level),
  separated(NO),
  pool_entry(NO)
{



}

/******************************************************************************/
/**
\brief  CopyParent - 


\return term - Success

\param  bdata - Pointer to BNF Node
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyParent"

logical BNFData :: CopyParent (BNFData *bdata )
{
  logical                 term = NO;
BEGINSEQ
  if ( !bdata->get_parent() )                        LEAVESEQ
    
  parent = new BNFData(NULL);
  *parent = bdata->get_parent();
  parent->CopyParent(bdata->get_parent());
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateDefinition - 


\return term - Success

\param  bparser - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDefinition"

logical BNFData :: CreateDefinition (BNFParser *bparser )
{
  BNFData                *bdata;
  BNFParser              *top_symbol = bparser->get_top_symbol();
  logical                 terminal = YES;
  char                    wstring[129];
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
//  definition  := sym_name ':=' rule [comment] nl
 
  if ( !(bdata = GetElement("sym_name")->GetElement("name")) )
                                                     LEAVESEQ
  gvtxbts(wstring,bdata->get_value(),bdata->get_value_len());
  
  if ( !(bdata = GetElement("rule")) )               LEAVESEQ
  if ( bdata->CreateRule(bparser,wstring) )          ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateDefinitions - 


\return term - Success

\param  bparser - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDefinitions"

logical BNFData :: CreateDefinitions (BNFParser *bparser )
{
  BNFData                *bdata;
  BNFData                *sdata;
  int                     indx0 = 0;
  logical                 term = NO;
  while ( bdata = GetElement(indx0++) )
    if ( !strcmp(bdata->Name(),"bnf_stmt") )
      if ( sdata = bdata->GetElement("definition") ) 
        term = sdata->CreateDefinition(bparser);
      else if ( sdata = bdata->GetElement("keyword") ) 
        term = sdata->CreateKeyword(bparser);

  return(term);
}

/******************************************************************************/
/**
\brief  CreateElement - 


\return term - Success

\param  bparser - 
\param  bexpression - 
\param  optional - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateElement"

logical BNFData :: CreateElement (BNFParser *bparser, BNFExpression *bexpression, logical optional )
{
  BNFData                *bdata;
  BNFData                *mdata;
  int32                   repcount = 1;
  char                    wstring[128];
  logical                 term = NO;
//  keydef      := cstring
//  ext_symbol  := elm_symbol [ multiple ]
//  multiple    := '(' maxnum ')'
//  maxnum      := '*' | number
//  elm_symbol  := sym_name | cstring | opt_symbol | impl_symbol
//  opt_symbol  := '[' rule ']' 
//  impl_symbol := '{' rule '}' 
  
  if ( bdata = GetTopElement("multiple") )
  {
    repcount = 0;
    if ( mdata = bdata->GetElement("maxnum") )
      if ( *mdata->get_value() != '*' )
        repcount = atoi(gvtxbts(wstring,mdata->get_value(),mdata->get_value_len()));
  }
  
  bdata = IsSymbol("keydef") ? this : GetTopElement("elm_symbol");
  
  switch ( bdata->GetSymbolCode("sym_name", "cstring", "opt_symbol", "impl_symbol") )
  {
    case 1 : bdata = GetElement("sym_name");
             bdata->CreateNameElement(bparser,bexpression,optional,repcount,NULL);
             break;
    case 2 : bdata = GetElement("cstring");
             bdata->CreateStringElement(bparser,bexpression,optional);
             break;
    case 3 : optional = YES;   
    case 4 : bdata->CreateLocalSymbol(bparser,bexpression,optional,repcount,wstring);
             break;
    default: break;
  }
             

  return(term);
}

/******************************************************************************/
/**
\brief  CreateExpression - 


\return term - Success

\param  bparser - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateExpression"

logical BNFData :: CreateExpression (BNFParser *bparser, char *names )
{
  BNFData                *bdata;
  BNFSymbol              *bsymbol = NULL;
  BNFParser              *top_symbol = bparser->get_top_symbol();
  BNFExpression          *expression;
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
//  prule       := ext_symbol(*)

  if ( !GetElement("ext_symbol") )                  SOSERR(99)
  if ( !strcmp(names,"CC") )
  {
    bparser->SetCC(GetConstantString());             LEAVESEQ
  }
  
  if ( !(bsymbol = top_symbol->GetSymbol(names)) )   SOSERR(99)
  expression = new BNFExpression(bsymbol);
  
  while ( bdata = GetElement(indx0++) )
    if ( bdata->CreateElement(bparser,expression,NO) )
                                                     ERROR
      

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateKeyExpression - 


\return term - Success

\param  bparser - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateKeyExpression"

logical BNFData :: CreateKeyExpression (BNFParser *bparser, char *names )
{
  BNFSymbol              *bsymbol = NULL;
  BNFParser              *top_symbol = bparser->get_top_symbol();
  BNFExpression          *expression;
  logical                 term = NO;
BEGINSEQ
  if ( !(bsymbol = top_symbol->GetSymbol(names)) )   SOSERR(99)
  expression = new BNFExpression(bsymbol);
  
  if ( CreateElement(bparser,expression,NO) )        ERROR
  

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateKeyword - 


\return term - Success

\param  bparser - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateKeyword"

logical BNFData :: CreateKeyword (BNFParser *bparser )
{
  BNFData                *bdata;
  BNFData                *edata;
  BNFParser              *top_symbol = bparser->get_top_symbol();
  char                    wstring[129];
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
//  keyword     := sym_name '::' keydef [ alt_keydef(*) ] nl
//  sym_name    := name
  
  if ( !(bdata = GetElement("name")) )               LEAVESEQ
    
  gvtxbts(wstring,bdata->get_value(),bdata->get_value_len());
  
  if ( !(edata = GetElement("keydef")) )             LEAVESEQ
  
  if ( edata->CreateKeyExpression(bparser,wstring) ) ERROR
    
  while ( bdata = GetElement(indx0++) )
    if ( !strcmp(bdata->Name(),"alt_keydef") )
      if ( edata = bdata->GetElement("keydef") )
        if ( edata->CreateKeyExpression(bparser,wstring) )
                                                     ERROR

  top_symbol->GetSymbol(wstring)->SetKeyword();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateLocalSymbol - 


\return term - Success

\param  bparser - 
\param  bexpression - 
\param  optional - 
\param  repcount - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateLocalSymbol"

logical BNFData :: CreateLocalSymbol (BNFParser *bparser, BNFExpression *bexpression, logical optional, int32 repcount, char *names )
{
  BNFData                *bdata;
  BNFData                *edata;
  logical                 term = NO;
BEGINSEQ
//  impl_symbol := '{' rule '}' 
//  opt_symbol  := '[' rule ']' 
  
// names is an output parameter!!

  bdata = GetElement("rule");
  if ( edata = bdata->GetSymbol("ext_symbol") )
    edata->CreateElement(bparser,bexpression,optional);
  else
  {
    bdata = GetElement("rule");
    GetLocalSymbolName(names);
    CreateSymbol(bparser,names);
    bdata->CreateNameElement(bparser,bexpression,optional,repcount,names);
    if ( bdata->CreateRule(bparser,names) )        ERROR
  }         

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateNameElement - 


\return term - Success

\param  bparser - 
\param  bexpression - 
\param  optional - 
\param  repcount - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNameElement"

logical BNFData :: CreateNameElement (BNFParser *bparser, BNFExpression *bexpression, logical optional, int32 repcount, char *names )
{
  BNFSymbol              *bsymbol = NULL;
  BNFData                *bdata;
  BNFParser              *top_symbol = bparser->get_top_symbol();
  char                    wstring[128];
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
//  sym_name    := name
  
  if ( names )
    strcpy(wstring,names);
  else
  {
    bdata = GetElement("name");
    gvtxbts(wstring,bdata->get_value(),bdata->get_value_len());
  }
  if ( !(bsymbol = top_symbol->GetSymbol(wstring)) ) SOSERR(99)
  
  bexpression->AddElement(bsymbol,optional,repcount,
                          *wstring != toupper(*wstring),YES);
RECOVER
  Output("\nSymbol '%s' not defined",wstring);
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateParser - 


\return bparser - 

\param  bs_parent - Parent parser
\param  list_symbols - List symbols
\param  trace_path - Trace file location
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateParser"

BNFParser *BNFData :: CreateParser (BNFParser *bs_parent, logical list_symbols, char *trace_path )
{
  BNFParser              *bparser = NULL;
  BNFData                *bdata;
  char                    wstring[129];
  logical                 term = NO;
BEGINSEQ
  if ( !(bdata = GetElement("std_name")) )           SOSERR(99)
  gvtxbts(wstring,bdata->get_value(),bdata->get_value_len());
  bparser = new BNFParser(wstring,bs_parent,YES,NO,trace_path);
  
  if ( !(bdata = GetElement(0)) )                    ERROR
    
  if ( bdata->CreateReferences(bparser) )            ERROR
  if ( !bs_parent )
    bparser->SetFirst();  
  if ( bdata->CreateSymbols(bparser) )               ERROR
  if ( bdata->CreateDefinitions(bparser) )           ERROR

  
  if ( !bs_parent )
  {    
    bparser->ReorderSymbols();
    bparser->Check();
  }
  if ( list_symbols )
    bparser->ListSymbols();
RECOVER
  bparser = NULL;
ENDSEQ
  return(bparser);
}

/******************************************************************************/
/**
\brief  CreateReference - 


\return term - Success

\param  bparser - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateReference"

logical BNFData :: CreateReference (BNFParser *bparser )
{
  BNFData                *bdata;
  BNFData                *ndata;
  BNFSymbol              *bsymbol = NULL;
  BNFParser              *top_symbol = bparser->get_top_symbol();
  char                    wstring[129];
  char                    names[129];
  logical                 term = NO;
BEGINSEQ
  bdata = GetElement("std_name");
  gvtxbts(names,bdata->get_value(),bdata->get_value_len());
  
  bdata = GetElement("symref");
  if ( !(ndata = bdata->GetElement("std_name")) )  SOSERR(99)
  gvtxbts(wstring,ndata->get_value(),ndata->get_value_len());
  bsymbol = top_symbol->GetSymbol(wstring);
  
  if ( bdata->GetElement("class_ref") && !bsymbol )
  {
    if ( !strcmp(wstring,"BNFStandardSymbols") )
      bsymbol = new BNFStandardSymbols(bparser);
    if ( !strcmp(wstring,"BNFDefinition") )
      bsymbol = new BNFDefinition(top_symbol);
    if ( !strcmp(wstring,"BNFSpecialSymbols") )
      bsymbol = new BNFSpecialSymbols(top_symbol);
//    if ( !bsymbol )                                  SOSERR(99)
  } 
  else if ( bdata->GetElement("symbol_ref") )
  {
//    if ( !bsymbol )                                  SOSERR(99)
    if ( bsymbol )
      bsymbol->CreateAlias(names);
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateReferences - 


\return term - Success

\param  bparser - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateReferences"

logical BNFData :: CreateReferences (BNFParser *bparser )
{
  BNFData                *bdata;
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  while ( bdata = GetElement(indx0++) )
    if ( !strcmp(bdata->Name(),"bnf_stmt") )
      if ( bdata = bdata->GetElement("reference") ) 
        if ( bdata->CreateReference(bparser) )       ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateRule - 


\return term - Success

\param  bparser - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateRule"

logical BNFData :: CreateRule (BNFParser *bparser, char *names )
{
  BNFData                *bdata;
  BNFData                *edata;
  BNFParser              *top_symbol = bparser->get_top_symbol();
  logical                 terminal = YES;
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
//  rule        := prule [ alt_prule(*) ] 
//  alt_prule   := '|' prule 
  
  if ( !(edata = GetElement("prule")) )            LEAVESEQ
  
  if ( edata->CreateExpression(bparser,names) )    ERROR
  terminal = terminal && edata->IsSymbol("cstring");
    
  while ( bdata = GetElement(++indx0) )
    if ( edata = bdata->GetElement("prule") )
    {
      if ( edata->CreateExpression(bparser,names) )
                                                     ERROR
      terminal = terminal && edata->IsSymbol("cstring");
    }

  if ( terminal )
    top_symbol->GetSymbol(names)->SetTerminal();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CreateStringElement - 


\return term - Success

\param  bparser - 
\param  bexpression - 
\param  optional - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStringElement"

logical BNFData :: CreateStringElement (BNFParser *bparser, BNFExpression *bexpression, logical optional )
{
  char                   *svalue;
  int                     len;
  int                     indx0 = 0;
  logical                 term = NO;
  svalue = value;
  len    = value_len;
  if ( IsSymbol("std_string") )
  {
    svalue++;
    len -= 2;
  }
  
  while ( indx0 < len )
  {
    bexpression->AddElement(bparser->ElementaryToken(svalue[indx0]),
                            optional,1,
                            svalue[indx0] != toupper(svalue[indx0]),
                            indx0 == len-1);   
    indx0++;
  }


  return(term);
}

/******************************************************************************/
/**
\brief  CreateSymbol - 


\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - 


\param  bparser - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSymbol"

logical BNFData :: CreateSymbol (BNFParser *bparser )
{
  BNFData                *bdata;
  char                    names[129];
  logical                 term = NO;
BEGINSEQ
//  definition  := sym_name ':=' rule [comment] nl
//  keyword     := sym_name '::' keydef [ alt_keydef(*) ] nl
//  sym_name    := name
  
  if ( !(bdata = GetElement("sym_name")->GetElement("name")) )
                                                     LEAVESEQ
  
  gvtxbts(names,bdata->get_value(),bdata->get_value_len());
  if ( !strcmp(names,"CC") )                         LEAVESEQ
    
  CreateSymbol(bparser,names);

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  bparser - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSymbol"

logical BNFData :: CreateSymbol (BNFParser *bparser, char *names )
{
  BNFParser              *top_symbol = bparser->get_top_symbol();
  char                    string[129];
  logical                 term = NO;
  if ( !names )
    names = GetLocalSymbolName(string);

  if ( !(bparser->GetSymbol(names)) )
    new BNFSymbol(top_symbol,names);

  return(term);
}

/******************************************************************************/
/**
\brief  CreateSymbols - 


\return term - Success

\param  bparser - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSymbols"

logical BNFData :: CreateSymbols (BNFParser *bparser )
{
  BNFData                *bdata;
  BNFData                *sdata;
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
  while ( bdata = GetElement(indx0++) )
    if ( !strcmp(bdata->Name(),"bnf_stmt") )
      if ( (sdata = bdata->GetElement("definition")) || 
           (sdata = bdata->GetElement("keyword"))       ) 
        if ( sdata->CreateSymbol(bparser) )         ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  CurrentToken - 


\return ctoken - Elementary token

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CurrentToken"

uint8 BNFData :: CurrentToken ( )
{


  return(*current_pos);
}

/******************************************************************************/
/**
\brief  Deinitialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Deinitialize"

void BNFData :: Deinitialize ( )
{

  nstring.NBase::Initialize();

  if ( symbol )
    RemoveChildren(symbol->get_top_symbol());

  delete elements;
  elements = NULL;


}

/******************************************************************************/
/**
\brief  End - 


\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "End"

char *BNFData :: End ( )
{

  return(current_pos+strlen(current_pos));

}

/******************************************************************************/
/**
\brief  GenerateDefinition - 


\return term - Success

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateDefinition"

logical BNFData :: GenerateDefinition (char *string )
{
  BNFData                *bdata;
  logical                 terminal = YES;
  char                    wstring[129];
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
//  definition  := sym_name ':=' rule [comment] nl
  
  if ( !(bdata = GetElement("sym_name")->GetElement("name")) )
                                                     ERROR
  gvtxbts(wstring,bdata->get_value(),bdata->get_value_len());
  strcat(strcat(strcat(string,"// "),wstring),"\n");
  
  if ( !(bdata = GetElement("rule")) )               LEAVESEQ
  if ( bdata->GenerateRule(string,wstring) )         ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateDefinitions - 


\return term - Success

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateDefinitions"

logical BNFData :: GenerateDefinitions (char *string )
{
  BNFData                *bdata;
  BNFData                *sdata;
  int                     indx0 = 0;
  logical                 term = NO;
  while ( bdata = GetElement(indx0++) )
    if ( !strcmp(bdata->Name(),"bnf_stmt") )
      if ( sdata = bdata->GetElement("definition") ) 
        term = sdata->GenerateDefinition(string);
      else if ( sdata = bdata->GetElement("keyword") ) 
        term = sdata->GenerateKeyword(string);

  return(term);
}

/******************************************************************************/
/**
\brief  GenerateElement - 


\return term - Success

\param  string - String value
\param  optional - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateElement"

logical BNFData :: GenerateElement (char *string, logical optional )
{
  BNFData                *bdata;
  BNFData                *mdata;
  char                   *repetitions = "1";
  char                    wstring[128];
  logical                 term = NO;
//  keydef      := cstring
//  ext_symbol  := elm_symbol [ multiple ]
//  multiple    := '(' maxnum ')'
//  maxnum      := '*' | number
//  elm_symbol  := sym_name | cstring | opt_symbol | impl_symbol
//  opt_symbol  := '[' rule ']' 
//  impl_symbol := '{' rule '}' 
  
  if ( bdata = GetTopElement("multiple") )
  {
    repetitions = "UNDEF";
    if ( mdata = bdata->GetElement("maxnum") )
      if ( *mdata->get_value() != '*' )
        repetitions = gvtxbts(wstring,mdata->get_value(),mdata->get_value_len());
  }
  
  bdata = IsSymbol("keydef") ? this : GetTopElement("elm_symbol");
  
  switch ( bdata->GetSymbolCode("sym_name", "cstring", "opt_symbol", "impl_symbol") )
  {
    case 1 : bdata = GetElement("sym_name");
             bdata->GenerateNameElement(string,optional,repetitions,NULL);
             break;
    case 2 : bdata = GetElement("cstring");
             bdata->GenerateStringElement(string,optional);
             break;
    case 3 : optional = YES;
    case 4 : bdata->GenerateLocalSymbol(string,optional,repetitions,wstring);
             break;
    default: break;
  }
             

  return(term);
}

/******************************************************************************/
/**
\brief  GenerateExpression - 


\return term - Success

\param  string - String value
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateExpression"

logical BNFData :: GenerateExpression (char *string, char *names )
{
  BNFData                *bdata;
  logical                 optional = NO;
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
//  prule       := ext_symbol(*)

  if ( !GetElement("ext_symbol") )                   ERROR
  if ( !strcmp(names,"CC") )
  {
    strcat(strcat(strcat(string,"  SetCC(\""),GetConstantString()),"\");\n");
                                                     LEAVESEQ
  }
  
  strcat(strcat(strcat(string,"  __expression = new BNFExpression("),names),");\n");
  
  while ( bdata = GetElement(indx0++) )
    bdata->GenerateElement(string,NO);

      

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateKeyExpression - 


\return term - Success

\param  string - String value
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateKeyExpression"

logical BNFData :: GenerateKeyExpression (char *string, char *names )
{
  logical                 term = NO;
  strcat(strcat(strcat(string,"  __expression = new BNFExpression("),names),");\n");
  GenerateElement(string,NO);
  

  return(term);
}

/******************************************************************************/
/**
\brief  GenerateKeyword - 


\return term - Success

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateKeyword"

logical BNFData :: GenerateKeyword (char *string )
{
  BNFData                *bdata;
  BNFData                *edata;
  logical                 terminal = YES;
  char                    wstring[129];
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
//  keyword     := sym_name '::' keydef [ alt_keydef(*) ] nl
//  sym_name    := name
  
  if ( !(bdata = GetElement("name")) )              ERROR
    
  gvtxbts(wstring,bdata->get_value(),bdata->get_value_len());
  strcat(strcat(strcat(string,"// "),wstring),"\n");
  
  if ( !(edata = GetElement("keydef")) )             LEAVESEQ
  
  edata->GenerateKeyExpression(string,wstring);
  
  while ( bdata = GetElement(indx0++) )
    if ( !strcmp(bdata->Name(),"alt_keydef") )
      if ( edata = bdata->GetElement("keydef") )   
        edata->GenerateKeyExpression(string,wstring);

  strcat(strcat(strcat(string,"  "),wstring),"->SetKeyword();\n");
  strcat(string,"\n");

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateLocalSymbol - 


\return term - Success

\param  string - String value
\param  optional - 
\param  repetitions - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateLocalSymbol"

logical BNFData :: GenerateLocalSymbol (char *string, logical optional, char *repetitions, char *names )
{
  BNFData                *bdata;
  BNFData                *edata;
  logical                 term = NO;
BEGINSEQ
//  impl_symbol := '{' rule '}' 
//  opt_symbol  := '[' rule ']' 
  
// names is an output parameter!!

  bdata = GetElement("rule");
  if ( edata = bdata->GetSymbol("ext_symbol") )
    edata->GenerateElement(string,optional);
  else
  {
    GetLocalSymbolName(names);
    GenerateSymbol(string,NULL,names);
    bdata->GenerateNameElement(string,optional,repetitions,names);
    if ( bdata->GenerateRule(string,names) ) ERROR
  }         

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateNameElement - 


\return term - Success

\param  string - String value
\param  optional - 
\param  repetitions - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateNameElement"

logical BNFData :: GenerateNameElement (char *string, logical optional, char *repetitions, char *names )
{
  BNFData                *bdata;
  char                    wstring[128];
  int                     indx0 = 0;
  logical                 term = NO;
//  sym_name    := name
  
  if ( names )
    strcpy(wstring,names);
  else
  {
    bdata = GetElement("name");
    gvtxbts(wstring,bdata->get_value(),bdata->get_value_len());
  }
  strcat(strcat(strcat(string,"    __expression->AddElement("),wstring),",");
  strcat(strcat(string,optional ?"YES" : "NO"),",");  
  strcat(strcat(string,repetitions),",");  
  
  if ( *wstring == toupper(*wstring) )
    strcat(strcat(string,"NO"),",");  
  else
    strcat(strcat(string,"YES"),",");  
  
  strcat(strcat(string,"YES"),");\n");  

  return(term);
}

/******************************************************************************/
/**
\brief  GenerateReference - 


\return term - Success

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateReference"

logical BNFData :: GenerateReference (char *string )
{
  BNFData                *bdata;
  BNFData                *ndata;
  char                    wstring[129];
  int                     indx0 = 0;
  logical                 term = NO;
  strcat(string,"  BNFSymbol  *");
  
  bdata = GetElement("std_name");
  gvtxbts(wstring,bdata->get_value(),bdata->get_value_len());
  strcat(string,wstring);
  
  bdata = GetElement("symref");
  if ( bdata->GetElement("class_ref") ) 
  {
    strcat(string," = new ");
    if ( ndata = bdata->GetElement("std_name") )
      gvtxbts(wstring,ndata->get_value(),ndata->get_value_len());
    else
      strcpy(wstring,"** Error **");
    strcat(string,wstring);
    strcat(string,"(bs_parent);");
  }
  if ( bdata->GetElement("symbol_ref") )
  {
    strcat(string," = top_symbol->GetSymbol(\"");
    if ( ndata = bdata->GetElement("std_name") )
      gvtxbts(wstring,ndata->get_value(),ndata->get_value_len());
    else
      strcpy(wstring,"** Error **");
    strcat(string,wstring);
    strcat(string,"\");");
  }

  strcat(string,"\n");

  return(term);
}

/******************************************************************************/
/**
\brief  GenerateReferences - 


\return term - Success

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateReferences"

logical BNFData :: GenerateReferences (char *string )
{
  BNFData                *bdata;
  int                     indx0 = 0;
  logical                 term = NO;
  while ( bdata = GetElement(indx0++) )
    if ( !strcmp(bdata->Name(),"bnf_stmt") )
      if ( bdata = bdata->GetElement("reference") ) 
        bdata->GenerateReference(string);

  return(term);
}

/******************************************************************************/
/**
\brief  GenerateRule - 


\return term - Success

\param  string - String value
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateRule"

logical BNFData :: GenerateRule (char *string, char *names )
{
  BNFData                *bdata;
  BNFData                *edata;
  logical                 terminal = YES;
  int                     indx0 = 0;
  logical                 term = NO;
BEGINSEQ
//  rule        := prule [ alt_prule(*) ] 
//  alt_prule   := '|' prule 
  
  if ( !(edata = GetElement("prule")) )               LEAVESEQ
  
  edata->GenerateExpression(string,names);
  terminal = terminal && edata->IsSymbol("cstring");
  
  while ( bdata = GetElement(++indx0) )
    if ( edata = bdata->GetElement("prule") )   
    {
      edata->GenerateExpression(string,names);
      terminal = terminal && edata->IsSymbol("cstring");
    }

  if ( terminal && strcmp(names,"CC") )
    strcat(strcat(strcat(string,"  "),names),"->SetTerminal();\n");
      
  strcat(string,"\n");


ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateSource - 


\return term - Success

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateSource"

logical BNFData :: GenerateSource (char *cpath )
{
  char                    area[1000000];
  BNFData                *bdata;
  char                   *pos = area;
  char                    names[129];
  char                    wstring[129];
  logical                 term = NO;
BEGINSEQ
  if ( !(bdata = GetElement("std_name")) )            SOSERR(99)
  gvtxbts(names,bdata->get_value(),bdata->get_value_len());
  
  strcpy(area,"/***********************************************************************/\n");
  strcat(area,"/*\n");
  strcat(strcat(strcat(area,"/*  Gerarated Parser for: "),Name()),"\n");
  strcat(area,"/*\n");
  strcat(area,"/***********************************************************************/\n");
  strcat(area,"#include <csos4mac.h>\n");
  strcat(area,"#include <sBNFParser.hpp>\n");
  strcat(area,"#include <sBNFStandardSymbols.hpp>\n");
  strcat(area,"#include <sBNFSpecialSymbols.hpp>\n");
  strcat(area,"#include <sBNF_cpp.hpp>\n");
  strcat(area,"#include <sBNFData.hpp>\n");

  strcat(strcat(strcat(area,"class "),wstring)," : public BNFParser {\n");
  strcat(area,"    public:\n");
  strcat(strcat(strcat(area,"                "),wstring),"(BNFParser *bs_parent);\n");
  strcat(area,"};\n");

  strcat(area,"\n");
  strcpy(wstring,"BNF_");
  strcat(wstring,names);
  strcat(strcat(strcat(strcat(area,wstring)," :: "),wstring),"(BNFParser *bs_parent)\n");
  strcat(strcat(strcat(strcat(area,"         : BNFParser (\""),names),"\""),",bs_parent,YES)\n");
  strcat(area,"{\n  BNFExpression *__expression;\n\n");
  
  strcat(area,"/*\n");
  strcat(area,value);  
  strcat(area,"\n*/\n\n");

  if ( !(bdata = GetElement(0)) )                    ERROR
    
  strcat(strcat(strcat(area,"\n  BNFSymbol  *"),names)," = this;");
  strcat(area,"\n  if ( !bs_parent ) bs_parent = this;\n");
  strcat(area,"\n");
  bdata->GenerateReferences(area);
  strcat(area,"  if ( !bs_parent || bs_parent == this )\n    SetFirst();\n");
  bdata->GenerateSymbols(area,names);
  strcat(area,"\n");
  bdata->GenerateDefinitions(area);

  strcat(area,"  if ( !bs_parent || bs_parent == this )\n    ReorderSymbols();\n\n");
  strcat(area,"\n};\n");
  
  filwrit(cpath,area,strlen(area));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateStringElement - 


\return term - Success

\param  string - String value
\param  optional - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateStringElement"

logical BNFData :: GenerateStringElement (char *string, logical optional )
{
  char                   *svalue;
  int                     len;
  int                     slen;
  int                     indx0 = 0;
  logical                 term = NO;
  svalue = value;
  len    = value_len;
  if ( IsSymbol("std_string") )
  {
    svalue++;
    len -= 2;
  }
  
  while ( indx0 < len )
  {
    if ( svalue[indx0] != '\\' || indx0+1 < len  )
    {
      strcat(string,"    __expression->AddElement(ElementaryToken('");
      slen = strlen(string);
      if ( svalue[indx0] == '\\' ) 
      {
        string[slen]                  = '\\';
        slen++;
        indx0++;
      }
      string[slen]                    = svalue[indx0];
      string[slen+1]                  = 0;
      strcat(string,"'),");
      strcat(strcat(string,optional ?"YES" : "NO"),",");  
      strcat(string,"1,");  
  
      if ( svalue[indx0] == toupper(svalue[indx0]) )
        strcat(strcat(string,"NO"),",");  
      else
        strcat(strcat(string,"YES"),",");  
  
      strcat(strcat(string,indx0 == len-1 ? "YES" : "NO"),");\n");  
    }
    indx0++;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  GenerateSymbol - 


\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - 


\param  string - String value
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateSymbol"

logical BNFData :: GenerateSymbol (char *string, char *names )
{
  BNFData                *bdata;
  char                    wstring[129];
  logical                 term = NO;
BEGINSEQ
//  definition  := sym_name ':=' rule [comment] nl
//  keyword     := sym_name '::' keydef [ alt_keydef(*) ] nl
//  sym_name    := name
  
  if ( !(bdata = GetElement("sym_name")->GetElement("name")) )
                                                     ERROR
  gvtxbts(wstring,bdata->get_value(),bdata->get_value_len());
  GenerateSymbol(string,names,wstring);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  string - String value
\param  names - Name
\param  snames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateSymbol"

logical BNFData :: GenerateSymbol (char *string, char *names, char *snames )
{
  BNFData                *bdata = this;
  char                    wstring[129];
  char                    pnames[129];
  logical                 term = NO;
BEGINSEQ
  if ( !snames )
    snames = GetLocalSymbolName(wstring);
    
  if ( !names )
  {
    while ( bdata->get_parent() )
      bdata = bdata->get_parent();
    bdata = bdata->GetElement("std_name");
    gvtxbts(pnames,bdata->get_value(),bdata->get_value_len());
    names = pnames; 
  }
    
  if ( !strcmp(snames,names) )                      LEAVESEQ
  if ( !strcmp(snames,"CC") )                       LEAVESEQ
  
  strcat(string,"  BNFSymbol  *");
  strcat(string,snames);
  strcat(string," = new BNFSymbol(top_symbol,\"");
  
  strcat(string,snames);
    
  strcat(string,"\");");
  strcat(string,"\n");

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateSymbols - 


\return term - Success

\param  string - String value
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateSymbols"

logical BNFData :: GenerateSymbols (char *string, char *names )
{
  BNFData                *bdata;
  BNFData                *sdata;
  int                     indx0 = 0;
  logical                 term = NO;
  while ( bdata = GetElement(indx0++) )
    if ( !strcmp(bdata->Name(),"bnf_stmt") )
      if ( (sdata = bdata->GetElement("definition")) || 
           (sdata = bdata->GetElement("keyword"))       ) 
        sdata->GenerateSymbol(string,names);

  return(term);
}

/******************************************************************************/
/**
\brief  GetConstantString - 


\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetConstantString"

char *BNFData :: GetConstantString ( )
{
  BNFData                   *bdata = this;
  char                      *string = NULL;
  int                        len;
BEGINSEQ
  if ( !(bdata = GetSymbol("std_string")) )           ERROR
  if ( !(string = bdata->StringValue()) )            ERROR
  
  string++;
  string[len = strlen(string)-1] = 0;
  STRExchange(string,"\\\"","\"",len);
  STRExchange(string,"\\\'","\'",len);

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetCurrentLine - 


\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentLine"

char *BNFData :: GetCurrentLine ( )
{
  char          *string = NULL;
  char          *end = NULL;
  char          *end1 = NULL;
  char          *start = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  end = strchr(value,'\r');
  end1 = strchr(value,'\n');
  if ( !end || (end1 && end1 < end) )
    end = end1;
  if ( !end )
    end = value+strlen(value);
  
  start = GetTop()->get_value();
  string = value;
  while ( string-1 >= start )  
  {
    string--;
    if ( *string == '\r' || *string == '\n' )
    {
       string++;
       break;
    }
  }
  nstring.SetString(string,end-string);
  string = nstring;

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetElement - 


\return bdata - Pointer to BNF Node
-------------------------------------------------------------------------------
\brief  i00 - Serch children by index
        The  function returnd the  child of the  BNFData node at position indx0.
        The first child has position 0.

\param  index0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElement"

BNFData *BNFData :: GetElement (int index0 )
{
  BNFData                *bdata = NULL;
  if ( this )
    if ( elements && elements->FindIndex(index0) )
      bdata = elements->GetAt();
  return(bdata);
}

/******************************************************************************/
/**
\brief  i01 - Search node by name
        The  function searches for the nearest BNFData node using a symbol name.
        When  no  node  with  the  symbol  name  passed was faond in the list of
        children the function searches recursively on all lower levels.

\param  symbol - Symbol name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElement"

BNFData *BNFData :: GetElement (char *symbol )
{
  int                     indx0 = 0;
  BNFData                *bdata = NULL;
BEGINSEQ
  if ( !this )                                       ERROR
    
  while ( bdata = GetElement(indx0++) )
    if ( !strcmp(bdata->Name(),symbol) )             LEAVESEQ

  indx0 = 0;
  while ( bdata = GetElement(indx0++) )
    if ( bdata = bdata->GetElement(symbol) )         LEAVESEQ

RECOVER
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  GetElementCount - 


\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElementCount"

int16 BNFData :: GetElementCount ( )
{

  return(elements->GetCount());

}

/******************************************************************************/
/**
\brief  GetLastElement - 


\return bdata - Pointer to BNF Node

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastElement"

BNFData *BNFData :: GetLastElement ( )
{

  return ( this && elements ? elements->GetTail() : NULL);

}

/******************************************************************************/
/**
\brief  GetLocalSymbolName - 


\return string - String value

\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLocalSymbolName"

char *BNFData :: GetLocalSymbolName (char *names )
{
  char                    string[129];
  logical                 term = NO;
  strcpy(names,"__LOCAL");
  //SOSImpExp          char *__cdecl gvtxltoa (int32 intval, char *buffer, uint32 radix );
  gvtxltoa(this, names+7, 10);

  return(names);
}

/******************************************************************************/
/**
\brief  GetParameter - 


\return string_value - 

\param  parm_name - 
\param  default_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParameter"

char *BNFData :: GetParameter (char *parm_name, char *default_value )
{
  BNFData                *bdata = this;
  BNFData                *parameter;
  char                   *string = default_value;
  char                   *kwd;
  int                     i = 0;
BEGINSEQ
  if ( !IsA("parm_list") && !(bdata = GetSymbol("parm_list")) )
                                                     ERROR
  parameter = bdata->GetElement(i++);
  while ( parameter )
  {
    parameter = parameter->GetElement(0);          // parm_spec | operand | '*'
    if ( parameter->IsSymbol("parm_spec") )
    {
      if ( kwd = parameter->GetElement("identifier")->GetStringValue(NULL,NULL) )
        if ( !stricmp(kwd,parm_name) )
        {
          string = "";
          if ( bdata = parameter->GetElement("assigned_value") )
          {
            bdata = bdata->GetElement("operand");
            string = bdata->GetStringValue(NULL,NULL);
          }
          break;
        }
    }
    else if ( parameter->IsSymbol("operation") )
    {
      parameter = parameter->GetElement(0);        // operation
      if ( parameter->GetElement(0)->IsSymbol("pname") )
      {
        kwd = parameter->GetElement("pname")->GetStringValue(NULL,NULL);
        if ( !stricmp(kwd,parm_name) )
        {
          string = "";
          if ( bdata = parameter->GetElement(1) )  // bin_operand
            string = bdata->GetElement(1)->IsSymbol("std_string")
                     ? bdata->GetElement(1)->GetStringConstant()
                     : bdata->GetElement(1)->GetStringValue(NULL,NULL);
          break;
        }
      }
    }
    if ( parameter = bdata->GetElement(i++) )
      parameter = parameter->GetElement(1);
  }

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetStringConstant - 


\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringConstant"

char *BNFData :: GetStringConstant ( )
{
  char                      *string = NULL;
  char                       string_sep;
  int                        len;
BEGINSEQ
  if ( !IsSymbol("std_string") )                     ERROR
  if ( !(string = GetStringValue()) )                ERROR
  
  string_sep = *string;
  string++;
  string[len = strlen(string)-1] = 0;
  STRExchange(string,"\\\"","\"",len);
  STRExchange(string,"\\\'","\'",len);
  if ( string_sep == '\'' )
    STRExchange(string,"\'\'","\'",len);
  else
    STRExchange(string,"\"\"","\"",len);

RECOVER

ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetStringValue - 


\return string - String value

\param  prefix - 
\param  suffix - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringValue"

char *BNFData :: GetStringValue (char *prefix, char *suffix )
{
  int                   len;
  char                 *strval = "";
BEGINSEQ
  if ( !this )                                       ERROR
    
  len = value_len+1;
  if ( prefix )
    len += strlen(prefix);

  if ( suffix )
    len += strlen(suffix);

  nstring.Resize(len,UNDEF); 
  nstring = "";
  if ( prefix )
    nstring += prefix;
  nstring.Append(value,value_len);
  if ( suffix )
    nstring += suffix;
    
  strval = nstring;

RECOVER

ENDSEQ
  return(strval);
}

/******************************************************************************/
/**
\brief  GetSymbol - 


\return bdata - Pointer to BNF Node

\param  symbol - Symbol name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSymbol"

BNFData *BNFData :: GetSymbol (char *symbol )
{
  BNFData        *bdata = this;
BEGINSEQ
  while ( bdata )
  {
    if ( !strcmp(bdata->Name(),symbol) )             LEAVESEQ
    if ( bdata->GetElement(1) )                      ERROR
    bdata = bdata->GetElement(0);
  }
  ERROR
RECOVER
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  GetSymbolCode - 


\return scode - 

\param  symbol1 - 
\param  symbol2 - 
\param  symbol3 - 
\param  symbol4 - 
\param  symbol5 - 
\param  symbol6 - 
\param  symbol7 - 
\param  symbol8 - 
\param  symbol9 - 
\param  symbol10 - 
\param  symbol11 - 
\param  symbol12 - 
\param  symbol13 - 
\param  symbol14 - 
\param  symbol15 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSymbolCode"

int8 BNFData :: GetSymbolCode (char *symbol1, char *symbol2, char *symbol3, char *symbol4, char *symbol5, char *symbol6, char *symbol7, char *symbol8, char *symbol9, char *symbol10, char *symbol11, char *symbol12, char *symbol13, char *symbol14, char *symbol15 )
{
  int8           scode = UNDEF;
  if ( IsSymbol(symbol1) )
    scode = 1;
  else if ( symbol2 && IsSymbol(symbol2) )
    scode = 2;
  else if ( symbol3 && IsSymbol(symbol3) )
    scode = 3;
  else if ( symbol4 && IsSymbol(symbol4) )
    scode = 4;
  else if ( symbol5 && IsSymbol(symbol5) )
    scode = 5;
  else if ( symbol6 && IsSymbol(symbol6) )
    scode = 6;
  else if ( symbol7 && IsSymbol(symbol7) )
    scode = 7;
  else if ( symbol8 && IsSymbol(symbol8) )
    scode = 8;
  else if ( symbol9 && IsSymbol(symbol9) )
    scode = 9;
  else if ( symbol10 && IsSymbol(symbol10) )
    scode = 10;
  else if ( symbol11 && IsSymbol(symbol11) )
    scode = 11;
  else if ( symbol12 && IsSymbol(symbol12) )
    scode = 12;
  else if ( symbol13 && IsSymbol(symbol13) )
    scode = 13;
  else if ( symbol14 && IsSymbol(symbol14) )
    scode = 14;
  else if ( symbol15 && IsSymbol(symbol15) )
    scode = 15;

  return(scode);
}

/******************************************************************************/
/**
\brief  GetTextPosition - 



\param  high_bdata - 
\param  row_ref - 
\param  col_ref - 
\param  use_curpos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextPosition"

void BNFData :: GetTextPosition (BNFData *high_bdata, int32 &row_ref, int32 &col_ref, logical use_curpos )
{
  char                   *pos;
  char                   *start = NULL;
  char                   *next  = start;
BEGINSEQ
  row_ref = 0;
  col_ref = 0;

  if ( !this )                                      ERROR
  
  if ( !high_bdata )
    high_bdata = GetTop();

  pos = use_curpos ? Position() : StartPosition();
  start = high_bdata->StartPosition();
  
  if ( !pos )                                        ERROR
  
  row_ref = 1;
  while ( next = strchr(start,'\n') )
  {
    if ( pos <= next )
      break;
    row_ref++;
    start = next+1;
    if ( *start == '\r' )
      start++;
  }
  col_ref = pos-start+1;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  GetTop - 


\return bdata - Pointer to BNF Node

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTop"

BNFData *BNFData :: GetTop ( )
{
  BNFData          *bdata = this;
BEGINSEQ
  if ( !this )                                       ERROR
  while ( bdata->get_parent() )
    bdata = bdata->get_parent();


RECOVER
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  GetTopElement - 


\return bdata - Pointer to BNF Node

\param  symbol - Symbol name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTopElement"

BNFData *BNFData :: GetTopElement (char *symbol )
{
  int                     indx0 = 0;
  BNFData                *bdata = NULL;
BEGINSEQ
  while ( bdata = GetElement(indx0++) )
    if ( !strcmp(bdata->Name(),symbol) )              LEAVESEQ


ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  GetValue - 


\return value - 

\param  string - String value
\param  maxlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetValue"

char *BNFData :: GetValue (char *string, int32 maxlen )
{

BEGINSEQ
  if ( !value )                                  ERROR

  gvtxbts(string,value,MIN(value_len,maxlen));

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetValueLength - 


\return len - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetValueLength"

int32 BNFData :: GetValueLength ( )
{

  return ( value ? value_len : UNDEF );

}

/******************************************************************************/
/**
\brief  HasData - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasData"

logical BNFData :: HasData ( )
{

  return( this && value ? value + value_len > current_pos : NO );

}

/******************************************************************************/
/**
\brief  HasPreceedingChar - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasPreceedingChar"

logical BNFData :: HasPreceedingChar ( )
{
  char                   *pos = current_pos-1;
  return ( value < current_pos && (isalnum(*pos) || *pos == '_') );

}

/******************************************************************************/
/**
\brief  HasTerminator - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasTerminator"

logical BNFData :: HasTerminator ( )
{
  BNFData                *bdata = this;
  logical                 cond = NO;
  while ( (bdata = bdata->get_parent()) && !cond )
    if ( bdata->get_symbol()->get_terminate() )
      cond = YES;
  return(cond);
}

/******************************************************************************/
/**
\brief  InitChild - 


\return bdata - Pointer to BNF Node

\param  bparent - 
\param  bsymbol - BNF Symbol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitChild"

BNFData *BNFData :: InitChild (BNFData *bparent, BNFSymbol *bsymbol )
{
  BNFData             *bdata = NULL;
  pool_entry = YES;      // wird nur für entries im entry pool benutzt
  
  Initialize();
  
  symbol = bsymbol;
  
  if ( bparent )
  {
    parent = bparent;
    level = parent->get_level()+1;
    parent->AddChild(this);
    value = parent->get_current_pos();
    current_pos = value;
    value_len = parent->get_value() + parent->get_value_len() - value;
  }

  return(bdata);
}

/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void BNFData :: Initialize ( )
{

  symbol   = NULL;
  parent   = NULL;
  
  value       = NULL;
  current_pos = NULL;
  value_len   = 0;


}

/******************************************************************************/
/**
\brief  IntValue - 


\return intval - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IntValue"

int32 BNFData :: IntValue ( )
{

  return ( atol(StringValue()) );


}

/******************************************************************************/
/**
\brief  IsA - 


\return cond - Return value

\param  symbol - Symbol name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsA"

logical BNFData :: IsA (char *symbol )
{

  return ( !strcmp(Name(),symbol) ? YES : NO );


}

/******************************************************************************/
/**
\brief  IsSymbol - 


\return cond - Return value

\param  symbol - Symbol name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsSymbol"

logical BNFData :: IsSymbol (char *symbol )
{

  return ( GetSymbol(symbol) ? YES : NO );


}

/******************************************************************************/
/**
\brief  IsTerminalSymbol - Is smbol (part of a) terminal symbol
        The  function returns, whether the symbol analyzed is part of a terminal
        symbol  or not, i.e. if one of the symbols in the BNFData hierarchy is a
        symbol.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsTerminalSymbol"

logical BNFData :: IsTerminalSymbol ( )
{
//BNFData                *bdata = this ? parent : NULL;
  BNFData                *bdata = this;
  logical                 cond = YES;
BEGINSEQ
  while ( bdata )
  {
    if ( bdata->get_symbol()->get_terminate() )     LEAVESEQ
    bdata = bdata->get_parent();
  }

  ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsValue - 


\return cond - Return value

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValue"

logical BNFData :: IsValue (char *string )
{
  logical                 cond = YES;
BEGINSEQ
  if ( value_len != strlen(string) )                 ERROR
  if ( value_len == 1 && *string == *value )         LEAVESEQ

  if ( memcmp(value,string,value_len) )              ERROR
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  Name - 


\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Name"

char *BNFData :: Name ( )
{

   if (this && symbol) return symbol->get_name();
   else return "";

}

/******************************************************************************/
/**
\brief  Output - 


\return term - Success

\param  fstring - 
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
\param  parm3 - Third message variable
\param  parm4 - 
\param  parm5 - 
\param  parm6 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical BNFData :: Output (char *fstring, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5, char *parm6 )
{
  char                    string[4096];
  logical                 term = NO;
  if ( !fstring )
    fstring = "\n*** format string missing for output command ***";
  
  sprintf(string,fstring,parm1,parm2,parm3,parm4,parm5);
  SystemOutput(string,NO,YES);


  return(term);
}

/******************************************************************************/
/**
\brief  Parent - 


\return bdata - Pointer to BNF Node

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parent"

BNFData *BNFData :: Parent ( )
{

  return(this ? parent : NULL);

}

/******************************************************************************/
/**
\brief  Position - 


\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Position"

char *BNFData :: Position ( )
{

  return(current_pos);

}

/******************************************************************************/
/**
\brief  Print - 


\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - 


\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Print"

logical BNFData :: Print (logical recursive )
{
  logical                 term = NO;
  Print((FILE *)NULL,recursive,NO);
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  path - Complete path
\param  recursive - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Print"

logical BNFData :: Print (char *path, logical recursive )
{
  FILE                   *fileptr = NULL;
  logical                 term = NO;
BEGINSEQ
  if ((fileptr = fopen(path,"w")) == 0)            ERROR
    
  Print(fileptr,recursive,NO);
  
  fclose(fileptr);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 


\param  fileptr - 
\param  recursive - 
\param  erropt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Print"

logical BNFData :: Print (FILE *fileptr, logical recursive, logical erropt )
{
  char                    string[1024];
  BNFData                *bdata;
  int                     len;
  char                   *pos;
  logical                 term = NO;
  memset(string,' ',sizeof(string));
  *string = '\n';
  pos = string+level*2+1;
  if ( erropt )
    *(pos-1) = '*';
  strcpy(pos,Name());
  pos = string+strlen(string);
  strcpy(pos,": ");
  pos += 2;
  len = MIN(value_len,sizeof(string)-(pos-string)-5);
  memcpy(pos,value,len);
  pos[len] = 0;
  if ( strchr(pos,'\n') )
    len = strchr(pos,'\n') - pos - 1;
  strcpy(pos+len," ...");
  if ( fileptr )
    fprintf(fileptr,string);
  else
    Output(string);

  if ( recursive && elements )
  {
    elements->GoTop();
    while ( bdata = elements->GetNext() )  
      bdata->Print(fileptr,recursive,erropt);
  }


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

logical BNFData :: PrintError ( )
{
  char                    string[65];
  logical                 term = NO;
  gvtxbts(string,current_pos,MIN(sizeof(string)-1,value_len-(current_pos-value)));
  Output("\nNo match for '%s' at: ... %s",symbol->get_name(),string);

  return(term);
}

/******************************************************************************/
/**
\brief  Release - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Release"

void BNFData :: Release ( )
{
  BNFData         *bdata;
  if ( parent )
    parent->RemoveChild(this,NO);
  parent = NULL;

  // die elements werden im Pool das Parsers verwaltet und dürfen nicht freigegeben werden
  if ( elements )
    while ( bdata = elements->RemoveHead() )
      if ( bdata->get_pool_entry() )
      {
        bdata->Release();
        if ( symbol )
          symbol->get_top_symbol()->RemoveChild(bdata);
      }
      else
        delete bdata;


}

/******************************************************************************/
/**
\brief  RemoveChild - 


\return bdata - Pointer to BNF Node

\param  bdata - Pointer to BNF Node
\param  del_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveChild"

BNFData *BNFData :: RemoveChild (BNFData *bdata, logical del_opt )
{

BEGINSEQ
  if ( !elements || !elements->Find(bdata) )          ERROR
    
  bdata = elements->RemoveAt();
  if ( del_opt )
    delete bdata;

RECOVER
  bdata = NULL;
ENDSEQ
  return(bdata);
}

/******************************************************************************/
/**
\brief  RemoveChildren - 



\param  bstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveChildren"

void BNFData :: RemoveChildren (BNFParser *bstring )
{
  BNFData             *bdata = NULL;
  if ( elements )
    while ( bdata = elements->RemoveTail() )
      if ( bdata->get_pool_entry() )
        bstring->RemoveChild(bdata);
      else
        delete bdata;

}

/******************************************************************************/
/**
\brief  RemoveLastChild - 


\return term - Success

\param  skip_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveLastChild"

logical BNFData :: RemoveLastChild (logical skip_opt )
{
  BNFData           *last_child;
  BNFParser         *bparser;
  int                count;
  logical            term = NO;
  if ( elements && (last_child = elements->GetTail()) )
  {
    if ( symbol && (bparser = symbol->get_top_symbol()) )
      bparser->RemoveChild(last_child);
    else
      RemoveChild(last_child,YES);
    UpdatePosition(skip_opt);
  }


  return(term);
}

/******************************************************************************/
/**
\brief  RemoveLastChildren - 


\return term - Success

\param  bdata - Pointer to BNF Node
\param  skip_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveLastChildren"

logical BNFData :: RemoveLastChildren (BNFData *bdata, logical skip_opt )
{
  BNFData           *last_child;
  BNFParser         *bparser;
  logical            term = NO;
BEGINSEQ
  if ( !this || !elements )                          LEAVESEQ

  if ( !bdata || elements->Find(bdata) )
    while ( last_child = elements->GetTail() )
      if ( bdata && last_child == bdata )            LEAVESEQ
      else RemoveLastChild(skip_opt);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RemoveParent - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RemoveParent"

logical BNFData :: RemoveParent ( )
{
  logical                 term = NO;
  if ( parent )
  {
    parent->RemoveParent();
    delete parent;
    parent = NULL;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  Reset - 



\param  bstring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void BNFData :: Reset (BNFParser *bstring )
{

  if ( parent )
    parent->RemoveChild(this,NO);
  
  if ( bstring )
    RemoveChildren(bstring);
    
  delete elements;
  elements = NULL;

  value       = NULL;
  value_len   = 0;
  current_pos = NULL;
  
  parent      = NULL;
  symbol      = NULL;

}

/******************************************************************************/
/**
\brief  SetLength - 



\param  string_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetLength"

void BNFData :: SetLength (int32 string_len )
{

  if ( string_len )
    value_len = string_len;
  else
    value_len = current_pos - value;


}

/******************************************************************************/
/**
\brief  SkipSpaces - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SkipSpaces"

void BNFData :: SkipSpaces ( )
{
  BNFParser  *bparser = symbol ? symbol->get_top_symbol() : NULL;
  char       *init_comment = bparser ? bparser->get_init_comment() : NULL;
  logical     skip_nl = bparser ? bparser->get_skip_nl() : YES;
  char       *end = value + value_len;
BEGINSEQ
  while ( current_pos )
  {
    while ( current_pos < end && 
            (*current_pos == 32 || *current_pos == 9 || 
             (skip_nl && (*current_pos == 13 || *current_pos == 10) ) ) )
    {
      current_pos++;
      separated = YES;
    }
    if ( !init_comment || memcmp(current_pos,init_comment,strlen(init_comment)) )
                                                     LEAVESEQ
    while ( *current_pos != 13 && *current_pos != 10 )
      current_pos++;
    
  }

ENDSEQ

}

/******************************************************************************/
/**
\brief  StartPosition - 


\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StartPosition"

char *BNFData :: StartPosition ( )
{

  return(value);

}

/******************************************************************************/
/**
\brief  StringValue - 


\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StringValue"

char *BNFData :: StringValue ( )
{

  if ( this )                                       
    nstring.SetString(value,value_len);

  return(this ? nstring : NString((int)NULL));
}

/******************************************************************************/
/**
\brief  TopParent - 


\return bdata - Pointer to BNF Node

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "TopParent"

BNFData *BNFData :: TopParent ( )
{
  BNFData      *bdata = this;
  while ( bdata->get_parent() )
    bdata = bdata->get_parent();
 return(bdata);
}

/******************************************************************************/
/**
\brief  UpdatePosition - 


-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdatePosition"

void BNFData :: UpdatePosition ( )
{
  BNFData           *last_child;
  current_pos = value;
  if ( elements && (last_child = elements->GetTail()) )
    current_pos = last_child->get_value() + last_child->get_value_len();
  


}

/******************************************************************************/
/**
\brief  i01 - 


\param  bsymbol - BNF Symbol
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdatePosition"

void BNFData :: UpdatePosition (BNFSymbol *bsymbol )
{

  value_len = bsymbol->get_name_len();
  current_pos = value + value_len;
  


}

/******************************************************************************/
/**
\brief  i02 - 


\param  cpos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdatePosition"

void BNFData :: UpdatePosition (char *cpos )
{

  if ( this ) 
  {
    current_pos = cpos;
    parent->UpdatePosition(cpos);
  }


}

/******************************************************************************/
/**
\brief  i03 - 


\param  skip_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdatePosition"

void BNFData :: UpdatePosition (logical skip_opt )
{

  UpdatePosition();
  
  if ( skip_opt )
    SkipSpaces();

}

/******************************************************************************/
/**
\brief  operator= - 


\return bdata_ref - 

\param  bdata - Pointer to BNF Node
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

BNFData &BNFData :: operator= (BNFData *bdata )
{

  current_pos = bdata->Position();
  value       = bdata->get_value();
  value_len   = bdata->get_value_len();
  symbol      = bdata->get_symbol();

  return(*this);
}

/******************************************************************************/
/**
\brief  ~BNFData - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BNFData"

     BNFData :: ~BNFData ( )
{

  Reset(symbol ? symbol->get_top_symbol() : NULL);
//  Deinitialize();

}


