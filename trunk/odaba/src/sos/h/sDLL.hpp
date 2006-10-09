/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:19:18,18}|(REF)
\class    DLL

\brief    


\date     $Date: 2006/03/12 19:19:52,90 $
\dbsource sos.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DLL_HPP
#define   DLL_HPP

class     DLL;

#ifndef   DLL_itp_HPP
#define   DLL_itp_HPP
#include  <sDLL.h>
#endif
#include  <sQuList.hpp>
#pragma pack(8)

class  DLL :public QuList
{

public     :
public     :                                     itp *RemoveHead ( );
public     :                                     void AddHead (itp *itpptr ){



}

public     :                                     void AddTail (itp *itpptr ){



}

public     :                                                             DLL ( ){



}

public     :                                                             DLL (DLL(itp) &dllref ){



}

public     :                                     int Find (itp *itpptr ){



}

public     :                                     int FindIndex (int index0 ){



}

public     :                                     itp *GetAt ( ){



}

public     :                                     int GetCount ( ){



}

public     :                                     itp *GetHead ( ){



}

public     :                                     itp *GetNext ( ){



}

public     :                                     itp *GetPrev ( ){



}

public     :                                     itp *GetTail ( ){



}

public     :                                     void GoBottom ( ){



}

public     :                                     void GoTop ( ){



}

public     :                                     void InsertAfter (itp *itpptr ){



}

public     :                                     void InsertBefore (itp *itpptr ){



}

public     :                                     itp *RemoveAt ( ){



}

public     :                                     itp *RemoveTail ( ){



}

public     :                                     void SetAt (itp *itpptr ){



}

public     :                                                             ~DLL ( ){



}

};

#pragma pack()
#endif
