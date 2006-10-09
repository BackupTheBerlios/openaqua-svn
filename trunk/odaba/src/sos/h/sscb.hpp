/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    scb

\brief    


\date     $Date: 2006/03/12 19:20:53,43 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   scb_HPP
#define   scb_HPP

class     scb;

#include  <sGSRT.h>
class     fcb;
class     fcb;
class     fmcb;
class     smcb;
class     srt;
#pragma pack(8)

class  scb
{
public     :         smcb                                        *scbsmcb;                                                   //
public     :         GSRT(fcb)                                   *scbfcb;                                                    //

public     :
public     :         SOS7ImpExp                  fmcb *GetFMCB (int16 indx );
public     :         SOS7ImpExp                  char *GetName ( );
public     :         SOS7ImpExp                                          scb ( );
public     :         SOS7ImpExp                                          scb (smcb *smcbptr, int16 elen );
public     :                                     fcb *scbeg (char *fldnames );
public     :                                     void scbini (smcb *smcbptr, srt *srtptr );
public     :                                     void scbini (smcb *smcbptr, int16 elen );
public     :         SOS7ImpExp                                          ~scb ( );
};

#pragma pack()
#endif
