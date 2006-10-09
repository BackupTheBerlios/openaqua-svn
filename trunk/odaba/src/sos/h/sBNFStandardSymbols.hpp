/********************************* Class Declaration ***************************/
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
          €

\date     $Date: 2006/03/12 19:19:32,07 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BNFStandardSymbols_HPP
#define   BNFStandardSymbols_HPP

class     BNFStandardSymbols;

#include  <sBNFParser.hpp>
class  BNFStandardSymbols :public BNFParser
{

public     :
public     :         SOS7ImpExp                                          BNFStandardSymbols (BNFParser *bs_parent=NULL );
public     : virtual SOS7ImpExp                                          ~BNFStandardSymbols ( );
};

#endif
