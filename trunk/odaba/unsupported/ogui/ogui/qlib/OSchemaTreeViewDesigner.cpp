/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    OSchemaTreeViewDesigner

\brief    


\date     $Date: 2006/03/13 21:36:13,54 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSchemaTreeViewDesigner"

#include  <pogui7.h>
#include  <cqt.h>
#include  <motrdssh.h>
#include  <mOSchemaTreeViewDesigner.h>
#include  <sOSchemaTreeProvider.hpp>
#include  <sOSchemaTreeViewDesigner.hpp>


/******************************************************************************/
/**
\brief  Add - 


\return term -

\param  pvoidFactory -
\param  pDesigner -
\param  pOSchemaTreeProviderCaseMatcher -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Add"

logical OSchemaTreeViewDesigner :: Add (void *pvoidFactory, Designer *pDesigner, OSchemaTreeProvider::CaseMatcher *pOSchemaTreeProviderCaseMatcher )
{

QListVoid* l= def.find( pvoidFactory );
if( !l )
{
  l= new QListVoid();
  l->setAutoDelete( YES );
  def.insert( pvoidFactory, l );
}
l->append( new Link( pvoidFactory, pDesigner, pOSchemaTreeProviderCaseMatcher ) );

}

/******************************************************************************/
/**
\brief  AddSimple - 


\return term -

\param  pvoidFactory -
\param  rcqcTexts -
\param  rcqcPixmaps -
\param  pOSchemaTreeProviderCaseMatcher -
\param  fCheckable -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddSimple"

OSchemaTreeViewDesigner::Designer *OSchemaTreeViewDesigner :: AddSimple (void *pvoidFactory, const QCString &rcqcTexts, const QCString &rcqcPixmaps, OSchemaTreeProvider::CaseMatcher *pOSchemaTreeProviderCaseMatcher, logical fCheckable )
{

SimpleDesigner* d= new SimpleDesigner( Tools::splitQCString( rcqcTexts, "," ), Tools::splitQCString( rcqcPixmaps, "," ), fCheckable );
Add( pvoidFactory, d, pOSchemaTreeProviderCaseMatcher );
return d;

}

/******************************************************************************/
/**
\brief  Fire - 



\param  rOTreeProviderState -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Fire"

void OSchemaTreeViewDesigner :: Fire (OTreeProviderState &rOTreeProviderState )
{

BEGINSEQ
Designer* d= getDesigner( rOTreeProviderState );
if( !d ) ERROR
emit d->Fire.FireFire();
RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  OSchemaTreeViewDesigner - 


\return term -

\param  pOSchemaTreeProvider -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSchemaTreeViewDesigner"

                        OSchemaTreeViewDesigner :: OSchemaTreeViewDesigner (OSchemaTreeProvider *pOSchemaTreeProvider )
                     : OTreeViewDesigner (),
  def(),
  schema(pOSchemaTreeProvider),
  lastState(-1)
{

def.setAutoDelete( YES );

}

/******************************************************************************/
/**
\brief  doGetCheckable - 


\return term -

\param  rOTreeProviderState -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doGetCheckable"

logical OSchemaTreeViewDesigner :: doGetCheckable (OTreeProviderState &rOTreeProviderState )
{

BEGINSEQ
Designer* d= getDesigner( rOTreeProviderState );
if( !d ) ERROR
return d->GetCheckable( rOTreeProviderState );
RECOVER
return NO;
ENDSEQ

}

/******************************************************************************/
/**
\brief  doGetPixmap - 


\return term -

\param  rOTreeProviderState -
\param  iColumn -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doGetPixmap"

QPixmap OSchemaTreeViewDesigner :: doGetPixmap (OTreeProviderState &rOTreeProviderState, int32 iColumn )
{

BEGINSEQ
Designer* d= getDesigner( rOTreeProviderState );
if( !d ) ERROR
return d->GetPixmap( rOTreeProviderState, iColumn );
RECOVER
return NULL;
ENDSEQ

}

/******************************************************************************/
/**
\brief  doGetText - 


\return term -

\param  rOTreeProviderState -
\param  iColumn -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "doGetText"

QString OSchemaTreeViewDesigner :: doGetText (OTreeProviderState &rOTreeProviderState, int32 iColumn )
{

BEGINSEQ
Designer* d= getDesigner( rOTreeProviderState );
if( !d ) ERROR
return d->GetText( rOTreeProviderState, iColumn );
RECOVER
return QString();
ENDSEQ

}

/******************************************************************************/
/**
\brief  getDesigner - 


\return term -

\param  rOTreeProviderState -
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getDesigner"

OSchemaTreeViewDesigner::Designer *OSchemaTreeViewDesigner :: getDesigner (OTreeProviderState &rOTreeProviderState )
{

if( rOTreeProviderState.id == lastState ) return lastDesigner;

Designer* d= NULL;

void* f= schema->GetFactory( rOTreeProviderState.currentNode );
QListVoid* l= def.find( f );
if( l )
{
  for( Link* k= (Link*) l->first(); k; k= (Link*) l->next() )
    if( !k->matcher || k->matcher->Match( &rOTreeProviderState ) )
    {
      d= k->designer;
      break;
    }
}

lastState= rOTreeProviderState.id;
lastDesigner= d;

return d;

}


