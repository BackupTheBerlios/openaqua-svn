/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/15|16:34:35,87}|(REF)
\class    OSettings

\brief    Settings
          Store User Settings into the System registry

\date     $Date: 2006/03/31 18:35:42,26 $
\dbsource ogui.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OSettings_HPP
#define   OSettings_HPP

class     OSettings;

#ifndef   VECTOR_StringVector_HPP
#define   VECTOR_StringVector_HPP
#include  <sStringVector.hpp>
#include  <sVECTOR.h>
#endif
class     ODataWidget;
#include  <sStringVector.hpp>
class  OSettings
{
protected  :         QSettings                                   *settings;                                                  // 
protected  :         QString                                      qsControlType;                                             // 
protected  :         QString                                      qsProductName;                                             // 
protected  :         QString                                      qsControlName;                                             // 
protected  :         QString                                      qsBase;                                                    // 
protected  :         int32                                        istorecount;                                               // 
protected  :         logical                                      grouped;                                                   
protected  :         ODataWidget                                 *pODataWidget;                                              

public     :
public     :                                     logical CheckTimeout (const QString qsKey );
public     :                                     logical Initialize ( );
public     :                                                             OSettings (QString qsControlType, ODataWidget *pODataWidget );
public     :                                     logical Restore (const QString qsKey, logical &rbValue, const logical bDefault );
public     :                                     logical Restore (const QString qsKey, int32 &riValue, const int32 iDefault );
public     :                                     logical Restore (const QString qsKey, QString &rqsValue, const QString qsDefault );
public     :                                     logical Restore (const QString qsKey, QStringList &rqslValue );
public     :                                     logical Restore (const QString qsKey, StringVector &rstringvector );
public     :                                     logical Restore (const QString qsKey, VECTOR(StringVector) &rstringvectorvector );
public     :                                     logical SetBasePath ( );
public     :                                     void SetTimeout (const QString qsKey, QString qsTimespan );
public     :                                     logical Store (const QString qsKey, logical bValue );
public     :                                     logical Store (const QString qsKey, int32 iValue );
public     :                                     logical Store (const QString qsKey, QString qsValue );
public     :                                     logical Store (const QString qsKey, QStringList qslValue );
public     :                                     logical Store ( );
public     :                                     logical Store (const QString qsKey, StringVector stringvector );
public     :                                     logical Store (const QString qsKey, VECTOR(StringVector) stringvectorvector );
public     :                                     void UpdateTimeout ( );
public     :                                     void UpdateTimeout (const QString qsKey );
public     :                                                             ~OSettings ( );
};

#endif
