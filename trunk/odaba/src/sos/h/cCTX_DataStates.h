//******************************************************************/
//*  CTX_DataStates     
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/27*/ 
//******************************************************************/

#ifndef   CTX_DataStates_HPP 
#define   CTX_DataStates_HPP 

typedef enum 
{

  DAT_undefined                    = 0,
  DAT_Clear                        = 1,
  DAT_Filled                       = 2,
  DAT_Modified                     = 3,
  DAT_Invalid                      = 4,

} CTX_DataStates;
#endif
