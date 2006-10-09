/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    XMLElement

\brief    XML element
          An  XML element describes  the attribute area,  the type and the value
          for  an XML element.  Strings are referenced  in the original text and
          should not me replaced.

\date     $Date: 2006/06/29 12:07:30,28 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   XMLElement_HPP
#define   XMLElement_HPP

#include "csosdll.h"
class     XMLElement;

#ifndef   DPA_XMLAttribute_HPP
#define   DPA_XMLAttribute_HPP
#include  <sXMLAttribute.hpp>
#include  <sDPA.h>
#endif
#ifndef   DPA_XMLElement_HPP
#define   DPA_XMLElement_HPP
#include  <sXMLElement.hpp>
#include  <sDPA.h>
#endif
class     NString;
class     XMLAttribute;
class     XMLElement;
#include  <sXMLValue.hpp>
#pragma pack(8)

class  XMLElement :public XMLValue
{
protected  :         char                                        *begin;                                                     // 
protected  :         char                                        *options;                                                   // 
protected  :         int32                                        options_len;                                               // 
protected  :         char                                        *end;                                                       // 
protected  :         int32                                        current_elm;                                               // 
protected  :         char                                        *current_pos;                                               // 
protected  :         DPA(XMLAttribute)                            attributes;                                                // 
protected  :         DPA(XMLElement)                              elements;                                                  // 
protected  :         logical                                      elmnt_filled;                                              // 
protected  :         logical                                      attr_filled;                                               // 

public     :
                     char                                        *get_begin() { return(begin); }
                     char                                        *get_options() { return(options); }
                     int32                                        get_options_len() { return(options_len); }
                     char                                        *get_end() { return(end); }
                     int32                                        get_current_elm() { return(current_elm); }
                     DPA(XMLAttribute)                           &get_attributes() { return(attributes); }
                     DPA(XMLElement)                             &get_elements() { return(elements); }
public     :                  SOSImpExp             XMLAttribute *AddAttribute (char *names );
public     :                  SOSImpExp             XMLAttribute *AddAttribute (char *names, char *string );
public     :                  SOSImpExp             XMLElement *AddElement (char *names );
public     :                  SOSImpExp             XMLElement *AddElement (char *names, char *string );
public     :                  SOSImpExp             void Close ( );
public     :                  SOSImpExp             logical FillAttributes (logical predefined );
public     :                  SOSImpExp             logical FillElements (logical predefined );
public     :                                        char *FindElementEnd (char *element_name, int32 element_len, char *string );
public     :                  SOSImpExp             XMLAttribute *GetAttribute (int32 indx0 );
public     :                  SOSImpExp             XMLAttribute *GetAttribute (char *names );
public     :                  SOSImpExp             XMLAttribute *GetAttribute (char *ns_prefix, char *names );
public     :                  SOSImpExp             char *GetAttributeValue (char *ns_prefix, char *names );
public     :                  SOSImpExp             char *GetAttributeValue (char *names );
public     :                  SOSImpExp             char *GetAttributes ( );
public     :                  SOSImpExp             XMLElement *GetCurrentElement ( );
public     :                  SOSImpExp             XMLElement *GetElement (int32 indx0 );
public     :                  SOSImpExp             XMLElement *GetElement (char *names );
public     :                  SOSImpExp             XMLElement *GetElement (char *ns_prefix, char *names );
public     :                  SOSImpExp             int32 GetElementCount ( );
public     :                  SOSImpExp             XMLElement *GetElementRecursive (char *names );
public     :                                        char *GetEndTag ( );
public     :                  SOSImpExp             XMLElement *GetNextElement ( );
public     :                                        char *GetStart ( );
public     :                                        char *GetStartTag ( );
public     :                                        logical GetString (NString &n_string, int32 level );
public     :                  SOSImpExp             int8 GetStringLength ( );
public     :                  SOSImpExp             logical GetTextData (NString &n_string, logical &par_ref );
public     :                  SOSImpExp             int8 GetTypeNumber (char *symbol1, char *symbol2=NULL, char *symbol3=NULL, char *symbol4=NULL, char *symbol5=NULL, char *symbol6=NULL, char *symbol7=NULL, char *symbol8=NULL, char *symbol9=NULL, char *symbol10=NULL, char *symbol11=NULL, char *symbol12=NULL, char *symbol13=NULL, char *symbol14=NULL, char *symbol15=NULL );
public     :                                        void InitString (NString &n_string, int32 level );
public     :                                        logical InvalidateAttributes ( );
public     :                                        logical InvalidateElements ( );
public     :                  SOSImpExp             logical IsAttributeValueTrue (char *ns_prefix, char *names );
public     :                  SOSImpExp             logical IsAttributeValueTrue (char *names );
public     :                  SOSImpExp             logical IsComment ( );
public     :                  SOSImpExp             logical IsElement (char *ns_prefix, char *names );
public     :                  SOSImpExp             logical IsValid ( );
public     :                  SOSImpExp             logical IsVersion ( );
public     :                  SOSImpExp             XMLElement *NextElement (logical structured );
public     :                                        logical Print (FILE *file, char *names, int32 level );
public     :                  SOSImpExp             XMLAttribute *ProvideAttribute (int32 indx0 );
public     :                  SOSImpExp             XMLAttribute *ProvideAttribute (char *names );
public     :                  SOSImpExp             XMLElement *ProvideElement (int32 indx0 );
public     :                  SOSImpExp             XMLElement *ProvideElement (char *names );
public     :                  SOSImpExp             void Reset ( );
public     :                  SOSImpExp             void ResetCurrent ( );
public     :                                        void SetAttributes (char *string, int32 slen );
public     :                                        void SetBegin (char *spos );
public     :                                        void SetEnd (char *spos );
public     :                                        void SetName (char *string, int32 slen );
public     :                  SOSImpExp             void ToTop ( );
public     :                  SOSImpExp                  XMLElement ( );
public     :                  SOSImpExp                  XMLElement (char *names );
public     :                  SOSImpExp                  XMLElement (char *string, int32 slen );
public     :                  SOSImpExp                  ~XMLElement ( );
};

#pragma pack()
#endif
