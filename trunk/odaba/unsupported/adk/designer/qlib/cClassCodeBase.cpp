/********************************* Class Source Code ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassCodeBase

\brief    Base class for all code edit controls


\date     $Date: 2006/06/01 16:40:12,65 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "cClassCodeBase"

#include  <stdinc.h>
#include  <pdesign.h>
#include  <igvts.h>
#ifndef   VECTOR_std_string_HPP
#define   VECTOR_std_string_HPP
#include  <sVECTOR.h>
#endif
#include  <scClassCodeBase.hpp>


/******************************************************************************/
/**
\brief  ActivateClassInputHelp

\return 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ActivateClassInputHelp"

logical cClassCodeBase :: ActivateClassInputHelp ( )
{
  pODE                   *ode_ctx = ODEContext(this);
  VECTOR(std_string)      as_project;
  VECTOR(std_string)      as_myclass;
  VECTOR(std_string)      as_class;
  VECTOR(std_string)      as_impls;
  CTX_Control            *ctxptr = NULL;
  logical                 term   = NO;
BEGINSEQ
  if ( UserState1() )                               LEAVESEQ
  SetUserState1(YES);

  as_myclass.push_back("");
  if ( ctxptr = AddInputHelp(NULL,"ClassMemberInputHelp","input_help",as_myclass) ) // -> cClassInputHelp
    ctxptr->ExecuteFunction("SetAsMyClass");
  
  as_class.push_back(".");
  as_class.push_back("->");
  as_class.push_back("::");
  AddInputHelp(NULL,"ClassMemberInputHelp","input_help",as_class);  // -> cClassInputHelp


  as_project.push_back("new ");
  AddInputHelp(NULL,"ClassInputHelp","input_help",as_project); // -> cProjectInputHelp
  
  as_impls.push_back("(");
  AddInputHelp(NULL,"ClassFunctImpInputHelp","input_help",as_impls);  // -> cFunctionInputHelp

ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Create

\return rc

\param  ctx_ctl_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 cClassCodeBase :: Create (CTX_Control **ctx_ctl_ptrp )
{

  *ctx_ctl_ptrp = new cClassCodeBase();
  return(NO);

}

/******************************************************************************/
/**
\brief  DeleteLine

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteLine"

logical cClassCodeBase :: DeleteLine ( )
{
  DPoint             dpos           = GetPosition();
  char              *code           = GetData()->GetString();
  int                curline_start  = 0;
  int                nextline_start = 0;
  logical            term           = NO;
BEGINSEQ
  if ( ProvideData() )                               ERROR
   
  curline_start  = matches[dpos.Y - 1].first;
  nextline_start = matches[dpos.Y].first;
  
  if ( matches.size() == dpos.Y )
    code[curline_start] = 0;
  else
    strcpy(code+curline_start,code+nextline_start);
  
  SetData(code);
  dpos.X = 0;
  SetPosition(dpos);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  DoAfterHandleActivated

\return executed

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DoAfterHandleActivated"

int8 cClassCodeBase :: DoAfterHandleActivated ( )
{

  ActivateClassInputHelp();
  SetZoomOutControl(GetHighContext("edit_class_function"),NO);
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

logical cClassCodeBase :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("DeleteLine",ALINK(this,cClassCodeBase,DeleteLine)),
                           cfte("FindBalancedPar",ALINK(this,cClassCodeBase,FindBalancedPar)),
                           cfte("GetClassName",ALINK(this,cClassCodeBase,GetClassName)),
                           cfte("GetCurrentOffset",ALINK(this,cClassCodeBase,GetCurrentOffset)),
                           cfte("InsertBlock",ALINK(this,cClassCodeBase,InsertBlock)),
                           cfte("InsertExpression",ALINK(this,cClassCodeBase,InsertExpression)),
                           cfte("InsertSwitch",ALINK(this,cClassCodeBase,InsertSwitch)),
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
    term = cNotifyHighContext::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FindBalancedPar

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindBalancedPar"

logical cClassCodeBase :: FindBalancedPar ( )
{
  DPoint             dpos      = GetPosition();
  char              *code      = GetData()->GetString();
  char              *start_pos = NULL;
  char              *par_pos   = NULL;
  logical            term      = NO;
BEGINSEQ
  if ( ProvideData() )                               ERROR

  start_pos = code + offset;
  
  if ( par_pos = gvtsfbp(start_pos,UNDEF) )
  {
    while ( code + matches[dpos.Y - 1].first + matches[dpos.Y - 1].second < par_pos )
      dpos.Y += 1;
  }
  else if ( par_pos = gvtsfbpb(start_pos,offset) )
  {
    while ( code + matches[dpos.Y - 1].first > par_pos )
      dpos.Y -= 1;
  }
  else                                               ERROR

  dpos.X = (par_pos - (code + matches[dpos.Y - 1].first)) + 1;
  SetPosition(dpos);

RECOVER
//  Beep();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetClassName

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetClassName"

logical cClassCodeBase :: GetClassName ( )
{
  PropertyHandle   *prophdl = GetPropertyHandle();
  logical           term    = NO;
BEGINSEQ
  if ( !(prophdl = prophdl->GetParentProperty()->GetParentProperty()->GetParentProperty()) )
                                                     ERROR
  SetResult(prophdl->GPH("sys_ident")->GetString());
RECOVER
  SetResult("");
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetCurrentOffset

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentOffset"

logical cClassCodeBase :: GetCurrentOffset ( )
{
  logical                 term = NO;
BEGINSEQ
  if ( ProvideData() )                               ERROR 
  SetResult(PropertyHandle(offset).GetString());
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InsertBlock

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertBlock"

logical cClassCodeBase :: InsertBlock ( )
{
  DPoint             dpos      = GetPosition();
  std::string        idata("");
  logical            term      = NO;
BEGINSEQ
  if ( ProvideData() )                               ERROR 

  idata.append("{\n");
  idata.append(dpos.X-1+2,' ');
  idata.append("\n");
  idata.append(dpos.X-1,' ');
  idata.append("}\n");
  
  data.insert(offset,idata);
  SetData((char *)data.c_str());
  
  dpos.Y++;
  dpos.X+=2;
  SetPosition(dpos);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InsertExpression

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertExpression"

logical cClassCodeBase :: InsertExpression ( )
{
  DPoint        dpos     = GetPosition();
  int           line_end = 0;
  std::string   idata("");
  logical       term     = NO;
BEGINSEQ
  if ( ProvideData() )                               ERROR 

  line_end = matches[dpos.Y - 1].second;

  idata.append("if (  )");
  if ( dpos.X < line_end )
  {
    idata.append("\n");
    idata.append(dpos.X+2,' ');
  }

  data.insert(offset,idata);
  SetData((char *)data.c_str());
  
  dpos.X+=5;
  SetPosition(dpos);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InsertSwitch

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertSwitch"

logical cClassCodeBase :: InsertSwitch ( )
{
  DPoint        dpos     = GetPosition();
  int           line_end = 0;
  std::string   idata("");
  logical       term     = NO;
BEGINSEQ
  if ( ProvideData() )                               ERROR 

  idata.append("switch (  )\n");
  idata.append(dpos.X-1,' ');
  idata.append("{\n");
  idata.append(dpos.X-1+2,' ');
  idata.append("case    : \n");
  idata.append(dpos.X-1+12,' ');
  idata.append("break;\n");
  idata.append(dpos.X-1+2,' ');
  idata.append("default : ;\n");
  idata.append(dpos.X-1,' ');
  idata.append("}\n");
  
  data.insert(offset,idata);
  SetData((char *)data.c_str());
  
  dpos.X+=9;
  SetPosition(dpos);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideData

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideData"

logical cClassCodeBase :: ProvideData ( )
{
  DPoint      dpos    = GetPosition();
  char       *datarea = GetData()->GetArea();
  logical     term    = NO;

BEGINSEQ
  if ( !datarea )
    datarea = "";
    
  data    = datarea;
  matches = lines.Search(data);
  offset  = UNDEF;
  
  if ( matches.size() < dpos.Y )                       ERROR

  offset  = matches[dpos.Y - 1].first + dpos.X - 1;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  cClassCodeBase


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "cClassCodeBase"

     cClassCodeBase :: cClassCodeBase ( )
                     : cNotifyHighContext (),
  lines("[^\n]*(\n|$)"),
  data(),
  matches(),
  offset(0)
{
}

/******************************************************************************/
/**
\brief  ~cClassCodeBase


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~cClassCodeBase"

     cClassCodeBase :: ~cClassCodeBase ( )
{



}


