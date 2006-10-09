/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/04/07|16:46:42,89}|(REF)
\class    DLL_Handle

\brief    


\date     $Date: 2006/04/11 11:59:16,90 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DLL_Handle"

#include  <popa7.h>
#include  <coctp.h>
#include  <iContext.h>
#include  <win32f.h>
#ifndef   GSRT_HInstEntry_HPP
#define   GSRT_HInstEntry_HPP
#include  <sHInstEntry.hpp>
#include  <sGSRT.h>
#endif
#ifndef   DLL_RootBaseEntry_HPP
#define   DLL_RootBaseEntry_HPP
#include  <sRootBaseEntry.hpp>
#include  <sDLL.h>
#endif
#include  <sACNode.hpp>
#include  <sACObject.hpp>
#include  <sCTX_DataBase.hpp>
#include  <sCTX_Object.hpp>
#include  <sCTX_Property.hpp>
#include  <sCTX_Structure.hpp>
#include  <sDBExtend.hpp>
#include  <sDBStructDef.hpp>
#include  <sDictionary.hpp>
#include  <sError.hpp>
#include  <sRootBaseEntry.hpp>
#include  <seb_RootBase.hpp>
#include  <sDLL_Handle.hpp>


/******************************************************************************/
/**
\brief  CreateBaseCtx - 


\return basectx

\param  dllname - 
\param  proc_name
\param  resid - 
\param  ctxtype - Context type
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateBaseCtx"

CTX_Base *DLL_Handle :: CreateBaseCtx (char *dllname, char *proc_name, int32 resid, CTX_Types ctxtype )
{
  CTX_Base           *basectx = NULL;
  HINSTANCE           hinstance;
  typedef             CTX_Base *(*CreateContextPtr)(int32);
  CreateContextPtr    pfunct;
BEGINSEQ
  if ( !dllname )                                    LEAVESEQ
    
  if ( (hinstance = GetHInstance(dllname)) &&      
       ((pfunct = (CreateContextPtr)GetProcAddress(hinstance,proc_name))  || 
        (pfunct = (CreateContextPtr)GetProcAddress(hinstance,"CreateContext")))  )
    basectx = pfunct(resid);

  if ( !basectx )
  {
    if ( !(basectx = SysCreateContext(resid)) )      ERROR
    if ( basectx->GetContextType() != ctxtype )
    {
      delete basectx;
      basectx = NULL;
      SDBSET(99)
    }
  }
RECOVER
  basectx = NULL;
ENDSEQ
  return(basectx);
}

/******************************************************************************/
/**
\brief  CreateDBCtx - 


\return dbctx

\param  dllname - 
\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateDBCtx"

CTX_DataBase *DLL_Handle :: CreateDBCtx (char *dllname, int32 resid )
{
  CTX_DataBase       *dbctx = NULL;
  CTX_Base           *basectx;
  if ( basectx = CreateBaseCtx(dllname,"CreateDBCtx",resid,CTXT_Database))
    dbctx = (CTX_DataBase *)basectx;
  else
    dbctx = new CTX_DataBase();
  return(dbctx);
}

/******************************************************************************/
/**
\brief  CreateNode - 


\return acnodeptr - 

\param  dllname - 
\param  obhandle - Database Object handle
\param  dbext_ptr - 
\param  accopt - Access mode
\param  netopt - Multi-user access
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateNode"

ACNode *DLL_Handle :: CreateNode (char *dllname, ACObject *obhandle, DBExtend *dbext_ptr, PIACC accopt, logical netopt )
{
  HINSTANCE     hinstance;
  ACNode       *acnodeptr = NULL;
  typedef       ACNode  *(*CreateNodePtr)(ACObject *,DBExtend *,PIACC,logical);
  CreateNodePtr pfunct;
BEGINSEQ
  if ( !(hinstance = GetHInstance(dllname)) )        ERROR
  
  if ( !(pfunct = (CreateNodePtr)GetProcAddress(hinstance,"CreateNode")) )
                                                     SDBERR(99)
  if ( !(acnodeptr = pfunct(obhandle,dbext_ptr,accopt,netopt)) )
                                                     ERROR

RECOVER
  acnodeptr = NULL;
ENDSEQ
  return(acnodeptr);
}

/******************************************************************************/
/**
\brief  CreateObjCtx

\return objctx

\param  dllname - 
\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateObjCtx"

CTX_Object *DLL_Handle :: CreateObjCtx (char *dllname, int32 resid )
{
  CTX_Object         *objctx = NULL;
  CTX_Base           *basectx;
  if ( basectx = CreateBaseCtx(dllname,"CreateObjCtx",resid,CTXT_Object))
    objctx = (CTX_Object *)basectx;
  else 
    objctx = new CTX_Object();

  return(objctx);
}

/******************************************************************************/
/**
\brief  CreatePropCtx - 


\return propctx - 

\param  dllname - 
\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreatePropCtx"

CTX_Property *DLL_Handle :: CreatePropCtx (char *dllname, int32 resid )
{
  CTX_Property    *propctx = NULL;
  CTX_Base        *basectx;
  if ( basectx = CreateBaseCtx(dllname,"CreatePropCtx",resid,CTXT_Property))
    propctx = (CTX_Property *)basectx;
  else 
    propctx = new CTX_Property();

  return(propctx);
}

/******************************************************************************/
/**
\brief  CreateStrCtx - 


\return strctx - Structure Context

\param  dllname - 
\param  resid - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStrCtx"

CTX_Structure *DLL_Handle :: CreateStrCtx (char *dllname, int32 resid )
{
  CTX_Structure   *strctx = NULL;
  CTX_Base        *basectx;
  if ( basectx = CreateBaseCtx(dllname,"CreateStrCtx",resid,CTXT_Structure))
    strctx = (CTX_Structure *)basectx;
  else
    strctx = new CTX_Structure();

  return(strctx);
}

/******************************************************************************/
/**
\brief  CreateStructDef - 


\return strdefptr - 

\param  dllname - 
\param  dictptr - Dictionary handle
\param  extnames - Extent name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateStructDef"

DBStructDef *DLL_Handle :: CreateStructDef (char *dllname, Dictionary *dictptr, char *extnames )
{
  HINSTANCE          hinstance;
  DBStructDef       *strdefptr = NULL;
  typedef            DBStructDef  *(*CreateStructDefPtr)(Dictionary *,char *);
  CreateStructDefPtr pfunct;
BEGINSEQ
  if ( !(hinstance = GetHInstance(dllname)) )        ERROR
  
  if ( !(pfunct = (CreateStructDefPtr)GetProcAddress(hinstance,"CreateStructDef")) )
                                                     SDBERR(99)
  if ( !(strdefptr = pfunct(dictptr,extnames)) )     ERROR

RECOVER
  strdefptr = NULL;
ENDSEQ
  return(strdefptr);
}

/******************************************************************************/
/**
\brief  DLL_Handle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DLL_Handle"

                        DLL_Handle :: DLL_Handle ( )
                     : hinst_list(NULL)
{

BEGINSEQ
  if ( !(hinst_list = new GSRT(HInstEntry)(10,sizeof(HInstEntry),256,1,'C',YES)) )
                                                     SDBERR(95)
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Delete


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

void __cdecl DLL_Handle :: Delete ( )
{
extern   DLL_Handle  *dllhandle;
  delete dllhandle;  // wird im Destruktor genullt

}

/******************************************************************************/
/**
\brief  GetFunctionPtr - 


\return pfunct - 

\param  dllname - 
\param  fnames - 
\param  check_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFunctionPtr"

void *DLL_Handle :: GetFunctionPtr (char *dllname, char *fnames, logical check_opt )
{
  char                    name[ID_SIZE+1];       
  char                    lnames[65];
  HINSTANCE               hinstance;
  void                   *pfunct = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !(hinstance = GetHInstance(dllname,check_opt)) )ERROR

  gvtxbts(name,fnames,ID_SIZE);
  if ( !(pfunct = (void *)GetProcAddress(hinstance,name)) )
                                                     ERROR

RECOVER

ENDSEQ
  return(pfunct);
}

/******************************************************************************/
/**
\brief  GetHInstance - 


\return hinst_ptr - 

\param  dllname - 
\param  check_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetHInstance"

HINSTANCE DLL_Handle :: GetHInstance (char *dllname, logical check_opt )
{
  char          name[256];
  int16         indx = 0;

BEGINSEQ
  if ( !dllname )                                    ERROR
 
  hinst_list->Lock();
  if ( !(indx = hinst_list->FindEntry(gvtxstb(name,dllname,256))) )
  {
    HInstEntry   hinstance(dllname,check_opt);
// nur erforderlich, wenn laden der DLL immer wieder versucht werden soll
//    if ( !hinstance.get_hinstance() )               ERROR
   indx = hinst_list->AddEntry(&hinstance);
  }
  hinst_list->Unlock();

RECOVER

ENDSEQ
  return(indx ? hinst_list->GetEntry(indx)->get_hinstance() : NULL);

}

/******************************************************************************/
/**
\brief  ~DLL_Handle - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DLL_Handle"

                        DLL_Handle :: ~DLL_Handle ( )
{
extern   DLL_Handle  *dllhandle;
  int16               indx = 0;
  HInstEntry         *he;
  dllhandle = NULL;
  
  while ( he = hinst_list->GetEntry(++indx) )
    if ( he->get_hinstance() )
#ifdef __unix__    
      dlclose(he->get_hinstance());
#else
      FreeLibrary(he->get_hinstance());
#endif    
  delete hinst_list;

}


