/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    OApplication



\date     $Date: 2006/04/28 16:10:48,29 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OApplication_HPP
#define   OApplication_HPP

class     OApplication;

#ifndef   DLL_OApplication_HPP
#define   DLL_OApplication_HPP
#include  <sOApplication.hpp>
#include  <sDLL.h>
#endif
class     OApplication;
class     PropertyHandle;
#include  <sDString.hpp>
#include  <sODB_Definition.hpp>
#include  <sODataSourceHaving.hpp>
#include  <sOWindow.hpp>
#pragma pack(4)

class  OApplication :public OWindow,
public ODataSourceHaving
{
protected  :         DLL(OApplication)                            subApplications;                                           
protected  :         logical                                      subApplicationsRead;                                       
protected  :         char                                        *object;                                                    
protected  :         int                                          language;                                                  
protected  :         ODB_Definition                               database;                                                  

public     :
                     int                                         &get_language() { return(language); }
                     ODB_Definition                              &get_database() { return(database); }
public     : virtual                                void *CastPointer (char *typenames );
public     :                                        int32 CreateInstance (void **instptrp );
public     :                                        logical FileTools ( );
public     :                  OADIImpExp            DataSourceHandle *GetDAT ( ) const;
public     :                  OADIImpExp            DataSourceHandle *GetRES ( ) const;
public     :                  OADIImpExp                 OApplication ( );
public     :                  OADIImpExp                 OApplication (OWindow bcOWindow, ODataSourceHaving bcODataSourceHaving, DLL(OApplication) subApplications, logical subApplicationsRead, char *sobject, int ilanguage, ODB_Definition odatabase );
public     : virtual                                TControl *Open (char *typenames, TControl *tparent, logical active_f );
public     : virtual                                logical Read (PropertyHandle *ph );
protected  :                                        logical ReadSubApplications (PropertyHandle *ph );
public     : virtual                                void Reset ( );
public     :                  OADIImpExp            OApplication *SubApplicationByName (const DString &rcdsName );
public     : virtual                                const char *fieldControlPHName ( ) const;
public     : virtual                                     ~OApplication ( );
};

#pragma pack()
#endif
