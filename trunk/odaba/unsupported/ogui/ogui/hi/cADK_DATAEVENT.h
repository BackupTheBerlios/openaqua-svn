//******************************************************************/
//*  ADK_DATAEVENT      
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    07.07.2005*/ 
//******************************************************************/

#ifndef   ADK_DATAEVENT_HPP 
#define   ADK_DATAEVENT_HPP 

typedef enum 
{

  DEV_undefined                    = 0,
  DEV_Clear                        = 101,
  DEV_Fill                         = 102,
  DEV_Delete                       = 103,
  DEV_Deleted                      = 104,
  DEV_Insert                       = 105,
  DEV_Inserted                     = 106,
  DEV_Store                        = 107,
  DEV_Save                         = 108,
  DEV_Validate                     = 109,
  DEV_Stored                       = 110,
  DEV_BeforeDataSet                = 111,
  DEV_AfterDataSet                 = 112,
  DEV_Opened                       = 113,
  DEV_Activated                    = 114,
  DEV_Filled                       = 115,
  DEV_Initialize                   = 116,
  DEV_Initialized                  = 117,
  DEV_Saved                        = 118,

} ADK_DATAEVENT;
#endif
