/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    rvre

\brief    


\date     $Date: 2006/03/12 19:15:09,78 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   rvre_HPP
#define   rvre_HPP

class     rvre;

#define  RVRE                                      sizeof(rvre)-2
#include  <sEB_Number.hpp>
#pragma pack(8)

class  rvre
{
public     :         char                                         rvreidnt[4];                                               
public     :         int32                                        rvredat;                                                   
public     :         int32                                        rvretim;                                                   
public     :         int32                                        rvreelen;                                                  
public     :         int32                                        rvreeoff;                                                  
public     :         int16                                        rvreulen;                                                  
public     :         char                                         rvreoper;                                                  
public     :         logical                                      rvreinst;                                                  
public     :         char                                         rvreuser[2];                                               

public     :
public     :                                                             rvre ( );
};

#pragma pack()
#endif
