/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OSGroupBox



\date     $Date: 2006/04/28 16:54:33,82 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSGroupBox_HPP
#define   OSGroupBox_HPP

class     OSGroupBox;

class     PropertyHandle;
#include  <sOStyle.hpp>
class  OSGroupBox :public OStyle
{
protected  :         logical                                      vertical;                                                  

public     :
                     logical                                      get_vertical() { return(vertical); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     : virtual                                char *GetObjectType ( );
public     :                                             OSGroupBox ( );
public     :                                             OSGroupBox (OStyle bcOStyle, logical vertical );
public     : virtual                                logical Read (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     : virtual                                     ~OSGroupBox ( );
};

#endif
