//******************************************************************/
//*  ADK_FontStyleStrat 
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    09.08.2004*/ 
//******************************************************************/

#ifndef   ADK_FontStyleStrategy_HPP 
#define   ADK_FontStyleStrategy_HPP 

typedef enum 
{

  FSS_undefined                    = 0,
  FSS_PreferBitmap                 = 1,
  FSS_PreferDevice                 = 2,
  FSS_PreferOutline                = 3,
  FSS_ForceOutline                 = 4,
  FSS_NoAntialias                  = 5,
  FSS_PreferAntialias              = 6,

} ADK_FontStyleStrategy;
#endif
