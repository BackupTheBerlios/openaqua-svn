/********************************* Class Declaration ***************************/
/**
\package  SOS
\class    ObjectInfo



\date     $Date: 2006/04/28 19:37:30,87 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ObjectInfo_HPP
#define   ObjectInfo_HPP

class     ObjectInfo;
#include "csosdll.h"

#include  <svcls.hpp>
class  ObjectInfo :public vcls
{

public     :
public     : virtual          SOSImpExp             void *CastPointer (char *typenames );
public     : virtual          SOSImpExp             char *GetObjectType ( );
public     :                  SOSImpExp                  ObjectInfo ( );
public     : static           SOSImpExp             void *__cdecl StaticCast (ObjectInfo *oinfo, char *typenames );
public     : virtual          SOSImpExp                  ~ObjectInfo ( );
};

#endif
