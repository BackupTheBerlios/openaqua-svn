/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mvl

\brief    


\date     $Date: 2006/03/12 19:14:33,54 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   mvl_HPP
#define   mvl_HPP

class     mvl;

#define  MVL_ECT                                   10
#define  MVL_IDCL                                  8088
#define  MVL_IDXL                                  4088
class     DBHandle;
class     DBIndex;
class     LACObject;
class     exd;
class     kcb;
class     ksrt;
class     mven;
class     srt;
#include  <cPIACC.h>
#include  <sEB_Number.hpp>
#include  <srefs.hpp>
#pragma pack(8)

class  mvl :public refs
{
public     :         srt                                         *mvlsrt ATTR_ALIGN(4);                                      
protected  :         int16                                        mvlmaxl;                                                   
protected  :         int16                                        mvlexte;                                                   
protected  :         logical                                      mvlrefi;                                                   

public     :
                     int16                                        get_mvlmaxl() { return(mvlmaxl); }
                     int16                                        get_mvlexte() { return(mvlexte); }
                     logical                                      get_mvlrefi() { return(mvlrefi); }
public     :                                     logical AutoCorrection ( );
public     :                                     logical CheckVersion6 ( );
public     :                                     logical CreateTable ( );
public     : virtual                             logical DelExt (int32 lindx0 );
public     : virtual                             logical FromPIF (exd *exdarea );
public     : virtual                             int32 GetCount ( );
public     : virtual                             logical GetTable ( );
public     :                                     logical IsMemoKey ( );
public     :                                     logical IsPD ( );
public     :                                     void Modify ( );
public     : virtual                             exd *ProvideEXD ( );
public     : virtual                             logical ProvideTable (EB_Number ebsnum );
public     :                                     logical Read (logical skip_ta=NO );
public     : virtual                             logical Refresh ( );
public     : virtual                             logical Reset ( );
public     : virtual                             logical ResetTable (mven *mvenptr );
public     : virtual                             logical Save ( );
public     :                                     void SetupTable ( );
public     : virtual                             logical ToPIF (exd *exdarea );
public     :                                                             mvl (LACObject *lobhandle, EB_Number *extref, EB_Number clnumb, char otyp, int16 extcnt, int16 maxl, DBIndex *akcbptr, logical globind );
public     :                                     logical mvlchck ( );
protected  :                                     int32 mvlchk (int32 lindx0 );
public     :                                     logical mvlcrt (int16 elen, int16 kpos, kcb *kcbptr );
protected  :                                     logical mvlexp (int64 maxent );
public     :                                     int32 mvlfec ( );
public     :                                     int32 mvlfec (EB_Number ebsnum );
public     :                                     char *mvllast (char *keyptr );
public     :                                     int32 mvlmaxg ( );
public     :                                     void mvlrmv ( );
public     :                                     int8 mvlshft (mven *mvenlow, mven *mvenhigh, char *skey );
public     :                                     logical mvlsplt (mven *mvenptr, mven *mvennew, char *skey );
public     : virtual                                                     ~mvl ( );
public     :                                     void mvlrefir ( ){

 mvlrefi = NO;

}

public     :                                     void mvlrefis ( ){

 mvlrefi = YES;

}

};

#pragma pack()
#endif
