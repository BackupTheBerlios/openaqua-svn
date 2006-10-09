/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OStyle



\date     $Date: 2006/04/28 16:54:50,57 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OStyle_HPP
#define   OStyle_HPP

class     OStyle;

class     PropertyHandle;
#include  <cADK_STYLES.h>
#include  <sDBorder.hpp>
#include  <sOResource.hpp>
#pragma pack(4)

class  OStyle :public OResource
{
protected  :         ADK_STYLES                                   type;                                                      
protected  :         logical                                      border;                                                    
protected  :         DBorder                                      border_style;                                              

public     :
                     ADK_STYLES                                   get_type() { return(type); }
                     logical                                      get_border() { return(border); }
                     DBorder                                     &get_border_style() { return(border_style); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                        logical HasBorder ( );
public     :                                             OStyle ( );
public     :                                             OStyle (OResource bcOResource, int16 itype, logical border, DBorder dborder );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OStyle ( );
};

#pragma pack()
#endif
