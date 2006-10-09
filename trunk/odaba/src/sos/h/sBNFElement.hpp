/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    BNFElement

\brief    BNF element
          A  BNF element  describes an  element in  a BNF expression. An element
          might  be  a  symbol  or  a  token.  Symbols  must  be  defined as BNF
          expressions,  again. Symbols  might be  optional or mandatory. Symbols
          can  be  defined  by  means  of  a repitition factor (0: any number of
          repititions).

\date     $Date: 2006/04/26 20:25:01,60 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BNFElement_HPP
#define   BNFElement_HPP

class     BNFElement;

#include  <sDLL.h>
class     BNFElement;
class     BNFData;
class     BNFExpression;
class     BNFSymbol;
class  BNFElement
{
protected  :         BNFSymbol                                   *symbol;                                                    // BNF Symbol
protected  :         logical                                      optional;                                                  // Optional value
protected  :         logical                                      separated;                                                 
protected  :         logical                                      case_sensitive;                                            // Case sensitive
protected  :         int32                                        repititions;                                               // Repititions of symbol
protected  :         BNFExpression                               *expression;                                                // BNF expression

public     :
                     BNFSymbol                                   *get_symbol() { return(symbol); }
                     logical                                      get_optional() { return(optional); }
                     logical                                      get_separated() { return(separated); }
                     logical                                      get_case_sensitive() { return(case_sensitive); }
                     int32                                        get_repititions() { return(repititions); }
                     BNFExpression                               *get_expression() { return(expression); }
public     :                                     int32 Analyze (BNFData *bdata, DLL(BNFElement) *belements, logical case_opt );
public     :                                     int32 AnalyzeExpression (BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt );
public     :                                     int32 AnalyzeRepetitions (BNFData *bdata, logical case_opt );
public     :                                                             BNFElement (BNFExpression *bexpression, BNFSymbol *bsymbol, logical is_optional, int32 rep_count, logical case_opt, logical sep_opt );
public     :                                     BNFSymbol *GetSymbol ( );
public     :                                                             ~BNFElement ( );
};

#endif
