/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    XMLString

\brief    XML text string
          The  class  supports  parsing  an  XML text string for tags. It allows
          returning XML tags from a string.

\date     $Date: 2006/06/11 11:57:58,84 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   XMLString_HPP
#define   XMLString_HPP

#include "csosdll.h"

class     XMLString;

#include  <sNString.hpp>
#include  <sXMLElement.hpp>
#pragma pack(8)

class  XMLString :public XMLElement
{
protected  :         char                                        *path;                                                      // 
protected  :         FILE                                        *file;                                                      // 
protected  :         NString                                      text;                                                      // 
protected  :         logical                                      owner;                                                     // 

public     :
                     char                                        *get_path() { return(path); }
                     NString                                     &get_text() { return(text); }
                     logical                                      get_owner() { return(owner); }
public     :                  SOSImpExp             void Close ( );
public     :                                        char *GetString ( );
public     :                  SOSImpExp             logical Open (char *string, int32 slen );
public     :                  SOSImpExp             logical Open (char *cpath );
public     :                  SOSImpExp             logical PrintStructure (char *cpath );
public     :                  SOSImpExp             logical ReplaceElement (XMLElement *xelement, char *string, int32 maxlen );
public     :                  SOSImpExp             void Save (char *cpath );
public     :                  SOSImpExp                  XMLString (char *string, int32 slen );
public     :                  SOSImpExp                  XMLString (char *cpath );
public     :                  SOSImpExp                  XMLString ( );
public     :                  SOSImpExp                  ~XMLString ( );
};

#pragma pack()
#endif
