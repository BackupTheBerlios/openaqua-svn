/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_ADK_Resource_

\brief    


\date     $Date: 2006/03/12 19:36:43,59 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ADK_Resource__HPP
#define   pc_ADK_Resource__HPP

class     pc_ADK_Resource_;

class     pc_ADK_Resource_;
#include  <cPIACC.h>
#include  <sDBObjectHandle.hpp>
#include  <sPropertyHandle.hpp>
class  pc_ADK_Resource_ :public PropertyHandle
{
protected  :         PropertyHandle                               sys_resource;                                              //

public     :
                     PropertyHandle                              &get_sys_resource() { return(sys_resource); }
public     :                                     logical InitResourceDB (pc_ADK_Resource_ &source_resource );
public     :                                                             pc_ADK_Resource_ (DBObjectHandle &obhandle, char *clsnames, PIACC accopt );
};

#endif
