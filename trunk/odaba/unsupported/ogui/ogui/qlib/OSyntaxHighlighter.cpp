/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSyntaxHighlighter

\brief    


\date     $Date: 2006/03/13 21:36:16,98 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSyntaxHighlighter"

#include  <pogui7.h>
#include  <cqt.h>
#include  <mOSyntaxHighlighter.h>
#include  <sODS.hpp>
#include  <sOMultiLineEdit.hpp>
#include  <sSyntaxClass.hpp>
#include  <sSyntaxElement.hpp>
#include  <sOSyntaxHighlighter.hpp>


/******************************************************************************/
/**
\brief  Add - Add a Keyword
        specify  a Classname (added by Class before) and a regular expression to
        highlight this expression with the classes font and color.

        read   QT::QRegExp   for   more   infomation   how   to  specify regular
        expressions.  OMultilineEdit::HiLightDefaultElements  also  provides  a 
        good example what you can do.

\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  szClassName -
\param  szKeyword -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical OSyntaxHighlighter :: Add (std_string szClassName, std_string szKeyword )
{
  logical                 term = NO;
  Add(szClassName,szKeyword,"");

  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  szClassName -
\param  szStartElement -
\param  szEndElement -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical OSyntaxHighlighter :: Add (std_string szClassName, std_string szStartElement, std_string szEndElement )
{
  logical                 term = NO;
BEGINSEQ
  SyntaxClass *pClass = NULL;
  std::vector<SyntaxClass*>::iterator it;
  for ( it = classes.begin(); it != classes.end(); ++it ){
    if((*it)->name == szClassName)
      pClass = (*it);
  }
  if(!pClass)                                        LEAVESEQ
  elements.push_back(SyntaxElement(pClass,szStartElement,szEndElement));
ENDSEQ
  return term;
}

/******************************************************************************/
/**
\brief  AddFormatRange - 


\return term -

\param  pSyntaxClass -
\param  iStart -
\param  iLength -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddFormatRange"

logical OSyntaxHighlighter :: AddFormatRange (SyntaxClass *pSyntaxClass, int iStart, int iLength )
{
  logical                                 term = NO;
  QTextCharFormat                         textformat;

BEGINSEQ
  if(!pSyntaxClass)                                  ERROR
  textformat.setFont(pSyntaxClass->font);
  textformat.setForeground(pSyntaxClass->color);
  setFormat(iStart, iLength, textformat);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Class - Class
        Create  a ClassName and highlight all  members of this class with rQFont
        and rQColor.
        Classnames are used with Add()

\return term -

\param  szClassName -
\param  rQFont -
\param  rQColor -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Class"

logical OSyntaxHighlighter :: Class (std_string szClassName, QFont &rQFont, QColor &rQColor )
{
  logical                 term = NO;
  classes.push_back(new SyntaxClass(szClassName,rQFont,rQColor));
  return(term);
}

/******************************************************************************/
/**
\brief  FindElement - 


\return cond -
-------------------------------------------------------------------------------
\brief  i0


\param  qsText -
\param  riStart -
\param  rx -
\param  pSyntaxClass -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindElement"

logical OSyntaxHighlighter :: FindElement (QString qsText, int32 &riStart, QRegExp &rx, SyntaxClass *pSyntaxClass )
{
  logical                 cond = NO;
  int                     iLength = 0
                         ,iStart = riStart;
BEGINSEQ
  // find with highlight
  if(!pSyntaxClass)                                  ERROR
  if(FindElement(qsText,riStart,rx)){
    AddFormatRange(pSyntaxClass,riStart,rx.cap(0).length());
    riStart+=rx.cap(0).length();
  }

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i01


\param  qsText -
\param  riStart -
\param  rx -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindElement"

logical OSyntaxHighlighter :: FindElement (QString qsText, int32 &riStart, QRegExp &rx )
{
  logical                 cond = NO;

BEGINSEQ
  if( riStart<0 )                                    ERROR
  riStart = rx.indexIn( qsText, riStart );
  if ( riStart > -1 )  // rx found
    cond = YES;
  

RECOVER
  cond = NO;
ENDSEQ
  return cond;
}

/******************************************************************************/
/**
\brief  FindElements - 


\return term -

\param  qsText -
\param  riStart -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindElements"

logical OSyntaxHighlighter :: FindElements (QString qsText, int32 &riStart )
{
  logical                 term = NO;
  int                     iEnd = 0
                         ,iStart = riStart
                         ,iLength = 0;
  std::vector<SyntaxElement>::iterator it;
BEGINSEQ
  if(qsText.isEmpty())                               ERROR
  
  for ( it = elements.begin(); it != elements.end() && !term; ++it ){
    iStart = riStart;
    while ( iStart >= 0 )
      if(FindElement(qsText,iStart,(*it).rxStart)){
        iLength = (*it).rxStart.cap(0).length();
        iEnd = iStart+iLength;
        if((*it).isBlock)
          if(FindElement(qsText,iEnd,(*it).rxEnd)){ //highlight the block to the end of line
            iLength = (iEnd + (*it).rxStart.cap(0).length()) - iStart;
          }else{ // remember that the block doesnt end here
            iLength = qsText.length() - iStart;
            setCurrentBlockState(GetSyntaxElementIndex((*it)));
          }
        AddFormatRange((*it).syntaxclass,iStart,iLength);
        iStart+=iLength;
      }
  }


RECOVER
  term = YES;
ENDSEQ
  return term;
}

/******************************************************************************/
/**
\brief  FindEndBlock - 



\param  qscText -
\param  riStart -
\param  rsyntaxelement -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FindEndBlock"

void OSyntaxHighlighter :: FindEndBlock (const QString &qscText, int32 &riStart, SyntaxElement &rsyntaxelement )
{
  int                        iLength = 0;

  if(FindElement(qscText,riStart,rsyntaxelement.rxEnd)){
    riStart += rsyntaxelement.rxEnd.cap(0).length();
    iLength = riStart;
  }
  else{
    iLength = qscText.length();
    setCurrentBlockState(previousBlockState());
  }
  AddFormatRange(rsyntaxelement.syntaxclass,0,iLength);



}

/******************************************************************************/
/**
\brief  GetSyntaxElementIndex - 


\return indx0 -

\param  syntaxelement -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetSyntaxElementIndex"

int32 OSyntaxHighlighter :: GetSyntaxElementIndex (SyntaxElement syntaxelement )
{
  std::vector<SyntaxElement>::iterator it;
  int                                  indx0 = 0;
BEGINSEQ
  for ( it = elements.begin(); it != elements.end(); ++it ){
    if(((SyntaxElement)(*it))==syntaxelement)
      LEAVESEQ
    indx0++;
  }
ENDSEQ
  return(indx0);
}

/******************************************************************************/
/**
\brief  OSyntaxHighlighter - Constructor


\return term -

\param  pOMultiLineEdit -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSyntaxHighlighter"

                        OSyntaxHighlighter :: OSyntaxHighlighter (OMultiLineEdit *pOMultiLineEdit )
                     :  QSyntaxHighlighter(pOMultiLineEdit->document())
,edit(pOMultiLineEdit)
,formatoverrides()
,currentBlockWidget(NULL)
{



}

/******************************************************************************/
/**
\brief  highlightBlock - 



\param  qscText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "highlightBlock"

void OSyntaxHighlighter :: highlightBlock (const QString &qscText )
{
  logical                    term = NO;
  int                        iStart = 0;
  setCurrentBlockState(0);
  if(previousBlockState() > 0) // in block
    FindEndBlock(qscText,iStart,elements[previousBlockState()]);
  
  if(iStart>=0)
    FindElements(qscText,iStart);


}


