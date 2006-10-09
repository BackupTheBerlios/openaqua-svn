/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODocument

\brief    ODocument Holds Formating Information for Texts
          use  setText(yourSourceCode);  to  fill  the document with information
          and  XML();  to  get  a  formated  version of your text, based on your
          stylesheet  definition. you can also pass  formated XML to get a valid
          rendered (plain)text.
          document  will ensure the well form of your document based on your tag
          definitons.

\date     $Date: 2006/03/13 21:35:39,25 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODocument"

#include  <pogui7.h>
#include  <mODocument.h>
#include  <sOMultiLineEdit.hpp>
#include  <sODocument.hpp>


/******************************************************************************/
/**
\brief  ODocument - Constructor
        use it to pass text and a name


\param  pOMultiLineEdit -
\param  isHTML -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODocument"

                        ODocument :: ODocument (OMultiLineEdit *pOMultiLineEdit, logical isHTML )
                     :  QTextDocument (
 pOMultiLineEdit
 ?pOMultiLineEdit->WidgetQ()
 :NULL
 )
,isHTML(isHTML)
{

  connect( this
          ,SIGNAL(cursorPositionChanged(QTextCursor))
          ,this
          ,SLOT  (slotCursorPositionChanged(QTextCursor))
         );

}

/******************************************************************************/
/**
\brief  Text - Returns Text
        returns the plain version of the document.
        ascii  (no font/format) except  that what is  possible with newlines and
        blanks

\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Text"

QString ODocument :: Text ( )
{

  if(isHTML)
    return toHtml();
  else
    return toPlainText();

}

/******************************************************************************/
/**
\brief  hiLight - 


\return term -

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "hiLight"

logical ODocument :: hiLight ( )
{
  logical                 term = NO;
  // foreach (syntaxelements as e)

  return(term);
}

/******************************************************************************/
/**
\brief  setText - setText
        set plain text to your document.

        this is the most simple way to start a document

\return term -
-------------------------------------------------------------------------------
\brief  i0


\param  szText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setText"

logical ODocument :: setText (char *szText )
{
  logical                 term = NO;
BEGINSEQ
  if(!szText)                                        ERROR
  term = setText(SZ2QS(szText));
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01


\param  qsText -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setText"

logical ODocument :: setText (QString qsText )
{
  logical                    term = NO;
  if(isHTML)
    setHtml(qsText);
  else
    setPlainText(qsText);
  return term;
}

/******************************************************************************/
/**
\brief  slotCursorPositionChanged - 



\param  crQTextCursor -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "slotCursorPositionChanged"

void ODocument :: slotCursorPositionChanged (const QTextCursor &crQTextCursor )
{
int line;
int lc;
int cline;
  QTextBlock  b = crQTextCursor.block();
  QTextLayout *l = b.layout();
  lc = l->lineCount();
  line = 0;
  for(b = begin();b!=end();b = b.next()){
    lc = l->lineCount();
    l = b.layout();
    if(b==crQTextCursor.block())
      cline = line;
    line++;
  }


}


