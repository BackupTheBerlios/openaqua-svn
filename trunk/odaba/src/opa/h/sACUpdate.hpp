/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACUpdate

\brief    


\date     $Date: 2006/03/12 19:12:18,34 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACUpdate_HPP
#define   ACUpdate_HPP

class     ACUpdate;

#include  <cPIACC.h>
#include  <sACView.hpp>
#include  <sDBViewDef.hpp>
#pragma pack(8)

class  ACUpdate :public ACView
{

public     :
public     :                                                             ACUpdate (DBViewDef &view_def, PIACC access_mode=PI_Read );
public     :                                     logical Execute ( );
public     :                                     logical InitUpdateFields (DBViewDef &view_def, PIACC access_mode=PI_Read );
public     : virtual                                                     ~ACUpdate ( );
};

#pragma pack()
#endif
