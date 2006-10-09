/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cODCFunctionImpl

\brief    


\date     $Date: 2006/06/01 17:08:19,29 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cODCFunctionImpl"

#include  <pdesign.h>
#include  <sODE_SearchReplace.hpp>
#include  <sPropertyHandle.hpp>
#include  <sRegExp.hpp>
#include  <sintPair.hpp>
#include  <spODE.hpp>
#include  <spc1_ODC_FunctImp.hpp>
#include  <scODCFunctionImpl.hpp>


/******************************************************************************/
/**
\brief  Changed - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Changed"

logical cODCFunctionImpl :: Changed ( )
{
  PropertyHandle   *cur_pi   = GetPropertyHandle();
  CTX_Control      *context  = GetControlContext(NULL);
  CTX_Control      *lineedit = NULL;
  int               row      = -1;
  int               col      = -1;
  DPoint            pos;
  logical           term     = NO;

BEGINSEQ
  if ( !context || !cur_pi )                         ERROR
  
  if ( ctx_init == context )
    row = cur_pi->GetInt("init_count");
  else if ( ctx_start == context )
    row = cur_pi->GetInt("start_count");
  else if ( ctx_code  == context )
    row = cur_pi->GetInt("code_count");
  else if ( ctx_error == context )
    row = cur_pi->GetInt("error_count");
  else if ( ctx_term  == context )
    row = cur_pi->GetInt("term_count");
  else
    context = NULL;
    
  if ( context )
  {
    pos  = context->GetPosition();
    row += (pos.Y - 1);
    col  = pos.X;
  }
  if ( lineedit = GetFieldContext("statusbar.row") )
  {
    lineedit->GetPropertyHandle()->SetValue(row);
    lineedit->FillControl();
  }
  if ( lineedit = GetFieldContext("statusbar.column") )
  {
    lineedit->GetPropertyHandle()->SetValue(col);
    lineedit->FillControl();
  }
RECOVER
  term = YES;
ENDSEQ
  return (term);
}

/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  ctx_ctl_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cODCFunctionImpl :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cODCFunctionImpl();
  return(NO);

}

/******************************************************************************/
/**
\brief  DoAfterFillData - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterFillData"

int8 cODCFunctionImpl :: DoAfterFillData ( )
{

  pc1_ODC_FunctImp   impl_pc(GetPropertyHandle());
  SwitchInitStart(impl_pc.IsConstructor() ? 2 : 1);

  return(NO);
}

/******************************************************************************/
/**
\brief  DoAfterOpen - 


\return executed - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterOpen"

int8 cODCFunctionImpl :: DoAfterOpen ( )
{

  ctx_init  = GetFieldContext("init_start.init");
  ctx_start = GetFieldContext("init_start.start");
  ctx_code  = GetFieldContext("code");
  ctx_error = GetFieldContext("error");
  ctx_term  = GetFieldContext("term");

  return(NO);
}

/******************************************************************************/
/**
\brief  ExecSearchReplace - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecSearchReplace"

logical cODCFunctionImpl :: ExecSearchReplace ( )
{
  ODE_SearchReplace *sr        = ODEContext(this)->GetCurSearchReplace();
  char              *find_next = "Y";


  find_next = SearchReplace(sr,ctx_init)  ||
              SearchReplace(sr,ctx_start) ||
              SearchReplace(sr,ctx_code)  ||
              SearchReplace(sr,ctx_error) ||
              SearchReplace(sr,ctx_term      ) ? "N" : "Y";

  SetResult(find_next);
  return(NO);
}

/******************************************************************************/
/**
\brief  ExecuteFunction - 


\return  - 

\param  fname - 
\param  chk_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical cODCFunctionImpl :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("Changed",ALINK(this,cODCFunctionImpl,Changed)),
                           cfte("ExecSearchReplace",ALINK(this,cODCFunctionImpl,ExecSearchReplace)),
                           cfte("GotoLine",ALINK(this,cODCFunctionImpl,GotoLine)),
                           cfte("InputHelp",ALINK(this,cODCFunctionImpl,InputHelp)),
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
    term = cSDBResource_Base::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GotoLine - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GotoLine"

logical cODCFunctionImpl :: GotoLine ( )
{
  int32        line    = 0;
  char        *parm1   = Parm(1);
  char        *area    = NULL;
  CTX_Control *context = NULL;
  logical      term    = NO;

BEGINSEQ
  if ( !parm1 )                                      ERROR
  line = strtol(parm1,NULL,10);
  if ( !(area = Parm(2)) )                           ERROR

  if ( !strcmp(area,"init") )
  {	
    area = "init_start.init";
    SwitchInitStart(2);
  }
  else if ( !strcmp(area,"start") )
  {
    area = "init_start.start";
    SwitchInitStart(1);
  }
    
  if ( !(context = GetFieldContext(area)) )          ERROR
  
  context->SetFocus();  
  context->SetPosition(DPoint(1,line));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InputHelp - 


\return term - 
-------------------------------------------------------------------------------
\brief  i00 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputHelp"

logical cODCFunctionImpl :: InputHelp ( )
{
  char        *parm1 = Parm(1);
  return ( InputHelp(parm1 && (*parm1 == 'Y' || *parm1 == 'y') ? YES : NO) );

}

/******************************************************************************/
/**
\brief  i01 - 


\param  enable_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InputHelp"

logical cODCFunctionImpl :: InputHelp (logical enable_opt )
{

  ctx_init->EnableInputHelp(enable_opt);
  ctx_start->EnableInputHelp(enable_opt);
  ctx_code->EnableInputHelp(enable_opt);
  ctx_error->EnableInputHelp(enable_opt);
  ctx_term->EnableInputHelp(enable_opt);

  return(NO);
}

/******************************************************************************/
/**
\brief  SearchReplace - 


\return term - 

\param  ode_search_replace - 
\param  context - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SearchReplace"

logical cODCFunctionImpl :: SearchReplace (ODE_SearchReplace *ode_search_replace, CTX_Control *context )
{
  char              *search_string  = ode_search_replace->GetSearchString();
  char              *replace_string = ode_search_replace->GetReplaceString();
  PropertyHandle    *pi             = context ? context->GetPropertyHandle() : NULL;
  std::string        data(pi->GetString());
  std::string        substring;
  VECTOR(intPair)    pos_vec;
  DPoint             old_pos;
  intPair            start;
  intPair            end;
  int                switch_init_start = 0;
  int                offset            = 0;
  logical            term              = NO;
BEGINSEQ
if ( !ode_search_replace )                           ERROR
    
if ( !context || !search_string || !*search_string )
                                                     ERROR

if ( ode_search_replace->GetReplace() && ode_search_replace->GetReplaceAll() )
{
  RegExp::ReplaceExpression(search_string, replace_string, data, YES, ode_search_replace->GetCaseSensitive());
  LEAVESEQ
}

if ( context == ctx_init )
  switch_init_start = 2;  // switch to init tab 
if ( context == ctx_start )
  switch_init_start = 1;  // switch to start tab
  
pos_vec = RegExp::SearchExpression(search_string,data,NO,ode_search_replace->GetCaseSensitive());
old_pos = context->GetPosition();

for ( VECTOR(intPair)::iterator  it = pos_vec.begin(); it != pos_vec.end(); it++ )
{
  start = RegExp::TextPositionToPoint(data,offset + it->first);
  end   = RegExp::TextPositionToPoint(data,offset + it->first + it->second);

  if ( switch_init_start )
    SwitchInitStart(switch_init_start);
    
  context->SetSelection(DPoint(start.second,start.first),
                        DPoint(end.second,end.first));

  if ( ode_search_replace->GetReplace() )
  {
    if ( !ode_search_replace->GetReplaceAll() )
      if ( !GetDecisionOk(15) )                     ERROR

    substring = data.substr(it->first, it->second);
    RegExp::ReplaceExpression(search_string, replace_string, substring, YES, ode_search_replace->GetCaseSensitive());
    data.replace(it->first, it->second, substring);
    offset += it->second - substring.length();
  }
  else
    if ( !GetDecisionOk(15) )                       ERROR
}

context->SetSelection(old_pos,old_pos);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SwitchInitStart - 


\return term - 

\param  display_level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SwitchInitStart"

logical cODCFunctionImpl :: SwitchInitStart (int32 display_level )
{
  CTX_Control *init_start = GetFieldContext("init_start");
  logical      term       = NO;
BEGINSEQ
  if ( !init_start )                                 ERROR

  init_start->SetDisplayLevel(display_level);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cODCFunctionImpl - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cODCFunctionImpl"

     cODCFunctionImpl :: cODCFunctionImpl ( )
                     : cSDBResource_Base (),
  ctx_init(NULL),
  ctx_start(NULL),
  ctx_code(NULL),
  ctx_error(NULL),
  ctx_term(NULL)
{



}

/******************************************************************************/
/**
\brief  ~cODCFunctionImpl - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cODCFunctionImpl"

     cODCFunctionImpl :: ~cODCFunctionImpl ( )
{



}


