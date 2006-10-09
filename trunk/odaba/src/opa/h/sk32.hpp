/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    k32

\brief    


\date     $Date: 2006/03/12 19:14:32,37 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   k32_HPP
#define   k32_HPP

class     k32;

#pragma pack(8)

class  k32
{
protected  :         char                                         k32name[32];                                               

public     :
                     char                                        *get_k32name() { return(k32name); }
public     :                                     NOTYPE operator char * ( ){

  return(k32name);

}

};

#pragma pack()
#endif
