//******************************************************************/
//*  ADK_BrushStyle     
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    10.08.2004*/ 
//******************************************************************/

#ifndef   ADK_BrushStyle_HPP 
#define   ADK_BrushStyle_HPP 

typedef enum 
{

  BS_Undefined                     = 0,
  BS_SolidPattern                  = 1,
  BS_Dense1Pattern                 = 2,
  BS_Dense2Pattern                 = 3,
  BS_Dense3Pattern                 = 4,
  BS_Dense4Pattern                 = 5,
  BS_Dense5Pattern                 = 6,
  BS_Dense6Pattern                 = 7,
  BS_Dense7Pattern                 = 8,
  BS_HorPattern                    = 9,
  BS_VerPattern                    = 10,
  BS_CrossPattern                  = 11,
  BS_BDiagPattern                  = 12,
  BS_FDiagPattern                  = 13,
  BS_DiagCrossPattern              = 14,
  BS_CustomPattern                 = 24,

} ADK_BrushStyle;
#endif
