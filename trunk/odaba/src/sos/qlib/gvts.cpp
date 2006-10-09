/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    gvts

\brief    Text String service functions


\date     $Date: 2006/07/12 12:48:35,50 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "gvts"

#include  <cpardef.h>
#include  <pdefault.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <string.h>
#include  <igvts.h>
#include  <igvtu.h>

#include  <igvts.h>

/******************************************************************************/
/**
\brief  CompleteExpression - 


\return expressin - 

\param  expression - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CompleteExpression"

char *__cdecl CompleteExpression (char *expression )
{
  char                   *expr = NULL;
BEGINSEQ
    if ( !expression || !*expression )               LEAVESEQ
    
    expr = (char *)malloc(strlen(expression)+10);
    *expr = 0;
    if ( *expression != '{' )
      strcat(expr,"{");
    strcat(expr,expression);
    if( expr[strlen(expr)-1] != ';' )
      strcat(expr,";");
    if ( *expression != '{' )
      strcat(expr,"};");

ENDSEQ
  return(expr);
}

/******************************************************************************/
/**
\brief  ContainsText - 


\return cond - Return value

\param  string - String value
\param  reg_string - Regular string expression
\param  max_len - maximum text length
\param  case_opt - Case sensitive (not supported)
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ContainsText"

logical __cdecl ContainsText (char *string, char *reg_string, int32 max_len, logical case_opt )
{
  int                     len = max_len;
  char                   *str = NULL;
  logical                 word_beg = YES;
  logical                 word_end = YES;
  char                   *sstr = NULL;
  int                     slen;
  int                     val;
  int                     sval;
  logical                 search_word = NO;
  logical                 first = YES;
  logical                 cond = NO;
BEGINSEQ
  if ( !len )
    len = strlen(string);

  sstr = ReplaceControlSequences(reg_string,len,YES);
  
  if ( !reg_string )                                 ERROR
  if ( !sstr )
    sstr = strdup( reg_string + (*reg_string == '*' ? 1 : 0) );
  else if ( *reg_string == '*' )
    sstr = strcpy(reg_string,reg_string+1);
  
  if ( *reg_string == '*' )
    word_beg = NO;
  if ( sstr[strlen(sstr)-1] == '*' )
  {
    sstr[strlen(sstr)-1] = 0;
    word_end = NO;
  }

  slen = strlen(sstr);
  sval = case_opt ? *sstr : toupper(*sstr);
  search_word = isalpha(sval) || isdigit(sval);

  while ( len >= slen )
  {
    if ( !(val = case_opt ? *string : toupper(*string)) )
      break;
    string++;
    len--;
    if ( val == sval )  
    {
      if ( search_word && word_beg && !first )
      {
        val = *(string-2);
        if ( isalpha(val) || isdigit(val) )
          continue;
      }
      first = NO;
      if ( case_opt )
      {
        if ( memcmp(string,sstr+1,slen-1) )
          continue;
      }
      else
        if ( gvtsicmp(string,sstr+1,slen-1) )
          continue;
      val = *(string+slen-1);
      if ( !word_end || len == slen-1 || !search_word || (!isalpha(val) && !isdigit(val)) )
      {
        cond = YES;
        break;
      }
    }
    first = NO;
  }

RECOVER
  cond = YES;
ENDSEQ
  if ( sstr )
    free(sstr);
  return(cond);
}

/******************************************************************************/
/**
\brief  GetExpressionBegin - 


\return endpos - 

\param  startpos - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExpressionBegin"

char *__cdecl GetExpressionBegin (char *startpos, int int_len )
{
  char                     op;
  char                    *newpos;
  ParenthethisDefinition  *pd;
  ParenthethisDefinition  *pardef;
  char                     cp = *(--startpos);
BEGINSEQ
  if ( --int_len < 1 )                               ERROR
  if ( !(pardef = GetStartChar(cp)) )                SOSERR(12)
  op = pardef->op;

  while( --int_len )
  {
    startpos--;
    if ( *(startpos-1) != '\\' )
    {
      if ( *startpos == cp )
        break;
      if ( (pd = GetStartChar(*startpos)) && pd->priority >= pardef->priority )
      {
        if ( !(newpos = GetExpressionBegin(startpos+1,int_len)) ) ERROR
        if ( (int_len -= startpos - newpos) <= 0 )
          break;
        startpos = newpos;
      }
    }  
  }  
  
  if ( int_len <= 0 )                                ERROR

RECOVER
  startpos = NULL;

ENDSEQ
  return(startpos);
}

/******************************************************************************/
/**
\brief  GetExpressionEnd - 


\return endpos - 

\param  startpos - 
\param  int_len - 
\param  ignore_last - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetExpressionEnd"

char *__cdecl GetExpressionEnd (char *startpos, int int_len, logical ignore_last )
{
  char                     op = *startpos;
  char                    *newpos;
  ParenthethisDefinition  *pd;
  ParenthethisDefinition  *pardef;
  char                     cp;
BEGINSEQ
  if ( !(pardef = GetStopChar(op)) )                 SOSERR(12)
  cp = pardef->cp;

  if ( !int_len )
     int_len = strlen(startpos);
  
  while( --int_len )
  {
    startpos++;
    if ( *(startpos-1) != '\\' )
    {
      if ( *startpos == cp )
        break;
      if ( (pd = GetStopChar(*startpos)) && pd->priority >= pardef->priority )
      {
        if ( !(newpos = GetExpressionEnd(startpos,int_len,ignore_last)) ) ERROR
        if ( (int_len -= newpos-1 - startpos) <= 0 )
          break;
        startpos = newpos-1;
      }
    }
  }  
  
  if ( int_len + ignore_last <= 0 )                  ERROR
  startpos++;

RECOVER
  startpos = NULL;

ENDSEQ
  return(startpos);
}

/******************************************************************************/
/**
\brief  GetKeyParm - 


\return parm_string - 

\param  string - String value
\param  keyword - 
\param  compress_opt - 
\param  ignore_last - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetKeyParm"

char *__cdecl GetKeyParm (char *string, char *keyword, logical compress_opt, logical ignore_last )
{
  char     *workstr     = NULL;
  char     *parm_string = NULL;
  char     *pos;
  char     *end         = NULL;
  int32     klen;
  ParenthethisDefinition  *pd;
BEGINSEQ
  if ( !string  || !*string ||
       !keyword || !*keyword        )                 ERROR
  
  SOSEV1(keyword,0)
  SOSEV2(string,0)
  
  klen = strlen(keyword);
  workstr = strdup(string);
  pos = workstr;
  while ( pos = strstr(pos,keyword) )
  {
    pos += klen;
    if ( !isalnum(*pos) && *pos != '_' )
      break; 
  }

  if ( pos )
  {
    pos--;
    while ( *(++pos) )
      if ( *pos != ' ' )
        break;
      else if ( !parm_string )
        parm_string = strdup("");
    if ( !*pos )                                     LEAVESEQ
      
    if ( !(end = GetExpressionEnd(pos,UNDEF,ignore_last)) )   
    {
      if ( *pos && *pos != ':' && GetStopChar(*pos) )SOSERR(16)
      // empty parameter: returns ""
      if ( !parm_string )
        parm_string = strdup("");
    }
    if ( !*pos )                                     LEAVESEQ
      
    if ( (pd = GetStopChar(*pos)) && *(end-1) == pd->cp )
      *(end-1) = 0;
   
    parm_string = strdup(pos+1);
    
    if ( compress_opt )
      STRExchange(parm_string," ","",strlen(parm_string));
  }

RECOVER

ENDSEQ
  if ( workstr )
    free(workstr);
  return(parm_string);
}

/******************************************************************************/
/**
\brief  GetParmKey - 


\return parm_string - 

\param  string - String value
\param  keyword_ptr - 
\param  compress_opt - 
\param  ignore_last - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmKey"

char *__cdecl GetParmKey (char *string, char **keyword_ptr, logical compress_opt, logical ignore_last )
{
  char     *workstr     = NULL;
  char     *parm_string = NULL;
  char     *pos;
  char     *epos;
  char      last;
BEGINSEQ
  if ( !string  || !*string ||
       !keyword_ptr              )            ERROR
  *keyword_ptr = NULL;
  
  SOSEV2(string,0)
  
  while ( *string )
    if ( *string != ' ' )
      break;
    else
      string++;
  workstr = strdup(string);
    
  epos = strchr(workstr,'=');
  if ( (pos = strchr(workstr,':')) && (!epos || epos > pos ) )
    epos = pos;
  if ( (pos = strchr(workstr,'(')) && (!epos || epos > pos ) )
    epos = pos;
  if ( (pos = strchr(workstr,';')) && (!epos || epos > pos ) )
    epos = pos;
    
  if ( !epos )
    epos = workstr+strlen(workstr);
  while ( epos > workstr )
    if ( *(--epos) != ' ' )
      break;
  
  if ( epos <= workstr )                    ERROR
    
  last = *(++epos);
  *epos = 0;
  *keyword_ptr = strdup(workstr);
  *epos = last;
  parm_string = GetKeyParm(workstr,*keyword_ptr,compress_opt,ignore_last);

RECOVER
  if ( *keyword_ptr )
    free(*keyword_ptr);
  *keyword_ptr = NULL;

ENDSEQ
  if ( workstr )
    free(workstr);
  return(parm_string);
}

/******************************************************************************/
/**
\brief  GetParmPos - 


\return parm_no - Parm number

\param  string - String value
\param  parm_string - 
\param  separator - Separator character
\param  compress_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmPos"

int32 __cdecl GetParmPos (char *string, char *parm_string, char separator, logical compress_opt )
{
  char     *workstr     = NULL;
  char     *pos         = NULL;
  int32     parm_no     = 0;
BEGINSEQ
  if ( !string  || !*string || !parm_string || !*parm_string )
                                                     ERROR
  SOSEV2(string,0) 
 
  workstr = strdup(string);
  if ( separator == ' ' )
    while ( strstr(workstr,"  ") )
      STRExchange(workstr,"  "," ",strlen(workstr));
    
  pos = workstr;
  while ( pos = STRGetToken(pos,separator) )
  {
    parm_no++;
    if ( !strcmp(pos,parm_string) )                  LEAVESEQ
    pos += (strlen(pos)+1);
    if ( pos >= workstr + strlen(string) )           ERROR
  }

  ERROR
RECOVER
  parm_no = 0;
ENDSEQ
  if ( workstr )
    free(workstr);
  return(parm_no);
}

/******************************************************************************/
/**
\brief  GetParmString - 


\return string - String value

\param  string - String value
\param  argc - 
\param  argv[] - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetParmString"

char *__cdecl GetParmString (char *string, int argc, char *argv[] )
{
  int                 i = 0;
  string[0] = 0;

  while ( ++i < argc )
    strcat(strcat(string,argv[i])," ");
  return(string);
}

/******************************************************************************/
/**
\brief  GetPosParm - 


\return parm_string - 

\param  string - String value
\param  parm_no - Parm number
\param  separator - Separator character
\param  compress_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetPosParm"

char *__cdecl GetPosParm (char *string, int32 parm_no, char separator, logical compress_opt )
{
  char     *workstr     = NULL;
  char     *parm_string = NULL;
  char     *pos;
  char     *end;
  char     *newpos;
  int       len;
  logical   first = YES;
BEGINSEQ
  if ( !string  || !*string || parm_no < 1 )        ERROR
  
  SOSEV2(string,0)
 
  workstr = strdup(string);
  if ( separator == ' ' )
    while ( strstr(workstr,"  ") )
      STRExchange(workstr,"  "," ",strlen(workstr));
    
  pos = workstr;
  len = strlen(pos);
  --parm_no;
  while( parm_no && len )
  {
    if ( *pos == separator )
    {
      parm_no--;
      pos++;
      len--;
    }
    else
    {
      if ( !first && *(pos-1) != '\\' && GetStopChar(*pos) )
      {
        if ( !(newpos = GetExpressionEnd(pos,len,NO)) ) ERROR
        if ( (len -= newpos - pos) < 0 )
          break;
        pos = newpos;
        if ( *(pos-1) == separator ) 
        {
          pos--;
          len++;
        }
      }
      else
      {
        pos++;
        len--;
      }
    }
    first = NO;
  }  
  
  if ( parm_no )                                     ERROR
  if ( !pos || !*pos )                               ERROR
  if ( end = strchr(pos,separator) )
    *end = 0;
  parm_string = strdup(pos);
    
  if ( compress_opt )
    STRExchange(parm_string," ","",strlen(parm_string));


RECOVER

ENDSEQ
  if ( workstr )
    free(workstr);
  return(parm_string);
}

/******************************************************************************/
/**
\brief  GetSearchStringCount - 


\return count - 

\param  string - String value
\param  search_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSearchStringCount"

int32 __cdecl GetSearchStringCount (char *string, char *search_string )
{
  char     *end        = NULL;
  int       search_len = 0;
  int32     count      = 0;
BEGINSEQ
  if ( !string  || !*string || !search_string || !*search_string )
                                                     ERROR
  end        = string + strlen(string);
  search_len = strlen(search_string);
  while ( end > string && gvtsscn(string,search_string) )
  {
    string += search_len;
    count++;
  }
RECOVER

ENDSEQ
  return(count);
}

/******************************************************************************/
/**
\brief  GetStartChar - 


\return stop_char - 

\param  stop_char - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStartChar"

ParenthethisDefinition *__cdecl GetStartChar (char stop_char )
{
  char        start_char = 0;
  int         count = sizeof(par_def)/sizeof(par_def[0]);
  while ( count )
    if ( par_def[--count].cp == stop_char )
      return(&par_def[count]);

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetStopChar - 


\return stop_char - 

\param  start_char - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStopChar"

ParenthethisDefinition *__cdecl GetStopChar (char start_char )
{
  char        stop_char = 0;;
  int         count = sizeof(par_def)/sizeof(par_def[0]);
  while ( count )
    if ( par_def[--count].op == start_char )
      return(&par_def[count]);

  return(NULL);

}

/******************************************************************************/
/**
\brief  GetStringValue - 


\return string - String value

\param  result_string - 
\param  source_string - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetStringValue"

char *__cdecl GetStringValue (char *result_string, char *source_string )
{
  int             len;
  char           *end;
BEGINSEQ
  if ( !result_string || !source_string )            ERROR
    
  if ( *source_string == '\'' )
  {
    if ( !(end = gvtsfbp(source_string,strlen(source_string))) )
                                                     ERROR
    len = end-1-(source_string+1);
    memcpy(result_string,source_string+1,len);
    result_string[len] = 0;
  }
  else
    strcpy(result_string,source_string);
  STRExchange(result_string,"\\'","'",strlen(result_string));
RECOVER
  result_string = NULL;
ENDSEQ
  return(result_string);
}

/******************************************************************************/
/**
\brief  GrtPropertyParms - 


\return string - String value

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GrtPropertyParms"

char *__cdecl GrtPropertyParms (char *string )
{
  int32     len;
  char     *pos = NULL;
BEGINSEQ
  SOSEV1(string,UNDEF);
  
  if ( !string )                                     ERROR
  string--;
  len = strlen(string);
  
  if ( !(*string == '}' || *string == ']' || *string == ')') )
                                                     ERROR
  if ( !(pos = gvtsfbpb(string+1,len)) )             SOSERR(19)
  

RECOVER
  pos = NULL;
ENDSEQ
  return(pos);
}

/******************************************************************************/
/**
\brief  InsertCharBefore - 


\return string - String value

\param  string - String value
\param  new_char - 
\param  search_char - 
\param  maxlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "InsertCharBefore"

char *__cdecl InsertCharBefore (char *string, char new_char, char search_char, int32 maxlen )
{
  char      *work_str = NULL;
  char      *str = string;
  char      *pos;
BEGINSEQ
  if ( !string || !*string )                         ERROR

  pos = work_str = strdup(string);

  while ( *pos && maxlen )
  {
    if ( *pos == search_char )
    {
      *str = new_char;
      str++;
      maxlen--;
    }
    if ( maxlen )
    {
      *str = *pos;
      str++;
      pos++;
      maxlen--;
    }
  }
  if ( maxlen > 0 )
    *str = 0;

RECOVER
  string = NULL;
ENDSEQ
  if ( work_str )
    free(work_str);
  return(string);
}

/******************************************************************************/
/**
\brief  IsValid - 


\return cond - Return value

\param  buffer - 
\param  int_len - 
\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical __cdecl IsValid (char *buffer, int int_len, char *string )
{
  logical                 cond = YES;
BEGINSEQ
  while ( int_len-- )
  {
    if ( !strchr(string,*buffer) )                   ERROR
    buffer++;
  }

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  NextProperty - 


\return string - String value

\param  string - String value
\param  expr_pos - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NextProperty"

char *__cdecl NextProperty (char *string, char **expr_pos )
{
  char     *pos = NULL;
  char     *blank;
  char     *end;
  char     *par;
  char     *par1;
BEGINSEQ
  SOSEV1(string,UNDEF);
  
  *expr_pos = NULL;
  pos = STRSearchChar(string,'.',NO);
  blank = STRSearchChar(string,' ',NO);
  if ( blank && blank < pos )
    pos = 0;
  
  par = STRSearchChar(string,'{',NO);
  if ( par1 = STRSearchChar(string,'[',NO) )
    par = par ? MIN(par,par1) : par1;
  if ( par1 = STRSearchChar(string,'(',NO) )
    par = par ? MIN(par,par1) : par1;
  
  if ( blank && blank < par )
    par = NULL;
  
  if ( !par || (pos && par > pos) )                  LEAVESEQ
    
  if ( !(end = gvtsfbp(par,UNDEF)) )                 SOSERR(19)
  if ( !*end )
    pos = NULL;
  else if ( *end == '.' )
    pos = end;
  else                                               SOSERR(18)
    
  *expr_pos = par;
RECOVER
  pos = NULL;
ENDSEQ
  return(pos);
}

/******************************************************************************/
/**
\brief  PrevProperty - 


\return string - String value

\param  string - String value
\param  expr_pos - 
\param  len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "PrevProperty"

char *__cdecl PrevProperty (char *string, char **expr_pos, size_t len )
{
  char     *pos = NULL;
  char      par;
  char     *begin;
BEGINSEQ
  SOSEV1(string,UNDEF);
  
  *expr_pos = NULL;
  if ( *string && *string != '.' )                   SOSERR(18)
  
  begin = string-len;
  string--;
  
  if ( *string == '}' || *string == ']' || *string == ')' )
  {
    if ( !(string = gvtsfbpb(string+1,len)) )      SOSERR(19)
    par        = *string;
    *expr_pos  = string;
    **expr_pos = 0;
  }
  
  pos = STRSearchChar(begin,'.',YES);
  if ( *expr_pos )
    **expr_pos = par;

RECOVER
  pos = NULL;
ENDSEQ
  return(pos);
}

/******************************************************************************/
/**
\brief  ReplaceControlSequences - Replece control characters
        The  function replaces control  character sequences (
,  
,       ) by the
        internal  control characters. When passing YES (true) fir duplicate, the
        string  is duplicated, when it  contains control sequences. The function
        returns  a pointer to the duplicated string, when it has been duplicated
        and  NULL  otherwise.  When  returning  a  string  pointer,  the calling
        function  is  responsible  to  release  the  string  with  the  free() 
        function..

\return string - String value

\param  string - String value
\param  lmaxlens - 
\param  duplicate - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceControlSequences"

char *__cdecl ReplaceControlSequences (char *string, int32 lmaxlens, logical duplicate )
{
  char                *str = NULL;
  char                *start = string;
  char                 ch;
  char                *pos   = NULL;
  char                *pos1  = NULL;
  char                *pos2  = NULL;
  char                 eins[2] = {1,0};

BEGINSEQ
  if ( !string )                                     ERROR
  if ( strlen(string) < 2 )                          LEAVESEQ
  if ( duplicate )
  {
    if ( !strchr(string,'\\') )                      LEAVESEQ
    start = str = strdup(string);
  }

  while ( start && ((pos1 = strchr(start,'\'')) || (pos2 = strchr(start,'"'))) )
  {
    if ( !(pos = MIN(pos1,pos2)) )
      pos = MAX(pos1,pos2);
      
    ch = *pos;
    *pos = 0;
    ReplaceControlSequences(start,UNDEF,NO);
    string = start+strlen(start);
    strcpy(string+1,pos+1);
    pos = string;
    *pos = ch;
    start = gvtsfbp(pos,UNDEF);
    pos2  = NULL;
  }
  
  if ( start )
  {
    STRExchange(start,"\\\\",eins,lmaxlens);
    STRExchange(start,"\\n","\n",lmaxlens); 
    STRExchange(start,"\\r","\r",lmaxlens);
    STRExchange(start,"\\t","\t",lmaxlens);
    STRExchange(start,eins,"\\",lmaxlens);
  }
RECOVER
  str = NULL;
ENDSEQ
  return(str);
}

/******************************************************************************/
/**
\brief  STRCompare - 


\return cmpval - Comparision result

\param  string1 - 
\param  string2 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "STRCompare"

int __cdecl STRCompare (char *string1, char *string2 )
{
  int   cmpval = 0;
  if ( string1 && !string2 )
    cmpval = 1;
  else if ( !string1 && string2 )
    cmpval = -1;
  else if ( string1 && string2 )
    cmpval = strcmp(string1,string2);
  return(cmpval);
}

/******************************************************************************/
/**
\brief  STRContainsAlpha - 


\return cond - Return value

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "STRContainsAlpha"

logical __cdecl STRContainsAlpha (char *string )
{
  logical     cond = YES;
BEGINSEQ
  while ( *string != 0 )
  {
    if ( isalpha(*string) )                          LEAVESEQ
    string++;
  };
  
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  STRExchange - 


\return string - String value

\param  string - String value
\param  ostring - 
\param  nstring - 
\param  lmaxlens - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "STRExchange"

char *__cdecl STRExchange (char *string, char *ostring, char *nstring, int32 lmaxlens )
{

  /* to restore previous code "Insert" gvtsexx(...) and replace
             "cf(string+pos,ostring)" 
     with
             "strstr(string+pos,ostring)" */
  return gvtsexx(string,ostring,nstring,lmaxlens,gvtsscn);

}

