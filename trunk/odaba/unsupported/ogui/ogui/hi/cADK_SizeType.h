//******************************************************************/
//*  ADK_SizeType       
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    30.09.2003*/ 
//******************************************************************/

#ifndef   ADK_SizeType_HPP 
#define   ADK_SizeType_HPP 

typedef enum 
{

  SIZE_undefined                   = 0,
  SIZE_Fixed                       = 1,
  SIZE_Minimal                     = 2,
  SIZE_Grow                        = 3,
  SIZE_Span                        = 4,

} ADK_SizeType;
#endif
