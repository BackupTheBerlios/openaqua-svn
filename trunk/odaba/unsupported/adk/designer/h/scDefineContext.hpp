/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cDefineContext

\brief    


\date     $Date: 2006/06/03 15:05:22,68 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cDefineContext_HPP
#define   cDefineContext_HPP

class     cDefineContext;

class  cDefineContext :public CTX_Control
{

public     :
public     :                                        logical AssociateEntry ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                             cDefineContext ( );
public     : virtual                                     ~cDefineContext ( );
};

#endif
