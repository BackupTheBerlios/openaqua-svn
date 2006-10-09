/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_ADK_Class_

\brief    


\date     $Date: 2006/03/12 19:36:42,78 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_Class__HPP
#define   pc_ADK_Class__HPP

class     pc_ADK_Class_;

#include  <cPIACC.h>
#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc_ADK_FieldControl__.hpp>
class  pc_ADK_Class_ :public PropertyHandle
{
protected  :         pc_ADK_FieldControl__                        controls;                                                  //

public     :
                     pc_ADK_FieldControl__                       &get_controls() { return(controls); }
public     :                                     logical InitResourceDB (char *clsnames, pc_ADK_Class_ &source_class );
public     :                                                             pc_ADK_Class_ (DBObjectHandle &obhandle, PIACC accopt );
};

#endif
