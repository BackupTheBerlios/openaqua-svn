/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    ObjectReference



\date     $Date: 2006/05/31 15:29:47,92 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ObjectReference_HPP
#define   ObjectReference_HPP

#include "csosdll.h"
class     ObjectReference;

#ifndef   DLL_ObjectReferenceHandle_HPP
#define   DLL_ObjectReferenceHandle_HPP
#include  <sObjectReferenceHandle.hpp>
#include  <sDLL.h>
#endif
class     ObjectReferenceHandle;
#include  <sReferenceObject.hpp>
#pragma pack(8)

class  ObjectReference :public ReferenceObject
{
protected  :         DLL(ObjectReferenceHandle)                   references;                                                

public     :
                     DLL(ObjectReferenceHandle)                  &get_references() { return(references); }
public     :                  SOSImpExp             void Connect (ObjectReferenceHandle *obref_hdl_ptr );
public     :                  SOSImpExp             void Disconnect (ObjectReferenceHandle *obref_hdl_ptr );
public     :                  SOSImpExp                  ObjectReference (logical activate_llist );
public     :                  SOSImpExp             logical Release (ObjectReferenceHandle *obref_hdl_ptr );
public     :                  SOSImpExp             logical Reserve (ObjectReferenceHandle *obref_hdl_ptr );
public     : virtual          SOSImpExp                  ~ObjectReference ( );
};

#pragma pack()
#endif
