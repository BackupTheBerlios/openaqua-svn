/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    Tools



\date     $Date: 2006/03/13 21:36:27,04 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "Tools"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sTools.hpp>


/******************************************************************************/
/**
\brief  ReplaceQStringChar

\return res -

\param  rcqsText -
\param  vQChar
\param  vQCharNew
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ReplaceQStringChar"

QString __cdecl Tools :: ReplaceQStringChar (const QString &rcqsText, QChar vQChar, QChar vQCharNew )
{

QString res= rcqsText;

for( int i= res.find( vQChar ); i >= 0; i= res.find( vQChar, i+1 ) )
  res[i]= vQCharNew;

return res;

}

/******************************************************************************/
/**
\brief  __DCL_STATIC


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "__DCL_STATIC"

void __cdecl Tools :: __DCL_STATIC ( )
{

}

char temps[Tools_TempCount][Tools_TempSize];
logical tempsUsed[Tools_TempCount];

void __nullTools0()
{


}

/******************************************************************************/
/**
\brief  __DEF_STATIC


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "__DEF_STATIC"

void __cdecl Tools :: __DEF_STATIC ( )
{

}

void __nullTools1()
{


}

/******************************************************************************/
/**
\brief  freetemp


\param  pBuf
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "freetemp"

void __cdecl Tools :: freetemp (void *pBuf )
{

BEGINSEQ
if( !pBuf ) ERROR
for( int i= 0; i < Tools_TempCount; i++ )
{
  if( pBuf == temps[i] )
  {
    tempsUsed[i]= NO;
    LEAVESEQ
  }
}
ERROR
RECOVER
free( pBuf );
ENDSEQ

}

/******************************************************************************/
/**
\brief  gettemp

\return res -

\param  iSize -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "gettemp"

void *__cdecl Tools :: gettemp (int32 iSize )
{

BEGINSEQ
if( iSize > Tools_TempSize ) ERROR

static RessourceLock lock;

lock.ILock();

for( int i= 0; i < Tools_TempCount; i++ )
{
  if( !tempsUsed[i] )
  {
    tempsUsed[i]= YES;
    lock.IUnlock();
    return temps[i];
  }
}
lock.IUnlock();
ERROR
RECOVER
return malloc( iSize );
ENDSEQ

}

/******************************************************************************/
/**
\brief  itoxarray


\param  pSrc
\param  iSrcLen
\param  pDest
\param  fPut0_NO
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "itoxarray"

void __cdecl Tools :: itoxarray (void *pSrc, int32 iSrcLen, void *pDest, logical fPut0_NO )
{

char* s= (char*) pSrc;
char* d= (char*) pDest;
while( iSrcLen > 0 )
{
  long i;
  LoadLong( i, s );
  itox( i, d );
  s+= 4;  
  d+= 5;
  iSrcLen-= 4;
}
if( fPut0_NO ) *d= 0;

}

/******************************************************************************/
/**
\brief  lookup

\return term -

\param  cszList
\param  cszText -
\param  iDefault_AUTO
\param  chDelimiter_Pipe
\param  fCaseSensitive_NO
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "lookup"

int __cdecl Tools :: lookup (const char *cszList, const char *cszText, char iDefault_AUTO, char chDelimiter_Pipe, logical fCaseSensitive_NO )
{
int idx= 0;
BEGINSEQ
if( !cszText ) cszText= "";

int tlen= strlen( cszText );

while( 1 )
{
  if( !*cszList )                                    ERROR
  
  logical fnd;
  
  fnd= ( fCaseSensitive_NO ? 
    strncmp( cszText, cszList, tlen ) :
    strnicmp( cszText, cszList, tlen ) ) == 0;
  
  fnd= fnd && (cszList[tlen] == 0 || cszList[tlen] == chDelimiter_Pipe );
  
  if( fnd ) break;
  
  idx++;
  while( *cszList )
  {
    if( *cszList == chDelimiter_Pipe ) 
    {
      cszList++;
      break;
    }
    cszList++;    
  }
}
RECOVER
idx= iDefault_AUTO;
ENDSEQ
return idx;
}

/******************************************************************************/
/**
\brief  scanfori

\return res -

\param  plBuf
\param  iLen
\param  i -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "scanfori"

int32 *__cdecl Tools :: scanfori (int32 *plBuf, int32 iLen, int32 i )
{

if( (((int) plBuf) % 4 ) == 0 )
{
  // faster
  int32 *pB= plBuf;
  while( iLen-- > 0 )
  {
    if( *pB == i ) return pB;
    pB++;
  }
}
else
{
  // slower
  int32 *pB= plBuf;
  while( iLen-- > 0 )
  {
    long l;
    LoadLong( l, pB );
    if( l == i ) return pB;
    pB++;
  }
}
return NULL;

}

/******************************************************************************/
/**
\brief  splitQCString

\return term -

\param  rcqc -
\param  rcqcSep
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "splitQCString"

QCStringList __cdecl Tools :: splitQCString (const QString &rcqc, const QCString &rcqcSep )
{

const QCString& str= rcqc;
const QCString& sep= rcqcSep;
// copied and adapted from QStringList::split
    QValueList<QCString> lst;

    int j = 0;
    int i = str.find( sep, j );

    while ( i != -1 ) {
        lst << str.mid( j, i - j );
	j = i + sep.length();
	i = str.find( sep, j );
    }

    int l = str.length() - 1;
    lst << str.mid( j, l - j + 1 );

    return lst;


}

/******************************************************************************/
/**
\brief  tempstrdup

\return res -

\param  szText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "tempstrdup"

char *__cdecl Tools :: tempstrdup (char *szText )
{

if( !szText ) return NULL;
long sl= strlen( szText ) + 1;
char* res= (char*) Tools::gettemp( sl );
memcpy( res, szText, sl );
return res;

}

/******************************************************************************/
/**
\brief  xtoiarray


\param  pSrc
\param  iSrcLen
\param  pDest
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "xtoiarray"

void __cdecl Tools :: xtoiarray (void *pSrc, int32 iSrcLen, void *pDest )
{

char* s= (char*) pSrc;
char* d= (char*) pDest;
while( iSrcLen > 0 )
{
  long i= xtoi( s );
  StoreLong( d, i );
  s+= 5;  
  d+= 4;
  iSrcLen-= 5;
}

}


