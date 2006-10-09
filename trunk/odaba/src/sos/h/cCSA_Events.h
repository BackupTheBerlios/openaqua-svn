//******************************************************************/
//*  CSA_Events         
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/27*/ 
//******************************************************************/

#ifndef   CSA_Events_HPP 
#define   CSA_Events_HPP 

typedef enum 
{

  CSA_undefined                    = 0,
  CE_Open                          = 1,
  CE_Opened                        = 2,
  CE_Command                       = 3,
  CE_Create                        = 4,
  CE_Update                        = 5,
  CE_Insert                        = 6,
  CE_Remove                        = 7,
  CE_Delete                        = 8,
  CE_Close                         = 9,
  CE_Closed                        = 10,
  SE_Open                          = 11,
  SE_Opened                        = 12,
  SE_Command                       = 13,
  SE_Create                        = 14,
  SE_Update                        = 15,
  SE_Insert                        = 16,
  SE_Remove                        = 17,
  SE_Delete                        = 18,
  SE_Close                         = 19,
  SE_Closed                        = 20,
  CE_Dirty                         = 21,

} CSA_Events;
#endif
