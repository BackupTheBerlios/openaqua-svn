/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    SyntaxBlock

\brief    


\date     $Date: 2006/03/13 21:34:53,56 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SyntaxBlock_HPP
#define   SyntaxBlock_HPP

class     SyntaxBlock;

#include  <sSyntaxElement.hpp>
class  SyntaxBlock
{
public     :         SyntaxElement                                syntaxelement;                                             //
public     :         int                                          begin;                                                     //
public     :         int                                          length;                                                    //

public     :
public     :                                     logical InBlock (int iPosition );
public     :                                                             SyntaxBlock (SyntaxElement syntaxelement, int iBegin, int iLength );
};

#endif
