/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pKlasseditor

\brief    


\date     $Date: 2006/06/16 18:08:04,01 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pKlasseditor_HPP
#define   pKlasseditor_HPP

class     pKlasseditor;

#include  <spODE.hpp>
class  pKlasseditor :public pODE
{

public     :
public     :                                        int32 Create (CTX_Project **ctx_prj_ptrp );
public     :                                        logical CreateCInterface ( );
public     :                                        logical CreateClientServerInterface ( );
public     :                                        logical CreateICEInterface ( );
public     :                                        logical CreateServerClientInterface ( );
public     :                                        logical CreateUSERContext ( );
public     : virtual                                int8 DoAfterOpen ( );
public     :                                        logical DoForProject (char *expression, char *string );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GenerateAllIncludes ( );
public     :                                        logical GenerateAllSources ( );
public     :                                        logical GenerateCompileBatch (char *parm1=NULL );
public     :                                        logical GenerateCompileBatchForUNIX ( );
public     :                                        logical GenerateCompileBatchForWIN ( );
public     :                                        logical GenerateIncludes ( );
public     :                                        logical GenerateSources ( );
public     : virtual                                CTX_Control *GetImpClassContext ( );
public     : virtual                                char *GetOptionState (char *option_name );
public     :                                        logical InitProjectResources ( );
public     :                                        logical InitResourceDB ( );
public     :                                        logical Link ( );
public     :                                        logical ProjectSelection ( );
public     : virtual                                logical SetupProjectSelection (logical reset_opt );
public     :                                             pKlasseditor ( );
public     : virtual                                     ~pKlasseditor ( );
};

#endif
