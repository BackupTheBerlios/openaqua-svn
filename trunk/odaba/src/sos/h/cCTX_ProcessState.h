//******************************************************************/
//*  CTX_ProcessState   
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/27*/ 
//******************************************************************/

#ifndef   CTX_ProcessState_HPP 
#define   CTX_ProcessState_HPP 

typedef enum 
{

  PRC_undefined                    = 0,
  PRC_Active                       = 4,
  PRC_Closed                       = 5,
  PRC_Opened                       = 6,
  PRC_Busy                         = 7,

} CTX_ProcessState;
#endif
