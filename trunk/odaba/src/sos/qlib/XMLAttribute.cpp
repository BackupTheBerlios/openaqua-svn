/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    XMLAttribute

\brief    XML attribute description
          The  attribute description  describes an  attribute of an XML element.
          Predefined  attributes own the attribute names and can be created with
          the name-constructor.

\date     $Date: 2006/03/12 19:22:03,18 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "XMLAttribute"

#include  <pdefault.h>
#include  <sXMLAttribute.hpp>


/******************************************************************************/
/**
\brief  GetAttribute

\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetAttribute"

char *XMLAttribute :: GetAttribute ( )
{
  char                   *string;
BEGINSEQ
  if ( !IsValid() )                                  ERROR
    
  work_area.SetString(name,name_len);
  work_area += "=";
  
  if ( has_quotes )
    work_area += "\"";
  
  work_area.Append(value,value_len);
  
  if ( has_quotes )
    work_area += "\"";

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  IsValid - Is attribute descriptor valid?
        The  function returns true (YES), when the attribute descriptor contains
        valid data.

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical XMLAttribute :: IsValid ( )
{

  return ( name ? YES : NO );

}

/******************************************************************************/
/**
\brief  Reset - Reset attribut description
        The  function  resets  the  current  attribute discription (and makes it
        invalid).


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Reset"

void XMLAttribute :: Reset ( )
{

  XMLValue::Reset();
  
  has_quotes = NO;


}

/******************************************************************************/
/**
\brief  SetName

\return term - Success

\param  string - String value
\param  slen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetName"

logical XMLAttribute :: SetName (char *string, int32 slen )
{
  logical                 term = NO;
BEGINSEQ
  if ( owner )                                       SOSERR(99)
  if ( !string )                                     ERROR

  name     = string;
  name_len = slen;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetValue

\return term - Success

\param  string - String value
\param  slen -
\param  quotes -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical XMLAttribute :: SetValue (char *string, int32 slen, logical quotes )
{
  logical                 term = NO;
BEGINSEQ
  if ( !string )                                      ERROR

  value     = string;
  value_len = slen;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  XMLAttribute

-------------------------------------------------------------------------------
\brief i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XMLAttribute"

                        XMLAttribute :: XMLAttribute ( )
                     : XMLValue (),
  has_quotes(NO)
{



}

/******************************************************************************/
/**
\brief i01


\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XMLAttribute"

                        XMLAttribute :: XMLAttribute (char *names )
                     : XMLValue (names),
  has_quotes(NO)
{



}

/******************************************************************************/
/**
\brief  operator= - Assign valueto attribute
        The  funcion  assigns  the  passed  value to the XML attribute. When the
        value  contains  blanks,  commas  or  semicolons,  the  value  is put in
        quotes. The value should not contain quotes.

\return xvalue_ref -
-------------------------------------------------------------------------------
\brief i00


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

XMLValue &XMLAttribute :: operator= (char *string )
{

  *(XMLValue *)this = string;
  
  has_quotes = strchr(string,' ') || strchr(string,',') || strchr(string,';');


  return(*this);
}

/******************************************************************************/
/**
\brief i01


\param  int_val -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

XMLValue &XMLAttribute :: operator= (int32 int_val )
{

  *(XMLValue *)this = int_val;

  return(*this);
}

/******************************************************************************/
/**
\brief  ~XMLAttribute


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~XMLAttribute"

                        XMLAttribute :: ~XMLAttribute ( )
{

  if ( owner )
    free(name);
  name = NULL;

  delete ovalue;
  ovalue = NULL;

}


