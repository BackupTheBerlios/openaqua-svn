//******************************************************************/
//* OPSynLeave - 
//*
//*               ODABA II - Class Declaration
//*                          from  L:/OQL7/OQL7.dev
//*
//*  ODE Version 2.1                                   13.03.2006
//******************************************************************/
#ifndef   OPSynLeave_HPP 
#define   OPSynLeave_HPP 





#include  <cExecReturnCodes.h>
#include  <sOPBase.hpp>



 class   OPSynLeave   : 
                                  public  OPBase                                            

{




public     : 



  public    :                           ExecReturnCodes Execute ( );
  public    :                                                   OPSynLeave (OPBase *parent_node );
  public    :                                                   ~OPSynLeave ( );




};



#endif

