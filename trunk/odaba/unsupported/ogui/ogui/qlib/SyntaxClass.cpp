/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    SyntaxClass

\brief    


\date     $Date: 2006/03/13 21:36:26,57 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SyntaxClass"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sSyntaxClass.hpp>


/******************************************************************************/
/**
\brief  SyntaxClass - Constructor
        creates a named syntaxclass with QFont and QColor

\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  szName -
\param  rQFont -
\param  rQColor -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyntaxClass"

                        SyntaxClass :: SyntaxClass (std_string szName, QFont &rQFont, QColor &rQColor )
                     :   name(szName),
  font(rQFont),
  color(rQColor)
{



}

/******************************************************************************/
/**
\brief  i01


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyntaxClass"

                        SyntaxClass :: SyntaxClass ( )
                     :   name(NULL),
  font(QFont(SZ2QS("Courier"),10)),
  color(QColor(0,0,0))
{



}


