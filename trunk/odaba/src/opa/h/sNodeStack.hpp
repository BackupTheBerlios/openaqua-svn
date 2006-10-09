/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    NodeStack

\brief    


\date     $Date: 2006/03/12 19:13:40,93 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   NodeStack_HPP
#define   NodeStack_HPP

class     NodeStack;

#ifndef   DPA_node_HPP
#define   DPA_node_HPP
#include  <snode.hpp>
#include  <sDPA.h>
#endif
class     node;
class  NodeStack :public DPA(node)
{
protected  :         int32                                        current_position ATTR_ALIGN(4);                            //

public     :
                     int32                                        get_current_position() { return(current_position); }
public     :                                     node *Get (int32 position );
public     :                                                             NodeStack ( );
public     :                                     node *Pop (int32 count );
public     :                                     node *Pop ( );
public     :                                     int32 Push (node *nodeptr );
public     :                                     logical Set (node *nodeptr, int32 position );
public     :                                                             ~NodeStack ( );
};

#endif
