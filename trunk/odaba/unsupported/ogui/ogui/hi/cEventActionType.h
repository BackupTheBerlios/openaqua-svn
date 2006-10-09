//******************************************************************/
//*  EventActionType    
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    07.09.2005*/ 
//******************************************************************/

#ifndef   EventActionType_HPP 
#define   EventActionType_HPP 

typedef enum 
{

  EAT_undefined                    = 0,
  EAT_toggle                       = 1,
  EAT_field                        = 2,
  EAT_group                        = 3,
  EAT_list                         = 4,
  EAT_command                      = 5,

} EventActionType;
#endif
