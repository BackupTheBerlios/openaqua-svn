/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BinSArrayObjEntry

\brief    


\date     $Date: 2006/03/12 19:19:38,67 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BinSArrayObjEntry_HPP
#define   BinSArrayObjEntry_HPP

class     BinSArrayObjEntry;

#pragma pack(8)

class  BinSArrayObjEntry
{
protected  :         int64                                        object_id;                                                 

public     :
                     int64                                        get_object_id() { return(object_id); }
public     :                                     void Initialize ( );
public     :                                     void SetIndex (uint64 entry_index );
};

#pragma pack()
#endif
