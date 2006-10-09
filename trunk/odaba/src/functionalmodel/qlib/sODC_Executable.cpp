/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    sODC_Executable

\brief    


\date     $Date: 2006/06/12 08:45:42,45 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sODC_Executable"

#include  <pfmodel.h>
#include  <spc_ODC_Executable.hpp>
#include  <spc_ODC_ImpClass.hpp>
#include  <ssODC_Executable.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  CTX_Structure_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sODC_Executable :: Create (CTX_Structure **CTX_Structure_ptrp )
{

  *CTX_Structure_ptrp = new sODC_Executable();
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

logical sODC_Executable :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("GetCompileCommand",ALINK(this,sODC_Executable,GetCompileCommand)),
                           cfte("GetLinkCommand",ALINK(this,sODC_Executable,GetLinkCommand)),
                           cfte("GetProjectPath",ALINK(this,sODC_Executable,GetProjectPath)),
                           cfte("SetCompileState",ALINK(this,sODC_Executable,SetCompileState)),
                           cfte("SetModified",ALINK(this,sODC_Executable,SetModified)),
                           cfte("SetupModLevel",ALINK(this,sODC_Executable,SetupModLevel)),
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
\brief  GetCompileCommand - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCompileCommand"

logical sODC_Executable :: GetCompileCommand ( )
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
    
  pc_ODC_Executable    main_pc(ph);
  SetResult(main_pc.GetCompileCommand(nstring));

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

logical sODC_Executable :: GetLinkCommand ( )
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
    
  pc_ODC_Executable    main_pc(ph);
  SetResult(main_pc.GetLinkCommand(nstring));

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

logical sODC_Executable :: GetProjectPath ( )
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
    
  pc_ODC_Executable    main_pc(ph);
  SetResult(main_pc.GetProjectPath(nstring,Parm(1)));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetCompileState - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCompileState"

logical sODC_Executable :: SetCompileState ( )
{
  PropertyHandle   *ph     = GetPropertyHandle();
  logical           term   = NO;
BEGINSEQ
  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR

  pc_ODC_Executable    main_pc(ph);
  main_pc.SetCompileState(Parm(1));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetModified - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetModified"

logical sODC_Executable :: SetModified ( )
{
  PropertyHandle   *ph      = GetPropertyHandle();
  char             *parm    = NULL;
  logical           genincl = YES;
  logical           term    = NO;
BEGINSEQ
  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR

  if ( parm = Parm(2) )
    if ( *parm == 'N' )
      genincl = NO;
      
  pc_ODC_Executable    main_pc(ph);
  main_pc.SetModified(Parm(1),genincl);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetupModLevel - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetupModLevel"

logical sODC_Executable :: SetupModLevel ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  pc_ODC_Executable    main_pc(ph);
  term = main_pc.ResModLevel();
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sODC_Executable - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sODC_Executable"

     sODC_Executable :: sODC_Executable ( )
                     : CTX_Structure()
{



}

/******************************************************************************/
/**
\brief  ~sODC_Executable - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sODC_Executable"

     sODC_Executable :: ~sODC_Executable ( )
{



}


