//******************************************************************/
//*  ADK_DataReferenceT 
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    14.07.2005*/ 
//******************************************************************/

#ifndef   ADK_DataReferenceType_HPP 
#define   ADK_DataReferenceType_HPP 

typedef enum 
{

  DRT_undefined                    = 0,
  DRT_Extent                       = 1,
  DRT_PropertyPath                 = 2,
  DRT_View                         = 3,
  DRT_Enumeration                  = 4,
  DRT_UserDefined                  = 5,
  DRT_ResExtent                    = 6,
  DRT_SystemVariable               = 7,

} ADK_DataReferenceType;
#endif
