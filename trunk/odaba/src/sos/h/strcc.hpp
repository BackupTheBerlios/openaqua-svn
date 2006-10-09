/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    trcc

\brief    


\date     $Date: 2006/03/12 19:21:00,95 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   trcc_HPP
#define   trcc_HPP

class     trcc;

class     srt;
class     trc;
#pragma pack(8)

class  trcc
{
protected  :         void                                        *trccpscb;                                                  //
protected  :         srt                                         *trcctrc;                                                   //

public     :
public     :         SOS7ImpExp                                          trcc ( );
public     :         SOS7ImpExp                  trc *trccloc (trc **trcptr, char *objid, char *modid );
public     :         SOS7ImpExp                  void trccprnt ( );
public     :         SOS7ImpExp                                          ~trcc ( );
};

#pragma pack()
#endif
