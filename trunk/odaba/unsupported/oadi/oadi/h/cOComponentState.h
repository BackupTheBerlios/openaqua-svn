//******************************************************************/
//*  OComponentState    
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/30*/ 
//******************************************************************/

#ifndef   OComponentState_HPP 
#define   OComponentState_HPP 

typedef enum 
{

  csDesigning                      = 1,
  csDestroying                     = 2,
  csLoading                        = 4,
  csReading                        = 8,
  csWriting                        = 16,
  csDangling                       = 32,

} OComponentState;
#endif
