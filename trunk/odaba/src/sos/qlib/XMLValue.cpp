/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    XMLValue

\brief    XML element
          An  XML element describes  the attribute area,  the type and the value
          for  an XML element.  Strings are referenced  in the original text and
          should not me replaced.

\date     $Date: 2006/07/12 19:09:09,64 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "XMLValue"

#include  <pdefault.h>
#include  <sNString.hpp>
#include  <sXMLValue.hpp>


/******************************************************************************/
/**
\brief  GetName - 


\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetName"

char *XMLValue :: GetName ( )
{
  char           *string = NULL;
BEGINSEQ
  if ( !this || !name )                              ERROR
    
  work_area.SetString(name,name_len);
  string = work_area;

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  GetValue - Get value string
        The  function returns  the string  that helds  the value for the element
        (area between the begin and end tag).

\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetValue"

char *XMLValue :: GetValue ( )
{
  char           *string = NULL;
BEGINSEQ
  if ( !this || !value )                              ERROR
    
  work_area.SetString(value,value_len);
  string = work_area;

RECOVER
  string = NULL;
ENDSEQ
  return(string);
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

void XMLValue :: Reset ( )
{

  if ( !owner )
  {
    name = NULL;
    name_len = 0;
  }
  value = NULL;
  value_len = 0;
 
  if ( ovalue )
    *ovalue = "";

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

void XMLValue :: SetName (char *string, int32 slen )
{

  name = string;
  name_len = slen;


}

/******************************************************************************/
/**
\brief  SetValue - Set element value


\return term - Success

\param  string - String value
\param  slen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetValue"

logical XMLValue :: SetValue (char *string, int32 slen )
{
  logical                 term = NO;
BEGINSEQ
  if ( !string )                                      ERROR

  value = string;
  
  value_len = slen ? slen : strlen(value);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  XMLValue - 


-------------------------------------------------------------------------------
\brief  i0 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XMLValue"

     XMLValue :: XMLValue ( )
                     :   name(NULL),
  name_len(0),
  value(NULL),
  value_len(0),
  owner(NO),
  work_area(), //initialized with NULL (j040922)
  ovalue(NULL)
{



}

/******************************************************************************/
/**
\brief  i01 - 


\param  names - Name
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XMLValue"

     XMLValue :: XMLValue (char *names )
                     :   name(NULL),
  name_len(0),
  value(NULL),
  value_len(0),
  owner(NO),
  work_area(), //initialized with NULL (j040922)
  ovalue(NULL)
{

  if ( names )
  {
    owner = YES;
    name = strdup(names);
    name_len = strlen(name);
  }


}

/******************************************************************************/
/**
\brief  i02 - 


\param  string - String value
\param  slen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XMLValue"

     XMLValue :: XMLValue (char *string, int32 slen )
                     :   name(NULL),
  name_len(0),
  value(string),
  value_len(slen),
  owner(NO),
  work_area(), //initialized with NULL (j040922)
  ovalue(NULL)
{

  if ( !value_len && value )
    value_len = strlen(value);

}

/******************************************************************************/
/**
\brief  operator= - Assign value to XML element
        The function assigns a value to an XML element or attribute..

\return xvalue_ref - 
-------------------------------------------------------------------------------
\brief  i00 - 


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

XMLValue &XMLValue :: operator= (char *string )
{

  if ( !ovalue )
    ovalue = new NString();

  *ovalue = string;

  value = *ovalue;
  value_len = strlen(value);

  return(*this);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  int_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

XMLValue &XMLValue :: operator= (int32 int_val )
{
  char       string[32];
  if ( !ovalue )
    ovalue = new NString();
    
  *ovalue = gvtxltoa(int_val,string,10);
  
  value = *ovalue;
  value_len = strlen(value);

  return(*this);
}

/******************************************************************************/
/**
\brief  ~XMLValue - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~XMLValue"

     XMLValue :: ~XMLValue ( )
{
  int            count;

  if ( owner )
    free(name);
  name = NULL;

  delete ovalue;
  ovalue = NULL;

}


