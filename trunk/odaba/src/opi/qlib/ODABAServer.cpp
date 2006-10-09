/********************************* Class Source Code ***************************/
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

\date     $Date: 2006/03/12 19:10:32,01 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODABAServer"

#include  <pdefault.h>
#include  <sCServer.hpp>
#include  <sODABAServer.hpp>


/******************************************************************************/
/**
\brief  Close

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical ODABAServer :: Close ( )
{

  delete odaba_server;
  odaba_server = NULL;
  return(NO);
}

/******************************************************************************/
/**
\brief  Continue

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Continue"

logical ODABAServer :: Continue ( )
{

  StopPause();
  return(NO);

}

/******************************************************************************/
/**
\brief  GetCatlgName - Get database name from catalogue
        The  function  returns  the  database  path  for  a symbolic name in the
        catalogue  (server.ini). If  no catalogue  entry with  the given name is
        found the function returns the original name.

\return filenames -

\param  sym_nams -
\param  cpath - Complete path
\param  maxlen - Size of output buffer
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCatlgName"

char *ODABAServer :: GetCatlgName (char *sym_nams, char *cpath, uint32 maxlen )
{

  return(odaba_server->GetCatlgName(sym_nams,cpath,maxlen));

}

/******************************************************************************/
/**
\brief  IsRunning

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsRunning"

logical ODABAServer :: IsRunning ( )
{

  return(odaba_server->IsRunning());

}

/******************************************************************************/
/**
\brief  ODABAServer - Constructor
        The  function creates an ODABA server. The INI-file passed to the server
        contains  information about the system databases and the data catalogue.
        The  programme path is used for searching actions and should be provided
        when other iINI-files or DLLs are to be loaded from this path.

-------------------------------------------------------------------------------
\brief i0


\param  inipath -
\param  prog_path - Programme path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODABAServer"

                        ODABAServer :: ODABAServer (char *inipath, char *prog_path )
                     :   odaba_server(NULL)
{

  Open(inipath,prog_path);

}

/******************************************************************************/
/**
\brief i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODABAServer"

                        ODABAServer :: ODABAServer ( )
                     :   odaba_server(NULL)
{



}

/******************************************************************************/
/**
\brief  Open

\return term - Termination code

\param  inipath -
\param  prog_path - Programme path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical ODABAServer :: Open (char *inipath, char *prog_path )
{
  logical        term = NO;
BEGINSEQ
  if ( !(odaba_server = new CServer(inipath,prog_path)) )
                                                     SDBERR(95)
                                                     SDBCERR

RECOVER
  Close();
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Pause

\return term - Termination code

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Pause"

logical ODABAServer :: Pause ( )
{

  return(StartPause(UNDEF));

}

/******************************************************************************/
/**
\brief  Start - Start server


\return term - Termination code

\param  wPort -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Start"

logical ODABAServer :: Start (int16 wPort )
{

  return(odaba_server->Start(wPort));


}

/******************************************************************************/
/**
\brief  Stop - Stop server
        When  stopping the server all client  connections are closed. You should
        ensure that no client is active anymore.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Stop"

void ODABAServer :: Stop ( )
{

  odaba_server->Stop();

}

/******************************************************************************/
/**
\brief  ~ODABAServer - Destructor
        When  destructing  the  server  it  is  stopped  if not done so far. You
        should ensure that no client is active anymore.


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~ODABAServer"

                        ODABAServer :: ~ODABAServer ( )
{

  Close();

}


