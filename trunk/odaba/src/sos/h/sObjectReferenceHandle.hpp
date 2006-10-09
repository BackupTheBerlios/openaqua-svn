/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    ObjectReferenceHandle



\date     $Date: 2006/05/31 15:47:49,96 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ObjectReferenceHandle_HPP
#define   ObjectReferenceHandle_HPP

#include "csosdll.h"
class     ObjectReferenceHandle;

class     ObjectReference;
#include  <sObjectReferenceHandle.hpp>
class  ObjectReferenceHandle
{
protected  :         ObjectReference                             *object_handle;                                             

public     :
                     ObjectReference                             *get_object_handle() { return(object_handle); }
public     :                  SOSImpExp             logical Close ( );
public     :                  SOSImpExp                  ObjectReferenceHandle (ObjectReference *obj_ref );
public     :                  SOSImpExp                  ObjectReferenceHandle (ObjectReferenceHandle &obref_handle );
public     :                  SOSImpExp                  ObjectReferenceHandle ( );
public     :                  SOSImpExp             logical Open (ObjectReference *obj_ref );
public     :                  SOSImpExp             logical operator!= (ObjectReferenceHandle &obref_handle );
public     :                  SOSImpExp             ObjectReferenceHandle &operator= (ObjectReferenceHandle &obref_handle );
public     :                  SOSImpExp             logical operator== (ObjectReferenceHandle &obref_handle );
public     :                                        void set_object_handle (ObjectReference *obj_ref );
public     :                  SOSImpExp                  ~ObjectReferenceHandle ( );
};

#endif
