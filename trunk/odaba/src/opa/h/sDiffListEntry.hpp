/********************************* Class Declaration ***************************/
/**
\package  {{{{{|{2006/03/12|19:11:33,12}|(REF)
\class    DiffListEntry

\brief    


\date     $Date: 2006/03/12 19:13:12,26 $
\dbsource opa.dev - ODABA Version 9.0
*/
/******************************************************************************/
#ifndef   DiffListEntry_HPP
#define   DiffListEntry_HPP

class     DiffListEntry;

#define  DIFFLISTENTRY                             20
#include  <sEB_Number.hpp>
#pragma pack(8)

class  DiffListEntry
{
protected  :         EB_Number                                    add_ebi;                                                   //
protected  :         EB_Number                                    del_ebi;                                                   //
protected  :         int32                                        ws_number;                                                 
protected  :         char                                         key;                                                       

public     :
                     EB_Number                                   &get_add_ebi() { return(add_ebi); }
                     EB_Number                                   &get_del_ebi() { return(del_ebi); }
                     int32                                        get_ws_number() { return(ws_number); }
                     char                                         get_key() { return(key); }
public     :                                     void FromPIF ( );
public     :                                     char *GetKey ( );
public     :                                     char IndexDifference ( );
public     :                                     char IndexDifferencePlus ( );
public     :                                     void Init (int32 ws_num, char *skey, int16 klen );
public     :                                     void ToPIF ( );
public     :                                     void set_ws_number (int32 wsnumber );
public     :                                                             ~DiffListEntry ( );
};

#pragma pack()
#endif
