/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    SyntaxHelp

\brief    Syntax Help


\date     $Date: 2006/03/13 21:34:53,90 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SyntaxHelp_HPP
#define   SyntaxHelp_HPP

class     SyntaxHelp;

#ifndef   VECTOR_std_string_HPP
#define   VECTOR_std_string_HPP
#include  <sVECTOR.h>
#endif
class     ODataWidget;
class  SyntaxHelp
{
protected  :         ODataWidget                                 *pODataWidget;                                              //
protected  :         VECTOR(std_string)                           vlActivators;                                              //

public     :
                     ODataWidget                                 *get_pODataWidget() { return(pODataWidget); }
                     VECTOR(std_string)                          &get_vlActivators() { return(vlActivators); }
public     :                                     ODataWidget *GetControl (QString qsComparator );
public     :                                     ODataWidget *GetDefaultControl ( );
public     :                                                             SyntaxHelp ( );
public     :                                                             SyntaxHelp (ODataWidget *pODW, VECTOR(std_string) &vlAct );
public     :                                                             ~SyntaxHelp ( );
};

#endif
