/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    GSRT

\brief    


\date     $Date: 2006/03/12 19:20:01,00 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   GSRT_HPP
#define   GSRT_HPP

class     GSRT;

class     fmcb;
#include  <ssrt.hpp>
#pragma pack(8)

class  GSRT :public srt
{

public     :
public     :                                     void Clear ( );
public     :                                     int16 AddEntry (int16 indx, itp *itpptr ){



}

public     :                                     int16 AddEntry (itp *itpptr ){



}

public     :                                     itp *AddFreeEntry ( ){



}

public     :                                     logical DeleteEntry (int16 indx ){



}

public     :                                     int16 FindEntry (void *skey ){



}

public     :                                                             GSRT (void *pscbptr, int32 maxe, int16 elen, int16 klen, int16 kpos, char ktype, logical expand ){



}

public     :                                                             GSRT (void *pscbptr, int32 ecnt, int16 elen, int16 klen, int16 kpos, char ktype, itp *itp_table, logical expand ){



}

public     :                                     int16 GetCount ( ){



}

public     :                                     itp *GetEntry (int16 indx ){



}

public     :                                     itp *GetEntry (void *skey ){
  itp                    *itpptr = NULL;

  return(itpptr);
}

public     :                                     int16 GetEntryLength ( ){



}

public     :                                     itp *GetFreeEntry ( ){



}

public     :                                     int16 GetKeyLength ( ){



}

public     :                                     void *GetPool ( ){



}

public     :                                     itp *GetTable ( ){



}

public     :                                     void SetTable (itp *itp_table ){



}

public     :                                     logical SortTable (int16 kpos, int16 klen, char ktype ){



}

public     :                                     itp *UpdateEntry (itp *itpptr, int16 indx ){



}

};

#pragma pack()
#endif
