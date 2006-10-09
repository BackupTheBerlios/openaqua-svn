//******************************************************************/
//*  CAU_Delay_Types    
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    28.09.2003*/ 
//******************************************************************/

#ifndef   CAU_Delay_Types_HPP 
#define   CAU_Delay_Types_HPP 

typedef enum 
{

  RDT_undefined                    = 0,
  RDT_immediately                  = 1,
  RDT_end_of_TA                    = 2,
  RDT_top_of_TA                    = 3,

} CAU_Delay_Types;
#endif
