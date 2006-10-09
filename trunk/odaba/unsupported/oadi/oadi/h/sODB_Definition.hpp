/********************************* Class Declaration ***************************/
/**
\package  OADI
\class    ODB_Definition



\date     $Date: 2006/04/28 14:51:23,64 $
\dbsource oadi.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODB_Definition_HPP
#define   ODB_Definition_HPP

class     ODB_Definition;

class     PropertyHandle;
#include  <sDString.hpp>
#include  <sOPersistent.hpp>
#pragma pack(4)

class  ODB_Definition :public OPersistent
{
protected  :         char                                        *dbPath;                                                    
protected  :         logical                                      netOpt;                                                    
protected  :         logical                                      writeMode;                                                 

public     :
                     char                                        *get_dbPath() { return(dbPath); }
                     logical                                      get_netOpt() { return(netOpt); }
                     logical                                      get_writeMode() { return(writeMode); }
public     :                                        PIACC GetAccessMode ( );
public     :                                        char *GetPath ( );
public     :                                             ODB_Definition ( );
public     :                                             ODB_Definition (OPersistent bcOPersistent, char *dbPath, logical netOpt, logical writeMode );
public     : virtual                                logical Read (PropertyHandle *ph );
public     :                                        void Reset ( );
public     : virtual                                     ~ODB_Definition ( );
};

#pragma pack()
#endif
