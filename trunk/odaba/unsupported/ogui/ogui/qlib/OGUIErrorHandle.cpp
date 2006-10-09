/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    OGUIErrorHandle

\brief    


\date     $Date: 2006/08/28 07:47:23,79 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OGUIErrorHandle"

#include  <pogui7.h>
#include  <sError.hpp>
#include  <sErrorMessage.hpp>
#include  <sOGUIErrorHandle.hpp>


/******************************************************************************/
/**
\brief  GetDecision - 



\return cond - 

\param  error_obj - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "GetDecision"

logical OGUIErrorHandle :: GetDecision (Error *error_obj )
{

  return ( QMessageBox::question(NULL,SZ2QS("Question"),SZ2QS(error_obj->get_text()),
                                 QMessageBox::Ok,QMessageBox::Cancel,0)  
           == QMessageBox::Cancel ? NO : YES );

}

/******************************************************************************/
/**
\brief  OGUIErrorHandle - 



\return term - 

\param  _obhandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OGUIErrorHandle"

     OGUIErrorHandle :: OGUIErrorHandle (DBObjectHandle &_obhandle )
                     : DBErrorHandle (_obhandle)
{

  ActivateGUIMessages();
  
  SystemServices()->SetErrorHandle(this);


}

/******************************************************************************/
/**
\brief  ShowMessage - 



\return term - 

\param  pError - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ShowMessage"

logical OGUIErrorHandle :: ShowMessage (Error *pError )
{
  logical           term = NO;
BEGINSEQ
  if ( !gui_message )                                ERROR

  if ( GetApplicationContext() )
  {
    ErrorHandle::ShowMessage(pError);                LEAVESEQ
  }
  
  QPixmap icon;
  QString b1, b2;
  QString cancel;
  
  b1= SZ2QS( "OK" );
  
  if ( strncmp(language,"EN",2) == 0 ) 
    cancel = SZ2QS("Cancel");
  else 
    cancel = SZ2QS("Abbruch");

  switch ( pError->type )
  {
    case  'D' : b2= cancel; 
    case  'M' : /*icon= QMessaeBox::Querstion;*/         break;
    case  'S' : // das muss auf die Statuszeile
    case  'I' : icon= QMessageBox::standardIcon(QMessageBox::Information);      break;
    case  'W' : icon= QMessageBox::standardIcon(QMessageBox::Warning);          break;
//    case  'E' : icon= QMessageBox::standardIcon(QMessageBox::Error);            break;
    default   : icon= QMessageBox::standardIcon(QMessageBox::Critical);
  }
  
  QMessageBox   mb( 
    SZ2QS(pError->GetTitle()), 
    SZ2QS(pError->GetText()), 
    QMessageBox::NoIcon,
    b1.isEmpty() ? 0 : QMessageBox::Yes | QMessageBox::Default,
    b2.isEmpty() ? 0 : QMessageBox::No | QMessageBox::Escape, NULL );
    
  if ( !b1.isEmpty() ) 
    mb.setButtonText(QMessageBox::Yes,b1);
  if ( !b2.isEmpty() ) 
    mb.setButtonText(QMessageBox::No,b2);
  
  mb.setIconPixmap(icon);
    
  term = mb.exec() == QMessageBox::Yes ? NO : YES;
   

RECOVER
  term = YES;
ENDSEQ
  return(term);
}


