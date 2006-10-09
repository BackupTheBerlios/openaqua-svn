/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    BNFData

\brief    BNF data element
          A  BNF data  element contains  the data  for a  given symbol in an BNF
          expression.  BNF  data  elements  form  a  hierarchie down to symbols,
          which have been defined as relevant symbols.

\date     $Date: 2006/08/27 18:11:58,31 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BNFData_HPP
#define   BNFData_HPP

class     BNFData;

#include "csosdll.h"
#include  <sDLO.h>
class     BNFData;
class     BNFExpression;
class     BNFParser;
class     BNFSymbol;
#include  <sBNFData.hpp>
#include  <sNString.hpp>
class  BNFData
{
protected  :         BNFData                                     *parent;                                                    // BNF Symbol
protected  :         BNFSymbol                                   *symbol;                                                    // String value
protected  :         char                                        *value;                                                     // Length for value
protected  :         int32                                        value_len;                                                 // Sub-data elements
protected  :         DLO(BNFData)                                *elements;                                                  // 
protected  :         char                                        *current_pos;                                               // 
protected  :         int8                                         level;                                                     // 
protected  :         logical                                      separated;                                                 // 
protected  :         logical                                      pool_entry;                                                // 
protected  :         NString                                      nstring;                                                   // 

public     :
                     BNFData                                     *get_parent() { return(parent); }
                     BNFSymbol                                   *get_symbol() { return(symbol); }
                     char                                        *get_value() { return(value); }
                     int32                                        get_value_len() { return(value_len); }
                     DLO(BNFData)                                *get_elements() { return(elements); }
                     char                                        *get_current_pos() { return(current_pos); }
                     int8                                         get_level() { return(level); }
                     logical                                      get_separated() { return(separated); }
                     logical                                      get_pool_entry() { return(pool_entry); }
                     NString                                     &get_nstring() { return(nstring); }
public     :                                        void AddChild (BNFData *bdata );
public     :                  SOSImpExp                  BNFData (BNFSymbol *bsymbol, char *string, int32 string_len );
public     :                  SOSImpExp                  BNFData (BNFData *bparent );
public     :                  SOSImpExp                  BNFData (const BNFData &bdata_ref );
public     :                                        logical CopyParent (BNFData *bdata );
public     :                                        logical CreateDefinition (BNFParser *bparser );
public     :                                        logical CreateDefinitions (BNFParser *bparser );
public     :                                        logical CreateElement (BNFParser *bparser, BNFExpression *bexpression, logical optional );
public     :                                        logical CreateExpression (BNFParser *bparser, char *names );
public     :                                        logical CreateKeyExpression (BNFParser *bparser, char *names );
public     :                                        logical CreateKeyword (BNFParser *bparser );
public     :                                        logical CreateLocalSymbol (BNFParser *bparser, BNFExpression *bexpression, logical optional, int32 repcount, char *names );
public     :                                        logical CreateNameElement (BNFParser *bparser, BNFExpression *bexpression, logical optional, int32 repcount, char *names );
public     :                  SOSImpExp             BNFParser *CreateParser (BNFParser *bs_parent=NULL, logical list_symbols=NO, char *trace_path=NULL );
public     :                                        logical CreateReference (BNFParser *bparser );
public     :                                        logical CreateReferences (BNFParser *bparser );
public     :                                        logical CreateRule (BNFParser *bparser, char *names );
public     :                                        logical CreateStringElement (BNFParser *bparser, BNFExpression *bexpression, logical optional );
public     :                                        logical CreateSymbol (BNFParser *bparser );
public     :                                        logical CreateSymbol (BNFParser *bparser, char *names );
public     :                                        logical CreateSymbols (BNFParser *bparser );
public     :                                        uint8 CurrentToken ( );
public     :                                        void Deinitialize ( );
public     :                                        char *End ( );
public     :                                        logical GenerateDefinition (char *string );
public     :                                        logical GenerateDefinitions (char *string );
public     :                                        logical GenerateElement (char *string, logical optional );
public     :                                        logical GenerateExpression (char *string, char *names );
public     :                                        logical GenerateKeyExpression (char *string, char *names );
public     :                                        logical GenerateKeyword (char *string );
public     :                                        logical GenerateLocalSymbol (char *string, logical optional, char *repetitions, char *names );
public     :                                        logical GenerateNameElement (char *string, logical optional, char *repetitions, char *names );
public     :                                        logical GenerateReference (char *string );
public     :                                        logical GenerateReferences (char *string );
public     :                                        logical GenerateRule (char *string, char *names );
public     :                  SOSImpExp             logical GenerateSource (char *cpath );
public     :                                        logical GenerateStringElement (char *string, logical optional );
public     :                                        logical GenerateSymbol (char *string, char *names );
public     :                                        logical GenerateSymbol (char *string, char *names, char *snames );
public     :                                        logical GenerateSymbols (char *string, char *names );
public     :                  SOSImpExp             char *GetConstantString ( );
public     :                  SOSImpExp             char *GetCurrentLine ( );
public     :                  SOSImpExp             BNFData *GetElement (int index0 );
public     :                  SOSImpExp             BNFData *GetElement (char *symbol );
public     :                  SOSImpExp             int16 GetElementCount ( );
public     :                  SOSImpExp             BNFData *GetLastElement ( );
public     :                                        char *GetLocalSymbolName (char *names );
public     :                  SOSImpExp             char *GetParameter (char *parm_name, char *default_value );
public     :                  SOSImpExp             char *GetStringConstant ( );
public     :                  SOSImpExp             char *GetStringValue (char *prefix=NULL, char *suffix=NULL );
public     :                  SOSImpExp             BNFData *GetSymbol (char *symbol );
public     :                  SOSImpExp             int8 GetSymbolCode (char *symbol1, char *symbol2=NULL, char *symbol3=NULL, char *symbol4=NULL, char *symbol5=NULL, char *symbol6=NULL, char *symbol7=NULL, char *symbol8=NULL, char *symbol9=NULL, char *symbol10=NULL, char *symbol11=NULL, char *symbol12=NULL, char *symbol13=NULL, char *symbol14=NULL, char *symbol15=NULL );
public     :                  SOSImpExp             void GetTextPosition (BNFData *high_bdata, int32 &row_ref, int32 &col_ref, logical use_curpos );
public     :                  SOSImpExp             BNFData *GetTop ( );
public     :                  SOSImpExp             BNFData *GetTopElement (char *symbol );
public     :                  SOSImpExp             char *GetValue (char *string, int32 maxlen );
public     :                  SOSImpExp             int32 GetValueLength ( );
public     :                  SOSImpExp             logical HasData ( );
public     :                                        logical HasPreceedingChar ( );
public     :                                        logical HasTerminator ( );
public     :                                        BNFData *InitChild (BNFData *bparent, BNFSymbol *bsymbol );
public     :                                        void Initialize ( );
public     :                  SOSImpExp             int32 IntValue ( );
public     :                  SOSImpExp             logical IsA (char *symbol );
public     :                  SOSImpExp             logical IsSymbol (char *symbol );
public     :                                        logical IsTerminalSymbol ( );
public     :                  SOSImpExp             logical IsValue (char *string );
public     :                  SOSImpExp             char *Name ( );
public     :                  SOSImpExp             logical Output (char *fstring, char *parm1=NULL, char *parm2=NULL, char *parm3=NULL, char *parm4=NULL, char *parm5=NULL, char *parm6=NULL );
public     :                  SOSImpExp             BNFData *Parent ( );
public     :                  SOSImpExp             char *Position ( );
public     :                  SOSImpExp             logical Print (logical recursive=YES );
public     :                  SOSImpExp             logical Print (char *path, logical recursive=YES );
public     :                  SOSImpExp             logical Print (FILE *fileptr, logical recursive=YES, logical erropt=NO );
public     :                                        logical PrintError ( );
public     :                  SOSImpExp             void Release ( );
public     :                                        BNFData *RemoveChild (BNFData *bdata, logical del_opt );
public     :                                        void RemoveChildren (BNFParser *bstring );
public     :                                        logical RemoveLastChild (logical skip_opt );
public     :                                        logical RemoveLastChildren (BNFData *bdata, logical skip_opt );
public     :                                        logical RemoveParent ( );
public     :                                        void Reset (BNFParser *bstring );
public     :                                        void SetLength (int32 string_len );
public     :                                        void SkipSpaces ( );
public     :                                        char *StartPosition ( );
public     :                  SOSImpExp             char *StringValue ( );
public     :                                        BNFData *TopParent ( );
public     :                                        void UpdatePosition ( );
public     :                                        void UpdatePosition (BNFSymbol *bsymbol );
public     :                                        void UpdatePosition (char *cpos );
public     :                                        void UpdatePosition (logical skip_opt );
public     :                                        BNFData &operator= (BNFData *bdata );
public     :                  SOSImpExp                  ~BNFData ( );
};

#endif
