/********************************* Class Source Code ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    OSettings

\brief    Settings
          Store User Settings into the System registry

\date     $Date: 2006/04/10 13:46:27,54 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "OSettings"

#include  <pogui7.h>
#include  <sODControl.hpp>
#include  <sODataWidget.hpp>
#include  <sOSettings.hpp>


/******************************************************************************/
/**
\brief  CheckTimeout

\return cond

\param  qsKey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "CheckTimeout"

logical OSettings :: CheckTimeout (const QString qsKey )
{
logical cond = YES;
QString timeout;
QString tspan;
int32   timestamp = 0;
BEGINSEQ

//LEAVESEQ

Initialize();
if(!settings)                                       ERROR
// check the timeout for the key
timestamp = settings->value(qsKey + SZ2QS("_timestamp"),-1).toInt();
if (timestamp==-1 || timestamp==0){ // not found| conversion error
  tspan = settings->value(qsKey + SZ2QS("_timestamp"),-1).toString();
  QStringList sl(tspan.split(":"));
  if(sl.count()==2 && sl[1]==((QApplication*)QCoreApplication::instance())->sessionId())          LEAVESEQ
}else if (timestamp>QDateTime::currentDateTime().toTime_t())
                                                    LEAVESEQ
settings->remove(qsKey);
settings->remove(qsKey+ SZ2QS("_timestamp"));
ERROR

RECOVER
cond = NO;
ENDSEQ
return cond;
}

/******************************************************************************/
/**
\brief  Initialize - 


\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Initialize"

logical OSettings :: Initialize ( )
{
  logical                 term = NO;
  if(!settings)
    settings = new QSettings(SZ2QS("run Software-Werkstatt GmbH"),SZ2QS("ogui"));

  SetBasePath();
  return(term);
}

/******************************************************************************/
/**
\brief  OSettings - Constructor



\param  qsControlType - 
\param  pODataWidget - Parent data widget
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "OSettings"

                        OSettings :: OSettings (QString qsControlType, ODataWidget *pODataWidget )
                     :  settings(NULL)
,qsControlType(qsControlType)
,qsControlName(SZ2QS("NoIdentifierImplemented")
 )
,qsProductName(SZ2QS("ogui"))
,istorecount(0)
,grouped(NO)
,pODataWidget(pODataWidget)
{



}

/******************************************************************************/
/**
\brief  Restore - Restores a Value
        Restores a previous saved value if it exist

\return cond - 
-------------------------------------------------------------------------------
\brief  i00


\param  qsKey - 
\param  rbValue - 
\param  bDefault - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Restore"

logical OSettings :: Restore (const QString qsKey, logical &rbValue, const logical bDefault )
{
  bool                 cond = YES;

BEGINSEQ
  rbValue = bDefault;
  Initialize();  
  if(!settings)                                     ERROR
  if(!CheckTimeout(qsKey))                          ERROR
  rbValue = settings->value(qsKey,bDefault).toBool();

RECOVER
  cond = NO;
  rbValue = bDefault;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i01


\param  qsKey - 
\param  riValue - 
\param  iDefault - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Restore"

logical OSettings :: Restore (const QString qsKey, int32 &riValue, const int32 iDefault )
{
  bool                 cond = YES;
BEGINSEQ
  Initialize();  
  riValue = iDefault;
  if(!settings)                                     ERROR
  if(!CheckTimeout(qsKey))                          ERROR
  riValue = settings->value(qsKey,iDefault).toInt();
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i02


\param  qsKey - 
\param  rqsValue - 
\param  qsDefault - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Restore"

logical OSettings :: Restore (const QString qsKey, QString &rqsValue, const QString qsDefault )
{
  bool                 cond = YES;
BEGINSEQ
  Initialize();  
  rqsValue = qsDefault;
  if(!settings)                                     ERROR
  if(!CheckTimeout(qsKey))                          ERROR

  rqsValue = settings->value(qsKey,qsDefault).toString();
RECOVER
  cond = NO;
  rqsValue = qsDefault;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i03


\param  qsKey - 
\param  rqslValue - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Restore"

logical OSettings :: Restore (const QString qsKey, QStringList &rqslValue )
{
  bool                 cond = YES;
BEGINSEQ
  Initialize();  
  if(!settings)                                     ERROR
  if(!CheckTimeout(qsKey))                          ERROR
  
  rqslValue = settings->value(qsKey,rqslValue).toStringList();
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i04


\param  qsKey - 
\param  rstringvector - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Restore"

logical OSettings :: Restore (const QString qsKey, StringVector &rstringvector )
{
  bool                 cond = YES;
  QStringList          qslValue;
  QStringList::iterator  it;
BEGINSEQ
  Initialize();  
  if(!settings)                                     ERROR
  if(!CheckTimeout(qsKey))                          ERROR
  cond = Restore(qsKey,qslValue);
  rstringvector.clear();
  if(cond)
    for(it = qslValue.begin(); it != qslValue.end(); it++)
      rstringvector.push_back(QS2SZ(*it));

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i05


\param  qsKey - 
\param  rstringvectorvector - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Restore"

logical OSettings :: Restore (const QString qsKey, VECTOR(StringVector) &rstringvectorvector )
{
  bool                 cond = YES;
  int                  i = 0;
  StringVector         stringvector;
  QString              qs;
  QStringList          qslValue;
  QStringList::iterator it;
BEGINSEQ
  Initialize();  
  if(!settings)                                     ERROR
  if(!CheckTimeout(qsKey))                          ERROR
  rstringvectorvector.clear();
  while(cond){
    qslValue.clear();
    cond = Restore(qsKey + SZ2QS("/value") + qs.setNum(i),qslValue);
    stringvector.clear();
    if(cond){
      for(it = qslValue.begin(); it != qslValue.end(); it++)
        stringvector.push_back(QS2SZ(*it));
      if(stringvector.size()>0)
        rstringvectorvector.push_back(StringVector(stringvector));
      else
        cond = NO;
    }
    i++;
  }
  cond = i==0;
  

RECOVER
  cond = NO;
ENDSEQ
  return (cond);
}

/******************************************************************************/
/**
\brief  SetBasePath - Sets the Basepath for the current
        this makes it easy to use variables.

        the basepath should consist of 
        controltype/controlname/

\return term - 

*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetBasePath"

logical OSettings :: SetBasePath ( )
{
  logical                 term = NO;
  char                   *szname = NULL;
BEGINSEQ
  if(! settings )                                    ERROR
  if(grouped)                                        ERROR
  if(qsControlName == "NoIdentifierImplemented"){
    //find a new Identifier //((QObject*)pODataWidget)->objectName()
    if(pODataWidget && pODataWidget->get_od_control())
      szname = pODataWidget->get_od_control()->GetControlName();
    if(szname)
      qsControlName = SZ2QS(szname);
    // not such a great idea.. fills up the registry with
    // lots of data 
    //else
    //  qsControlName.setNum((int)pODataWidget);
  }
  qsBase = qsControlType + SZ2QS("/") 
          +qsControlName + SZ2QS("/");
     
  settings->beginGroup(qsBase);
  grouped = YES;
RECOVER
  term = YES;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  SetTimeout


\param  qsKey - 
\param  qsTimespan
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "SetTimeout"

void OSettings :: SetTimeout (const QString qsKey, QString qsTimespan )
{
QDateTime qtime = QDateTime::currentDateTime();
BEGINSEQ
//LEAVESEQ

Initialize();
if(!settings)                                       ERROR
      if(qsTimespan == "day"){
  qtime.addDays(1);
}else if(qsTimespan == "week"){
  qtime.addDays(7);
}else if(qsTimespan == "application"){
  //TODO add better algorithm
  qtime.addYears(1);
}
settings->setValue(qsKey +  SZ2QS("_timestamp"),qtime.toTime_t());

if(qsTimespan == "runtime"){
  // dont change qtime -> gets invalid next time
  settings->setValue(qsKey +  SZ2QS("_timestamp")
  ,SZ2QS("session:")+((QApplication*)QCoreApplication::instance ())->sessionId());
}


RECOVER

ENDSEQ

}

/******************************************************************************/
/**
\brief  Store - Stores A Value
        -bool
        -int
        -string
        -stringlist

\return cond - 
-------------------------------------------------------------------------------
\brief  i00


\param  qsKey - 
\param  bValue - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical OSettings :: Store (const QString qsKey, logical bValue )
{
  logical                 cond = YES;
BEGINSEQ
  Initialize();  
  if(!settings)                                      ERROR
  settings->setValue(qsKey,bValue);
  cond = settings->status() == QSettings::NoError;
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i01


\param  qsKey - 
\param  iValue - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical OSettings :: Store (const QString qsKey, int32 iValue )
{
  logical                 cond = YES;
BEGINSEQ
  Initialize();  
  if(!settings)                                      ERROR
  settings->setValue(qsKey,iValue);
  cond = settings->status() == QSettings::NoError;
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i02


\param  qsKey - 
\param  qsValue - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical OSettings :: Store (const QString qsKey, QString qsValue )
{
  logical                 cond = YES;
BEGINSEQ
  Initialize();  
  if(!settings)                                      ERROR
  settings->setValue(qsKey,qsValue);
  cond = settings->status() == QSettings::NoError;
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i03


\param  qsKey - 
\param  qslValue - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical OSettings :: Store (const QString qsKey, QStringList qslValue )
{
  logical                 cond = YES;
BEGINSEQ
  Initialize();  
  if(!settings)                                      ERROR
  settings->setValue(qsKey,qslValue);
  cond = settings->status() == QSettings::NoError;
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i04


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical OSettings :: Store ( )
{
  logical                 cond = YES;
BEGINSEQ
  if(! settings )                                    ERROR
  settings->endGroup();
  delete settings;
  settings = NULL;
  grouped = NO;
  istorecount=0;

RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i05


\param  qsKey - 
\param  stringvector - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical OSettings :: Store (const QString qsKey, StringVector stringvector )
{
  logical                 cond = YES;
  StringVector::iterator  it;
  QStringList             qslValue;
BEGINSEQ
  Initialize();  
  if(!settings)                                      ERROR
  
  for(it = stringvector.begin();it!=stringvector.end();it++)
    qslValue.push_back(SZ2QS((*it).c_str()));
  
  cond = Store(qsKey,qslValue);
  qslValue.clear();
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  i06


\param  qsKey - 
\param  stringvectorvector - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "Store"

logical OSettings :: Store (const QString qsKey, VECTOR(StringVector) stringvectorvector )
{
  logical                 cond = YES;
  int                     i = 0;
  QString                 qs;
  std::vector<StringVector>::iterator it;
  StringVector::iterator  iv;
  QStringList             qslValue;
BEGINSEQ
  Initialize();  
  if(!settings)                                      ERROR
  for(it = stringvectorvector.begin();it!=stringvectorvector.end();it++){
    Store(qsKey + SZ2QS("/value") + qs.setNum(i),(*it));
    i++;
  }
RECOVER
  cond = NO;
ENDSEQ
  return(cond);
}

/******************************************************************************/
/**
\brief  UpdateTimeout

-------------------------------------------------------------------------------
\brief  i00


*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateTimeout"

void OSettings :: UpdateTimeout ( )
{



}

/******************************************************************************/
/**
\brief  i01


\param  qsKey - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "UpdateTimeout"

void OSettings :: UpdateTimeout (const QString qsKey )
{



}

/******************************************************************************/
/**
\brief  ~OSettings - Destructor



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "~OSettings"

                        OSettings :: ~OSettings ( )
{

  if(settings) 
    delete settings;

}


