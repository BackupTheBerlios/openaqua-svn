/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    fmcl

\brief    


\date     $Date: 2006/03/12 19:20:44,14 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   fmcl_HPP
#define   fmcl_HPP

class     fmcl;

#ifndef   GSRT_fmcb_HPP
#define   GSRT_fmcb_HPP
#include  <sfmcb.hpp>
#include  <sGSRT.h>
#endif
class     fmcb;
class     fmcl;
#pragma pack(8)

class  fmcl :public GSRT(fmcb)
{

public     :
public     :         SOS7ImpExp                  fmcb *GetFMCB (char *fldnames, logical syn_opt );
public     :         SOS7ImpExp                  fmcb *GetFMCB (char *fldnames );
public     :         SOS7ImpExp                                          fmcl (int32 maxe, logical expand );
public     :         SOS7ImpExp                                          fmcl (fmcl *fmclptr=NULL );
public     :         SOS7ImpExp                                          fmcl (fmcb *table, int16 tesize, int32 ecnt );
public     :         SOS7ImpExp                  int fmclicmp (fmcl *srcefmcl, char *targinst, char *srceinst );
public     :         SOS7ImpExp                  logical fmclicpy (fmcl *srcefmcl, char *targinst, char *srceinst );
public     :         SOS7ImpExp                  logical fmcliini (char *instptr );
public     :         SOS7ImpExp                                          ~fmcl ( );
};

#pragma pack()
#endif
