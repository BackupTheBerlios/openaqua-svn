/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    XMLElement

\brief    XML element
          An  XML element describes  the attribute area,  the type and the value
          for  an XML element.  Strings are referenced  in the original text and
          should not me replaced.

\date     $Date: 2006/08/27 18:39:57,54 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "XMLElement"

#include  <pdefault.h>
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
#include  <sNString.hpp>
#include  <sXMLAttribute.hpp>
#include  <sXMLElement.hpp>
#include  <sXMLElement.hpp>


/******************************************************************************/
/**
\brief  AddAttribute - 



\return xattribute - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddAttribute"

XMLAttribute *XMLElement :: AddAttribute (char *names )
{
  XMLAttribute   *xattribute = NULL;
BEGINSEQ
  if ( !names || !IsValid() )                        ERROR
  
  if ( xattribute = GetAttribute(names) )            ERROR
  
  xattribute = new XMLAttribute(names);
  attributes.Add(xattribute);

RECOVER
  xattribute = NULL;
ENDSEQ
  return(xattribute);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  names - Name
\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddAttribute"

XMLAttribute *XMLElement :: AddAttribute (char *names, char *string )
{
  XMLAttribute           *xattribute = NULL;
BEGINSEQ
  if ( !AddAttribute(names) )                         ERROR

  (XMLValue) *this = string;
RECOVER
  xattribute = NULL;
ENDSEQ
  return(xattribute);
}

/******************************************************************************/
/**
\brief  AddElement - Add sub-element

        The  function is used to add apre-defined element with the given name to
        the element list. The element is marked as invalid.
        Several elements with the same name can be created for an XMLnode.

\return xelement - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddElement"

XMLElement *XMLElement :: AddElement (char *names )
{
  XMLElement     *xelement = NULL;
BEGINSEQ
  if ( !names || !IsValid() )                        ERROR
  
  xelement = new XMLElement(names);
  elements.Add(xelement);
  current_elm = elements.GetSize();

RECOVER
  current_elm = AUTO;
  xelement = NULL;
ENDSEQ
  return(xelement);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  names - Name
\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddElement"

XMLElement *XMLElement :: AddElement (char *names, char *string )
{
  XMLElement             *xelement = NULL;
BEGINSEQ
  if ( !AddElement(names) )                          ERROR

  (XMLValue)*this = string;
RECOVER
  xelement = NULL;
ENDSEQ
  return(xelement);
}

/******************************************************************************/
/**
\brief  Close - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void XMLElement :: Close ( )
{
  int            count;

  count = elements.GetSize();
  while ( count-- )
    delete elements[count];
  elements.Clear();

  count = attributes.GetSize();
  while ( count-- )
    delete attributes[count];
  attributes.Clear();


}

/******************************************************************************/
/**
\brief  FillAttributes - 



\return term - Success

\param  predefined - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillAttributes"

logical XMLElement :: FillAttributes (logical predefined )
{
  char                   *pos    = options;
  char                   *endpos = options+options_len;
  char                   *next;
  XMLAttribute           *xattribute;
  logical                 quotes = NO;
  char                   *comma;
  char                   *blank;
  int                     indx0 = 0;
  int                     count = attributes.GetSize();
  logical                 term = NO;
BEGINSEQ
  if ( !IsValid()  )                                 ERROR
  attr_filled = YES;
  
  while ( pos < endpos )
  {
    if ( !(next = strchr(pos,'=')) )
      next = endpos;
    work_area.SetString(pos,next-pos);
    if ( predefined )
      xattribute = ProvideAttribute(work_area);
    else 
    {
      xattribute = ProvideAttribute(indx0++);
      xattribute->SetName(pos,next-pos);
    }
    pos = next+1;
    quotes = NO;
    if ( *pos == '"' )
    {
      quotes = YES;
      if ( !(next = gvtsfbp(pos,options_len-(pos-options))) )
                                                     SOSERR(99)
      xattribute->SetValue(pos+1,next-pos-2,YES);
    }     
    else
    {
      if ( !(comma = strchr(pos,',')) && (blank = strchr(pos,' ')) )
        next = endpos;
      else
        next = comma < blank ? comma : blank;
      xattribute->SetValue(pos,next-pos,NO);
    }
    pos = next;
    while ( pos < endpos && (*pos == ' ' || *pos == ',') ) 
      pos++;
  }


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FillElements - 



\return term - Success

\param  predefined - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FillElements"

logical XMLElement :: FillElements (logical predefined )
{
  logical                 term = NO;
BEGINSEQ
  if ( !IsValid()  )                                 ERROR
  elmnt_filled = YES;
  
  ToTop();
  while ( NextElement(YES) ) ;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FindElementEnd - 



\return tpos - 

\param  element_name - 
\param  element_len - 
\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindElementEnd"

char *XMLElement :: FindElementEnd (char *element_name, int32 element_len, char *string )
{
  char        *tpos = NULL;
  char        *pos = string;
  char        *end;
BEGINSEQ
  while ( pos = strchr(pos,'<') )
  {
    tpos = pos;
    if ( *(++pos) == '/' )
    {
      if ( memcmp(++pos,element_name,element_len) )
        continue;
      else
      {
        pos+=element_len;
        while ( *pos == ' ' ) 
          pos++;
        if ( *pos != '>' )
          continue;
        break;
      }
    }
    else
    {
      if ( memcmp(pos,element_name,element_len) )
        continue;
      
      pos += element_len;
      end = strchr(pos,'>');
      if ( *(end-1) == '/' )
        continue;
      
      if ( *pos == ' ' || *pos == '>' )
        pos = FindElementEnd(element_name,element_len,pos);
      if ( !pos )                                    ERROR
      pos++;             // skip < of </tagname>
      continue;
    }
  }

RECOVER
  tpos = NULL;
ENDSEQ
  return(tpos);
}

/******************************************************************************/
/**
\brief  GetAttribute - Get attribute from element

        The  function  returns  the  required  attribute  from  the element. The
        function  returns  the  attribute  descriptor or NULL, when no attribute
        was found.

\return xattribute - 
-------------------------------------------------------------------------------
\brief  i0 - Return attribute by index

        The  function  returns  the  n-th  attribute  from the data element. The
        position  of the attribute depends on  the sequence of definition in the
        element.

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAttribute"

XMLAttribute *XMLElement :: GetAttribute (int32 indx0 )
{
  XMLAttribute           *xattribute = NULL;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
    
  if ( !attr_filled )
    FillAttributes(NO);
  
  if ( indx0 >= attributes.GetSize() )                ERROR
  
  xattribute = attributes[indx0];

RECOVER
  xattribute = NULL;
ENDSEQ
  return(xattribute);
}

/******************************************************************************/
/**
\brief  i01 - Get attribute by name

        The function looks for the requiresd attribute by name.

\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAttribute"

XMLAttribute *XMLElement :: GetAttribute (char *names )
{
  XMLAttribute   *xattribute = NULL;
  int             count;
BEGINSEQ
  if ( !names || !IsValid() )                        ERROR
  
  if ( !attr_filled )
    FillAttributes(NO);
  
  count = attributes.GetSize();
  while ( count-- )
  {
    xattribute = attributes[count];
    if ( !strcmp(xattribute->GetName(),names) )       LEAVESEQ
  }
  ERROR

RECOVER
  xattribute = NULL;
ENDSEQ
  return(xattribute);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  ns_prefix - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAttribute"

XMLAttribute *XMLElement :: GetAttribute (char *ns_prefix, char *names )
{
  XMLAttribute   *xattribute = NULL;
  NString         nstring;
  int             count;
  if ( ns_prefix && *ns_prefix )
    nstring << ns_prefix << ':';
  nstring << names;
  
  xattribute = GetAttribute(nstring);    

  return(xattribute);
}

/******************************************************************************/
/**
\brief  GetAttributeValue - 



\return string - String value
-------------------------------------------------------------------------------
\brief  i0 - 



\param  ns_prefix - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAttributeValue"

char *XMLElement :: GetAttributeValue (char *ns_prefix, char *names )
{

  return( GetAttribute(ns_prefix,names)->GetValue() );


}

/******************************************************************************/
/**
\brief  i01 - 



\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAttributeValue"

char *XMLElement :: GetAttributeValue (char *names )
{

  return( GetAttribute(names)->GetValue() );


}

/******************************************************************************/
/**
\brief  GetAttributes - 



\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAttributes"

char *XMLElement :: GetAttributes ( )
{
  char           *string = NULL;
BEGINSEQ
  if ( !end )                                        ERROR
    
  work_area.SetString(options,options_len);
  string = work_area;

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetCurrentElement - 



\return xelement - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetCurrentElement"

XMLElement *XMLElement :: GetCurrentElement ( )
{

  return ( IsValid() && elmnt_filled && current_elm > AUTO
           ? GetElement(current_elm) : NULL                  );

}

/******************************************************************************/
/**
\brief  GetElement - Get sub-element from element

        The  function  returns  the  required  sub-element from the element. The
        function  returns the  element descriptor  or NULL,  when no element was
        found.

\return xelement - 
-------------------------------------------------------------------------------
\brief  i0 - Return element by index

        The  function returns  the n-th  sub-element from  the data element. The
        position  of sub-elements  depend on  the sequence  of definition in the
        element.

\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElement"

XMLElement *XMLElement :: GetElement (int32 indx0 )
{
  XMLElement           *xelement = NULL;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
  
  if ( !elmnt_filled )
    FillElements(NO);
  
  if ( indx0 >= elements.GetSize() )                  ERROR
  
  xelement = elements[indx0];
  current_elm = indx0;  
  
  if ( !xelement->IsValid() )                         ERROR

RECOVER
  current_elm = AUTO;  
  xelement = NULL;
ENDSEQ
  return(xelement);
}

/******************************************************************************/
/**
\brief  i01 - Get sub-element by name

        The function looks for the requiresd sub-element by name.

\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElement"

XMLElement *XMLElement :: GetElement (char *names )
{
  int32           last = 0;
  XMLElement     *xelement = NULL;
BEGINSEQ
  if ( !names || !IsValid() )                        ERROR
  
  if ( !elmnt_filled )
    FillElements(NO);
  
  last = elements.GetSize();
  current_elm = 0;
  while ( current_elm < last )
  {
    xelement = elements[current_elm];
    if ( !strcmp(xelement->GetName(),names) )        LEAVESEQ
    current_elm++;
  }
  ERROR

RECOVER
  current_elm = AUTO;
  xelement = NULL;
ENDSEQ
  return(xelement);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  ns_prefix - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElement"

XMLElement *XMLElement :: GetElement (char *ns_prefix, char *names )
{
  int32           last = 0;
  NString         nstring;
  XMLElement     *xelement = NULL;
BEGINSEQ
  if ( !names || !IsValid() )                        ERROR

  if ( ns_prefix && *ns_prefix )
    nstring << ns_prefix << ':';
  nstring << names;
  
  xelement = GetElement(nstring);

RECOVER
  xelement = NULL;
ENDSEQ
  return(xelement);
}

/******************************************************************************/
/**
\brief  GetElementCount - 



\return count - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElementCount"

int32 XMLElement :: GetElementCount ( )
{
  int32           count = 0;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
  
  if ( !elmnt_filled )
    FillElements(NO);
  
  count = elements.GetSize();

RECOVER
  count = ERIC;
ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  GetElementRecursive - 



\return xelement - 

\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetElementRecursive"

XMLElement *XMLElement :: GetElementRecursive (char *names )
{
  int32           indx0 = 0;
  XMLElement     *xelement = NULL;
BEGINSEQ
  if ( !names || !IsValid() )                        ERROR
  
  if ( xelement = GetElement(names) )                LEAVESEQ

  while ( xelement = GetElement(indx0++) )
    if ( xelement = xelement->GetElementRecursive(names) )
                                                     LEAVESEQ

RECOVER
  xelement = NULL;
ENDSEQ
  return(xelement);
}

/******************************************************************************/
/**
\brief  GetEndTag - 



\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetEndTag"

char *XMLElement :: GetEndTag ( )
{

  work_area = "</";
  work_area.Append(name,name_len);
  work_area += '>';
  return(work_area);
}

/******************************************************************************/
/**
\brief  GetNextElement - 



\return xelement - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNextElement"

XMLElement *XMLElement :: GetNextElement ( )
{
  XMLElement             *xelement = NULL;
BEGINSEQ
  while ( xelement = GetElement(++current_elm) )
    if ( !xelement->IsComment() && !xelement->IsVersion() ) LEAVESEQ

  current_elm = AUTO;
ENDSEQ
  return(xelement);
}

/******************************************************************************/
/**
\brief  GetStart - 



\return start - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStart"

char *XMLElement :: GetStart ( )
{

  return ( IsValid() ? begin : NULL );

}

/******************************************************************************/
/**
\brief  GetStartTag - 



\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStartTag"

char *XMLElement :: GetStartTag ( )
{
  XMLAttribute           *xattribute;
  int32                   indx = 0;

  work_area = "<";
  work_area.Append(name,name_len);
  while ( xattribute = GetAttribute(indx++) )
  {
    work_area += ' ';
    work_area += xattribute->GetAttribute();
  }
  work_area += '>';

  return(work_area);
}

/******************************************************************************/
/**
\brief  GetString - 



\return term - Success

\param  n_string - 
\param  level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

logical XMLElement :: GetString (NString &n_string, int32 level )
{
  XMLElement             *xelement;
  int32                   indx = 0;
  logical                 term = NO;
  InitString(n_string,level);
  n_string += GetStartTag();
  n_string += '\n';
  
  if ( value_len )
  {
    InitString(n_string,level+1);
    n_string += GetValue();
    n_string += '\n';
  }

  while ( xelement = GetElement(indx) )
    xelement->GetString(n_string,level+1);

  InitString(n_string,level);
  n_string += GetEndTag();
  n_string += '\n';

  return(term);
}

/******************************************************************************/
/**
\brief  GetStringLength - 



\return slen - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringLength"

int8 XMLElement :: GetStringLength ( )
{

  return ( end ? end-begin : 0 );

}

/******************************************************************************/
/**
\brief  GetTextData - 



\return term - Success

\param  n_string - 
\param  par_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTextData"

logical XMLElement :: GetTextData (NString &n_string, logical &par_ref )
{
  XMLElement             *xelement;
  logical                 is_paragraph = NO;
  int32                   indx0 = 0;
  logical                 term = NO;
  while ( xelement = GetElement(indx0++) )
  {
    if ( par_ref )
      n_string += '\n';
    par_ref = NO;
    xelement->GetTextData(n_string,par_ref);
  }

  if ( !elements.GetSize() && value )
    n_string.Append(value,value_len);
    
  if ( name_len == 1 && (*name == 'P' || *name == 'p') )
    par_ref = YES;
  return(term);
}

/******************************************************************************/
/**
\brief  GetTypeNumber - 



\return scode - 

\param  symbol1 - 
\param  symbol2 - 
\param  symbol3 - 
\param  symbol4 - 
\param  symbol5 - 
\param  symbol6 - 
\param  symbol7 - 
\param  symbol8 - 
\param  symbol9 - 
\param  symbol10 - 
\param  symbol11 - 
\param  symbol12 - 
\param  symbol13 - 
\param  symbol14 - 
\param  symbol15 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetTypeNumber"

int8 XMLElement :: GetTypeNumber (char *symbol1, char *symbol2, char *symbol3, char *symbol4, char *symbol5, char *symbol6, char *symbol7, char *symbol8, char *symbol9, char *symbol10, char *symbol11, char *symbol12, char *symbol13, char *symbol14, char *symbol15 )
{
  int8           scode = UNDEF;
  if ( symbol1 && !strcmp(GetName(),symbol1) )
    scode = 1;
  else if ( symbol2 && !strcmp(GetName(),symbol2) )
    scode = 2;
  else if ( symbol3 && !strcmp(GetName(),symbol3) )
    scode = 3;
  else if ( symbol4 && !strcmp(GetName(),symbol4) )
    scode = 4;
  else if ( symbol5 && !strcmp(GetName(),symbol5) )
    scode = 5;
  else if ( symbol6 && !strcmp(GetName(),symbol6) )
    scode = 6;
  else if ( symbol7 && !strcmp(GetName(),symbol7) )
    scode = 7;
  else if ( symbol8 && !strcmp(GetName(),symbol8) )
    scode = 8;
  else if ( symbol9 && !strcmp(GetName(),symbol9) )
    scode = 9;
  else if ( symbol10 && !strcmp(GetName(),symbol10) )
    scode = 10;
  else if ( symbol11 && !strcmp(GetName(),symbol11) )
    scode = 11;
  else if ( symbol12 && !strcmp(GetName(),symbol12) )
    scode = 12;
  else if ( symbol13 && !strcmp(GetName(),symbol13) )
    scode = 13;
  else if ( symbol14 && !strcmp(GetName(),symbol14) )
    scode = 14;
  else if ( symbol15 && !strcmp(GetName(),symbol15) )
    scode = 15;

  return(scode);
}

/******************************************************************************/
/**
\brief  InitString - 




\param  n_string - 
\param  level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InitString"

void XMLElement :: InitString (NString &n_string, int32 level )
{
  char                    string[257];
  int16                   indent = MIN(level,128)*2;
  memset(string,' ',indent);
  string[indent] = 0;
  n_string += string;


}

/******************************************************************************/
/**
\brief  InvalidateAttributes - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InvalidateAttributes"

logical XMLElement :: InvalidateAttributes ( )
{
  int            count = attributes.GetSize();
  XMLAttribute  *xattribute;
  logical        term = NO;
  while ( count-- )
    if ( xattribute = attributes[count] )
      xattribute->Reset();

  return(term);
}

/******************************************************************************/
/**
\brief  InvalidateElements - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InvalidateElements"

logical XMLElement :: InvalidateElements ( )
{
  int            count = elements.GetSize();
  XMLElement    *xelement;
  logical        term = NO;
  while ( count-- )
    if ( xelement = elements[count] )
      xelement->Reset();

  return(term);
}

/******************************************************************************/
/**
\brief  IsAttributeValueTrue - 



\return cond - Return value
-------------------------------------------------------------------------------
\brief  i0 - 



\param  ns_prefix - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAttributeValueTrue"

logical XMLElement :: IsAttributeValueTrue (char *ns_prefix, char *names )
{
  char              *value;
  logical            cond = NO;
  if ( value = GetAttribute(ns_prefix,name)->GetValue() )
    if ( !strcmp(value,"true") )
      cond = YES;


  return(cond);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsAttributeValueTrue"

logical XMLElement :: IsAttributeValueTrue (char *names )
{
  char              *value;
  logical            cond = NO;
  if ( value = GetAttribute(name)->GetValue() )
    if ( !strcmp(value,"true") )
      cond = YES;

  return(cond);
}

/******************************************************************************/
/**
\brief  IsComment - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsComment"

logical XMLElement :: IsComment ( )
{

  return ( this && name && *name == '!' ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsElement - 



\return cond - Return value

\param  ns_prefix - 
\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsElement"

logical XMLElement :: IsElement (char *ns_prefix, char *names )
{
  logical       cond = YES;
BEGINSEQ
  work_area = "";
  if ( ns_prefix && *ns_prefix )
    work_area << ns_prefix << ':';
  work_area << names;
  
  if ( name_len != strlen(work_area) )              ERROR
  if ( memcmp(name,work_area,name_len) )            ERROR

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  IsValid - Is element valid?

        The  function  returns,  whether  the  XML  element description contains
        valid data or not.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical XMLElement :: IsValid ( )
{

  return ( end || ovalue ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsVersion - 



\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsVersion"

logical XMLElement :: IsVersion ( )
{

  return ( this && name && *name == '?' ? YES : NO );

}

/******************************************************************************/
/**
\brief  NextElement - 



\return xelement - 

\param  structured - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextElement"

XMLElement *XMLElement :: NextElement (logical structured )
{
  char            lc = value ? value[value_len] : 0;
  XMLElement     *xelement = NULL;
  char           *pos;
  char           *tbend;
  char           *tend;
  char           *end;
  char           *tagend;

BEGINSEQ
  if ( structured && current_elm >= 0 )
    current_pos = GetCurrentElement()->get_end();
  
  if ( current_pos - value >= value_len )            ERROR
    
  if ( value )
    value[value_len] = 0;
  
  pos = current_pos;
  while ( pos = strchr(pos,'<') )
  {
    // if not in CDATA ... fehlt noch
    break;
  }
  if ( !pos || !*pos || *(pos+1) == '/' )            ERROR
  if ( !(tbend = strchr(pos+1,'>')) )                ERROR
  
  if ( !(xelement = ProvideElement(++current_elm)) ) ERROR
  xelement->Reset();
  xelement->SetBegin(pos);
  pos++;
  
  current_pos = tbend+1;  // next search position
  
  if ( *(tbend-1) == '/' )
  {
    tend = tbend+1;   // end of tag, no data
    tbend--;          // end of tag value
  }
  tagend = tbend;
  if ( end = strchr(pos,' ') ) 
    if ( end < tbend )
      tagend = end;
 
  xelement->SetName(pos,tagend-pos);
  if ( *pos == '!' || *pos == '?' )  // comment and version
    tend = tbend+1;
  else
  {
    while ( *tagend == ' ' ) tagend++;
    xelement->SetAttributes(tagend,tbend - tagend);
  
    if ( *tbend != '/' )
    {
      tbend++;
      if ( !(pos = FindElementEnd(xelement->get_name(),xelement->get_name_len(),tbend)) )
                                                     ERROR
      xelement->SetValue(tbend,pos - tbend);
      tend =   strchr(pos,'>')+1;
    }
  }
  xelement->SetEnd(tend);

RECOVER
  if ( xelement )
  {
    elements.RemoveLast(1);
    delete xelement;
    xelement = NULL;
  }
ENDSEQ
  if ( value )
    value[value_len] = lc;
  return(xelement);
}

/******************************************************************************/
/**
\brief  Print - 



\return term - Success

\param  file - 
\param  names - Name
\param  level - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Print"

logical XMLElement :: Print (FILE *file, char *names, int32 level )
{
  XMLElement             *xelement = NULL;
  logical                 term = NO;
  work_area.Initialize(' ',level*2);

  if ( names )
    work_area += names;
  else
    work_area.Append(name,name_len);
  
  if ( options_len )
  {
    work_area += '(';
    work_area.Append(options,options_len);
    work_area += ')';
  }
  if ( value_len )
  {
    work_area += ':';
    work_area.Append(value,MIN(40,value_len));
  }
  STRExchange(work_area,"\r\n"," ",work_area.GetSize());
  work_area += "\n";

  if ( file )
    fprintf(file,work_area);
  else
    SystemOutput(work_area,NO,YES);

  ToTop();
  while ( xelement = GetNextElement() )
    xelement->Print(file,NULL,level+1);
  return(term);
}

/******************************************************************************/
/**
\brief  ProvideAttribute - 



\return xattribute - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideAttribute"

XMLAttribute *XMLElement :: ProvideAttribute (int32 indx0 )
{
  XMLAttribute           *xattribute = NULL;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
    
  if ( xattribute = GetAttribute(indx0) )             LEAVESEQ
  
  xattribute = new XMLAttribute();
  attributes.SetAtGrow(indx0,xattribute);
  current_elm = indx0;

RECOVER
  xattribute = NULL;
ENDSEQ
  return(xattribute);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideAttribute"

XMLAttribute *XMLElement :: ProvideAttribute (char *names )
{
  XMLAttribute   *xattribute = NULL;
BEGINSEQ
  if ( !names || !IsValid() )                        ERROR
  
  if ( xattribute = GetAttribute(names) )            LEAVESEQ
  
  xattribute = new XMLAttribute(names);
  attributes.Add(xattribute);

RECOVER
  xattribute = NULL;
ENDSEQ
  return(xattribute);
}

/******************************************************************************/
/**
\brief  ProvideElement - 



\return xelement - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  indx0 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideElement"

XMLElement *XMLElement :: ProvideElement (int32 indx0 )
{
  XMLElement           *xelement = NULL;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
    
  if ( xelement = GetElement(indx0) )             LEAVESEQ
  
  xelement = new XMLElement();
  elements.SetAtGrow(indx0,xelement);
  current_elm = indx0;
RECOVER
  xelement = NULL;
ENDSEQ
  return(xelement);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ProvideElement"

XMLElement *XMLElement :: ProvideElement (char *names )
{
  XMLElement     *xelement = NULL;
BEGINSEQ
  if ( !names || !IsValid() )                        ERROR
  
  if ( xelement = GetElement(names) )            LEAVESEQ
  
  xelement = AddElement(names);
RECOVER
  current_elm = AUTO;
  xelement = NULL;
ENDSEQ
  return(xelement);
}

/******************************************************************************/
/**
\brief  Reset - Reset XML element description

        The  function  resets  the  current  element  discription  (and makes it
        invalid).


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void XMLElement :: Reset ( )
{

  XMLValue::Reset();
  
  begin = NULL;
  options = NULL;
  options_len = 0;
  end = NULL;
  current_pos = NULL;
  current_elm = AUTO;
 
  InvalidateAttributes();
  InvalidateElements();
  attr_filled = NO;
  elmnt_filled = NO;

}

/******************************************************************************/
/**
\brief  ResetCurrent - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ResetCurrent"

void XMLElement :: ResetCurrent ( )
{

  current_elm = AUTO;

}

/******************************************************************************/
/**
\brief  SetAttributes - 




\param  string - String value
\param  slen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetAttributes"

void XMLElement :: SetAttributes (char *string, int32 slen )
{

  options = string;
  options_len = slen;


}

/******************************************************************************/
/**
\brief  SetBegin - 




\param  spos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBegin"

void XMLElement :: SetBegin (char *spos )
{

  begin = spos;

}

/******************************************************************************/
/**
\brief  SetEnd - 




\param  spos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetEnd"

void XMLElement :: SetEnd (char *spos )
{

  end = spos;

}

/******************************************************************************/
/**
\brief  SetName - Set element name




\param  string - String value
\param  slen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetName"

void XMLElement :: SetName (char *string, int32 slen )
{

  name = string;
  name_len = slen;


}

/******************************************************************************/
/**
\brief  ToTop - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToTop"

void XMLElement :: ToTop ( )
{

  current_pos = value;
  current_elm = AUTO;

}

/******************************************************************************/
/**
\brief  XMLElement - 



-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XMLElement"

     XMLElement :: XMLElement ( )
                     : XMLValue (),
  begin(NULL),
  options(NULL),
  options_len(0),
  end(NULL),
  current_elm(AUTO),
  current_pos(NULL),
  attributes(),
  elements(),
  elmnt_filled(NO),
  attr_filled(NO)
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XMLElement"

     XMLElement :: XMLElement (char *names )
                     : XMLValue (names),
  begin(NULL),
  options(NULL),
  options_len(0),
  end(NULL),
  current_elm(AUTO),
  current_pos(NULL),
  attributes(),
  elements(),
  elmnt_filled(NO),
  attr_filled(NO)
{



}

/******************************************************************************/
/**
\brief  i02 - 



\param  string - String value
\param  slen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XMLElement"

     XMLElement :: XMLElement (char *string, int32 slen )
                     : XMLValue (string,slen),
  begin(NULL),
  options(NULL),
  options_len(0),
  end(NULL),
  current_elm(AUTO),
  current_pos(NULL),
  attributes(),
  elements(),
  elmnt_filled(NO),
  attr_filled(NO)
{

  begin = value;
  end = value ? value+value_len : NULL;

}

/******************************************************************************/
/**
\brief  ~XMLElement - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~XMLElement"

     XMLElement :: ~XMLElement ( )
{


  Close();

}


