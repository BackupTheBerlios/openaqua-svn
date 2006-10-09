/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:02,18}|(REF)
\class    SDB_ObjectVE

\brief    Database object version list entry
          A  database object version  list entry defines  the version number and
          the  validity period for the database object version. The presentation
          describes  the external  presentation of  a version  list entry in the
          database. 
          A  maximum  of  65000  versions  can be defined for a database object.
          Database  version entries  are stored  as linked entries, which allays
          allows defining a new database version entry.

\date     $Date: 2006/03/13 21:30:11,09 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   SDB_ObjectVE_HPP
#define   SDB_ObjectVE_HPP

class     SDB_ObjectVE;

#include  <sEB_Number.hpp>
#include  <sdttm.hpp>
#pragma pack(2)

class  SDB_ObjectVE
{
protected  :         uint16                                       version_number;                                            // Version number
protected  :         dttm                                         time_stamp;                                                
protected  :         EB_Number                                    next_object_ve;                                            // Next version entry
protected  :         char                                         reserved[16];                                              // Reserved for future

public     :
                     uint16                                       get_version_number() { return(version_number); }
                     EB_Number                                   &get_next_object_ve() { return(next_object_ve); }
                     char                                        *get_reserved() { return(reserved); }
public     :                                     void FromPIF (logical pif );
public     :                                     void Reset ( );
public     :                                                             SDB_ObjectVE (EB_Number entnr, uint16 version_nr=CUR_VERSION, dttm timestamp=dttm() );
public     :                                     void ToPIF (logical pif );
public     :                                     dttm get_time_stamp ( );
public     :                                     void set_time_stamp (dttm timestamp=dttm() );
};

#pragma pack()
#endif
