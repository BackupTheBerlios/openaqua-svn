/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    ODABAServer

\brief    ODABA Server
          A  ODABA server will manage any number of databases. After creating an
          ODABA  server it can be started and halted using the functions Start()
          and  Stop(). There is no login  required for connecting to the server,
          however,  for  accessing  a  database  you  may  have  to  pass  login
          information  to  the  server.  Login-Information must be passed to the
          CreateClient  function.  You  can  overload  this  function  in  your 
          application  procedure to  provide specific  login checkings and other
          services for an application ODABA2 server. 
          The  ODABA-server  maintains  a  list  (catalogue) for database files.
          This  catalogue  must  be  stored  under  server.ini  in  the  ODABA2 
          installation    path.    The    catalogue    section    starts    with
          [ODABA-CATALOGUE].

\date     $Date: 2006/03/12 19:10:02,00 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODABAServer_HPP
#define   ODABAServer_HPP

class     ODABAServer;

class     CServer;
#pragma pack(8)

class  ODABAServer
{
protected  :         CServer                                     *odaba_server;                                              

public     :
                     CServer                                     *get_odaba_server() { return(odaba_server); }
public     :                                     logical Close ( );
public     :         OPI7ImpExp                  logical Continue ( );
public     :         OPI7ImpExp                  char *GetCatlgName (char *sym_nams, char *cpath, uint32 maxlen );
public     :         OPI7ImpExp                  logical IsRunning ( );
public     :         OPI7ImpExp                                          ODABAServer (char *inipath, char *prog_path );
public     :         OPI7ImpExp                                          ODABAServer ( );
public     :         OPI7ImpExp                  logical Open (char *inipath, char *prog_path );
public     :         OPI7ImpExp                  logical Pause ( );
public     :         OPI7ImpExp                  logical Start (int16 wPort );
public     :         OPI7ImpExp                  void Stop ( );
public     :         OPI7ImpExp                                          ~ODABAServer ( );
};

#pragma pack()
#endif
