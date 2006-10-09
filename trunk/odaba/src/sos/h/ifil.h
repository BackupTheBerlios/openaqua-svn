/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    fil

\brief    


\date     $Date: 2006/07/12 13:26:52,39 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   fil_H
#define   fil_H

#include "csosdll.h"
#define  BUF_LENGTH                                1024*1024
#define  filread                                   FileRead
#define  filwrit                                   FileWrite
class     srt;

#if defined (__cplusplus)
  extern "C" {
#endif

                   logical __cdecl CopyDirect (FILE *fsource, FILE *ftarget, int64 fillength );
SOSImpExp          logical __cdecl CopyFiles (char *source_path, char *target_dir );
SOSImpExp          logical __cdecl CopySingleFile (char *source_path, char *target_path );
SOSImpExp          srt *__cdecl CreateFileTable (char *cpath, char *mask );
SOSImpExp          logical __cdecl FileCopy (char *source_path, char *target_path, logical pack_opt );
SOSImpExp          logical __cdecl FileLock (char *cpath );
SOSImpExp          int32 __cdecl FileRead (char *cpath, void **areaptr );
SOSImpExp          logical __cdecl FileWrite (char *cpath, void *area, int32 fillen );
SOSImpExp          logical __cdecl GetDirectoryPath (char *cpath, char *dpath );
SOSImpExp          logical __cdecl GetDirectoryPathInfo (char *cpath, char *dpath, int16 dpath_len );
SOSImpExp          char *__cdecl GetFileName (char *cpath, char *filname, char *filext );
SOSImpExp          char *__cdecl GetFileNameInfo (char *cpath, char *filname, char *filext, int16 name_len, int16 ext_len );
SOSImpExp          logical __cdecl GetLastFolderInfo (char *cpath, char *dpath, char *folder, int16 dpath_len, int16 folder_len );
SOSImpExp          logical __cdecl IsDirectory (char *cpath );
SOSImpExp          logical __cdecl IsFile (char *cpath );
SOSImpExp          logical __cdecl MakePathDirectories (char *cpath );
                   logical __cdecl PackFile (FILE *fsource, FILE *ftarget, int64 fillength );
SOSImpExp          char *__cdecl ReadTextFile (char *cpath );
                   logical __cdecl UnpackFile (FILE *fsource, FILE *ftarget, int64 fillength );
SOSImpExp          logical __cdecl WriteTextFile (char *cpath, void *area );
                   logical __cdecl filchck (char const * const cpath, char filstat );
SOSImpExp          logical __cdecl filcopy (char *opath, char *npath );
SOSImpExp          logical __cdecl filddel (char *cpath, logical deldir );
SOSImpExp          int __cdecl fildirg (char *cpath, char *drives, char *dirs );
SOSImpExp          char *__cdecl fildpgt (char *path, int16 maxlens );
SOSImpExp          char *__cdecl filevfd (char *envname, char *path );
SOSImpExp          char *__cdecl filevgp (char *filname, char *envname, char *cpath );
SOSImpExp          char *__cdecl filextr (char *path, char *filext );
SOSImpExp          char *__cdecl filfegt (char *cpath, char *filname, char *filext );
SOSImpExp          void *__cdecl filfill (char *cpath, int16 filoffset, int16 readlen, void *area );
                   logical __cdecl filfitsmsk (char *filname, char *mask );
                   logical __cdecl filifitsmsk (char *filname, char *mask );
SOSImpExp          int32 __cdecl fillen (char *cpath );
SOSImpExp          int32 __cdecl fillength (int fhandle );
SOSImpExp          char *__cdecl filncat (char *cpath, char *string, int16 maxlens );
SOSImpExp          int32 __cdecl filreada (char *cpath, void *area, int32 arealen );

#if defined (__cplusplus)
             }
#endif
#endif
