/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cMainFunctionEdit

\brief    


\date     $Date: 2006/06/04 10:31:01,51 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cMainFunctionEdit_HPP
#define   cMainFunctionEdit_HPP

class     cMainFunctionEdit;

class  cMainFunctionEdit :protected CTX_Control
{

public     :
public     :                                        logical Compile ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                        logical ErrorLookup ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical Link ( );
public     :                                        logical SetupOutput (char *string, logical clear_opt=YES );
public     :                                             cMainFunctionEdit ( );
public     : virtual                                     ~cMainFunctionEdit ( );
};

#endif
