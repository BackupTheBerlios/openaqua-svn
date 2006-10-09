#include "coaformbuilder.h"
#include <CoaDebug>
#include <cassert>


#include <CoaTextEdit>
#include <CoaLabel>
#include <CoaDockWidget>
#include <CoaFrame>
#include <CoaGroupBox>
#include <CoaLabel>
#include <CoaLCDNumber>
#include <CoaProgressBar>
#include <CoaStackedWidget>
#include <CoaTabWidget>
#include <CoaTextBrowser>
#include <CoaTextEdit>
#include <CoaLineEdit>
#include <CoaToolBox>
#include <CoaPushButton>
#include <CoaRadioButton>
#include <CoaTreeView>
#include <CoaTreeWidget>
#include <CoaTableView>
#include <CoaCheckBox>
#include <CoaWidget>
#include <CoaDateEdit>
#include <CoaComboBox>
#include <CoaToolButton>
#include <CoaSqlConnectionWidget>
#include <CoaSplitter>
#include <CoaListView>
#include <CoaLineEditView>

#include <CoaDialog>
//#include <CoaMainWindow>
#include <iostream>




CoaFormBuilder::CoaFormBuilder(QObject *parent)
: QUiLoader(parent)
{
   BEGIN;
}

CoaFormBuilder::~CoaFormBuilder()
{
   BEGIN;
}


QWidget *CoaFormBuilder::createWidget( const QString & widgetName, QWidget * parentWidget , const QString & name )
{
   BEGIN;
   
   QWidget *widget = QUiLoader::createWidget(widgetName, parentWidget, name);

   if (widget==0)
   {
      ERR(QString ("Cannot create widget: %1  with name: %2").arg(widgetName ).arg(name));
   }
   
   assert(widget);
   return widget;
}


