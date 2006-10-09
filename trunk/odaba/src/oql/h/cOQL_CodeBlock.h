//******************************************************************/
//*  OQL_CodeBlock      
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    30.01.2005*/ 
//******************************************************************/

#ifndef   OQL_CodeBlock_HPP 
#define   OQL_CodeBlock_HPP 

typedef enum 
{

  CB_undefined                     = 0,
  CB_IniBlock                      = 1,
  CB_ProcessBlock                  = 2,
  CB_ErrorBlock                    = 3,
  CB_FinalBlock                    = 4,
  CB_LeaveExpression               = 99,
  CB_StartExpression               = 100,
  CB_CaseBlock                     = 101,
  CB_DefaultBlock                  = 102,

} OQL_CodeBlock;
#endif
