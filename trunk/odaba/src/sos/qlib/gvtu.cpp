/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    gvtu

\brief    


\date     $Date: 2006/03/12 19:22:33,81 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "gvtu"

#include  <pdefault.h>
#include  <ctype.h>

#include  <igvtu.h>

/******************************************************************************/
/**
\brief  gvtucat

\return overflow

\param  targbuf -
\param  targmlen
\param  srcebuf
\param  srcemlen
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtucat"

logical __cdecl gvtucat (char *targbuf, int32 targmlen, char *srcebuf, int32 srcemlen )
{
  int       srcelen  = gvtutle0(srcebuf,(int)srcemlen);
  int       targlen  = gvtutle0(targbuf,(int)targmlen);

  memcpy(targbuf+targlen,srcebuf,MIN((int)targmlen-targlen,srcelen));

  return(targlen + srcelen > (int)targmlen ? YES : NO);



}

/******************************************************************************/
/**
\brief  gvtucin

\return buffer -

\param  buffer -
\param  int_len -
\param  num -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtucin"

char *__cdecl gvtucin (char *buffer, int int_len, int16 num )
{
  short int     tlen;


  if ( (tlen = int_len - num) > 0 )
  {
     while ( (--tlen) >= 0 )
       buffer[tlen+num] = buffer[tlen];

     while ( (--num) >= 0 )
       buffer[num] = ' ';
  }

  return(buffer);

}

/******************************************************************************/
/**
\brief  gvtufck

\return term - Success

\param  buffer -
\param  int_len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtufck"

logical __cdecl gvtufck (char *buffer, int int_len )
{
  register int  i;
  logical       blank = YES;
  logical       point = YES;
  logical       sign  = YES;                    /* old: NO */
  logical       exp   = YES;
  logical       term  = NO;

BEGINSEQ
  for ( i=0; i < int_len; i++ )
    switch ( ( buffer[i] == ' '                      ) * 1   +
	     ( buffer[i] >= '0' && buffer[i] <= '9'  ) * 2   +
	     ( buffer[i] == 'e' || buffer[i] == 'E'  ) * 3   +
	     ( buffer[i] == '+' || buffer[i] == '-'  ) * 4   +
	     ( buffer[i] == '.'                      ) * 5     )
    {
      case  0 :                                      ERROR
      case  1 : if ( !blank )                        ERROR
		break;
      case  2 : blank = NO;
		sign  = NO;
		break;
      case  3 : if ( !exp  )                         ERROR
		exp   = NO;
		point = NO;
		sign  = YES;
		break;
      case  4 : if ( !sign )                         ERROR
		sign  = NO;
		break;
      case  5 : if ( !point )                        ERROR
		point = NO;
		sign  = NO;
		break;
    }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  gvtultu

\return buffer -

\param  buffer -
\param  int_len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtultu"

char *__cdecl gvtultu (char *buffer, int int_len )
{

  while ( int_len-- )
    buffer[int_len] = (char)toupper(buffer[int_len]);
  return(buffer);

}

