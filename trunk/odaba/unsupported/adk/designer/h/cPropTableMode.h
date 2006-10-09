//******************************************************************/
//*  PropTableMode      
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    29.06.2004*/ 
//******************************************************************/

#ifndef   PropTableMode_HPP 
#define   PropTableMode_HPP 

typedef enum 
{

  PTM_undefined                    = 0,
  PTM_Control                      = 1,
  PTM_Field                        = 2,
  PTM_Button                       = 3,
  PTM_Constant                     = 4,
  PTM_Menu                         = 5,

} PropTableMode;
#endif
