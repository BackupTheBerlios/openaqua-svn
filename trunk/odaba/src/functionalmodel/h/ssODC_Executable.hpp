/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel - 
\class    sODC_Executable

\brief    


\date     $Date: 2006/06/04 10:53:15,20 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sODC_Executable_HPP
#define   sODC_Executable_HPP

class     sODC_Executable;

#include  <sCTX_Structure.hpp>
class  sODC_Executable :public CTX_Structure
{

public     :
public     :                                        int32 Create (CTX_Structure **CTX_Structure_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GetCompileCommand ( );
public     :                                        logical GetLinkCommand ( );
public     :                                        logical GetProjectPath ( );
public     :                                        logical SetCompileState ( );
public     :                                        logical SetModified ( );
public     :                                        logical SetupModLevel ( );
public     :                                             sODC_Executable ( );
public     : virtual                                     ~sODC_Executable ( );
};

#endif
