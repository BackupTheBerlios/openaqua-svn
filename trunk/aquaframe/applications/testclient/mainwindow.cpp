#include "mainwindow.h"

#include <CoaDebug>
#include <CoaWorkbench>
#include <CoaFormFactory>
#include <CoaApplication>
#include <CoaString>
#include <CoaToolButton>
#include <CoaFileDialog>
#include <CoaWorkspace>
#include <CoaFile>
#include <CoaLineEditView>
#include <CoaLineEdit>

#include <CoaWidgetController>

#include <CoaMessageBox>
#include <QCloseEvent>
#include <QHeaderView>
#include <QTableWidget>



MainWindow::MainWindow( const CoaString& objectName, CoaWorkspace *const parent, Qt::WFlags flags )
      : CoaApplicationWindow( objectName, parent, flags )
      , m_btnRemAction( 0 )
      , m_btnAddAction( 0 )
      , m_table1( 0 )
      , m_dataSetModel( this )
      , m_corbaClient (m_dataSetModel, this)
{
   BEGIN;
   m_dataSetModel.start();
}





MainWindow::~MainWindow()
{
   BEGIN;
   //unregister all widgets, quit the model
   m_dataSetModel.unregisterWidgets(*this);
   m_dataSetModel.quit();

   //store settings
   writeSettings();

   //wait untill the model is finished
   m_dataSetModel.wait();
}



void MainWindow::initialize()
{
   BEGIN;


   //Build the Window itself
   Q_INIT_RESOURCE( actioneditor );
   CoaFormFactory factory( this );
   factory.formBuild( ":/form/mainwindow.ui" );
   readSettings();

   //register all widgets
   m_dataSetModel.registerWidgets(*this);

   //set up the table1
   m_table1 = qFindChild<QTableWidget*> ( this, "table1" );
   assert( m_table1 );
   m_table1->setColumnCount( 1 );
   m_table1->setRowCount( 1 );

   //setup the corbaclient
   m_corbaClient.initialize();
   setEnabled(m_corbaClient.isValid());
   m_corbaClient.slotGotoFirst();

   //connects form buttons
   assert( qFindChild<CoaPushButton*>( this, "btnFirst" ) );
   assert( qFindChild<CoaPushButton*>( this, "btnPrev" ) );
   assert( qFindChild<CoaPushButton*>( this, "btnNext" ) );
   assert( qFindChild<CoaPushButton*>( this, "btnLast" ) );
   connect ( qFindChild<CoaPushButton*>( this, "btnFirst" ), SIGNAL( clicked() ), &m_corbaClient, SLOT( slotGotoFirst() ) );
   connect ( qFindChild<CoaPushButton*>( this, "btnPrev" ), SIGNAL( clicked() ), &m_corbaClient, SLOT( slotGotoPrev() ) );
   connect ( qFindChild<CoaPushButton*>( this, "btnNext" ), SIGNAL( clicked() ), &m_corbaClient, SLOT( slotGotoNext() ) );
   connect ( qFindChild<CoaPushButton*>( this, "btnLast" ), SIGNAL( clicked() ), &m_corbaClient, SLOT( slotGotoLast() ) );


   //connect (qFindChild<CoaPushButton*>(this, "btnReqTime"),  SIGNAL(clicked()), &myConnection, SLOT(reqTime()));
   //connect (qFindChild<CoaPushButton*>(this, "btnReqSize"),  SIGNAL(clicked()), &myConnection, SLOT(reqTabSize()));
   //connect ( qFindChild<CoaPushButton*>( this, "btnReqContent" ), SIGNAL( clicked() ), this, SLOT( reqTableContent() ) );


   //start the network connection
   //connect (&myConnection, SIGNAL(newMessage(const CoaString& )), this, SLOT(slotNewMessage(const CoaString& )));
   //connect (&myConnection, SIGNAL(newTime(const CoaString& )),    this, SLOT(slotNewTime(const CoaString& )));
   //connect (&myConnection, SIGNAL(newError(const CoaString& )),   this, SLOT(slotNewError(const CoaString& )));
   //connect (&myConnection, SIGNAL(changeTableSize(const int, const int )),   this, SLOT(resizeTable1(const int, const int )));
   //connect (&myConnection, SIGNAL(tableContent(int, int, const QVariant )),  this, SLOT(setTableContent(int, int, const QVariant& )));

   //connect (this, SIGNAL(newMessage(const CoaString& )), &myConnection, SLOT(reqStr(const CoaString& )));
   connect ( m_table1, SIGNAL( itemSelectionChanged () ), this, SLOT( reqTableContent() ) );




}

