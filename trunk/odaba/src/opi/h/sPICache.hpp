/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:09:46,17}|(REF)
\class    PICache

\brief    


\date     $Date: 2006/03/12 19:10:02,78 $
\dbsource opi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   PICache_HPP
#define   PICache_HPP

class     PICache;

#ifndef   DLL_PropertyHandle_HPP
#define   DLL_PropertyHandle_HPP
#include  <sPropertyHandle.hpp>
#include  <sDLL.h>
#endif
#include  <sPropertyHandle.hpp>
#include  <sRessourceLock.hpp>
class  PICache :public DLL(PropertyHandle)
{
protected  :         RessourceLock                                res_lock ATTR_ALIGN(4);                                    //

public     :
public     :         OPI7ImpExp                                          PICache ( );
public     :         OPI7ImpExp                  void Release (PropertyHandle *ph_ptr );
public     :         OPI7ImpExp                  PropertyHandle Reserve ( );
public     :         OPI7ImpExp                                          ~PICache ( );
};

#endif
