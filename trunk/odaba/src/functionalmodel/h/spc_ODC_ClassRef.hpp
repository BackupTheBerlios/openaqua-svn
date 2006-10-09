/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    pc_ODC_ClassRef

\brief    


\date     $Date: 2006/03/13 21:30:35,00 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_ODC_ClassRef_HPP
#define   pc_ODC_ClassRef_HPP

class     pc_ODC_ClassRef;

#ifndef   P_ODC_ClassRef_HPP
#define   P_ODC_ClassRef_HPP
#include  <sPI.hpp>
class       ODC_ClassRef;
PI_dcl     (ODC_ClassRef)
#endif
#include  <cClassModLevel.h>
#include  <cPIACC.h>
#include  <sDatabaseHandle.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  pc_ODC_ClassRef :public PropertyHandle
{

public     :
public     :                                     logical SetCompRequest (char *classname, ClassModLevel cmod_level );
public     :                                                             pc_ODC_ClassRef (DatabaseHandle &dbhandle, PIACC accopt );
public     :                                                             pc_ODC_ClassRef (PI(mem) *pmemptr );
};

#pragma pack()
#endif
