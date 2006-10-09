//******************************************************************/
//*  DB_Event           
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2004/08/13*/ 
//******************************************************************/

#ifndef   DB_Event_HPP 
#define   DB_Event_HPP 

typedef enum 
{

  DB_undefined                     = 0,
  DBP_Modify                       = 7,
  DBP_Insert                       = 8,
  DBP_Remove                       = 9,
  DBP_Delete                       = 10,
  DBP_Create                       = 13,
  DBP_Store                        = 15,
  DBO_NotCreated                   = 16,
  DBO_NotInserted                  = 17,
  DBO_NotOpened                    = 18,
  DBO_NotRemoved                   = 19,
  DBO_NotDeleted                   = 20,
  DBP_Read                         = 23,
  DBP_Select                       = 24,
  DBP_Open                         = 28,
  DBO_Stored                       = 257,
  DBO_Initialize                   = 513,
  DBO_Read                         = 514,
  DBO_Reset                        = 515,
  DBO_Created                      = 769,
  DBO_Deleted                      = 770,
  DBO_Inserted                     = 771,
  DBO_Removed                      = 772,
  DBO_Refresh                      = 1025,
  DBO_Close                        = 2049,
  DBO_Opened                       = 2050,

} DB_Event;
#endif
