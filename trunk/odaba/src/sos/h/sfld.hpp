/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    fld

\brief    


\date     $Date: 2006/06/13 22:32:39,39 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   fld_HPP
#define   fld_HPP

class     fld;

#include "csosdll.h"
#define  dum                                       
class     fmcb;
class     smcb;
#include  <sdbdt.hpp>
#include  <sdbtm.hpp>
#include  <sdttm.hpp>
#include  <sfld.hpp>
#pragma pack(8)

class  fld
{
protected  :         fmcb                                        *fldfmcb;                                                   // 
protected  :         char                                        *flddata;                                                   // 
protected  :         logical                                      flddaloc;                                                  // 
protected  :         logical                                      fldfaloc;                                                  // 

public     :
                     fmcb                                        *get_fldfmcb() { return(fldfmcb); }
                     char                                        *get_flddata() { return(flddata); }
                     logical                                      get_flddaloc() { return(flddaloc); }
                     logical                                      get_fldfaloc() { return(fldfaloc); }
public     :                  SOSImpExp             logical AllocateArea ( );
public     :                  SOSImpExp             fmcb *AllocateFMCB ( );
public     :                  SOSImpExp             logical CreateStructFMCB (char *fldnames, smcb *smcbptr );
public     :                  SOSImpExp             char *GetArea ( );
public     :                  SOSImpExp             char GetChar ( );
public     :                  SOSImpExp             dbdt GetDate ( );
public     :                  SOSImpExp             dttm GetDateTime ( );
public     :                  SOSImpExp             double GetDouble ( );
public     :                  SOSImpExp             fmcb *GetFMCB ( ) const;
public     :                  SOSImpExp             fld GetField (char *fldnames );
public     :                  SOSImpExp             int16 GetInt ( );
public     :                  SOSImpExp             int32 GetLong ( );
public     :                  SOSImpExp             int32 GetNormalized ( );
public     :                  SOSImpExp             uint32 GetNormalizedU ( );
public     :                  SOSImpExp             smcb *GetSMCB ( );
public     :                  SOSImpExp             dbtm GetTime ( );
public     :                                        logical InitString (char *string, size_t len );
public     :                  SOSImpExp             void Initialize ( );
public     :                  SOSImpExp             logical IsTrue ( );
public     :                  SOSImpExp             int32 NormalizedLong ( );
public     :                  SOSImpExp             int32 *NormalizedLongPt ( );
public     :                  SOSImpExp             int16 NormalizedShort ( );
public     :                  SOSImpExp             int32 *NormalizedShortP ( );
public     :                  SOSImpExp             char *SetArea (char *datarea );
public     :                  SOSImpExp             void SetDouble (double dblval );
public     :                  SOSImpExp             fmcb *SetFMCB (fmcb *fmcbptr );
public     :                  SOSImpExp             void SetNormalized (int32 longval );
public     :                  SOSImpExp             void SetNormalizedU (uint32 luval );
public     :                  SOSImpExp             logical SetupLength (const fld &fldentyc );
public     :                  SOSImpExp                  fld (int64 int64_val );
public     :                  SOSImpExp                  fld (dbdt datefld );
public     :                  SOSImpExp                  fld ( );
public     :                  SOSImpExp                  fld (logical logval );
public     :                  SOSImpExp                  fld (smcb *smcbptr, char *fldnames, void *entry_area );
public     :                  SOSImpExp                  fld (char *string );
public     :                  SOSImpExp                  fld (char *string, size_t len );
public     :                  SOSImpExp                  fld (dbtm timefld );
public     :                  SOSImpExp                  fld (fmcb *fmcbptr );
public     :                  SOSImpExp                  fld (double dblval );
public     :                  SOSImpExp                  fld (fmcb *fmcbptr, void *entry_area );
public     :                  SOSImpExp                  fld (int32 intval );
public     :                  SOSImpExp                  fld (const fld &fldentyc );
public     :                  SOSImpExp                  fld (dttm datetimeval );
public     :                  SOSImpExp             int fldcmp (fld &fldenty );
public     :                  SOSImpExp             void fldfalos (logical opt );
public     :                  SOSImpExp             logical fldfmcbx (fmcb *fmcbptr );
public     :                                        void fldinit ( );
public     :                                        logical fldsfmcb (char *fldnames, smcb *smcbptr );
public     :                  SOSImpExp             fld &operator() (char *instptr );
public     :                  SOSImpExp             fld &operator= (int64 int64_val );
public     :                  SOSImpExp             fld &operator= (logical logval );
public     :                  SOSImpExp             fld &operator= (dbdt dateval );
public     :                  SOSImpExp             fld &operator= (const fld &fldentyc );
public     :                  SOSImpExp             fld &operator= (double dblval );
public     :                  SOSImpExp             fld &operator= (int32 intval );
public     :                  SOSImpExp             fld &operator= (char *string );
public     :                  SOSImpExp             fld &operator= (dbtm timeval );
public     :                  SOSImpExp             fld &operator= (dttm datetimeval );
public     :                                        char *xxGetString ( );
public     :                  SOSImpExp                  ~fld ( );
};

#pragma pack()
#endif
