/********************************* Class Source Code ***************************/
/**
\package  OGUI - 
\class    ODragObject

\brief    The ODragObject class encapsulates MIME-based data transfer
          The  ODragObject  class  is  a  drag  and drop object for transferring
          ODSItems.

\date     $Date: 2006/08/29 20:15:48,46 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#define    OBJ_ID  "ODragObject"

#include  <pogui7.h>
#include  <cqt.h>
#include  <cDragAndDropActions.h>
#include  <sDatabaseHandle.hpp>
#include  <sDictionaryHandle.hpp>
#include  <sODS.hpp>
#include  <sODSItem.hpp>
#include  <sODSRegion.hpp>
#include  <sODataWidget.hpp>
#include  <sODragObject.hpp>
#include  <sPropertyHandle.hpp>
#include  <sODragObject.hpp>


/******************************************************************************/
/**
\brief  ODragObject - Constructor

        Sets data of the starting drag

\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dragSource - 
\param  qsText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODragObject"

     ODragObject :: ODragObject (QWidget *dragSource, QString qsText )
                     : QDrag (dragSource)
{

  setData(qsText);


}

/******************************************************************************/
/**
\brief  i01 - 



\param  dragSource - 
\param  pODS - 
\param  qsText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "ODragObject"

     ODragObject :: ODragObject (QWidget *dragSource, ODS *pODS, QString qsText )
                     : QDrag (dragSource)
{

  setData(pODS,qsText);
  setData(qsText);


}

/******************************************************************************/
/**
\brief  allow - 



\return term - 

\param  iAllow - 
\param  pm_link - 
\param  pm_copyA - 
\param  pm_copyB - 
\param  pm_moveA - 
\param  pm_moveB - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "allow"

logical ODragObject :: allow (int64 iAllow, QPixmap *pm_link, QPixmap *pm_copyA, QPixmap *pm_copyB, QPixmap *pm_moveA, QPixmap *pm_moveB )
{
  logical                 term = NO;
  int                     ipixcount = 0;
  QPixmap                *allowed   = NULL;
  
  if(DNDA_CopyA & iAllow) ipixcount++;
  if(DNDA_CopyB & iAllow) ipixcount++;
  if(DNDA_MoveA & iAllow) ipixcount++;
  if(DNDA_MoveB & iAllow) ipixcount++;
  if(DNDA_Link  & iAllow) ipixcount++;
  /*
  allowed = new QPixmap(QImage(ipixcount*pm_link->width(),pm_link->height(),32));
  ipixcount = 0;
  if(DNDA_CopyA & iAllow){
    bitBlt(allowed,32*ipixcount,1,pm_copyA,0,0,32,32,CopyROP);
    ipixcount++;
  }
  if(DNDA_CopyB & iAllow){
    bitBlt(allowed,32*ipixcount,1,pm_copyB,0,0,32,32,CopyROP);
    ipixcount++;
  }
  if(DNDA_MoveA & iAllow){
    bitBlt(allowed,32*ipixcount,1,pm_moveA,0,0,32,32,CopyROP);
    ipixcount++;
  }
  if(DNDA_MoveB & iAllow){
    bitBlt(allowed,32*ipixcount,1,pm_moveB,0,0,32,32,CopyROP);
    ipixcount++;
  }
  if(DNDA_Link & iAllow){
    bitBlt(allowed,32*ipixcount,1,pm_link,0,0,32,32,CopyROP);
    ipixcount++;
  }
  setPixmap(*allowed,QPoint(-16,-16));
  */
  return(term);
}

