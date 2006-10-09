//******************************************************************/
//* OPSynBreak - 
//*
//*               ODABA II - Class Declaration
//*                          from  L:/OQL7/OQL7.dev
//*
//*  ODE Version 2.1                                   13.03.2006
//******************************************************************/
#ifndef   OPSynBreak_HPP 
#define   OPSynBreak_HPP 





#include  <cExecReturnCodes.h>
#include  <sOPBase.hpp>



 class   OPSynBreak   : 
                                  public  OPBase                                            

{




public     : 



  public    :                           ExecReturnCodes Execute ( );
  public    :                                                   OPSynBreak (OPBase *parent_node );
  public    :                                                   ~OPSynBreak ( );




};



#endif

