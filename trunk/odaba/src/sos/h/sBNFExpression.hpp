/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    BNFExpression

\brief    BNF expression
          A  BNF expression defines a BNF symbol.  A BNF Symbol might be defined
          by  more than one  expression. A BNF  expression may consist of one or
          more BNF elements with a defined order.

\date     $Date: 2006/04/26 20:24:04,37 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BNFExpression_HPP
#define   BNFExpression_HPP

class     BNFExpression;

#include "csosdll.h"
#ifndef   DLL_BNFElement_HPP
#define   DLL_BNFElement_HPP
#include  <sBNFElement.hpp>
#include  <sDLL.h>
#endif
class     BNFData;
class     BNFElement;
class     BNFExpression;
class     BNFSymbol;
class  BNFExpression
{
protected  :         DLL(BNFElement)                              elements;                                                  // Elements for the BNF expression
protected  :         BNFSymbol                                   *symbol;                                                    // BNF symbol

public     :
                     DLL(BNFElement)                             &get_elements() { return(elements); }
                     BNFSymbol                                   *get_symbol() { return(symbol); }
public     :         SOSImpExp                   int32 AddElement (BNFSymbol *bsymbol, logical is_optional, int32 rep_count, logical case_opt, logical sep_opt );
public     :                                     int32 Analyze (BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt );
public     :         SOSImpExp                                           BNFExpression (BNFSymbol *bsymbol );
public     :                                     logical IsElementary ( );
public     :                                     logical IsIdentified ( );
public     :                                     int16 LocateExpressions (BNFSymbol *target_symbol, BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt );
public     :                                     int32 MatchKeyword (BNFData *bdata );
public     :                                     int16 NextExpressions (BNFSymbol *target_symbol, BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt );
public     :                                     void SetSymbol (BNFSymbol *bsymbol );
public     :                                     int32 UpdateData (BNFData *bdata );
public     :         SOSImpExp                                           ~BNFExpression ( );
};

#endif
