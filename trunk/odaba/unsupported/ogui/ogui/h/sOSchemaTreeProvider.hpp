/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSchemaTreeProvider

\brief    


\date     $Date: 2006/03/13 21:34:33,98 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSchemaTreeProvider_HPP
#define   OSchemaTreeProvider_HPP

class     OSchemaTreeProvider;

class     ODS;
#pragma pack(4)

class  OSchemaTreeProvider :public OTreeProvider
{
public     :         class                                        CaseMatcher ATTR_ALIGN(4);                                 //
protected  :         void                                        *defroot;                                                   //

public     :
public     :         OGUI7ImpExp                 void *AddCollection (void *pvoidParent, ODSRelation *pODSRelation, CaseMatcher *pCaseMatcher );
public     :         OGUI7ImpExp                 void *AddInstance (void *pvoidParent, ODSRelation *pODSRelation, CaseMatcher *pCaseMatcher );
public     :         OGUI7ImpExp                 void *AddRecursion (void *pvoidParent, void *pvoidTo, CaseMatcher *pCaseMatcher );
public     :         OGUI7ImpExp                 void *AddVirtual (void *pvoidParent, CaseMatcher *pCaseMatcher );
public     :         OGUI7ImpExp                 void *GetFactory (void *pvoidNode );
public     :         OGUI7ImpExp                                         OSchemaTreeProvider ( );
protected  : virtual OGUI7ImpExp                 logical doFinalizeODS (OTreeProviderState &rOTreeProviderState );
protected  : virtual OGUI7ImpExp                 logical doGetChildren (OTreeProviderState &rOTreeProviderState );
protected  : virtual OGUI7ImpExp                 ODS *doGetODS (OTreeProviderState &rOTreeProviderState, void *pvoidNode, ODS *podsOld );
protected  : virtual OGUI7ImpExp                 logical doHasChildren (OTreeProviderState &rOTreeProviderState );
public     : virtual OGUI7ImpExp                                         ~OSchemaTreeProvider ( );
public     :                                     logical AA__DEC ( ){
}
public: class CaseMatcher
{
public:
  virtual logical Match( OTreeProviderState* state )
  {
    return YES;
  }

public:
  CaseMatcher()
  {
  }
  virtual ~CaseMatcher() {}
};

private: class CustomDefNode;
private: class SchemaNode;

private: class SchemaODS : public ODS
{
public:
  SchemaNode* node;
  SchemaODS( SchemaNode* n ) : ODS(), node( n ) { n->ref(); }
  virtual ~SchemaODS() 
  {
    node->deref();
  }
};

private: class SchemaNode : public OTreeProvider::Node
{
public:
  CustomDefNode* factory;

  SchemaNode( Node* p, CustomDefNode* fac ) : Node( p ), factory( fac ) {}

public:
  virtual ODS* GetODS( OTreeProviderState* state, ODS* old ) { return NULL; }
  
  logical HasChildren( OTreeProviderState* state )
  {
    return factory->HasChildren( state );
  } 
  void GetChildren( OTreeProviderState* state )
  {
    factory->GetChildren( state );
  }
  virtual void FinalizeODS( OTreeProviderState* state )
  {
  }
};

private: class CustomDefNode
{
public:
  CustomDefNode* parent;
  QList<CustomDefNode> children;
  
  CustomDefNode( CustomDefNode* p ) :
    parent( p )
  {
    if( parent ) parent->children.append( this );
    children.setAutoDelete( YES );
  }
  virtual ~CustomDefNode()
  {
  }
  
  virtual logical IsVisible( OTreeProviderState* state ) { return YES; }
  virtual logical HasItems( OTreeProviderState* state ) { return NO; }
  virtual void Expand( OTreeProviderState* state ) { }
  
  logical HasChildren( OTreeProviderState* state )
  {
    for( CustomDefNode* n= children.first(); n; n = children.next() )
      if( n->IsVisible( state ) )
        if( n->HasItems( state ) ) return YES;
    return NO;
  }
  void GetChildren( OTreeProviderState* state )
  {
    for( CustomDefNode* n= children.first(); n; n = children.next() )
      if( n->IsVisible( state ) )
        n->Expand( state );
  }
  
};

private: class DefNode : public CustomDefNode
{
public:
  CaseMatcher* matcher;
    
  DefNode( CustomDefNode* p, CaseMatcher* m ) : 
    CustomDefNode( p ),
    matcher( m )
    {}
    
  virtual ~DefNode()
  {
    if( matcher ) delete matcher;
  }

  virtual logical IsVisible( Node* node, OTreeProviderState* state )
  {
    return matcher ? matcher->Match( state ) : YES;
  }
};

private: class VirtualDefNode : public DefNode
{
public:
  VirtualDefNode( CustomDefNode* p, CaseMatcher* m ) : DefNode( p, m ) {}
  
  virtual logical HasItems( OTreeProviderState* state ) { return HasChildren( state ); }
  virtual void Expand( OTreeProviderState* state ) { GetChildren( state ); }
};

private: class InstanceDefNode;

private: class InstanceNode : public SchemaNode
{
public:
  InstanceNode( Node* p, CustomDefNode* n ) : SchemaNode( p, n ) {}
protected:
  virtual ODS* GetODS( OTreeProviderState* state, ODS* old )
  {
    ODS* p= new SchemaODS( this );
    ((InstanceDefNode*) factory)->rel->Apply( &state->path, p, YES );
    return p;
  }
  virtual void FinalizeODS( OTreeProviderState* state )
  {
    ODS* p= state->path.last();
    state->path.remove();
    ((InstanceDefNode*) factory)->rel->Apply( &state->path, p, NO );
    state->path.append( p );
  }
};

private: class InstanceDefNode : public DefNode
{
public:
  ODSRelation* rel;
  
  InstanceDefNode( CustomDefNode* p, ODSRelation* r, CaseMatcher* m ) :
    DefNode( p, m ),
    rel( r )
  {
  }
  
  virtual logical HasItems( OTreeProviderState* state )
  {
    return YES; // und zwar genau 1
  }
  virtual void Expand( OTreeProviderState* state )
  {
    Node* node= new InstanceNode( state->currentNode, this );
  }
};

private: class CollectionDefNode;

private: class CollectionNode : public SchemaNode
{
public:
  int pos;
  CollectionNode( Node* p, CustomDefNode* n, int ps ) : SchemaNode( p, n ), pos(ps) {}
protected:
  virtual ODS* GetODS( OTreeProviderState* state, ODS* old )
  {
    ODS* p= NULL;
    if( old && ((SchemaODS*) old)->node->factory == factory ) p= old;
    if( !p )
    {
      p= new SchemaODS(this);
      ((CollectionDefNode*) factory)->rel->Apply( &state->path, p, YES );
    }
    p->ColScroll( pos );
    return p;
  }
  virtual void FinalizeODS( OTreeProviderState* state )
  {
    ODS* p= state->path.last();
    state->path.remove();
    ((CollectionDefNode*) factory)->rel->Apply( &state->path, p, NO );
    state->path.append( p );
  }
};

private: class CollectionDefNode : public DefNode
{
public:
  ODSRelation* rel;
  
  CollectionDefNode( CustomDefNode* p, ODSRelation* r, CaseMatcher* m ) :
    DefNode( p, m ),
    rel( r )
  {
  }
  virtual logical HasItems( OTreeProviderState* state )
  {
    ODS r;
    rel->Apply( &state->path, &r, YES );
    return r.ColGetCount() > 0;
  }
  virtual void Expand( OTreeProviderState* state )
  {
    ODS r;
    rel->Apply( &state->path, &r, YES );
    
    int c= r.ColGetCount();
    
    for( int i= 0; i < c; i++ )
      Node* node= new CollectionNode( state->currentNode, this, i++ );
  }
};

private: class RecursionDefNode : public DefNode
{
public:
  CustomDefNode* to;
  
  RecursionDefNode( CustomDefNode* p, CustomDefNode* t, CaseMatcher* m ) : DefNode( p, m ), to( t ) {}
  
  virtual logical HasItems( OTreeProviderState* state ) { return to->HasChildren( state ); }
  virtual void Expand( OTreeProviderState* state ) { to->GetChildren( state ); }
};

private: void __DEC0()
{
}

};

#pragma pack()
#endif
