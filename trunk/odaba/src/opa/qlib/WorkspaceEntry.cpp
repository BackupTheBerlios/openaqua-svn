/********************************* Class Source Code ***************************/
/**
\package  OPA
\class    WorkspaceEntry

\brief    Workspace entry
          Workspace  entries  are  stored  for  each  workspace  for  defining 
          subordinated workspaces on a given level.

\date     $Date: 2006/05/31 18:30:46,79 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "WorkspaceEntry"

#include  <popa7.h>
#include  <sSDB_Workspace.hpp>
#include  <sWorkspaceEntry.hpp>


/******************************************************************************/
/**
\brief  Initialize


\param  ws_root
\param  ws_name
\param  ws_user
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void WorkspaceEntry :: Initialize (char *ws_root, char *ws_name, char *ws_user )
{
  memset(this,' ',sizeof(WorkspaceEntry));
  if ( ws_root )
    gvtxstb(root,ws_root,sizeof(root));
  if ( ws_name )
    gvtxstb(name,ws_name,sizeof(name));
  if ( ws_user )
    gvtxstb(user,ws_user,sizeof(user));

  checked = NO;
}

/******************************************************************************/
/**
\brief  SetUser


\param  user_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUser"

void WorkspaceEntry :: SetUser (char *user_name )
{

  if ( !user_name || *user_name <=' ' )
    memset(user,' ',sizeof(user));
  else
  {
    gvtxstb(user,user_name,sizeof(user));
    checked = YES;
  }


}

/******************************************************************************/
/**
\brief  WorkspaceEntry

-------------------------------------------------------------------------------
\brief  i0


\param  ws_root
\param  ws_name
\param  ws_user
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WorkspaceEntry"

     WorkspaceEntry :: WorkspaceEntry (char *ws_root, char *ws_name, char *ws_user )
                     :   checked(NO)
{
  Initialize(ws_root,ws_name,ws_user);
}

/******************************************************************************/
/**
\brief  i01


\param  names - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WorkspaceEntry"

     WorkspaceEntry :: WorkspaceEntry (char *names )
                     : root(),
  name(),
  user(),
  checked(NO)
{
  char            *ws_name = NULL;
  char            *ws_root = NULL;
  char            *string = NULL;
  if ( names )
  {
    ws_root = string = strdup(names);
    if ( ws_name = STRSearchChar(string,'.',YES) )
    {
      *ws_name = 0;
      ws_name++;
    }
    else
    {
      ws_name = string;
      ws_root = NULL;
    }
  }
  Initialize(ws_root,ws_name,NULL);
  if ( string )
    free(string);
}

/******************************************************************************/
/**
\brief  operator== - 


\return comp

\param  wsentry
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

int16 WorkspaceEntry :: operator== (SDB_Workspace &wsentry )
{
  int16              comp = 0;
BEGINSEQ
  if ( comp = memcmp(root,wsentry.get_root(),sizeof(root)) )
                                                     LEAVESEQ
  if ( *wsentry.get_name() > ' ' )
    if ( comp = memcmp(name,wsentry.get_name(),sizeof(name)) )
                                                     LEAVESEQ
  if ( *wsentry.get_user() > ' ' )
    if ( comp = memcmp(user,wsentry.get_user(),sizeof(user)) )
                                                     LEAVESEQ

ENDSEQ
  return(comp ? NO : YES);
}

/******************************************************************************/
/**
\brief  set_checked


\param  checked_val
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "set_checked"

void WorkspaceEntry :: set_checked (int8 checked_val )
{

  checked = checked_val;

}


