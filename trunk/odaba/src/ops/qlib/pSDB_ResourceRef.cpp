/********************************* Class Source Code ***************************/
/**
\package  OPS
\class    pSDB_ResourceRef



\date     $Date: 2006/05/23 15:30:22,68 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "pSDB_ResourceRef"

#include  <pops7.h>
#include  <sCTX_Property.hpp>
#include  <scfte.hpp>
#include  <spSDB_ResourceRef.hpp>


/******************************************************************************/
/**
\brief  Create

\return rc

\param  propctx_ptrp
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Create"

int32 pSDB_ResourceRef :: Create (CTX_Property **propctx_ptrp )
{

  *propctx_ptrp = new pSDB_ResourceRef();
  return(NO);

}

/******************************************************************************/
/**
\brief  ExecuteFunction

\return term

\param  fname
\param  chk_opt
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ExecuteFunction"

logical pSDB_ResourceRef :: ExecuteFunction (char *fname, logical chk_opt )
{
  char     actname[ID_SIZE];
  cfte    *cfteptr;
  logical  term      = NO;
BEGINSEQ
  static cfte acttbl[] = { 
                           cfte("WriteContextFiles",ALINK(this,pSDB_ResourceRef,WriteContextFiles)),
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
    term = CTX_Property::ExecuteFunction(fname,chk_opt);
  
  if ( term && !chk_opt )
    DisplayMessage();
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  WriteContextFiles

\return term
-------------------------------------------------------------------------------
\brief  i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteContextFiles"

logical pSDB_ResourceRef :: WriteContextFiles ( )
{
  char         *project = NULL;
  char         *path    = NULL;
  char         *string;
  logical       term    = NO;
BEGINSEQ
  if ( !(string = Parm(1)) )
    string = GetSysVariable("PROJECT_NAME");
  if ( !string || !*string )                         CTXERR(99)
    
  project = strdup(string);
      
  if ( !(string = Parm(2)) )
    string = GetSysVariable("PROJECT_INCLUDE_PATH");
  if ( !string || !*string )                         CTXERR(99)
  if ( !IsDirectory(string) )                        CTXERR(99)
    
  path = strdup(string);
  
  if ( WriteContextFiles(project,path) )             ERROR
      
  

  


RECOVER
  term = YES;
ENDSEQ
  if ( project )
    free(project);
  if ( path )
    free(path);
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  project
\param  path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteContextFiles"

logical pSDB_ResourceRef :: WriteContextFiles (char *project, char *path )
{
  PropertyHandle  *prophdl       = GetPropertyHandle();
  PropertyHandle  *resid         = prophdl->GPH("__AUTOIDENT");
  PropertyHandle  *type_ref      = prophdl->GPH("type_ref");
  PropertyHandle  *context_class = prophdl->GPH("context_class");
  PropertyHandle  *cc_sys_ident  = context_class->GPH("sys_ident");
  PropertyHandle  *cc_smceclas   = context_class->GPH("smceclas");
  PropertyHandle  *cls_module    = NULL;
  char             cpath[512];
  char             filarea[128];
  int32            indx0         = 0;
  FILE            *file_incl     = NULL;
  FILE            *file_flnk     = NULL;
  logical          term          = NO;
BEGINSEQ
  strcat(strcpy(cpath,path),"/iCtxIncl.h");
  CTXSETEV1(cpath,0)
  if ( !(file_incl = fopen(cpath,"wb")) )              CTXERR(1)

  strcat(strcpy(cpath,path),"/iCtxClasses.h");
  CTXSETEV1(cpath,0)
  if ( !(file_flnk = fopen(cpath,"wb")) )              CTXERR(1)

  CTXSETEV1(strcat(strcpy(cpath,path),"/iContext"),0)
  
  prophdl->ToTop();
  while ( prophdl->Get(indx0++) )
    if ( type_ref->GetCount() > 0                              && 
         context_class->Get(FIRST_INSTANCE)                    && 
         cc_smceclas->Get(FIRST_INSTANCE)                      &&
         !strcmp(cc_smceclas->GetCurrentType(),"ODC_ImpClass") &&
         (cls_module = cc_smceclas->GPH("module"))             && 
         cls_module->Get(FIRST_INSTANCE)                       &&
         !strcmp(cls_module->GPH("sys_ident")->GetString(),project) )
    {
      strcat(strcat(strcpy(filarea,"#include  <s"),cc_sys_ident->GetString()),".hpp>\r\n");
      if ( !fwrite(filarea,(unsigned int)strlen(filarea),1,file_incl) ) 
                                                     CTXERR(1)
      strcat(strcat(strcat(strcat(strcpy(filarea,"ctxe("),
                           resid->GetString()),",SLINK("),
                           cc_sys_ident->GetString()),",Create)),\r\n");
      if ( !fwrite(filarea,(unsigned int)strlen(filarea),1,file_flnk) ) 
                                                     CTXERR(1)
    }

RECOVER
  term = YES;
ENDSEQ
  if ( file_incl )
    fclose(file_incl);
  if ( file_flnk )
    fclose(file_flnk);
  return(term);
}

/******************************************************************************/
/**
\brief  pSDB_ResourceRef


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "pSDB_ResourceRef"

     pSDB_ResourceRef :: pSDB_ResourceRef ( )
                     : CTX_Property ()
{
}

/******************************************************************************/
/**
\brief  ~pSDB_ResourceRef


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~pSDB_ResourceRef"

     pSDB_ResourceRef :: ~pSDB_ResourceRef ( )
{
}


