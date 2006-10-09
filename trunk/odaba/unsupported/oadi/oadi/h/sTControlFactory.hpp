/********************************* Class Declaration ***************************/
/**
\package  OADI - 
\class    TControlFactory

\brief    


\date     $Date: 2006/06/19 19:42:47,32 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TControlFactory_HPP
#define   TControlFactory_HPP

class     TControlFactory;

class     OAction;
class     OElementStyle;
class     OFieldControl;
class     OWindow;
class     TAction;
class     TControl;
class     TEditField;
class     TField;
class     TRadioGroup;
class     TWindow;
#include  <sOSSplitter.hpp>
#pragma pack(4)

class  TControlFactory
{

public     :
public     : static                                 TControl *__cdecl NewControl (char *typenames );
public     :                                             TControlFactory ( );
};

#pragma pack()
#endif
