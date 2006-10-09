/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel - 
\class    pc_ODC_Project

\brief    


\date     $Date: 2006/06/04 11:17:51,54 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_Project_HPP
#define   pc_ODC_Project_HPP

class     pc_ODC_Project;

#include  <cCompileStates.h>
#include  <cProgramLanguage.h>
#include  <spc_ODC_compile_object_base.hpp>
class  pc_ODC_Project :public pc_ODC_compile_object_base
{

public     :
public     :                                        logical CreateCompAllUnix (CompileStates compreq, logical nocomp_ignore, NString *result_string );
public     :                                        logical CreateCompAllWin (CompileStates compreq, logical nocomp_ignore, NString *result_string );
public     :                                        void CreateCompLine (char *procstr, char *project_name, char *storage_name );
public     :                                        void CreateCompLine2 (char *procstr, char *cmdline, char *obname );
public     :                                        void CreateCompLine3 (char *procstr, char *storage_name, logical debug_opt );
public     :                                        void CreateSection (char *procstr, PropertyHandle &exe_ph );
public     :                                        void CreateSection_if (char *procstr, char *class_names );
public     :                                        char *GetCompileCommand (NString &nstring, char *praefix );
public     :                                        char *GetDocFileName (NString &nstring, char *doc_type );
public     :                                        char *GetDocFileName (char *ppath, char *folder_type, int max_len );
public     :                                        char *GetLinkCommand (NString &nstring, logical debug_opt );
public     :                                        char *GetProjectPath (NString &nstring, char *folder_type );
public     :                                        char *GetProjectPath (char *ppath, char *folder_type, int max_len );
public     :                                        int32 GetProjectPathIndex (char *folder_type );
public     :                                        logical InitializeExternalResources (NString *error_string, logical folder_opt );
public     :                                        logical InitializeFolder (NString *error_string, char *folder_type, char *init_string );
public     :                                        void SetCompile (CompileStates compreq );
public     :                                        void SetGenInc (logical genincl );
public     :                                        logical SetupReferences ( );
public     :                                        logical WriteBatchFile (char *area, char *path, char *filnames, NString *result_string );
public     :                                             pc_ODC_Project (PropertyHandle *prophdl );
public     :                                             pc_ODC_Project (DatabaseHandle &dbhandle );
};

#endif
