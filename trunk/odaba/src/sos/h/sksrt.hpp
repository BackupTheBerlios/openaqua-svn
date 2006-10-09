/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    ksrt

\brief    


\date     $Date: 2006/03/12 19:20:52,31 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ksrt_HPP
#define   ksrt_HPP

class     ksrt;

class     kcb;
class     ksrt;
#include  <ssrt.hpp>
#pragma pack(8)

class  ksrt :public srt
{
protected  :         kcb                                         *ksrtkcb ATTR_ALIGN(4);                                     //

public     :
                     kcb                                         *get_ksrtkcb() { return(ksrtkcb); }
public     :         SOS7ImpExp                  int Compare (const void *entry1, const void *entry2 );
public     :         SOS7ImpExp                  char *ExtractKey (const void *entry1, char *key_area );
public     :         SOS7ImpExp                  char *SetKey (const void *entry1, char *key_area );
public     :         SOS7ImpExp                                          ksrt (kcb *kcbptr, int32 maxe, int16 elen, int16 klen, int16 kpos, char ktype, logical expand );
public     :         SOS7ImpExp                                          ksrt (ksrt *ksrtptr, int32 ecnt, int16 elen );
public     :         SOS7ImpExp                                          ksrt (kcb *kcbptr, int32 ecnt, int16 elen, int16 klen, int16 kpos, char ktype, char *table_ptr, logical expand );
public     :         SOS7ImpExp                                          ksrt ( );
protected  :         SOS7ImpExp                  logical ksrtchk ( );
public     :         SOS7ImpExp                  kcb *ksrtkcbg ( );
public     :         SOS7ImpExp                                          ~ksrt ( );
};

#pragma pack()
#endif
