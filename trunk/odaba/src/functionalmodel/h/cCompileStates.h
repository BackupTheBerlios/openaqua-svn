//******************************************************************/
//*  CompileStates      
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2005/01/19*/ 
//******************************************************************/

#ifndef   CompileStates_HPP 
#define   CompileStates_HPP 

typedef enum 
{

  CPS_undefined                    = 0,
  CPS_requested                    = 1,
  CPS_failed                       = 2,
  CPS_ready                        = 3,

} CompileStates;
#endif
