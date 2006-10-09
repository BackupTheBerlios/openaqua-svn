/********************************* Class Source Code ***************************/
/**
\package  ODCP - 
\class    oe_helper

\brief    
          funktionen  die das plattformabhaengige zeugs zum dll laden trennen um
          die mainfunktionen frei davon zu halten

          alle funktionen sollten static sein, um ihren aufruf zu vereinfachen

\date     $Date: 2006/07/05 14:04:39,79 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "oe_helper"

#include  <podcp8.h>
#include  <unxdl.h>
#include  <standard.hpp>
#include  <soe_helper.hpp>


/******************************************************************************/
/**
\brief  bindLibFunc - 



\return pvoid - 

\param  pvoid - 
\param  sname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bindLibFunc"

void *oe_helper :: bindLibFunc (void *pvoid, std_string sname )
{
  void*              ret = NULL;
  std::string        dlerr;
BEGINSEQ
#ifdef __unix__
    ret = dlsym(pvoid, sname.c_str());
    // sorry for this construction dlerror can return NULL, string does not like that!
    char* tdlerr = dlerror();
    if(tdlerr)  dlerr = std::string(tdlerr);
    if (!dlerr.empty()) {
      /* handle error, the symbol wasn't found */
      std::cerr << "! error finding " << sname << ": " << dlerr << std::endl;
      ERROR
    }
#else
  if(!pvoid)                                         ERROR
  ret = GetProcAddress((HINSTANCE)pvoid,sname.c_str());
  if(!ret){
    //TODO: get&write error messages
    ERROR
  }
#endif
RECOVER
  exit(1); // end the program with errorcode
ENDSEQ
  return ret;
}

/******************************************************************************/
/**
\brief  closeLibs - 



\return term - 

\param  dlhandles - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "closeLibs"

logical oe_helper :: closeLibs (std::vector<void*> &dlhandles )
{
  logical                 term = NO;
  std::vector<void*>::iterator it;

#ifdef __unix__  
  for(it = dlhandles.begin();it!=dlhandles.end();it++){
    term |= dlclose((*it));
    // nonzero on error
  }
  dlhandles.clear();
#else
  // afaik this system cannot  close loaded dlls
#endif
  return(term);
}

/******************************************************************************/
/**
\brief  help - finds out if there is the request of help



\return term - 

\param  argc - 
\param  argv - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "help"

logical oe_helper :: help (int argc, char **argv )
{
  logical                 term = NO;
  std::string             parm;
BEGINSEQ
  for(int i = 0; i<argc;i++)
    if(argv[i]){
      parm = std::string(argv[i]);
      if(  parm.find("--help") != std::string::npos
         ||parm.find("-h") != std::string::npos
         ||parm.find("/?") != std::string::npos
        ){
        usage();
        ERROR
        }
    }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  loadLib - 



\return term - 

\param  dlhandles - 
\param  sname - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "loadLib"

logical oe_helper :: loadLib (std::vector<void*> &dlhandles, std_string sname )
{
  logical                 term = NO;
  std::string             name,fullname,opath;
  void                   *handle = NULL;
BEGINSEQ
#ifdef __unix__
  name = "lib" + sname + ".so";
  handle = dlopen (name.c_str(), RTLD_NOW);
  if (!handle) {
    std::cerr << dlerror() << std::endl;
    ERROR
  }
  dlerror(); /* clear error code */  
#else
  opath = ""; // weird thing from given INI file
  fullname = opath + sname + ".dll";
  name     = sname + ".dll";
  if ( !(handle = LoadLibrary(fullname.c_str())) ){
    SetErrorMode(0);
    handle = LoadLibrary(name.c_str());
  }
  if(!handle) // text from Mo$
    ERROR
#endif
  // remember the handle for later unload
  
  dlhandles.push_back(handle);
  handle = NULL;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  usage - dumps the usage to the cout



\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "usage"

logical oe_helper :: usage ( )
{
  logical                 term = NO;
std::cout << " - Qt Options - " << std::endl;
std::cout << " * -style= style, sets the application GUI style." << std::endl;
std::cout << "    Possible values are motif, windows, and platinum." << std::endl;
std::cout << "    If you compiled Qt with additional styles or have additional styles" << std::endl;
std::cout << "    as plugins these will be available to the -style command line option." << std::endl;
std::cout << " * -style style, is the same as listed above." << std::endl;
std::cout << " * -session= session, restores the application from an earlier session." << std::endl;
std::cout << " * -session session, is the same as listed above." << std::endl;
std::cout << " * -widgetcount, prints debug message at the end about number of widgets" << std::endl;
std::cout << "    left undestroyed and maximum number of widgets existed at the same time" << std::endl;
#ifdef __unix__
std::cout << std::endl << " ---------------------------- " << std::endl;
std::cout << " - Qt X11 Options - " << std::endl;
std::cout << " * -display display, sets the X display (default is $DISPLAY)." << std::endl;
std::cout << " * -geometry geometry, sets the client geometry of the first window that is shown." << std::endl;
std::cout << " * -fn or -font font, defines the application font. The font should be specified using an X logical font description." << std::endl;
std::cout << " * -bg or -background color, sets the default background color and an application palette (light and dark shades are calculated)." << std::endl;
std::cout << " * -fg or -foreground color, sets the default foreground color." << std::endl;
std::cout << " * -btn or -button color, sets the default button color." << std::endl;
std::cout << " * -name name, sets the application name." << std::endl;
std::cout << " * -title title, sets the application title." << std::endl;
std::cout << " * -visual TrueColor, forces the application to use a TrueColor visual on an 8-bit display." << std::endl;
std::cout << " * -ncols count, limits the number of colors allocated in the color cube on an 8-bit display, if the application is using the QApplication::ManyColor color specification. If count is 216 then a 6x6x6 color cube is used (i.e. 6 levels of red, 6 of green, and 6 of blue); for other values, a cube approximately proportional to a 2x3x1 cube is used." << std::endl;
std::cout << " * -cmap, causes the application to install a private color map on an 8-bit display." << std::endl;
#endif
std::cout << std::endl << " ---------------------------- " << std::endl;
std::cout << " - [c|w]oe ini-file [options] " << std::endl;
std::cout << " (c) 1995 - 2006 RuN-Software GmbH" << std::endl;
std::cout << " [console|windows]object environment" << std::endl;
std::cout << "  binary name is usaly the name of a section in the" << std::endl;
std::cout << "  given ini-file" << std::endl << std::endl;
  return(term);
}


