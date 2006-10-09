/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    ptypecollection

\brief    


\date     $Date: 2006/06/20 15:09:53,21 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ptypecollection"

#include  <pvgkctxi.h>
#include  <spc_typ_collection.hpp>
#include  <sptypecollection.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - return value

\param  ctx_prop_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 ptypecollection :: Create (CTX_Property **ctx_prop_ptrp )
{

  *ctx_prop_ptrp = new ptypecollection();
  return(NO);


}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return  - 

\param  fname - Name der Funktion
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical ptypecollection :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("SetupCollectionByTyp",ALINK(this,ptypecollection,SetupCollectionByTyp)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    cfteptr->LINKINST(this);
    term = cfteptr->ActionCall();
  }
  else
    term = CTX_Property::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupCollectionByTyp - 


\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCollectionByTyp"

logical ptypecollection :: SetupCollectionByTyp ( )
{
  PropertyHandle    *ph   = GetPropertyHandle();
  logical            term = NO;
BEGINSEQ
  if ( !ph->IsServer() )                            LEAVESEQ
  
  if ( pc_typ_collection(ph).SetupCollectionByTyp() )
                                                    ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ptypecollection - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ptypecollection"

     ptypecollection :: ptypecollection ( )
                     : CTX_Property()
{



}

/******************************************************************************/
/**
\brief  ~ptypecollection - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ptypecollection"

     ptypecollection :: ~ptypecollection ( )
{



}


