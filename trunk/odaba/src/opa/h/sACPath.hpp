/********************************* Class Declaration ***************************/
/**
\package  OPA - 
\class    ACPath

\brief    


\date     $Date: 2006/07/19 16:31:34,95 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACPath_HPP
#define   ACPath_HPP

class     ACPath;

class     ACObject;
class     BNFData;
class     CTX_DBBase;
class     DBExtend;
class     DBFieldDef;
class     DBStructDef;
class     Dictionary;
class     LACObject;
class     OperEnvironment;
class     Operation;
class     node;
#include  <cPIACC.h>
#include  <sACOperation.hpp>
#include  <sACPath.hpp>
#include  <sLNode.hpp>
#include  <sNString.hpp>
#pragma pack(8)

class  ACPath :public ACOperation
{
protected  :         Operation                                   *operation;                                                 // 
protected  :         int64                                        parent_objid;                                              // 

public     :
                     Operation                                   *get_operation() { return(operation); }
                     int64                                        get_parent_objid() { return(parent_objid); }
public     :                                             ACPath (ACObject *obhandle, node *nodeptr, DBStructDef *structdef, OperEnvironment *operenv, PIACC accopt );
public     :                                             ACPath (ACObject *obhandle, node *nodeptr, char *proppath, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                             ACPath (ACObject *obhandle, node *nodeptr, BNFData *bnf_data, OperEnvironment *operenv, PIACC accopt, char *strnames_w=NULL );
public     :                                             ACPath (ACObject *obhandle, DBExtend *dbextdef, OperEnvironment *operenv, PIACC accopt );
public     :                                             ACPath (ACObject *obhandle, node *nodeptr, DBFieldDef *fielddef, OperEnvironment *operenv, PIACC accopt );
public     :                                             ACPath (ACPath &acpathref );
public     :                                        logical BuildResult ( );
public     : virtual                                logical Cancel (logical chknode=YES );
public     : virtual          OPAImpExp             PIACC ChangeMode (PIACC accopt, char chkopt=AUTO );
public     : virtual                                logical Check (logical autoini=NO, logical acccheck=YES );
public     : virtual                                node *CreateCopyNode ( );
public     : virtual          OPAImpExp             logical ExecPropCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual          OPAImpExp             logical ExecStrCtxFunc (char *fnames, char *w_parms=NULL );
public     : virtual                                logical Execute (ParmList *parmlist );
public     :                                        void *Get (int32 indx0, logical chknode=YES );
public     :                                        void *Get (char *skey, logical chknode=YES );
public     : virtual                                CTX_Property *GetContext ( );
public     :                                        node *GetResultNode ( );
public     :                                        logical InitExpression (char *exprstr );
public     :                                        logical InitOQLElements (DBStructDef *dbview_str );
public     :                                        logical InitOQLFrom (DBStructDef *dbview_str, NString &nstring );
public     :                                        logical InitOQLGroupBy (DBStructDef *dbview_str, NString &nstring );
public     :                                        logical InitResult ( );
public     :                                        logical Initialize (char *strnames_w=NULL );
public     :                                        logical Initialize (ACObject *obhandle );
public     :                                        logical Initialize (DBFieldDef *fielddef );
public     :                                        logical Open ( );
public     : virtual          OPAImpExp             int32 Position (int32 count, logical chknode=YES );
public     : virtual          OPAImpExp             void ResetInstance ( );
public     :                                        logical ResetResult ( );
public     :                                        logical Save (logical switchopt, logical overwrite=NO, logical chknode=YES );
public     :                                        void *SetupInstance ( );
public     : virtual          OPAImpExp             node *ValidateNode (logical crt_opt );
public     : virtual                                     ~ACPath ( );
};

#pragma pack()
#endif
