/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    dsc

\brief    


\date     $Date: 2006/03/12 19:14:14,06 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   dsc_HPP
#define   dsc_HPP

class     dsc;

#ifndef   P_k32_HPP
#define   P_k32_HPP
#include  <sPI.hpp>
class       k32;
PI_dcl     (k32)
#endif
#include  <sk32.hpp>
#pragma pack(4)

class  dsc
{
protected  :         k32                                          dscref;                                                    
protected  :         char                                         dsctitle[80];                                              
protected  :         char                                         dsclang[2];                                                
protected  :         PI(k32)                                      dsckeys;                                                   
protected  :         PI(mem)                                      dscuser;                                                   
protected  :         PI(mem)                                      dscsys;                                                    
protected  :         PI(mem)                                      dscexpl;                                                   
protected  :         PI(mem)                                      dscnote;                                                   

public     :
                     k32                                         &get_dscref() { return(dscref); }
                     char                                        *get_dsctitle() { return(dsctitle); }
                     char                                        *get_dsclang() { return(dsclang); }
                     PI(k32)                                     &get_dsckeys() { return(dsckeys); }
                     PI(mem)                                     &get_dscuser() { return(dscuser); }
                     PI(mem)                                     &get_dscsys() { return(dscsys); }
                     PI(mem)                                     &get_dscexpl() { return(dscexpl); }
                     PI(mem)                                     &get_dscnote() { return(dscnote); }
};

#pragma pack()
#endif