/******************************************************************************/
/**
\brief  gvtussr

\return posb

\param  buffer -
\param  string - String value
\param  maxlen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtussr"

int32 __cdecl gvtussr (char *buffer, char *string, int32 maxlen )
{
  int       len      = strlen(string);
  char     *newpos;
  int32     curpos   = UNDEF;
  logical   notfound = YES;

BEGINSEQ
  if ( !len )                                        LEAVESEQ

  while ( curpos + len <= maxlen                         &&
          (newpos   = (char *)memchr(buffer+curpos,*string,(int)(maxlen-curpos))) &&
          (notfound = memcmp(newpos,string,len))             )
    curpos = newpos - buffer + 1;

  if ( notfound )                                    ERROR
  curpos = newpos - buffer;
RECOVER
  curpos = AUTO;

ENDSEQ
  return(curpos);

}

/******************************************************************************/
/**
\brief  gvtutcp

\return buffer -

\param  buffer -
\param  int_len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtutcp"

char *__cdecl gvtutcp (char *buffer, int int_len )
{
  short int   nxword = 0;
  char       *bpos = buffer;

  if ( *bpos == ' ' )
  {
    nxword = gvtuwfd(bpos,int_len,' ');
    memcpy(bpos,bpos+nxword,int_len-=nxword);
    memset(bpos+int_len,' ',nxword);
  }

  while ( nxword = gvtuwfd(bpos,int_len,' ') )
  {
    while ( int_len--  &&  nxword--  &&  *(bpos++) != ' '  ) ;
    memcpy(bpos,bpos+nxword,int_len-=nxword);
    memset(bpos+int_len,' ',nxword);
  }

  return(buffer);

}

/******************************************************************************/
/**
\brief  gvtutlb

\return buffer -

\param  buffer -
\param  int_len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtutlb"

char *__cdecl gvtutlb (char *buffer, int int_len )
{
  short int   cnt;
  short int   free;
  short int   ins = 0;
  short int   nxword = 0;
  char       *bpos = buffer;

  if ( (cnt  = gvtutwc(gvtutcp(buffer,int_len),int_len))   &&
       (free = int_len - gvtutle(buffer,int_len))               )
    while ( --cnt )
    {
      nxword = gvtuwfd(bpos+=ins,int_len-=ins,' ');
      free -= (ins = free/cnt);
      gvtucin(bpos+=nxword,int_len-=nxword,ins);
    }

  return(buffer);

}

/******************************************************************************/
/**
\brief  gvtutlc

\return buffer -

\param  buffer -
\param  int_len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtutlc"

char *__cdecl gvtutlc (char *buffer, int int_len )
{

  return ( gvtucin(buffer,int_len,(int_len-gvtutle(buffer,int_len))/2) );



}

/******************************************************************************/
/**
\brief  gvtutle

\return int_len -

\param  buffer -
\param  int_len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtutle"

int __cdecl gvtutle (char *buffer, int int_len )
{

  buffer+= (int_len-1);

  while ( *(buffer--) ==' ' && --int_len > 0) ;
  return( int_len > 0 ? int_len : 0 );



}

/******************************************************************************/
/**
\brief  gvtutle0

\return int_len -

\param  buffer -
\param  int_len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtutle0"

int __cdecl gvtutle0 (char *buffer, int int_len )
{
  int          len = 0;

  if ( int_len < 1 || !buffer )
    return(0);
    
  while( *buffer && len < int_len )
  {
    buffer++;
    len++;
  }

  while ( len && *(--buffer) == ' ' )
    len--;

  return(len);

}

/******************************************************************************/
/**
\brief  gvtutwc

\return cnt

\param  buffer -
\param  int_len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtutwc"

int16 __cdecl gvtutwc (char *buffer, int int_len )
{
  short int   pos = 0;
  short int   cnt = (*buffer == ' ' ? 0 : 1);

  while ( pos = gvtuwfd(buffer+=pos,int_len-=pos,' ') )
    cnt++;

  return(cnt);

}

/******************************************************************************/
/**
\brief  gvtuutl

\return buffer -

\param  buffer -
\param  int_len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtuutl"

char *__cdecl gvtuutl (char *buffer, int int_len )
{

  while ( int_len-- )
    buffer[int_len] = (char)tolower(buffer[int_len]);
  return(buffer);

}

/******************************************************************************/
/**
\brief  gvtuwfd

\return posn - Position relative 0

\param  buffer -
\param  int_len -
\param  sepchar -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gvtuwfd"

int16 __cdecl gvtuwfd (char *buffer, int int_len, char sepchar )
{
  short int   nxword = 0;

BEGINSEQ
  if ( *buffer != sepchar )
    while ( --int_len  &&  *(buffer+(++nxword)) != sepchar ) ;

  if ( !int_len )                                    ERROR

  while ( --int_len  &&  *(buffer+(++nxword)) == sepchar ) ;

  if ( !int_len )                                    ERROR

RECOVER
  nxword = 0;
ENDSEQ
  return(nxword);

}

