/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_ClassFunctImpInputHelp

\brief    


\date     $Date: 2006/03/12 19:36:43,82 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ClassFunctImpInputHelp_HPP
#define   pc_ClassFunctImpInputHelp_HPP

class     pc_ClassFunctImpInputHelp;

#include  <sPropertyHandle.hpp>
class  pc_ClassFunctImpInputHelp :public PropertyHandle
{
protected  :         PropertyHandle                               ident;                                                     
protected  :         PropertyHandle                               source;                                                    

public     :
                     PropertyHandle                              &get_ident() { return(ident); }
                     PropertyHandle                              &get_source() { return(source); }
public     :                                     void DeinitHandles ( );
public     :                                     logical InitHandles (PropertyHandle *prophdl );
public     :                                     logical IsFilled ( );
public     :                                     logical SetFilled ( );
public     :                                     logical SetupList (PropertyHandle *functimp_ph, logical base_opt );
public     :                                                             pc_ClassFunctImpInputHelp ( );
};

#endif
