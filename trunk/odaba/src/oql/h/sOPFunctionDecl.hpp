/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:37,14}|(REF)
\class    OPFunctionDecl

\brief    


\date     $Date: 2006/03/12 19:20:06,37 $
\dbsource oql.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OPFunctionDecl_HPP
#define   OPFunctionDecl_HPP

class     OPFunctionDecl;

class     ACObject;
class     Dictionary;
class     OPParmList;
class     OperEnvironment;
class     ParmList;
class     node;
#include  <sFunctLink.hpp>
#include  <sOPDecl.hpp>
#include  <sPropertyHandle.hpp>
class  OPFunctionDecl :public OPDecl,
public FunctLink
{
protected  :         ParmList                                    *pi_parms;                                                  //
protected  :         logical                                      no_decl;                                                   //

public     :
                     ParmList                                    *get_pi_parms() { return(pi_parms); }
public     : virtual                             logical Call (PropertyHandle *co, OPParmList *call_parms, int8 set_operation=NO );
public     : virtual                             logical Call (PropertyHandle *co, ParmList *parm_list, int8 set_operation=NO );
public     :                                     logical Check (PropertyHandle *retval, PropertyHandle *co, ParmList *parm_list, logical convopt );
public     : virtual                             ExecReturnCodes Execute ( );
public     :                                     logical Init (PropertyHandle *co, ParmList *parm_list );
public     :                                     int32 InitParameters (OPParmList *call_parms );
public     :                                     int32 InitParameters (ParmList *parm_list );
public     :                                     logical InitResult ( );
public     :                                     logical IsValid ( );
public     :                                                             OPFunctionDecl (Dictionary *dictptr, char *strnames, ACObject *obhandle, PropertyHandle *co, char *fnames, logical check_opt=YES );
public     :                                                             OPFunctionDecl (Dictionary *dictptr, char *strnames, ACObject *obhandle, PropertyHandle *co, PropertyHandle *impl_ph, logical check_opt=YES );
public     :                                     ParmList *PIParmList ( );
public     :                                     void SetParmlist (ParmList *plist );
public     :                                                             ~OPFunctionDecl ( );
};

#endif
