//******************************************************************/
//*  CS_ParmTypes       
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/28*/ 
//******************************************************************/

#ifndef   CS_ParmTypes_HPP 
#define   CS_ParmTypes_HPP 

typedef enum 
{

  CPT_end                          = 0,
  CPT_buffer                       = 66,
  CPT_char                         = 67,
  CPT_double                       = 68,
  CPT_handle                       = 72,
  CPT_instance                     = 73,
  CPT_key                          = 75,
  CPT_long                         = 76,
  CPT_LOID                         = 108,
  CPT_GUID                         = 103,
  CPT_string                       = 83,
  CPT_timestamp                    = 84,
  CPT_void                         = 86,
  CPT_handle_list                  = 104,
  CPT_short                        = 115,

} CS_ParmTypes;
#endif
