/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    trc

\brief    


\date     $Date: 2006/03/12 19:22:51,03 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "trc"

#include  <pdefault.h>
#include  <dosdt.h>
#include  <streams.h>
#include  <strc.hpp>


/******************************************************************************/
/**
\brief  trc


\param  trcptr -
\param  objid -
\param  modid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "trc"

                        trc :: trc (trc **trcptr, char *objid, char *modid )
                     : trctrcp(trcptr), trcbegs(0), trcreco(0), trcends(0), 
 trcetim(0), trcstim(0)

{

  gvtxstb(trconame,objid,ID_SIZE);
  gvtxstb(trcfname,modid,ID_SIZE);


}

/******************************************************************************/
/**
\brief  trcbeg


\param  objid -
\param  modid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "trcbeg"

void trc :: trcbeg (char *objid, char *modid )
{

#ifndef _USRDLL
  if ( trcends == trcbegs )
#ifdef __unix__
  trcstim = clock();
#else
  QueryPerformanceCounter( (LARGE_INTEGER*) &trcstim );
#endif
#endif

  trcbegs++;


}

/******************************************************************************/
/**
\brief  trcend


\param  objid -
\param  modid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "trcend"

void trc :: trcend (char *objid, char *modid )
{
  int64       exectim = 0;

#ifndef _USRDLL
#ifdef __unix__
  exectim = clock();
#else
  QueryPerformanceCounter( (LARGE_INTEGER*) &exectim );
#endif
#endif

  trcends++;
  if ( trcends == trcbegs )
  {
    trcetim += (exectim - trcstim);
    trcstim = 0;
  }


}

/******************************************************************************/
/**
\brief  trcprn


\param  output -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "trcprn"

void trc :: trcprn (std::ostream &output )
{
  char      string[20];
  char      cnum[20];
  int64   frequency=1;

  memset(string,0,sizeof(string));
  memset(cnum,0,sizeof(cnum));
  memcpy(string,trconame,7);
  memcpy(string+7,trcfname,12);

#ifndef __unix__
  QueryPerformanceFrequency( (LARGE_INTEGER*)frequency );
#endif
  output << "\n" 
         << string
         << "\t" << trcbegs
         << "\t" << trcreco 
         << "\t" << trcends
         << "\t" << gvtxltp((char *)memcpy(cnum,"ZZZZZ9,999",11),(int32)(trcetim/frequency),10);


}

/******************************************************************************/
/**
\brief  trcrec


\param  objid -
\param  modid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "trcrec"

void trc :: trcrec (char *objid, char *modid )
{

  trcreco++;


}

/******************************************************************************/
/**
\brief  trcutrc


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "trcutrc"

void trc :: trcutrc ( )
{

  *trctrcp = this;

}


