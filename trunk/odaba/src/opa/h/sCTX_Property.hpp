/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    CTX_Property

\brief    Property contexts
          Property  contexts  are  created  for extents, references, attributes,
          relationships  and  base  structures.  The  property  context  defines
          refers  to  the  property  instance  as  well  as  to  the  property 
          definition.  Moreover,  it  allows  determining  the  active  context 
          hierarchy  for  the  property,  i.e.  the  parent  structure/Database 
          Object,  the  property  the  parent  structure  is  accessed from, the
          parent  parent structure  etc. Thus,  the property context defines the
          context in which the property instance has been provided. 
          The  parent  context  for  a  property  context is a structure context
          (when  the  property  is  part  of  an  object instance) or a Database
          Object context (when the property is an extent. 
          The  property context allows handling read and update events, validity
          checks and insert and remove events.
          The  default  property  context  can  be  overloaded  by a application
          specific property context classes.

\date     $Date: 2006/03/12 19:12:43,15 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   CTX_Property_HPP
#define   CTX_Property_HPP

class     CTX_Property;

class     CTX_Base;
class     CTX_Property;
class     CTX_Structure;
class     DBFieldDef;
class     bnode;
class     node;
#include  <sCTX_DBBase.hpp>
#include  <sPropertyHandle.hpp>
#pragma pack(8)

class  CTX_Property :public CTX_DBBase
{
protected  :         node                                        *prop_node ATTR_ALIGN(4);                                   //

public     :
                     node                                        *get_prop_node() { return(prop_node); }
public     :         opa7ImpExp                                          CTX_Property ( );
public     : virtual opa7ImpExp                  logical DBRefresh ( );
public     :         opa7ImpExp                  ODABAClient &GetConnectionClient ( );
public     : virtual opa7ImpExp                  CTX_Types GetContextType ( );
public     : virtual opa7ImpExp                  PropertyHandle GetDBField (char *fldname_w=NULL );
public     :                                     DBFieldDef *GetDefinition ( );
public     :         opa7ImpExp                  CTX_Structure *GetInstContext ( );
public     : virtual opa7ImpExp                  CTX_Property *GetPropContext (char *w_fldnames=NULL );
public     : virtual opa7ImpExp                  PropertyHandle *GetPropertyHandle (char *fldname_w=NULL );
public     : virtual opa7ImpExp                  char *GetResourceName ( );
public     : virtual opa7ImpExp                  CTX_Structure *GetStructContext (char *w_strnames=NULL );
public     :                                     void Initialize (bnode *bnode_ptr, CTX_Base *highctx );
public     : virtual opa7ImpExp                  logical IsEdit ( );
public     :         opa7ImpExp                  logical IsReadOnly ( );
public     :                                     void MarkReadOnly (logical readonly );
public     :         opa7ImpExp                  logical SetReadOnly (logical readonly );
public     :         opa7ImpExp                  void SetResult (char *result_string );
public     : virtual opa7ImpExp                  void SetTransactionError ( );
public     : virtual opa7ImpExp                                          ~CTX_Property ( );
};

#pragma pack()
#endif
