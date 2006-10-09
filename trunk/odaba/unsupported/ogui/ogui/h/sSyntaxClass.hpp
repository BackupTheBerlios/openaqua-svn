/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    SyntaxClass

\brief    


\date     $Date: 2006/03/13 21:34:53,65 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SyntaxClass_HPP
#define   SyntaxClass_HPP

class     SyntaxClass;

class  SyntaxClass
{
public     :         std_string                                   name;                                                      //
public     :         QFont                                        font;                                                      //
public     :         QColor                                       color;                                                     //

public     :
public     :                                                             SyntaxClass (std_string szName, QFont &rQFont, QColor &rQColor );
public     :                                                             SyntaxClass ( );
};

#endif
