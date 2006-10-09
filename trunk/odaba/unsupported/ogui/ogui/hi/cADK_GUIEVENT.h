//******************************************************************/
//*  ADK_GUIEVENT       
//*                                                                */
//*                    ODABA Codeset Enum Declaration              */ 
//*                                                                */
//*  PD21 Version 1.1                                    11.07.2005*/ 
//******************************************************************/

#ifndef   ADK_GUIEVENT_HPP 
#define   ADK_GUIEVENT_HPP 

typedef enum 
{

  GEV_undefined                    = 0,
  GEV_Open                         = 301,
  GEV_Close                        = 302,
  GEV_Enter                        = 303,
  GEV_Leave                        = 304,
  GEV_Select                       = 305,
  GEV_KeyInput                     = 306,
  GEV_Repaint                      = 307,
  GEV_HelpIndex                    = 308,
  GEV_Click                        = 309,
  GEV_Opened                       = 310,
  GEV_ContextMenu                  = 311,
  GEV_BeginDrag                    = 312,
  GEV_EndDrag                      = 313,
  GEV_EndDrop                      = 314,
  GEV_BeginDrop                    = 315,
  GEV_MouseMove                    = 316,
  GEV_Selected                     = 317,
  GEV_Show                         = 318,
  GEV_Hide                         = 319,
  GEV_MouseClick                   = 320,
  GEV_MouseDoubleClick             = 321,
  GEV_Dock                         = 322,
  GEV_Undock                       = 323,

} ADK_GUIEVENT;
#endif
