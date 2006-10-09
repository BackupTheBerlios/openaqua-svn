/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    XMLString

\brief    XML text string
          The  class  supports  parsing  an  XML text string for tags. It allows
          returning XML tags from a string.

\date     $Date: 2006/07/12 19:11:54,42 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "XMLString"

#include  <pdefault.h>
#include  <sXMLElement.hpp>
#include  <sXMLString.hpp>


/******************************************************************************/
/**
\brief  Close - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

void XMLString :: Close ( )
{

  XMLElement::Close();
  
  if ( owner )
    free(value);
  value = NULL;
  value_len = 0;

  if ( path )
  {
    free(path);
    path = NULL;
  }

  if ( file )
    fclose(file);
  file = NULL;
  Reset();

}

/******************************************************************************/
/**
\brief  GetString - Get XMLString
        The  function will recreate an XMLstring  from the information stored in
        XML  elements after updating them. The function returns a pointer to the
        string created.

\return string - String value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetString"

char *XMLString :: GetString ( )
{
  NString        wstr;
  wstr.Resize(text.GetSize());
  XMLElement::GetString(wstr,0);
  text = wstr;
  return(text);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Success
-------------------------------------------------------------------------------
\brief  i0 - 


\param  string - String value
\param  slen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical XMLString :: Open (char *string, int32 slen )
{
  logical             term = NO;
  text.SetString(string,slen);
  if ( value = begin = text )
    end = begin + (value_len = text.GetSize());
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical XMLString :: Open (char *cpath )
{
  logical             term = NO;
BEGINSEQ
  path = strdup(cpath);
  
  if ( (value_len = filread(path,(void **)&value)) <= 0 )
                                                    ERROR
  owner = YES;
  
  begin = value;
  end = value+value_len;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  PrintStructure - 


\return term - Success

\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrintStructure"

logical XMLString :: PrintStructure (char *cpath )
{
  FILE                   *file = NULL;
  logical                 term = NO;
  if ( cpath ) 
    file = fopen(cpath,"w");

  Print(file,"Top",0);

  if ( file )
    fclose(file);
  return(term);
}

/******************************************************************************/
/**
\brief  ReplaceElement - 


\return term - Success

\param  xelement - 
\param  string - String value
\param  maxlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceElement"

logical XMLString :: ReplaceElement (XMLElement *xelement, char *string, int32 maxlen )
{
  char                   *start;
  logical                 term = NO;
BEGINSEQ
  if ( !xelement->IsValid() )                      ERROR

  if ( ovalue )
    (XMLValue)*this = string;
  else if ( start = xelement->GetStart() )
  {
    gvtssdl(start,xelement->GetStringLength());
    gvtssin(start,string,maxlen-(current_pos-text.GetArea()));
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Save - 



\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

void XMLString :: Save (char *cpath )
{

BEGINSEQ
  if ( cpath && cpath != path )
  {
    if ( path )
      free(path);
    path = strdup(cpath);
    if ( file )
      fclose(file);
    file = NULL;
  }

  if ( !file )
    if ( !(file = fopen(path,"w")) )                 ERROR
  
  if ( !GetString() )                                ERROR
  if ( fwrite(text,text.GetSize(),1,file) )          ERROR


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  XMLString - 


-------------------------------------------------------------------------------
\brief  i0 - 


\param  string - String value
\param  slen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XMLString"

     XMLString :: XMLString (char *string, int32 slen )
                     : XMLElement (),
  path(NULL),
  file(NULL),
  text(),
  owner(NO)
{

  Open(string,slen);

}

/******************************************************************************/
/**
\brief  i01 - 


\param  cpath - Complete path
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XMLString"

     XMLString :: XMLString (char *cpath )
                     : XMLElement (),
  path(NULL),
  file(NULL),
  text(),
  owner(NO)
{

  Open(cpath);

}

/******************************************************************************/
/**
\brief  i02 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "XMLString"

     XMLString :: XMLString ( )
                     : XMLElement(),
  path(NULL),
  file(NULL),
  text(),
  owner(NO)
{



}

/******************************************************************************/
/**
\brief  ~XMLString - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~XMLString"

     XMLString :: ~XMLString ( )
{

  Close();

}