/******************************************************************************/
/**
\brief  STRGetToken - 


\return string - String value

\param  string - String value
\param  sepchar - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "STRGetToken"

char *__cdecl STRGetToken (char *string, char sepchar )
{
  char   *pos;
BEGINSEQ
  if ( !string || !*string )                         ERROR
    
  if ( pos = strchr(string,sepchar) )
    *pos = 0;

RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  STRReplaceCharacter - 


\return count - 

\param  string - String value
\param  ichar - 
\param  ochar - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "STRReplaceCharacter"

int32 __cdecl STRReplaceCharacter (char *string, char ichar, char ochar )
{
  int32         count = 0;
BEGINSEQ
  if ( !string )                                    ERROR
  
  while ( string = strchr(string,ichar) )
  {
    *string = ochar;
    string++;
    count++;
  }

RECOVER
  count = AUTO;
ENDSEQ
  return(count);

}

/******************************************************************************/
/**
\brief  STRSearchChar - 


\return pos - 

\param  string - String value
\param  searchChar - 
\param  tail - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "STRSearchChar"

char *__cdecl STRSearchChar (char *string, char searchChar, logical tail )
{
  char    *pos = string+strlen(string);
BEGINSEQ
  if ( tail )
  {
    while ( pos > string )
      if ( *(--pos) == searchChar )                  LEAVESEQ
    pos = NULL;
  }
  else
    pos = strchr(string,searchChar);

ENDSEQ
  return(pos);
}

/******************************************************************************/
/**
\brief  STRToPosition - 


\return indx - 

\param  string - String value
\param  strcnt - 
\param  strarea_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "STRToPosition"

int32 __cdecl STRToPosition (char *string, int16 strcnt, char **strarea_ptr )
{
  register int indx = 0;

  if ( string )
  {
    while ( strcmp(strarea_ptr[indx],string)  &&  ++indx <= strcnt-1 ) ;

    if ( indx < strcnt )
      return(++indx);
  }
  return(0);


}

/******************************************************************************/
/**
\brief  gvtsapb - 


\return string - String value

\param  string - String value
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsapb"

char *__cdecl gvtsapb (char *string, int int_len )
{
  register    int j;

BEGINSEQ
  if ( (j=strlen(string))  >  int_len )           SOSERR(11)

  memset(&string[j],' ',int_len-j);
  string[int_len] = 0;
RECOVER
  string = NULL;
ENDSEQ
  return(string);

}

/******************************************************************************/
/**
\brief  gvtsbls - 


\return remstr - 

\param  string - String value
\param  remain - 
\param  buffer - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsbls"

char *__cdecl gvtsbls (char *string, int16 remain, char *buffer, int int_len )
{
  short      slen     = strlen(string);
  short      mlen     = 0;
  short      nxword   = 0;
  short      lastword = 0;

  if ( !slen ) 
    return(NULL);

  while ( (nxword += gvtuwfd(string+nxword,slen-nxword,' ')) < int_len   &&
           nxword  > lastword                                               )
    lastword = nxword;

  if ( lastword == nxword )
    nxword = slen;

  if ( (mlen = gvtutle(string,nxword)) <= int_len )
  {
    memcpy(buffer,string,mlen);
    return(string[nxword]  ?  string+nxword : NULL);
  }

  if ( !lastword  ||   slen-lastword > remain )
  {
    memcpy(buffer,string,int_len);
    return(string+int_len);
  }

  memcpy(buffer,string,lastword);
  return(string+lastword);

}

/******************************************************************************/
/**
\brief  gvtscat - 


\return string - String value

\param  targ_string - 
\param  maxlen - 
\param  string1 - 
\param  string2 - 
\param  string3 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtscat"

char *__cdecl gvtscat (char *targ_string, int32 maxlen, char *string1, char *string2, char *string3 )
{


BEGINSEQ
  if ( strlen(targ_string) + strlen(string1) +
       ( string2 ? strlen(string2) : 0 )     +
       ( string3 ? strlen(string3) : 0 )         > maxlen )
                                                     SOSERR(11)  

  strcat(targ_string,string1);
  if ( string2 )
    strcat(targ_string,string2);
  if ( string3 )
    strcat(targ_string,string3);

RECOVER
  targ_string = NULL;
ENDSEQ
  return(targ_string);
}

/******************************************************************************/
/**
\brief  gvtscct - 


\return string - String value

\param  string - String value
\param  sign - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtscct"

char *__cdecl gvtscct (char *string, char sign )
{
  char     *str = string;

  while ( *str )
  {
    if ( *str <= ' ' )
      *str = sign;
    str++;
  }

  return(string);

}

/******************************************************************************/
/**
\brief  gvtschs - 


\return remstr - 

\param  string - String value
\param  sepchar - 
\param  buffer - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtschs"

char *__cdecl gvtschs (char *string, char sepchar, char *buffer, int int_len )
{
  char       *remstr;

  if ( remstr = strchr(string,sepchar) )
  {
    memcpy(buffer,string,MIN(int_len,remstr-string));
    return(++remstr);
  }

  memcpy(buffer,string,MIN(int_len,(int)strlen(string)));
  return(NULL);



}

/******************************************************************************/
/**
\brief  gvtscin - 


\return string - String value

\param  string - String value
\param  ichar - 
\param  num - 
\param  lmaxlens - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtscin"

char *__cdecl gvtscin (char *string, char ichar, int16 num, int32 lmaxlens )
{
  register    int j = strlen(string);

BEGINSEQ
  if ( j + num >= lmaxlens )                       SOSERR(11)

  string[j+num] = 0;
  while ( j-- )
    string[j+num] = string[j];

  memset(string,ichar,num);
RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  gvtsexc - 


\return string - String value

\param  string - String value
\param  ostring - 
\param  nstring - 
\param  lmaxlens - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsexc"

char *__cdecl gvtsexc (char *string, char *ostring, char *nstring, int32 lmaxlens )
{


  return STRExchange(string,ostring,nstring,lmaxlens);

}

/******************************************************************************/
/**
\brief  gvtsexi - 


\return string - String value

\param  string - String value
\param  ostring - 
\param  nstring - 
\param  lmaxlens - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsexi"

char *__cdecl gvtsexi (char *string, char *ostring, char *nstring, int32 lmaxlens )
{


  return gvtsexx(string,ostring,nstring,lmaxlens,gvtsiscn);

}

/******************************************************************************/
/**
\brief  gvtsexx - 


\return strptr - 

\param  string - String value
\param  ostring - 
\param  nstring - 
\param  lmaxlens - 
\param  cf)(char*,char*) - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsexx"

char *__cdecl gvtsexx (char *string, char *ostring, char *nstring, int32 lmaxlens, char *( __far __cdecl *cf)(char*,char*) )
{
  char         *ptr     = NULL;
  int           pos     = 0;
  int           olen    = ostring ? strlen(ostring) : 0;
  int           nlen    = nstring ? strlen(nstring) : 0;

BEGINSEQ
  if ( !string )                                     ERROR
  if ( !olen )                                       LEAVESEQ
    
  if ( !lmaxlens )
    lmaxlens = strlen(string);

  while ( ptr = cf(string+pos,ostring) )
  {
    pos = ptr - string;
    if ( olen == nlen )
      memcpy(string+pos,nstring,olen);
    else
    {
      if ( strlen(string) - olen + nlen > lmaxlens ) SOSERR(11)
      gvtssdl(string+pos,olen);
      gvtssin(string+pos,nstring,lmaxlens-pos);
    }
    if ( (pos += strlen(nstring)) >= lmaxlens )      LEAVESEQ
  }
RECOVER

ENDSEQ
  return(string);

}

/******************************************************************************/
/**
\brief  gvtsfac - 


\return estrn - 

\param  astrn - 
\param  vstrn - 
\param  nstrn - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsfac"

char *__cdecl gvtsfac (char *astrn, char *vstrn, char *nstrn )
{
 char   *eins  = "?"  ;
 int    fsize = strlen(astrn) ;
 int    i = 0 ;

  while ( (i = (int)strcspn( astrn , vstrn )) < fsize )
  {
    *eins = astrn[i] ;
    astrn[i] = nstrn[strcspn( vstrn , eins )] ;
  }
  return(astrn);

}

/******************************************************************************/
/**
\brief  gvtsfbp - 


\return endpos - 

\param  startpos - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsfbp"

char *__cdecl gvtsfbp (char *startpos, int int_len )
{
  int       parlev = 1;
  char      op = *startpos;
  char     *newpos;
  char      cp;

BEGINSEQ
  switch ( op )
  {
    case '(' : cp = ')';
               break;
    case '[' : cp = ']';
               break;
    case '{' : cp = '}';
               break;
    case '<' : cp = '>';
               break;
    case '®' : cp = '¯';
               break;
    case '"':  cp = '"';
               break;
    case '\'': cp = '\'';
               break;
    case '%' : cp = '%';
               break;
    default  :                                     SOSERR(12)
  }

  if ( !int_len )
     int_len = strlen(startpos);
  
  while( --int_len && parlev )
  {
    startpos++;
    if ( *startpos == cp && *(startpos-1) != '\\' )
      parlev--;
    else 
      if ( *startpos == op && *(startpos-1) != '\\' )
        parlev++;
  }  
  
  if ( parlev )                                        ERROR
  startpos++;

RECOVER
  startpos = NULL;

ENDSEQ
  return(startpos);
}

/******************************************************************************/
/**
\brief  gvtsfbpb - 


\return endpos - 

\param  startpos - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsfbpb"

char *__cdecl gvtsfbpb (char *startpos, int int_len )
{
  int       parlev = 1;
  char      cp = *(--startpos);
  char      op;
BEGINSEQ
  if ( --int_len < 1 )                                ERROR

  switch ( cp )
  {
    case ')' : op = '(';
               break;
    case ']' : op = '[';
               break;
    case '}' : op = '{';
               break;
    case '>' : op = '<';
               break;
    case '¯' : op = '®';
               break;
    case '"':  op = '"';
               break;
    case '\'': op = '\'';
               break;
    case '%' : op = '%';
               break;
    default  :                                    SOSERR(12)
  }

  while( --int_len && parlev )
  {
    startpos--;
    if ( *startpos == op && *(startpos-1) != '\\' )
      parlev--;
    else 
      if ( *startpos == cp && *(startpos-1) != '\\' )
        parlev++;
  }  
  
  if ( parlev )                                       ERROR
RECOVER
  startpos = NULL;

ENDSEQ
  return(startpos);

}

/******************************************************************************/
/**
\brief  gvtsicmp - 


\return cmpval - Comparision result

\param  string1 - 
\param  string2 - 
\param  maxlen_w - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsicmp"

int __cdecl gvtsicmp (char *string1, char *string2, int32 maxlen_w )
{
  int       len    = maxlen_w;
  int       val1   = 0;
  int       val2   = 0;
  int       i      = 0;
  int       cmpval = 0;
BEGINSEQ
  if ( !string1 || !string2 )
  {
    cmpval = string1 ?  1 : string2 ? -1 : 0;
    LEAVESEQ
    
  }

  if ( !len )
    len = strlen(string1);
    
  for ( i = 0; i < len && !cmpval; i++ )
  {
    if ( !(val1 = string1[i]) || !(val2 = string2[i]) )
    {
      cmpval = string1[i] - string2[i];
      LEAVESEQ
    }
  
    if ( isalpha(val1) )
      val1 = toupper(val1);
    if ( isalpha(val2) )
      val2 = toupper(val2);
    cmpval = val1 - val2;
  }
  
  if ( !cmpval && !maxlen_w && string2[i] )
    cmpval = -1;
ENDSEQ
  return(cmpval > 0 ? 1 : cmpval < 0 ? -1 : 0);
}

/******************************************************************************/
/**
\brief  gvtsiscn - 


\return strptr - 

\param  string - String value
\param  ostring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsiscn"

char *__cdecl gvtsiscn (char *string, char *ostring )
{
// performs sort of "char *stristr(char*,char*)"
  int  len    = 0;
  int  oupper = 0;
  int  olower = 0;
BEGINSEQ
  if ( !string || !ostring )                         ERROR
  if ( !*ostring )                                   LEAVESEQ
  
  len    = strlen(ostring);
  oupper = toupper(*ostring);
  olower = tolower(*ostring);
  
  while ( *string )
  {
    while ( *string != oupper && *string != olower )
      if ( !(*(++string)) )                          ERROR

    if ( !gvtsicmp(string,ostring,len) )             LEAVESEQ
    string++;
  }

  ERROR
RECOVER
  string = NULL;
ENDSEQ
  return(string);
}

/******************************************************************************/
/**
\brief  gvtslwr - 


\return string - String value

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtslwr"

char *__cdecl gvtslwr (char *string )
{
  char *pos = string;
  while ( *string != 0 )
  {
    *string = tolower(*string);
    string++;
  };
  string = pos;

  return(string);
}

/******************************************************************************/
/**
\brief  gvtsnck - 


\return term - Success

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsnck"

logical __cdecl gvtsnck (char *string )
{
  logical  blank = YES;
  logical  term  = NO;

BEGINSEQ
  while ( *string )
  {
    if ( !blank  ||  *string != ' ' )
    {
      blank = NO;
      if ( !isdigit(*string) )                        ERROR
    }
    string++;
  }
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  gvtsnicmp - 


\return cmpval - Comparision result

\param  string1 - 
\param  string2 - 
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsnicmp"

int __cdecl gvtsnicmp (char *string1, char *string2, int int_len )
{
// int   cmpval = 0;
// int   i      = 0;
BEGINSEQ
  return ( int_len ? gvtsicmp(string1,string2,int_len) : 0 );
/*
  for ( i = 0; !cmpval && i < int_len; i++ )
  {
    if ( !string1[i] || !string2[i] )
    {
      cmpval = string1[i] - string2[i];
      LEAVESEQ
    }
    else
    {
      if ( (string1[i] > 'Z') && (string1[i] < 'a') || 
           (string2[i] > 'Z') && (string2[i] < 'a')    )
        cmpval = string1[i] - string2[i];
      }
      else
        cmpval = toupper(string1[i]) - toupper(string2[i]);
    }
  };
*/
ENDSEQ
//  return(cmpval > 0 ? 1 : cmpval < 0 ? -1 : 0);
}

