/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:33:30,06}|(REF)
\class    ODragObject

\brief    The ODragObject class encapsulates MIME-based data transfer
          The  ODragObject  class  is  a  drag  and drop object for transferring
          ODSItems.

\date     $Date: 2006/03/13 21:34:07,31 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODragObject_HPP
#define   ODragObject_HPP

class     ODragObject;

class     DatabaseHandle;
class     DictionaryHandle;
class     ODS;
class     ODSRegion;
class     ODataWidget;
class     ODragObject;
#include  <sODSItem.hpp>
#include  <sPropertyHandle.hpp>
class  ODragObject :public QDrag
{
protected  :         ODS                                         *data;                                                      //
protected  :         QByteArray                                   enc_text;                                                  //
protected  :         QByteArray                                   enc_propertyhandle;                                        //
protected  :         QByteArray                                   enc_xmlpropertyhandle;                                     //
protected  :         QString                                      textdata;                                                  //
protected  :         PropertyHandle                              *pEncodedPropertyHandle;                                    //

public     :
public     :         OGUI7ImpExp                                         ODragObject (QWidget *dragSource, QString qsText );
public     :         OGUI7ImpExp                                         ODragObject (QWidget *dragSource, ODS *pODS, QString qsText );
public     :                                     logical allow (int64 iAllow, QPixmap *pm_link, QPixmap *pm_copyA, QPixmap *pm_copyB, QPixmap *pm_moveA, QPixmap *pm_moveB );
public     : static  OGUI7ImpExp                 logical __cdecl canDecode (QMimeSource *mimesource );
public     : static  OGUI7ImpExp                 logical __cdecl decode (const QMimeData *pQMimeData, PropertyHandle **ppPropertyHandle, DatabaseHandle **ppDatabaseHandle, DictionaryHandle **ppDictionaryHandle );
public     : static  OGUI7ImpExp                 logical __cdecl decode (const QMimeData *pQMimeData, QString &pQString );
public     :                                     Qt::DropAction drag (Qt::DropActions dropActions );
public     :                                     Qt::DropAction drag ( );
public     : virtual                             QByteArray encodedData (const char *mimetype ) const;
public     :         OGUI7ImpExp                 const char *format (int32 i ) const;
public     : virtual OGUI7ImpExp                 void setData (ODS *pODS, QString qsText );
public     : virtual OGUI7ImpExp                 void setData (QString qsText );
};

#endif
