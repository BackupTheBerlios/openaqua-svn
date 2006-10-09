/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    srt

\brief    Ordered list
          Ordered  lists are  lists of  entries that  are ordered according to a
          value in the list or according to a component key.

\date     $Date: 2006/03/12 19:20:57,09 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   srt_HPP
#define   srt_HPP

class     srt;

class     fmcb;
class     srt;
#include  <sRessourceLock.hpp>
#include  <ssts.hpp>
#pragma pack(8)

class  srt :public sts
{
protected  :         int32                                        srtmaxe ATTR_ALIGN(1);                                     //
protected  :         int32                                        srtecnt;                                                   //
protected  :         int16                                        srtelen;                                                   //
protected  :         int16                                        srtklen;                                                   //
protected  :         int16                                        srtkpos;                                                   //
protected  :         char                                         srtktyp;                                                   //
protected  :         logical                                      srtexp;                                                    //
protected  :         logical                                      srtind;                                                    //
protected  :         char                                        *srtenty;                                                   //
protected  :         RessourceLock                               *srt_lock;                                                  

public     :
                     int32                                        get_srtmaxe() { return(srtmaxe); }
                     int32                                        get_srtecnt() { return(srtecnt); }
                     int16                                        get_srtelen() { return(srtelen); }
                     int16                                        get_srtklen() { return(srtklen); }
                     int16                                        get_srtkpos() { return(srtkpos); }
                     char                                         get_srtktyp() { return(srtktyp); }
                     logical                                      get_srtexp() { return(srtexp); }
                     logical                                      get_srtind() { return(srtind); }
                     char                                        *get_srtenty() { return(srtenty); }
                     RessourceLock                               *get_srt_lock() { return(srt_lock); }
public     :         SOS7ImpExp                  int CheckError ( );
public     :                                     int Compare (const void *entry1, const void *entry2 );
public     :         SOS7ImpExp                  logical EntryFromPIF (int16 indx );
public     :         SOS7ImpExp                  logical EntryToPIF (int16 indx );
public     :         SOS7ImpExp                  char *ExtractKey (const void *entry1, char *key_area );
public     :         SOS7ImpExp                  logical FreeTable ( );
public     :         SOS7ImpExp                  logical FromPIF ( );
public     :         SOS7ImpExp                  logical Lock (logical wait=YES );
public     :         SOS7ImpExp                  logical ToPIF ( );
public     :         SOS7ImpExp                  logical Unlock ( );
public     :         SOS7ImpExp                                          srt (int32 maxe, int16 elen, int16 klen, int16 kpos, char ktype, logical expand );
public     :         SOS7ImpExp                                          srt (srt *srtptr, int16 fcnt, int16 elen );
public     :         SOS7ImpExp                                          srt (int32 ecnt, int16 elen, int16 klen, int16 kpos, char ktype, char *table_ptr, logical expand );
public     :         SOS7ImpExp                                          srt ( );
public     :         SOS7ImpExp                                          srt (char **codset );
public     :         SOS7ImpExp                  int32 srtbsr (void *skey );
protected  :         SOS7ImpExp                  logical srtchk ( );
public     :         SOS7ImpExp                  int32 srtcnt ( );
public     :         SOS7ImpExp                  void *srtfad ( );
public     :         SOS7ImpExp                  void *srtfgt ( );
public     :         SOS7ImpExp                  logical srtiad (int32 lindx, void *entry_area );
public     :         SOS7ImpExp                  logical srtidl (int32 lindx );
public     :         SOS7ImpExp                  void *srtigt (int32 lindx );
public     :         SOS7ImpExp                  logical srtini ( );
public     :         SOS7ImpExp                  void *srtiup (void *entry_area, int32 lindx );
public     :         SOS7ImpExp                  int32 srtkad (void *entry_area );
protected  :         SOS7ImpExp                  int srtkcp (void *skey, void *entry_area );
public     :         SOS7ImpExp                  int16 srtkln ( );
public     :         SOS7ImpExp                  int16 srtkps ( );
public     :         SOS7ImpExp                  char srtktp ( );
public     :         SOS7ImpExp                  int16 srtlen ( );
public     :         SOS7ImpExp                  int32 srtmax ( );
public     :         SOS7ImpExp                  void srtres ( );
public     :         SOS7ImpExp                  int32 srtsch (int32 maxe );
public     :         SOS7ImpExp                  logical srtset (int32 maxe, int16 elen, int16 klen, int16 kpos, char ktype, logical expand );
public     :         SOS7ImpExp                  void srtsetc (int32 ecnt );
public     :         SOS7ImpExp                  void srtsete (int32 tbllen );
public     :         SOS7ImpExp                  void srtsetm (int32 maxe );
public     :         SOS7ImpExp                  void srtsett (void *tblptr );
public     :         SOS7ImpExp                  void srtsind ( );
public     :         SOS7ImpExp                  logical srtsor (int16 kpos, int16 klen, char ktype );
public     :         SOS7ImpExp                  int32 srtssr (void *skey );
public     :         SOS7ImpExp                  void *srttbl ( );
public     :         SOS7ImpExp                                          ~srt ( );
};

#pragma pack()
#endif
