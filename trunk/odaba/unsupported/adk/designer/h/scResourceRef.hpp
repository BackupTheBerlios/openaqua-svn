/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cResourceRef

\brief    


\date     $Date: 2006/06/03 15:05:24,20 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cResourceRef_HPP
#define   cResourceRef_HPP

class     cResourceRef;

class  cResourceRef :public CTX_Control
{

public     :
public     :                                        logical AssociateEntry ( );
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                             cResourceRef ( );
public     :                                             ~cResourceRef ( );
};

#endif
