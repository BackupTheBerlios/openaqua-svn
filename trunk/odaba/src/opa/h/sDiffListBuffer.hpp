/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DiffListBuffer

\brief    


\date     $Date: 2006/03/12 19:13:12,09 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DiffListBuffer_HPP
#define   DiffListBuffer_HPP

class     DiffListBuffer;

class     LACObject;
#include  <sexdBuffer.hpp>
#pragma pack(8)

class  DiffListBuffer :public exdBuffer
{
protected  :         int16                                        ws_level ATTR_ALIGN(4);                                    
protected  :         int32                                        temp_entnr;                                                

public     :
                     int16                                        get_ws_level() { return(ws_level); }
                     int32                                        get_temp_entnr() { return(temp_entnr); }
public     :                                                             DiffListBuffer (LACObject *lobhandle, uint8 wslevel );
public     :                                                             DiffListBuffer ( );
public     :                                     exd *ProvideEXD (EB_Number entnr );
public     :                                                             ~DiffListBuffer ( );
};

#pragma pack()
#endif
