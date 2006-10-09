/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassTree

\brief    


\date     $Date: 2006/06/03 15:05:20,98 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cClassTree_HPP
#define   cClassTree_HPP

class     cClassTree;

class  cClassTree :public CTX_Control
{

public     :
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                        logical DesignEntry ( );
public     : virtual                                int8 DoAfterSelect ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                             cClassTree ( );
public     :                                             ~cClassTree ( );
};

#endif
