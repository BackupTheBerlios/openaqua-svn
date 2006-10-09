/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    bds

\brief    


\date     $Date: 2006/03/12 19:22:06,98 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "bds"

#include  <pdefault.h>
#include  <sbds.hpp>


/******************************************************************************/
/**
\brief  Append

\return term - Success

\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Append"

logical bds :: Append (char *string )
{
  int       applen = strlen(string);
  logical   term   = NO;
BEGINSEQ
  if ( bdslen + applen >= bdsmax )
  {
    bds   oldbds(bdsarea,bdslen,bdsmax);
    
    bdsarea = NULL;
    if ( bdsaloc(bdslen + applen + 1) )
    {
      bdsarea = oldbds.bdsagt();                    ERROR
    }
    *this + oldbds;
    
    oldbds.bdsfree();
  }
  
  *this + string;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Delete - 


\return term - Success

\param  pos -
\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Delete"

logical bds :: Delete (uint16 pos, size_t len )
{
  logical   term = NO;

BEGINSEQ
  if ( !bdsarea || bdslen >= bdsmax || pos >= bdslen )
                                                     ERROR
  *(bdsarea+bdslen) = 0;
  len = pos+len <= bdslen ? len : bdslen - pos;
  gvtssdl(bdsarea+pos,len);
  bdslen -= len;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  FindBalancedPar

\return position -

\param  curpos -
\param  bwd -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindBalancedPar"

int16 bds :: FindBalancedPar (uint16 curpos, logical bwd )
{
  char     *cpos  = bdsarea+curpos;
  short int len;
  short int position;
  char     *fpstr = "([{<®\'%";
  char     *bpstr = ")]}>¯\'%";

BEGINSEQ
  if ( !bwd && !memchr(fpstr,*cpos,7) )
  {
    if ( curpos && memchr(bpstr,*(cpos-1),7) )
      bwd = YES;
    else
    {
      if ( (len = bdslen-curpos) > 0 )
      {
        while ( --len && !memchr(fpstr,*(++cpos),7) ) ;
        if ( !len )                                  ERROR
      }
    }
  }

  if ( bwd && !memchr(bpstr,*(cpos-1),7) && (len = curpos) > 0 )
  {
    while ( --len && !memchr(bpstr,*(--cpos),7) ) ;
    if ( !len )                                      ERROR
    cpos++;
    len++;
  }

  if ( !(cpos = bwd ? gvtsfbpb(cpos,cpos-bdsarea) : 
                      gvtsfbp(cpos,bdslen-(cpos-bdsarea))) )
                                                     ERROR
  position = cpos - bdsarea;

RECOVER
  position = AUTO;
ENDSEQ
  return(position);

}

/******************************************************************************/
/**
\brief  GetArea - 


\return bdsarea -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetArea"

char *bds :: GetArea ( )
{


  return(bdsarea);
}

/******************************************************************************/
/**
\brief  GetFirstChar

\return pos -

\param  curpos -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFirstChar"

uint16 bds :: GetFirstChar (uint16 curpos )
{
  ushort   len;
  ushort   pos = 0;
  char    *cpos;


  if ( len = GetLineLength(curpos = GetLinePosition(curpos)) )
  {
    cpos = bdsarea+curpos;
    while ( len-- && *cpos == ' ' )
    {
      pos++;
      cpos++;
    }
  }
  return(pos);

}

/******************************************************************************/
/**
\brief  GetLineCount

\return linecnt

\param  curpos -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLineCount"

int16 bds :: GetLineCount (uint16 curpos )
{
  short     linecnt = UNDF;

  if ( !curpos )
    curpos = bdslen;

  while ( curpos-- )
    if ( bdsarea[curpos] == '\n' )
      linecnt++;
  return(linecnt);

}

/******************************************************************************/
/**
\brief  GetLineLength

\return len -

\param  curpos -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLineLength"

uint16 bds :: GetLineLength (uint16 curpos )
{
  char     *cpos  = bdsarea+curpos;
  short int start = curpos;

  if ( curpos < 0 || curpos >= bdslen )
    return(0);
    
  while ( curpos < bdslen && *cpos != '\r' )
    curpos++, cpos++;
  return(curpos-start);

}

/******************************************************************************/
/**
\brief  GetLinePosition

\return pos -

\param  curpos -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetLinePosition"

uint16 bds :: GetLinePosition (uint16 curpos )
{
  char     *cpos = bdsarea+curpos;

  if ( curpos <= 0 )
    return(0);
    
  while ( --curpos && *(--cpos) != '\n' ) ;

  return(*cpos == '\n' ? curpos+1 : 0);
}

/******************************************************************************/
/**
\brief  Insert - 


\return term - Success
-------------------------------------------------------------------------------
\brief BDSCIN


\param  pos -
\param  ichar -
\param  num -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

logical bds :: Insert (uint16 pos, char ichar, int16 num )
{
  logical   term = NO;

BEGINSEQ
  if ( !bdsarea || bdslen >= bdsmax || bdslen + num >= bdsmax )  ERROR
  *(bdsarea+bdslen) = 0;
  gvtscin(bdsarea+pos,ichar,num,bdsmax-pos);
  bdslen += num;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief BDSINS


\param  pos -
\param  text - Error text
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Insert"

logical bds :: Insert (uint16 pos, char *text )
{
  ushort    len  = strlen(text);
  logical   term = NO;

BEGINSEQ
  if ( !bdsarea || bdslen >= bdsmax || bdslen + len >= bdsmax )  ERROR
  *(bdsarea+bdslen) = 0;
  gvtssin(bdsarea+pos,text,bdsmax-pos);
  bdslen += len;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  bds

-------------------------------------------------------------------------------
\brief BDS_


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bds"

                        bds :: bds ( )
                     : bdsarea(NULL), bdslen(0), bdsmax(0)

{



}

/******************************************************************************/
/**
\brief BDS_F


\param  datarea -
\param  clen -
\param  mlen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bds"

                        bds :: bds (char *datarea, uint16 clen, uint16 mlen )
                     : bdsarea(datarea), bdslen(clen), bdsmax(mlen)

{



}

/******************************************************************************/
/**
\brief  bdsagt

\return bdsarea -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bdsagt"

char *bds :: bdsagt ( )
{

  return(bdsarea);

}

/******************************************************************************/
/**
\brief  bdsaloc

\return term - Success

\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bdsaloc"

logical bds :: bdsaloc (size_t len )
{
  logical   term = NO;

BEGINSEQ
  if ( !(bdsarea = new char[len]) )                SOSERR(95) 
  memset(bdsarea,0,len);
  bdslen = 0;
  bdsmax = len;

RECOVER
  term = YES;
ENDSEQ
  return(term);

}

/******************************************************************************/
/**
\brief  bdsast

\return bdsarea -

\param  datarea -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bdsast"

char *bds :: bdsast (char *datarea )
{

  return(bdsarea = datarea);

}

/******************************************************************************/
/**
\brief  bdsend

\return dataend

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bdsend"

char *bds :: bdsend ( )
{

  return(bdsarea+bdslen);

}

/******************************************************************************/
/**
\brief  bdsfree


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bdsfree"

void bds :: bdsfree ( )
{

  delete bdsarea;
  bdsarea = NULL;
  bdslen  = bdsmax = 0;


}

/******************************************************************************/
/**
\brief  bdslgt

\return bdslen

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bdslgt"

uint16 bds :: bdslgt ( )
{

  return(bdslen);

}

/******************************************************************************/
/**
\brief  bdslst

\return bdslen

\param  len -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bdslst"

uint16 bds :: bdslst (size_t len )
{

  return(bdslen=len);

}

/******************************************************************************/
/**
\brief  bdsmgt

\return bdsmax

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bdsmgt"

uint16 bds :: bdsmgt ( )
{

  return(bdsmax);

}

/******************************************************************************/
/**
\brief  bdsmst

\return bdsmax

\param  mlen -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "bdsmst"

uint16 bds :: bdsmst (uint16 mlen )
{

  return(bdsmax=mlen);

}

/******************************************************************************/
/**
\brief  operator+ - 


\return bdsptr -
-------------------------------------------------------------------------------
\brief BDSCONC


\param  bdsptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

bds &bds :: operator+ (bds &bdsptr )
{
  ushort    addlen = MIN(bdsmax-bdslen,bdsptr.bdslen);

  memcpy(bdsarea+bdslen,bdsptr.bdsarea,addlen);
  bdslen += addlen;


  return(*this);
}

/******************************************************************************/
/**
\brief BDSCONCS


\param  string - String value
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

bds &bds :: operator+ (char *string )
{
  ushort    addlen = MIN(bdsmax-bdslen,(ushort)strlen(string));

  memcpy(bdsarea+bdslen,string,addlen);
  bdslen += addlen;

  return(*this);

}

/******************************************************************************/
/**
\brief  operator+= - 


\return bdsptr -
-------------------------------------------------------------------------------
\brief BDSCONP


\param  bdsptr -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

bds bds :: operator+= (bds &bdsptr )
{

  return(*this+bdsptr);

}


