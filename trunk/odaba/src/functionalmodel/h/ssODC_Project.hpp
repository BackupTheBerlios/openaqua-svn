/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel
\class    sODC_Project



\date     $Date: 2006/05/18 14:30:07,87 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sODC_Project_HPP
#define   sODC_Project_HPP

class     sODC_Project;

#include  <sCTX_Structure.hpp>
class  sODC_Project :public CTX_Structure
{

public     :
public     :                                        int32 Create (CTX_Structure **CTX_Structure_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GenerateCompile ( );
public     :                                        logical GetCompileCommand ( );
public     :                                        logical GetLinkCommand ( );
public     :                                        logical GetProjectPath ( );
public     :                                        logical InitializeExternalResources ( );
public     :                                        logical SetupReferences ( );
public     :                                             sODC_Project ( );
public     : virtual                                     ~sODC_Project ( );
};

#endif
