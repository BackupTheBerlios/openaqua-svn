//******************************************************************/
//*  ItemCandidateTypes 
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2005/06/01*/ 
//******************************************************************/

#ifndef   ItemCandidateTypes_HPP 
#define   ItemCandidateTypes_HPP 

typedef enum 
{

  ICT_undefined                    = 0,
  ICT_AboutToDelete                = 2,
  ICT_CommitFind                   = 4,
  ICT_DataScrolled                 = 8,
  ICT_Deleted                      = 16,
  ICT_EmptyItem                    = 32,
  ICT_ListRefresh                  = 64,
  ICT_NewData                      = 128,
  ICT_NewDataLast                  = 256,
  ICT_NewItem                      = 512,
  ICT_RestoreCurrentItem           = 1024,
  ICT_StoreCurrentItem             = 2048,

} ItemCandidateTypes;
#endif
