/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ObjectExt

\brief    Database object instance (external)
          When  creating a  database object  in the  database, a database object
          instance  is  created,  which  is  the  root  for  accessing  extents,
          sub-objects  and  other  resources  of  the  database  object.  This 
          structure  is  equivalent  to  SDB_ObjectID,  but defines the external
          presentation of a database object instance.

\date     $Date: 2006/03/13 21:30:10,85 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_ObjectExt_HPP
#define   SDB_ObjectExt_HPP

class     SDB_ObjectExt;

class     SDBOExt;
#include  <sEB_Number.hpp>
#include  <sSDB_Object.hpp>
#pragma pack(8)

class  SDB_ObjectExt
{
protected  :         EB_Number                                    derivates;                                                 // Reserved for future
protected  :         EB_Number                                    extends;                                                   // Reserved for future
protected  :         EB_Number                                    version_list;                                              // Reserved for future
protected  :         int32                                        object_id;                                                 // Internal database object number
protected  :         uint16                                       version;                                                   // Current version
protected  :         uint16                                       db_version;                                                // Database version

public     :
                     EB_Number                                   &get_derivates() { return(derivates); }
                     EB_Number                                   &get_extends() { return(extends); }
                     EB_Number                                   &get_version_list() { return(version_list); }
                     int32                                        get_object_id() { return(object_id); }
                     uint16                                       get_version() { return(version); }
                     uint16                                       get_db_version() { return(db_version); }
public     :                                     void ConvertTo6 (logical pif );
public     :                                     void FromPIF (logical pif );
public     :                                     void InitVersion (EB_Number entnr, uint16 version_nr=CUR_VERSION );
public     :                                                             SDB_ObjectExt (int32 objid );
public     :                                                             SDB_ObjectExt (SDB_ObjectExt &extobj_ref );
public     :                                     void ToPIF (logical pif );
public     :                                     EB_Number *get_extends_ptr ( ){

  return ( &extends );

}

};

#pragma pack()
#endif
