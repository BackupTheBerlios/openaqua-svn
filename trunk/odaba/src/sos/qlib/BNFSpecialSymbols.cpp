/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BNFSpecialSymbols

\brief    


\date     $Date: 2006/03/12 19:21:13,39 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BNFSpecialSymbols"

#include  <pdefault.h>
#include  <sBNFParser.hpp>
#include  <sBNFSpecialSymbols.hpp>


/******************************************************************************/
/**
\brief  BNFSpecialSymbols


\param  bs_parent - Parent parser
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFSpecialSymbols"

                        BNFSpecialSymbols :: BNFSpecialSymbols (BNFParser *bs_parent )
                     : BNFParser ("spec_symbols",bs_parent,NO,YES)
{
  uint16         i;
  BNFExpression *expression;
/*
 spec_plist     := spec_plistchar(*)
 spec_block     := spec_blockchar(*)
 spec_line      := [spec_nl_line(*)] spec_last_line
 specc_nl_line  := [spec_linechar(*)] '\'
 spec_last_line := [spec_linechar(*)] nl
 spec_plistchar := 1-255 except: ( )
 spec_blockchar := 1-255 except: { } 10 13
 spec_linechar  := 1-255 except: 10, 13, \
 spec_bnfchar   := 1-255 except: 10, 13, ' ', '|' '[' ']' \
*/
// symbols
  BNFSymbol  *spec_plist      = new BNFSymbol(top_symbol,"spec_plist",YES);
  BNFSymbol  *spec_block      = new BNFSymbol(top_symbol,"spec_block",YES);
  BNFSymbol  *spec_line       = new BNFSymbol(top_symbol,"spec_line",YES);
  BNFSymbol  *spec_nl_line    = new BNFSymbol(top_symbol,"spec_nl_line");
  BNFSymbol  *spec_last_line  = new BNFSymbol(top_symbol,"spec_last_line");
  BNFSymbol  *spec_plistchar  = new BNFSymbol(top_symbol,"spec_plistchar");
  BNFSymbol  *spec_blockchar  = new BNFSymbol(top_symbol,"spec_blockchar");
  BNFSymbol  *spec_linechar   = new BNFSymbol(top_symbol,"spec_linechar");

// spec_plist     := spec_plistchar(*)
  expression = new BNFExpression(spec_plist);
    expression->AddElement(spec_plistchar,NO,UNDEF,YES,NO);

// spec_block     := spec_blockchar(*)
  expression = new BNFExpression(spec_block);
    expression->AddElement(spec_blockchar,NO,UNDEF,YES,NO);

// spec_line      := [spec_nl_line(*)] spec_last_line
  expression = new BNFExpression(spec_line);
    expression->AddElement(spec_nl_line,YES,UNDEF,YES,YES);
    expression->AddElement(spec_last_line,NO,1,YES,YES);

// spec_nl_line   := [spec_linechar(*)] '\'
  expression = new BNFExpression(spec_nl_line);
    expression->AddElement(spec_linechar,YES,UNDEF,YES,NO);
    expression->AddElement(ElementaryToken('\\'),NO,1,YES,YES);
 
// spec_last_line := [spec_linechar(*)] nl
  expression = new BNFExpression(spec_last_line);
    expression->AddElement(spec_linechar,YES,UNDEF,YES,NO);
    expression->AddElement(ElementaryToken(13),YES,1,YES,NO);
    expression->AddElement(ElementaryToken(10),NO,1,YES,NO);
 
// spec_plistchar := 1-255 except: ( )
  i = 0;
  while ( ++i < 256 )
    if ( i != '(' && i != ')' )
    {
      expression = new BNFExpression(spec_plistchar);
      expression->AddElement(ElementaryToken(i),NO,1,YES,NO);
    }
    
// spec_blockchar := 1-255 except: { } 10 13
  i = 0;
  while ( ++i < 256 )
    if ( i != '{' && i != '}' && i != 10 && i != 13 && i != '"' && i != '\'' )
    {
      expression = new BNFExpression(spec_blockchar);
      expression->AddElement(ElementaryToken(i),NO,1,YES,NO);
    }
    
// spec_linechar  := 1-255 except: 10, 13, '\'
  i = 0;
  while ( ++i < 256 )
    if ( i != '\\' && i != 10 && i != 13  )
    {
      expression = new BNFExpression(spec_linechar);
      expression->AddElement(ElementaryToken(i),NO,1,YES,NO);
    }
    
  if ( !bs_parent )
    ReorderSymbols();

}

/******************************************************************************/
/**
\brief  ~BNFSpecialSymbols


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BNFSpecialSymbols"

                        BNFSpecialSymbols :: ~BNFSpecialSymbols ( )
{



}


