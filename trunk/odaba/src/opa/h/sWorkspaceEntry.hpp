/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    WorkspaceEntry

\brief    Workspace entry
          Workspace  entries  are  stored  for  each  workspace  for  defining 
          subordinated workspaces on a given level.

\date     $Date: 2006/03/12 19:13:58,37 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   WorkspaceEntry_HPP
#define   WorkspaceEntry_HPP

class     WorkspaceEntry;

class     SDB_Workspace;
#include  <sWorkspaceEntry.hpp>
#pragma pack(8)

class  WorkspaceEntry
{
protected  :         char                                         root[256];                                                 // Workspace root
protected  :         char                                         name[128];                                                 // Workspace Name
protected  :         char                                         user[80];                                                  //
protected  :         int8                                         checked;                                                   // Indicates that the workspace is checked

public     :
                     char                                        *get_root() { return(root); }
                     char                                        *get_name() { return(name); }
                     char                                        *get_user() { return(user); }
                     int8                                         get_checked() { return(checked); }
public     :                                     void Initialize (char *ws_root, char *ws_name, char *ws_user );
public     :                                     void SetUser (char *user_name );
public     :                                                             WorkspaceEntry (char *ws_root, char *ws_name, char *ws_user );
public     :                                                             WorkspaceEntry (char *names );
public     :                                     int16 operator== (SDB_Workspace &wsentry );
public     :                                     void set_checked (int8 checked_val );
};

#pragma pack()
#endif