/******************************************************************************/
/**
\brief  gvtsopg - 


\return oprnd - 

\param  string - String value
\param  int_len_ptr - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsopg"

char *__cdecl gvtsopg (char *string, int *int_len_ptr )
{
  char     *opernd;

BEGINSEQ
  while ( *string && *string == ' ' ) 
    string++;

  if ( !*string || *string != '(' || 
       !(opernd = gvtsfbp(string,UNDEF))     )       ERROR

  string++;
  *int_len_ptr = opernd - string -1;
  opernd       = string;
RECOVER
  *int_len_ptr = UNDEF;
  opernd       = NULL;

ENDSEQ
  return(opernd);

}

/******************************************************************************/
/**
\brief  gvtsscn - 


\return strptr - 

\param  string - String value
\param  ostring - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsscn"

char *__cdecl gvtsscn (char *string, char *ostring )
{


  return strstr(string,ostring);
}

/******************************************************************************/
/**
\brief  gvtssdl - 


\return string - String value

\param  string - String value
\param  dcount - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtssdl"

char *__cdecl gvtssdl (char *string, int16 dcount )
{

  if ( strlen(string) <= (unsigned short int)dcount )
    *string = 0;
  else
    strcpy(string,string+dcount);

  return(string);

}

/******************************************************************************/
/**
\brief  gvtssin - 


\return string - String value

\param  string - String value
\param  istring - 
\param  maxlen - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtssin"

char *__cdecl gvtssin (char *string, char *istring, int32 maxlen )
{
  int     i = istring ? strlen(istring) : 0;
  int     j = string  ? strlen(string)  : 0;
BEGINSEQ
  if ( !string || !istring )                        ERROR
  if ( j + i > maxlen )                             SOSERR(11)

  while ( j >= 0 )
  {
    string[j+i] = string[j];
    j--;
  }
  
  while ( *istring )
    string[++j] = *(istring++);

RECOVER
  string = NULL;
ENDSEQ
  return(string);

}

/******************************************************************************/
/**
\brief  gvtssrt - 


\return string - String value

\param  string - String value
\param  int_len - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtssrt"

char *__cdecl gvtssrt (char *string, int int_len )
{
  register    int i;
  register    int j;

BEGINSEQ
  if ( (j=strlen(string))  >  (i = int_len) )      SOSERR(11)
  
  while ( j >= 0  &&  string[j] != ' ' )
    string[i--] = string[j--];

  memset(&string[j+1],' ',i-j);
RECOVER
  string = NULL;
ENDSEQ
  return(string);

}

/******************************************************************************/
/**
\brief  gvtsupr - 


\return string - String value

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtsupr"

char *__cdecl gvtsupr (char *string )
{
  char *pos = string;
  while ( *string != 0 )
  {
    *string = toupper(*string);
    string++;
  };
  string = pos;

  return(string);
}

