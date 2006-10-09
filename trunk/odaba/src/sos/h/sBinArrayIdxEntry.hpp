/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    BinArrayIdxEntry

\brief    


\date     $Date: 2006/03/12 19:19:37,17 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   BinArrayIdxEntry_HPP
#define   BinArrayIdxEntry_HPP

class     BinArrayIdxEntry;

class     BinArray;
class     BinArrayIdxEntry;
#pragma pack(8)

class  BinArrayIdxEntry
{
protected  :         BinArrayIdxEntry                            *lower_entries[16];                                         
protected  :         BinArrayIdxEntry                            *upper_entry;                                               
protected  :         BinArray                                    *bin_array;                                                 

public     :
                     BinArrayIdxEntry                            *get_upper_entry() { return(upper_entry); }
                     BinArray                                    *get_bin_array() { return(bin_array); }
public     :                                     logical IsEmpty ( );
public     :                                     BinArrayIdxEntry *operator() (int32 indx0 ){

  return(lower_entries[indx0]);

}

public     :                                     BinArrayIdxEntry **operator[] (int32 indx0 ){

  return(&lower_entries[indx0]);

}

};

#pragma pack()
#endif
