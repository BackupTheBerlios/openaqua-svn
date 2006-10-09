//******************************************************************/
//*  DataFormSpec       
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/29*/ 
//******************************************************************/

#ifndef   DataFormSpec_HPP 
#define   DataFormSpec_HPP 

typedef enum 
{

  DFS_Default                      = 0,
  DFS_HHMM                         = 6,
  DFS_HHMMSS                       = 7,
  DFS_HHMMSSHH                     = 8,
  DFS_TTMMJJ                       = 9,
  DFS_TTMMJJJJ                     = 10,
  DFS_YYMMDD                       = 11,
  DFS_YYYYMMDD                     = 12,
  DFS_English                      = 13,
  DFS_Deutsch                      = 14,
  DFS_YYMMDD_point                 = 15,
  DFS_YYMMDD_slash                 = 16,
  DFS_TTMMJJJJ_punkt               = 17,
  DFS_TTMMJJ_punkt                 = 18,

} DataFormSpec;
#endif
