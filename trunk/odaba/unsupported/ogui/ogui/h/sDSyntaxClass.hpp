/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    DSyntaxClass

\brief    


\date     $Date: 2006/03/13 21:33:38,90 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DSyntaxClass_HPP
#define   DSyntaxClass_HPP

class     DSyntaxClass;

#ifndef   DLL_char_HPP
#define   DLL_char_HPP
#include  <sDLL.h>
#endif
class  DSyntaxClass
{
protected  :         char                                         class_name[41];                                            //
protected  :         DLL(char)                                    expressions;                                               //

public     :
                     char                                        *get_class_name() { return(class_name); }
                     DLL(char)                                    get_expressions() { return(expressions); }
public     :         OGUI7ImpExp                                         DSyntaxClass ( );
public     :         OGUI7ImpExp                 void Reset ( );
public     :         OGUI7ImpExp                                         ~DSyntaxClass ( );
};

#endif
