/********************************* Class Source Code ***************************/
/**
\package  FunctionalModel - 
\class    sODC_ImpClass

\brief    


\date     $Date: 2006/06/04 11:28:54,20 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "sODC_ImpClass"

#include  <pfmodel.h>
#include  <sCTX_Structure.hpp>
#include  <spc_ODC_ImpClass.hpp>
#include  <ssODC_ImpClass.hpp>


/******************************************************************************/
/**
\brief  Create - 


\return rc - 

\param  CTX_Structure_ptrp - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 sODC_ImpClass :: Create (CTX_Structure **CTX_Structure_ptrp )
{

  *CTX_Structure_ptrp = new sODC_ImpClass();
  return(NO);


}

/******************************************************************************/
/**
\brief  DeleteExternalResources - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DeleteExternalResources"

logical sODC_ImpClass :: DeleteExternalResources ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsClient() )                             LEAVESEQ
  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  pc_ODC_ImpClass    class_pc(ph);
  term = class_pc.DeleteExternalResources();
RECOVER
  term = YES;
ENDSEQ
  return(term);
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

logical sODC_ImpClass :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("DeleteExternalResources",ALINK(this,sODC_ImpClass,DeleteExternalResources)),
                           cfte("GetCompileCommand",ALINK(this,sODC_ImpClass,GetCompileCommand)),
                           cfte("GetProjectPath",ALINK(this,sODC_ImpClass,GetProjectPath)),
                           cfte("HasActions",ALINK(this,sODC_ImpClass,HasActions)),
                           cfte("HasProperty",ALINK(this,sODC_ImpClass,HasProperty)),
                           cfte("PC_Class_Setup",ALINK(this,sODC_ImpClass,PC_Class_Setup)),
                           cfte("SetCompileState",ALINK(this,sODC_ImpClass,SetCompileState)),
                           cfte("SetIncludeState",ALINK(this,sODC_ImpClass,SetIncludeState)),
                           cfte("SetModified",ALINK(this,sODC_ImpClass,SetModified)),
                           cfte("SetupModLevel",ALINK(this,sODC_ImpClass,SetupModLevel)),
                           cfte("SetupReferences",ALINK(this,sODC_ImpClass,SetupReferences)),
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

logical sODC_ImpClass :: GetCompileCommand ( )
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
    
  pc_ODC_ImpClass    class_pc(ph);
  SetResult(class_pc.GetCompileCommand(nstring));

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

logical sODC_ImpClass :: GetProjectPath ( )
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
    
  pc_ODC_ImpClass    class_pc(ph);
  SetResult(class_pc.GetProjectPath(nstring,Parm(1)));

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  HasActions - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasActions"

logical sODC_ImpClass :: HasActions ( )
{
  PropertyHandle   *ph     = GetPropertyHandle();
  char             *result = "NO";
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ

  SetResult("");

  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  pc_ODC_ImpClass    class_pc(ph);
  if ( class_pc.HasActions() )
    result = "YES";
  
  SetResult(result);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  HasProperty - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "HasProperty"

logical sODC_ImpClass :: HasProperty ( )
{
  PropertyHandle   *ph     = GetPropertyHandle();
  char             *parm   = NULL;
  char             *result = "NO";
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ

  SetResult("");

  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  if ( !(parm = Parm(1)) )                           ERROR
    
  pc_ODC_ImpClass    class_pc(ph);
  if ( class_pc.HasProperty(parm) )
    result = "YES";
  
  SetResult(result);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PC_Class_Setup - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PC_Class_Setup"

logical sODC_ImpClass :: PC_Class_Setup ( )
{
  PropertyHandle   *ph          = GetPropertyHandle();
  char             *scoped_name = Parm(1);
  logical           term        = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( !ph->IsPositioned() )                         ERROR
  if ( !scoped_name )                                ERROR

  PropertyHandle  sdb_structure(ph->GetDBHandle(),"SDB_Structure",PI_Read);
                                                     SDBCERR  
  if ( !sdb_structure.Get(TypeKey(ph->GetDBHandle(),scoped_name)) )
                                                     ERROR
  pc_ODC_ImpClass    class_pc(ph);
  class_pc.PC_Class_Setup(&sdb_structure);  

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

logical sODC_ImpClass :: SetCompileState ( )
{
  PropertyHandle   *ph     = GetPropertyHandle();
  logical           term   = NO;
BEGINSEQ
  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR

  pc_ODC_ImpClass    class_pc(ph);
  class_pc.SetCompileState(Parm(1));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetIncludeState - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetIncludeState"

logical sODC_ImpClass :: SetIncludeState ( )
{
  PropertyHandle   *ph      = GetPropertyHandle();
  char             *parm    = NULL;
  logical           genincl = YES;
  logical           term    = NO;
BEGINSEQ
  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR

  if ( parm = Parm(1) )
    if ( *parm == 'N' )
      genincl = NO;
      
  pc_ODC_ImpClass    class_pc(ph);
  class_pc.SetIncludeState(genincl);
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

logical sODC_ImpClass :: SetModified ( )
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
      
  pc_ODC_ImpClass    class_pc(ph);
  class_pc.SetModified(Parm(1),genincl);
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

logical sODC_ImpClass :: SetupModLevel ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( !ph->IsSelected() )                           ERROR
  if ( !ph->IsPositioned() )
    if ( !ph->Get().GetData() )                      ERROR
    
  pc_ODC_ImpClass    class_pc(ph);
  term = class_pc.ResModLevel();
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

logical sODC_ImpClass :: SetupReferences ( )
{
  PropertyHandle   *ph   = GetPropertyHandle();
  logical           term = NO;
BEGINSEQ
  if ( !ph->IsServer() )                             LEAVESEQ
  if ( ph->NoWrite() )                               ERROR
    
  pc_ODC_ImpClass    class_pc(ph);
  term = class_pc.SetupReferences();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  sODC_ImpClass - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "sODC_ImpClass"

     sODC_ImpClass :: sODC_ImpClass ( )
                     : CTX_Structure()
{



}

/******************************************************************************/
/**
\brief  ~sODC_ImpClass - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~sODC_ImpClass"

     sODC_ImpClass :: ~sODC_ImpClass ( )
{



}