/******************************************************************************/
/**
\brief  canDecode - 

        Returns  TRUE if the information in [mimetype] can be decoded. otherwise
        returns FALSE.

\return term - 

\param  mimesource - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "canDecode"

logical __cdecl ODragObject :: canDecode (QMimeSource *mimesource )
{
  logical                 term = NO;
BEGINSEQ
  if(!mimesource)                                    ERROR
  if(mimesource->provides("application/vnd.odaba.propertyhandle"))
    term |= YES;
  if(mimesource->provides("text/plain"))
    term |= YES;
  if(mimesource->provides("text/xml"))
    term |= YES;


RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  decode - 

        Attempts  to decode the dropped  information in [mimesource] into [data]
        Returns TRUE if successful; otherwise returns FALSE.

\return term - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  pQMimeData - 
\param  ppPropertyHandle - 
\param  ppDatabaseHandle - 
\param  ppDictionaryHandle - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "decode"

logical __cdecl ODragObject :: decode (const QMimeData *pQMimeData, PropertyHandle **ppPropertyHandle, DatabaseHandle **ppDatabaseHandle, DictionaryHandle **ppDictionaryHandle )
{
  logical                 term = NO;
  /* decoding data */
  QTextCodec             *codec = QTextCodec::codecForLocale();
  QByteArray              payload;
  QString                 qsText;
  QRegExp                 regex;
  bool                    ok;
  /* decoded raw data*/
  int                     inst_id           = 0;
  int                     ipph              = 0;
  int                     iqapp             = 0;
  int                     idbh              = 0;
  int                     ithis             = 0;
  QString                 szdbpath;
  QString                 szdictpath;
  /* decoded handles */


BEGINSEQ
  if(!pQMimeData)                                    ERROR
  if(!pQMimeData->hasFormat("application/vnd.odaba.propertyhandle"))
                                                     ERROR
  qsText = pQMimeData->data("application/vnd.odaba.propertyhandle");
  /* qstext contains:
     inst_id\npph\nqApp\ndbhandle\ndatabase\ndictionary
   */
  regex.setPattern(SZ2QS("^(.*)\n(.*)\n(.*)\n(.*)\n(.*)\n(.*)\n(.*)$"));
  regex.indexIn(qsText);
  inst_id    = regex.cap(1).toInt(&ok,10);
  ipph       = regex.cap(2).toInt(&ok,16);
  iqapp      = regex.cap(3).toInt(&ok,16);
  idbh       = regex.cap(4).toInt(&ok,16);
  ithis      = regex.cap(5).toInt(&ok,16);
  szdbpath   = regex.cap(6);
  szdictpath = regex.cap(7);
  
  /* well now we get that property handle */
  if(QCoreApplication::instance() == (QCoreApplication*)iqapp){
    *ppDatabaseHandle   = (DatabaseHandle*)idbh;
    *ppDictionaryHandle = NULL;
    *ppPropertyHandle   = (PropertyHandle*)ipph;

    // *ppPropertyHandle->OpenHierachy(NULL);
  }else{
    ODABAClient oclient;
    *ppDictionaryHandle = new DictionaryHandle(oclient,QS2SZ(szdictpath),PI_Read,YES);
    *ppDatabaseHandle = new DatabaseHandle(*(*ppDictionaryHandle),QS2SZ(szdbpath),PI_Read,YES);
    *ppPropertyHandle = new PropertyHandle( *(*ppDatabaseHandle), "VOID",PI_Read);
    // *ppODragObject    = NULL;
    (*ppPropertyHandle)->Get(inst_id);
  }

RECOVER
  term = NO;
ENDSEQ
  return(term);
}

