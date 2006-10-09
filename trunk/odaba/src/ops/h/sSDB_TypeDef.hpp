/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_TypeDef

\brief    


\date     $Date: 2006/03/13 21:30:13,81 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_TypeDef_HPP
#define   SDB_TypeDef_HPP

class     SDB_TypeDef;

#ifndef   P_SDB_NameSpace_HPP
#define   P_SDB_NameSpace_HPP
#include  <sPI.hpp>
class       SDB_NameSpace;
PI_dcl     (SDB_NameSpace)
#endif
#include  <sSDB_Member.hpp>
#include  <sSDB_Type.hpp>
#pragma pack(8)

class  SDB_TypeDef :public SDB_Type,
public SDB_Member
{
protected  :         PI(SDB_NameSpace)                            name_space;                                                

public     :
                     PI(SDB_NameSpace)                           &get_name_space() { return(name_space); }
};

#pragma pack()
#endif
