/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    trc

\brief    


\date     $Date: 2006/03/12 19:21:00,60 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   trc_HPP
#define   trc_HPP

class     trc;

#pragma pack(8)

class  trc
{
protected  :         char                                         trconame[40];                                              //
protected  :         char                                         trcfname[40];                                              //
protected  :         trc                                        **trctrcp;                                                   //
protected  :         int32                                        trcbegs;                                                   //
protected  :         int32                                        trcreco;                                                   //
protected  :         int32                                        trcends;                                                   //
protected  :         int64                                        trcetim;                                                   //
protected  :         int64                                        trcstim;                                                   //

public     :
public     :         SOS7ImpExp                                          trc (trc **trcptr, char *objid, char *modid );
public     :         SOS7ImpExp                  void trcbeg (char *objid, char *modid );
public     :         SOS7ImpExp                  void trcend (char *objid, char *modid );
public     :         SOS7ImpExp                  void trcprn (std::ostream &output );
public     :         SOS7ImpExp                  void trcrec (char *objid, char *modid );
public     :         SOS7ImpExp                  void trcutrc ( );
};

#pragma pack()
#endif
