/********************************* Class Declaration ***************************/
/**
\package  OXML - 
\class    XNode

\brief    


\date     $Date: 2006/06/05 18:19:37,73 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   XNode_HPP
#define   XNode_HPP

class     XNode;

class     ACObject;
class     CTX_Base;
class     DBFieldDef;
class     XMLElement;
class     node;
#include  <cPIACC.h>
#include  <sLNode.hpp>
#include  <sXNode.hpp>
class  XNode :public LNode
{
protected  :         XMLElement                                  *xdata;                                                     // 

public     :
                     XMLElement                                  *get_xdata() { return(xdata); }
public     : virtual                                     ~XNode ( );
};

#endif
