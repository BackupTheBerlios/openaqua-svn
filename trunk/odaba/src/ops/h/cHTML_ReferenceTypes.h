//******************************************************************/
//*  HTML_ReferenceType 
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    28.09.2003*/ 
//******************************************************************/

#ifndef   HTML_ReferenceTypes_HPP 
#define   HTML_ReferenceTypes_HPP 

typedef enum 
{

  HRT_undefined                    = 0,
  HRT_Constant                     = 1,
  HRT_Reference                    = 2,
  HRT_Expression                   = 3,
  HRT_Template                     = 4,

} HTML_ReferenceTypes;
#endif
