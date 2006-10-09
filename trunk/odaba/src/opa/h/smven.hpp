/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    mven

\brief    


\date     $Date: 2006/03/12 19:14:33,09 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   mven_HPP
#define   mven_HPP

class     mven;

#define  MVEN                                      sizeof(EB_Number)+4
class     mven;
#include  <sEB_Number.hpp>
#pragma pack(8)

class  mven :public EB_Number
{
protected  :         int32                                        mvencnt ATTR_ALIGN(1);                                     
protected  :         char                                         mvenkey[2];                                                

public     :
public     :                                     int32 mvencntg (logical pif );
public     :                                     void mvencnts (int32 count, logical pif );
public     : static                              mven *__cdecl mvencrt (int16 klen );
public     :                                     int32 mvendcr (logical pif );
public     :                                     int32 mvenicr (logical pif );
public     :                                     void mvenini (int16 klen );
public     :                                     void mvencntr ( ){

 mvencnt = 0;

}

public     :                                     char *mvenkeyg ( ){

 return (mvenkey);

}

};

#pragma pack()
#endif
