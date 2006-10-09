/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    bsts

\brief    STS-Status Information
          0x0100 - stsinit
          0x0200 - stsfill
          0x0400 - stsmod
          0x0800 - stserr
          0x1000 - stsdel
          0x6000 - stswpt
          0x8000 - stslck

          0x0001 - stssav
          0x0002 - stsnof
          0x0004 - stsold
          0x0008 - ststrans
          0x0010 - stsres
          0x0020 - stsuser1
          0x0040 - stsuser2
          0x0080 - stsuser3
          ressource database.

\date     $Date: 2006/03/12 19:20:26,35 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   bsts_HPP
#define   bsts_HPP

class     bsts;

#define  not_stsdel                                0xEF
#define  not_stserr                                0xF7
#define  not_stsfil                                0xFD
#define  not_stsinit                               0xFE
#define  not_stslck                                0x7F
#define  not_stsmod                                0xFB
#define  not_stsnof                                0xFD
#define  not_stsold                                0xFB
#define  not_stsres                                0xEF
#define  not_stssav                                0xFE
#define  not_ststrans                              0xF7
#define  not_stsuser1                              0xDF
#define  not_stsuser2                              0xBF
#define  not_stsuser3                              0x7F
#define  not_stswpt                                0x9F
#define  stsdel                                    0x10
#define  stserr                                    0x08
#define  stsfil                                    0x02
#define  stsinit                                   0x01
#define  stslck                                    0x80
#define  stsmod                                    0x04
#define  stsnof                                    0x02
#define  stsold                                    0x04
#define  stsres                                    0x10
#define  stssav                                    0x01
#define  ststrans                                  0x08
#define  stsuser1                                  0x20
#define  stsuser2                                  0x40
#define  stsuser3                                  0x80
#define  stswpt                                    0x60
#pragma pack(2)

class  bsts
{
public     :         uint8                                        sts1;                                                      
public     :         uint8                                        sts2;                                                      

public     :
public     :         SOS7ImpExp                                          bsts ( );
public     :         SOS7ImpExp                  void stsawpt (uint8 wpmode );
public     :         SOS7ImpExp                  logical stscdel ( );
public     :         SOS7ImpExp                  logical stscerr ( );
public     :         SOS7ImpExp                  logical stscfil ( );
public     :         SOS7ImpExp                  logical stscini ( );
public     :         SOS7ImpExp                  logical stsclck ( );
public     :         SOS7ImpExp                  logical stscmod ( );
public     :         SOS7ImpExp                  logical stscnof ( );
public     :         SOS7ImpExp                  logical stscold ( );
public     :         SOS7ImpExp                  logical stscres ( );
public     :         SOS7ImpExp                  logical stscsav ( );
public     :         SOS7ImpExp                  logical stsctrans ( );
public     :         SOS7ImpExp                  logical stscusr1 ( );
public     :         SOS7ImpExp                  logical stscusr2 ( );
public     :         SOS7ImpExp                  logical stscusr3 ( );
public     :         SOS7ImpExp                  uint8 stscwpt ( );
public     :         SOS7ImpExp                  uint8 stscwpt (uint8 wpmode );
public     :         SOS7ImpExp                  void stsrdel ( );
public     :         SOS7ImpExp                  void stsrerr ( );
public     :         SOS7ImpExp                  void stsreset ( );
public     :         SOS7ImpExp                  void stsrfil ( );
public     :         SOS7ImpExp                  void stsrini ( );
public     :         SOS7ImpExp                  void stsrlck ( );
public     :         SOS7ImpExp                  void stsrmod ( );
public     :         SOS7ImpExp                  void stsrnof ( );
public     :         SOS7ImpExp                  void stsrold ( );
public     :         SOS7ImpExp                  void stsrres ( );
public     :         SOS7ImpExp                  void stsrsav ( );
public     :         SOS7ImpExp                  void stsrtrans ( );
public     :         SOS7ImpExp                  void stsrusr ( );
public     :         SOS7ImpExp                  void stsrusr1 ( );
public     :         SOS7ImpExp                  void stsrusr2 ( );
public     :         SOS7ImpExp                  void stsrusr3 ( );
public     :         SOS7ImpExp                  void stsrwpt ( );
public     :         SOS7ImpExp                  void stsrwpt (uint8 wpmode );
public     :         SOS7ImpExp                  void stssdel ( );
public     :         SOS7ImpExp                  void stsserr ( );
public     :         SOS7ImpExp                  void stssetini ( );
public     :         SOS7ImpExp                  void stssfil ( );
public     :         SOS7ImpExp                  void stssini ( );
public     :         SOS7ImpExp                  void stsslck ( );
public     :         SOS7ImpExp                  void stssmod ( );
public     :         SOS7ImpExp                  void stssnof ( );
public     :         SOS7ImpExp                  void stssold ( );
public     :         SOS7ImpExp                  void stssres ( );
public     :         SOS7ImpExp                  void stsssav ( );
public     :         SOS7ImpExp                  void stsstrans ( );
public     :         SOS7ImpExp                  void stssusr1 ( );
public     :         SOS7ImpExp                  void stssusr2 ( );
public     :         SOS7ImpExp                  void stssusr3 ( );
public     :         SOS7ImpExp                  void stsswpt (uint8 wpmode );
};

#pragma pack()
#endif
