/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    Tools



\date     $Date: 2006/03/13 21:34:54,26 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   Tools_HPP
#define   Tools_HPP

class     Tools;

#define  Tools_TempCount                           16
#define  Tools_TempSize                            4096
#pragma pack(4)

class  Tools
{

public     :
public     : static  OGUI7ImpExp                 QString __cdecl ReplaceQStringChar (const QString &rcqsText, QChar vQChar, QChar vQCharNew );
public     : static                              void __cdecl __DCL_STATIC ( );
public     : static                              void __cdecl __DEF_STATIC ( );
public     : static  OGUI7ImpExp                 void __cdecl freetemp (void *pBuf );
public     : static  OGUI7ImpExp                 void *__cdecl gettemp (int32 iSize );
public     : static  OGUI7ImpExp                 void __cdecl itoxarray (void *pSrc, int32 iSrcLen, void *pDest, logical fPut0_NO=NO );
public     : static  OGUI7ImpExp                 int __cdecl lookup (const char *cszList, const char *cszText, char iDefault_AUTO=AUTO, char chDelimiter_Pipe='|', logical fCaseSensitive_NO=NO );
public     : static  OGUI7ImpExp                 int32 *__cdecl scanfori (int32 *plBuf, int32 iLen, int32 i );
public     : static  OGUI7ImpExp                 QCStringList __cdecl splitQCString (const QString &rcqc, const QCString &rcqcSep );
public     : static  OGUI7ImpExp                 char *__cdecl tempstrdup (char *szText );
public     : static  OGUI7ImpExp                 void __cdecl xtoiarray (void *pSrc, int32 iSrcLen, void *pDest );
public     : static  OGUI7ImpExp                 int32 __cdecl ilen (int32 iCount ){

return ( iCount / 5 ) * 4;

}

public     : static  OGUI7ImpExp                 void *__cdecl itox (int32 i, void *pBuf, logical fPut0_NO=NO ){

char* p= (char*) pBuf;
*(p++)= 32 + ( i & 127 );
*(p++)= 32 + ( i >> 7 ) & 127;
*(p++)= 32 + ( i >> 14 ) & 127;
*(p++)= 32 + ( i >> 21 ) & 127;
*(p++)= 32 + ( i >> 28 ) & 127;
if( fPut0_NO ) *p= 0;
return pBuf;
}

public     : static  OGUI7ImpExp                 int32 __cdecl xlen (int32 iCount ){

return ( iCount / 4 ) * 5;

}

public     : static  OGUI7ImpExp                 int32 __cdecl xtoi (void *pBuf ){

char* p= (char*) pBuf;
return   ( *(p) - 32 )
   | ( ( *(p+1) - 32 ) << 7 )
   | ( ( *(p+2) - 32 ) << 14 )
   | ( ( *(p+3) - 32 ) << 21 )
   | ( ( *(p+4) - 32 ) << 28 );


}

};

#pragma pack()
#endif
