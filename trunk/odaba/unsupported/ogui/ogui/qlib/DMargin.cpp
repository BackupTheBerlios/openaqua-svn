/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DMargin

\brief    


\date     $Date: 2006/03/13 21:35:01,18 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "DMargin"

#include  <pogui7.h>
#include  <sDMargin.hpp>


/******************************************************************************/
/**
\brief  DMargin - 


\return term -
/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "DMargin"

                        DMargin :: DMargin ( )
                     :   Left(0),
  Top(0),
  Right(0),
  Bottom(0)
{



}

/******************************************************************************/
/**
\brief  IsEmpty - 


\return cond -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "IsEmpty"

logical DMargin :: IsEmpty ( )
{

  return ( this && !(Left | Right | Top | Bottom) );

}

/******************************************************************************/
/**
\brief  Maximum - 


\return max_margin -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Maximum"

int32 DMargin :: Maximum ( )
{

  return ( MAX(MAX(Left,Right),MAX(Top,Bottom)) );

}


