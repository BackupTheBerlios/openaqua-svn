/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/03/12 19:19:28,85 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BNFDefinition_HPP
#define   BNFDefinition_HPP

class     BNFDefinition;

#include  <sBNFParser.hpp>
class  BNFDefinition :public BNFParser
{

public     :
public     :         SOS7ImpExp                                          BNFDefinition (BNFParser *bs_parent=NULL, char *trace_path=NULL );
public     :         SOS7ImpExp                                          ~BNFDefinition ( );
};

#endif
