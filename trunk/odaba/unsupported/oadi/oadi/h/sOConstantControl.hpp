/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OConstantControl



\date     $Date: 2006/04/27 19:42:11,31 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OConstantControl_HPP
#define   OConstantControl_HPP

class     OConstantControl;

class     PropertyHandle;
#include  <sOStyleAction.hpp>
class  OConstantControl :public OStyleAction
{
protected  :         DSize                                        grid_size;                                                 
protected  :         int16                                        inner_distance;                                            

public     :
                     DSize                                       &get_grid_size() { return(grid_size); }
                     int16                                        get_inner_distance() { return(inner_distance); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                             OConstantControl ( );
public     :                                             OConstantControl (OStyleAction bcOStyleAction, DSize grid_size, int16 inner_distance );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OConstantControl ( );
};

#endif
