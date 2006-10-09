//******************************************************************/
//*  CommandTypes       
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/27*/ 
//******************************************************************/

#ifndef   CommandTypes_HPP 
#define   CommandTypes_HPP 

typedef enum 
{

  CLT_undefined                    = 0,
  CLT_comment                      = 1,
  CLT_command                      = 2,
  CLT_begin                        = 3,
  CLT_end                          = 4,
  CLT_entrypoint                   = 5,
  CLT_function                     = 6,
  CLT_redirection                  = 7,
} CommandTypes;
#endif
