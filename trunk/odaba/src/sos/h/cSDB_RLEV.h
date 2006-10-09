//******************************************************************/
//*  SDB_RLEV           
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/28*/ 
//******************************************************************/

#ifndef   SDB_RLEV_HPP 
#define   SDB_RLEV_HPP 

typedef enum 
{

  RL_undefined                     = -99,
  RL_generic                       = -2,
  RL_reference                     = -1,
  RL_direct                        = 0,
  RL_1                             = 1,
  RL_2                             = 2,
  RL_3                             = 3,

} SDB_RLEV;
#endif
