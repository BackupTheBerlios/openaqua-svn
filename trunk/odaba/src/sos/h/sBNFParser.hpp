/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/08/27 18:17:44,67 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BNFParser_HPP
#define   BNFParser_HPP

class     BNFParser;
#include "csosdll.h"

#ifndef   DLL_BNFParser_HPP
#define   DLL_BNFParser_HPP
#include  <sBNFParser.hpp>
#include  <sDLL.h>
#endif
#ifndef   DLL_BNFSymbol_HPP
#define   DLL_BNFSymbol_HPP
#include  <sBNFSymbol.hpp>
#include  <sDLL.h>
#endif
#ifndef   GISRT_BNFSymbol_HPP
#define   GISRT_BNFSymbol_HPP
#include  <sBNFSymbol.hpp>
#include  <sGISRT.h>
#endif
class     BNFElmTokens;
class     BNFParser;
class     EntryPool;
#include  <sBNFData.hpp>
#include  <sBNFSymbol.hpp>
#include  <sRessourceLock.hpp>
class  BNFParser :public BNFSymbol
{
protected  :         DLL(BNFSymbol)                               symbols;                                                   // Tokens defined for the symbol
protected  :         BNFElmTokens                                *elementary_tokens;                                         // 
protected  :         EntryPool                                   *data_pool;                                                 // 
protected  :         BNFData                                      err_position;                                              // 
protected  :         BNFSymbol                                   *first_referenced;                                          // 
protected  :         logical                                      skip_nl;                                                   // 
protected  :         FILE                                        *trace_file;                                                // 
protected  :         char                                        *last_error;                                                // 
protected  :         char                                        *expression;                                                // 
protected  :         char                                        *init_comment;                                              // 
protected  :         DLL(BNFParser)                               sub_parser;                                                // 
protected  :         RessourceLock                                res_lock;                                                  // 

public     :
                     DLL(BNFSymbol)                              &get_symbols() { return(symbols); }
                     EntryPool                                   *get_data_pool() { return(data_pool); }
                     BNFData                                     &get_err_position() { return(err_position); }
                     BNFSymbol                                   *get_first_referenced() { return(first_referenced); }
                     logical                                      get_skip_nl() { return(skip_nl); }
                     FILE                                        *get_trace_file() { return(trace_file); }
                     char                                        *get_last_error() { return(last_error); }
                     char                                        *get_expression() { return(expression); }
                     char                                        *get_init_comment() { return(init_comment); }
                     DLL(BNFParser)                              &get_sub_parser() { return(sub_parser); }
public     :                  SOSImpExp             void AddSymbol (BNFSymbol *bsymbol );
public     :                  SOSImpExp             BNFData *Analyze (char *string, logical skip_sep );
public     :                  SOSImpExp             BNFData *Analyze (char *string, char *symbol, logical skip_sep );
public     :                  SOSImpExp             BNFData *AnalyzeFile (char *path, logical skip_sep );
public     :                  SOSImpExp             BNFData *AnalyzeFile (char *path, char *symbol, logical skip_sep );
public     :                                        BNFData *AnalyzeSymbol (BNFSymbol *bsymbol, char *string, logical skip_sep );
public     :                  SOSImpExp                  BNFParser (char *names, BNFParser *bs_parent=NULL, logical skip_new_line=YES, logical term_opt=NO, char *trace_path=NULL );
public     :                  SOSImpExp             logical Check ( );
public     :                                        BNFData *CreateChild (BNFData *bparent, BNFSymbol *bsymbol );
public     :                  SOSImpExp             BNFSymbol *ElementaryToken (uint8 ctoken );
public     :                                        logical GenerateError (BNFData *bdata );
public     :                  SOSImpExp             char *GetLastError ( );
public     :                  SOSImpExp             BNFSymbol *GetSymbol (char *symbol );
public     :                                        int16 GetSymbolCount ( );
public     :                                        void InitCTokens ( );
public     :                  SOSImpExp             logical IsValidString (char *symbol_name, char *string, int32 string_len );
public     :                  SOSImpExp             logical ListSymbols ( );
public     :                                        logical MoveElementarySymbol (BNFSymbol *bsymbol, DLL(BNFSymbol) *symbol_list );
public     :                                        logical MoveIdentifiedSymbol (BNFSymbol *bsymbol, DLL(BNFSymbol) *symbol_list );
public     :                  SOSImpExp             logical PrintError ( );
public     :                  SOSImpExp             void ReleaseExpression ( );
public     :                                        logical RemoveChild (BNFData *bchild );
public     :                  SOSImpExp             void RemoveSymbol (BNFSymbol *bsymbol );
public     :                                        logical ReorderSymbol (BNFSymbol *bsymbol, DLL(BNFSymbol) *symbol_list );
public     :                  SOSImpExp             logical ReorderSymbols ( );
public     :                                        void ResetError ( );
public     :                  SOSImpExp             void ResetLastError ( );
public     :                  SOSImpExp             void SetCC (char *string );
public     :                                        void SetError (BNFData *bdata );
public     :                  SOSImpExp             logical SetFirst ( );
public     :                                        logical SkipSeparators (BNFData *bdata );
public     : virtual          SOSImpExp                  ~BNFParser ( );
};

#endif
