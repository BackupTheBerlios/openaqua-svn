/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    VersionEntry

\brief    


\date     $Date: 2006/03/12 19:13:56,84 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   VersionEntry_HPP
#define   VersionEntry_HPP

class     VersionEntry;

#pragma pack(8)

class  VersionEntry
{
protected  :         uint16                                       version;                                                   
protected  :         dttm                                         time_stamp;                                                

public     :
                     uint16                                       get_version() { return(version); }
                     dttm                                        &get_time_stamp() { return(time_stamp); }
public     :                                                             VersionEntry (uint16 version_nr=CUR_VERSION, dttm timestamp=dttm() );
};

#pragma pack()
#endif
