/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OSButtonGroup



\date     $Date: 2006/04/28 16:52:53,89 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSButtonGroup_HPP
#define   OSButtonGroup_HPP

class     OSButtonGroup;

class     PropertyHandle;
#include  <sOStyle.hpp>
class  OSButtonGroup :public OStyle
{
protected  :         logical                                      vertical;                                                  
protected  :         logical                                      exclusive;                                                 

public     :
                     logical                                      get_vertical() { return(vertical); }
                     logical                                      get_exclusive() { return(exclusive); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                             OSButtonGroup ( );
public     :                                             OSButtonGroup (OStyle bcOStyle, logical vertical, logical exclusive );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OSButtonGroup ( );
};

#endif
