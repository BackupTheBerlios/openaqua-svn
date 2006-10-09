/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    UCA_Function

\brief    


\date     $Date: 2006/03/12 19:20:21,62 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   UCA_Function_HPP
#define   UCA_Function_HPP

class     UCA_Function;

class     CTX_Base;
#include  <sUCA_Action.hpp>
#pragma pack(8)

class  UCA_Function :public UCA_Action
{

public     :
public     : virtual SOS7ImpExp                  logical Execute ( );
public     :         SOS7ImpExp                                          UCA_Function (char *fname, CTX_Base *fncptr );
public     : virtual SOS7ImpExp                                          ~UCA_Function ( );
};

#pragma pack()
#endif
