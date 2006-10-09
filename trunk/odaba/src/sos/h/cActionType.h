//******************************************************************/
//*  ActionType         
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/29*/ 
//******************************************************************/

#ifndef   ActionType_HPP 
#define   ActionType_HPP 

typedef enum 
{

  ACT_undefined                    = 0,
  ACT_ParmAction                   = 65,
  ACT_Constant                     = 67,
  ACT_Document                     = 68,
  ACT_Expression                   = 69,
  ACT_Function                     = 70,
  ACT_Jump                         = 74,
  ACT_Menu                         = 77,
  ACT_Program                      = 80,
  ACT_Sequence                     = 83,
  ACT_Window                       = 87,
  ACT_Extended                     = 88,

} ActionType;
#endif
