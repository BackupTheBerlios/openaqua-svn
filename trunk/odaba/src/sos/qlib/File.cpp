/********************************* Class Source Code ***************************/
/**
\package  SOS - Accept a Connection
\class    File

\brief    


\date     $Date: 2006/07/12 19:12:16,65 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "File"

#include  <pdefault.h>
#include  <fileacc.h>
#include  <sFile.hpp>


/******************************************************************************/
/**
\brief  AlignText - 


\return term - Success

\param  string - String value
\param  maxlen - 
\param  size - 
\param  indent - 
\param  align_type - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AlignText"

logical File :: AlignText (char *string, int32 maxlen, uint16 size, uint16 indent, TextAlignment align_type )
{
  int32         len     = size-indent;
  int32         wcount;
  int32         icount;
  int32         wlen;
  int32         ilen;
  int32         skip;
  int32         last_skip;
  uchar        *ustring = (uchar *)string;
  uchar        *last_pos;
  uchar        *pos;
  NString       nstring;
  NString       temp_nstring;
  logical       line_end;
  logical       term = NO;

BEGINSEQ
  if ( len <= 0 )                                SOSERR(99)
  
  if ( maxlen )
  {
    temp_nstring.Append((char *)ustring,maxlen);
    ustring = (uchar *)(char *)temp_nstring;
  }
   
  while ( *ustring )
  {
    if ( indent )
      nstring.Append(' ',indent);
      
    while ( *ustring && (*ustring == ' ' || *ustring == '\t') )
      ustring++;
      
    last_pos = NULL;
    wcount = 0;
    for ( pos=ustring; *pos && pos-ustring < len; )
    {
      wlen=0;
      line_end = NO;
      
      while ( pos && *pos <= ' ' )
      {
        if ( *pos == '\r' || *pos == '\n' )
        {
          line_end = YES;
          while ( *(++pos) && (*pos == '\r' || *pos == '\n') ) ;
        }
        else 
          pos++;
      }
      if ( line_end )
        break;
        
      for ( wlen = 0; *pos > ' '; wlen++ )
        pos++;
      
      if ( wlen > 0 && (pos-ustring < len || !last_pos) )
      {
        last_pos = pos;
        if ( wlen > len )
          last_pos = ustring+len;
      }
      wcount++;
    }
    
    if ( last_pos )                                  
    {
      if ( !*last_pos )
        line_end = YES;    
      switch ( align_type )
      {
        case TA_block    : if ( !line_end && (icount = len-(last_pos-ustring)) )
                           {
                             skip = wcount/icount;
                             ilen = icount/wcount + (icount%wcount ? 1 : 0);
                             last_skip = skip;
                             while ( ustring < last_pos )
                             {
                               while ( *ustring > ' ' && ustring < last_pos )
                               {
                                 nstring.Append((char)*ustring);
                                 ustring++;
                               }
                               if ( last_skip >= skip -1 )
                               {
                                 nstring.Append(' ',ilen);
                                 icount -= ilen;
                                 if ( icount < ilen )
                                   ilen = icount;
                                 last_skip = 0;
                               }
                               last_skip++;
                               while ( *ustring <= ' ' && ustring < last_pos )
                               {
                                 nstring.Append((char)*ustring);
                                 ustring++;
                               }
                             }
                           }
                           else
                             nstring.Append((char *)ustring,last_pos-ustring);
                           break;
        case TA_centered : 
        case TA_right    : nstring.Append(' ',(len-(last_pos-ustring))/align_type);
        case TA_left     : 
        default          : nstring.Append((char *)ustring,last_pos-ustring);
                           break;
      }
      if ( !line_end )
        nstring += "\r\n";
      ustring = last_pos;
      if ( line_end )
      {
        nstring.Append((char *)ustring,pos-ustring);
        ustring = pos;
      }
    }
    else if ( pos > ustring )
    {
      nstring.Append((char *)ustring,pos-ustring);
      ustring = pos;
    }
  }
  if ( !nstring.IsEmpty() )
    Out(nstring);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Close - 


\return term - Success

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Close"

logical File :: Close ( )
{

  if ( filhandle )
  {
    if ( !curline.IsEmpty() )
      fwrite(curline.GetArea(),(unsigned int)strlen(curline.GetArea()),1,filhandle);
      
    fclose(filhandle);
    filhandle = NULL;
  }
  
  stsrerr();

  return(NO);
}

/******************************************************************************/
/**
\brief  CurrentLine - 


\return line_cnt - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CurrentLine"

int32 File :: CurrentLine ( )
{

  return(linecount);

}

/******************************************************************************/
/**
\brief  File - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "File"

     File :: File ( )
                     : sts (),
  filpath(NULL),
  filhandle(NULL),
  accmode(PI_Read),
  net_opt(NO),
  file_len(0),
  linecount(0),
  curline(NULL,4096),
  formatline(NULL,4096)
{



}

/******************************************************************************/
/**
\brief  FormatParm - 


\return term - Success

\param  parm_string - 
\param  index_ref - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FormatParm"

logical File :: FormatParm (char *parm_string, uint16 &index_ref )
{
  char        *pos  = parm_string;
  logical      term = NO;
BEGINSEQ
  if ( !parm_string )
    index_ref++;
  else
  {
    if ( formatline.ReplaceSymbol("%s",parm_string,index_ref) ) 
                                                     ERROR
    while ( pos = strstr(pos,"%s") )
    {
      index_ref++;
      pos++;
    }
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  IsOpened - 


\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsOpened"

logical File :: IsOpened ( )
{

  return ( filhandle && !stscerr() ? YES : NO );

}

/******************************************************************************/
/**
\brief  LinePosition - 


\return term - Success

\param  pos - 
\param  min_forward - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "LinePosition"

logical File :: LinePosition (uint16 pos, int16 min_forward )
{
  int32       diff = pos - strlen(curline.GetArea());      
  logical     term = NO;
BEGINSEQ
  if ( pos < 1 )                                     ERROR
    
  curline.Resize(pos);
  pos--;
  diff = pos - strlen(curline.GetArea());  
  
  if ( !diff )
  {
    if ( min_forward <= 0 )                          LEAVESEQ
    diff = min_forward;
  }
    
  if ( diff > 0 )
  {
    if ( curline.Append(' ',diff) )                  ERROR
  }
  else
    if ( min_forward == AUTO )
      curline.GetArea()[pos] = 0;


RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Open - 


\return term - Success
-------------------------------------------------------------------------------
\brief  i00 - 


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical File :: Open ( )
{
#ifdef __unix__
  struct stat  statbuffer;
#endif
  char     accstr[6];
  logical  exist;
  logical  term = NO;
BEGINSEQ
  if ( filhandle )                                   LEAVESEQ
  if ( stscerr() )                                   LEAVESEQ
    
  curline   = "";
  linecount = 1;
  
  exist = IsFile(filpath);
   
  switch ( accmode )
  {
    case PI_Write  : strcpy(accstr,"w+");
                     break;
    case PI_Update : if ( exist )
                       strcpy(accstr,"r+");
                     else
                       strcpy(accstr,"w+");
                     break;
    case PI_Read   : 
    default        : if ( !exist )                   SOSERR(21)
                     strcpy(accstr,"r");
                     break;
  }
  strcat(accstr,"b");
  
  if ( !(filhandle = fopen(filpath,accstr)) )        SOSERR(1)
#ifdef __unix__
  fstat(fileno(filhandle), &statbuffer);
  file_len = statbuffer.st_size;
#else  
  file_len = filelength(fileno(filhandle));
#endif
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 


\param  cpath - Complete path
\param  acc_opt - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical File :: Open (char *cpath, PIACC acc_opt )
{
  logical                 term = NO;
BEGINSEQ
  Close();
  
  if ( !cpath )
    cpath = filpath;
    
  if ( filpath && strcmp(filpath,cpath) )
  {
    free(filpath);
    filpath = NULL;
  }

  if ( !filpath )
    filpath = strdup(cpath);
  accmode = acc_opt;

  if ( Open() )                                      ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Out - 


\return term - Success

\param  format_string - 
\param  parm1 - First Message parameter
\param  parm2 - Second message variable
\param  parm3 - Third message variable
\param  parm4 - 
\param  parm5 - 
\param  parm6 - 
\param  parm7 - 
\param  parm8 - 
\param  parm9 - 
\param  parm10 - 
\param  parm11 - 
\param  parm12 - 
\param  parm13 - 
\param  parm14 - 
\param  parm15 - 
\param  parm16 - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Out"

logical File :: Out (char *format_string, char *parm1, char *parm2, char *parm3, char *parm4, char *parm5, char *parm6, char *parm7, char *parm8, char *parm9, char *parm10, char *parm11, char *parm12, char *parm13, char *parm14, char *parm15, char *parm16 )
{
  char       *pos       = NULL;
  char       *last_pos  = NULL;
  char        next_char = 0;
  uint16      index     = 1;
  logical     term      = NO;
BEGINSEQ
  if ( !filhandle )                                 SOSERR(1)
    
  formatline = format_string;
  formatline.ReplaceControlSequences();
  
  term = FormatParm(parm1,index)  ||
         FormatParm(parm2,index)  ||
         FormatParm(parm3,index)  ||
         FormatParm(parm4,index)  ||
         FormatParm(parm5,index)  ||
         FormatParm(parm6,index)  ||
         FormatParm(parm7,index)  ||
         FormatParm(parm8,index)  ||
         FormatParm(parm9,index)  ||
         FormatParm(parm10,index) ||
         FormatParm(parm11,index) ||
         FormatParm(parm12,index) ||
         FormatParm(parm13,index) ||
         FormatParm(parm14,index) ||
         FormatParm(parm15,index) ||
         FormatParm(parm16,index);

  curline += formatline;
  if ( *formatline && formatline[strlen(formatline)-1] == ' ' )  
    curline += ' ';
    
  pos = curline.GetArea();
  while ( pos = strstr(pos,"\n") )
  {
    last_pos = pos;
    pos++;
    linecount++; 
  }
  
  if ( !last_pos )                                   LEAVESEQ
    
  last_pos++;
  next_char = *last_pos;
  *last_pos = 0;
  
  if ( !fwrite(curline.GetArea(),(unsigned int)strlen(curline.GetArea()),1,filhandle) )
                                                     SOSERR(1)
  *last_pos  = next_char;
  formatline = last_pos;
  curline    = formatline.GetArea();

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  ~File - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~File"

     File :: ~File ( )
{

  if ( filpath )
    free(filpath);


}


