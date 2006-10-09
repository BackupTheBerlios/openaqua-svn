/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OSSplitter



\date     $Date: 2006/04/28 16:56:15,15 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSSplitter_HPP
#define   OSSplitter_HPP

class     OSSplitter;

class     PropertyHandle;
#include  <sOStyle.hpp>
class  OSSplitter :public OStyle
{
protected  :         int32                                        hwidth;                                                    
protected  :         logical                                      horizontal;                                                

public     :
                     int32                                        get_hwidth() { return(hwidth); }
                     logical                                      get_horizontal() { return(horizontal); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                             OSSplitter ( );
public     :                                             OSSplitter (OStyle bcOStyle, int32 hwidth, logical horizontal );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OSSplitter ( );
};

#endif
