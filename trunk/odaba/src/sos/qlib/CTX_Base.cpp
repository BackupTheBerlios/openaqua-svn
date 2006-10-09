/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    CTX_Base

\brief    General Context Class


\date     $Date: 2006/08/28 11:58:32,43 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "CTX_Base"

#include  <pdefault.h>
#include  <ctxdef.h>
class     CTX_UCBase;
#include  <sCTX_Base.hpp>
#include  <sError.hpp>
#include  <sErrorMessage.hpp>
#include  <sNParm.hpp>
#include  <sSimpleAction.hpp>
#include  <sSystemIO.hpp>
#include  <sUCA_Action.hpp>
#include  <sUCA_CAction.hpp>
#include  <ssvel.hpp>
#include  <sCTX_Base.hpp>

int32 ctx_count = 0;
int32 ctx_max = 0;

/******************************************************************************/
/**
\brief  CTX_Base - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CTX_Base"

     CTX_Base :: CTX_Base ( )
                     : vcls (),
  high_ctx(NULL),
  user_states(),
  intern_states(),
  action_rc(AUTO),
  action_parms(NULL)

{


if ( ++ctx_count > ctx_max ) ctx_max = ctx_count;
}

/******************************************************************************/
/**
\brief  CheckPermission - 


\return cont - 

\param  actptr - Action pointer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckPermission"

logical CTX_Base :: CheckPermission (UCA_Action *actptr )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  Close - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical CTX_Base :: Close ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  CreateAction - 


\return actptr - Action pointer

\param  action - Simple action
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateAction"

UCA_Action *CTX_Base :: CreateAction (SimpleAction *action )
{

  return (UCA_Action::Create(action->get_action_type(),
                             action->get_action_name(), this));

}

/******************************************************************************/
/**
\brief  CreateCAction - 


\return cactptr - 

\param  prehandler - Pre-handler
\param  action - Simple action
\param  postandler - Post-handler
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateCAction"

UCA_CAction *CTX_Base :: CreateCAction (SimpleAction *prehandler, SimpleAction *action, SimpleAction *postandler )
{
  UCA_CAction            *cactptr;
  UCA_Action             *pre_action  = NULL;
  UCA_Action             *cur_action  = NULL;
  UCA_Action             *post_action = NULL;
BEGINSEQ
  if ( action )
    if ( !(cur_action = CreateAction(action)) )      ERROR
  
  if ( prehandler )
    if ( !(pre_action = CreateAction(prehandler)) )  SOSCERR

  if ( postandler )
    if ( !(post_action = CreateAction(postandler)) ) SOSCERR
  
  if ( !(cactptr = new UCA_CAction(pre_action,cur_action,post_action)) )  
                                                     SOSERR(95)

RECOVER
  if ( pre_action ) 
    delete pre_action;
  if ( post_action ) 
    delete post_action;
  if ( cur_action ) 
    delete cur_action;
  cactptr = NULL;
ENDSEQ
  return(cactptr);
}

/******************************************************************************/
/**
\brief  DataState - 


\return datstate - Data state

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DataState"

CTX_DataStates CTX_Base :: DataState ( )
{

  return ( this ? intern_states.data_state : DAT_undefined);

}

/******************************************************************************/
/**
\brief  DeleteData - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteData"

logical CTX_Base :: DeleteData ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  Disable - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Disable"

void CTX_Base :: Disable ( )
{

  intern_states.DisableContext();

}

/******************************************************************************/
/**
\brief  DisplayDecision - 


\return mult_dec - 

\param  msgnum - Message number
\param  buttons - Decision combinations
\param  def_dec - Default reply
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
\param  parm3 - Third message variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayDecision"

ReplyTypes CTX_Base :: DisplayDecision (int16 msgnum, ReplyCombi buttons, ReplyTypes def_dec, char *parm1, char *parm2, char *parm3 )
{
  ReplyTypes  mult_dec = RT_none;
  char       *msgtext;


/*
  if ( msgnum )
    P_ISET(msgnum);

  if ( msgtext = P_Error().adceget(GetRESDB(),
                                 parm1 ? parm1 : *sdbuptr->sdbuerv1  ? sdbuptr->sdbuerv1 : NULL,
                                 parm2 ? parm2 : *sdbuptr->sdbuerv2  ? sdbuptr->sdbuerv2 : NULL,
                                 parm3 ? parm3 : *sdbuptr->sdbuerv3  ? sdbuptr->sdbuerv3 : NULL,
                                                 *sdbuptr->sdbuerv4  ? sdbuptr->sdbuerv4 : NULL,
                                                 *sdbuptr->sdbuerv5  ? sdbuptr->sdbuerv5 : NULL ) )

    mult_dec = adcw::adcwdec(msgtext,P_Error().sdbehidg(),buttons,def_dec,GetWindow());

  P_RESET
*/
  return(mult_dec);


}

