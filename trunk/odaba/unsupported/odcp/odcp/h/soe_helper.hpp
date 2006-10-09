/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:39:49,98}|(REF)
\class    oe_helper

\brief    
          funktionen  die das plattformabhaengige zeugs zum dll laden trennen um
          die mainfunktionen frei davon zu halten

          alle funktionen sollten static sein, um ihren aufruf zu vereinfachen

\date     $Date: 2006/03/12 19:40:04,26 $
\dbsource odcp.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   oe_helper_HPP
#define   oe_helper_HPP

class     oe_helper;

class  oe_helper
{

public     :
public     :         ODCP8ImpExp                 void *bindLibFunc (void *pvoid, std_string sname );
public     :         ODCP8ImpExp                 logical closeLibs (std::vector<void*> &dlhandles );
public     :                                     logical help (int argc, char **argv );
public     :         ODCP8ImpExp                 logical loadLib (std::vector<void*> &dlhandles, std_string sname );
public     :                                     logical usage ( );
};

#endif
