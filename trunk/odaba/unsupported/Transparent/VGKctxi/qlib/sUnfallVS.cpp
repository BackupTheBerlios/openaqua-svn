/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sUnfallVS

\brief    


\date     $Date: 2006/07/07 18:15:24,23 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sUnfallVS"

#include  <pvgkctxi.h>
#include  <sCTX_Structure.hpp>
#include  <ssUnfallVS.hpp>


/******************************************************************************/
/**
\brief  Create - 



\return rc - return value

\param  ctx_str_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sUnfallVS :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new sUnfallVS();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBCreate - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreate"

logical sUnfallVS :: DBCreate ( )
{

  return ( sVS_base::DBCreate_intern("UN") );

}

/******************************************************************************/
/**
\brief  DBCreated - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreated"

logical sUnfallVS :: DBCreated ( )
{

  SetupCollectionsByTyp();
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

logical sUnfallVS :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("SetupCollectionsByTyp",ALINK(this,sUnfallVS,SetupCollectionsByTyp)),
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
    term = sVS_base::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Export - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Export"

logical sUnfallVS :: Export ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsClient() )                            LEAVESEQ
  
  sVS_base::SetupCollectionsByTyp();
  
  ph->GPH("gliedertaxe")->ExecutePropertyAction("SetupCollectionByTyp",NULL);
  ph->GPH("optionen")->ExecutePropertyAction("SetupCollectionByTyp",NULL);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupCollectionsByTyp - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCollectionsByTyp"

logical sUnfallVS :: SetupCollectionsByTyp ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsServer() )                            LEAVESEQ
  
  sVS_base::SetupCollectionsByTyp();
  
  ph->GPH("gliedertaxe")->ExecutePropertyAction("SetupCollectionByTyp",NULL);
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sUnfallVS - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sUnfallVS"

     sUnfallVS :: sUnfallVS ( )
                     : sVS_base()
{



}

/******************************************************************************/
/**
\brief  ~sUnfallVS - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sUnfallVS"

     sUnfallVS :: ~sUnfallVS ( )
{



}


