/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_NamedObject

\brief    Named database objects
          Named  database  objects  can  be  defined  for a database in order to
          refer  it by  name instead  of following  the complete hierarchy path.
          Named  objects can be arranged in object hierarchies but can be opened
          just  by referring  to the  object name.  Moreover, named objects will
          get  a  resource  identifier,  which allows defining specific database
          object context functions.

\date     $Date: 2006/03/13 21:30:33,78 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_NamedObject_HPP
#define   ODC_NamedObject_HPP

class     ODC_NamedObject;

#ifndef   P_ODC_Module_HPP
#define   P_ODC_Module_HPP
#include  <sPI.hpp>
class       ODC_Module;
PI_dcl     (ODC_Module)
#endif
#include  <sEB_Number.hpp>
#include  <sSDB_Resource.hpp>
#pragma pack(8)

class  ODC_NamedObject :public SDB_Resource
{
public     :         EB_Number                                    object_ref ATTR_ALIGN(4);                                  
protected  :         PI(ODC_Module)                               module;                                                    

public     :
                     PI(ODC_Module)                              &get_module() { return(module); }
};

#pragma pack()
#endif
