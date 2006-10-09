/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    stest

\brief    


\date     $Date: 2006/03/12 19:19:34,71 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "stest"

#include  <popa7.h>
#include  <sstest.hpp>


/******************************************************************************/
/**
\brief  ExecuteFunction

\return term - Termination code

\param  fname -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical stest :: ExecuteFunction (char *fname )
{
  char     actname[16];
  cfte    *cfteptr;
  logical  term      = NO;


  static cfte acttbl[] = { 
                           cfte("Test1",ALINK(this,stest,Test1)),
                         };
  static srt  cftesrt(NULL,sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,16))) )
  {
    cfteptr->LINKINST(this);
    term = cfteptr->ActionCall();
  }
  else
    term = CTX_Structure::ExecuteFunction(fname);          

//  if ( term )
//    DisplayMessage();

  return(term);
}

/******************************************************************************/
/**
\brief  Test1

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Test1"

logical stest :: Test1 ( )
{
  logical                 term = NO;
  sdbuptr->DisplayMessage(998,"Das ist Test Nummer Eins");
  return(term);
}

/******************************************************************************/
/**
\brief  stest

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "stest"

                        stest :: stest ( )
                     : CTX_Structure ()
{



}

/******************************************************************************/
/**
\brief  ~stest

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~stest"

                        stest :: ~stest ( )
{



}


