/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    pc_TopicFromOldStyle

\brief    


\date     $Date: 2006/03/13 21:30:35,71 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   pc_TopicFromOldStyle_HPP
#define   pc_TopicFromOldStyle_HPP

class     pc_TopicFromOldStyle;

#include  <sPropertyHandle.hpp>
class  pc_TopicFromOldStyle :public PropertyHandle
{
protected  :         DictionaryHandle                             dict;                                                      

public     :
public     :                                     PropertyHandle *Check (PropertyHandle *prophdl );
public     :                                     logical Setup_ODC_FunctImp (PropertyHandle *prophdl );
public     :                                     logical Setup_ODC_ImpClass ( );
public     :                                     logical Setup_ODC_PFunction (PropertyHandle *prophdl );
public     :                                     logical Setup_SDB_Resource (PropertyHandle *prophdl );
public     :                                     logical Setup_SDB_Structure ( );
public     :                                     logical Setup_SDB_ValueList ( );
public     :                                     logical Setup_collection (PropertyHandle *prophdl );
public     :                                                             pc_TopicFromOldStyle (PropertyHandle *prophdl );
};

#endif
