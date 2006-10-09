//******************************************************************/
//*  ProcessVariableNam 
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2005/01/19*/ 
//******************************************************************/

#ifndef   ProcessVariableNames_HPP 
#define   ProcessVariableNames_HPP 

typedef enum 
{

  PVN_undefined                    = 0,
  PVN_OPASDBError                  = 1,
  PVN_GUISQLError                  = 2,
  PVN_GUIDCError                   = 3,
  PVN_GUIError                     = 4,
  PVN_OPAOQLError                  = 5,
  PVN_CISError                     = 6,
  PVN_OPACTXError                  = 7,
  PVN_ReservedError                = 8,
  PVN_SOSError                     = 9,
  PVN_GUIUserError                 = 10,
  PVN_ReservedError1               = 11,
  PVN_ReservedError2               = 12,
  PVN_ReservedError3               = 13,
  PVN_ReservedError4               = 14,
  PVN_ReservedError5               = 15,
  PVN_ReservedError6               = 16,
  PVN_ReservedError7               = 17,
  PVN_ReservedError8               = 18,
  PVN_ReservedError9               = 19,
  PVN_SOSSysVariables              = 20,
  PVN_SOSDataFormat                = 21,
  PVN_SOSTraceObject               = 22,
  PVN_SOSSystemIO                  = 23,
  PVN_SOSReserve1                  = 24,
  PVN_SOSReserve2                  = 25,
  PVN_OPAUtilityCB                 = 26,
  PVN_OPADLLHandle                 = 27,
  PVN_OPAInitArea                  = 28,
  PVN_OPAActiveHandle              = 29,
  PVN_GlobalVariables              = 30,
  PVN_CISGlobal                    = 31,
  PVN_GUIReserve1                  = 32,
  PVN_GUIReserve2                  = 33,
  PVN_GUIReserve3                  = 34,
  PVN_GUIDLLHandle                 = 35,
  PVN_ApplInformation              = 36,
  PVN_SOSLONG_JUMP                 = 37,

} ProcessVariableNames;
#endif
