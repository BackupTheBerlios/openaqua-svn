/********************************* Class Source Code ***************************/
/**
\package  AdkCtxi
\class    sADK_FieldControl



\date     $Date: 2006/06/01 16:00:31,90 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sADK_FieldControl"

#include  <padkctxi.h>
#include  <spc_ADK_FieldControl.hpp>
#include  <ssADK_FieldControl.hpp>


/******************************************************************************/
/**
\brief  AddColumn

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddColumn"

logical sADK_FieldControl :: AddColumn ( )
{
  int32             pos;
  logical           term      = NO;
BEGINSEQ
  if ( !Parm(1) )                                   ERROR

  if ( Parm(2) )
    pos = atoi(Parm(2));
    
  if ( pc_ADK_FieldControl(GetPropertyHandle()).AddColumn(Parm(1),pos) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddField

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddField"

logical sADK_FieldControl :: AddField ( )
{
  int32             posx;
  int32             posy;
  logical           term      = NO;
BEGINSEQ
  if ( !Parm(1) )                                   ERROR

  if ( Parm(2) )
    posx = atoi(Parm(2));
  if ( Parm(3) )
    posy = atoi(Parm(3));
    
  if ( pc_ADK_FieldControl(GetPropertyHandle()).AddField(Parm(1),posx,posy) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddRegion

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddRegion"

logical sADK_FieldControl :: AddRegion ( )
{
  int32             pos;
  logical           term      = NO;
BEGINSEQ
  if ( !Parm(1) )                                   ERROR

  if ( Parm(2) )
    pos = atoi(Parm(2));
    
  if ( pc_ADK_FieldControl(GetPropertyHandle()).AddRegion(Parm(1),pos) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  AddTabControl

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddTabControl"

logical sADK_FieldControl :: AddTabControl ( )
{
  int32             posx;
  int32             posy;
  logical           term      = NO;
BEGINSEQ
  if ( Parm(1) )
    posx = atoi(Parm(1));
  if ( Parm(2) )
    posy = atoi(Parm(2));
    
  if ( pc_ADK_FieldControl(GetPropertyHandle()).AddTabControl(posx,posy) )
                                                     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Create

\return rc

\param  strctx_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sADK_FieldControl :: Create (CTX_Structure **strctx_ptrp )
{

  *strctx_ptrp = new sADK_FieldControl();
  return(NO);


}

/******************************************************************************/
/**
\brief  ExecuteFunction

\return 

\param  fname
\param  chk_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical sADK_FieldControl :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("AddColumn",ALINK(this,sADK_FieldControl,AddColumn)),
                           cfte("AddField",ALINK(this,sADK_FieldControl,AddField)),
                           cfte("AddRegion",ALINK(this,sADK_FieldControl,AddRegion)),
                           cfte("AddTabControl",ALINK(this,sADK_FieldControl,AddTabControl)),
                         };
  static srt  cftesrt(sizeof(acttbl)/CFTE,CFTE,UNDEF,UNDEF,UNDEF,(char *)acttbl,NO);

  if ( !cftesrt.srtkln() )
    cftesrt.srtsor(CFTE_KPS,CFTE_KLN,CFTE_KTP);

  if ( cfteptr = (cfte *)cftesrt.srtigt(cftesrt.srtssr(gvtxstb(actname,fname,ID_SIZE))) )
  {
    if ( chk_opt )                                   LEAVESEQ
    term = cfteptr->ActionCall(this);
  }
  else
    term = sLanguageDependendBase::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sADK_FieldControl - Konstruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sADK_FieldControl"

     sADK_FieldControl :: sADK_FieldControl ( )
                     : sLanguageDependendBase ()
{
}

/******************************************************************************/
/**
\brief  ~sADK_FieldControl - Destruktor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sADK_FieldControl"

     sADK_FieldControl :: ~sADK_FieldControl ( )
{
}


