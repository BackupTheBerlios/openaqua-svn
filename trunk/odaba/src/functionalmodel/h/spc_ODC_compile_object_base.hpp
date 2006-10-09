/********************************* Class Declaration ***************************/
/**
\package  FunctionalModel - 
\class    pc_ODC_compile_object_base

\brief    


\date     $Date: 2006/06/04 10:52:57,53 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_compile_object_base_HPP
#define   pc_ODC_compile_object_base_HPP

class     pc_ODC_compile_object_base;

#include  <cClassModLevel.h>
#include  <cCompileStates.h>
#include  <sDatabaseHandle.hpp>
#include  <sNString.hpp>
#include  <sPropertyHandle.hpp>
class  pc_ODC_compile_object_base :public PropertyHandle
{

public     :
public     :                                        char *GetCompileCommand (NString &nstring, logical main_opt, logical if_opt, char *preafix );
public     :                                        char *GetDocFileName (NString &nstring, char *doc_type, logical if_opt );
public     :                                        char *GetDocFilePath (NString &nstring, char *doc_type, logical if_opt );
public     :                                        PropertyHandle *GetProject ( );
public     :                                        char *GetProjectPath (NString &nstring, char *folder_type );
public     :                                        void ResCompileState ( );
public     :                                        logical ResModLevel ( );
public     :                                        void ResetProject (PropertyHandle *prophdl );
public     :                                        void SetCompileState (CompileStates compreq );
public     :                                        void SetCompileState (char *compreq_string );
public     :                                        void SetIncludeState (logical genincl );
public     :                                        logical SetModified (ClassModLevel cmod_level, logical genincl );
public     :                                        logical SetModified (char *cmod_level_string, logical genincl );
public     :                                             pc_ODC_compile_object_base (PropertyHandle *prophdl );
public     :                                             pc_ODC_compile_object_base (DatabaseHandle &dbhandle, char *extnames );
};

#endif
