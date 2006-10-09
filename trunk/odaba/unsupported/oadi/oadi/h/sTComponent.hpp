/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TComponent



\date     $Date: 2006/05/01 11:08:36,65 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TComponent_HPP
#define   TComponent_HPP

class     TComponent;

#ifndef   DLL_TComponent_HPP
#define   DLL_TComponent_HPP
#include  <sTComponent.hpp>
#include  <sDLL.h>
#endif
class     TComponent;
#include  <sObjectInfo.hpp>
#include  <sTBaseComponent.hpp>
#pragma pack(4)

class  TComponent :public ObjectInfo
{
protected  :         TComponent                                  *owner;                                                     
protected  :         DLL(TComponent)                              children;                                                  
protected  :         logical                                      deleting;                                                  

public     :
                     TComponent                                  *get_owner() { return(owner); }
                     DLL(TComponent)                             &get_children() { return(children); }
                     logical                                      get_deleting() { return(deleting); }
public     : virtual                                void *CastPointer (char *typenames );
public     : virtual                                void Close ( );
public     :                                        logical Create (TComponent *pTComponent );
public     :                                        void Deleting ( );
protected  : virtual                                logical DoCreate ( );
protected  : virtual                                logical DoCreated ( );
public     :                                        void InsertComponent (TComponent *pTComponent );
public     :                                        logical IsDeleting ( );
public     :                                        TComponent *Owner ( ) const;
public     :                                        TComponent *OwnerOfType (char *typenames );
public     :                                        void RemoveComponent (TComponent *pTComponent );
public     :                                             TComponent ( );
public     : virtual                                     ~TComponent ( );
};

#pragma pack()
#endif
