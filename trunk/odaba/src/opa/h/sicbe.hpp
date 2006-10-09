/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    icbe

\brief    


\date     $Date: 2006/03/12 19:14:25,76 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   icbe_HPP
#define   icbe_HPP

class     icbe;

#include  <sEB_Number.hpp>
#pragma pack(8)

class  icbe :public EB_Number
{
protected  :         int16                                        icbelev ATTR_ALIGN(1);                                     

public     :
                     int16                                        get_icbelev() { return(icbelev); }
public     :                                     void FromPIF (logical pif );
public     :                                     void ToPIF (logical pif );
public     :                                     void icbeini ( );
public     :                                     int16 icbelevi ( ){

 return(++icbelev);

}

public     :                                     void icbelevr ( ){

 icbelev = 1;

}

};

#pragma pack()
#endif
