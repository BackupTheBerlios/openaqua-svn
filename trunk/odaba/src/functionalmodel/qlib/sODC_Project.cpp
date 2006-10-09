/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    sODC_Project

\brief    


\date     $Date: 2006/06/04 11:28:48,31 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sODC_Project"

#include  <pfmodel.h>
#include  <spc_ODC_Project.hpp>
#include  <ssODC_Project.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  CTX_Structure_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sODC_Project :: Create (CTX_Structure **CTX_Structure_ptrp )
{

  *CTX_Structure_ptrp = new sODC_Project();
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

logical sODC_Project :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("GenerateCompile",ALINK(this,sODC_Project,GenerateCompile)),
                           cfte("GetCompileCommand",ALINK(this,sODC_Project,GetCompileCommand)),
                           cfte("GetLinkCommand",ALINK(this,sODC_Project,GetLinkCommand)),
                           cfte("GetProjectPath",ALINK(this,sODC_Project,GetProjectPath)),
                           cfte("InitializeExternalResources",ALINK(this,sODC_Project,InitializeExternalResources)),
                           cfte("SetupReferences",ALINK(this,sODC_Project,SetupReferences)),
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
    term = CTX_Structure::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GenerateCompile - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GenerateCompile"

logical sODC_Project :: GenerateCompile ( )
{
  pc_ODC_Project    proj_pc(GetPropertyHandle());
  NString           output;
  char             *parm          = NULL;
  CompileStates     compreq       = CPS_undefined;
  logical           nocomp_ignore = NO;
  logical           term          = NO;
BEGINSEQ
  if ( !proj_pc.IsClient() )                        LEAVESEQ
  if ( !proj_pc.IsPositioned() )                    ERROR
    
//  if ( parm = Parm(2) )  
//    compreq =

  if ( (parm = Parm(3)) && *parm == 'Y' )  
    nocomp_ignore = YES;
  
  if ( (parm = Parm(1)) && *parm == 'U' )
    term = proj_pc.CreateCompAllUnix(compreq,nocomp_ignore,&output);
  else
    term = proj_pc.CreateCompAllWin(compreq,nocomp_ignore,&output);

RECOVER
  term = YES;
ENDSEQ
  proj_pc.SetActionResult(output);
  return(term);
}

/******************************************************************************/
/**
\brief  GetCompileCommand - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCompileCommand"

logical sODC_Project :: GetCompileCommand ( )
{
  PropertyHandle   *ph      = GetPropertyHandle();
  NString           nstring;
  logical           term    = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ

  SetResult("");

  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  pc_ODC_Project    project_pc(ph);
  SetResult(project_pc.GetCompileCommand(nstring,Parm(1)));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetLinkCommand - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLinkCommand"

logical sODC_Project :: GetLinkCommand ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  NString           nstring;
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ

  SetResult("");

  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  pc_ODC_Project    project_pc(ph);
  SetResult(project_pc.GetLinkCommand(nstring,NO));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  GetProjectPath - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetProjectPath"

logical sODC_Project :: GetProjectPath ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  NString           nstring;
  logical           term = NO;
BEGINSEQ
  SetResult("");   
  
  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR

  pc_ODC_Project    project_pc(ph);
  SetResult(project_pc.GetProjectPath(nstring,Parm(1)));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  InitializeExternalResources - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitializeExternalResources"

logical sODC_Project :: InitializeExternalResources ( )
{
  PropertyHandle   *ph         = GetPropertyHandle();
  char             *folder_opt = Parm(1);
  NString           nstring;
  logical           term       = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ

  SetResult("");

  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  pc_ODC_Project    project_pc(ph);
  project_pc.InitializeExternalResources(&nstring,folder_opt && *folder_opt == 'Y' ? YES : NO);
  SetResult(nstring);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupReferences - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupReferences"

logical sODC_Project :: SetupReferences ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( ph->NoWrite() )                               ERROR
    
  pc_ODC_Project    project_pc(ph);
  project_pc.SetupReferences();

  ph->Save();                                        SDBCERR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sODC_Project - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sODC_Project"

     sODC_Project :: sODC_Project ( )
                     : CTX_Structure()
{



}

/******************************************************************************/
/**
\brief  ~sODC_Project - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sODC_Project"

     sODC_Project :: ~sODC_Project ( )
{



}


