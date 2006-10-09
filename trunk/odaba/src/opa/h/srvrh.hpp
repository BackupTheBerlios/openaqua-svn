/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    rvrh

\brief    


\date     $Date: 2006/03/12 19:15:09,95 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   rvrh_HPP
#define   rvrh_HPP

class     rvrh;

#pragma pack(8)

class  rvrh
{
protected  :         char                                         rvrhidnt[4];                                               
public     :         int32                                        rvrhstim;                                                  
public     :         int32                                        rvrhttim;                                                  
public     :         int32                                        rvrhsdat;                                                  
public     :         int32                                        rvrhtdat;                                                  
protected  :         char                                         rvrhres[120];                                              

public     :
public     :                                                             rvrh ( );
};

#pragma pack()
#endif