/******************************************************************************/
/**
\brief  DisplayMessage - 



\param  w_msgnum - Message code
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
\param  parm3 - Third message variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayMessage"

void CTX_Base :: DisplayMessage (int16 w_msgnum, char *parm1, char *parm2, char *parm3 )
{

/*
  if ( msgnum )
    P_ISET(msgnum);

  if ( parm1 )
    SDBUERV1(parm1,UNDEF);
  if ( parm2 )
    SDBUERV2(parm2,UNDEF);
  if ( parm3 )
    SDBUERV3(parm3,UNDEF);
*/
//  P_Error().DisplayMessage(GetWindow());


}

/******************************************************************************/
/**
\brief  DisplayState - 


\return dsptype - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DisplayState"

CTX_DisplayState CTX_Base :: DisplayState ( )
{

  return ( this ? intern_states.display_state : DSP_undefined);

}

/******************************************************************************/
/**
\brief  Enable - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Enable"

void CTX_Base :: Enable ( )
{

  intern_states.EnableContext();

}

/******************************************************************************/
/**
\brief  ExecLogin - 


\return term - Success

\param  prophdl - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecLogin"

logical CTX_Base :: ExecLogin (PropertyHandle *prophdl )
{

  return(YES);

}

/******************************************************************************/
/**
\brief  ExecuteAction - 


\return term - Success
-------------------------------------------------------------------------------
\brief  FNCACTE_ - 


\param  acnames - Action name
\param  actype - Action type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

logical CTX_Base :: ExecuteAction (char *acnames, ActionType actype )
{
  char        acname[ID_SIZE];
  UCA_Action *actptr = NULL;
  logical     term   = NO;

BEGINSEQ
  if ( !acnames )                                    ERROR

  SimpleAction sact(acnames,actype);
  if ( !(actptr = CreateAction(&sact)) )             ERROR
  if ( actptr->Execute() )                           ERROR

RECOVER
  term = YES;
ENDSEQ
  delete actptr;
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  eventid - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteAction"

logical CTX_Base :: ExecuteAction (InternalEvent eventid )
{
  logical                 term = NO;
BEGINSEQ
  if ( !this )                                       LEAVESEQ
  
  switch ( eventid )
  {
    case CA_Close       : term = Close();        break;
    case CA_DeleteData  : term = DeleteData();   break;
    case CA_FillData    : term = FillData();     break;
    case CA_InsertData  : term = InsertData();   break;
    case CA_SaveData    : term = SaveData();     break;
    case CA_NextData    : term = NextData();     break;
    case CA_Open        : term = Open();         break;
    case CA_PreviousData: term = PreviousData(); break;
    case CA_ResetData   : term = ResetData();    break;
    case CA_StoreData   : term = StoreData();    break;
    default             : ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return term - Success
-------------------------------------------------------------------------------
\brief  FNCEXE - 


\param  fname - Function name
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical CTX_Base :: ExecuteFunction (char *fname, logical chk_opt )
{
  char         buffer[ID_SIZE];
  short        indx0     = 0;
  logical      term      = NO;
BEGINSEQ
  static char *functbl[] = { 
                             "fc_dummy                                ",  //  1
                             "Close                                   ",  //  2
                             "DeleteData                              ",  //  3
                             "FillData                                ",  //  4
                             "InsertData                              ",  //  5
                             "SaveData                                ",  //  6
                             "NextData                                ",  //  7
                             "Open                                    ",  //  8
                             "PeviousData                             ",  //  9
                             "ResetData                               ",  // 10
                             "StoreData                               ",  // 11
                           };
  short int  funccnt   = sizeof(functbl)/sizeof(functbl[0]);    
    
  gvtxstb(buffer,fname,ID_SIZE);
  
  while ( indx0++ < funccnt )
    if ( !memcmp(buffer,functbl[indx0-1],16) )
      break;

  if ( chk_opt )
  {
    if ( indx0 <= funccnt )
      term = NO;
    LEAVESEQ
  }
  
  switch ( indx0 )
  {
    case  1 :                                               break;
    case  2 : term = Close();                               break;
    case  3 : term = DeleteData();                          break;
    case  4 : term = FillData();                            break;
    case  5 : term = InsertData();                          break;
    case  6 : term = SaveData();                            break;
    case  7 : term = NextData();                            break;
    case  8 : term = Open();                                break;
    case  9 : term = PreviousData();                        break;
    case 10 : term = ResetData();                           break;
    case 11 : term = StoreData();                           break;
    default : SOSEV1(buffer,ID_SIZE); 
              SOSERR(100)
  } 

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i1 - 


\param  fname - Function name
\param  parmcnt - Number of parameters
\param  parmlist - Parameter list
\param  retfld - Return value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical CTX_Base :: ExecuteFunction (char *fname, int16 parmcnt, PropertyHandle **parmlist, PropertyHandle &retfld )
{
  short int    indx0     = 0;                         
  char         buffer[ID_SIZE];
  logical      term      = NO;
BEGINSEQ
  static char *functbl[] = { 
                             "dummy           ",
                           };
  short int    funccnt   = sizeof(functbl)/sizeof(functbl[0]);                         

  gvtxstb(buffer,fname,ID_SIZE);
  
  while ( indx0++ < funccnt )
    if ( !memcmp(buffer,functbl[indx0-1],16) )
      break;

  switch ( indx0 )
  {
    case  1 : break;
    default : SOSERR(100);
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ExecuteProgram - 


\return term - Success

\param  prgnams - Program path
\param  pgmparm1 - First parameter
\param  pgmparm2 - Third parameter
\param  pgmparm3 - Third parameter
\param  pgmparm4 - Fourth parameter
\param  pgmparm5 - Fifth parameter
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteProgram"

logical CTX_Base :: ExecuteProgram (char *prgnams, char *pgmparm1, char *pgmparm2, char *pgmparm3, char *pgmparm4, char *pgmparm5 )
{
 

  return(::ExecuteProgram(prgnams,pgmparm1,pgmparm2,pgmparm3,pgmparm4,pgmparm5));
 

}

/******************************************************************************/
/**
\brief  FillData - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillData"

logical CTX_Base :: FillData ( )
{

  return(NO);

}

/******************************************************************************/
/**
\brief  FindContext - 


\return term - Success

\param  highctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindContext"

logical CTX_Base :: FindContext (CTX_Base *highctx )
{

  return ( !this ? YES : this == highctx ? NO : high_ctx->FindContext(highctx) );

}

/******************************************************************************/
/**
\brief  GUIContext - 


\return ucctx_ptr - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GUIContext"

CTX_UCBase *CTX_Base :: GUIContext ( )
{

  return(NULL);

}

/******************************************************************************/
/**
\brief  GenerateEvent - 


\return term - Success

\param  eventid - Event identifier
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateEvent"

logical CTX_Base :: GenerateEvent (InternalEvent eventid )
{


  return(YES);
}

/******************************************************************************/
/**
\brief  GetActionResult - 


\return rc - Retrun code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetActionResult"

int32 CTX_Base :: GetActionResult ( )
{


  return(action_rc);
}

/******************************************************************************/
/**
\brief  GetContextType - 


\return ctxtype - Context type

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetContextType"

CTX_Types CTX_Base :: GetContextType ( )
{


  return(CTXT_undefined);
}

/******************************************************************************/
/**
\brief  GetDecision - 


\return decision - 

\param  msgnum - Message number
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
\param  parm3 - Third message variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecision"

logical CTX_Base :: GetDecision (int16 msgnum, char *parm1, char *parm2, char *parm3 )
{
  char          *msgtext;
  logical        cont = YES;


/*  
  if ( msgnum )
    P_ISET(msgnum);

  if ( msgtext = P_Error().GetErrText()(GetRESDB(),
                                 parm1 ? parm1 : *sdbuptr->sdbuerv1  ? sdbuptr->sdbuerv1 : NULL,
                                 parm2 ? parm2 : *sdbuptr->sdbuerv2  ? sdbuptr->sdbuerv2 : NULL,
                                 parm3 ? parm3 : *sdbuptr->sdbuerv3  ? sdbuptr->sdbuerv3 : NULL,
                                                 *sdbuptr->sdbuerv4  ? sdbuptr->sdbuerv4 : NULL,
                                                 *sdbuptr->sdbuerv5  ? sdbuptr->sdbuerv5 : NULL ) )
    cont = adcw::adcwdsn(msgtext,WB_YES_NO,GetWindow());
  
  P_RESET
*/

  return(cont);

}

