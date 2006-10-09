//******************************************************************/
//*  DragAndDropActions 
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2004/04/29*/ 
//******************************************************************/

#ifndef   DragAndDropActions_HPP 
#define   DragAndDropActions_HPP 

typedef enum 
{

  DNDA_undefined                   = 0,
  DNDA_CopyA                       = 2,
  DNDA_CopyB                       = 4,
  DNDA_Link                        = 8,
  DNDA_MoveA                       = 16,
  DNDA_MoveB                       = 32,

} DragAndDropActions;
#endif
