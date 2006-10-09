/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pDesigner

\brief    


\date     $Date: 2006/06/03 15:05:25,17 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pDesigner_HPP
#define   pDesigner_HPP

class     pDesigner;

#include  <spODE.hpp>
class  pDesigner :public pODE
{

public     :
public     :                                        int32 Create (CTX_Project **ctx_prj_ptrp );
public     :                                        logical DefineBitmapsFromFolder ( );
public     : virtual                                int8 DoAfterHandleActivated ( );
public     : virtual                                int8 DoAfterOpen ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical InitResourceDB ( );
public     :                                             pDesigner ( );
public     :                                             ~pDesigner ( );
};

#endif
