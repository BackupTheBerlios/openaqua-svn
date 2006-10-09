/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
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

\date     $Date: 2006/06/30 14:52:13,57 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "FFileDialog"

#include  <pogui7.h>
#include  <mFFileDialog.h>
#include  <sODS.hpp>
#include  <sODataWidget.hpp>
#include  <sFFileDialog.hpp>


/******************************************************************************/
/**
\brief  AddFilter - Adds a filter
        used for open,many and save
        last added filter is selected

\return term - 

\param  qsFilter - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "AddFilter"

logical FFileDialog :: AddFilter (QString qsFilter )
{
  logical                 term = NO;
BEGINSEQ
  if(qsFilter.isEmpty())                             ERROR
  
  qslFilter.push_front(qsFilter);
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  FFileDialog - Constructor



\param  pODataWidget - Parent data widget
\param  oODataWidget - Owning data widget
\param  pODS - 
\param  qsDirName - 
\param  qsFilter - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "FFileDialog"

     FFileDialog :: FFileDialog (ODataWidget *pODataWidget, ODataWidget *oODataWidget, ODS *pODS, QString qsDirName, QString qsFilter )
                     :  OEHDataWidget (
   pODataWidget
  ,oODataWidget
  ,pODS
  )
,QFileDialog(
  pODataWidget->WidgetQ()
  ,SZ2QS("File Dialog")
  ,qsDirName
  ,qsFilter
  )
{

  Initialize();
  AddFilter(qsFilter);
  SetBaseDirectory(qsDirName);

}

/******************************************************************************/
/**
\brief  GetFilename - Returns result of dialog
        returns  a qstring - the first inserted  and deletes it from the list if
        the optional bPop parameter is YES
        usefull for OpenMany
        DON'T call if Open/Save returned YES
        if  you  crash  here  you  did  not catch the 'Cancel' case for the open
        dialog

\return qsFilename - 

\param  bPop - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetFilename"

QString FFileDialog :: GetFilename (logical bPop )
{
  QString filename;
BEGINSEQ
  if(qslFilenames.isEmpty())                        OGUIERR(200)
  filename = qslFilenames.first();
  if (bPop)
    qslFilenames.pop_front();
RECOVER

ENDSEQ
  return filename;
}

/******************************************************************************/
/**
\brief  Initialize - Initialize
        used by Constructor

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical FFileDialog :: Initialize ( )
{
  logical                 term = NO;
  AddFilter(SZ2QS("All Files (*)"));
  qsCaption=SZ2QS("File[Open|Save[as]] Dialog");
  setWindowTitle(qsCaption);

  return(term);
}

/******************************************************************************/
/**
\brief  Open - Simple Open
        Allows to select one file, change the filter (if more than one).
        returns YES; when cancel was pressed

        the selected file is available with GetFilename()

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Open"

logical FFileDialog :: Open ( )
{
  logical term              = NO;
BEGINSEQ
  qslFilenames += getOpenFileName(
    WidgetQ()
   ,"open file dialog"
   ,qsFilename.isEmpty()?qsDirectory:qsFilename
   ,getFilter()
   );
  if(qslFilenames.last().isEmpty())                  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenDirectory - Directory Open
        Allows to select one Directory. (and maybe create one)
        returns YES; when cancel was pressed

        the selected directory is available with GetFilename()

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenDirectory"

logical FFileDialog :: OpenDirectory ( )
{
  logical                 term = NO;
BEGINSEQ
  qslFilenames += getExistingDirectory (
    WidgetQ()
   ,"open files dialog"
   ,qsDirectory
  );

  if(qslFilenames.last().isEmpty())                  ERROR
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  OpenMany - Open Many
        Allows  to select  more than  one file,  change the filter (if more than
        one).
        returns YES; when cancel was pressed

        the selected files are available with GetFilename()
        while(!fd->GetFilename().isEmpty()){
        QString fn = fd->GetFilename(YES);
        dosomethinwith(fn);
        }

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OpenMany"

logical FFileDialog :: OpenMany ( )
{
  logical                 term = NO;
BEGINSEQ
  qslFilenames += getOpenFileNames(
    WidgetQ()
   ,"open files dialog"
   ,qsDirectory
   ,getFilter()
  );
  if(qslFilenames.last().isEmpty())                  ERROR

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  Save - Save
        Allows to select one File and Change the availabe filters.
        You may enter a filename that not yet exists
        returns YES; when cancel was pressed
        the selected file is available with GetFilename()

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Save"

logical FFileDialog :: Save ( )
{
  logical                term = NO;
BEGINSEQ
  qslFilenames += QFileDialog::getSaveFileName(
    WidgetQ()
   ,"save file dialog"
   ,qsFilename.isEmpty()?qsDirectory:qsFilename
   ,getFilter()
   );
   
  if(qslFilenames.last().isEmpty()){
    qslFilenames.pop_back();
    ERROR
  }

RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetBaseDirectory - Sets Base Directory
        if no file is given (SetFilename)
        this directory will be selected/shown when the dialog executes

\return term - 

\param  qsValue - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBaseDirectory"

logical FFileDialog :: SetBaseDirectory (QString qsValue )
{
  logical                 term = NO;
BEGINSEQ
  if(qsValue.isEmpty())                             ERROR
  
  qsDirectory = qsValue;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetCaption - Caption
        Sets the Caption of the Dialog

\return term - 

\param  qsValue - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetCaption"

logical FFileDialog :: SetCaption (QString qsValue )
{
  logical                 term = NO;
BEGINSEQ
  if(qsValue.isEmpty())                             ERROR
//  setWindowTitle(qsValue);
  qsCaption = qsValue;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetFilename - Set Filename
        to  provide  a  filename  (maybe  for  saveas or open) you can specify a
        filename

\return term - 

\param  qsName - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetFilename"

logical FFileDialog :: SetFilename (QString qsName )
{
  logical                 term = NO;
  // maybe needed to 'forget' about filenames 
  // - so no checking for isEmpty 
  qsFilename = qsName;
  return(term);
}

/******************************************************************************/
/**
\brief  WidgetQ - WidgetQ
        QWidget

\return pQWidget - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "WidgetQ"

QWidget *FFileDialog :: WidgetQ ( )
{


  return(this);
}

/******************************************************************************/
/**
\brief  getFilter - private
        returns a valid filterstring

\return qsFilter - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "getFilter"

QString FFileDialog :: getFilter ( )
{

  return qslFilter.join(SZ2QS(";;"));

}

/******************************************************************************/
/**
\brief  ~FFileDialog - destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~FFileDialog"

     FFileDialog :: ~FFileDialog ( )
{



}


