/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OSRadioGroup



\date     $Date: 2006/04/28 16:55:32,56 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSRadioGroup_HPP
#define   OSRadioGroup_HPP

class     OSRadioGroup;

class     PropertyHandle;
#include  <cADK_HoriPos.h>
#include  <sOStyle.hpp>
class  OSRadioGroup :public OStyle
{
protected  :         int16                                        checked_num;                                               
protected  :         int8                                         vertical;                                                  
protected  :         logical                                      vscrol;                                                    
protected  :         int8                                         horizontal;                                                
protected  :         logical                                      hscrol;                                                    
protected  :         ADK_HoriPos                                  label_position;                                            
protected  :         logical                                      group_label;                                               

public     :
                     int16                                        get_checked_num() { return(checked_num); }
                     int8                                         get_vertical() { return(vertical); }
                     logical                                      get_vscrol() { return(vscrol); }
                     int8                                         get_horizontal() { return(horizontal); }
                     logical                                      get_hscrol() { return(hscrol); }
                     ADK_HoriPos                                  get_label_position() { return(label_position); }
                     logical                                      get_group_label() { return(group_label); }
public     :                                        logical AutoResize ( );
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                        logical HasHscrol ( );
public     :                                        logical HasVscrol ( );
public     :                                             OSRadioGroup ( );
public     :                                             OSRadioGroup (OStyle bcOStyle, int16 ichecked_num, int8 ivertical, logical vscroll, int8 ihorizontal, logical hscroll, int16 ilabel_position, logical group_label );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                        void ResetBorder ( );
public     : virtual                                     ~OSRadioGroup ( );
};

#endif
