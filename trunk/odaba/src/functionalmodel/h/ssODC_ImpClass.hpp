/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    sODC_ImpClass



\date     $Date: 2006/05/03 22:19:46,12 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sODC_ImpClass_HPP
#define   sODC_ImpClass_HPP

class     sODC_ImpClass;

class     CTX_Structure;
class  sODC_ImpClass :public CTX_Structure
{

public     :
public     :                                        int32 Create (CTX_Structure **CTX_Structure_ptrp );
public     :                                        logical DeleteExternalResources ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetCompileCommand ( );
public     :                                        logical GetProjectPath ( );
public     :                                        logical HasActions ( );
public     :                                        logical HasProperty ( );
public     :                                        logical PC_Class_Setup ( );
public     :                                        logical SetCompileState ( );
public     :                                        logical SetIncludeState ( );
public     :                                        logical SetModified ( );
public     :                                        logical SetupModLevel ( );
public     :                                        logical SetupReferences ( );
public     :                                             sODC_ImpClass ( );
public     : virtual                                     ~sODC_ImpClass ( );
};

#endif
