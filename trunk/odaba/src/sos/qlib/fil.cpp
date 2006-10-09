/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    fil

\brief    


\date     $Date: 2006/08/22 12:08:21,98 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "fil"

#include  <pdefault.h>
#include  <fileacc.h>
#include  <ssrt.hpp>
#include  <stim.hpp>

#include  <ifil.h>

/******************************************************************************/
/**
\brief  CopyDirect - 



\return term - Success

\param  fsource - 
\param  ftarget - 
\param  fillength - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyDirect"

logical __cdecl CopyDirect (FILE *fsource, FILE *ftarget, int64 fillength )
{
  uint32                  buflen = BUF_LENGTH;
  uint32                  len;
  void                   *area = NULL;
  logical                 term = NO;
BEGINSEQ
  area = new char[buflen];

  if ( !area )                                       SOSERR(95)
  
  while ( fillength > 0 )
  {
    if ( !(len = fread(area,1,buflen,fsource)) )     SOSERR(2)
    if ( !fwrite(area,len,1,ftarget) )               SOSERR(2)
    fillength -= len;
  }
RECOVER
  term = YES;
ENDSEQ
  delete area;
  return(term);
}

/******************************************************************************/
/**
\brief  CopyFiles - 



\return term - Success

\param  source_path - 
\param  target_dir - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopyFiles"

logical __cdecl CopyFiles (char *source_path, char *target_dir )
{
  srt                    *file_list = NULL;
  char                    spath[256];
  char                    swork_path[256];
  char                    twork_dir[256];
  int                     indx = 0;
  char                   *filename;
  logical                 term = NO;
BEGINSEQ
  if ( !source_path || !target_dir )                 ERROR
  gvtsexc(strcpy(swork_path,source_path),"\\","/",UNDEF);
  gvtsexc(strcpy(twork_dir,target_dir),"\\","/",UNDEF);
  
  if ( twork_dir[strlen(twork_dir)-1] == '/' )
    twork_dir[strlen(twork_dir)-1] = 0;
  if ( !IsDirectory(twork_dir) )                    ERROR
  
  if ( IsFile(swork_path) )
  {
    CopySingleFile(swork_path,twork_dir);          LEAVESEQ
  }
  
  if ( IsDirectory(swork_path) )
  {
    if ( swork_path[strlen(swork_path)-1] == '/' )
      swork_path[strlen(swork_path)-1] = 0;
    file_list = CreateFileTable(swork_path,NULL);
    while ( filename = (char *)file_list->srtigt(++indx) )
    {
      strcat(strcat(strcpy(spath,swork_path),"/"),filename);
      CopySingleFile(spath,twork_dir);
    }
  }


RECOVER
  term = YES;
ENDSEQ
  delete file_list;
  return(term);
}

/******************************************************************************/
/**
\brief  CopySingleFile - 



\return term - Success

\param  source_path - 
\param  target_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CopySingleFile"

logical __cdecl CopySingleFile (char *source_path, char *target_path )
{
  char                    filename[256];
  char                    fileext[256];
  char                    path[512];
  int                     fillen;
  void                   *areaptr = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !source_path || !target_path )                 ERROR
  strcpy(path,target_path);
  gvtsexc(path,"\\","/",UNDEF);
  if ( IsDirectory(target_path) )
  {
    if ( path[strlen(path)-1] != '/' )
      strcat(path,"/");
    filfegt(source_path,filename,fileext);
    strcat(strcat(strcat(path,filename),"."),fileext);
  }
  if ( !(fillen = filread(source_path,&areaptr)) )
                                                     SOSCERR
  if ( filwrit(path,areaptr,fillen) )                ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( areaptr )
    delete areaptr;
  return(term);
}

/******************************************************************************/
/**
\brief  CreateFileTable - 



\return srtptr - 

\param  cpath - Complete path
\param  mask - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateFileTable"

srt *__cdecl CreateFileTable (char *cpath, char *mask )
{
#ifdef __unix__
  DIR    *dir;
  struct dirent *file;
  struct stat   *status;
  char          *string;
  uint          pos;
#else
  struct _finddata_t   ff;
  long                 fhandle;  // so gewollt!
#endif

  char                 path[512];
  srt                 *srtptr = NULL;
  logical              term = NO;

BEGINSEQ
  if ( !cpath )                                       SOSERR(80)
    
  if ( !mask )
    mask = "*.*";
  
  strcpy(path,cpath);
  gvtsexc(path,"\\","/",UNDEF);
  
  srtptr = new srt(20,_MAX_FNAME,_MAX_FNAME-1,1,'C',YES);
  
#ifdef __unix__  
  if ( dir = opendir(path) )
  {
    while ( (file = readdir(dir)) )
    {
      if ( strcmp(file->d_name,".") && strcmp(file->d_name,"..") )
        if ( !filfitsmsk(file->d_name, mask) )
          srtptr->srtkad(file->d_name);

    };
  };

#else
  if ( *mask )
  { 
    if ( path[strlen(path)-1] != '/' )
      strcat(path,"/");
    strcat(path,mask);
  }
  
  if ( (fhandle = _findfirst(path,&ff)) != AUTO )
    do
      if ( strcmp(ff.name,".") && strcmp(ff.name,"..") )
        srtptr->srtkad(ff.name);
    while ( !_findnext(fhandle,&ff) );

#endif

RECOVER
  delete srtptr;
  srtptr = NULL;
ENDSEQ
  return(srtptr);
}

/******************************************************************************/
/**
\brief  FileCopy - 



\return term - Success

\param  source_path - 
\param  target_path - 
\param  pack_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FileCopy"

logical __cdecl FileCopy (char *source_path, char *target_path, logical pack_opt )
{
  int                     buflen = 1024 * 1024;
  FILE                   *fsource = NULL;
  FILE                   *ftarget = NULL;
  char                    filename[256];
  char                    fileext[256];
  char                    path[512];
  int64                   fillength;
  logical                 term = NO;
BEGINSEQ
  if ( !source_path )                                 ERROR
  if ( target_path && *target_path )
  {
    strcpy(path,target_path);
    gvtsexc(path,"\\","/",UNDEF);
    if ( IsDirectory(target_path) )
    {
      if ( path[strlen(path)-1] != '/' )
        strcat(path,"/");
      filfegt(source_path,filename,fileext);
      if ( pack_opt )
        strcpy(fileext,"ozi");
      strcat(strcat(strcat(path,filename),"."),fileext);
    }
  }
  else
  {
    strcpy(path,source_path);
    filextr(path,"ozi");
  }

  fillength = fillen(source_path);
  if ( !(fsource = fopen(source_path,"rb")) )        SOSERR(3)
  if ( !(ftarget = fopen(path,"wb")) )               SOSERR(3)
  
  switch ( pack_opt )
  {
    case 255  : term = UnpackFile(fsource,ftarget,fillength);
                break;
    case  1   : term = PackFile(fsource,ftarget,fillength); 
                break;
    case  0   : term = CopyDirect(fsource,ftarget,fillength);
                break;
  }
RECOVER
  term = YES;
ENDSEQ
  if ( ftarget ) fclose(ftarget);
  if ( fsource ) fclose(fsource);
  return(term);
}

/******************************************************************************/
/**
\brief  FileLock - 



\return term - Success

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FileLock"

logical __cdecl FileLock (char *cpath )
{
  int                     handle;
  logical                 opened = NO;
  logical                 term = NO;
  while ( !opened )
  {
#ifdef __unix__
    if ( (handle = _open (cpath,
                          (int)( O_CREAT ),
                          (S_IREAD )        )) > 0 )
#else  
    if ( (handle = _open (cpath,
                          (int)(O_WRONLY | O_CREAT | O_BINARY ),
                          S_IREAD           )) > 0 )
#endif
      opened = YES;
    else
      TWAIT(10);
  }
  return(term);
}

/******************************************************************************/
/**
\brief  FileRead - 



\return fillen - 

\param  cpath - Complete path
\param  areaptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FileRead"

int32 __cdecl FileRead (char *cpath, void **areaptr )
{
  char         path[1025];
  FILE        *fsource;
  int32        fillength = UNDEF;

BEGINSEQ
  strcpy(path,cpath);
  ReplaceSysVariable(path,sizeof(path)-1);

//  SOSRESET  führt zu dead-locks im multithreading
  *areaptr = NULL;
  fillength = fillen(path);
  
  if ((fsource = fopen(path,"rb")) == 0)             ERROR
  if ( !(*areaptr = new char[fillength+1]) )         SOSERR(95)
  
  if ( fillength )
    if ( !fread(*areaptr,(unsigned int) fillength,1,fsource) )
                                                     SOSERR(2)
  ((char *)(*areaptr))[fillength] = 0;

RECOVER
  delete *areaptr;
  *areaptr = NULL;
  fillength = UNDEF;
ENDSEQ
  if ( fsource )
    fclose(fsource);
  return(fillength);
}

/******************************************************************************/
/**
\brief  FileWrite - 



\return term - Success

\param  cpath - Complete path
\param  area - 
\param  fillen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FileWrite"

logical __cdecl FileWrite (char *cpath, void *area, int32 fillen )
{
  char         path[1025];
  FILE        *filptr = NULL;
  logical      term   = NO;
BEGINSEQ
  strcpy(path,cpath);
  ReplaceSysVariable(path,sizeof(path)-1);

  SOSEV1(path,UNDEF)
  
  if ( !(filptr = fopen(path,"wb")) )               SOSERR(3)

  if ( !fillen )
    fillen = strlen((char *)area);
  if ( fillen )
    if ( !fwrite(area,(unsigned int) fillen,1,filptr) ) 
                                                     SOSERR(2)
RECOVER
  term = YES;
ENDSEQ
  if ( filptr )
    fclose(filptr);
  return(term);
}

/******************************************************************************/
/**
\brief  GetDirectoryPath - 



\return cond - Return value

\param  cpath - Complete path
\param  dpath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDirectoryPath"

logical __cdecl GetDirectoryPath (char *cpath, char *dpath )
{

  return ( GetDirectoryPathInfo(cpath,dpath,strlen(cpath)+1) );


}

/******************************************************************************/
/**
\brief  GetDirectoryPathInfo - 



\return cond - Return value

\param  cpath - Complete path
\param  dpath - 
\param  dpath_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDirectoryPathInfo"

logical __cdecl GetDirectoryPathInfo (char *cpath, char *dpath, int16 dpath_len )
{
  int         len  = strlen(cpath);
  logical     cond = YES;
BEGINSEQ
  memset(dpath,0,dpath_len);  
  strncpy(dpath,cpath,dpath_len-1);
  gvtsexc(dpath,"\\","/",UNDEF);
  
  if ( IsDirectory(dpath) )                          LEAVESEQ
  while ( --len )
  {
    dpath[len+1] = 0;
    if ( dpath[len] == '/' ||  dpath[len] == ':' )
      break;
  }  
  if ( IsDirectory(dpath) )                          LEAVESEQ
  else                                               ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  GetFileName - 



\return filename - 

\param  cpath - Complete path
\param  filname - 
\param  filext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFileName"

char *__cdecl GetFileName (char *cpath, char *filname, char *filext )
{

  return(GetFileNameInfo(cpath,filname,filext,256,256));


}

/******************************************************************************/
/**
\brief  GetFileNameInfo - 



\return filename - 

\param  cpath - Complete path
\param  filname - 
\param  filext - 
\param  name_len - 
\param  ext_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFileNameInfo"

char *__cdecl GetFileNameInfo (char *cpath, char *filname, char *filext, int16 name_len, int16 ext_len )
{
  char      dpath[1024];
  char      drives[3];
  int       pos;
  int       i;

BEGINSEQ
  memset(filname,0,name_len--);

  if ( !cpath )                                      ERROR

  if ( (pos = fildirg(cpath,drives,dpath)) < strlen(cpath) )
  {
    for ( i=0; cpath[pos] && cpath[pos] != '.' && i < name_len; pos++, i++ )
      filname[i] = cpath[pos];
    
    if ( filext )
    {
      memset(filext ,0,ext_len--);
      if ( cpath[pos] == '.' )
        for ( pos++, i=0; cpath[pos] && i < ext_len; pos++, i++ )
          filext[i] = cpath[pos];
    }
  }

RECOVER

ENDSEQ
  return(filname);

}

/******************************************************************************/
/**
\brief  GetLastFolderInfo - 



\return cond - Return value

\param  cpath - Complete path
\param  dpath - 
\param  folder - 
\param  dpath_len - 
\param  folder_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLastFolderInfo"

logical __cdecl GetLastFolderInfo (char *cpath, char *dpath, char *folder, int16 dpath_len, int16 folder_len )
{
  char       *wpath = cpath ? strdup(cpath) : NULL;
  int         len   = strlen(cpath);
  logical     cond  = YES;
BEGINSEQ
  if ( !GetDirectoryPathInfo(cpath,wpath,len) )      ERROR

  len = strlen(wpath)+1;
  while ( --len )
  {
    if ( wpath[len] != '/' &&  wpath[len] != ':' )
      break;
    wpath[len] = 0;
  }  
  if ( !len )                                       ERROR
  
  while ( --len )
    if ( wpath[len] == '/' ||  wpath[len] == ':' )
      break;
  if ( !len )                                       ERROR
  wpath[len] = 0;

  if ( dpath )
  {
    memset(dpath,0,dpath_len);
    strncpy(dpath,wpath,dpath_len-1);
  }
  if ( folder )
  {
    memset(folder,0,folder_len);
    strncpy(folder,wpath+len+1,folder_len-1);
  }

RECOVER
  if ( dpath )
    *dpath = 0;
  if ( folder )
    *folder = 0;
  cond = NO;
ENDSEQ
  if ( wpath )
    free(wpath);
  return(cond);
}

/******************************************************************************/
/**
\brief  IsDirectory - 



\return cond - Return value

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsDirectory"

logical __cdecl IsDirectory (char *cpath )
{

  return(!filchck(cpath,'D'));

}

/******************************************************************************/
/**
\brief  IsFile - 



\return cond - Return value

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsFile"

logical __cdecl IsFile (char *cpath )
{
  char         path[1025];
  strcpy(path,cpath);
  ReplaceSysVariable(path,sizeof(path)-1);

  return(!filchck(path,'F'));

}

/******************************************************************************/
/**
\brief  MakePathDirectories - 



\return term - Success

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "MakePathDirectories"

logical __cdecl MakePathDirectories (char *cpath )
{
  char     workpath[129];
  int      pos  = strlen(cpath)-1;
  logical  term = NO;

BEGINSEQ
  if ( pos < 0 )                                     ERROR

  strcpy(workpath,cpath);
  gvtsexc(workpath,"\\","/",UNDEF);
  if ( workpath[pos] == '/' )
    workpath[pos--] = 0;

  while ( pos )
    if ( workpath[pos] != '/' )
      --pos;
    else
    {  
      workpath[pos] = 0;
      if ( !IsDirectory(workpath) )
        if ( MakePathDirectories(workpath) )         ERROR
      break;  
    }

#ifdef __unix__
  if ( mkdir(cpath,0777) )                               ERROR
#else
  gvtsexc(cpath,"/","\\",UNDEF);
  if ( _mkdir(cpath) )                               ERROR
#endif

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PackFile - 



\return term - Success

\param  fsource - 
\param  ftarget - 
\param  fillength - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PackFile"

logical __cdecl PackFile (FILE *fsource, FILE *ftarget, int64 fillength )
{
  uint32                  buflen = BUF_LENGTH;
  uint32                  outlen;
  uint32                  len;
  uint32                  olen;
  void                   *inarea  = NULL;
  void                   *outarea = NULL;
  logical                 term    = NO;
BEGINSEQ
  if ( !fwrite("SOSZ",4,1,ftarget) )                 SOSERR(2)
  outlen = buflen+buflen/1000+16;
  if ( !fwrite(&buflen,4,1,ftarget) )                SOSERR(2)
  if ( !fwrite(&outlen,4,1,ftarget) )                 SOSERR(2)
  
  inarea  = new char[buflen];
  outarea = new char[outlen];
  if ( !inarea || !outarea )                         SOSERR(95)
  
  while ( fillength > 0 )
  {
    if ( !(len = fread(inarea,1,buflen,fsource)) )   SOSERR(2)
    olen = outlen;
    if ( Pack(outarea,(size_t*)&olen,inarea,len,AUTO) )       ERROR
    if ( !fwrite(&olen,4,1,ftarget) )                SOSERR(2)
    if ( !fwrite(outarea,olen,1,ftarget) )           SOSERR(2)
    fillength -= len;
  }
RECOVER
  term = YES;
ENDSEQ
  delete inarea;
  delete outarea;
  return(term);
}

/******************************************************************************/
/**
\brief  ReadTextFile - 



\return text - Error text

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReadTextFile"

char *__cdecl ReadTextFile (char *cpath )
{
  char           *area = NULL;
BEGINSEQ
  if ( filread(cpath,(void **)&area) <= 0 )          ERROR
RECOVER
  area = NULL;
ENDSEQ
  return(area);
}

/******************************************************************************/
/**
\brief  UnpackFile - 



\return term - Success

\param  fsource - 
\param  ftarget - 
\param  fillength - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UnpackFile"

logical __cdecl UnpackFile (FILE *fsource, FILE *ftarget, int64 fillength )
{
  uint32                  buflen;
  uint32                  outlen;
  uint32                  len;
  uint32                  olen;
  char                    header[4];
  void                   *inarea  = NULL;
  void                   *outarea = NULL;
  logical                 term    = NO;
BEGINSEQ
  if ( fread(header,1,4,fsource) != 4 )              SOSERR(202)
  fillength -= 4;
  if ( memcmp(header,"SOSZ",4) )                     SOSERR(202)
  if ( fread(&buflen,1,4,fsource) != 4 )             SOSERR(202)
  fillength -= 4;
  if ( fread(&outlen,1,4,fsource) != 4 )             SOSERR(202)
  fillength -= 4;
  
  outarea = new char[buflen];
  inarea = new char[outlen];
  if ( !inarea || !outarea )                         SOSERR(95)
  
  while ( fillength > 0 )
  {
    if ( fread(&len,1,4,fsource) != 4 )              SOSERR(202)
    if ( len > outlen )                              SOSERR(202)
    if ( !fread(inarea,len,1,fsource) )              SOSERR(2)
    olen = outlen;
    if ( Unpack(outarea,(size_t*)&olen,inarea,len) )          ERROR
    if ( !fwrite(outarea,olen,1,ftarget) )           SOSERR(2)
    fillength -= (len+4);
  }
RECOVER
  term = YES;
ENDSEQ
  delete inarea;
  delete outarea;
  return(term);
}

/******************************************************************************/
/**
\brief  WriteTextFile - 



\return term - Success

\param  cpath - Complete path
\param  area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WriteTextFile"

logical __cdecl WriteTextFile (char *cpath, void *area )
{

  return (   cpath && area
           ? filwrit(cpath,area,strlen((char *)area)) 
           : YES     );

}

/******************************************************************************/
/**
\brief  filchck - 



\return term - Success

\param  cpath - Complete path
\param  filstat - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filchck"

logical __cdecl filchck (char const * const cpath, char filstat )
{
  struct stat   status;
  char          workpath[129];

  strcpy(workpath,cpath);
  gvtsexc(workpath,"\\","/",UNDEF);
  
  switch ( strlen(workpath) )
  {
    case  2 : strcat(workpath,"/");
    case  3 : break;
    default : if ( workpath[strlen(workpath)-1] == '/' )
                workpath[strlen(workpath)-1] = 0;
              break;
  }

  return ( (logical)
           (stat(workpath,&status) ||
           ((status.st_mode & S_IFMT) != ((unsigned short)(filstat == 'D'
                                      ?  S_IFDIR
                                      :  S_IFREG)))         ));

}

/******************************************************************************/
/**
\brief  filcopy - 



\return term - Success

\param  opath - 
\param  npath - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filcopy"

logical __cdecl filcopy (char *opath, char *npath )
{
  char      string[300];
#ifdef _WINDOWS
  return(YES);
#else
  return ( (logical)system(strcat(strcat(strcat(strcat(strcpy(string,
                           "copy "),opath)," "),npath)," >NUL")) );
#endif


}

/******************************************************************************/
/**
\brief  filddel - 



\return term - Success

\param  cpath - Complete path
\param  deldir - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filddel"

logical __cdecl filddel (char const * const cpath, logical deldir )
{
  srt                 *file_list = NULL;
  char                 dpath[129];
  char                 path[129];
  int                  indx = 0;
  char                *filename;
  char                *last;
  logical              term = NO;
BEGINSEQ
  strcpy(path,cpath);
  gvtsexc(path,"\\","/",UNDEF);
  if ( IsDirectory(cpath) )    
  {
    if ( path[strlen(path)-1] != '/' )
      strcat(path,"/");
    strcat(path,"*.*");
  }

  strcpy(dpath,path);
  for (last = dpath+strlen(dpath); last > dpath; last-- )
    if ( *(last-1) == '/' || *(last-1) == ':' )
      break;

  file_list = CreateFileTable(path,"");
  while ( filename = (char *)file_list->srtigt(++indx) )
  {
    *last = 0;
    if ( remove(strcat(dpath,filename)) )      
      term = YES;
  }
  if ( term )                                        SOSERR(2)
    
  if ( deldir && *(last-1) == '/' )
  {
    *(last-1) = 0;
#ifdef __unix__    
    rmdir(dpath);
#else
    _rmdir(dpath);
#endif
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  fildirg - 



\return filnpos - 

\param  cpath - Complete path
\param  drives - 
\param  dirs - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fildirg"

int __cdecl fildirg (char *cpath, char *drives, char *dirs )
{
  char      wpath[129];
  int       len = strlen(cpath);

  memset(drives,0,3);
  memset(dirs,0,129);
  strcpy(wpath,cpath);
  gvtsexc(wpath,"\\","/",UNDEF);
  
  if ( !IsDirectory(wpath) )
    while ( len-- )
    {
      if ( wpath[len] == '/' ||  wpath[len] == ':' )
        break;
      wpath[len] = 0;
    }  

  if ( (len = strlen(wpath)) && wpath[len-1] != '/' )
    strcat(wpath,"/");

  if ( wpath[1] == ':' )
    memcpy(drives,wpath,2);

  strcpy(dirs,wpath+(*drives ? 2 : 0));

  return ( strlen(wpath) );

}

/******************************************************************************/
/**
\brief  fildpgt - 



\return path - Complete path

\param  path - Complete path
\param  maxlens - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fildpgt"

char *__cdecl fildpgt (char *path, int16 maxlens )
{
  logical                 term = NO;
  getcwd(path,maxlens);

  gvtsexc(path,"\\","/",UNDEF);
  if ( path[strlen(path)-1] != '/' )
    strcat(path,"/");

  return(path);

}

/******************************************************************************/
/**
\brief  filevfd - 



\return path - Complete path

\param  envname - 
\param  path - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filevfd"

char *__cdecl filevfd (char *envname, char *path )
{
  struct stat   status;
  char         *tpath;
  register     int  plen;

BEGINSEQ
  if ( !( tpath = getenv(envname)) )                 ERROR

  memset(path,0,128);
  gvtschs(tpath,';',path,strlen(tpath));

  gvtsexc(path,"\\","/",UNDEF);
  if ( path[ (plen=strlen(path))-1 ] == ';' )
    path[strlen(path)-1] = 0;

  if ( path[strlen(path)-1] == '/' )
    path[strlen(path)-1] = 0;

  if ( path[strlen(path)-1] == ':' )
    strcat(path,"/");

  if ( stat(path,&status) || (status.st_mode & S_IFMT) != S_IFDIR )
                                                     ERROR
  if ( path[strlen(path)-1] != '/' )
    strcat(path,"/");

RECOVER
  path = NULL;
ENDSEQ
  return(path);

}

/******************************************************************************/
/**
\brief  filevgp - 



\return cpath - Complete path

\param  filname - 
\param  envname - 
\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filevgp"

char *__cdecl filevgp (char *filname, char *envname, char *cpath )
{
  char      *path;
  register   int len;

BEGINSEQ
  if ( !( path = ( envname ? getenv(envname) : getenv("PATH") ))  )
                                                     SOSERR(1)
  while ( (len = strlen(path)) && path )
  {
    memset(cpath,0,128);
    gvtschs(path,';',cpath,len);
    if ( path = (char *)memchr(path,';',len) )
      path++;

    if ( cpath[strlen(cpath)-1] == ';' )
      cpath[strlen(cpath)-1] = 0;

    gvtsexc(cpath,"\\","/",UNDEF);
    if ( strlen(cpath) > 2 && cpath[strlen(cpath)-1] != '/' )
      strcat(cpath,"/");
    strcat(cpath,filname);

    if ( !access(cpath,0) )
      return(cpath);
  }
  ERROR

RECOVER
  cpath = NULL;
ENDSEQ
  return(cpath);
}

/******************************************************************************/
/**
\brief  filextr - 



\return path - Complete path

\param  path - Complete path
\param  filext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filextr"

char *__cdecl filextr (char *path, char *filext )
{
  int       len = strlen(path);

  gvtsexc(path,"\\","/",UNDEF);
  while ( --len )
    switch ( path[len]  )
    {
      case '.'  : strcpy(path+len+(*filext ? 1 : 0 ),filext);
                  return(path);
      case '/' : return ( strcat(strcat(path,"."),filext) );
    }

  if ( *filext )
    strcat(path,".");

    return ( strcat(path,filext) );

}

/******************************************************************************/
/**
\brief  filfegt - 



\return filname - 

\param  cpath - Complete path
\param  filname - 
\param  filext - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filfegt"

char *__cdecl filfegt (char *cpath, char *filname, char *filext )
{

  return(GetFileNameInfo(cpath,filname,filext,9,4));


}

/******************************************************************************/
/**
\brief  filfill - 



\return datarea - 

\param  cpath - Complete path
\param  filoffset - 
\param  readlen - 
\param  area - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filfill"

void *__cdecl filfill (char *cpath, int16 filoffset, int16 readlen, void *area )
{
  FILE        *fsource;

BEGINSEQ
  if ( !(fsource = fopen(cpath,"rb")) )              ERROR

  if ( fseek(fsource,filoffset,SEEK_SET) )           SOSERR(2)
  if ( !fread(area,(unsigned int)readlen,1,fsource)) SOSERR(2)

RECOVER
  area = NULL;
ENDSEQ
  if ( fsource )
    fclose(fsource);
  return(area);

}

/******************************************************************************/
/**
\brief  filfitsmsk - 



\return term - Success

\param  filname - 
\param  mask - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filfitsmsk"

logical __cdecl filfitsmsk (char *filname, char *mask )
{
  char       *namedup = strdup(filname);
  char       *maskdup = strdup(mask);
  char       *name    = namedup;
  char       *maskcpy = maskdup;
  char       *submask = NULL;
  int         pos     = 0;
  logical     term    = NO;

BEGINSEQ
  if ( submask = strrchr(maskcpy, '.') )
    if ( submask[1] )
      if ( strspn(&submask[1],"*") == strlen(&submask[1]) )
        strcpy(submask, ".*");

  while ( submask = strstr(maskcpy,"*?") )
  {
    submask[0] = '?';
    submask[1] = '*';
  };

  while ( (pos = strcspn(maskcpy, "*?")) != strlen(maskcpy) )
  {
    if ( strncmp(name,maskcpy,pos) )                LEAVESEQ

    name = &name[pos];
    switch ( maskcpy[pos] )
    {
      case '?' : if ( !*name || name == strrchr(name,'.') )
                                                    LEAVESEQ
                 name++;
                 maskcpy = &maskcpy[pos + 1];
                 break;
      case '*' : maskcpy = &maskcpy[pos + 1];
                 while ( *maskcpy == '*' ) 
                   maskcpy++;
                 if ( !strcmp(maskcpy,".*") )       ERROR
                 if ( !strcmp(mask,".") && !strchr(name,'.') )
                                                    ERROR
                 if ( !*maskcpy )                   ERROR
                 submask = strdup(maskcpy);
                 submask[strcspn(maskcpy,"*?")] = 0;
                 while ( name = strstr(name,submask) )
                 {
                   if ( filfitsmsk(name,maskcpy) )  ERROR
                   name++;
                 }
                 free(submask);
                 submask = NULL;
                 LEAVESEQ
      default  : ;
    } 

    if ( !strcmp(maskcpy,".*") )                    ERROR
  }

  if ( !strcmp(maskcpy,".") && !*name )             ERROR
  if ( !strcmp(name,maskcpy) )                      ERROR
RECOVER
  term = YES;
ENDSEQ
  if ( submask )
    free(submask);
  free(namedup);
  free(maskdup);
  return(term);
}

/******************************************************************************/
/**
\brief  filifitsmsk - 



\return term - Success

\param  filname - 
\param  mask - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filifitsmsk"

logical __cdecl filifitsmsk (char *filname, char *mask )
{
  char       *namedup = strdup(filname);
  char       *maskdup = strdup(mask);
  char       *name    = namedup;
  char       *maskcpy = maskdup;
  char       *submask = NULL;
  int         pos     = 0;
  logical     term    = NO;
BEGINSEQ
  if ( submask = strrchr(maskcpy,'.') )
    if ( submask[1] )
      if ( strspn(&submask[1],"*") == strlen(&submask[1]) )
        strcpy(submask, ".*");

  while ( submask = strstr(maskcpy,"*?") )
  {
    submask[0] = '?';
    submask[1] = '*';
  };

  while ( (pos = strcspn(maskcpy,"*?")) != strlen(maskcpy) )
  {
    if ( gvtsicmp(name,maskcpy,pos) )               LEAVESEQ

    name = &name[pos];
    switch ( maskcpy[pos] )
    {
      case '?' : if ( !*name || name == strrchr(name,'.') )
                                                    LEAVESEQ
                 name++;
                 maskcpy = &maskcpy[pos + 1];
                 break;
      case '*' : maskcpy = &maskcpy[pos + 1];
                 while ( *maskcpy == '*' ) 
                   maskcpy++;
                 if ( !strcmp(maskcpy,".*") )       ERROR
                 if ( !strcmp(mask,".") && !strchr(name,'.') )
                                                    ERROR
                 if ( !*maskcpy )                   ERROR
                 submask = strdup(maskcpy);
                 submask[strcspn(maskcpy, "*?")] = 0;
                 while ( name = gvtsiscn(name,submask) )
                 {
                   if ( filifitsmsk(name,maskcpy) ) ERROR
                   name++;
                 }
                 free(submask);
                 submask = NULL;
                 LEAVESEQ
      default  : ;
    } 
    if ( !strcmp(maskcpy,".*") )                    ERROR
  }
  
  if ( !strcmp(maskcpy,".") && !*name )             ERROR
  if ( !gvtsicmp(name,maskcpy,0) )                  ERROR

RECOVER
  term = NO;
ENDSEQ
  if ( submask )
    free(submask);
  free(namedup);
  free(maskdup);
  return(term);
}

/******************************************************************************/
/**
\brief  fillen - 



\return len - 

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fillen"

int32 __cdecl fillen (char *cpath )
{
/* DaGnuwwel : term wird nicht benötigt... */
//#ifdef __unix__
  struct stat             status;
