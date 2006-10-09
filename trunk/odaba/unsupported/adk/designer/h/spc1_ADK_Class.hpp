/********************************* Class Declaration ***************************/
/**
\package  Designer - Context that communicates with the output area
\class    pc1_ADK_Class



\date     $Date: 2006/05/23 13:05:16,84 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc1_ADK_Class_HPP
#define   pc1_ADK_Class_HPP

class     pc1_ADK_Class;

#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc1_ADK_FieldControl.hpp>
class  pc1_ADK_Class :public PropertyHandle
{
protected  :         pc1_ADK_FieldControl                         controls;                                                  

public     :
                     pc1_ADK_FieldControl                        &get_controls() { return(controls); }
public     :                                        logical InitResourceDB (char *clsnames, pc1_ADK_Class &source_class );
public     :                                             pc1_ADK_Class (DBObjectHandle &obhandle, PIACC accopt );
};

#endif
