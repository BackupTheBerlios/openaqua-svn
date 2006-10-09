/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    OBH_ListEntry

\brief    


\date     $Date: 2006/03/12 19:13:41,14 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   OBH_ListEntry_HPP
#define   OBH_ListEntry_HPP

class     OBH_ListEntry;

class     ACObject;
#pragma pack(8)

class  OBH_ListEntry
{
protected  :         uint32                                       version;                                                   
protected  :         ACObject                                    *ob_handle;                                                 

public     :
                     uint32                                       get_version() { return(version); }
                     ACObject                                    *get_ob_handle() { return(ob_handle); }
public     :                                                             OBH_ListEntry (ACObject *obhandle, uint16 version_nr=CUR_VERSION );
public     :                                     void set_version (uint16 version_nr=CUR_VERSION );
};

#pragma pack()
#endif
