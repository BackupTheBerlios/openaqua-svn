/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DSize

\brief    


\date     $Date: 2006/03/13 21:35:02,62 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DSize"

#include  <pogui7.h>
#include  <sDSize.hpp>


/******************************************************************************/
/**
\brief  IsValid - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsValid"

logical DSize :: IsValid ( ) const
{
  logical                 term = NO;
  term = !(
    (Width  < 0) ||
    (Height < 0)
  );

  return(term);
}

/******************************************************************************/
/**
\brief  operator+

\return dsize -

\param  rcDSize -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator+"

DSize DSize :: operator+ (const DSize &rcDSize )
{

  return ( DSize(Width + rcDSize.Width,
                 Height + rcDSize.Height) );

}


