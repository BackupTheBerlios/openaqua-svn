/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    IniFile

\brief    


\date     $Date: 2006/07/12 19:08:31,32 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "IniFile"

#include  <pdefault.h>
#include  <igvts.h>
#include  <sNString.hpp>
#include  <ifil.h>
#include  <sIniFile.hpp>


/******************************************************************************/
/**
\brief  GetFileName - 


\return filename - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFileName"

char *IniFile :: GetFileName ( )
{

  if (this == 0) return file_name;
  else return "";

}

/******************************************************************************/
/**
\brief  GetVariable - 


\return vtext - 

\param  vnames - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetVariable"

char *IniFile :: GetVariable (char *vnames )
{


  char *DataBegin; 
  int   DataLenght; 
  char *SearchString = new char[strlen(vnames) + 4];
  char        *vtext = NULL;
BEGINSEQ
  if ( !section )                                    ERROR
    
  strcpy(SearchString, "\n");
  strcat(SearchString, vnames);
  strcat(SearchString, "=");
  
  if ( !(DataBegin = gvtsiscn(section, SearchString)) )ERROR
    
  DataBegin  = &DataBegin[strlen(SearchString)-1];
  DataLenght = strcspn(DataBegin, "\n");
  while ( DataBegin[--DataLenght] < 33 ) ;
  DataBegin++;
  char BackupChar = DataBegin[DataLenght];
  DataBegin[DataLenght] = 0;
  variable_string = DataBegin;
  DataBegin[DataLenght] = BackupChar;
  
  vtext = variable_string;
RECOVER
  vtext = NULL;
ENDSEQ
  delete SearchString;
  return(vtext);
}

/******************************************************************************/
/**
\brief  IniFile - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IniFile"

     IniFile :: IniFile (char *cpath )
                     : max_len(),
  ini_string(NULL),
  section(NULL),
  variable_string(255)
{


  SOSRESET
  
  strncpy(file_name, cpath, sizeof(file_name));
  Initialize();
  strcpy(section_name, "");



}

/******************************************************************************/
/**
\brief  i02 - 


\param  maxlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IniFile"

     IniFile :: IniFile (int32 maxlen )
                     : max_len(maxlen),
  file_name(),
  ini_string(NULL),
  section(NULL),
  section_name(),
  variable_string(255)
{

BEGINSEQ
  *file_name       = 0;
  *section_name    = 0;
  variable_string  = "";
  
  if ( !(ini_string = new char[max_len]) )           SOSERR(95) 
  strcpy(ini_string, "\n");

RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  i1 - 


\param  inifile - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IniFile"

     IniFile :: IniFile (IniFile &inifile )
                     : max_len(),
  ini_string(NULL),
  section(NULL),
  variable_string(255)
{


  strcpy(file_name,inifile.get_file_name());
  Initialize();
  
  LocateSection(inifile.get_section_name());


}

/******************************************************************************/
/**
\brief  Initialize - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

void IniFile :: Initialize ( )
{
  char *area = NULL;
  SOSEV2(file_name,UNDEF)
  
  delete ini_string;
  ini_string = new char[filread(file_name, (void**)&area) + 2];
  strcpy(ini_string, "\n");
  if ( area )
    strcat(ini_string, area);
  
  variable_string  = "";

  delete area;
}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical IniFile :: IsEmpty ( )
{

  return(ini_string && strlen(ini_string) > 2 ? NO : YES);

}

/******************************************************************************/
/**
\brief  LocateSection - 


\return term - Success

\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LocateSection"

logical IniFile :: LocateSection (char *names )
{
  char *SectionBegin; 
  char *SectionEnd; 
  char *SearchString = new char[strlen(names) + 4];
  logical term = NO;

BEGINSEQ
  strncpy(section_name, names ? names : "", sizeof(section_name));
  delete section;
  section = NULL;
  
  if ( !*section_name )                              LEAVESEQ
    
  strcpy(SearchString, "\n[");
  strcat(SearchString, section_name);
  strcat(SearchString, "]");
  
  if ( !(SectionBegin = gvtsiscn(ini_string, SearchString)) )
                                                     ERROR
  SectionBegin = &SectionBegin[strlen(SearchString)];
  if ( !(SectionEnd = strstr(SectionBegin, "\n[")) )
    SectionEnd = &SectionBegin[strlen(SectionBegin)];
  char BackupChar = SectionEnd[0];
  SectionEnd[0] = 0;
  section = new char[strlen(SectionBegin) + 1];
  strcpy(section, SectionBegin);
  SectionEnd[0] = BackupChar;

RECOVER
  term = YES;

ENDSEQ
  delete SearchString;
  return term;

}

/******************************************************************************/
/**
\brief  PutSection - 


\return term - Success

\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PutSection"

logical IniFile :: PutSection (char *names )
{
  int32       need_len = strlen(ini_string) + strlen(names) + 7;
  logical     term     = NO;
BEGINSEQ
  if ( need_len > max_len )
    if ( ReAllocIniString() )                        ERROR
  if ( need_len > max_len )                          SOSERR(95)

  if ( strlen(ini_string) > 2 )
    strcat(ini_string,"\r\n\r\n");

  strcat(strcat(strcat(ini_string,"["),names),"]");

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PutVariable - 


\return term - Success

\param  vnames - 
\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PutVariable"

logical IniFile :: PutVariable (char *vnames, char *string )
{
  int32       need_len = strlen(ini_string) + strlen(vnames) + strlen(string) + 5;
  logical     term     = NO;
BEGINSEQ
  if ( need_len > max_len )
    if ( ReAllocIniString() )                        ERROR
  if ( need_len > max_len )                          SOSERR(95)

  strcat(strcat(strcat(strcat(ini_string,"\r\n"),vnames),"="),string);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReAllocIniString - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReAllocIniString"

logical IniFile :: ReAllocIniString ( )
{
  char       *old_string = ini_string;
  logical     term       = NO;
BEGINSEQ
  if ( !(ini_string = new char[(max_len*=2)]) )      SOSERR(95)
  
  strcpy(ini_string,old_string);
  delete old_string;  

RECOVER
  ini_string = old_string;
  term       = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Refresh - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Refresh"

logical IniFile :: Refresh ( )
{
  logical                 term = NO;
  Initialize();
  LocateSection(section_name);
  return(term);
}

/******************************************************************************/
/**
\brief  Write - 


\return term - Success

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Write"

logical IniFile :: Write (char *cpath )
{

  return ( filwrit(cpath,ini_string+1,strlen(ini_string)-1) );


}

/******************************************************************************/
/**
\brief  ~IniFile - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~IniFile"

     IniFile :: ~IniFile ( )
{

  delete section;
  delete ini_string;

}


