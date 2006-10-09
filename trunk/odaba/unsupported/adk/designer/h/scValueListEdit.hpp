/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cValueListEdit

\brief    


\date     $Date: 2006/06/03 15:05:24,98 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cValueListEdit_HPP
#define   cValueListEdit_HPP

class     cValueListEdit;

class  cValueListEdit :protected CTX_Control
{

public     :
public     :                                        logical CheckSave ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical GenerateInclude ( );
public     :                                             cValueListEdit ( );
public     : virtual                                     ~cValueListEdit ( );
};

#endif
