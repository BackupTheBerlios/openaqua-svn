/********************************* Class Declaration ***************************/
/**
\package  SOS - Accept a Connection
\class    ReferenceObject



\date     $Date: 2006/05/31 18:45:25,75 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ReferenceObject_HPP
#define   ReferenceObject_HPP

#include "csosdll.h"
class     ReferenceObject;

#include  <sRessourceLock.hpp>
#include  <svcls.hpp>
#pragma pack(8)

class  ReferenceObject :public vcls
{
protected  :         int32                                        use_count;                                                 
protected  :         RessourceLock                                res_lock;                                                  

public     :
                     int32                                        get_use_count() { return(use_count); }
                     RessourceLock                               &get_res_lock() { return(res_lock); }
public     :                  SOSImpExp             logical Exist ( );
public     :                  SOSImpExp             logical ILock (logical wait=YES );
public     :                  SOSImpExp             logical IUnlock ( );
public     :                  SOSImpExp             logical IsLocked ( );
public     :                  SOSImpExp                  ReferenceObject (logical activate_llist );
public     : virtual          SOSImpExp             logical Release ( );
public     : virtual          SOSImpExp             void Reserve ( );
public     :                  SOSImpExp             void ResetUseCount ( );
public     : virtual          SOSImpExp                  ~ReferenceObject ( );
};

#pragma pack()
#endif