/******************************************************************************/
/**
\brief  GetMessageString - 


\return msg_string - 

\param  msgnum - Message number
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
\param  parm3 - Third message variable
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetMessageString"

char *CTX_Base :: GetMessageString (int16 msgnum, char *parm1, char *parm2, char *parm3 )
{
  char   *string = NULL;
//  int     saverr = P_ERROR;

/*
  P_ISET(msgnum);
  string = P_Error().GetErrText(adcappl->adcasysg() ? sdbuptr->sdbusys.dbhandle : sdbuptr->sdbures.dbhandle,
                           parm1,parm2,parm3);

  P_ISET(saverr);
*/

  return(string);

}

/******************************************************************************/
/**
\brief  GetParameters - 


\return term - Success

\param  pparm1 - 
\param  pparm2 - 
\param  pparm3 - 
\param  pparm4 - 
\param  pparm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParameters"

logical CTX_Base :: GetParameters (char **pparm1, char **pparm2, char **pparm3, char **pparm4, char **pparm5 )
{
  logical  term = NO;
  if ( pparm1 )
    *pparm1 = Parm(1);
  if ( pparm2 )  
    *pparm2 = Parm(2);
  if ( pparm3 )  
    *pparm3 = Parm(3);
  if ( pparm4 )  
    *pparm4 = Parm(4);
  if ( pparm5 )  
    *pparm5 = Parm(5);

  return(term);
}

/******************************************************************************/
/**
\brief  GetResourceName - 


\return ResName - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetResourceName"

char *CTX_Base :: GetResourceName ( )
{


  return(NULL);
}

/******************************************************************************/
/**
\brief  GetSystemStates - 


\return sys_sts - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSystemStates"

sts &CTX_Base :: GetSystemStates ( )
{

  return(intern_states.sys_sts);

}

/******************************************************************************/
/**
\brief  HighContext - 


\return ctxptr - 
-------------------------------------------------------------------------------
\brief  FNCHIGHG - 


\param  ctxtype - Context type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HighContext"

CTX_Base *CTX_Base :: HighContext (CTX_Types ctxtype )
{

  return ( this && high_ctx && (ctxtype == CTXT_undefined || high_ctx->GetContextType() == ctxtype) 
           ? high_ctx : NULL);


}

/******************************************************************************/
/**
\brief  i1 - 


\param  resname - 
\param  ctxtype - Context type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HighContext"

CTX_Base *CTX_Base :: HighContext (char *resname, CTX_Types ctxtype )
{
  CTX_Base    *ctx_ptr = this;
  char         name[ID_SIZE];
  char         ctx_name[ID_SIZE];
  gvtxstb(name,resname,ID_SIZE);
  while ( ctx_ptr = ctx_ptr->HighContext() )
  {
    gvtxstb(ctx_name,ctx_ptr->GetResourceName(),ID_SIZE);
    if ( !memcmp(name,ctx_name,ID_SIZE) )
      if ( ctxtype == CTXT_undefined || ctx_ptr->GetContextType() == ctxtype )
        break;
  }
  return(ctx_ptr);

}

/******************************************************************************/
/**
\brief  InitData - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitData"

logical CTX_Base :: InitData ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Initialize - 



\param  highctx - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void CTX_Base :: Initialize (CTX_Base *highctx )
{

  high_ctx = highctx;


}

/******************************************************************************/
/**
\brief  Input - 


\return string - String value

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Input"

char *CTX_Base :: Input (char *string )
{

  return( SystemIO::ReadConsole(string) );

}

/******************************************************************************/
/**
\brief  InsertData - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertData"

logical CTX_Base :: InsertData ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  IsEdit - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEdit"

logical CTX_Base :: IsEdit ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  IsEnabled - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEnabled"

logical CTX_Base :: IsEnabled ( )
{

  return(!intern_states.element_stati[RQ_Disabled]);

}

/******************************************************************************/
/**
\brief  NextData - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextData"

logical CTX_Base :: NextData ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical CTX_Base :: Open ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  Output - 


\return term - Success

\param  string - String value
\param  clear_opt - 
\param  flush_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Output"

logical CTX_Base :: Output (char *string, logical clear_opt, logical flush_opt )
{
  CTX_Base       *applctx = GetApplicationContext();
  return( applctx && applctx != this
          ? applctx->Output(string,clear_opt,flush_opt)
          : SystemIO::WriteConsole(string,clear_opt,flush_opt) );

}

/******************************************************************************/
/**
\brief  Parm - 


\return parm_string - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  parm_no - Parm number
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parm"

char *CTX_Base :: Parm (int32 parm_no )
{
  char                   *parm_string = NULL;
BEGINSEQ
  if ( !action_parms )                               ERROR
    
  parm_string = (*action_parms)(parm_no);
RECOVER

ENDSEQ
  return(parm_string);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  parm_key - Parameter keyword
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parm"

char *CTX_Base :: Parm (char *parm_key )
{
  char                   *parm_string = NULL;
BEGINSEQ
  if ( !action_parms )                               ERROR
    
  parm_string = (*action_parms)(parm_key);
RECOVER

ENDSEQ
  return(parm_string);
}

/******************************************************************************/
/**
\brief  i02 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Parm"

char *CTX_Base :: Parm ( )
{

  return( action_parms->GetArea() );

}

/******************************************************************************/
/**
\brief  PreviousData - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PreviousData"

logical CTX_Base :: PreviousData ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  ProcessState - 


\return procstate - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProcessState"

CTX_ProcessState CTX_Base :: ProcessState ( )
{

  return ( this ? intern_states.process_state : PRC_undefined);

}

/******************************************************************************/
/**
\brief  ResetData - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetData"

logical CTX_Base :: ResetData ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  SaveData - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SaveData"

logical CTX_Base :: SaveData ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  SelectData - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SelectData"

logical CTX_Base :: SelectData ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  SetActionResult - 



\param  rc - Retrun code
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetActionResult"

void CTX_Base :: SetActionResult (int32 rc )
{

  action_rc = rc;

}

/******************************************************************************/
/**
\brief  SetDataState - 


\return datstate - Data state

\param  datstate - Data state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDataState"

CTX_DataStates CTX_Base :: SetDataState (CTX_DataStates datstate )
{

  return ( this ? intern_states.data_state = datstate : DAT_undefined);


}

/******************************************************************************/
/**
\brief  SetDisplayState - 


\return dspstate - Display state

\param  dspstate - Display state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetDisplayState"

CTX_DisplayState CTX_Base :: SetDisplayState (CTX_DisplayState dspstate )
{

  return ( this ? intern_states.display_state = dspstate : DSP_undefined);

}

/******************************************************************************/
/**
\brief  SetParm - 


\return term - Success

\param  parm1 - First Message parameter
\param  parm2 - Second message variable
\param  parm3 - Third message variable
\param  parm4 - 
\param  parm5 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetParm"

logical CTX_Base :: SetParm (char *parm1, char *parm2, char *parm3, char *parm4, char *parm5 )
{
  char                    separator;
  logical                 term = NO;
BEGINSEQ
  if ( !action_parms )
    SetupParm();
  separator = action_parms->get_separator();
  action_parms->Cut(0);
  
  if ( !parm1 )                                      LEAVESEQ
  action_parms->AddBuffer(parm1,strlen(parm1));

  if ( !parm2 )                                      LEAVESEQ
  action_parms->AddBuffer(&separator,1);
  action_parms->AddBuffer(parm2,strlen(parm2));

  if ( !parm3 )                                      LEAVESEQ
  action_parms->AddBuffer(&separator,1);
  action_parms->AddBuffer(parm3,strlen(parm3));

  if ( !parm4 )                                      LEAVESEQ
  action_parms->AddBuffer(&separator,1);
  action_parms->AddBuffer(parm4,strlen(parm4));

  if ( !parm5 )                                      LEAVESEQ
  action_parms->AddBuffer(&separator,1);
  action_parms->AddBuffer(parm5,strlen(parm5));

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetProcessState - 


\return prcstate - 

\param  prcstate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetProcessState"

CTX_ProcessState CTX_Base :: SetProcessState (CTX_ProcessState prcstate )
{

  return ( this ? intern_states.process_state = prcstate : PRC_undefined);

}

/******************************************************************************/
/**
\brief  SetRequest - 



\param  reqtype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetRequest"

void CTX_Base :: SetRequest (CTX_RequestTypes reqtype )
{

  intern_states.SetRequest(reqtype);


}

/******************************************************************************/
/**
\brief  SetUserState1 - 


\return userstat - User state

\param  userstat - User state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUserState1"

int16 CTX_Base :: SetUserState1 (int16 userstat )
{

  return(user_states.state1 = userstat);


}

/******************************************************************************/
/**
\brief  SetUserState2 - 


\return userstat - User state

\param  userstat - User state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUserState2"

int16 CTX_Base :: SetUserState2 (int16 userstat )
{

  return(user_states.state2 = userstat);


}

/******************************************************************************/
/**
\brief  SetUserState3 - 


\return userstat - User state

\param  userstat - User state
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUserState3"

int16 CTX_Base :: SetUserState3 (int16 userstat )
{

  return(user_states.state3 = userstat);


}

/******************************************************************************/
/**
\brief  SetupParm - 


\return term - Success

\param  separator - Separator character
\param  key_parms - Parmlist with key parameter format
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupParm"

logical CTX_Base :: SetupParm (char separator, logical key_parms )
{
  logical                 term = NO;
  if ( action_parms )
    delete action_parms;

  action_parms = new NParm(separator,key_parms);
  return(term);
}

/******************************************************************************/
/**
\brief  StoreData - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "StoreData"

logical CTX_Base :: StoreData ( )
{


  return(NO);
}

/******************************************************************************/
/**
\brief  UserState1 - 


\return userstate - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UserState1"

int16 CTX_Base :: UserState1 ( )
{

  return(user_states.state1);

}

/******************************************************************************/
/**
\brief  UserState2 - 


\return userstate - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UserState2"

int16 CTX_Base :: UserState2 ( )
{

  return(user_states.state2);

}

/******************************************************************************/
/**
\brief  UserState3 - 


\return userstate - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UserState3"

int16 CTX_Base :: UserState3 ( )
{

  return(user_states.state3);

}

/******************************************************************************/
/**
\brief  ~CTX_Base - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~CTX_Base"

     CTX_Base :: ~CTX_Base ( )
{

  delete action_parms;
  action_parms = NULL;
ctx_count--;
}


