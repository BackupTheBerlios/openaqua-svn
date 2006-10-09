/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OConstant



\date     $Date: 2006/04/27 19:43:27,70 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OConstant_HPP
#define   OConstant_HPP

class     OConstant;

class     OFrameStyle;
class     PropertyHandle;
class     TControl;
#include  <sOConstantControl.hpp>
class  OConstant :public OConstantControl
{
protected  :         OConstantControl                            *constControl;                                              
protected  :         OFrameStyle                                 *frameStyle;                                                

public     :
                     OConstantControl                            *get_constControl() { return(constControl); }
                     OFrameStyle                                 *get_frameStyle() { return(frameStyle); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                             OConstant ( );
public     :                                             OConstant (OConstantControl bcOConstantControl, OConstantControl *pOConstantControl, OFrameStyle *pOFrameStyle );
public     :                                        TControl *Open (TControl *tparent, logical active_f );
public     :                                        logical Read (PropertyHandle *ph );
public     :                                        void Reset ( );
public     :                                             ~OConstant ( );
};

#endif
