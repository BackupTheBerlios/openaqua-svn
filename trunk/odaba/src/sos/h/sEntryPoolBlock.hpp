/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    EntryPoolBlock

\brief    


\date     $Date: 2006/03/12 19:19:56,37 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   EntryPoolBlock_HPP
#define   EntryPoolBlock_HPP

class     EntryPoolBlock;

#pragma pack(8)

class  EntryPoolBlock
{
protected  :         void                                        *entries;                                                   

public     :
                     void                                        *get_entries() { return(entries); }
public     :                                                             EntryPoolBlock (uint16 size, int16 count );
public     :                                                             ~EntryPoolBlock ( );
};

#pragma pack()
#endif
