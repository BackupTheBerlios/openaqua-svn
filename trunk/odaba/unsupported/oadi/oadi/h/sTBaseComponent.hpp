/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TBaseComponent

\brief    Resource component
          Resources  defined  in  the  repository are converted into an internal
          format when being activated (red).

\date     $Date: 2006/04/28 15:32:08,62 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TBaseComponent_HPP
#define   TBaseComponent_HPP

class     TBaseComponent;

#ifndef   DLL_TBaseComponent_HPP
#define   DLL_TBaseComponent_HPP
#include  <sTBaseComponent.hpp>
#include  <sDLL.h>
#endif
class     PropertyHandle;
class     TBaseComponent;
#include  <cOComponentState.h>
#pragma pack(4)

class  TBaseComponent
{
protected  :         logical                                      deleteOnDestroy;                                           
protected  :         int32                                        componentState;                                            

public     :
                     int32                                        get_componentState() { return(componentState); }
public     : virtual                                void Close ( );
public     :                                        int ComponentState ( ) const;
public     :                                        logical Create (logical fDeleteOnDestroy_YES=YES );
protected  : virtual                                logical DoCreate ( );
protected  : virtual                                logical DoCreated ( );
protected  : virtual                                void DoDestroy ( );
public     : virtual                                int GetID ( );
public     :                                        logical IsDeleting ( );
public     : virtual                                logical Read (PropertyHandle *ph );
public     :                                             TBaseComponent ( );
public     :                                             TBaseComponent (DLL(TBaseComponent) children_list, logical delete_on_destroy, int component_state, TBaseComponent *component_owner );
public     : virtual                                     ~TBaseComponent ( );
};

#pragma pack()
#endif
