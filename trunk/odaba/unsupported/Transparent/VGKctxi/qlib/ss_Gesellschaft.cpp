/********************************* Class Source Code ***************************/
/**
\package  VGKctxi
\class    ss_Gesellschaft



\date     $Date: 2006/05/16 14:37:54,64 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ss_Gesellschaft"

#include  <pvgkctxi.h>
#include  <sss_Gesellschaft.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc - return value

\param  ctx_str_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 ss_Gesellschaft :: Create (CTX_Structure **ctx_str_ptrp )
{

  *ctx_str_ptrp = new ss_Gesellschaft();
  return(NO);


}

/******************************************************************************/
/**
\brief  DBCreated

\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreated"

logical ss_Gesellschaft :: DBCreated ( )
{

  SetupCollectionsByTyp();
  return(NO);
}

/******************************************************************************/
/**
\brief  ExecuteFunction

\return 

\param  fname - Name der Funktion
\param  chk_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical ss_Gesellschaft :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("SetupCollectionsByTyp",ALINK(this,ss_Gesellschaft,SetupCollectionsByTyp)),
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
    term = CTX_Structure::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupCollectionsByTyp

\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupCollectionsByTyp"

logical ss_Gesellschaft :: SetupCollectionsByTyp ( )
{
  PropertyHandle  *ph   = GetPropertyHandle();
  logical          term = NO;
  ph->GPH("kontakte")->ExecutePropertyAction("SetupCollectionByTyp",NULL);
  ph->GPH("antrags_uebermittlungen")->ExecutePropertyAction("SetupCollectionByTyp",NULL);

  return(term);
}

/******************************************************************************/
/**
\brief  ss_Gesellschaft


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ss_Gesellschaft"

     ss_Gesellschaft :: ss_Gesellschaft ( )
                     : CTX_Structure()
{
}

/******************************************************************************/
/**
\brief  ~ss_Gesellschaft

\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ss_Gesellschaft"

     ss_Gesellschaft :: ~ss_Gesellschaft ( )
{


}


