/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pStrukteditor

\brief    


\date     $Date: 2006/06/03 15:05:27,46 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pStrukteditor_HPP
#define   pStrukteditor_HPP

class     pStrukteditor;

#include  <spODE.hpp>
class  pStrukteditor :public pODE
{

public     :
public     :                                        int32 Create (CTX_Project **ctx_prj_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GenerateSQLDefinitions ( );
public     :                                             pStrukteditor ( );
public     : virtual                                     ~pStrukteditor ( );
};

#endif
