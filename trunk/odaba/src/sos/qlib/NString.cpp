/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    NString

\brief    String class
          NString  is a string class, which provides a number of specific string
          features.

\date     $Date: 2006/08/28 21:45:40,03 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "NString"

#include  <pdefault.h>
#include  <Code64.h>
#include  <cDataFormSpec.h>
#include  <ssvel.hpp>
#include  <sNString.hpp>


/******************************************************************************/
/**
\brief  ASCIIToUTF - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ASCIIToUTF"

logical NString :: ASCIIToUTF ( )
{
  logical      term = NO;
  ReplaceText("ö","Ã¶");
  ReplaceText("Ö","Ã?");
  ReplaceText("ä","Ã¤");
  ReplaceText("Ä","Ã?");
  ReplaceText("ü","Ã¼");
  ReplaceText("Ü","Ã?");
  ReplaceText("ß","ÃŸ");

  return(term);
}

/******************************************************************************/
/**
\brief  Append - 



\return term - Success
-------------------------------------------------------------------------------
\brief  date - 



\param  dateval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical NString :: Append (dbdt dateval )
{
  char       string[33];
  dateval.ToString(string,sizeof(string)-1,DFS_Default);
  Append(string,UNDEF);
  return(NO);
}

/******************************************************************************/
/**
\brief  i00 - 



\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical NString :: Append (char *string )
{
  int32     nlen      = 0;
  logical   term      = NO;
BEGINSEQ
  if ( !this || !string || !*string )                ERROR

  nlen = strlen(string) + (area ? strlen(area) : 0);
    
  if ( Resize(nlen) )                                LEAVESEQ
    
  strcat(area,string);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  string - String value
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical NString :: Append (char *string, size_t len )
{
  int32     olen      = 0;
  int32     nlen      = 0;
  logical   term      = NO;
BEGINSEQ
  if ( !string || !*string )                         ERROR

  if ( !len )
    len = strlen(string);  
  nlen = len + (area ? (olen = strlen(area)) : 0);
    
  if ( Resize(nlen) )                                LEAVESEQ
    
  gvtxbts(area+olen,string,len);

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  char_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical NString :: Append (char char_val )
{
  int       len = 0;

BEGINSEQ
  if ( area )
    len = strlen(area);
    
  if ( Resize(len+1) )                            LEAVESEQ
    
  area[len]   = char_val;
  area[len+1] = 0;

ENDSEQ
  return(NO);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  char_val - 
\param  count - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical NString :: Append (char char_val, int16 count )
{
  int       len  = 0;
  logical   term = NO;
BEGINSEQ
  if ( count < 0 )                                   ERROR
    
  if ( area )
    len = strlen(area);
    
  if ( Resize(len+count) )                           ERROR
        
  memset(area+len,char_val,count);
  area[len+count] = 0;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i04 - 



\param  intval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical NString :: Append (int32 intval )
{
  char       string[33];
  gvtxltoa(intval,string,10);
  Append(string,UNDEF);
  return(NO);
}

/******************************************************************************/
/**
\brief  i05 - 



\param  n_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical NString :: Append (NString &n_string )
{

  return ( Append(n_string.GetArea(),UNDEF) );

}

/******************************************************************************/
/**
\brief  i06 - 



\param  val64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical NString :: Append (int64 val64 )
{
  char       string[33];
  gvtxxtoa(val64,string,10);
  Append(string,UNDEF);
  return(NO);
}

/******************************************************************************/
/**
\brief  time - 



\param  timeval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical NString :: Append (dbtm timeval )
{
  char       string[33];
  timeval.ToString(string,sizeof(string)-1,DFS_Default);
  Append(string,UNDEF);
  return(NO);
}

/******************************************************************************/
/**
\brief  Copy - 



\return string - 

\param  string - String value
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Copy"

char *NString :: Copy (char *string, int int_len )
{

BEGINSEQ
  if ( int_len <= 0 )
    string = NULL;
  if ( !string  )                                    SOSERR(99)
  
  memset(string,0,int_len);
  if ( area )
    strncpy(string,area,int_len-1);
RECOVER

ENDSEQ
  if (string == 0) string = "";
  return ( string );
}

/******************************************************************************/
/**
\brief  Find - 



\return string - String value

\param  string - String value
\param  case_opt_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Find"

char *NString :: Find (char *string, logical case_opt_w )
{
  char        *pos = NULL;
  if ( case_opt_w )
    pos = strstr(area,string);
  else
    pos = gvtsiscn(area,string);
  return(pos);
}

/******************************************************************************/
/**
\brief  FromBase64 - 



\return nstring - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FromBase64"

NString &NString :: FromBase64 ( )
{
  char       *pos = area;
  NString     result;
  char       *out = NULL;
  int32       len;
  int32       i;
  int32       code;
BEGINSEQ
  if ( !area )                                      ERROR
  len = strlen(area);
  result.Resize( (len*3)/4 + 3 );
  out = result.area;
  while ( len )
  {
    for ( i=0; i < 4; i++ )
    {
      if ( i )
        code = code << 6;
      if ( len && --len )
        code += code256[*pos++];
    }
    
    *(out+2) = (code<<24) >> 24;
    *(out+1) = (code<<16) >> 24;
    *out = (code<<24) >> 24;
    out += 3;
  }
  *out = 0;
RECOVER

ENDSEQ
  return(result);
}

/******************************************************************************/
/**
\brief  GetKeyValue - 



\return nstring - 

\param  parm_key - Parameter keyword
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyValue"

NString NString :: GetKeyValue (char *parm_key )
{
  NString       nstring;
  char         *string;
  nstring = string = GetKeyParm(*this,parm_key,YES,YES);
  free(string);
  return(nstring);
}

/******************************************************************************/
/**
\brief  GetLength - 



\return string_len - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLength"

int NString :: GetLength ( )
{

  return ( area ? strlen(area) : 0 );

}

/******************************************************************************/
/**
\brief  Initialize - 



\return term - Success

\param  char_val - 
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical NString :: Initialize (char char_val, size_t len )
{
  logical                 term = NO;
BEGINSEQ
  if ( !len )                                        ERROR
  if ( Resize(len) )                                 SOSERR(95)
    
  memset(area,char_val,len);
  area[len] = 0;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Insert - 



\return term - Success

\param  pos - 
\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

logical NString :: Insert (uint16 pos, char *string )
{
  int32                   olen = 0;
  int32                   nlen;
  int                     len;
  logical                 term = NO;
BEGINSEQ
  if ( !string || !*string )                         ERROR
  len = strlen(string);  
  nlen = len + (area ? (olen = strlen(area)) : 0);
    
  if ( Resize(nlen) )                                LEAVESEQ

  if ( pos > olen )
    pos = olen;
  if ( pos < 0 )
    pos = 0;
  gvtssin(area+pos,string,nlen-pos);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsEmpty - Is the string empty

        The  function  returns  YES,  if  no  area  is  allocated  or  the first
        character is the NULL;

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical NString :: IsEmpty ( )
{

  return ( !area || !*area ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsHTML - 



\return cond - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsHTML"

logical NString :: IsHTML ( )
{
  logical      cond = NO;
  cond = (bool)Find("<html>",YES)
           | (bool)Find("<body>",YES)
           | (bool)Find("<br/>",YES)
       | (bool)Find("<p>",YES)
       | (bool)Find("<b>",YES)
       | (bool)Find("<i>",YES)
       | (bool)Find("<div>",YES)
       | (bool)Find("<table",YES);

  return(cond);
}

/******************************************************************************/
/**
\brief  NString - 



-------------------------------------------------------------------------------
\brief  i0 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NString"

     NString :: NString ( )
                     :  NBase ()
{



}

/******************************************************************************/
/**
\brief  i01 - 



\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NString"

     NString :: NString (char *string )
                     :  NBase ()
{

  *this = string;

}

/******************************************************************************/
/**
\brief  i02 - 



\param  string - String value
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NString"

     NString :: NString (char *string, size_t len )
                     :  NBase ()
{

  SetString(string,len);

}

/******************************************************************************/
/**
\brief  i03 - 



\param  intval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NString"

     NString :: NString (int32 intval )
                     : NBase ()
{
  char       string[33];
  gvtxltoa(intval,string,10);
  SetString(string,strlen(string));

}

/******************************************************************************/
/**
\brief  i04 - 



\param  n_string_const - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NString"

     NString :: NString (const NString &n_string_const )
{

  Append(((NString *)&n_string_const)->GetArea(),UNDEF);

}

/******************************************************************************/
/**
\brief  Normalize - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Normalize"

logical NString :: Normalize ( )
{
  int32        pos = 0;
  logical      term = NO;
BEGINSEQ
  if ( !this || !area )                              ERROR
 
  while ( *area == ' ' )
    pos++;
  if ( pos )
    gvtssdl(area,pos);
 
  pos = strlen(area);
  while ( --pos && area[pos] == ' ' )
    area[pos] = 0;

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  RenderHTML - 



\return nstring - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "RenderHTML"

NString NString :: RenderHTML ( )
{
  uchar       *pos;
  NString      result,tresult;
  logical      inTag = NO;


  result.SetString(area,0);
  result.ReplaceText("\n"," ");
  result.ReplaceText("</p>",    "\n\n");
  result.ReplaceText("<br />",  "\n");
  result.ReplaceText("<br/>",   "\n");
  result.ReplaceText("<li",     "\n * <li");
  result.ReplaceText("</ul><p", "\n");
  result.ReplaceText("<i>",     "_");
  result.ReplaceText("</i>",    "_");
  result.ReplaceText("<b>",     "*");
  result.ReplaceText("</b>",    "*");
  while(result.Find("  ")) result.ReplaceText("  "," ");

  pos = (uchar *)result.area;
  while(*pos){
    if( *pos=='<' ) inTag = YES;
    if( !inTag ) tresult+=(char)*pos;
    if( *pos=='>' ) inTag = NO;
    pos++;
  }
  result = tresult;
  // entitys;
  result.ReplaceText("&lt;",    "<");
  result.ReplaceText("&gt;",    ">");
  result.ReplaceText("&nbsp;",  " ");
  result.ReplaceText("&szlig;", "ß");
  result.ReplaceText("&ouml;",  "ö");
  result.ReplaceText("&uuml;",  "ü");
  result.ReplaceText("&auml;",  "ä");
  result.ReplaceText("&Ouml;",  "Ö");
  result.ReplaceText("&Uuml;",  "Ü");
  result.ReplaceText("&Auml;",  "Ä");
  result.ReplaceText("&amp;",   "&");

  return(result);
}

/******************************************************************************/
/**
\brief  ReplaceCharacter - 



\return count - 

\param  ichar - 
\param  ochar - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceCharacter"

int32 NString :: ReplaceCharacter (char ichar, char ochar )
{

  return ( ::STRReplaceCharacter(area,ichar,ochar) );

}

/******************************************************************************/
/**
\brief  ReplaceControlSequences - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceControlSequences"

logical NString :: ReplaceControlSequences ( )
{

  return ( ::ReplaceControlSequences(area,UNDEF,NO) ? NO : YES );

}

/******************************************************************************/
/**
\brief  ReplaceFirstSymbol - Replace first symbol in string

        The  functio  replaces  the  first  symbol  in  the  string by the value
        passed.  Further symbols are ignored. When the symbol was not found, the
        function returns an error.

\return term - Success

\param  symbol - Symbol name
\param  value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceFirstSymbol"

logical NString :: ReplaceFirstSymbol (char *symbol, char *value )
{

  return ( ReplaceSymbol(symbol,value,1) );

}

/******************************************************************************/
/**
\brief  ReplaceNLbyBR - 



\return term - Success

\param  res_val - Value to be added when resizing the area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceNLbyBR"

logical NString :: ReplaceNLbyBR (int32 res_val )
{
  logical      term  = NO;
BEGINSEQ
  if ( !GetLength() )                               LEAVESEQ
  if ( Resize(size,res_val) )                       ERROR
  
  ReplaceText("\n","<br/>\n");

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReplaceSymbol - 



\return term - Success

\param  symbol - Symbol name
\param  value - 
\param  index - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceSymbol"

logical NString :: ReplaceSymbol (char *symbol, char *value, uint16 index )
{
  int32                   olen = area ? strlen(area) : 0;
  int32                   slen = symbol ? strlen(symbol) : 0;
  int32                   nlen = 0;
  char                   *pos  = NULL;
  logical                 term = NO;
BEGINSEQ
  if ( !symbol || !value || !index )                 ERROR
  if ( olen < slen )                                 ERROR
  
  nlen = olen - slen + strlen(value);
  if ( Resize(nlen) )                                LEAVESEQ

  pos = area;
  while ( index-- )
  {
    if ( pos != area )
      pos++;
    if ( !(pos = strstr(pos,symbol)) )              ERROR
  }

  gvtssdl(pos,slen);
  gvtssin(pos,value,nlen-(area-pos));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReplaceSysVariables - 



\return term - Success

\param  svelptr - 
\param  res_val - Value to be added when resizing the area
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceSysVariables"

logical NString :: ReplaceSysVariables (svel *svelptr, int32 res_val )
{
  int16        trying = 16;
  logical      term   = NO;
BEGINSEQ
  if ( !svelptr )                                   ERROR
  if ( !GetLength() )                               LEAVESEQ
  if ( Resize(size,res_val) )                       ERROR
  
  while ( trying-- )
  {
    if ( svelptr->svelexc(area,size-1) )            LEAVESEQ
    if ( Resize(size + (res_val > 0 ? res_val : size),res_val) )
                                                    ERROR
  }
  
  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ReplaceText - 



\return term - Success

\param  symbol - Symbol name
\param  value - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceText"

logical NString :: ReplaceText (char *symbol, char *value )
{
  int        add_len = 0;
  int32      count   = 0;
  logical    term    = NO;
BEGINSEQ
//  while ( ++indx0 )
//    if ( ReplaceSymbol(symbol,value,indx0) )      LEAVESEQ  

  if ( !GetLength() )                               LEAVESEQ
  if ( !symbol || !value )                          ERROR
   
  if ( (add_len = strlen(value) - strlen(symbol))  > 0 )
  {
    if ( !(count = GetSearchStringCount(area,symbol)) )
                                                    LEAVESEQ
    if ( Resize(size+(count*add_len),add_len) )    ERROR
  }

  if ( !STRExchange(area,symbol,value,size-1) )     ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetString - 



\return string - String value

\param  string - String value
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetString"

char *NString :: SetString (char *string, size_t len )
{

BEGINSEQ
  if ( !len && string )
    len = strlen(string);
    
  if ( Resize(len) )                                 SOSERR(95)
    
  if ( !string || !*string || !len )
    *area = 0;
  else
    gvtxbts(area,string,len);

RECOVER
  return(NULL);
ENDSEQ
  return(area);
}

/******************************************************************************/
/**
\brief  ToBase64 - 



\return nstring - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ToBase64"

NString &NString :: ToBase64 ( )
{
  uchar      *pos = (uchar *)area;
  NString     result;
  char       *out = NULL;
  int32       len;
  int32       i;
  uint32      code;
  uint32      c64p;
  int32       pad = 0;
BEGINSEQ
  if ( !area )                                      ERROR
  len = strlen(area);
  result.Resize( (len*4)/3 + 3 );
  out = result.area;
  while ( len > 0 )
  {
    code = 0;
    code = *pos++;
    code = code << 8;
    if ( --len )
      code += *pos++;
    else
      pad++;
    code = code << 8;
    if ( len && --len ){
      code += *pos++;
      len--;
    }else{
      pad++;
    }
    for ( i=0; i < 4; i++,out++ ){
//        c64p = (code = code<<6) >> 24;
      code = code<<6;
          c64p = code >> 24;
          c64p&= 0x0000003f;
      *out = code64[c64p];
    }
  }
  *out = 0;
  while(pad){
    out--;
    *out = '=';
    pad--;
  }
  // *out = 0; j060828 - bad generated code
  SetString(result.area,0);
RECOVER

ENDSEQ
  return(result);
}

/******************************************************************************/
/**
\brief  UTFToASCII - 



\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UTFToASCII"

logical NString :: UTFToASCII ( )
{
  logical      term = NO;
  ReplaceText("Ã¶","ö");
  ReplaceText("Ã?","Ö");
  ReplaceText("Ã¤","ä");
  ReplaceText("Ã?","Ä");
  ReplaceText("Ã¼","ü");
  ReplaceText("Ã?","Ü");
  ReplaceText("ÃŸ","ß");

  return(term);
}

/******************************************************************************/
/**
\brief  operator+= - 



\return term - Success
-------------------------------------------------------------------------------
\brief  date - 



\param  dateval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

logical NString :: operator+= (dbdt dateval )
{

  return ( Append(dateval) );

}

/******************************************************************************/
/**
\brief  i00 - 



\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

logical NString :: operator+= (char *string )
{

  return( Append(string,UNDEF) );

}

/******************************************************************************/
/**
\brief  i01 - 



\param  char_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

logical NString :: operator+= (char char_val )
{

  return( Append(char_val) );

}

/******************************************************************************/
/**
\brief  i02 - 



\param  intval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

logical NString :: operator+= (int32 intval )
{

  return( Append(intval) );

}

/******************************************************************************/
/**
\brief  i03 - 



\param  n_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

logical NString :: operator+= (NString &n_string )
{

  return( Append(n_string) );

}

/******************************************************************************/
/**
\brief  i04 - 



\param  val64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

logical NString :: operator+= (int64 val64 )
{

  return( Append(val64) );

}

/******************************************************************************/
/**
\brief  time - 



\param  timeval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

logical NString :: operator+= (dbtm timeval )
{

  return( Append(timeval) );
  return(NO);
}

/******************************************************************************/
/**
\brief  operator<< - 



\return n_string - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<<"

NString &NString :: operator<< (char *string )
{

  if ( string && *string )
    Append(string,UNDEF);
  return(*this);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  char_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<<"

NString &NString :: operator<< (char char_val )
{

  Append(char_val);
  return(*this);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  intval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<<"

NString &NString :: operator<< (int32 intval )
{

  Append(intval);
  return(*this);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  n_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<<"

NString &NString :: operator<< (NString &n_string )
{

  if ( &n_string )
    Append(n_string);
  return(*this);
}

/******************************************************************************/
/**
\brief  i04 - 



\param  val64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<<"

NString &NString :: operator<< (int64 val64 )
{

  Append(val64);
  return(*this);
}

/******************************************************************************/
/**
\brief  operator= - 



\return n_string - 
-------------------------------------------------------------------------------
\brief  i00 - 



\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

NString &NString :: operator= (char *string )
{

  if ( area )
    *area = 0;
  Append(string,UNDEF);


  return(*this);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  char_val - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

NString &NString :: operator= (char char_val )
{

  if ( area )
    *area = 0;
  Append(char_val);

  return(*this);
}

/******************************************************************************/
/**
\brief  i02 - 



\param  intval - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

NString &NString :: operator= (int32 intval )
{

  if ( area )
    *area = 0;
  Append(intval);

  return(*this);
}

/******************************************************************************/
/**
\brief  i03 - 



\param  n_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

NString &NString :: operator= (NString &n_string )
{

  if ( area )
    *area = 0;
  Append(n_string);

  return(*this);
}

/******************************************************************************/
/**
\brief  i04 - 



\param  val64 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

NString &NString :: operator= (int64 val64 )
{

  if ( area )
    *area = 0;
  Append(val64);

  return(*this);
}

/******************************************************************************/
/**
\brief  ~NString - 




*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~NString"

     NString :: ~NString ( )
{



}


