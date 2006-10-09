/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    sinti

\brief    Instance area for operations
          Operation  instances are created for  different types of ACOperations.
          Operation  instances  are  based  on  a  calling  node  (nodenode  in 
          ACOperation).  Instance  areas  for  operations  may  consist  of four
          parts:
          Base  structures:  Base  structures  describe instances inherited from
          other  nodes. Usually,  base instances  inherit the instance area from
          the  referenced node. Base instances  do nor contain values calculated
          in the context of the operation (Product, Join)
          Attributes:  attribute values are attributes derived from the instance
          in the calling object  (Select, GrupBy). 
          References:  reference values are collections derived from the calling
          object (Select, GrupBy).
          An  sinti may  contain multiple  instances (Product, Join) when having
          one  or more base structures. otherwise it inherits the selection from
          its calling object.

\date     $Date: 2006/03/12 19:15:10,09 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   sinti_HPP
#define   sinti_HPP

class     sinti;

class     ACOperation;
class     DBStructDef;
class     OperEnvironment;
class     node;
#include  <sEB_Number.hpp>
#include  <sOPDecl.hpp>
#include  <sbinti.hpp>
#pragma pack(8)

class  sinti :public binti,
public OPDecl
{
protected  :         ACOperation                                 *operation;                                                 //
protected  :         OperEnvironment                             *oper_env;                                                  //
protected  :         logical                                      is_multiple;                                               //

public     :
                     ACOperation                                 *get_operation() { return(operation); }
                     OperEnvironment                             *get_oper_env() { return(oper_env); }
                     logical                                      get_is_multiple() { return(is_multiple); }
public     :                                     logical Add (logical global_add=NO );
public     :                                     logical Cancel ( );
public     : virtual                             logical Delete (char *extname, logical is_root, int16 delopt=AUTO );
public     :                                     logical First ( );
public     : virtual                             logical Get (EB_Number entnr );
public     : virtual                             logical GetData ( );
public     :                                     void InitBaseInti (node *nodeptr );
public     : virtual                             logical IsPositioned ( );
public     :                                     logical Last ( );
public     :                                     logical LocateKey (char *skey, logical exact=YES );
public     :                                     logical Next (int32 count );
public     :                                     logical Next (node *nodeptr );
public     :                                     logical OpenOperands ( );
public     :                                     logical Position (int32 count );
public     :                                     logical Previous (int32 count );
public     :                                     logical Previous (node *nodeptr );
public     :                                     logical ResetInstance ( );
public     :                                     logical ResetInstance (node *nodeptr );
public     :                                     logical Save (logical switchopt, logical overwrite=NO, logical refresh_opt=NO );
public     :                                     logical Switch ( );
public     :                                                             sinti (ACOperation *op_node, DBStructDef *strdef, void *instptr, logical crt_opt, OperEnvironment *operenv );
public     :                                                             sinti ( );
public     : virtual                                                     ~sinti ( );
};

#pragma pack()
#endif
