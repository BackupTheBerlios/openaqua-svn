#ifndef __unix__
//******************************************************************/
//* ODABAServer
//*
//*               ODABA II - Main Function Code
//*                          from  L:/OPI7/OPI7.dev
//*  PD Version 2.0                                     2006/02/20
//******************************************************************/

#define    OBJ_ID  "ODABAServer"

#include  <puti.h>
 
 
 
#include  <sWinODABAService.hpp>





//******************************************************************/
//* WinMain             - 
//*
//* RETURN
//*   rc                - 
//*
//* PARAMETERS
//*
//******************************************************************/


#undef     MOD_ID
#define    MOD_ID  "WinMain"

int APIENTRY WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )

{
  int                   rc = 0;
  char                 *sname;
  char                 *sdname;
  char                 *description;
  char                  command;
  char                  inifile[1000];
  char                 *parms;
  char                  string[256];
  char                 *pos;


  if ( !memcmp(lpCmdLine,"-I",2) || !memcmp(lpCmdLine,"-i",2) ) 
  {
    command = 'I';
    lpCmdLine += 2;
  }
  else if ( !memcmp(lpCmdLine,"-U",2) || !memcmp(lpCmdLine,"-u",2)) 
  {
    command = 'U';
    lpCmdLine += 2;
  }
  
  while ( *lpCmdLine && *lpCmdLine == ' ' )
    *lpCmdLine++;
  
  if ( *lpCmdLine == '"' )
  {
    pos = gvtsfbp(lpCmdLine,UNDEF);
    lpCmdLine++;
  }
  else
    if ( !(pos = strchr(lpCmdLine,' ')) )
      pos = lpCmdLine + strlen(lpCmdLine);
      
  memset(inifile,0,sizeof(inifile));
  memcpy(inifile,lpCmdLine,pos-lpCmdLine);
  
  svel      variables(20);
  variables.svelfini(inifile,"ODABAServer");
  sname = variables.svelget("NAME");
  sdname = variables.svelget("DISPLAY_NAME");
  description = variables.svelget("DESCRIPTION");
  
  WinODABAService       service(sname,sdname,description);
  if ( command == 'I' )
  {
    strcpy(string,"Server installation");
    rc = service.Install(NULL,NULL,SERVICE_DEMAND_START,lpCmdLine);
  }
  else if ( command == 'U' )
  {
    strcpy(string,"Server de-installation");
    rc = service.Uninstall();
  }
  else
  {
    strcpy(string,"Server test");
    service.SetCommandParms(lpCmdLine);
    rc = OService::WinServiceMain();
  }
  if ( rc )
    strcat(string," terminated with errors");
  else
    strcat(string," terminated successfully");  

  MessageBox(NULL, string, "Register ODABA Server", MB_ICONINFORMATION);




  return(rc);
}
#endif //ndef __unix__
