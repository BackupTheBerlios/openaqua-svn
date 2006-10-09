//******************************************************************/
//*  EventClasses       
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2004/07/16*/ 
//******************************************************************/

#ifndef   EventClasses_HPP 
#define   EventClasses_HPP 

typedef enum 
{

  EC_Context                       = 0,
  EC_Update                        = 1,
  EC_Position                      = 2,
  EC_Extension                     = 3,
  EC_Collection                    = 4,
  EC_Administrative                = 8,

} EventClasses;
#endif
