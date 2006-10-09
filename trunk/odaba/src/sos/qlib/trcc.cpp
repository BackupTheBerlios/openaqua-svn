/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    trcc

\brief    


\date     $Date: 2006/03/12 19:22:51,31 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "trcc"

#include  <fileacc.h>
#include  <pdefault.h>
#include  <gtrcc.h>
#include  <streams.h>
#include  <ssrt.hpp>
#include  <strc.hpp>
#include  <strcc.hpp>


/******************************************************************************/
/**
\brief  trcc


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "trcc"

                        trcc :: trcc ( )
                     : trccpscb(NULL), trcctrc(NULL)

{

  trcctrc = new srt(100,sizeof(trc),32,1,'C',YES);
  


}

/******************************************************************************/
/**
\brief  trccloc

\return trcptr -

\param  trcptr -
\param  objid -
\param  modid -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "trccloc"

trc *trcc :: trccloc (trc **trcptr, char *objid, char *modid )
{
  short int   indx;
  trc         trcenty(trcptr,objid,modid);
BEGINSEQ
  if ( !(indx = trcctrc->srtssr(&trcenty)) )
    if ( !(indx = trcctrc->srtkad(&trcenty)) )        SOSPERR                //ERROR

  *trcptr = (trc *)trcctrc->srtigt(indx);

  for (indx=1; indx <= trcctrc->srtcnt(); indx++)
    ((trc *)trcctrc->srtigt(indx))->trcutrc(); 

RECOVER
  return(NULL);

ENDSEQ
  return(*trcptr);

}

/******************************************************************************/
/**
\brief  trccprnt


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "trccprnt"

void trcc :: trccprnt ( )
{
  short i;
  char      cpath[513];
  if ( filevfd("TRACE",cpath) )
  {
    std::ofstream output( strcat( cpath, "TRACE.LST" ), std::ios::app );
    if ( output )
/* 
    if( filevfd("TRACE",cpath) 
    &&  (handle = _open
                  ( strcat( cpath, "TRACE.LST" ),
		    (int)(O_WRONLY | O_APPEND  | O_CREAT | O_TEXT),
		    S_IWRITE                                
                  )) > 0 
    )
*/
    {
      output << "\n" 
             << "Object Function    "
             << "\t" << "#Calls"
             << "\t" << "#Error"
             << "\t" << "#Term."
             << "\t" << "Time\n";

      for( i=1; i <= trcctrc->srtcnt(); i++ )
        ((trc*)trcctrc->srtigt( i ))->trcprn( output );

      output.flush();
    }
  }

}

/******************************************************************************/
/**
\brief  ~trcc


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~trcc"

                        trcc :: ~trcc ( )
{

#ifndef __unix__
  trccprnt();
#endif

  delete trcctrc;
  trcctrc = NULL;
  
  msmcl(&trccpscb);



}


