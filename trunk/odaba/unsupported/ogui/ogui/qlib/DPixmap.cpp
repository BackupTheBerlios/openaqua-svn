/********************************* Class Source Code ***************************/
/**
\package  OGUI
\class    DPixmap



\date     $Date: 2006/04/28 14:17:38,31 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DPixmap"

#include  <pogui7.h>
#include  <sDPixmap.hpp>


/******************************************************************************/
/**
\brief  DPixmap

\return 
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DPixmap"

     DPixmap :: DPixmap ( )
                     : path(NULL)
{


}

/******************************************************************************/
/**
\brief  i01


\param  cpath
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DPixmap"

     DPixmap :: DPixmap (char *cpath )
{
  SetPath(cpath);
}

/******************************************************************************/
/**
\brief  GetPath

\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPath"

char *DPixmap :: GetPath ( )
{

  return ( path && *path ? path : NULL );

}

/******************************************************************************/
/**
\brief  GetUsedPath

\return string - Character string

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetUsedPath"

char *DPixmap :: GetUsedPath ( )
{
  static char          string[1024];
  std::string          spath;
BEGINSEQ
  if ( !path || !*path )                            ERROR
  
  ReplaceSysVariable(gvtxbts(string,path,sizeof(string)-1),sizeof(string)-1);
  // on unix it can be bad if someone hacks in '\\'
  for(int pos = 0; pos<1024 && string[pos]!='\0';pos++)
    if(string[pos]=='\\')
      string[pos] = '/';

RECOVER
  return(NULL);
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  ReleasePath


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReleasePath"

void DPixmap :: ReleasePath ( )
{

  if ( path )
    free(path);
  path = NULL;

}

/******************************************************************************/
/**
\brief  SetPath


\param  cpath
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetPath"

void DPixmap :: SetPath (char *cpath )
{

  ReleasePath();
  
  if ( cpath )
    path = strdup(cpath);


}

/******************************************************************************/
/**
\brief  ~DPixmap

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DPixmap"

     DPixmap :: ~DPixmap ( )
{

  ReleasePath();

}


