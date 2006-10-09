/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cContextClass

\brief    


\date     $Date: 2006/06/03 15:05:21,39 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cContextClass_HPP
#define   cContextClass_HPP

class     cContextClass;

class  cContextClass :public CTX_Control
{

public     :
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     :                                        logical EditEntry ( );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
};

#endif
