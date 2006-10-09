/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    FFileDialog

\brief    Constructs a FileDialog
          Example of use:
          // initialze oehdatawidget
          FFileDialog *fd = new FFileDialog(this,this,(ODS*)NULL);
          fd->SetPath(NULL,NULL,YES,NULL,PT_none);
          fd->ods()->SetParentODS(oTV->List());
          fd->Activate
          Allows to select one file, change the filter (if more than one).
          returns YES; when cancel was pressed

          the selected file is available with GetFilename()();
          // add some filters
          fd->addFilter(SZ2QS("C++ Source (*.cpp *.hpp)"));
          fd->addFilter(SZ2QS("PHP Source (*.php *.inc *.phtml)"));
          fd->addFilter(SZ2QS("Java Source (*.java *.javascript *.vj)"));
          fd->SetFilename(SZ2QS("L:\\ogui8\\QLIB\\BinaryList.cpp"));
          // execute the dialogs
          if(!fd->Open())
          while(!fd->GetFilename().isEmpty())
          QMessageBox::information(this,      SZ2QS("associate")      ,     
          fd->GetFilename(YES) );
          if(!fd->OpenMany())
          while(!fd->GetFilename().isEmpty())
          QMessageBox::information(this,      SZ2QS("associate")      ,     
          fd->GetFilename(YES) );
          if(!fd->OpenDirectory())
          while(!fd->GetFilename().isEmpty())
          QMessageBox::information(this,      SZ2QS("associate")      ,     
          fd->GetFilename(YES) );
          if(!fd->Save())
          while(!fd->GetFilename().isEmpty())
          QMessageBox::information(this,      SZ2QS("associate")      ,     
          fd->GetFilename(YES) );
          // clean up
          delete fd;

\date     $Date: 2006/03/13 21:33:39,42 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   FFileDialog_HPP
#define   FFileDialog_HPP

class     FFileDialog;

class     ODS;
class     ODataWidget;
#include  <sOEHDataWidget.hpp>
class  FFileDialog :public QFileDialog,
public OEHDataWidget
{
protected  :                                                      Q_OBJECT;                                                  //
protected  :         QStringList                                  qslFilter;                                                 //
protected  :         QString                                      qsCaption;                                                 //
protected  :         QString                                      qsFilename;                                                //
protected  :         QStringList                                  qslFilenames;                                              //
protected  :         QString                                      qsDirectory;                                               //

public     :
                     QStringList                                 &get_qslFilter() { return(qslFilter); }
                     QString                                     &get_qsCaption() { return(qsCaption); }
                     QString                                     &get_qsFilename() { return(qsFilename); }
                     QStringList                                 &get_qslFilenames() { return(qslFilenames); }
                     QString                                     &get_qsDirectory() { return(qsDirectory); }
public     :         OGUI7ImpExp                 logical AddFilter (QString qsFilter=SZ2QS("") );
public     :         OGUI7ImpExp                                         FFileDialog (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, QString qsDirName=SZ2QS(""), QString qsFilter=SZ2QS("") );
public     :         OGUI7ImpExp                 QString GetFilename (logical bPop=NO );
protected  :                                     logical Initialize ( );
public     :         OGUI7ImpExp                 logical Open ( );
public     :         OGUI7ImpExp                 logical OpenDirectory ( );
public     :         OGUI7ImpExp                 logical OpenMany ( );
public     :         OGUI7ImpExp                 logical Save ( );
public     :         OGUI7ImpExp                 logical SetBaseDirectory (QString qsValue );
public     :         OGUI7ImpExp                 logical SetCaption (QString qsValue );
public     :         OGUI7ImpExp                 logical SetFilename (QString qsName );
public     :                                     QWidget *WidgetQ ( );
protected  :         OGUI7ImpExp                 QString getFilter ( );
public     :         OGUI7ImpExp                                         ~FFileDialog ( );
};

#endif
