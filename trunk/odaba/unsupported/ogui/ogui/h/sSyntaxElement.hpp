/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    SyntaxElement

\brief    SyntaxElement
          StorageClass for SyntaxElements
          stores  a QRegExp for a startElement  and a endElement and a Paragraph
          and Index.

          used by OSyntaxHighlighter

\date     $Date: 2006/03/13 21:34:53,73 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SyntaxElement_HPP
#define   SyntaxElement_HPP

class     SyntaxElement;

class     SyntaxClass;
#include  <sSyntaxElement.hpp>
class  SyntaxElement
{
public     :         SyntaxClass                                 *syntaxclass;                                               //
public     :         QRegExp                                      rxStart;                                                   //
public     :         QRegExp                                      rxEnd;                                                     //
public     :         std_string                                   szStart;                                                   //
public     :         std_string                                   szEnd;                                                     //
public     :         logical                                      isBlock;                                                   //
public     :         int32                                        iParagraph;                                                //
public     :         int32                                        iIndex;                                                    //

public     :
public     :                                                             SyntaxElement ( );
public     :                                                             SyntaxElement (SyntaxClass *pSyntaxClass, std_string szStartElement, std_string szEndElement );
public     :                                                             SyntaxElement (std_string szName, int iParagraph, int iIndex );
public     :                                     logical operator== (SyntaxElement &rsyntaxelement );
};

#endif
