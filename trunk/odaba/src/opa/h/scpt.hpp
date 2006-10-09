/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    cpt

\brief    


\date     $Date: 2006/03/12 19:14:08,51 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   cpt_HPP
#define   cpt_HPP

class     cpt;

#ifndef   P_cpt_HPP
#define   P_cpt_HPP
#include  <sPI.hpp>
class       cpt;
PI_dcl     (cpt)
#endif
#ifndef   P_dsc_HPP
#define   P_dsc_HPP
#include  <sPI.hpp>
class       dsc;
PI_dcl     (dsc)
#endif
#pragma pack(4)

class  cpt
{
protected  :         char                                         cpttop[40];                                                
protected  :         PI(dsc)                                      cptdsc;                                                    
protected  :         PI(cpt)                                      cptptop;                                                   
protected  :         PI(cpt)                                      cptpcpt;                                                   

public     :
                     char                                        *get_cpttop() { return(cpttop); }
                     PI(dsc)                                     &get_cptdsc() { return(cptdsc); }
                     PI(cpt)                                     &get_cptptop() { return(cptptop); }
                     PI(cpt)                                     &get_cptpcpt() { return(cptpcpt); }
};

#pragma pack()
#endif
