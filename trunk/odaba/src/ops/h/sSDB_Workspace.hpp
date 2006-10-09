/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_Workspace

\brief    Workspace definition
          A  workspace  definition  entry  describes  a  subordinated  workspace
          (persistent  transaction) for a database. Workspace entries are stored
          for  each  workspace  for  defining subordinated workspaces on a given
          level.

\date     $Date: 2006/03/13 21:30:14,17 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_Workspace_HPP
#define   SDB_Workspace_HPP

class     SDB_Workspace;

#include  <sSDB_Workspace.hpp>
#pragma pack(8)

class  SDB_Workspace
{
protected  :         char                                         root[256];                                                 // Workspace root
protected  :         char                                         name[128];                                                 // Workspace name
protected  :         char                                         user[80];                                                  // Owner of the workspace
protected  :         int32                                        id;                                                        // Workspace identifier
protected  :         char                                         location[256];                                             // Physical location of the workspace

public     :
                     char                                        *get_root() { return(root); }
                     char                                        *get_name() { return(name); }
                     char                                        *get_user() { return(user); }
                     int32                                        get_id() { return(id); }
                     char                                        *get_location() { return(location); }
public     :                                     logical Check (logical new_opt );
public     :         OPS7ImpExp                  logical Fill (char *ws_info );
public     :                                     void Initialize (char *ws_root, char *ws_name, char *ws_user, int32 ws_id=UNDEF, char *ws_path=NULL );
public     :                                                             SDB_Workspace (char *ws_root, char *ws_name, char *ws_user, int32 ws_id=UNDEF, char *ws_path=NULL );
public     :                                                             SDB_Workspace (char *names );
public     :                                     void SetUser (char *user_name );
public     :                                     void SetWSNumber (int32 wsnumber );
public     :                                     int16 operator== (SDB_Workspace &wsentry );
};

#pragma pack()
#endif
