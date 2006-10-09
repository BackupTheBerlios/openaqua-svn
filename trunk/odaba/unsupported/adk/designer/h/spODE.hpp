/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pODE

\brief    


\date     $Date: 2006/08/28 07:55:31,25 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pODE_HPP
#define   pODE_HPP

class     pODE;

class     ErrorMessage;
class     PropertyHandle;
class     pc1_ODC_PFunction;
#include  <sODE_Project.hpp>
#include  <sODE_SearchReplace.hpp>
#include  <sTypeKey.hpp>
#pragma pack(8)

class  pODE :public CTX_Project,
public ODE_Project
{
protected  :         char                                         language[41];                                              // Current language for content within an ODE application
protected  :         logical                                      docu_enabled;                                              // Current project selected in the PropertyHandle for the opened
protected  :         CTX_Control                                 *docu_ctx;                                                  // 
protected  :         ODE_SearchReplace                            search_replace;                                            // 
protected  :         ODE_SearchReplace                           *cur_search_replace;                                        // 
protected  :         char                                         application_name[41];                                      // 
protected  :         CTX_Control                                 *imp_class_ctx;                                             // 

public     :
                     char                                        *get_language() { return(language); }
                     logical                                      get_docu_enabled() { return(docu_enabled); }
                     CTX_Control                                 *get_docu_ctx() { return(docu_ctx); }
                     ODE_SearchReplace                           &get_search_replace() { return(search_replace); }
                     ODE_SearchReplace                           *get_cur_search_replace() { return(cur_search_replace); }
                     char                                        *get_application_name() { return(application_name); }
                     CTX_Control                                 *get_imp_class_ctx() { return(imp_class_ctx); }
public     :                                        int8 ChangeLanguage ( );
public     :                                        void DeselectProject ( );
public     :                                        logical DistributeSearchReplace ( );
public     :                                        logical DistributeSearchReplace (ODE_SearchReplace *ode_search_replace );
public     : virtual                                int8 DoAfterHandleActivated ( );
public     : virtual                                int8 DoAfterOpen ( );
public     : virtual                                int8 DoBeforeClose ( );
public     :                                        logical Documentation ( );
public     :                                        logical EnableDocumentation (logical enable_opt );
public     :                  DesignerImpExp        logical EnableInputHelp (logical enable_opt );
public     : virtual                                logical ExecuteFunction (char *fname, logical chk_opt=NO );
public     :                                        logical Find ( );
public     :                                        logical GenerateSystemInclude ( );
public     :                                        ODE_SearchReplace *GetCurSearchReplace ( );
public     : virtual                                CTX_Control *GetImpClassContext ( );
public     :                                        char *GetOption (char *option_name );
public     : virtual                                char *GetOptionState (char *option_name );
public     :                                        logical GetProjectName ( );
public     :                                        logical GetProjectPath ( );
public     :                                        void InitOptions ( );
public     :                                        logical InitializePFunction (pc1_ODC_PFunction *pfunct_pc, TypeKey &type_key, logical recursive );
public     :                                        logical InputHelp ( );
public     :                                        logical IsODEContext ( );
public     :                                        logical NewProject ( );
public     :                                        char *ProjectContextClass ( );
public     :                                        char *ProjectName ( );
public     :                                        char *ProjectPath (char *folder_type );
public     :                                        logical ProvideNewError ( );
public     :                                        logical ProvideReferencedType ( );
public     :                                        logical ProvideType ( );
public     :                                        logical ProvideType (TypeKey &type_key, logical no_struct );
public     :                                        logical ReleaseProject ( );
public     :                                        logical Replace ( );
public     :                                        logical ReserveProject ( );
public     :                                        logical ResetCache ( );
public     :                                        logical SearchReplace (logical do_replace );
public     :                                        logical SelectProject (char *prj_name );
public     :                                        void SetApplicationTitle (char *appl_name, char *prj_name, char *selected_object );
public     :                                        logical SetCurSearchReplace (ODE_SearchReplace *ode_search_replace );
public     :                                        logical SetDocumentContext (CTX_Control *ctx_ptr );
public     :                                        void SetDocumentPH (PropertyHandle *doc_ph );
public     :                                        void SetImpClassContext (CTX_Control *control_ctx );
public     :                                        logical SetupOutput (char *string, logical clear_opt=YES );
public     : virtual                                logical SetupProjectSelection (logical reset_opt );
public     :                                        logical ShowMessage (Error *pError, ErrorMessage *err_message );
public     :                                        logical ShowProtocol (Error *pError, ErrorMessage *err_message );
public     :                                             pODE ( );
public     : virtual                                     ~pODE ( );
};

#pragma pack()
#endif
