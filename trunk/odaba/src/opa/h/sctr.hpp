/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ctr

\brief    


\date     $Date: 2006/03/12 19:14:09,75 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ctr_HPP
#define   ctr_HPP

class     ctr;

#define  CTR_HEADER_LEN                            sizeof(ctr)-1
class     cte;
#pragma pack(1)

class  ctr
{
protected  :         int32                                        ctrlen;                                                    
protected  :         int16                                        ctrecnt;                                                   
protected  :         char                                         ctrtable;                                                  

public     :
                     int32                                        get_ctrlen() { return(ctrlen); }
                     int16                                        get_ctrecnt() { return(ctrecnt); }
public     :                                     void Initialize ( );
public     :                                     logical Reorganize ( );
public     :                                     logical ReorganizeOld ( );
public     :                                     cte *ctrget (int32 indx0, logical pif, cte &cteenty, uint16 version );
public     :                                     cte *ctrget (int32 indx0 );
public     :                                     void SetCount (int16 ecnt ){

  ctrecnt = ecnt;

}

public     :                                     void SetLength (int32 length ){

  ctrlen = length;

}

};

#pragma pack()
#endif
