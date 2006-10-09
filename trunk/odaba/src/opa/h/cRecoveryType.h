//******************************************************************/
//*  RecoveryType       
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/28*/ 
//******************************************************************/

#ifndef   RecoveryType_HPP 
#define   RecoveryType_HPP 

typedef enum 
{

  RECOVERY_none                    = 0,
  RECOVERY_Transaction             = 1,
  RECOVERY_Full                    = 2,

} RecoveryType;
#endif
