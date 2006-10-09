#include <iostream.h>
#include <puti.h>
#include <ifil.h>
#include  <sODABAServer.hpp> 
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <fstream>
#define NULL ((void*)0)

int run;
const char* pidf="/var/run/odabaserverd.pid";

void HDLTERM (int i)
{
  run = 0;
}
int Clean(){
  if ( remove(pidf) )
  {
    puts(strerror(errno));
    return -1;
  }
  return 1;
}

int StopDeamon ()
{
  pid_t deamonid;
  std::ifstream f(pidf,std::ios::in);
  if(f.bad()) {
    Clean();
    return -1;
  }
  f >> deamonid;
  f.close();
  
  Clean();
  if ( kill(deamonid, SIGTERM) )
  {
    puts(strerror(errno));
    return -1;
  }
  puts("serverd stoped");
  return 1;
}

void StartDeamon(char* spath, char* inifile, long port)
{
  run=1;
  if ( setsid() == -1 )
  {
    puts(strerror(errno));
    return;
  } 
  ODABAServer    server(inifile,spath);

  server.Start(port);

  while (run) pause();

  server.Stop();
  free(spath);
  free(inifile);
} 

int main (int argc, char* argv[])
{

  int    port    = 6123;
  char * spath   = strdup(argv[0]);
  char * inifile = strdup("server.ini");

  if ( argc > 1 )
  {
    if( !strcmp(argv[1], "--kill")
    ||  !strcmp(argv[1], "-k") )
      return StopDeamon();
    
    if ( !(port = atol(argv[1])) )
    {
      puts("invalid port");
      puts(argv[1]);
      return -1;
    }
  }

  if ( argc > 2 )
  {
    inifile = strdup(argv[2]);
  }
  
  if ( !filchck(pidf, 'F') )
  {
    puts("serverd is already runnig");
    return -1;
  }

  pid_t child;
  signal(SIGTERM, HDLTERM);
  switch ( (child = fork()) )
  {
    case -1 : puts("unable to fork");
              puts(strerror(errno));
              return -1;
    case  0 : StartDeamon(spath, inifile, port); break;
    default : std::ofstream f(pidf,std::ios::out);
              f << child;
	      f.close();
  }
  return 0;
}