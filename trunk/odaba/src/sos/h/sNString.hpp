/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    NString

\brief    String class
          NString  is a string class, which provides a number of specific string
          features.

\date     $Date: 2006/08/28 21:13:21,21 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   NString_HPP
#define   NString_HPP

class     NString;
#include "csosdll.h"

class     svel;
#include  <sNBase.hpp>
#include  <sNString.hpp>
#include  <sdbdt.hpp>
#include  <sdbtm.hpp>
#pragma pack(8)

class  NString :public NBase
{

public     :
public     :                  SOSImpExp             logical ASCIIToUTF ( );
public     :                  SOSImpExp             logical Append (dbdt dateval );
public     :                  SOSImpExp             logical Append (char *string );
public     :                  SOSImpExp             logical Append (char *string, size_t len );
public     :                  SOSImpExp             logical Append (char char_val );
public     :                  SOSImpExp             logical Append (char char_val, int16 count );
public     :                  SOSImpExp             logical Append (int32 intval );
public     :                  SOSImpExp             logical Append (NString &n_string );
public     :                  SOSImpExp             logical Append (int64 val64 );
public     :                  SOSImpExp             logical Append (dbtm timeval );
public     :                  SOSImpExp             char *Copy (char *string, int int_len );
public     :                  SOSImpExp             char *Find (char *string, logical case_opt_w=YES );
public     :                  SOSImpExp             NString &FromBase64 ( );
public     :                  SOSImpExp             NString GetKeyValue (char *parm_key );
public     :                  SOSImpExp             int GetLength ( );
public     :                  SOSImpExp             logical Initialize (char char_val, size_t len );
public     :                  SOSImpExp             logical Insert (uint16 pos, char *string );
public     :                  SOSImpExp             logical IsEmpty ( );
public     :                                        logical IsHTML ( );
public     :                  SOSImpExp                  NString ( );
public     :                  SOSImpExp                  NString (char *string );
public     :                  SOSImpExp                  NString (char *string, size_t len );
public     :                  SOSImpExp                  NString (int32 intval );
public     :                  SOSImpExp                  NString (const NString &n_string_const );
public     :                  SOSImpExp             logical Normalize ( );
public     :                  SOSImpExp             NString RenderHTML ( );
public     :                  SOSImpExp             int32 ReplaceCharacter (char ichar, char ochar );
public     :                  SOSImpExp             logical ReplaceControlSequences ( );
public     :                  SOSImpExp             logical ReplaceFirstSymbol (char *symbol, char *value );
public     :                  SOSImpExp             logical ReplaceNLbyBR (int32 res_val=0 );
public     :                  SOSImpExp             logical ReplaceSymbol (char *symbol, char *value, uint16 index );
public     :                  SOSImpExp             logical ReplaceSysVariables (svel *svelptr, int32 res_val=0 );
public     :                  SOSImpExp             logical ReplaceText (char *symbol, char *value );
public     :                  SOSImpExp             char *SetString (char *string, size_t len );
public     :                  SOSImpExp             NString &ToBase64 ( );
public     :                  SOSImpExp             logical UTFToASCII ( );
public     :                  SOSImpExp             logical operator+= (dbdt dateval );
public     :                  SOSImpExp             logical operator+= (char *string );
public     :                  SOSImpExp             logical operator+= (char char_val );
public     :                  SOSImpExp             logical operator+= (int32 intval );
public     :                  SOSImpExp             logical operator+= (NString &n_string );
public     :                  SOSImpExp             logical operator+= (int64 val64 );
public     :                  SOSImpExp             logical operator+= (dbtm timeval );
public     :                  SOSImpExp             NString &operator<< (char *string );
public     :                  SOSImpExp             NString &operator<< (char char_val );
public     :                  SOSImpExp             NString &operator<< (int32 intval );
public     :                  SOSImpExp             NString &operator<< (NString &n_string );
public     :                  SOSImpExp             NString &operator<< (int64 val64 );
public     :                  SOSImpExp             NString &operator= (char *string );
public     :                  SOSImpExp             NString &operator= (char char_val );
public     :                  SOSImpExp             NString &operator= (int32 intval );
public     :                  SOSImpExp             NString &operator= (NString &n_string );
public     :                  SOSImpExp             NString &operator= (int64 val64 );
public     :                  SOSImpExp                  ~NString ( );
};

#pragma pack()
#endif
