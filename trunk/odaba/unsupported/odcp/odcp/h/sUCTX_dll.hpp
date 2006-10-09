/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:39:49,98}|(REF)
\class    UCTX_dll

\brief    


\date     $Date: 2006/03/12 19:40:03,87 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   UCTX_dll_HPP
#define   UCTX_dll_HPP

class     UCTX_dll;

class     CTX_Administration;
class     CTX_Application;
class     CTX_Control;
class     CTX_Document;
class     CTX_Project;
class  UCTX_dll
{
protected  :         HINSTANCE                                    dll_instance;                                              
public     :         CreateCtxPtr                                 crt_ctx;                                                   
protected  :         logical                                      loaded;                                                    

public     :
                     logical                                      get_loaded() { return(loaded); }
public     :                                     CTX_Administration *CreateAdminCtx (int32 resid );
public     :                                     CTX_Application *CreateApplicationCtx (int32 resid );
public     :                                     CTX_Control *CreateControlCtx (int32 resid );
public     :                                     CTX_Document *CreateDocumentCtx (int32 resid );
public     :                                     CTX_Project *CreateProjectCtx (int32 resid );
public     :                                     char *GetDLLPath ( );
public     :                                     logical Initialize ( );
public     :                                                             UCTX_dll ( );
public     :                                                             ~UCTX_dll ( );
};

#endif
