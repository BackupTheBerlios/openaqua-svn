//******************************************************************/
//*  ADT_Types          
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2005/03/20*/ 
//******************************************************************/

#ifndef   ADT_Types_HPP 
#define   ADT_Types_HPP 

typedef enum 
{

  ADT_undefined                    = 0,
  ADT_PropertyPath                 = 1,
  ADT_Function                     = 2,
  ADT_Expression                   = 3,
  ADT_Constant                     = 4,
  ADT_Type                         = 7,
  ADT_View                         = 10,
  ADT_AccessPath                   = 11,
  ADT_SystemVariable               = 12,
  ADT_BaseCollection               = 13,
  ADT_Operation                    = 14,
  ADT_Error                        = 15,
  ADT_SetOperation                 = 16,
  ADT_InstOperation                = 17,
  ADT_MetaOperation                = 18,

} ADT_Types;
#endif
