/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BNFStandardSymbols

\brief    Definition for standard symbols
          This  class contains a  number of definitions  for standard symbols as
          name,  number, constant etc. Standard symbols can be made available by
          deriving  a BNF class  from the standard  symbols class or by creating
          an instance of the standard symbol class in your BNF parser.
          You can find the BNF for the defined standard symbols below. 

          std_constant := std_number | std_string
          std_name := std_alpha [ std_nchars ]

          std_number = std_integer | std_decimal | std_float
          std_integer := std_digits | '+' std_digits | '-' std_digits
          std_decimal .= std_integer [ '.' std_digits
          std_float := std_decimal 'E' std_integer
  
          std:string   :=   '\''   [   std_str1section(*)   ]   '\''   |   '"' [
          std_str2section(*) ] '"'
          std_str1section := std_cchar1(*) [ '\\\'' ]
          std_str2section := std_cchar2(*) [ '\\"' ]

          std_nchars := std_nchar(*)
          std_nchar := std_alpha | std_digit | std_nspec

          std_digits := std_digit(*)
          std_digit := 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
          std_alpha  := a | b | c | d | e | f | g  | h | i | j | k | l | m | n |
          o | p | q | r | s | t | u | v | w | x | y | z |
          A  | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R
          | S | T | U | V | W | X | Y | Z
          std_npec := _ | $ 
          std_cchar1 = std_cchar | '"'
          std_cchar2 = std_cchar | '\''
          std_cchar := 1-255 except: ', " and \
          ected  with  the  calling  hierarchy.  This  is  done automatically by
          connect functions and reset by disconnect functions.

\date     $Date: 2006/03/12 19:21:13,50 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "BNFStandardSymbols"

#include  <pdefault.h>
#include  <sBNFParser.hpp>
#include  <sBNFStandardSymbols.hpp>


/******************************************************************************/
/**
\brief  BNFStandardSymbols


\param  bs_parent - Parent parser
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "BNFStandardSymbols"

                        BNFStandardSymbols :: BNFStandardSymbols (BNFParser *bs_parent )
                     : BNFParser ("std_symbols",bs_parent,NO,YES)
{
  uint16         i;
  BNFExpression *expression;
/*
  std_constant  := std_float | std_string | std_bool
  
  std_bool      := 'false' | 'true' | 'FALSE' | 'TRUE' | 'YES' | 'NO'
  
  std_name      := std_alpha1 [ std_nchars ]
  std_alpha1    := std_alpha | std_nspec

  std_number    := std_integer | std_decimal | std_float
  std_float     := std_decimal [ std_floatp ]
  std_floatp    := 'E' std_integer
  std_decimal   := std_integer [ std_decimalp ]
  std_decimalp  := '.' std_digits
  std_integer   := std_digits | '+' std_digits | '-' std_digits
  std_line_end  := [' '(*)] nl
  
  std_string    := '\'' [std_str1(*)] '\'' | '"' [std_str2(*)] '"'
  std_str1      := std_cchar1(*) 
  std_str2      := std_cchar2(*) 

  std_comment   := 0x01 [std_comchar(*)] 0x02
  std_comchar   := 1-255 except: 0x01, 0x02 (for / * and * /)
  std_bnfchar   := 33-255 except: ; <
  
  std_anychars  := std_anychar(*)
  std_nchars    := std_nchar(*)
  std_nchar     := std_alpha | std_digit | std_nspec
  std_digits    := std_digit(*)
  std_cchar1    := std_cchar | \' | "
  std_cchar2    := std_cchar | \" | '
  std_separators:= std_separator(*)
  std_separator := ' ' | std_nl | 0x09

  std_digit     := 0 - 9  
  std_alpha     := a - z | A - Z
  std_cchar     := std_bss | 1-255 except: ' " \
  std_bss       := std_bs | '\\n' | '\\t' | '\\r'
  std_bs        := \\
  std_anychar   := 1-255 except: 0x0D, 0x0A
  std_nspec     := '_' | '$' 
  std_nl        := 0x0A | 0x0D 0x0A
*/
// symbols
  BNFSymbol  *std_constant    = new BNFSymbol(top_symbol,"std_constant");
  BNFSymbol  *std_bool        = new BNFSymbol(top_symbol,"std_bool",YES);
  BNFSymbol  *std_name        = new BNFSymbol(top_symbol,"std_name",YES);
  BNFSymbol  *std_number      = new BNFSymbol(top_symbol,"std_number",YES);
  BNFSymbol  *std_float       = new BNFSymbol(top_symbol,"std_float");
  BNFSymbol  *std_floatp      = new BNFSymbol(top_symbol,"std_floatp");
  BNFSymbol  *std_decimal     = new BNFSymbol(top_symbol,"std_decimal");
  BNFSymbol  *std_decimalp    = new BNFSymbol(top_symbol,"std_decimalp");
  BNFSymbol  *std_integer     = new BNFSymbol(top_symbol,"std_integer",YES);
  BNFSymbol  *std_line_end    = new BNFSymbol(top_symbol,"std_line_end",YES);
  BNFSymbol  *std_str         = new BNFSymbol(top_symbol,"std_string",YES);
  BNFSymbol  *std_str1        = new BNFSymbol(top_symbol,"std_str1");
  BNFSymbol  *std_str2        = new BNFSymbol(top_symbol,"std_str2");
  BNFSymbol  *std_comment     = new BNFSymbol(top_symbol,"std_comment",YES);
  BNFSymbol  *std_comchar     = new BNFSymbol(top_symbol,"std_comchar");
  BNFSymbol  *std_bnfchar     = new BNFSymbol(top_symbol,"std_bnfchar");
  BNFSymbol  *std_anychars    = new BNFSymbol(top_symbol,"std_anychars",YES);
  BNFSymbol  *std_nchars      = new BNFSymbol(top_symbol,"std_nchars");
  BNFSymbol  *std_nchar       = new BNFSymbol(top_symbol,"std_nchar");
  BNFSymbol  *std_digits      = new BNFSymbol(top_symbol,"std_digits",YES);
  BNFSymbol  *std_cchar1      = new BNFSymbol(top_symbol,"std_cchar1");
  BNFSymbol  *std_cchar2      = new BNFSymbol(top_symbol,"std_cchar2");
  BNFSymbol  *std_separators  = new BNFSymbol(top_symbol,"std_separators");
  BNFSymbol  *std_separator   = new BNFSymbol(top_symbol,"std_separator");
  BNFSymbol  *std_bss         = new BNFSymbol(top_symbol,"std_bss");
  BNFSymbol  *std_bs          = new BNFSymbol(top_symbol,"std_bs");
  BNFSymbol  *std_digit       = new BNFSymbol(top_symbol,"std_digit");
  BNFSymbol  *std_alpha1      = new BNFSymbol(top_symbol,"std_alpha1");
  BNFSymbol  *std_alpha       = new BNFSymbol(top_symbol,"std_alpha");
  BNFSymbol  *std_cchar       = new BNFSymbol(top_symbol,"std_cchar");
  BNFSymbol  *std_anychar     = new BNFSymbol(top_symbol,"std_anychar");
  BNFSymbol  *std_nspec       = new BNFSymbol(top_symbol,"std_nspec");
  BNFSymbol  *std_nl          = new BNFSymbol(top_symbol,"std_nl",YES);
    
// std_symbol := std_constant | std_name | std_separator
  expression = new BNFExpression(this);
    expression->AddElement(std_constant,NO,1,YES,NO);
  expression = new BNFExpression(this);
    expression->AddElement(std_name,NO,1,YES,NO);
  expression = new BNFExpression(this);
    expression->AddElement(std_separator,NO,1,YES,NO);

// std_constant := std_float | std_string | std_bool
  expression = new BNFExpression(std_constant);
    expression->AddElement(std_float,NO,1,YES,NO);
  expression = new BNFExpression(std_constant);
    expression->AddElement(std_str,NO,1,YES,NO);
  expression = new BNFExpression(std_constant);
    expression->AddElement(std_bool,NO,1,YES,NO);

// std_bool := 'false' | 'true' | 'FALSE' | 'TRUE'
  expression = new BNFExpression(std_bool);
    expression->AddElement(ElementaryToken('f'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('a'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('l'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('s'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  expression = new BNFExpression(std_bool);
    expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('u'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('e'),NO,1,YES,YES);
  expression = new BNFExpression(std_bool);
    expression->AddElement(ElementaryToken('F'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('A'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('L'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('S'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('E'),NO,1,YES,YES);
  expression = new BNFExpression(std_bool);
    expression->AddElement(ElementaryToken('T'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('R'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('U'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('E'),NO,1,YES,YES);
  expression = new BNFExpression(std_bool);
    expression->AddElement(ElementaryToken('Y'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('E'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('S'),NO,1,YES,NO);
  expression = new BNFExpression(std_bool);
    expression->AddElement(ElementaryToken('N'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('O'),NO,1,YES,NO);
//  std_bool->SetKeyword();
  
// std_name := std_alpha1 [ std_nchars ]
  expression = new BNFExpression(std_name);
    expression->AddElement(std_alpha1,NO,1,YES,NO);
    expression->AddElement(std_nchars,YES,1,YES,NO);

// std_alpha1    := std_alpha | std_nspec
  expression = new BNFExpression(std_alpha1);
    expression->AddElement(std_alpha,NO,1,YES,NO);
  expression = new BNFExpression(std_alpha1);
    expression->AddElement(std_nspec,NO,1,YES,NO);

// std_number := std_integer | std_decimal | std_float
  expression = new BNFExpression(std_number);
    expression->AddElement(std_integer,NO,1,YES,NO);
  expression = new BNFExpression(std_number);
    expression->AddElement(std_decimal,NO,1,YES,NO);
  expression = new BNFExpression(std_number);
    expression->AddElement(std_float,NO,1,YES,NO);

// std_float := std_decimal [ std_floatp ]
  expression = new BNFExpression(std_float);
    expression->AddElement(std_decimal,NO,1,YES,NO);
    expression->AddElement(std_floatp,YES,1,YES,NO);

// std_floatp := 'E' std_integer
  expression = new BNFExpression(std_floatp);
    expression->AddElement(ElementaryToken('E'),NO,1,YES,NO);
    expression->AddElement(std_integer,NO,1,YES,NO);

// std_decimal := std_integer [ std_decimalp ]
  expression = new BNFExpression(std_decimal);
    expression->AddElement(std_integer,NO,1,YES,NO);
    expression->AddElement(std_decimalp,YES,1,YES,NO);

// std_decimalp := '.' std_digits
  expression = new BNFExpression(std_decimalp);
    expression->AddElement(ElementaryToken('.'),NO,1,YES,NO);
    expression->AddElement(std_digits,NO,1,YES,NO);

// std_integer := std_digits | '+' std_digits | '-' std_digits
  expression = new BNFExpression(std_integer);
    expression->AddElement(std_digits,NO,1,YES,NO);
  expression = new BNFExpression(std_integer);
    expression->AddElement(ElementaryToken('+'),NO,1,YES,NO);
    expression->AddElement(std_digits,NO,1,YES,NO);
  expression = new BNFExpression(std_integer);
    expression->AddElement(ElementaryToken('-'),NO,1,YES,NO);
    expression->AddElement(std_digits,NO,1,YES,NO);

//  std_line_end  := [' '(*)] nl
  expression = new BNFExpression(std_line_end);
    expression->AddElement(ElementaryToken(' '),YES,UNDEF,YES,NO);
    expression->AddElement(std_nl,NO,1,YES,NO);

// std_string := '\'' [ std_str1(*) ] '\'' | '"' [ std_str2(*) ] '"'
  expression = new BNFExpression(std_str);
    expression->AddElement(ElementaryToken('\''),NO,1,YES,NO);
    expression->AddElement(std_str1,YES,UNDEF,YES,NO);
    expression->AddElement(ElementaryToken('\''),NO,1,YES,NO);
  expression = new BNFExpression(std_str);
    expression->AddElement(ElementaryToken('"'),NO,1,YES,NO);
    expression->AddElement(std_str2,YES,UNDEF,YES,NO);
    expression->AddElement(ElementaryToken('"'),NO,1,YES,NO);

// std_str1 := std_cchar1(*) 
  expression = new BNFExpression(std_str1);
    expression->AddElement(std_cchar1,NO,UNDEF,YES,NO);

// std_str2 := std_cchar2(*) 
  expression = new BNFExpression(std_str2);
    expression->AddElement(std_cchar2,NO,UNDEF,YES,NO);
  
// std_comment := 0x01 [std_comchar(*)] 0x02
  expression = new BNFExpression(std_comment);
    expression->AddElement(ElementaryToken(1),NO,1,NO,NO);
    expression->AddElement(ElementaryToken(1),NO,1,NO,NO);
    expression->AddElement(std_comchar,YES,UNDEF,NO,NO);
    expression->AddElement(ElementaryToken(2),NO,1,NO,NO);
    expression->AddElement(ElementaryToken(2),NO,1,NO,NO);

// std_comchar := 1-255 except: */
  i = 0;
  while ( ++i < 256 )
    if ( i != 1 && i != 2 )
    {
      expression = new BNFExpression(std_comchar);
      expression->AddElement(ElementaryToken(i),NO,1,YES,NO);
    }
    
// std_bnfchar := 33-255 except: ;
  i = 32;
  while ( ++i < 256 )
    if ( i != ';' && i != '<')
    {
      expression = new BNFExpression(std_bnfchar);
      expression->AddElement(ElementaryToken(i),NO,1,YES,NO);
    }
    
// std_anychars := std_anychar(*)
  expression = new BNFExpression(std_anychars);
    expression->AddElement(std_anychar,NO,UNDEF,YES,NO);

// std_nchars := std_nchar(*)
  expression = new BNFExpression(std_nchars);
    expression->AddElement(std_nchar,NO,UNDEF,YES,NO);

// std_nchar := std_alpha | std_digit | std_nspec
  expression = new BNFExpression(std_nchar);
    expression->AddElement(std_alpha,NO,1,YES,YES);
  expression = new BNFExpression(std_nchar);
    expression->AddElement(std_digit,NO,1,YES,YES);
  expression = new BNFExpression(std_nchar);
    expression->AddElement(std_nspec,NO,1,YES,YES);

// std_digits := std_digit(*)
  expression = new BNFExpression(std_digits);
    expression->AddElement(std_digit,NO,UNDEF,YES,NO);

// std_cchar1 := std_cchar | \' | "
  expression = new BNFExpression(std_cchar1);
    expression->AddElement(std_cchar,NO,1,YES,NO);
  expression = new BNFExpression(std_cchar1);
    expression->AddElement(ElementaryToken('\\'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('\''),NO,1,YES,NO);
  expression = new BNFExpression(std_cchar1);
    expression->AddElement(ElementaryToken('"'),NO,1,YES,NO);

// std_cchar2 := std_cchar | \" | ' 
  expression = new BNFExpression(std_cchar2);
    expression->AddElement(std_cchar,NO,1,YES,NO);
  expression = new BNFExpression(std_cchar2);
    expression->AddElement(ElementaryToken('\\'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('"'),NO,1,YES,NO);
  expression = new BNFExpression(std_cchar2);
    expression->AddElement(ElementaryToken('\''),NO,1,YES,NO);

// std_separators := std_separator(*)
  expression = new BNFExpression(std_separators);
    expression->AddElement(std_separator,NO,UNDEF,YES,NO);

// std_separator := ' ' | std_nl
  expression = new BNFExpression(std_separator);
    expression->AddElement(ElementaryToken(' '),NO,1,YES,NO);
  expression = new BNFExpression(std_separator);
    expression->AddElement(std_nl,NO,1,YES,NO);

// std_digit := 0-9
  i = 0;
  while ( ++i < 256 )
    if ( (i >= '0' && i <= '9') )
    {
      expression = new BNFExpression(std_digit);
      expression->AddElement(ElementaryToken(i),NO,1,YES,NO);
    }

// std_alpha := a-z, A-Z
  i = 0;
  while ( ++i < 256 )
    if ( (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') )
    {
      expression = new BNFExpression(std_alpha);
      expression->AddElement(ElementaryToken(i),NO,1,YES,NO);
    }

// std_cchar := 1-255 except: ', " and backslash
  expression = new BNFExpression(std_cchar);
    expression->AddElement(std_bss,NO,1,YES,NO);
  i = 0;
  while ( ++i < 256 )
//  if ( i != '\'' && i != '"' && i != '\\' && i != '\n' && i != '\r' )
    if ( i != '\'' && i != '"' && i != '\\' )
    {
      expression = new BNFExpression(std_cchar);
      expression->AddElement(ElementaryToken(i),NO,1,YES,NO);
    }
    
// std_bss := std_bs | '\\n' | '\\t' | '\\r'
  expression = new BNFExpression(std_bss);
    expression->AddElement(ElementaryToken('\\'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('n'),NO,1,YES,NO);
  expression = new BNFExpression(std_bss);
    expression->AddElement(ElementaryToken('\\'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('t'),NO,1,YES,NO);
  expression = new BNFExpression(std_bss);
    expression->AddElement(ElementaryToken('\\'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('r'),NO,1,YES,NO);
  expression = new BNFExpression(std_bss);
    expression->AddElement(std_bs,NO,1,YES,NO);

// std_bs := '\\\\'
  expression = new BNFExpression(std_bs);
    expression->AddElement(ElementaryToken('\\'),NO,1,YES,NO);
    expression->AddElement(ElementaryToken('\\'),NO,1,YES,NO);

// std_anychar := 1-255 except: 10,13
  i = 0;
  while ( ++i < 256 )
    if ( i != 10 && i != 13 )
    {
      expression = new BNFExpression(std_anychar);
      expression->AddElement(ElementaryToken(i),NO,1,YES,NO);
    }
    
// std_nspec := _ | $ 
  expression = new BNFExpression(std_nspec);
    expression->AddElement(ElementaryToken('_'),NO,1,NO,NO);
  expression = new BNFExpression(std_nspec);
    expression->AddElement(ElementaryToken('$'),NO,1,NO,NO);

// std_nl := 10 | 13 10 
  expression = new BNFExpression(std_nl);
    expression->AddElement(ElementaryToken(10),NO,1,YES,YES);
  expression = new BNFExpression(std_nl);
    expression->AddElement(ElementaryToken(13),NO,1,YES,NO);
    expression->AddElement(ElementaryToken(10),YES,1,YES,YES);

  if ( !bs_parent )
    ReorderSymbols();

}

/******************************************************************************/
/**
\brief  ~BNFStandardSymbols


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~BNFStandardSymbols"

                        BNFStandardSymbols :: ~BNFStandardSymbols ( )
{



}


