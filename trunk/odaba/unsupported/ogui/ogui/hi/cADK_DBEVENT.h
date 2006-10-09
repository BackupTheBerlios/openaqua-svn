//******************************************************************/
//*  ADK_DBEVENT        
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    29.09.2003*/ 
//******************************************************************/

#ifndef   ADK_DBEVENT_HPP 
#define   ADK_DBEVENT_HPP 

typedef enum 
{

  DBEV_undefined                   = 0,
  DBEV_CollectionChanged           = 201,
  DBEV_CollectionUpdated           = 202,
  DBEV_InstanceInserted            = 203,
  DBEV_InstanceRemoved             = 204,
  DBEV_InstanceSelected            = 205,
  DBEV_InstanceUnselected          = 206,
  DBEV_InstanceUpdated             = 207,
  DBEV_HandleOpened                = 208,
  DBEV_HandleClosed                = 209,

} ADK_DBEVENT;
#endif
