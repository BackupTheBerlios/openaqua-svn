/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DString

\brief    


\date     $Date: 2006/03/13 21:35:02,75 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DString"

#include  <pogui7.h>
#include  <sDStringPrivate.hpp>
#include  <sDString.hpp>


/******************************************************************************/
/**
\brief  DString - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  cszString -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DString"

                        DString :: DString (const char *cszString )
                     : p(NULL)
{

  *this = cszString;

}

/******************************************************************************/
/**
\brief  i01


\param  rcDString -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DString"

                        DString :: DString (const DString &rcDString )
                     : p(rcDString.p)
{

  if ( p ) 
    p->refCnt++;

}

/******************************************************************************/
/**
\brief  i02


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DString"

                        DString :: DString ( )
                     : p(NULL)
{



}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical DString :: IsEmpty ( ) const
{

  return ( !p || !p->length ? YES : NO );

}

/******************************************************************************/
/**
\brief  IsNull - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsNull"

logical DString :: IsNull ( ) const
{

  return !p;

}

/******************************************************************************/
/**
\brief  Length - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Length"

int DString :: Length ( ) const
{

  return p ? p->length : 0;

}

/******************************************************************************/
/**
\brief  operator const char* - 


\return empty -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator const char*"

NOTYPE DString :: operator const char* ( ) const
{

  return p ? p->data : NULL;

}

/******************************************************************************/
/**
\brief  operator!= - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  rcdsText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical DString :: operator!= (const DString &rcdsText ) const
{

  return !(*this == rcdsText );

}

/******************************************************************************/
/**
\brief  i01


\param  cszText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical DString :: operator!= (const char *cszText ) const
{

return !(*this == cszText );

}

/******************************************************************************/
/**
\brief  operator+ - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  rcdsText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

DString &DString :: operator+ (const DString &rcdsText )
{
  int   oldlen;
  int   delta;
  if ( !p ) 
    return *this = rcdsText;

  if ( !rcdsText.p ) 
    return *this;

// even safe if rcdsText == *this

  oldlen = p->length;
  delta  = rcdsText.p->length;
  
  resize(oldlen + delta,YES);
  memcpy(p->data + oldlen,rcdsText.p->data,delta);
  return *this;
}

/******************************************************************************/
/**
\brief  i01


\param  cszText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

DString &DString :: operator+ (const char *cszText )
{

if( !p ) return *this= cszText;
if( !cszText ) return *this;

int oldlen= p->length;
int delta= strlen( cszText );
resize( oldlen + delta, YES );
memcpy( p->data + oldlen, cszText, delta );

return *this;

}

/******************************************************************************/
/**
\brief  operator+= - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  rcdsText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

DString &DString :: operator+= (const DString &rcdsText )
{
  int   oldlen;
  int   delta;

  if ( !p ) 
    return *this = rcdsText;

  if ( !rcdsText.p ) 
    return *this;

// even safe if rcdsText == *this
  
  oldlen= p->length;
  delta= rcdsText.p->length;

  resize(oldlen + delta,YES);
  memcpy(p->data + oldlen,rcdsText.p->data,delta);
  return *this;
}

/******************************************************************************/
/**
\brief  i01


\param  cszText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

DString &DString :: operator+= (const char *cszText )
{

if( !p ) return *this= cszText;
if( !cszText ) return *this;

int oldlen= p->length;
int delta= strlen( cszText );
resize( oldlen + delta, YES );
memcpy( p->data + oldlen, cszText, delta );

return *this;

}

/******************************************************************************/
/**
\brief  operator= - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  cszString -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

DString &DString :: operator= (const char *cszString )
{
  int   l;
  if ( !cszString )
  {
    if ( p && --p->refCnt == 0 ) 
      free( p );
    p = 0;
  }
  else
  {
    l = strlen(cszString);
    resize(l,NO);
    if ( l ) 
      memcpy(p->data,cszString,l);
  }

  return *this;
}

/******************************************************************************/
/**
\brief  i01


\param  rcDString -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

DString &DString :: operator= (const DString &rcDString )
{

if( p && --p->refCnt == 0 ) free( p );
p= rcDString.p;
if( p ) p->refCnt++;
return *this;

}

/******************************************************************************/
/**
\brief  operator== - 


\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  rcdsText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical DString :: operator== (const DString &rcdsText ) const
{

  return 
    rcdsText.p == p ||
    ( p && rcdsText.p && p->length == rcdsText.p->length &&
      !memcmp( p, rcdsText.p, p->length ) );

}

/******************************************************************************/
/**
\brief  i01


\param  cszText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical DString :: operator== (const char *cszText ) const
{
  int     l = cszText ? strlen(cszText) : UNDEF;

  return ( ( !p && !cszText ) ||
           ( p && cszText && p->length == l && !memcmp(p->data,cszText,l) ) );

}

/******************************************************************************/
/**
\brief  operator[] - 


\return term -

\param  iIndex -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator[]"

const char DString :: operator[] (int iIndex ) const
{

  return p ? p->data[iIndex] : 0;

}

/******************************************************************************/
/**
\brief  resize - 



\param  newLength -
\param  fCopy -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "resize"

void DString :: resize (int newLength, logical fCopy )
{
  const char *old       = NULL;
  int         oldLength = 0;

  if ( p && p->refCnt > 1 )
  {
    p->refCnt--;
    old       = p->data;
    oldLength = p->length;
    p         = 0;
  }

  if ( !p ) 
  {
    p = (DStringPrivate*) malloc(sizeof(DStringPrivate) + newLength );
    p->refCnt = 1;
    p->length = newLength;
    p->data[newLength] = 0;
    if ( fCopy && old && oldLength && newLength ) 
      memcpy(p->data,old,MIN(oldLength,newLength));
  }
  else
  {
    p = (DStringPrivate*) realloc(p,sizeof(DStringPrivate) + newLength );
    p->length = newLength;
    p->data[newLength] = 0;
  }

}

/******************************************************************************/
/**
\brief  ~DString - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~DString"

                        DString :: ~DString ( )
{

  if ( p ) 
    if ( --p->refCnt == 0 )
      free(p);

}


