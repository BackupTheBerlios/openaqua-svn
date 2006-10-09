//******************************************************************/
//*  ADK_WinType        
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    30.09.2003*/ 
//******************************************************************/

#ifndef   ADK_WinType_HPP 
#define   ADK_WinType_HPP 

typedef enum 
{

  WT_undefined                     = 0,
  WT_Dialog                        = 1,
  WT_Hierarchy                     = 2,
  WT_Popup                         = 3,
  WT_Simple                        = 4,
  WT_Tool                          = 5,

} ADK_WinType;
#endif
