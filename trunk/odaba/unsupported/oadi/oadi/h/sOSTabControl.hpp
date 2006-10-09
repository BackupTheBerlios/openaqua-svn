/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OSTabControl



\date     $Date: 2006/04/28 16:56:34,95 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSTabControl_HPP
#define   OSTabControl_HPP

class     OSTabControl;

class     PropertyHandle;
#include  <cADK_Shape.h>
#include  <cADK_VertPos.h>
#include  <sOStyle.hpp>
class  OSTabControl :public OStyle
{
protected  :         ADK_VertPos                                  position;                                                  
protected  :         ADK_Shape                                    shape;                                                     
protected  :         ADK_VertPos                                  fix_child;                                                 

public     :
                     ADK_VertPos                                  get_position() { return(position); }
                     ADK_Shape                                    get_shape() { return(shape); }
                     ADK_VertPos                                  get_fix_child() { return(fix_child); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                             OSTabControl ( );
public     :                                             OSTabControl (OStyle bcOStyle, int16 iposition, int8 ishape, int8 ifix_child );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OSTabControl ( );
};

#endif
