//******************************************************************/
//*  ProgramLanguage    
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    03.10.2003*/ 
//******************************************************************/

#ifndef   ProgramLanguage_HPP 
#define   ProgramLanguage_HPP 

typedef enum 
{

  PL_undefined                     = 0,
  PL_CPP                           = 1,
  PL_ASM                           = 2,
  PL_C                             = 3,
  PL_COM_IDL                       = 4,
  PL_CORBA_IDL                     = 5,

} ProgramLanguage;
#endif
