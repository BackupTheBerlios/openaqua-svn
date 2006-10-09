/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DLL_Handle

\brief    


\date     $Date: 2006/03/12 19:13:07,15 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DLL_Handle_HPP
#define   DLL_Handle_HPP

class     DLL_Handle;

#include  <sGSRT.h>
class     HInstEntry;
#include  <sDLL.h>
class     RootBaseEntry;
class     ACNode;
class     ACObject;
class     CTX_DataBase;
class     CTX_Object;
class     CTX_Property;
class     CTX_Structure;
class     DBExtend;
class     DBStructDef;
class     Dictionary;
class     RootBaseEntry;
class     eb_RootBase;
#include  <cPIACC.h>
#pragma pack(8)

class  DLL_Handle
{
protected  :         GSRT(HInstEntry)                            *hinst_list;                                                

public     :
                     GSRT(HInstEntry)                            *get_hinst_list() { return(hinst_list); }
public     :                                     CTX_Base *CreateBaseCtx (char *dllname, char *proc_name, int32 resid, CTX_Types ctxtype=CTXT_undefined );
public     :                                     CTX_DataBase *CreateDBCtx (char *dllname, int32 resid );
public     :                                     ACNode *CreateNode (char *dllname, ACObject *obhandle, DBExtend *dbext_ptr, PIACC accopt, logical netopt );
public     :                                     CTX_Object *CreateObjCtx (char *dllname, int32 resid );
public     :                                     CTX_Property *CreatePropCtx (char *dllname, int32 resid );
public     :                                     CTX_Structure *CreateStrCtx (char *dllname, int32 resid );
public     :                                     DBStructDef *CreateStructDef (char *dllname, Dictionary *dictptr, char *extnames );
public     :                                                             DLL_Handle ( );
public     : static                              void __cdecl Delete ( );
public     :         opa7ImpExp                  void *GetFunctionPtr (char *dllname, char *fnames, logical check_opt=NO );
public     :                                     HINSTANCE GetHInstance (char *dllname, logical check_opt=NO );
public     :                                                             ~DLL_Handle ( );
};

#pragma pack()
#endif
