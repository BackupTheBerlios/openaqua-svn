//******************************************************************/
//*  OperationTypes     
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/28*/ 
//******************************************************************/

#ifndef   OperationTypes_HPP 
#define   OperationTypes_HPP 

typedef enum 
{

  OT_undefined                     = 0,
  OT_GROUP                         = 1,
  OT_WHERE                         = 2,
  OT_DEFINE                        = 3,
  OT_CREATE                        = 4,
  OT_FROM                          = 5,
  OT_JOIN                          = 6,
  OT_ORDER                         = 7,
  OT_MINUS                         = 8,
  OT_INTERSECT                     = 9,
  OT_UPDATE                        = 10,
  OT_VIEW                          = 11,
  OT_USER                          = 12,
  OT_UNION                         = 13,

} OperationTypes;
#endif
