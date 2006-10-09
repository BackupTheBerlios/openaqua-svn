/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    NumFraction

\brief    


\date     $Date: 2006/03/12 19:21:48,07 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "NumFraction"

#include  <pdefault.h>
#include  <limits.h>
#include  <sNumFraction.hpp>


/******************************************************************************/
/**
\brief  GetDenominator

\return denominator -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDenominator"

int8 NumFraction :: GetDenominator ( ) const
{
  char                    denominator;
// das ist mist!
  return(denominator);
}

/******************************************************************************/
/**
\brief  GetGGT

\return intval -

\param  val1 -
\param  val2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGGT"

int32 __cdecl NumFraction :: GetGGT (int32 val1, int32 val2 )
{
  int32       intval = 1;
BEGINSEQ
  val1 = abs( val1 );
  val2 = abs( val2 );

  if ( (val1 == 1) || (val2 == 1) || (val1 == 0) || (val2 == 0) )
                                                     LEAVESEQ

  while ( val1 != val2 )
  {
    if ( val1 > val2 )
    {
      val1 %= val2;
      if ( val1 == 0 )
      {
        intval = val2;
        LEAVESEQ
      }
    }
    else
    {
      val2 %= val1;
      if ( val2 == 0 )
      {
        intval = val1;
        LEAVESEQ
      }
    }
  }

ENDSEQ
  return(intval);
}

/******************************************************************************/
/**
\brief  GetGGT64

\return intval -

\param  i64_val1 -
\param  i64_val2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetGGT64"

int64 NumFraction :: GetGGT64 (int64 i64_val1, int64 i64_val2 )
{
  int64      intval = 1;
BEGINSEQ
  i64_val1 = abs64( i64_val1 );
  i64_val2 = abs64( i64_val2 );

  if ( (i64_val1 == 1) || (i64_val2 == 1) || (i64_val1 == 0) || (i64_val2 == 0) )
                                                     LEAVESEQ

  while ( i64_val1 != i64_val2 )
  {
    if ( i64_val1 > i64_val2 )
    {
      i64_val1 %= i64_val2;
      if ( i64_val1 == 0 )
      {
        intval = i64_val2;
        LEAVESEQ
      }
    }
    else
    {
      i64_val2 %= i64_val1;
      if ( i64_val2 == 0 )
      {
        intval = i64_val1;
        LEAVESEQ
      }
    }
  }

ENDSEQ
  return(intval);
}

/******************************************************************************/
/**
\brief  GetNumerator

\return numerator -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetNumerator"

int32 NumFraction :: GetNumerator ( )
{
  int32                   numerator = 0;
// das ist mist!
  return(numerator);
}

/******************************************************************************/
/**
\brief  IsValid

\return cond - Return value

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical NumFraction :: IsValid ( ) const
{

  return ( den > 0 );

}

/******************************************************************************/
/**
\brief  Normalize


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Normalize"

void NumFraction :: Normalize ( )
{
  int32   n1;
  if ( den < 0 )
  {
    den = -den;
    num = -num;
  }

  n1 = GetGGT(num,den);
  num /= n1;
  den /= n1;


}

/******************************************************************************/
/**
\brief  NumFraction

-------------------------------------------------------------------------------
\brief i0


\param  numerator -
\param  denominator -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NumFraction"

                        NumFraction :: NumFraction (int32 numerator, int32 denominator )
                     : den(denominator),
  num(numerator)
{

  Normalize();

}

/******************************************************************************/
/**
\brief i1


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NumFraction"

                        NumFraction :: NumFraction ( )
                     : den(1),
  num(0)
{



}

/******************************************************************************/
/**
\brief i2


\param  dblval -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NumFraction"

                        NumFraction :: NumFraction (double dblval )
                     : den(1),
  num(0)
{
  int32 nDen = 1;
  int32 nMAX = LONG_MAX / 10;
BEGINSEQ
  if ( dblval > LONG_MAX || dblval < LONG_MIN )
  {
    num = 0;
    den = -1;                                        
    LEAVESEQ
  }

  while ( abs((int32)dblval) < nMAX && ( nDen < nMAX ) ) 
  {
    dblval *= 10;
    nDen   *= 10;
  }
  num = (int32)dblval;
  den = nDen;

  Normalize();
ENDSEQ

}

/******************************************************************************/
/**
\brief i3


\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NumFraction"

                        NumFraction :: NumFraction (const NumFraction &fraction_ref )
                     : den(fraction_ref.den),
  num(fraction_ref.num)
{



}

/******************************************************************************/
/**
\brief i4


\param  i64_val1 -
\param  i64_val2 -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "NumFraction"

                        NumFraction :: NumFraction (int64 i64_val1, int64 i64_val2 )
                     : den(1),
  num(0)
{
  int64              ggt;
  ggt = GetGGT64(i64_val1,i64_val2);
  i64_val1 /= ggt;
  i64_val2 /= ggt;

  if ( i64_val1 > ULONGMAX || i64_val2 > ULONGMAX )
  {
    num = 0;
    den = -1;
  }
  else
  {
    num = (int32)i64_val1;
    den = (int32)i64_val2;
  }



}

/******************************************************************************/
/**
\brief  operator double

\return none

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator double"

BLANKVAL NumFraction :: operator double ( ) const
{

  return ( den > 0 ? (double)num / (double)den
                   : (double)0               );


}

/******************************************************************************/
/**
\brief  operator long

\return none

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator long"

BLANKVAL NumFraction :: operator long ( ) const
{

  return ( den > 0 ? num/den : 0 );

}

/******************************************************************************/
/**
\brief  operator!=

\return cond - Return value

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator!="

logical NumFraction :: operator!= (const NumFraction &fraction_ref ) const
{
  logical                 cond = YES;
BEGINSEQ
  if ( !fraction_ref.IsValid() || !IsValid() )       ERROR

  cond = num != fraction_ref.num ||
         den != fraction_ref.den;
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  operator*

\return fraction -

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator*"

NumFraction NumFraction :: operator* (const NumFraction &fraction_ref )
{
  int64              w1;
  int64              w2;
BEGINSEQ
  if ( !fraction_ref.IsValid() || !IsValid() )       ERROR

  // (a/b) * (c/d) = (a*c) / (b*d)
  w1 = num * fraction_ref.num;
  w2 = den * fraction_ref.den;

RECOVER
  return ( NumFraction((int32)0,(int32)0) );

ENDSEQ
  return ( NumFraction(w1,w2) );
}

/******************************************************************************/
/**
\brief  operator*=

\return fraction_ref -

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator*="

NumFraction &NumFraction :: operator*= (const NumFraction &fraction_ref )
{

  return(*this = *this * fraction_ref);

}

/******************************************************************************/
/**
\brief  operator+

\return fraction -

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

NumFraction NumFraction :: operator+ (const NumFraction &fraction_ref )
{
  int64              w1;
  int64              w2;
BEGINSEQ
  if ( !fraction_ref.IsValid() || !IsValid() )       ERROR

  // (a/b) + (c/d) = ( (a*d) + (c*b) ) / (b*d)
  w1 = (num * fraction_ref.den) + (den * fraction_ref.num);
  w2 = den * fraction_ref.den;
RECOVER
  return ( NumFraction((int32)0,(int32)0) );
ENDSEQ
  return ( NumFraction(w1,w2) );
}

/******************************************************************************/
/**
\brief  operator+= - 


\return fraction_ref -

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+="

NumFraction &NumFraction :: operator+= (const NumFraction &fraction_ref )
{

  return(*this = *this + fraction_ref);

}

/******************************************************************************/
/**
\brief  operator-

\return fraction -

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-"

NumFraction NumFraction :: operator- (const NumFraction &fraction_ref )
{
  int64              w1;
  int64              w2;
BEGINSEQ
  if ( !fraction_ref.IsValid() || !IsValid() )       ERROR

  // (a/b) + (c/d) = ( (a*d) - (c*b) ) / (b*d)
  w1 = (num * fraction_ref.den) - (den * fraction_ref.num);
  w2 = den * fraction_ref.den;

RECOVER
  return ( NumFraction((int32)0,(int32)0) );
ENDSEQ
  return ( NumFraction(w1,w2) );
}

/******************************************************************************/
/**
\brief  operator-=

\return fraction_ref -

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator-="

NumFraction &NumFraction :: operator-= (const NumFraction &fraction_ref )
{

  return(*this = *this - fraction_ref);

}

/******************************************************************************/
/**
\brief  operator/

\return fraction -

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator/"

NumFraction NumFraction :: operator/ (const NumFraction &fraction_ref )
{
  int64              w1;
  int64              w2;
BEGINSEQ
  if ( !fraction_ref.IsValid() || !IsValid() )       ERROR

  // (a/b) / (c/d) = (a*d) / (b*c)
  w1 = num * fraction_ref.den;
  w2 = den * fraction_ref.num;
RECOVER
  return ( NumFraction((int32)0,(int32)0) );

ENDSEQ
  return ( NumFraction(w1,w2) );
}

/******************************************************************************/
/**
\brief  operator/=

\return fraction_ref -

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator/="

NumFraction &NumFraction :: operator/= (const NumFraction &fraction_ref )
{

  return(*this = *this / fraction_ref);

}

/******************************************************************************/
/**
\brief  operator<

\return cond - Return value

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<"

logical NumFraction :: operator< (const NumFraction &fraction_ref ) const
{
  int64              w1;
  int64              w2;
  logical              cond;
BEGINSEQ
  if ( !fraction_ref.IsValid() || !IsValid() )       ERROR

  // (a/b) < (c/d) =: (a*d) < (c*b)
  w1 = num * fraction_ref.den;
  w2 = den * fraction_ref.num;

  cond = w1 < w2;
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  operator<=

\return cond - Return value

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator<="

logical NumFraction :: operator<= (const NumFraction &fraction_ref ) const
{

  return( !(*this > fraction_ref) );

}

/******************************************************************************/
/**
\brief  operator= - 


\return fraction_ref -

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator="

NumFraction &NumFraction :: operator= (const NumFraction &fraction_ref )
{

    num = fraction_ref.num;
    den = fraction_ref.den;

  return(*this);
}

/******************************************************************************/
/**
\brief  operator== - 


\return cond - Return value

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical NumFraction :: operator== (const NumFraction &fraction_ref ) const
{
  logical                 cond = YES;
BEGINSEQ
  if ( !fraction_ref.IsValid() || !IsValid() )       ERROR

  cond = num == fraction_ref.num &&
         den == fraction_ref.den;
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  operator>

\return cond - Return value

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>"

logical NumFraction :: operator> (const NumFraction &fraction_ref ) const
{
  int64              w1;
  int64              w2;
  logical              cond;
BEGINSEQ
  if ( !fraction_ref.IsValid() || !IsValid() )       ERROR

  // (a/b) > (c/d) =: (a*d) > (c*b)
  w1 = num * fraction_ref.den;
  w2 = den * fraction_ref.num;

  cond = w1 > w2;
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  operator>=

\return cond - Return value

\param  fraction_ref -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator>="

logical NumFraction :: operator>= (const NumFraction &fraction_ref ) const
{

  return( !(*this < fraction_ref) );

}

/******************************************************************************/
/**
\brief  ~NumFraction


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~NumFraction"

                        NumFraction :: ~NumFraction ( )
{



}


