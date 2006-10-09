/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cVlaueListEdit



\date     $Date: 2006/05/22 23:27:00,23 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cVlaueListEdit_HPP
#define   cVlaueListEdit_HPP

class     cVlaueListEdit;

class  cVlaueListEdit :protected CTX_Control
{

public     :
public     :                                        logical CheckSave ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GenerateInclude ( );
public     :                                             cVlaueListEdit ( );
public     : virtual                                     ~cVlaueListEdit ( );
};

#endif
