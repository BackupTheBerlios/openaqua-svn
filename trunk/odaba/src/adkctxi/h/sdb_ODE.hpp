/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:18,03}|(REF)
\class    db_ODE

\brief    


\date     $Date: 2006/03/12 19:35:24,79 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   db_ODE_HPP
#define   db_ODE_HPP

class     db_ODE;

class  db_ODE :public CTX_DataBase
{

public     :
public     :                                     int32 Create (CTX_DataBase **dbctx_ptrp );
public     : virtual                             logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                     logical GenerateCompile ( );
public     :                                                             db_ODE ( );
public     :                                                             ~db_ODE ( );
};

#endif
