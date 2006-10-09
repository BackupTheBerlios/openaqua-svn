/********************************* Class Source Code ***************************/
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

\date     $Date: 2006/03/12 19:22:08,17 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "bsts"

#include  <pdefault.h>
#include  <sbsts.hpp>


/******************************************************************************/
/**
\brief  bsts


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bsts"

                        bsts :: bsts ( )
{

  memset(this,0,sizeof(sts));


}

/******************************************************************************/
/**
\brief  stsawpt


\param  wpmode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsawpt"

void bsts :: stsawpt (uint8 wpmode )
{

  sts1 |= (wpmode << 5);

}

/******************************************************************************/
/**
\brief  stscdel

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscdel"

logical bsts :: stscdel ( )
{

  return( sts1 & stsdel );
//return((logical)stsdel);

}

/******************************************************************************/
/**
\brief  stscerr

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscerr"

logical bsts :: stscerr ( )
{

  return( sts1 & stserr );


}

/******************************************************************************/
/**
\brief  stscfil

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscfil"

logical bsts :: stscfil ( )
{

  return(sts1 & stsfil);

}

/******************************************************************************/
/**
\brief  stscini

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscini"

logical bsts :: stscini ( )
{

  return(sts1 & stsinit);

}

/******************************************************************************/
/**
\brief  stsclck

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsclck"

logical bsts :: stsclck ( )
{

  return(sts1 & stslck);

}

/******************************************************************************/
/**
\brief  stscmod

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscmod"

logical bsts :: stscmod ( )
{

  return(sts1 & stsmod);

}

/******************************************************************************/
/**
\brief  stscnof

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscnof"

logical bsts :: stscnof ( )
{

  return(sts2 & stsnof);

}

/******************************************************************************/
/**
\brief  stscold

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscold"

logical bsts :: stscold ( )
{

  return(sts2 & stsold);

}

/******************************************************************************/
/**
\brief  stscres

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscres"

logical bsts :: stscres ( )
{

  return(sts2 & stsres);

}

/******************************************************************************/
/**
\brief  stscsav

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscsav"

logical bsts :: stscsav ( )
{

  return(sts2 & stssav);

}

/******************************************************************************/
/**
\brief  stsctrans

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsctrans"

logical bsts :: stsctrans ( )
{

  return(sts2 & ststrans);

}

/******************************************************************************/
/**
\brief  stscusr1

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscusr1"

logical bsts :: stscusr1 ( )
{

  return(sts2 & stsuser1);

}

/******************************************************************************/
/**
\brief  stscusr2

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscusr2"

logical bsts :: stscusr2 ( )
{

  return(sts2 & stsuser2);

}

/******************************************************************************/
/**
\brief  stscusr3

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscusr3"

logical bsts :: stscusr3 ( )
{

  return(sts2 & stsuser3);

}

/******************************************************************************/
/**
\brief  stscwpt

\return cond - Return value
-------------------------------------------------------------------------------
\brief STSCWPT


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscwpt"

uint8 bsts :: stscwpt ( )
{

  return( (sts1 & stswpt) >> 5 );

}

/******************************************************************************/
/**
\brief i1


\param  wpmode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stscwpt"

uint8 bsts :: stscwpt (uint8 wpmode )
{

  return( sts1 & (wpmode << 5) );

}

/******************************************************************************/
/**
\brief  stsrdel


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrdel"

void bsts :: stsrdel ( )
{

  sts1 &= not_stsdel;

}

/******************************************************************************/
/**
\brief  stsrerr


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrerr"

void bsts :: stsrerr ( )
{

  sts1 &= not_stserr;

}

/******************************************************************************/
/**
\brief  stsreset


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsreset"

void bsts :: stsreset ( )
{

  stsrini();
  stsrsav();
  stsrmod();
  stsrfil();
  stsrerr();


}

/******************************************************************************/
/**
\brief  stsrfil


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrfil"

void bsts :: stsrfil ( )
{

  sts1 &= not_stsfil;

}

/******************************************************************************/
/**
\brief  stsrini


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrini"

void bsts :: stsrini ( )
{

  sts1 &= not_stsinit;

}

/******************************************************************************/
/**
\brief  stsrlck


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrlck"

void bsts :: stsrlck ( )
{

  sts1 &= not_stslck;

}

/******************************************************************************/
/**
\brief  stsrmod


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrmod"

void bsts :: stsrmod ( )
{

  sts1 &= not_stsmod;

}

/******************************************************************************/
/**
\brief  stsrnof


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrnof"

void bsts :: stsrnof ( )
{

  sts2 &= not_stsnof;

}

/******************************************************************************/
/**
\brief  stsrold


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrold"

void bsts :: stsrold ( )
{

  sts2 &= not_stsold;

}

/******************************************************************************/
/**
\brief  stsrres


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrres"

void bsts :: stsrres ( )
{

  sts2 &= not_stsres;

}

/******************************************************************************/
/**
\brief  stsrsav


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrsav"

void bsts :: stsrsav ( )
{

  sts2 &= not_stssav;

}

/******************************************************************************/
/**
\brief  stsrtrans


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrtrans"

void bsts :: stsrtrans ( )
{

  sts2 &= not_ststrans;

}

/******************************************************************************/
/**
\brief  stsrusr


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrusr"

void bsts :: stsrusr ( )
{

  stsrusr3();
  stsrusr2();
  stsrusr1();


}

/******************************************************************************/
/**
\brief  stsrusr1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrusr1"

void bsts :: stsrusr1 ( )
{

  sts2 &= not_stsuser1;

}

/******************************************************************************/
/**
\brief  stsrusr2


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrusr2"

void bsts :: stsrusr2 ( )
{

  sts2 &= not_stsuser2;

}

/******************************************************************************/
/**
\brief  stsrusr3


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrusr3"

void bsts :: stsrusr3 ( )
{

  sts2 &= not_stsuser3;

}

/******************************************************************************/
/**
\brief  stsrwpt

-------------------------------------------------------------------------------
\brief STSRWPT


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrwpt"

void bsts :: stsrwpt ( )
{

  sts1 &= not_stswpt;

}

/******************************************************************************/
/**
\brief i1


\param  wpmode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsrwpt"

void bsts :: stsrwpt (uint8 wpmode )
{

  sts1 &= ~(wpmode << 5);

}

/******************************************************************************/
/**
\brief  stssdel


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stssdel"

void bsts :: stssdel ( )
{

  sts1 |= stsdel;

}

/******************************************************************************/
/**
\brief  stsserr


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsserr"

void bsts :: stsserr ( )
{

  sts1 |= stserr;

}

/******************************************************************************/
/**
\brief  stssetini


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stssetini"

void bsts :: stssetini ( )
{

  sts1 |= stsinit; 


}

/******************************************************************************/
/**
\brief  stssfil


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stssfil"

void bsts :: stssfil ( )
{

  sts1 |= stsfil;
  stsrsav();
  stsrmod();
  stsrerr();

}

/******************************************************************************/
/**
\brief  stssini


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stssini"

void bsts :: stssini ( )
{

  sts1 |= stsinit; 
  stsrsav();
  stsrmod();
  stsrfil();
  stsrold();
  stsrerr();
  stsrres();

}

/******************************************************************************/
/**
\brief  stsslck


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsslck"

void bsts :: stsslck ( )
{

  sts1 |= stslck;

}

/******************************************************************************/
/**
\brief  stssmod


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stssmod"

void bsts :: stssmod ( )
{

  sts1 |= stsmod;

}

/******************************************************************************/
/**
\brief  stssnof


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stssnof"

void bsts :: stssnof ( )
{

  sts2 |= stsnof;

}

/******************************************************************************/
/**
\brief  stssold


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stssold"

void bsts :: stssold ( )
{

  sts2 |= stsold;

}

/******************************************************************************/
/**
\brief  stssres


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stssres"

void bsts :: stssres ( )
{

  sts2 |= stsres;

}

/******************************************************************************/
/**
\brief  stsssav


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsssav"

void bsts :: stsssav ( )
{

  sts2 |= stssav;

}

/******************************************************************************/
/**
\brief  stsstrans


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsstrans"

void bsts :: stsstrans ( )
{

  sts2 |= ststrans;

}

/******************************************************************************/
/**
\brief  stssusr1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stssusr1"

void bsts :: stssusr1 ( )
{

  sts2 |= stsuser1;

}

/******************************************************************************/
/**
\brief  stssusr2


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stssusr2"

void bsts :: stssusr2 ( )
{

  sts2 |= stsuser2;

}

/******************************************************************************/
/**
\brief  stssusr3


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stssusr3"

void bsts :: stssusr3 ( )
{

  sts2 |= stsuser3;

}

/******************************************************************************/
/**
\brief  stsswpt


\param  wpmode -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stsswpt"

void bsts :: stsswpt (uint8 wpmode )
{

  stsrwpt();
  stsawpt(wpmode);

}


