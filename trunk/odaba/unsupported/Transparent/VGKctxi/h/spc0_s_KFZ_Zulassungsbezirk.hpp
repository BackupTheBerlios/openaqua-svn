/********************************* Class Declaration ***************************/
/**
\package  VGKctxi - 
\class    pc0_s_KFZ_Zulassungsbezirk

\brief    


\date     $Date: 2006/07/03 16:08:44,75 $
\dbsource Q:/Transparent.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc0_s_KFZ_Zulassungsbezirk_HPP
#define   pc0_s_KFZ_Zulassungsbezirk_HPP

class     pc0_s_KFZ_Zulassungsbezirk;

class     PropertyHandle;
#include  <sDatabaseHandle.hpp>
#include  <spc0_Stammdaten.hpp>
class  pc0_s_KFZ_Zulassungsbezirk :public pc0_Stammdaten
{

public     :
public     :                                             pc0_s_KFZ_Zulassungsbezirk (PropertyHandle *prophdl );
public     :                                             pc0_s_KFZ_Zulassungsbezirk (DatabaseHandle &dbhandle, PIACC accopt );
};

#endif
