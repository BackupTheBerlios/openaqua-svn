/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    XMLAttribute

\brief    XML attribute description
          The  attribute description  describes an  attribute of an XML element.
          Predefined  attributes own the attribute names and can be created with
          the name-constructor.

\date     $Date: 2006/03/12 19:20:21,89 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   XMLAttribute_HPP
#define   XMLAttribute_HPP

class     XMLAttribute;

#include  <sNString.hpp>
#include  <sXMLAttribute.hpp>
#include  <sXMLValue.hpp>
#pragma pack(8)

class  XMLAttribute :public XMLValue
{
protected  :         logical                                      has_quotes ATTR_ALIGN(4);                                  

public     :
                     logical                                      get_has_quotes() { return(has_quotes); }
public     :                                     char *GetAttribute ( );
public     :                                     logical IsValid ( );
public     :                                     void Reset ( );
public     :                                     logical SetName (char *string, int32 slen );
public     :                                     logical SetValue (char *string, int32 slen, logical quotes );
public     :                                                             XMLAttribute ( );
public     :                                                             XMLAttribute (char *names );
public     :         SOS7ImpExp                  XMLValue &operator= (char *string );
public     :         SOS7ImpExp                  XMLValue &operator= (int32 int_val );
public     :                                                             ~XMLAttribute ( );
};

#pragma pack()
#endif
