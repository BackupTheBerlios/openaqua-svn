//******************************************************************/
//*  ODSPropertyType    
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2005/07/14*/ 
//******************************************************************/

#ifndef   ODSPropertyType_HPP 
#define   ODSPropertyType_HPP 

typedef enum 
{

  PT_none                          = -1,
  PT_undefined                     = 0,
  PT_Self                          = 1,
  PT_Extent                        = 2,
  PT_Enumeration                   = 3,
  PT_DictionaryExtent              = 4,
  PT_Property                      = 5,
  PT_Key                           = 6,
  PT_BaseCollection                = 7,
  PT_NewCursor                     = 8,
  PT_Intern                        = 9,
  PT_CopyProperty                  = 10,
  PT_SystemVariable                = 11,

} ODSPropertyType;
#endif
