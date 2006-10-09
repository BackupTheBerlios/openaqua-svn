/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    TSplitter



\date     $Date: 2006/04/28 15:22:40,93 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   TSplitter_HPP
#define   TSplitter_HPP

class     TSplitter;

class     OSSplitter;
#include  <sTField.hpp>
#pragma pack(4)

class  TSplitter :public TField
{

public     :
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateControl (TControl **tc_ptr );
public     : virtual                                logical DoCreate ( );
protected  : virtual                                logical DoCreated ( );
public     :                                        OSSplitter *Style ( ) const;
public     :                                             TSplitter ( );
};

#pragma pack()
#endif
