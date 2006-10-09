/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OFont_



\date     $Date: 2006/04/28 16:44:04,92 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OFont__HPP
#define   OFont__HPP

class     OFont_;

class     PropertyHandle;
#include  <sDFont.hpp>
#include  <sOResource.hpp>
class  OFont_ :public OResource,
public DFont
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                             OFont_ ( );
public     :                                             OFont_ (OResource bcOResource, DFont bcDFont );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : static                                 OFont_ *__cdecl ReadFromResource (char *font_name );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OFont_ ( );
};

#endif
