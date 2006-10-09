/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    acc



\date     $Date: 2006/05/09 13:53:09,10 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   acc_HPP
#define   acc_HPP

#include "csosdll.h"
#include "padcstd.h"

class     fmcb;
class     smcb;
#pragma pack(8)

class  acc
{
protected  :         logical                                      accinst;                                                   
protected  :         int16                                        acccntrd;                                                  
protected  :         int16                                        acccntwt;                                                  

public     :
                     logical                                      get_accinst() { return(accinst); }
                     int16                                        get_acccntrd() { return(acccntrd); }
                     int16                                        get_acccntwt() { return(acccntwt); }
public     : virtual          SOSImpExp             char *Access (int32 indx0, char *string, int32 maxlen );
public     : virtual          SOSImpExp             logical DirToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targ_fld, void *srce_fld, int16 replace=UNDEF, int16 copy_type=UNDEF );
public     : virtual          SOSImpExp             acc *GetAccess (int16 atyp=UNDF );
public     : virtual          SOSImpExp             smcb *GetSortKeySMCB (char *fldnames );
public     : virtual          SOSImpExp             logical RefToDir (fmcb *targfmcb, fmcb *srcefmcb, void *targ_fld, void *srce_fld, int16 replace=UNDEF, int16 copy_type=UNDEF );
public     : virtual          SOSImpExp             logical RefToRef (fmcb *targfmcb, fmcb *srcefmcb, void *targ_fld, void *srce_fld, int16 replace=UNDEF, int16 copy_type=UNDEF );
public     :                  SOSImpExp                  acc (logical insind );
public     :                  SOSImpExp             int16 acccntg ( );
public     :                  SOSImpExp             int16 accdcr (char accopt=RD );
public     :                  SOSImpExp             int16 accinc (char accopt=RD );
public     :                  SOSImpExp             logical accinstc ( );
public     :                  SOSImpExp             void accinsts (logical inststo );
public     : virtual          SOSImpExp                  ~acc ( );
public     : virtual          SOSImpExp             char *Access (char *, int32 & ){
  return(NULL);
}

};

#pragma pack()
#endif
