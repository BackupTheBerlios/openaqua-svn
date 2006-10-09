#include "coaformfactory.h"
#include <CoaDebug>
#include <cassert>

#include <CoaFormBuilder>
#include <CoaToolBarBuilder>
#include <CoaMenuBarBuilder>
#include <CoaStatusBarBuilder>
#include <CoaStatusBar>
#include <CoaToolBar>
#include <CoaMenuBar>
#include <CoaMainWindow>
#include <CoaToolWindow>
#include <CoaDialog>
#include <CoaGroupBox>
#include <CoaFile>
//#include <CoaFrame>

#include <QVBoxLayout>

CoaFormFactory::CoaFormFactory( CoaMainWindow* const parent )
      : QObject( parent )
{
   BEGIN;
   assert( parent );
   m_parentWidget = parent;
}


CoaFormFactory::CoaFormFactory( CoaWidget* const parent )
      : QObject( parent )
{
   BEGIN;
   assert( parent );
   m_parentWidget = parent;
}



CoaFormFactory::CoaFormFactory( CoaDialog* const parent )
      : QObject( parent )
{
   BEGIN;
   assert( parent );
   m_parentWidget = parent;
}



CoaFormFactory::~CoaFormFactory()
{
   BEGIN;
}




QWidget* CoaFormFactory::getParentWidget()
{
   BEGIN;
   return m_parentWidget;
}



bool CoaFormFactory::formBuild( QString filename )
{
   BEGIN;
   INF( QString( "build form from file <%1>" ).arg( filename ) );

   //check the file
   CoaFile file( filename );
   if ( ! file.exists () )
   {
      ERR( QString( "Widget description <%1> doesn't exist" ).arg( filename ) );
      RETURN( false );   }


   //open the file
   file.open( QFile::ReadOnly );

   //load the stuff to a widget
   CoaFormBuilder loader;
   QWidget *formWidget = loader.load( &file, getParentWidget() );
   assert( formWidget );
   if ( formWidget == 0 )
   {
      ERR( QString( "Could not create Form from file <%1>" ).arg( filename ) );
      RETURN( false );
   }
   file.close();
   RETURN( true );
}




void CoaFormFactory::statusBarBuild ( QString filename )
{
   BEGIN;
   Q_UNUSED( filename );
#if 0

   CoaStatusBarBuilder builder;

   CoaFile *file = new CoaFile( filename );
   CoaStatusBar * bar = builder.load( file, getParentWidget() );
   assert( bar );
   delete file;

   //getMainWindow()->setStatusBar(bar);

#endif
}





void CoaFormFactory::toolBarBuild ( QString filename )
{
   BEGIN;
   Q_UNUSED( filename );
#if 0

   CoaToolBarBuilder builder;
   CoaFile *file = new CoaFile( filename );

   CoaToolBar *bar = builder.load( file, getParentWidget() );
   assert( bar );
   delete file;

   //getMainWindow()->addToolBar(Qt::TopToolBarArea, bar);
#endif
}





void CoaFormFactory::menuBarBuild ( QString filename )
{
   BEGIN;
   Q_UNUSED( filename );
#if 0

   CoaMenuBarBuilder builder;
   CoaFile *file = new CoaFile( filename );

   CoaMenuBar *bar = builder.load( file, getParentWidget() );
   assert( bar );
   delete file;

   //getMainWindow()->setMenuBar(bar);
#endif
}





