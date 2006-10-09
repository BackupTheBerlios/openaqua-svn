/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    FieldList

\brief    


\date     $Date: 2006/03/12 19:13:22,85 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   FieldList_HPP
#define   FieldList_HPP

class     FieldList;

#ifndef   P_SDB_Member_HPP
#define   P_SDB_Member_HPP
#include  <sPI.hpp>
class       SDB_Member;
PI_dcl     (SDB_Member)
#endif
class     DBHandle;
class     Dictionary;
class     FieldList;
#include  <sfmcl.hpp>
#pragma pack(8)

class  FieldList :public fmcl
{

public     :
public     :                                                             FieldList (int16 memcnt );
public     :                                                             FieldList (void *table, int16 tesize, int16 memcnt );
public     :                                     logical fmcdicpy (FieldList *srceflist, void *targinst, void *srceinst );
public     :                                                             ~FieldList ( );
};

#pragma pack()
#endif
