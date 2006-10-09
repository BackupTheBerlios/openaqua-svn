/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    nodelist

\brief    


\date     $Date: 2006/03/12 19:14:56,68 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   nodelist_HPP
#define   nodelist_HPP

class     nodelist;

#ifndef   DLL_node_HPP
#define   DLL_node_HPP
#include  <snode.hpp>
#include  <sDLL.h>
#endif
class     CTX_Property;
class     bnode;
class     node;
#include  <snodelist.hpp>
#pragma pack(8)

class  nodelist :public DLL(node)
{

public     :
public     :         opa7ImpExp                  void DeleteNodes ( );
public     :         opa7ImpExp                  bnode *GetNextBNode ( );
public     :         opa7ImpExp                  node *GetNode (char *fldname, CTX_Property *highprop_ctx, logical recursiv=NO );
public     :         opa7ImpExp                  node *GetNode (char *fldname, char *proppath, logical recursiv=NO );
public     :         opa7ImpExp                  node **GetNodePtr (char *fldname, CTX_Property *highprop_ctx, logical recursiv=NO );
public     :         opa7ImpExp                  node **GetNodePtr (char *fldname, char *proppath, logical recursiv=NO );
public     :         opa7ImpExp                  logical Modify ( );
public     :         opa7ImpExp                                          nodelist ( );
public     :         opa7ImpExp                                          nodelist (nodelist &nlist_ref );
public     :         opa7ImpExp                  nodelist &operator= (nodelist &nlist_ref );
public     :         opa7ImpExp                                          ~nodelist ( );
};

#pragma pack()
#endif
