#ifndef __unix__
/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    RegistryKey

\brief    


\date     $Date: 2006/07/12 19:08:45,76 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "RegistryKey"

#include  <pdefault.h>
#include  <windows.h>
#ifndef   DLL_RegistryKey_HPP
#define   DLL_RegistryKey_HPP
#include  <sRegistryKey.hpp>
#include  <sDLL.h>
#endif
#include  <sRegistryKey.hpp>
#include  <sRegistryKey.hpp>


/******************************************************************************/
/**
\brief  Close - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void RegistryKey :: Close ( )
{
  RegistryKey    *reg_key = NULL;
  while ( reg_key = sub_keys->RemoveTail() )
    delete reg_key;
  
  if ( path )
    free(path);
  path = NULL;
    
  if ( opened ) 
    RegCloseKey(hkey);

  hkey   = 0;
  opened = NO;


}

/******************************************************************************/
/**
\brief  CreateSubKey - 


\return pRegistryKey - 

\param  key_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CreateSubKey"

RegistryKey *RegistryKey :: CreateSubKey (char *key_path )
{
  RegistryKey     *reg_key = NULL;
BEGINSEQ
  if ( !(reg_key = new RegistryKey()) )              SOSERR(95)
  
  reg_key->parent = this;
  sub_keys->AddTail(reg_key);
  
  if ( reg_key->Open(key_path) )                     ERROR

RECOVER
  delete reg_key;
  reg_key = NULL;
ENDSEQ
  return(reg_key);
}

/******************************************************************************/
/**
\brief  GetFilePath - 


\return cpath - Complete path

\param  key_path - 
\param  reg_value - 
\param  file_name - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFilePath"

char *RegistryKey :: GetFilePath (char *key_path, char *reg_value, char *file_name )
{
  char            *str_value = NULL;
BEGINSEQ
  if ( !GetStringValue(key_path,reg_value) )         ERROR
  
  if ( file_name && *file_name )
  {
    value += "\\";
    value += file_name;
  }
  
  if ( !IsFile(value) )                              ERROR

  str_value = value;
RECOVER
  value = "";
ENDSEQ
  return(str_value);
}

/******************************************************************************/
/**
\brief  GetStringValue - 


\return string - String value

\param  key_path - 
\param  reg_value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringValue"

char *RegistryKey :: GetStringValue (char *key_path, char *reg_value )
{
  RegistryKey     *reg_key   = this;
  char             string[2000];
  LPBYTE           varea     = (LPBYTE)&string[0];
  DWORD            vsize     = sizeof(string);
  DWORD            vtype     = 0;
  char            *str_value = NULL;

BEGINSEQ
  value = "";
  
  if ( key_path )
    if ( !(reg_key = CreateSubKey(key_path)) )       ERROR
  
  if ( !reg_value )
    reg_value = "";

  if ( RegQueryValueEx(reg_key->get_hkey(),reg_value,0,&vtype,varea,&vsize) != ERROR_SUCCESS )
                                                     ERROR
  if ( vtype != REG_SZ && vtype != REG_EXPAND_SZ || !strlen(string) )
                                                     ERROR
  value    += string;
  str_value = value;  

RECOVER

ENDSEQ
  return(str_value);
}

/******************************************************************************/
/**
\brief  GetWinwordPath - 


\return cpath - Complete path

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetWinwordPath"

char *__cdecl RegistryKey :: GetWinwordPath ( )
{
  RegistryKey   reg_key(HKEY_LOCAL_MACHINE,NULL);
  char         *word_path = NULL;
BEGINSEQ
  if ( !reg_key.GetFilePath("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\Winword.exe","",NULL)  &&
       !reg_key.GetFilePath("Software\\Microsoft\\Office\\11.0\\Common\\InstallRoot","Path","Winword.exe") &&
       !reg_key.GetFilePath("Software\\Microsoft\\Office\\10.0\\Common\\InstallRoot","Path","Winword.exe") &&
       !reg_key.GetFilePath("Software\\Microsoft\\Office\\9.0\\Common\\InstallRoot","Path","Winword.exe")     )
                                                     ERROR
  word_path = strdup(reg_key.get_value());
RECOVER

ENDSEQ
  return(word_path);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Success

\param  key_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical RegistryKey :: Open (char *key_path )
{
  logical                 term = NO;
BEGINSEQ
  Close();
  
  if ( !parent )                                     ERROR
  
  if ( RegOpenKeyEx(parent->get_hkey(),key_path,0,KEY_READ,&hkey) != ERROR_SUCCESS )
                                                     ERROR
  path   = strdup(key_path);
  opened = YES;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RegistryKey - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  key_handle - 
\param  key_path - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegistryKey"

     RegistryKey :: RegistryKey (HKEY key_handle, char *key_path )
                     :   hkey(0),
  path(NULL),
  sub_keys(new DLL(RegistryKey)),
  parent(NULL),
  opened(NO)
{

  hkey = key_handle;

  if ( key_path )
    path = strdup(key_path);

}

/******************************************************************************/
/**
\brief  i01 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RegistryKey"

     RegistryKey :: RegistryKey ( )
                     :   hkey(0),
  path(NULL),
  sub_keys(new DLL(RegistryKey)),
  parent(NULL),
  opened(NO)
{



}

/******************************************************************************/
/**
\brief  ~RegistryKey - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~RegistryKey"

     RegistryKey :: ~RegistryKey ( )
{

  Close();

  delete sub_keys;
  sub_keys = NULL;
    
  if ( parent && parent->get_sub_keys()->Find(this) )
    parent->get_sub_keys()->RemoveAt();


}


#endif //ndef __unix__