void MainWindow::saveChanges()
{
   BEGIN;
}


void MainWindow::saveChangesAs()
{
   BEGIN;
}


void MainWindow::closeEvent( QCloseEvent *ev )
{
   BEGIN;

   if ( isWindowModified() == true )
   {
      raise();

      QMessageBox box( tr( "Save Changes?" ),
                       tr( "Do you want to save the changes you made before closing?" ),
                       QMessageBox::Question,
                       QMessageBox::Yes | QMessageBox::Default,
                       QMessageBox::No,
                       QMessageBox::Cancel | QMessageBox::Escape,
                       this, Qt::Sheet );
      box.setButtonText( QMessageBox::Yes, tr( "Save" ) );
      box.setButtonText( QMessageBox::No, tr( "Don't Save" ) );

      switch ( box.exec() )
      {
         case QMessageBox::Yes:
            {
               saveChanges();
               setWindowModified( false ); // Not really necessary, but stops problems if we get close again.
               //getWorkbench()->remWindow(this);
               ev->accept();
               break;
            }
         case QMessageBox::No:
            {
               setWindowModified( false ); // Not really necessary, but stops problems if we get close again.
               //getWorkbench()->remWindow(this);
               ev->accept();
               break;
            }
         default:
            {
               ev->ignore();
               break;
            }
      }
   }
}



void MainWindow::resizeTable1( const int col, const int row )
{
   BEGIN;
   m_table1->setColumnCount( col );
   m_table1->setRowCount( row );


}




void MainWindow::reqTableContent()
{
   BEGIN;
   QRect rec = m_table1->contentsRect();
   QModelIndex tl = m_table1->indexAt ( rec.topLeft() );
   QModelIndex br = m_table1->indexAt ( rec.bottomRight() );
   int colFrom, colTo, rowFrom, rowTo;
   colFrom = tl.column();
   colTo = br.column();
   rowFrom = tl.row();
   rowTo = br.row();
   if ( colFrom < 1 )
      colFrom = 1;
   if ( colTo < 1 )
      colTo = m_table1->columnCount () ;
   if ( rowFrom < 1 )
      rowFrom = 1;
   if ( rowTo < 1 )
      rowTo = m_table1->rowCount () ;
   //myConnection.reqTabContent(colFrom, colTo, rowFrom, rowTo);
}




void MainWindow::setTableContent( int col, int row, const QVariant& value )
{
   BEGIN;
   INF( CoaString( "Update Cell at pos %1 %2 with val %3" ).arg( col ).arg( row ).arg( value.toString() ) );
   QTableWidgetItem * item = m_table1->item ( row, col );
   if ( item != 0 )
   {
      item->setData( Qt::DisplayRole, value );
   }
   else
   {
      item = new QTableWidgetItem();
      item->setData( Qt::DisplayRole, value );
      m_table1->setItem( row, col, item );
      ERR( "No Table Item found .." );
   }
}


bool MainWindow::editingBegin()
{
   BEGIN;
   RETURN( true );
}


bool MainWindow::editingCommit()
{
   BEGIN;
   RETURN( true );
}


bool MainWindow::editingRollback()
{
   BEGIN;
   RETURN( true );
}

