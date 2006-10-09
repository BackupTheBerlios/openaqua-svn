//******************************************************************/
//* OPSynContinue - 
//*
//*               ODABA II - Class Declaration
//*                          from  L:/OQL7/OQL7.dev
//*
//*  ODE Version 2.1                                   13.03.2006
//******************************************************************/
#ifndef   OPSynContinue_HPP 
#define   OPSynContinue_HPP 





#include  <cExecReturnCodes.h>
#include  <sOPBase.hpp>



 class   OPSynContinue   : 
                                  public  OPBase                                            

{




public     : 



  public    :                           ExecReturnCodes Execute ( );
  public    :                                                   OPSynContinue (OPBase *parent_node );
  public    :                                                   ~OPSynContinue ( );




};



#endif

