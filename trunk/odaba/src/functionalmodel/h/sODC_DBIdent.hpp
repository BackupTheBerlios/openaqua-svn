/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/13|21:30:26,96}|(REF)
\class    ODC_DBIdent

\brief    Database type identification
          The  resource  identifier  and  the  time  stamp identify the database
          type. When it has been created.

\date     $Date: 2006/03/13 21:30:31,00 $
\dbsource ops.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   ODC_DBIdent_HPP
#define   ODC_DBIdent_HPP

class     ODC_DBIdent;

#pragma pack(8)

class  ODC_DBIdent
{
protected  :         dbdt                                         date;                                                      // Date of database creation
protected  :         dbtm                                         time;                                                      // Time of database creation
protected  :         int32                                        id;                                                        // Resource id

public     :
                     dbdt                                         get_date() { return(date); }
                     dbtm                                         get_time() { return(time); }
                     int32                                        get_id() { return(id); }
};

#pragma pack()
#endif