//#else
//  logical                 term = NO;
//  FILE                   *fsource;
//#endif
  int32                  len = UNDEF;

BEGINSEQ
//#ifdef __unix__
  if ( stat(cpath,&status) )                         ERROR
  len = status.st_size;
/*
#else
  if ((fsource = fopen(cpath,"rb")) == 0)            ERROR
  len = filelength(fileno(fsource));

  fclose(fsource);
#endif
*/
RECOVER

ENDSEQ
  return(len);
}

/******************************************************************************/
/**
\brief  fillength - 



\return len - 

\param  fhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "fillength"

int32 __cdecl fillength (int fhandle )
{
  struct stat status;
  int32       len = UNDEF;

BEGINSEQ
  if ( fstat(fhandle,&status) )                       ERROR
  len = status.st_size;

RECOVER
  len = 0;
ENDSEQ
  return(len);
}

/******************************************************************************/
/**
\brief  filncat - 



\return cpath - Complete path

\param  cpath - Complete path
\param  string - String value
\param  maxlens - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filncat"

char *__cdecl filncat (char *cpath, char *string, int16 maxlens )
{

BEGINSEQ
  if ( strlen(cpath) + strlen(string) + 1 > maxlens )
                                                     ERROR
  gvtsexc(cpath,"\\","/",UNDEF);
  
  if ( cpath[strlen(cpath)-1] != '/' )
    strcat(cpath,"/");

  if ( string )
    strcat(cpath,string);
RECOVER
  cpath = NULL;
ENDSEQ
  return(cpath);
}

/******************************************************************************/
/**
\brief  filreada - 



\return fillen - 

\param  cpath - Complete path
\param  area - 
\param  arealen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "filreada"

int32 __cdecl filreada (char *cpath, void *area, int32 arealen )
{
  char         path[1025];
  FILE       *fsource;
  int32       fillength;

BEGINSEQ
  strcpy(path,cpath);
  ReplaceSysVariable(path,sizeof(path)-1);

  fillength = fillen(path);
  
  if ((fsource = fopen(path,"rb")) == 0)            ERROR
  
  if ( area )
  {
    if ( !fread(area,MIN(fillength,arealen),1,fsource) )     
                                                     SOSERR(2)
    ((char *)area)[MIN(fillength,arealen)] = 0;
  }

RECOVER
  fillength = 0;
ENDSEQ
  if ( fsource )
    fclose(fsource);
  return(fillength);
}

