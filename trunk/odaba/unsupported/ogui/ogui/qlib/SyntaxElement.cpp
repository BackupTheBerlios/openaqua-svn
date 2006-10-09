/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    SyntaxElement

\brief    SyntaxElement
          StorageClass for SyntaxElements
          stores  a QRegExp for a startElement  and a endElement and a Paragraph
          and Index.

          used by OSyntaxHighlighter

\date     $Date: 2006/03/13 21:36:26,65 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "SyntaxElement"

#include  <pogui7.h>
#include  <cqt.h>
#include  <sSyntaxClass.hpp>
#include  <sSyntaxElement.hpp>


/******************************************************************************/
/**
\brief  SyntaxElement - Constructor
        Creates  a  SyntaxElement  with  Syntaxclass and regular expressions for
        start and end elements

\return term -
-------------------------------------------------------------------------------
\brief  i0


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyntaxElement"

                        SyntaxElement :: SyntaxElement ( )
                     : syntaxclass(NULL),
szStart(),
szEnd(),
isBlock(NO),
iIndex(0),
iParagraph(0)
{



}

/******************************************************************************/
/**
\brief  i01


\param  pSyntaxClass -
\param  szStartElement -
\param  szEndElement -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyntaxElement"

                        SyntaxElement :: SyntaxElement (SyntaxClass *pSyntaxClass, std_string szStartElement, std_string szEndElement )
                     : syntaxclass(pSyntaxClass),
szStart(szStartElement),
szEnd(szEndElement),
isBlock(!szEndElement.empty()?YES:NO),
rxStart(SZ2QS(szStartElement.c_str())),
rxEnd(SZ2QS(szEndElement.c_str())),
iIndex(0),
iParagraph(0)
{

  rxStart.setMinimal(YES);
  rxStart.setPatternSyntax( QRegExp::RegExp);
  rxEnd.setMinimal(YES);
  rxEnd.setPatternSyntax( QRegExp::RegExp);


}

/******************************************************************************/
/**
\brief  i02


\param  szName -
\param  iParagraph -
\param  iIndex -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SyntaxElement"

                        SyntaxElement :: SyntaxElement (std_string szName, int iParagraph, int iIndex )
                     : syntaxclass(NULL),
szStart(szName),
szEnd(NULL),
isBlock(NO),
iIndex(iIndex),
iParagraph(iParagraph)
{



}

/******************************************************************************/
/**
\brief  operator== - 


\return term -

\param  rsyntaxelement -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "operator=="

logical SyntaxElement :: operator== (SyntaxElement &rsyntaxelement )
{

  return    syntaxclass == rsyntaxelement.syntaxclass
         && szStart     == rsyntaxelement.szStart
         && szEnd       == rsyntaxelement.szEnd
         && isBlock     == rsyntaxelement.isBlock
        ;

}


