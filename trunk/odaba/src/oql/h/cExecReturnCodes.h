//******************************************************************/
//*  ExecReturnCodes    
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    29.01.2005*/ 
//******************************************************************/

#ifndef   ExecReturnCodes_HPP 
#define   ExecReturnCodes_HPP 

typedef enum 
{

  ERC_undefined                    = 0,
  ERC_success                      = 1,
  ERC_continue                     = 2,
  ERC_break                        = 3,
  ERC_leave                        = 4,
  ERC_error                        = 5,
  ERC_return                       = 6,
  ERC_terminate                    = 7,
  ERC_null                         = 8,

} ExecReturnCodes;
#endif
