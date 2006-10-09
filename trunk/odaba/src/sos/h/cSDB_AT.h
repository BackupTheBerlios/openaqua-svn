//******************************************************************/
//*  SDB_AT             
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/28*/ 
//******************************************************************/

#ifndef   SDB_AT_HPP 
#define   SDB_AT_HPP 

typedef enum 
{

  AT_unknown                       = -1,
  AT_NONE                          = 0,
  AT_ODABA                         = 1,
  AT_CODE                          = 2,
  AT_BIN                           = 3,
  AT_EXTERN                        = 4,
  AT_ODBC                          = 5,
  AT_OEL                           = 6,
  AT_ESDF                          = 7,
  AT_VIEW                          = 8,
  AT_COMEIN                        = 9,
  AT_XML                           = 10,
  AT_SLIST                         = 11,

} SDB_AT;
#endif
