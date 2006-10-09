/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/14|13:42:34,87}|(REF)
\class    pc_ClassMemberInputHelp

\brief    


\date     $Date: 2006/03/17 12:28:04,64 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ClassMemberInputHelp_HPP
#define   pc_ClassMemberInputHelp_HPP

class     pc_ClassMemberInputHelp;

#include  <cODE_OBJECTTYPE.h>
#include  <sPropertyHandle.hpp>
#include  <spc_ClassFunctImpInputHelp.hpp>
class  pc_ClassMemberInputHelp :public PropertyHandle
{
protected  :         PropertyHandle                               ident;                                                     //
protected  :         PropertyHandle                               source;                                                    
protected  :         PropertyHandle                               type;                                                      //
protected  :         PropertyHandle                               filled;                                                    //
protected  :         pc_ClassFunctImpInputHelp                    funct_impls;                                               //

public     :
public     :                                     logical CreateVariables (char *codestring );
public     :                                     void DeinitHandles ( );
public     :                                     logical InitHandles (PropertyHandle *prophdl );
public     :                                     logical IsFilled ( );
public     :                                     pc_ClassFunctImpInputHelp *ProvideFunctionInputHelp (PropertyHandle *funct_ph, logical refresh_opt );
public     :                                     logical ResetLocals (PropertyHandle *memb_ph );
public     :                                     logical SetFilled ( );
public     :                                     logical SetupList (PropertyHandle *memb_ph, ODE_OBJECTTYPE ode_objtype, logical base_opt, logical direct_access );
public     :                                     logical SetupVariables (char *codestring, ODE_OBJECTTYPE ode_objtype );
public     :                                                             pc_ClassMemberInputHelp ( );
};

#endif
