/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    RootBaseEntry

\brief    


\date     $Date: 2006/03/12 19:13:47,18 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   RootBaseEntry_HPP
#define   RootBaseEntry_HPP

class     RootBaseEntry;

class     db_RootBase;
#pragma pack(8)

class  RootBaseEntry
{
protected  :         char                                         database_id[10];                                           //
protected  :         db_RootBase                                 *root_base;                                                 //
protected  :         char                                         database_path[129];                                        //

public     :
                     char                                        *get_database_id() { return(database_id); }
                     db_RootBase                                 *get_root_base() { return(root_base); }
                     char                                        *get_database_path() { return(database_path); }
public     :                                                             RootBaseEntry (char *db_id, db_RootBase *rootbase, char *cpath );
public     :                                                             ~RootBaseEntry ( );
};

#pragma pack()
#endif
