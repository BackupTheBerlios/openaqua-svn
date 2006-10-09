/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    EBRootBase

\brief    


\date     $Date: 2006/03/12 19:13:15,79 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EBRootBase_HPP
#define   EBRootBase_HPP

class     EBRootBase;

#include  <sEBMainBase.hpp>
#pragma pack(1)

class  EBRootBase :public EBMainBase
{

public     :
public     :                                                             EBRootBase (char *filename );
public     :                                     void FromPif (logical pif );
public     :                                     void ToPIF (logical pif );
};

#pragma pack()
#endif
