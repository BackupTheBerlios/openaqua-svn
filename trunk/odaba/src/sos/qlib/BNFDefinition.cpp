/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BNFDefinition

\brief    BNF for default BNF support
          This  definition describes  the BNF,  that is  used for generating BNF
          parser  from a BNF  definition. Those definitions  must be provided in
          the format defined below:

          bnf         := symdef(*) tsymdef(*)
          symdef      := name ':=' expr [ alt_expr(*) ] nl
          alt_expr    := '|' expr 
          expr        := mult_symbol [ osymbol(*) ]  
          osymbol     := psymbol | mult_symbol
          psymbol     := '[' mult_symbol ']'
          mult_symbol := elm_symbol [ sym_count ]
          sym_count   := '(' onumber ')'
          onumber     := * | number
          elm_symbol  := name | cstring
  
          tsymdef     := name '::=' symref nl
          symref      := 'class' '(' name ')' | 'ref' '(' name ')'

          name       ::= class(BNF_std_name)
          number     ::= ref(number)
          _          ::= ref(space)
          nl         ::= ref(nl)
          cstring    ::= ref(const_string)

          Between  two symbols  in an  expression spaces  (blank or newline) may
          appear.  When blanks must appear, you may define this as 'a _ b', i.e.
          at  least  one  separator  must  appear between a and b. Fixed symbols
          must be written in quotes.

\date     $Date: 2006/03/12 19:21:10,12 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BNFDefinition"

#include  <pdefault.h>
#include  <sBNFExpression.hpp>
#include  <sBNFParser.hpp>
#include  <sBNFStandardSymbols.hpp>
#include  <sBNFDefinition.hpp>


/******************************************************************************/
/**
\brief  BNFDefinition


\param  bs_parent - Parent parser
\param  trace_path - Trace file location
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFDefinition"

                        BNFDefinition :: BNFDefinition (BNFParser *bs_parent, char *trace_path )
                     : BNFParser ("bnf",bs_parent,NO,NO,trace_path)
{
  BNFExpression *__expression;

/*
  bnf         := bnf_stmt(*) 
  bnf_stmt    := definition | keyword | reference | comment_line | nl

  definition  := sym_name ':=' rule [comment] nl
  rule        := prule [ alt_prule(*) ] 
  alt_prule   := '|' prule 
  prule       := ext_symbol(*)
  ext_symbol  := elm_symbol [ multiple ]
  multiple    := '(' maxnum ')'
  maxnum      := '*' | std_number
  elm_symbol  := sym_name | cstring | impl_symbol | opt_symbol
  impl_symbol := '{' rule '}' 
  opt_symbol  := '[' rule ']'
  
  keyword     := sym_name '::' keydef [ alt_keydef(*) ] nl
  alt_keydef  := '|' keydef 
  keydef      := cstring

  reference   := name '::=' symref nl
  symref      := class_ref | symbol_ref
  class_ref   := 'class' '(' name ')' 
  symbol_ref  := 'ref' '(' name ')'

  sym_name    := name
  name        := std_name
  cstring     := std_str
  
  comment_line:= comment nl
  comment     := '//' std_anychar(*)

  CC          := '//'
  
  std_symbols ::= class(BNFStandardSymbols)
  std_name    ::= ref(std_name)
  std_number  ::= ref(std_integer)
  std_str     ::= ref(std_string)
  std_anychar ::= ref(std_anychar)
  nl          ::= ref(std_nl)

*/


  BNFSymbol  *bnf = this;
  if ( !bs_parent ) bs_parent = this;

  BNFSymbol  *std_symbols = new BNFStandardSymbols(bs_parent);
  BNFSymbol  *std_name = top_symbol->GetSymbol("std_name");
  BNFSymbol  *std_number = top_symbol->GetSymbol("std_integer");
  BNFSymbol  *std_str = top_symbol->GetSymbol("std_string");
  BNFSymbol  *std_anychar = top_symbol->GetSymbol("std_anychar");
  BNFSymbol  *nl = top_symbol->GetSymbol("std_nl");
  if ( !bs_parent || bs_parent == this )
    SetFirst();
  BNFSymbol  *bnf_stmt = new BNFSymbol(top_symbol,"bnf_stmt");
  BNFSymbol  *definition = new BNFSymbol(top_symbol,"definition");
  BNFSymbol  *rule = new BNFSymbol(top_symbol,"rule");
  BNFSymbol  *alt_prule = new BNFSymbol(top_symbol,"alt_prule");
  BNFSymbol  *prule = new BNFSymbol(top_symbol,"prule");
  BNFSymbol  *ext_symbol = new BNFSymbol(top_symbol,"ext_symbol");
  BNFSymbol  *multiple = new BNFSymbol(top_symbol,"multiple");
  BNFSymbol  *maxnum = new BNFSymbol(top_symbol,"maxnum");
  BNFSymbol  *elm_symbol = new BNFSymbol(top_symbol,"elm_symbol");
  BNFSymbol  *impl_symbol = new BNFSymbol(top_symbol,"impl_symbol");
  BNFSymbol  *opt_symbol = new BNFSymbol(top_symbol,"opt_symbol");
  BNFSymbol  *keyword = new BNFSymbol(top_symbol,"keyword");
  BNFSymbol  *alt_keydef = new BNFSymbol(top_symbol,"alt_keydef");
  BNFSymbol  *keydef = new BNFSymbol(top_symbol,"keydef");
  BNFSymbol  *reference = new BNFSymbol(top_symbol,"reference");
  BNFSymbol  *symref = new BNFSymbol(top_symbol,"symref");
  BNFSymbol  *class_ref = new BNFSymbol(top_symbol,"class_ref");
  BNFSymbol  *symbol_ref = new BNFSymbol(top_symbol,"symbol_ref");
  BNFSymbol  *sym_name = new BNFSymbol(top_symbol,"sym_name");
  BNFSymbol  *name = new BNFSymbol(top_symbol,"name");
  BNFSymbol  *cstring = new BNFSymbol(top_symbol,"cstring");
  BNFSymbol  *comment_line = new BNFSymbol(top_symbol,"comment_line");
  BNFSymbol  *comment = new BNFSymbol(top_symbol,"comment");

