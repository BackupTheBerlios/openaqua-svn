/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    cftd



\date     $Date: 2006/04/27 19:06:07,56 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cftd_HPP
#define   cftd_HPP

class     cftd;

#include "csosdll.h"
#define  CFTD                                      sizeof(cftd)
#define  CFTD_KLN                                  40
#define  CFTD_KPS                                  sizeof(cfte)+1
#define  CFTD_KTP                                  'C'
#include  <scfte.hpp>
#include  <sflnk.hpp>
#pragma pack(8)

class  cftd :public cfte
{
protected  :         char                                         cftdfnam[40];                                              

public     :
                     char                                        *get_cftdfnam() { return(cftdfnam); }
public     :                  SOSImpExp                  cftd (char *fnames, char *names, flnk flnkptr );
public     :                  SOSImpExp                  cftd ( );
};

#pragma pack()
#endif
