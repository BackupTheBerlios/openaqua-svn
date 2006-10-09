/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    UCA_CActionList

\brief    


\date     $Date: 2006/03/12 19:20:21,46 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   UCA_CActionList_HPP
#define   UCA_CActionList_HPP

class     UCA_CActionList;

#ifndef   DLL_UCA_CAction_HPP
#define   DLL_UCA_CAction_HPP
#include  <sUCA_CAction.hpp>
#include  <sDLL.h>
#endif
#pragma pack(8)

class  UCA_CActionList :public DLL(UCA_CAction)
{

public     :
public     :         SOS7ImpExp                  UCA_CAction *Search (char *acname );
public     :         SOS7ImpExp                                          UCA_CActionList ( );
public     :         SOS7ImpExp                                          ~UCA_CActionList ( );
};

#pragma pack()
#endif
