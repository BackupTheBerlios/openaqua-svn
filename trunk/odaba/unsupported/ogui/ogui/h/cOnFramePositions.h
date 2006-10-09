//******************************************************************/
//*  OnFramePositions   
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    2003/09/30*/ 
//******************************************************************/

#ifndef   OnFramePositions_HPP 
#define   OnFramePositions_HPP 

typedef enum 
{

  OF_undefined                     = 0,
  OF_Top                           = 1,
  OF_Bottom                        = 2,
  OF_Left                          = 4,
  OF_TopLeft                       = 5,
  OF_BottomLeft                    = 6,
  OF_Right                         = 8,
  OF_TopRight                      = 9,
  OF_BottomRight                   = 10,

} OnFramePositions;
#endif