/******************************************************************************/
/**
\brief  i01 - 



\param  pQMimeData - 
\param  pQString - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "decode"

logical __cdecl ODragObject :: decode (const QMimeData *pQMimeData, QString &pQString )
{
  logical                 term = YES;

BEGINSEQ
  if(!pQMimeData)                                    ERROR
  pQString = pQMimeData->text();



RECOVER
  term = YES;
ENDSEQ
  return (term);
}

/******************************************************************************/
/**
\brief  drag - 



\return dropAction - 
-------------------------------------------------------------------------------
\brief  i0 - 



\param  dropActions - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "drag"

Qt::DropAction ODragObject :: drag (Qt::DropActions dropActions )
{
  Qt::DropAction          dropAction;
  dropAction = start(dropActions);
  return(dropAction);
}

/******************************************************************************/
/**
\brief  i01 - 



*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "drag"

Qt::DropAction ODragObject :: drag ( )
{

  return drag(Qt::CopyAction | Qt::MoveAction);

}

/******************************************************************************/
/**
\brief  encodedData - returns QByteArray

        decodes data to a qbytearray

\return term - 

\param  mimetype - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "encodedData"

QByteArray ODragObject :: encodedData (const char *mimetype ) const
{
  QByteArray                 term = QByteArray();
  if(!strcmp(mimetype,"application/vnd.odaba.propertyhandle")){
    return enc_propertyhandle;
  }
  if(!strcmp(mimetype,"text/plain")){
    return enc_text;
  }
  if(!strcmp(mimetype,"text/xml")){
    return enc_xmlpropertyhandle;
  }

  return(term);
}

/******************************************************************************/
/**
\brief  format - format

        returns format of current drag

\return term - 

\param  i - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "format"

const char *ODragObject :: format (int32 i ) const
{

  switch ( i )
  {
    case    0:
      return "application/vnd.odaba.propertyhandle";
              break;
    case    1:
      return "text/plain";
              break;     
    case    2:
      return "text/xml";
              break;     
  }

  return(NULL);
}

/******************************************************************************/
/**
\brief  setData - sets data

        uses  pODS to store the current  propertyhandle into a string and qsText
        to store ascii data for other applications

-------------------------------------------------------------------------------
\brief  i0 - 



\param  pODS - 
\param  qsText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setData"

void ODragObject :: setData (ODS *pODS, QString qsText )
{
  QString                          dbpath,dictpath,s,xmlinstance;
  PropertyHandle                   *ph = NULL;
  int                               inst_id= 0;
  DatabaseHandle                   *dbh   = NULL;
  inst_id= pODS->InstGetObjID();
  ph = pODS->Handle();
  if(ph){
    ph->ExtractKey();
    dbh     = &ph->GetDBHandle();
    dbpath = SZ2QS(dbh->GetPath());
    dictpath = SZ2QS(dbh->GetDictionary().GetPath());
    pEncodedPropertyHandle = new PropertyHandle();
    pEncodedPropertyHandle->OpenHierarchy(ph); 
    pEncodedPropertyHandle->ExtractKey();
    ph->ExtractKey();
  }else{
    dbpath = SZ2QS("undefined");
    dbpath = SZ2QS("undefined");
    dbh    = NULL;
  }
  xmlinstance   = SZ2QS("<instance id=\"%i\" propertyhandle=\"%p\" applicationhandle=\"%p\" databasehandle=\"%p\" odragobject=\"%p\" databasepath=\"%s\" dictionarypath=\"%s\">\n%s\n</instance>");
  s.sprintf(QS2SZ(xmlinstance),inst_id,pEncodedPropertyHandle,QCoreApplication::instance(),dbh,this,QS2SZ(dbpath),QS2SZ(dictpath),QS2SZ(qsText));
  enc_xmlpropertyhandle.resize( s.length() );
  memcpy( enc_xmlpropertyhandle.data(), s.toLatin1(), s.length() );

  xmlinstance   = SZ2QS("%i\n%p\n%p\n%p\n%p\n%s\n%s");
  s.sprintf(QS2SZ(xmlinstance),inst_id,pEncodedPropertyHandle,QCoreApplication::instance(),dbh,this,QS2SZ(dbpath),QS2SZ(dictpath));
  enc_propertyhandle.resize( s.length() );
  memcpy( enc_propertyhandle.data(), s.toLatin1(), s.length() );



}

/******************************************************************************/
/**
\brief  i01 - 



\param  qsText - 
*/
/******************************************************************************/

#undef     MOD_ID
#define    MOD_ID  "setData"

void ODragObject :: setData (QString qsText )
{

  enc_text.resize( qsText.length() );
  memcpy( enc_text.data(), qsText.toLatin1(), qsText.length() );



}


