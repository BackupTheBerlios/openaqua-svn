/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    dfs

\brief    Data format specification


\date     $Date: 2006/06/27 17:23:33,89 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   dfs_HPP
#define   dfs_HPP

class     dfs;
#include "csosdll.h"

#pragma pack(2)

class  dfs
{
protected  :         int16                                        dfslang;                                                   // 
protected  :         int16                                        dfsfdate;                                                  // 
protected  :         int16                                        dfsftime;                                                  // 
protected  :         char                                         dfscdec;                                                   // 
protected  :         char                                         dfscthou;                                                  // 
protected  :         char                                         dfscsep;                                                   // 
protected  :         char                                         dfscpar[2];                                                // 

public     :
                     int16                                        get_dfslang() { return(dfslang); }
                     int16                                        get_dfsfdate() { return(dfsfdate); }
                     int16                                        get_dfsftime() { return(dfsftime); }
                     char                                         get_dfscdec() { return(dfscdec); }
                     char                                         get_dfscthou() { return(dfscthou); }
                     char                                         get_dfscsep() { return(dfscsep); }
                     char                                        *get_dfscpar() { return(dfscpar); }
public     : static           SOSImpExp             void __cdecl Change (int16 timefmt, int16 datefmt, char decpoint, char thopoint, char separate, char parenth );
public     : static           SOSImpExp             void __cdecl ChangeDate (int16 datefmt );
public     : static           SOSImpExp             void __cdecl ChangeDecimal (char decpoint );
public     : static           SOSImpExp             void __cdecl ChangeLanguage (int16 language=UNDEF );
public     : static           SOSImpExp             void __cdecl ChangeParenthes (char parchar );
public     : static           SOSImpExp             void __cdecl ChangeSeparator (char separate );
public     : static           SOSImpExp             void __cdecl ChangeThousands (char thopoint );
public     : static           SOSImpExp             void __cdecl ChangeTime (int16 timefmt );
public     : static           SOSImpExp             int16 __cdecl GetDateFormat ( );
public     : static           SOSImpExp             int16 __cdecl GetDateFormat (char *string );
public     : static           SOSImpExp             char __cdecl GetDecimal ( );
public     : static           SOSImpExp             int16 __cdecl GetLanguage ( );
public     : static           SOSImpExp             char *__cdecl GetOffValue ( );
public     : static           SOSImpExp             char *__cdecl GetOnValue ( );
public     : static           SOSImpExp             char *__cdecl GetParenthesis ( );
public     : static           SOSImpExp             char __cdecl GetSeparator ( );
public     : static           SOSImpExp             int16 __cdecl GetTimeFormat ( );
public     : static           SOSImpExp             int16 __cdecl GetTimeFormat (char *string );
public     :                  SOSImpExp             void Set (int16 timefmt, int16 datefmt, char decpoint, char thopoint, char separate, char parenth );
public     :                  SOSImpExp             void SetDate (int16 datefmt );
public     :                  SOSImpExp             void SetDecimal (char decpoint );
public     :                  SOSImpExp             void SetLanguage (int16 language=UNDEF );
public     :                  SOSImpExp             void SetParenthes (char parchar );
public     :                  SOSImpExp             void SetSeparator (char separate );
public     :                  SOSImpExp             void SetThousands (char thopoint );
public     :                  SOSImpExp             void SetTime (int16 timefmt );
public     :                  SOSImpExp                  dfs ( );
};

#pragma pack()
#endif
