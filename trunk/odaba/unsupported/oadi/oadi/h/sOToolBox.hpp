/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OToolBox



\date     $Date: 2006/04/28 16:56:33,54 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OToolBox_HPP
#define   OToolBox_HPP

class     OToolBox;

class     PropertyHandle;
class     TControl;
#include  <sOEventAction.hpp>
#include  <sOFrameStyle.hpp>
class  OToolBox :public OEventAction
{
protected  :         OFrameStyle                                  frameStyle;                                                

public     :
                     OFrameStyle                                 &get_frameStyle() { return(frameStyle); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OToolBox ( );
public     :                                             OToolBox (OEventAction bcOEventAction, OFrameStyle frameStyle );
public     :                                        logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OToolBox ( );
};

#endif
