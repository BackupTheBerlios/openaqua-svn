//******************************************************************/
//*  ItemStates         
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2005/02/24*/ 
//******************************************************************/

#ifndef   ItemStates_HPP 
#define   ItemStates_HPP 

typedef enum 
{

  IST_undefined                    = 0,
  IST_defined                      = 1,
  IST_opened                       = 2,
  IST_valid                        = 3,
  IST_located                      = 4,
  IST_selected                     = 5,
  IST_positioned                   = 6,

} ItemStates;
#endif
