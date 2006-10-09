/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    fmcl

\brief    


\date     $Date: 2006/03/12 19:22:29,71 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "fmcl"

#include  <pdefault.h>
#include  <sfmcb.hpp>
#include  <sfmcl.hpp>
#include  <sfmcl.hpp>


/******************************************************************************/
/**
\brief  GetFMCB - 


\return fmcbptr - Field definition block
-------------------------------------------------------------------------------
\brief FMCLFMCG


\param  fldnames - Field name
\param  syn_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFMCB"

fmcb *fmcl :: GetFMCB (char *fldnames, logical syn_opt )
{
  fmcb         *fmcbptr = NULL;
  char          name[ID_SIZE];
  int32         indx    = 0;

BEGINSEQ
  if ( !this )                                       ERROR
  stsrerr();

  gvtxstb(name, fldnames,sizeof(name));

  while ( fmcbptr = GetEntry(++indx) )
  {
    if ( !memcmp(fmcbptr->fmcbname,name,sizeof(fmcbptr->fmcbname)) )
                                                     LEAVESEQ
    if ( syn_opt && fmcbptr->IsSynonym(fldnames) )   LEAVESEQ
  }
RECOVER

ENDSEQ
  return(fmcbptr);

}

/******************************************************************************/
/**
\brief i01


\param  fldnames - Field name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFMCB"

fmcb *fmcl :: GetFMCB (char *fldnames )
{

  return ( GetFMCB(fldnames,NO) );

}

/******************************************************************************/
/**
\brief  fmcl

-------------------------------------------------------------------------------
\brief FMCL_


\param  maxe -
\param  expand -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcl"

                        fmcl :: fmcl (int32 maxe, logical expand )
                     : GSRT(fmcb) (maxe,
 sizeof(fmcb),UNDEF,UNDEF,UNDEF,expand)

{



}

/******************************************************************************/
/**
\brief FMCL_C


\param  fmclptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcl"

                        fmcl :: fmcl (fmcl *fmclptr )
                     : GSRT(fmcb) (fmclptr->GetCount(),
 sizeof(fmcb),UNDEF,UNDEF,UNDEF,NO)

{
  fmcb     *fmcbptr;
  int       indx = 0;

BEGINSEQ
  SOSCERR

  while ( fmcbptr = fmclptr->GetEntry(++indx) )
    AddEntry(indx,fmcbptr);

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief FMCL_T


\param  table -
\param  tesize -
\param  ecnt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcl"

                        fmcl :: fmcl (fmcb *table, int16 tesize, int32 ecnt )
                     : GSRT(fmcb)(ecnt,tesize,UNDEF,UNDEF,UNDEF,table,
           !table)

{



}

/******************************************************************************/
/**
\brief  fmclicmp

\return cmpval - Comparision result

\param  srcefmcl -
\param  targinst - Structured instance
\param  srceinst - Structured instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmclicmp"

int fmcl :: fmclicmp (fmcl *srcefmcl, char *targinst, char *srceinst )
{
  fmcb          *srcefmcb;
  fmcb          *targfmcb;
  register int   indx   = 0;
  int            cmpval = UNDEF;

BEGINSEQ
  if ( !this || !srcefmcl )                          ERROR
  stsrerr();
  
  if ( GetCount() != srcefmcl->GetCount() )          ERROR
       
  while ( srcefmcb = srcefmcl->GetEntry(++indx) )
  {
    if ( !(targfmcb = GetFMCB(srcefmcb->fmcbname,YES)) )
                                                     ERROR
    if ( (cmpval = targfmcb->fmcbicmp(srcefmcb,targinst+targfmcb->fmcbposn,
                                       srceinst+srcefmcb->fmcbposn)) )
                                                     LEAVESEQ   
  }

RECOVER
  if ( this && SOSERROR )
    stsserr();
ENDSEQ
  return(cmpval);

}

/******************************************************************************/
/**
\brief  fmclicpy

\return term - Success

\param  srcefmcl -
\param  targinst - Structured instance
\param  srceinst - Structured instance area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmclicpy"

logical fmcl :: fmclicpy (fmcl *srcefmcl, char *targinst, char *srceinst )
{
  fmcb          *srcefmcb;
  fmcb          *targfmcb;
  register int   indx = 0;
  logical        term = NO;

BEGINSEQ

  if ( !this || !srcefmcl )                                ERROR
  stsrerr();

  while ( srcefmcb = srcefmcl->GetEntry(++indx) )
    if ( targfmcb = GetFMCB(srcefmcb->fmcbname,YES) )
      if ( targfmcb->fmcbicpy(srcefmcb,targinst+targfmcb->fmcbposn,
                                       srceinst+srcefmcb->fmcbposn) )
                                                           ERROR
RECOVER
  if ( this && SOSERROR )
    stsserr();
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  fmcliini

\return term - Success

\param  instptr - Structured instance
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fmcliini"

logical fmcl :: fmcliini (char *instptr )
{
  fmcb      *fmcbptr;
  short      indx = 0;
  logical        term = NO;

BEGINSEQ
  if ( !this )                                       ERROR
  stsrerr();

  while ( fmcbptr = GetEntry(++indx) )
    if ( fmcbptr->fmcbiini(instptr+fmcbptr->fmcbposn) )
                                                     ERROR

RECOVER
  if ( this && SOSERROR )
    stsserr();
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  ~fmcl


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~fmcl"

                        fmcl :: ~fmcl ( )
{



}


