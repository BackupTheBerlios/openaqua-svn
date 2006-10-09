/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OSyntaxClass



\date     $Date: 2006/04/28 16:53:31,71 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSyntaxClass_HPP
#define   OSyntaxClass_HPP

class     OSyntaxClass;

class     PropertyHandle;
#include  <sDSyntaxClass.hpp>
#include  <sOResource.hpp>
class  OSyntaxClass :public OResource,
public DSyntaxClass
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OSyntaxClass ( );
public     :                                             OSyntaxClass (OResource bcOResource, DSyntaxClass bcDSyntaxClass );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                                             ~OSyntaxClass ( );
};

#endif
