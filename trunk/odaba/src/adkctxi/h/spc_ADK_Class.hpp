/********************************* Class Declaration ***************************/
/**
\package  AdkCtxi - 
\class    pc_ADK_Class

\brief    


\date     $Date: 2006/06/18 11:13:04,96 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_Class_HPP
#define   pc_ADK_Class_HPP

class     pc_ADK_Class;

#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc0_SDB_Structure.hpp>
class  pc_ADK_Class :public pc0_SDB_Structure
{

public     :
public     :                                        PropertyHandle *ProvideDefaultCollectionControl (PropertyHandle *prophdl, logical &rhgrow, logical &rvgrow );
public     :                                        PropertyHandle *ProvideDefaultControl (PropertyHandle *prophdl, logical &rhgrow, logical &rvgrow );
public     :                                        PropertyHandle *ProvideDefaultImbeddedControl (PropertyHandle *prophdl, char *typenames );
public     :                                        PropertyHandle *ProvideDefaultTabControl ( );
public     :                                             pc_ADK_Class (PropertyHandle *prophdl );
public     :                                             pc_ADK_Class (PropertyHandle &prophdl_ref );
public     :                                             pc_ADK_Class (DBObjectHandle &obhandle, PIACC accopt );
};

#endif
