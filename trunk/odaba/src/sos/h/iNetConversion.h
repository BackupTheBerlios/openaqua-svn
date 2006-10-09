/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    NetConversion

\brief    


\date     $Date: 2006/03/12 19:20:06,53 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   NetConversion_H
#define   NetConversion_H


#if defined (__cplusplus)
  extern "C" {
#endif

SOS7ImpExp         int64 __cdecl BigToPIF (int64 big_val, logical convert );
SOS7ImpExp         int32 __cdecl LongToPIF (int32 long_val, logical convert );
SOS7ImpExp         int64 __cdecl PIFToBig (int64 big_val, logical convert );
SOS7ImpExp         int32 __cdecl PIFToLong (int32 long_val, logical convert );
SOS7ImpExp         int16 __cdecl PIFToShort (int16 short_val, logical convert );
SOS7ImpExp         int16 __cdecl ShortToPIF (int16 short_val, logical convert );

#if defined (__cplusplus)
             }
#endif
#endif
