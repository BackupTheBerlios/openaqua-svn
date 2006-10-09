/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    IniFile

\brief    


\date     $Date: 2006/03/12 19:20:03,56 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   IniFile_HPP
#define   IniFile_HPP

class     IniFile;

#include  <sIniFile.hpp>
#include  <sNString.hpp>
#pragma pack(8)

class  IniFile
{
protected  :         int32                                        max_len;                                                   //
protected  :         char                                         file_name[256];                                            //
protected  :         char                                        *ini_string;                                                //
protected  :         char                                        *section;                                                   //
protected  :         char                                         section_name[256];                                         //
protected  :         NString                                      variable_string;                                           //

public     :
                     int32                                        get_max_len() { return(max_len); }
                     char                                        *get_file_name() { return(file_name); }
                     char                                        *get_ini_string() { return(ini_string); }
                     char                                        *get_section() { return(section); }
                     char                                        *get_section_name() { return(section_name); }
                     NString                                     &get_variable_string() { return(variable_string); }
public     :         SOS7ImpExp                  char *GetFileName ( );
public     :         SOS7ImpExp                  char *GetVariable (char *vnames );
public     :         SOS7ImpExp                                          IniFile (char *cpath );
public     :         SOS7ImpExp                                          IniFile (int32 maxlen );
public     :         SOS7ImpExp                                          IniFile (IniFile &inifile );
public     :         SOS7ImpExp                  void Initialize ( );
public     :                                     logical IsEmpty ( );
public     :         SOS7ImpExp                  logical LocateSection (char *names );
public     :         SOS7ImpExp                  logical PutSection (char *names );
public     :         SOS7ImpExp                  logical PutVariable (char *vnames, char *string );
public     :                                     logical ReAllocIniString ( );
public     :         SOS7ImpExp                  logical Refresh ( );
public     :         SOS7ImpExp                  logical Write (char *cpath );
public     :         SOS7ImpExp                                          ~IniFile ( );
};

#pragma pack()
#endif
