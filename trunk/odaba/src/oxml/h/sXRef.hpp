/********************************* Class Declaration ***************************/
/**
\package  OXML - 
\class    XRef

\brief    


\date     $Date: 2006/06/29 12:02:57,39 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   XRef_HPP
#define   XRef_HPP

class     XRef;

class     BinTree;
class     DBIndex;
class     LACObject;
class     XMLElement;
#include  <sEB_Number.hpp>
#include  <sOXMLBase.hpp>
#include  <sref.hpp>
class  XRef :public ref,
public OXMLBase
{
protected  :         BinTree                                     *tree;                                                      // 

public     :
                     BinTree                                     *get_tree() { return(tree); }
public     : virtual                                int32 GetCount ( );
public     : virtual                                EB_Number GetID (int32 lindx0 );
public     : virtual                                int32 GetIndex (char *skey, EB_Number ebsnum, logical exact=YES );
public     : virtual                                int32 GetIndex (EB_Number ebsnum );
public     : virtual                                logical Reset ( );
public     : virtual                                logical Setup (EB_Number *extref, EB_Number clnumb, int16 w_mbnumber=0 );
public     :                                             XRef (LACObject *lobhandle, DBIndex *akcbptr );
public     :                                             ~XRef ( );
};

#endif
