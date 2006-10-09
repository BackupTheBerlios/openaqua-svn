/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    cte

\brief    


\date     $Date: 2006/03/12 19:14:09,57 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cte_HPP
#define   cte_HPP

class     cte;

#include  <sEB_Number.hpp>
#pragma pack(1)

class  cte
{
protected  :         EB_Number                                    cteebsn;                                                   
protected  :         int32                                        ctelen;                                                    
protected  :         int32                                        ctepos;                                                    

public     :
                     EB_Number                                   &get_cteebsn() { return(cteebsn); }
                     int32                                        get_ctelen() { return(ctelen); }
                     int32                                        get_ctepos() { return(ctepos); }
public     :                                     void FromPIF (logical pif );
public     :                                     void ToPIF (logical pif );
public     :                                     void SetLength (int32 length ){

  ctelen = length;

}

public     :                                     void SetNumber (EB_Number entnr ){

  cteebsn = entnr;

}

public     :                                     void SetPosition (int32 position ){

  ctepos = position;

}

};

#pragma pack()
#endif