// bnf
  __expression = new BNFExpression(bnf);
    __expression->AddElement(bnf_stmt,NO,UNDEF,YES,YES);

// bnf_stmt
  __expression = new BNFExpression(bnf_stmt);
    __expression->AddElement(definition,NO,1,YES,YES);
  __expression = new BNFExpression(bnf_stmt);
    __expression->AddElement(keyword,NO,1,YES,YES);
  __expression = new BNFExpression(bnf_stmt);
    __expression->AddElement(reference,NO,1,YES,YES);
  __expression = new BNFExpression(bnf_stmt);
    __expression->AddElement(comment_line,NO,1,YES,YES);
  __expression = new BNFExpression(bnf_stmt);
    __expression->AddElement(nl,NO,1,YES,YES);

// definition
  __expression = new BNFExpression(definition);
    __expression->AddElement(sym_name,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
    __expression->AddElement(rule,NO,1,YES,YES);
    __expression->AddElement(comment,YES,1,YES,YES);
    __expression->AddElement(nl,NO,1,YES,YES);

// rule
  __expression = new BNFExpression(rule);
    __expression->AddElement(prule,NO,1,YES,YES);
    __expression->AddElement(alt_prule,YES,UNDEF,YES,YES);

// alt_prule
  __expression = new BNFExpression(alt_prule);
    __expression->AddElement(ElementaryToken('|'),NO,1,NO,YES);
    __expression->AddElement(prule,NO,1,YES,YES);

// prule
  __expression = new BNFExpression(prule);
    __expression->AddElement(ext_symbol,NO,UNDEF,YES,YES);

// ext_symbol
  __expression = new BNFExpression(ext_symbol);
    __expression->AddElement(elm_symbol,NO,1,YES,YES);
    __expression->AddElement(multiple,YES,1,YES,YES);

// multiple
  __expression = new BNFExpression(multiple);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(maxnum,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// maxnum
  __expression = new BNFExpression(maxnum);
    __expression->AddElement(ElementaryToken('*'),NO,1,NO,YES);
  __expression = new BNFExpression(maxnum);
    __expression->AddElement(std_number,NO,1,YES,YES);

// elm_symbol
  __expression = new BNFExpression(elm_symbol);
    __expression->AddElement(sym_name,NO,1,YES,YES);
  __expression = new BNFExpression(elm_symbol);
    __expression->AddElement(cstring,NO,1,YES,YES);
  __expression = new BNFExpression(elm_symbol);
    __expression->AddElement(impl_symbol,NO,1,YES,YES);
  __expression = new BNFExpression(elm_symbol);
    __expression->AddElement(opt_symbol,NO,1,YES,YES);

// impl_symbol
  __expression = new BNFExpression(impl_symbol);
    __expression->AddElement(ElementaryToken('{'),NO,1,NO,YES);
    __expression->AddElement(rule,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('}'),NO,1,NO,YES);

// opt_symbol
  __expression = new BNFExpression(opt_symbol);
    __expression->AddElement(ElementaryToken('['),NO,1,NO,YES);
    __expression->AddElement(rule,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(']'),NO,1,NO,YES);

// keyword
  __expression = new BNFExpression(keyword);
    __expression->AddElement(sym_name,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,YES);
    __expression->AddElement(keydef,NO,1,YES,YES);
    __expression->AddElement(alt_keydef,YES,UNDEF,YES,YES);
    __expression->AddElement(nl,NO,1,YES,YES);

// alt_keydef
  __expression = new BNFExpression(alt_keydef);
    __expression->AddElement(ElementaryToken('|'),NO,1,NO,YES);
    __expression->AddElement(keydef,NO,1,YES,YES);

// keydef
  __expression = new BNFExpression(keydef);
    __expression->AddElement(cstring,NO,1,YES,YES);

// reference
  __expression = new BNFExpression(reference);
    __expression->AddElement(name,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken(':'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('='),NO,1,NO,YES);
    __expression->AddElement(symref,NO,1,YES,YES);
    __expression->AddElement(nl,NO,1,YES,YES);

// symref
  __expression = new BNFExpression(symref);
    __expression->AddElement(class_ref,NO,1,YES,YES);
  __expression = new BNFExpression(symref);
    __expression->AddElement(symbol_ref,NO,1,YES,YES);

// class_ref
  __expression = new BNFExpression(class_ref);
    __expression->AddElement(ElementaryToken('c'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('s'),NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(name,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// symbol_ref
  __expression = new BNFExpression(symbol_ref);
    __expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('e'),NO,1,YES,NO);
    __expression->AddElement(ElementaryToken('f'),NO,1,YES,YES);
    __expression->AddElement(ElementaryToken('('),NO,1,NO,YES);
    __expression->AddElement(name,NO,1,YES,YES);
    __expression->AddElement(ElementaryToken(')'),NO,1,NO,YES);

// sym_name
  __expression = new BNFExpression(sym_name);
    __expression->AddElement(name,NO,1,YES,YES);

// name
  __expression = new BNFExpression(name);
    __expression->AddElement(std_name,NO,1,YES,YES);

// cstring
  __expression = new BNFExpression(cstring);
    __expression->AddElement(std_str,NO,1,YES,YES);

// comment_line
  __expression = new BNFExpression(comment_line);
    __expression->AddElement(comment,NO,1,YES,YES);
    __expression->AddElement(nl,NO,1,YES,YES);

// comment
  __expression = new BNFExpression(comment);
    __expression->AddElement(ElementaryToken('/'),NO,1,NO,NO);
    __expression->AddElement(ElementaryToken('/'),NO,1,NO,YES);
    __expression->AddElement(std_anychar,NO,UNDEF,YES,YES);

// CC
  SetCC("//");

  if ( !bs_parent || bs_parent == this )
    ReorderSymbols();


}

/******************************************************************************/
/**
\brief  ~BNFDefinition


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BNFDefinition"

                        BNFDefinition :: ~BNFDefinition ( )
{



}


