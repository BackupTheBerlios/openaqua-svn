/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSchemaTreeViewDesigner

\brief    


\date     $Date: 2006/03/13 21:34:34,81 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSchemaTreeViewDesigner_HPP
#define   OSchemaTreeViewDesigner_HPP

class     OSchemaTreeViewDesigner;

#include  <sOSchemaTreeProvider.hpp>
class  OSchemaTreeViewDesigner :public OTreeViewDesigner
{
protected  :                                                      Q_OBJECT;                                                  //
public     :         class                                        Designer;                                                  //
public     :         typedef QList<void>                          QListVoid;                                                 //
protected  :         QPtrDict<QListVoid>                          def;                                                       //
protected  :         OSchemaTreeProvider                         *schema;                                                    //
protected  :         __int64                                      lastState;                                                 //
protected  :         Designer                                    *lastDesigner;                                              //

public     :
public     :         OGUI7ImpExp                 logical Add (void *pvoidFactory, Designer *pDesigner, OSchemaTreeProvider::CaseMatcher *pOSchemaTreeProviderCaseMatcher );
public     :         OGUI7ImpExp                 OSchemaTreeViewDesigner::Designer *AddSimple (void *pvoidFactory, const QCString &rcqcTexts, const QCString &rcqcPixmaps, OSchemaTreeProvider::CaseMatcher *pOSchemaTreeProviderCaseMatcher, logical fCheckable );
public     :                                     public slots: void Fire (OTreeProviderState &rOTreeProviderState );
public     :         OGUI7ImpExp                                         OSchemaTreeViewDesigner (OSchemaTreeProvider *pOSchemaTreeProvider );
protected  : virtual                             logical doGetCheckable (OTreeProviderState &rOTreeProviderState );
protected  : virtual                             QPixmap doGetPixmap (OTreeProviderState &rOTreeProviderState, int32 iColumn );
protected  : virtual                             QString doGetText (OTreeProviderState &rOTreeProviderState, int32 iColumn );
protected  :                                     OSchemaTreeViewDesigner::Designer *getDesigner (OTreeProviderState &rOTreeProviderState );
protected  :                                     logical _Designer ( ){
}
public: class Designer
{
public:
  OSignalRouter Fire;
public:
  virtual QString GetText( OTreeProviderState& state, int iColumn )
  {
    return QString();
  }
  
  virtual QPixmap GetPixmap( OTreeProviderState& state, int iColumn )
  {
    return NULL;
  }
  
  virtual logical GetCheckable( OTreeProviderState& state )
  {
    return NULL;
  }
  Designer() : Fire() {};
};
private: void _Designer_(){
}

protected  :                                     logical _Link ( ){
}
private: class Link
{
public:
  void* factory;
  OSchemaTreeProvider::CaseMatcher* matcher;
  Designer* designer;
  Link( void *f, Designer* d, OSchemaTreeProvider::CaseMatcher* m ) :
    factory( f ),
    designer( d ),
    matcher( m )
  {
  }
  ~Link()
  {
    if( designer ) delete designer;
    if( matcher ) delete matcher;      
  }
};
private: void _Link_() {
}

protected  :                                     logical _SimpleDesigner ( ){
}
public: class SimpleDesigner : public Designer
{
private:
  QCStringList texts;
  QCStringList pixmaps;
  logical checkable;
public:
  virtual QString GetText( OTreeProviderState& state, int iColumn )
  {
    ODS txt;
    txt.SetParentODS( &state.current );
    txt.SetPath( texts[ iColumn ] );
    txt.SetActive( YES );
    return txt.InstGetString();
  }
  
  virtual QPixmap GetPixmap( OTreeProviderState& state, int iColumn )
  {
    ODS pm;
    pm.SetParentODS( &state.current );
    pm.SetPath( pixmaps[ iColumn ] );
    pm.SetActive( YES );
    return NULL;
  }
  
  virtual logical GetCheckable( OTreeProviderState& state )
  {
    return checkable;
  }

  SimpleDesigner( QCStringList t, QCStringList p, logical c ) :
    Designer(),
    texts( t ),
    pixmaps( p ),
    checkable( c )
   {};
};

private: void _SimpleDesigner_() {
}

};

#endif
