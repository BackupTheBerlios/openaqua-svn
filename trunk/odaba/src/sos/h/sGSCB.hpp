/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    GSCB

\brief    


\date     $Date: 2006/03/12 19:20:00,79 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   GSCB_HPP
#define   GSCB_HPP

class     GSCB;

class     smcb;
#include  <sscb.hpp>
#pragma pack(8)

class  GSCB :public scb
{

public     :
public     :                                                             GSCB (void *pscbptr, smcb *smcbptr );
public     :                                                             GSCB ( );
public     :                                     itp *GetEntry (char *fldnames );
public     :                                     itp *GetEntry (int16 indx );
};

#pragma pack()
#endif
