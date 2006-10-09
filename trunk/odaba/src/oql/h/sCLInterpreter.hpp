/********************************* Class Declaration ***************************/
/**
\package  OQL - 
\class    CLInterpreter

\brief    


\date     $Date: 2006/07/21 17:17:24,56 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CLInterpreter_HPP
#define   CLInterpreter_HPP

class     CLInterpreter;

class     CLInterpreter;
#include  <sCLInterpreterBase.hpp>
#pragma pack(8)

class  CLInterpreter :public CLInterpreterBase
{

public     :
public     :                                        logical BEGIN ( );
public     :                                        logical BEGINTRANSACTION ( );
public     :                                        logical CALL ( );
public     :                                        logical CC ( );
public     :                                        logical CD ( );
public     :                  OQLImpExp                  CLInterpreter (ODABAClient &odaba_client );
public     :                  OQLImpExp                  CLInterpreter (CLInterpreter *clip );
public     :                                        logical CO ( );
public     :                                        logical COMMITTRANSACTION ( );
public     :                                        logical CPY ( );
public     :                                        logical CRT ( );
public     :                                        logical DEL ( );
public     :                                        logical DELETEEXTENT ( );
public     :                                        logical DELETEEXTENTREF ( );
public     :                                        logical DO ( );
public     :                                        logical ECHO ( );
public     :                                        logical END ( );
public     :                                        logical EXECUTEACTION ( );
public     :                                        logical EXECUTEEXPRESSION ( );
public     :                                        logical EXECUTEINSTANCEACTION ( );
public     :                                        logical EXECUTEPROPERTYACTION ( );
public     :                                        logical EXIT ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical FA ( );
public     :                                        logical HELP ( );
public     :                                        logical IF ( );
public     :                                        logical LAN ( );
public     :                                        logical LAV ( );
public     :                                        logical LCN ( );
public     :                                        logical LD ( );
public     :                                        logical LEAVE ( );
public     :                                        logical LI ( );
public     :                                        logical LK ( );
public     :                                        logical LO ( );
public     :                                        logical LOAD ( );
public     :                                        logical LOC ( );
public     :                                        logical MOV ( );
public     :                                        logical NEXT ( );
public     :                                        logical OQL ( );
public     :                                        logical PAUSE ( );
public     :                                        logical PREV ( );
public     :                                        logical PRINT ( );
public     :                                        logical Q ( );
public     :                                        logical QUIT ( );
public     :                                        logical RECREATEEXTENT ( );
public     :                                        logical REDIR ( );
public     :                                        logical RETURN ( );
public     :                                        logical RFC ( );
public     :                                        logical ROLLBACK ( );
public     :                                        logical SAL ( );
public     :                                        logical SAV ( );
public     :                                        logical SET ( );
public     :                                        logical SFC ( );
public     :                                        logical WHILE ( );
public     : virtual          OQLImpExp                  ~CLInterpreter ( );
};

#pragma pack()
#endif
