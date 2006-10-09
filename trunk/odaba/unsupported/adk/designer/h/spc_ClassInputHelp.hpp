/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:35:58,07}|(REF)
\class    pc_ClassInputHelp

\brief    


\date     $Date: 2006/03/12 19:36:44,28 $
\dbsource adk.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ClassInputHelp_HPP
#define   pc_ClassInputHelp_HPP

class     pc_ClassInputHelp;

class     pc_ClassFunctImpInputHelp;
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#include  <spc_ClassMemberInputHelp.hpp>
class  pc_ClassInputHelp :public PropertyHandle
{
protected  :         PropertyHandle                               ident;                                                     
protected  :         PropertyHandle                               source;                                                    
protected  :         PropertyHandle                               filled;                                                    //
protected  :         pc_ClassMemberInputHelp                      member;                                                    //
protected  :         logical                                      coll_filled;                                               //

public     :
public     :                                     void DeinitHandles ( );
public     :                                     logical InitHandles (DatabaseHandle &dbhandle, char *prjnames );
public     :                                     logical IsFilled ( );
public     :                                     pc_ClassFunctImpInputHelp *ProvideFunctionInputHelp (PropertyHandle *funct_ph, logical refresh_opt );
public     :                                     pc_ClassMemberInputHelp *ProvideMemberInputHelp (PropertyHandle *impcls_ph, logical refresh_opt );
public     :                                     logical SetFilled ( );
public     :                                     logical SetupList (PropertyHandle *class_ph, logical base_opt );
public     :                                                             pc_ClassInputHelp ( );
public     :                                                             ~pc_ClassInputHelp ( );
};

#endif
