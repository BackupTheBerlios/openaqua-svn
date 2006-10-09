/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACSysProperty

\brief    


\date     $Date: 2006/03/12 19:12:15,21 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACSysProperty_HPP
#define   ACSysProperty_HPP

class     ACSysProperty;

class     DBFieldDef;
class     node;
#include  <cSystemPropertyTypes.h>
#include  <sbnode.hpp>
class  ACSysProperty :public bnode
{
protected  :         SystemPropertyTypes                          type ATTR_ALIGN(4);                                        //

public     :
public     :                                                             ACSysProperty (node *nodeptr, DBFieldDef *fielddef );
public     :                                     logical Check (logical autoini=NO, logical acccheck=YES );
public     :                                     void *Get (int32 indx0, logical chknode=YES );
public     :                                     void *Get (char *skey, logical chknode=YES );
public     :                                     void *Get ( );
public     :                                     void *Modify (logical chknode=YES );
public     :                                     logical Store ( );
public     :                                                             ~ACSysProperty ( );
};

#endif
