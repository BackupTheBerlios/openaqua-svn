/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    RegistryKey

\brief    


\date     $Date: 2006/03/12 19:20:15,93 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   RegistryKey_HPP
#define   RegistryKey_HPP

class     RegistryKey;

#include  <sDLL.h>
class     RegistryKey;
class     RegistryKey;
#include  <sNString.hpp>
class  RegistryKey
{
protected  :         HKEY                                         hkey;                                                      //
protected  :         char                                        *path;                                                      //
protected  :         DLL(RegistryKey)                            *sub_keys;                                                  //
protected  :         RegistryKey                                 *parent;                                                    //
protected  :         logical                                      opened;                                                    //
protected  :         NString                                      value;                                                     //

public     :
                     HKEY                                        &get_hkey() { return(hkey); }
                     char                                        *get_path() { return(path); }
                     DLL(RegistryKey)                            *get_sub_keys() { return(sub_keys); }
                     RegistryKey                                 *get_parent() { return(parent); }
                     logical                                      get_opened() { return(opened); }
                     NString                                     &get_value() { return(value); }
public     :         SOS7ImpExp                  void Close ( );
public     :         SOS7ImpExp                  RegistryKey *CreateSubKey (char *key_path );
public     :         SOS7ImpExp                  char *GetFilePath (char *key_path, char *reg_value, char *file_name );
public     :         SOS7ImpExp                  char *GetStringValue (char *key_path, char *reg_value );
public     : static  SOS7ImpExp                  char *__cdecl GetWinwordPath ( );
public     :         SOS7ImpExp                  logical Open (char *key_path );
public     :         SOS7ImpExp                                          RegistryKey (HKEY key_handle, char *key_path );
public     :         SOS7ImpExp                                          RegistryKey ( );
public     :         SOS7ImpExp                                          ~RegistryKey ( );
};

#endif
