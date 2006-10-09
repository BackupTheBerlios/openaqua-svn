/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    sve

\brief    


\date     $Date: 2006/03/12 19:22:49,25 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sve"

#include  <pdefault.h>
#include  <ssve.hpp>


/******************************************************************************/
/**
\brief  sve


\param  vnames -
\param  vtext -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sve"

                        sve :: sve (char *vnames, char *vtext )
                     :   svetext()
{

BEGINSEQ
  gvtxstb(svename,vnames,sizeof(svename));
  if ( svetext.bdsaloc(strlen(vtext)+1) )            ERROR
  svetext += vtext;

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  sveupd

\return term - Success

\param  vtext -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sveupd"

logical sve :: sveupd (char *vtext )
{
  logical   term = NO;

BEGINSEQ
  if ( svetext.bdsmgt() < strlen(vtext)+1 )
  {
    svetext.bdsfree();
    if ( svetext.bdsaloc(strlen(vtext)+1) )          ERROR
  }

  svetext.bdslst(0);
  svetext += vtext;
  svetext.bdsagt()[svetext.bdslgt()] = 0;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}


