/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    ACOperand

\brief    Operand node
          Operand  nodes  are  used  for  operations  representing  the operands
          passed  to the operation  (Select, Product, ...).  The operand node it
          set  in the  query node  (op_base) as  value. The expression is set in
          the source node.

\date     $Date: 2006/03/12 19:11:57,25 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ACOperand_HPP
#define   ACOperand_HPP

class     ACOperand;

class     ACOperation;
class     OPBase;
class     node;
#include  <sbnode.hpp>
class  ACOperand :public bnode
{
protected  :         OPBase                                      *op_base ATTR_ALIGN(4);                                     //

public     :
                     OPBase                                      *get_op_base() { return(op_base); }
public     :                                                             ACOperand (OPBase *op_base );
public     :                                     logical Cancel (logical chknode=YES );
public     :                                     logical Open (ACOperation *op_node );
public     :                                     logical Read ( );
public     :                                     logical Store ( );
public     :                                     logical Switch (int32 indx0 );
public     :                                                             ~ACOperand ( );
};

#endif