/**
@warning dont use this method anymore
*/
QWidget *CoaFormBuilder::createWidget2( const QString & widgetName, QWidget * parentWidget , const QString & name )
{
   BEGIN;

   //INF(QString("Request widget for CoaFormBuilder: %1").arg(widgetName));
   //Create default or already registered widgets
   QWidget *w = 0;

   //default doesn't work. Lets try it for our self
   if (widgetName == "QTextEdit")             {  w = new CoaTextEdit(parentWidget);     }
   else if (widgetName == "QLabel")           {  w = new CoaLabel(parentWidget);        }
   else if (widgetName == "QDockWidget")      {  w = new CoaDockWidget(parentWidget);   }
   else if (widgetName == "QFrame")           {  w = new CoaFrame(parentWidget);        }
   else if (widgetName == "QGroupBox")        {  w = new CoaGroupBox(parentWidget);     }
   else if (widgetName == "QLCDNumber")       {  w = new CoaLCDNumber(parentWidget);    }
   else if (widgetName == "QProgressBar")     {  w = new CoaProgressBar(parentWidget);  }
   else if (widgetName == "QStackedWidget")   {  w = new CoaStackedWidget(parentWidget);}
   else if (widgetName == "QTabWidget")       {  w = new CoaTabWidget(parentWidget);    }
   else if (widgetName == "QTextBrowser")     {  w = new CoaTextBrowser(parentWidget);  }
   else if (widgetName == "QLineEdit")        {  w = new CoaLineEdit(parentWidget);     }
   else if (widgetName == "QToolBox")         {  w = new CoaToolBox(parentWidget);      }
   else if (widgetName == "QDialog")          {  w = new CoaDialog(name, parentWidget); }
   else if (widgetName == "QWidget")          {  w = new CoaWidget(parentWidget);       }
   else if (widgetName == "QPushButton")      {  w = new CoaPushButton(parentWidget);   }
   else if (widgetName == "QRadioButton")     {  w = new CoaRadioButton(parentWidget);  }
   else if (widgetName == "QTreeView")        {  w = new CoaTreeView(parentWidget);     }
   else if (widgetName == "QTreeWidget")      {  w = new CoaTreeWidget(parentWidget);   }
   else if (widgetName == "QTableView")       {  w = new CoaTableView(parentWidget);    }
   else if (widgetName == "QListView")        {  w = new CoaListView(parentWidget);     }
   else if (widgetName == "QCheckBox")        {  w = new CoaCheckBox(parentWidget);     }
   else if (widgetName == "QDateEdit")        {  w = new CoaDateEdit(parentWidget);     }
   else if (widgetName == "QComboBox")        {  w = new CoaComboBox(parentWidget);     }
   else if (widgetName == "QToolButton")      {  w = new CoaToolButton(parentWidget);   }
   else if (widgetName == "QSplitter")        {  w = new CoaSplitter(parentWidget);     }

   else if (widgetName == "CoaTextEdit")      {  w = new CoaTextEdit(parentWidget);     }
   else if (widgetName == "CoaLabel")         {  w = new CoaLabel(parentWidget);        }
   else if (widgetName == "CoaDockWidget")    {  w = new CoaDockWidget(parentWidget);   }
   else if (widgetName == "CoaFrame")         {  w = new CoaFrame(parentWidget);        }
   else if (widgetName == "CoaGroupBox")      {  w = new CoaGroupBox(parentWidget);     }
   else if (widgetName == "CoaLCDNumber")     {  w = new CoaLCDNumber(parentWidget);    }
   else if (widgetName == "CoaProgressBar")   {  w = new CoaProgressBar(parentWidget);  }
   else if (widgetName == "CoaStackedWidget") {  w = new CoaStackedWidget(parentWidget);}
   else if (widgetName == "CoaTabWidget")     {  w = new CoaTabWidget(parentWidget);    }
   else if (widgetName == "CoaTextBrowser")   {  w = new CoaTextBrowser(parentWidget);  }
   else if (widgetName == "CoaLineEdit")      {  w = new CoaLineEdit(parentWidget);     }
   else if (widgetName == "CoaToolBox")       {  w = new CoaToolBox(parentWidget);      }
   else if (widgetName == "CoaDialog")        {  w = new CoaDialog(name, parentWidget); }
   else if (widgetName == "CoaWidget")        {  w = new CoaWidget(parentWidget);       }
   else if (widgetName == "CoaPushButton")    {  w = new CoaPushButton(parentWidget);   }
   else if (widgetName == "CoaRadioButton")   {  w = new CoaRadioButton(parentWidget);  }
   else if (widgetName == "CoaTreeView")      {  w = new CoaTreeView(parentWidget);     }
   else if (widgetName == "CoaTreeWidget")    {  w = new CoaTreeWidget(parentWidget);   }
   else if (widgetName == "CoaTableView")     {  w = new CoaTableView(parentWidget);    }
   else if (widgetName == "CoaListView")      {  w = new CoaListView(parentWidget);     }
   else if (widgetName == "CoaCheckBox")      {  w = new CoaCheckBox(parentWidget);     }
   else if (widgetName == "CoaDateEdit")      {  w = new CoaDateEdit(parentWidget);     }
   else if (widgetName == "CoaComboBox")      {  w = new CoaComboBox(parentWidget);     }
   else if (widgetName == "CoaToolButton")    {  w = new CoaToolButton(parentWidget);   }
   else if (widgetName == "CoaSplitter")      {  w = new CoaSplitter(parentWidget);     }
   else if (widgetName == "CoaLineEditView")  {  w = new CoaLineEditView(parentWidget); }

   else if (widgetName == "CoaSqlConnectionWidget") { w = new CoaSqlConnectionWidget(parentWidget);   }



   else {
      WRN(QString("Cannot create widget %1, must use default factory").arg(widgetName) );
      w = QUiLoader::createWidget(widgetName, parentWidget, name);
   }

   if (w == 0) {
      ERR(QString("Unknown Widget requested: %1").arg(widgetName));
   } else {
      w->setObjectName(name);
   }

   assert(w);
   RETURN(w);
}

