/********************************* Class Declaration ***************************/
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

\date     $Date: 2006/03/13 21:34:06,35 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODocument_HPP
#define   ODocument_HPP

class     ODocument;

class     OMultiLineEdit;
class  ODocument :public QTextDocument
{
protected  :                                                      Q_OBJECT;                                                  //
protected  :         logical                                      isHTML;                                                    //

public     :
public     :         OGUI7ImpExp                                         ODocument (OMultiLineEdit *pOMultiLineEdit, logical isHTML );
public     :         OGUI7ImpExp                 QString Text ( );
public     :                                     logical hiLight ( );
public     :         OGUI7ImpExp                 logical setText (char *szText );
public     :         OGUI7ImpExp                 logical setText (QString qsText );
public     :                                     public slots: void slotCursorPositionChanged (const QTextCursor &crQTextCursor );
};

#endif
