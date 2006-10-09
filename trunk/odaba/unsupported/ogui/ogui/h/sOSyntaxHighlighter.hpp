/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSyntaxHighlighter

\brief    


\date     $Date: 2006/03/13 21:34:42,82 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSyntaxHighlighter_HPP
#define   OSyntaxHighlighter_HPP

class     OSyntaxHighlighter;

#ifndef   VECTOR_SyntaxBlock_HPP
#define   VECTOR_SyntaxBlock_HPP
#include  <sSyntaxBlock.hpp>
#include  <sVECTOR.h>
#endif
class     ODS;
class     OMultiLineEdit;
#include  <sSyntaxClass.hpp>
#include  <sSyntaxElement.hpp>
class  OSyntaxHighlighter :public QSyntaxHighlighter
{
protected  :                                                      Q_OBJECT;                                                  //
protected  :         std::vector<SyntaxClass*>                    classes;                                                   //
protected  :         std::vector<SyntaxElement>                   elements;                                                  //
protected  :         logical                                      bHighLightParagraphBackground;                             //
protected  :         OMultiLineEdit                              *edit;                                                      //
protected  :         QList<QTextLayout::FormatRange>              formatoverrides;                                           //
protected  :         QWidget                                     *currentBlockWidget;                                        //

public     :
                     logical                                      get_bHighLightParagraphBackground() { return(bHighLightParagraphBackground); }
public     :         OGUI7ImpExp                 logical Add (std_string szClassName, std_string szKeyword );
public     :         OGUI7ImpExp                 logical Add (std_string szClassName, std_string szStartElement, std_string szEndElement );
public     :                                     logical AddFormatRange (SyntaxClass *pSyntaxClass, int iStart, int iLength );
public     :         OGUI7ImpExp                 logical Class (std_string szClassName, QFont &rQFont, QColor &rQColor );
public     :                                     logical FindElement (QString qsText, int32 &riStart, QRegExp &rx, SyntaxClass *pSyntaxClass );
public     :                                     logical FindElement (QString qsText, int32 &riStart, QRegExp &rx );
public     :                                     logical FindElements (QString qsText, int32 &riStart );
public     :                                     void FindEndBlock (const QString &qscText, int32 &riStart, SyntaxElement &rsyntaxelement );
public     :                                     int32 GetSyntaxElementIndex (SyntaxElement syntaxelement );
public     :         OGUI7ImpExp                                         OSyntaxHighlighter (OMultiLineEdit *pOMultiLineEdit );
protected  : virtual                             void highlightBlock (const QString &qscText );
};

#endif
