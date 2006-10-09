/********************************* Class Source Code ***************************/
/**
\package  VGKctxi - 
\class    sVS_base

\brief    


\date     $Date: 2006/07/17 18:50:48,57 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sVS_base"

#include  <pvgkctxi.h>
#include  <spc_Action.hpp>
#include  <ssVS_base.hpp>


/******************************************************************************/
/**
\brief  DBCreate_intern - 



\return term - Abbruchbedingung

\param  sparte_str - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreate_intern"

logical sVS_base :: DBCreate_intern (char *sparte_str )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  dttm              datetime;
  datetime.SetCurrent();
  ph->GPH("created")->SetValue(datetime,NO);
  ph->GPH("sparte")->SetValue(sparte_str,NO);
  return(NO);
}

/******************************************************************************/
/**
\brief  DBCreated - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBCreated"

logical sVS_base :: DBCreated ( )
{
  PropertyHandle  *ph   = GetPropertyHandle();
BEGINSEQ
  if ( !ph->IsServer() )                            LEAVESEQ

  PropertyHandle     state1("1");
  ph->GPH("status")->Add(state1);

  ph->GPH("ausgangs_daten")->Add(FIRST_INSTANCE);
  
  SetupCollectionsByTyp();
  FillIdentifier();
ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  DBOpened - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBOpened"

logical sVS_base :: DBOpened ( )
{
  PropertyHandle  *ph   = GetPropertyHandle();
  char             typnames[ID_SIZE+1];
  logical          term = NO;

BEGINSEQ
  strcat(strcpy(typnames,ph->GetCurrentType()),"Ausgangsdaten");
  ph->GPH("ausgangs_daten")->SetType(typnames);     SDBCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DBRead - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DBRead"

logical sVS_base :: DBRead ( )
{
  logical          term = NO;
  FillIdentifier();
  return(term);
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

logical sVS_base :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("SetupCollectionsByTyp",ALINK(this,sVS_base,SetupCollectionsByTyp)),
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
\brief  FillIdentifier - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillIdentifier"

logical sVS_base :: FillIdentifier ( )
{
  PropertyHandle  *ph   = GetPropertyHandle();
  NString          nstring;
  logical          term = NO;
  *GPH("identifier") = pc_Action(ph).GetIdentString(nstring,NO,NO);
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

logical sVS_base :: SetupCollectionsByTyp ( )
{
  PropertyHandle  *ph   = GetPropertyHandle();
  logical          term = NO;
  ph->GPH("leistungenD")->ExecutePropertyAction("SetupCollectionByTyp",NULL);
  ph->GPH("leistungenO")->ExecutePropertyAction("SetupCollectionByTyp",NULL);
  ph->GPH("leistungenI")->ExecutePropertyAction("SetupCollectionByTyp",NULL);
  return(term);
}

/******************************************************************************/
/**
\brief  sVS_base - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sVS_base"

     sVS_base :: sVS_base ( )
                     : CTX_Structure()
{



}

/******************************************************************************/
/**
\brief  ~sVS_base - 



\return term - Abbruchbedingung

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sVS_base"

     sVS_base :: ~sVS_base ( )
{



}


