//******************************************************************/
//*  CTX_Types          
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2004/02/23*/ 
//******************************************************************/

#ifndef   CTX_Types_HPP 
#define   CTX_Types_HPP 

typedef enum 
{

  CTXT_none                        = -1,
  CTXT_undefined                   = 0,
  CTXT_Administration              = 65,
  CTXT_Control                     = 67,
  CTXT_Document                    = 68,
  CTXT_Project                     = 79,
  CTXT_Application                 = 80,
  CTXT_Structure                   = 83,
  CTXT_Object                      = 84,
  CTXT_Window                      = 87,
  CTXT_Database                    = 88,
  CTXT_Property                    = 89,

} CTX_Types;
#endif
