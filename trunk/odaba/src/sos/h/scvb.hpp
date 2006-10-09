/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    cvb

\brief    


\date     $Date: 2006/03/12 19:20:28,42 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cvb_HPP
#define   cvb_HPP

class     cvb;

class     fmcb;
#include  <sdfs.hpp>
#pragma pack(8)

class  cvb
{
protected  :         fmcb                                        *cvbsfmcb;                                                  //
protected  :         fmcb                                        *cvbtfmcb;                                                  //
protected  :         char                                        *cvbsdata;                                                  //
protected  :         char                                        *cvbtdata;                                                  //

public     :
public     :         SOS7ImpExp                                          cvb (fmcb *srcefmcb, fmcb *targfmcb, char *srcearea, char *targarea );
public     :                                     logical cvbblbl ( );
public     :                                     logical cvbcccc ( );
public     :                                     logical cvbccch ( );
public     :                                     logical cvbccsr ( );
public     :                                     logical cvbcdcd ( );
public     :                                     logical cvbcdch ( );
public     :                                     logical cvbcdfl ( );
public     :                                     logical cvbcdin ( );
public     :                                     logical cvbcdlo ( );
public     :                                     logical cvbcdsr ( );
public     :                                     logical cvbchcc ( );
public     :                                     logical cvbchcd ( );
public     :                                     logical cvbchch ( );
public     :                                     logical cvbchdm ( );
public     :                                     logical cvbchdt ( );
public     :                                     logical cvbchfl ( );
public     :                                     logical cvbchin ( );
public     :                                     logical cvbchlo ( );
public     :                                     logical cvbchmm ( );
public     :                                     logical cvbchsc ( );
public     :                                     logical cvbchsr ( );
public     :                                     logical cvbchst ( );
public     :                                     logical cvbchtm ( );
public     :                                     logical cvbchui ( );
public     :         SOS7ImpExp                  logical cvbconv (int16 replace=UNDEF, logical chkonly=NO, int16 copy_type=UNDEF );
public     :                                     logical cvbdmch ( );
public     :                                     logical cvbdmdm ( );
public     :                                     logical cvbdmdt ( );
public     :                                     logical cvbdmlo ( );
public     :                                     logical cvbdmsr ( );
public     :                                     logical cvbdmst ( );
public     :                                     logical cvbdmtm ( );
public     :                                     logical cvbdtch ( );
public     :                                     logical cvbdtdm ( );
public     :                                     logical cvbdtdt ( );
public     :                                     logical cvbdtin ( );
public     :                                     logical cvbdtlo ( );
public     :                                     logical cvbdtsr ( );
public     :                                     logical cvbflcd ( );
public     :                                     logical cvbflch ( );
public     :                                     logical cvbflfl ( );
public     :                                     logical cvbflin ( );
public     :                                     logical cvbfllo ( );
public     :                                     int64 cvbftoi (double dblval );
public     :                                     logical cvbgugu ( );
public     :                                     logical cvbgusr ( );
public     :                                     logical cvbincd ( );
public     :                                     logical cvbinch ( );
public     :                                     logical cvbindt ( );
public     :                                     logical cvbinfl ( );
public     :                                     logical cvbinin ( );
public     :                                     logical cvbinlo ( );
public     :                                     logical cvbinsr ( );
public     :                                     logical cvbintm ( );
public     :                                     logical cvbinui ( );
public     :                                     logical cvblocd ( );
public     :                                     logical cvbloch ( );
public     :                                     logical cvblofl ( );
public     :                                     logical cvbloin ( );
public     :                                     logical cvblolo ( );
public     :                                     logical cvblosr ( );
public     :                                     logical cvbmmch ( );
public     :                                     logical cvbmmlo ( );
public     :                                     logical cvbmmmm ( );
public     :                                     logical cvbmmsr ( );
public     :                                     logical cvbscch ( );
public     :                                     logical cvbscsr ( );
public     :                                     logical cvbsrcc ( );
public     :                                     logical cvbsrcd ( );
public     :                                     logical cvbsrch ( );
public     :                                     logical cvbsrdm ( );
public     :                                     logical cvbsrdt ( );
public     :                                     logical cvbsrgu ( );
public     :                                     logical cvbsrin ( );
public     :                                     logical cvbsrlo ( );
public     :                                     logical cvbsrmm ( );
public     :                                     logical cvbsrsc ( );
public     :                                     logical cvbsrsr ( );
public     :                                     logical cvbsrst ( );
public     :                                     logical cvbsrtm ( );
public     :                                     logical cvbsrui ( );
public     :                                     logical cvbstch ( );
public     :                                     logical cvbstdm ( );
public     :                                     logical cvbstsr ( );
public     :                                     logical cvbstst (int16 replace=UNDEF, int16 copy_type=UNDEF );
public     :                                     logical cvbtmch ( );
public     :                                     logical cvbtmdm ( );
public     :                                     logical cvbtmin ( );
public     :                                     logical cvbtmlo ( );
public     :                                     logical cvbtmsr ( );
public     :                                     logical cvbtmtm ( );
public     :                                     logical cvbuich ( );
public     :                                     logical cvbuiin ( );
public     :                                     logical cvbuisr ( );
public     :                                     logical cvbuiui ( );
public     :                                     logical cvbvivi ( );
public     :                                     int64 cvbxpru (int64 val64 );
public     :                                     logical cvbxxyy ( );
};

#pragma pack()
#endif
