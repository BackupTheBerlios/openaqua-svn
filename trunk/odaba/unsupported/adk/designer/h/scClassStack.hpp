/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    cClassStack

\brief    


\date     $Date: 2006/06/03 15:05:20,76 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cClassStack_HPP
#define   cClassStack_HPP

class     cClassStack;

class  cClassStack :public CTX_Control
{
protected  :         char                                         last_impl[41];                                             // 

public     :
                     char                                        *get_last_impl() { return(last_impl); }
public     :                                        int32 Create (CTX_Control **ctx_ctl_ptrp );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical SetLastImplementation ( );
public     :                                        logical SetLastImplementation (char *impl_name );
public     :                                        logical Synchronize ( );
public     :                                             cClassStack ( );
public     : virtual                                     ~cClassStack ( );
};

#endif
