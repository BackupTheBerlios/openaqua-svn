//******************************************************************/
//*  ExternalResource   
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2005/02/21*/ 
//******************************************************************/

#ifndef   ExternalResource_HPP 
#define   ExternalResource_HPP 

typedef enum 
{

  ERC_undefined                    = 0,
  ERC_Source                       = 1,
  ERC_Include                      = 2,
  ERC_Document                     = 3,
  ERC_Executable                   = 4,
  ERC_Batch                        = 5,
  ERC_Temp                         = 6,
  ERC_Test                         = 7,

} ExternalResource;
#endif
