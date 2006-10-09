/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OSButton



\date     $Date: 2006/04/28 16:52:21,39 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSButton_HPP
#define   OSButton_HPP

class     OSButton;

class     PropertyHandle;
#include  <cADK_ButtonType.h>
#include  <sOStyle.hpp>
class  OSButton :public OStyle
{
protected  :         ADK_ButtonType                               button_type;                                               
protected  :         logical                                      toggle;                                                    
protected  :         logical                                      tristate;                                                  

public     :
                     ADK_ButtonType                               get_button_type() { return(button_type); }
                     logical                                      get_toggle() { return(toggle); }
                     logical                                      get_tristate() { return(tristate); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                             OSButton ( );
public     :                                             OSButton (OStyle bcOStyle, int16 button_type, logical toggle, logical tristate );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                             ~OSButton ( );
};

#endif
