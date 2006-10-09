/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_Workspace

\brief    Workspace definition
          A  workspace  definition  entry  describes  a  subordinated  workspace
          (persistent  transaction) for a database. Workspace entries are stored
          for  each  workspace  for  defining subordinated workspaces on a given
          level.

\date     $Date: 2006/03/13 21:30:24,18 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SDB_Workspace"

#include  <pops7.h>
#include  <sSDB_Workspace.hpp>


/******************************************************************************/
/**
\brief  Check - 


\return term

\param  new_opt -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Check"

logical SDB_Workspace :: Check (logical new_opt )
{
  char         path[sizeof(location)+1];
  logical      term = NO;
BEGINSEQ
  if ( !id )                                         SDBERR(335)
  if ( *location <= ' ' )                            SDBERR(336)

  if ( new_opt )
  {
    if ( IsFile(location) )                          SDBERR(337)
    if ( IsDirectory(location) )                     SDBERR(336)
    if ( !GetDirectoryPath(location,path) )          SDBERR(336)
  }
  else
    if ( !IsFile(location) )                         SDBERR(336)

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Fill - 


\return term

\param  ws_info -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fill"

logical SDB_Workspace :: Fill (char *ws_info )
{
  logical                 term = NO;
BEGINSEQ
  if ( !ws_info || !this )                           ERROR

  gvtxbts(ws_info,name,sizeof(name));
  strcat(ws_info," (ID=");
  gvtxltoa(id,ws_info+strlen(ws_info),10);
  if ( *user > ' ' )
  {
    strcat(ws_info,"; User=");
    gvtxbts(ws_info+strlen(ws_info),user,sizeof(user));
  }
  strcat(ws_info,")");

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Initialize - 



\param  ws_root -
\param  ws_name -
\param  ws_user -
\param  ws_id -
\param  ws_path -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void SDB_Workspace :: Initialize (char *ws_root, char *ws_name, char *ws_user, int32 ws_id, char *ws_path )
{

  memset(this,' ',sizeof(SDB_Workspace));
  if ( ws_root )
    gvtxstb(root,ws_root,sizeof(root));
  if ( ws_name )
    gvtxstb(name,ws_name,sizeof(name));
  if ( ws_user )
    gvtxstb(user,ws_user,sizeof(user));

  if ( ws_path )
    strncpy(location,ws_path,sizeof(location)-1);
  else 
    *location = 0;
  
  id = ws_id;

}

/******************************************************************************/
/**
\brief  SDB_Workspace - 


-------------------------------------------------------------------------------
\brief  i0


\param  ws_root -
\param  ws_name -
\param  ws_user -
\param  ws_id -
\param  ws_path -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Workspace"

                        SDB_Workspace :: SDB_Workspace (char *ws_root, char *ws_name, char *ws_user, int32 ws_id, char *ws_path )
{

  Initialize(ws_root,ws_name,ws_user,ws_id,ws_path);

}

/******************************************************************************/
/**
\brief  i01


\param  names -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SDB_Workspace"

                        SDB_Workspace :: SDB_Workspace (char *names )
                     : root(),
  name(),
  user()
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
\brief  SetUser - 



\param  user_name -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetUser"

void SDB_Workspace :: SetUser (char *user_name )
{

  if ( !user_name || *user_name <=' ' )
    memset(user,' ',sizeof(user));
  else
    gvtxstb(user,user_name,sizeof(user));


}

/******************************************************************************/
/**
\brief  SetWSNumber - 



\param  wsnumber -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetWSNumber"

void SDB_Workspace :: SetWSNumber (int32 wsnumber )
{

  id = wsnumber;

}

/******************************************************************************/
/**
\brief  operator== - 


\return comp -

\param  wsentry -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

int16 SDB_Workspace :: operator== (SDB_Workspace &wsentry )
{
  int16              comp = 0;
BEGINSEQ
  if ( *wsentry.get_root() > ' ' )
    if ( comp = memcmp(root,wsentry.get_root(),sizeof(root)) )
                                                     LEAVESEQ
  if ( *wsentry.get_name() > ' ' )
    if ( comp = memcmp(name,wsentry.get_name(),sizeof(name)) )
                                                     LEAVESEQ
  if ( *wsentry.get_user() > ' ' && *wsentry.get_user() != '#') // system-Fuctions may access all work spaces
    if ( comp = memcmp(user,wsentry.get_user(),sizeof(user)) )
                                                     LEAVESEQ

ENDSEQ
  return(comp ? NO : YES);
}


