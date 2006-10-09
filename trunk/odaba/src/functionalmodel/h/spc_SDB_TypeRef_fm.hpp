/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/19|19:04:48,89}|(REF)
\class    pc_SDB_TypeRef_fm



\date     $Date: 2006/03/20 20:59:42,89 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_SDB_TypeRef_fm_HPP
#define   pc_SDB_TypeRef_fm_HPP

class     pc_SDB_TypeRef_fm;

#include  <cClassModLevel.h>
#include  <cCompileStates.h>
#include  <cIncRef_Level.h>
#include  <spc_SDB_TypeRef.hpp>
class  pc_SDB_TypeRef_fm :public pc_SDB_TypeRef
{

public     :
public     :                                     logical ProvideReference (PropertyHandle *member_ph );
public     :                                     logical SetCompRequest (ClassModLevel cmod_level );
public     :                                                             pc_SDB_TypeRef_fm (PropertyHandle *prophdl );
};

#endif
