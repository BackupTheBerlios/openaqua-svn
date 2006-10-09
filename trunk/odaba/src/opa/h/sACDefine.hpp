/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACDefine

\brief    


\date     $Date: 2006/03/12 19:11:39,82 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACDefine_HPP
#define   ACDefine_HPP

class     ACDefine;

#include  <cPIACC.h>
#include  <sACView.hpp>
#include  <sDBViewDef.hpp>
#pragma pack(8)

class  ACDefine :public ACView
{

public     :
public     :                                                             ACDefine (DBViewDef &view_def, PIACC access_mode=PI_Read );
public     : virtual                                                     ~ACDefine ( );
};

#pragma pack()
#endif
