//******************************************************************/
//*  StructModLevel     
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    28.09.2003*/ 
//******************************************************************/

#ifndef   StructModLevel_HPP 
#define   StructModLevel_HPP 

typedef enum 
{

  SML_undefined                    = 0,
  SML_logical                      = 1,
  SML_reference                    = 3,
  SML_imbedded                     = 5,
  SML_key                          = 7,

} StructModLevel;
#endif
