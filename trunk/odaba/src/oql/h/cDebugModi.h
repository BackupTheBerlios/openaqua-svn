//******************************************************************/
//*  DebugModi          
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    04.09.2005*/ 
//******************************************************************/

#ifndef   DebugModi_HPP 
#define   DebugModi_HPP 

typedef enum 
{

  DM_undefined                     = 0,
  DM_always                        = 1,
  DM_break_point                   = 2,
  DM_step_in                       = 3,
  DM_step_over                     = 4,
  DM_first_statement               = 5,
  DM_jump_over                     = 6,
  DM_step_out                      = 7,
  DM_terminate                     = 8,

} DebugModi;
#endif
