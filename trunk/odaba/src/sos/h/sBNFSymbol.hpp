/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    BNFSymbol

\brief    BNF symbol
          A  BNF symbol is  a variable in  a BNF specification, which is defined
          by  one  or  more  BNF  expressions.  Symbols  do  have a neme and may
          consist  of one or more expressions.  Terminal symbols are tokens with
          a  fixed value, which  is stored in  the name. Terminal symbols do not
          habe expressions.

\date     $Date: 2006/08/27 18:18:19,25 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BNFSymbol_HPP
#define   BNFSymbol_HPP

#include "csosdll.h"
class     BNFSymbol;

#define  EXP_VECT_SIZE                             1024
#include  <sDLL.h>
class     BNFExpression;
#include  <sDLL.h>
class     BNFSymbol;
class     BNFData;
class     BNFParser;
class     BNFSymbol;
#include  <sBNFExpression.hpp>
class  BNFSymbol
{
protected  :         char                                         name[65];                                                  // Name for symbol
protected  :         logical                                      terminate;                                                 // Expressions defining the symbol
protected  :         logical                                      is_keyword;                                                // Expressions defining the symbol
protected  :         int16                                        name_len;                                                  // BNF expressions referring to the symbol
protected  :         DLL(BNFExpression)                          *expressions;                                               // BNF expressions referring to the symbol as first element
protected  :         DLL(BNFSymbol)                              *used_in;                                                   // 
protected  :         DLL(BNFExpression)                          *starting_symbol_in;                                        // 
protected  :         BNFParser                                   *top_symbol;                                                // 
protected  :         BNFSymbol                                   *osymbol;                                                   // 
protected  :         int32                                        priority;                                                  // 

public     :
                     char                                        *get_name() { return(name); }
                     logical                                      get_terminate() { return(terminate); }
                     logical                                      get_is_keyword() { return(is_keyword); }
                     int16                                        get_name_len() { return(name_len); }
                     DLL(BNFExpression)                          *get_expressions() { return(expressions); }
                     DLL(BNFSymbol)                              *get_used_in() { return(used_in); }
                     DLL(BNFExpression)                          *get_starting_symbol_in() { return(starting_symbol_in); }
                     BNFParser                                   *get_top_symbol() { return(top_symbol); }
                     BNFSymbol                                   *get_osymbol() { return(osymbol); }
                     int32                                        get_priority() { return(priority); }
public     :                                        void AddExpression (BNFExpression *bexpression );
public     :                                        int32 Analyze (BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt );
public     :                                        int32 Analyze (BNFData *bdata, logical case_opt );
public     :                                        int32 AnalyzeExpression (BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt );
public     :                  SOSImpExp                  BNFSymbol (BNFParser *bparser, char *names, logical term_opt=NO );
public     :                  SOSImpExp                  BNFSymbol ( );
public     :                                        BNFSymbol *CreateAlias (char *names );
public     :                                        BNFSymbol *ElementaryToken (uint8 ctoken, logical case_opt );
public     :                                        int16 GetExpCount (BNFExpression **bexpressions );
public     :                                        logical HasExpressions ( );
public     :                  SOSImpExp             void Initialize (BNFParser *bstring, uint8 ctoken );
public     :                                        logical IsKeyword ( );
public     :                                        int16 LocateExpressions (BNFSymbol *target_symbol, BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt, logical chk_opt=NO );
public     :                                        int16 NextExpressions (BNFSymbol *target_symbol, BNFExpression **bexpressions, BNFData *bdata, int index0, logical case_opt );
public     :                                        logical Optimize ( );
public     :                  SOSImpExp             logical Output (char *fstring, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL, char *parm6=NULL );
public     :                                        void RegisterFirstSymbol (BNFExpression *bexpression );
public     :                                        void RegisterUpper (BNFSymbol *bsymbol );
public     :                  SOSImpExp             void SetKeyword ( );
public     :                                        void SetPriority (int32 indx0 );
public     :                                        void SetSymbol (BNFSymbol *bsymbol );
public     :                  SOSImpExp             void SetTerminal ( );
public     :                                        void SetupStartingSymbols ( );
public     :                                        BNFSymbol *TerminalSymbol (BNFExpression **bexpressions, BNFData *bdata, logical case_opt );
public     :                  SOSImpExp                  ~BNFSymbol ( );
};

#endif
